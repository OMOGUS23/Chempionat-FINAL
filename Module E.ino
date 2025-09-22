#include <PubSubClient.h>

#include <WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "MLX90614.h" //Можно поставить любой другой датчик

// --- Настройки WI-FI и MQTT ---
const char* ssid = "YourSSID";
const char* password = "YourPassword";
const char* mqtt_server = "192.168.1.100"; // Адрес брокера
const char* topic_temp = "robot/temperature";

// --- Объекты ---
WiFiClient espClient;
PubSubClient client(espClient);
Servo servo;
Adafruit_NeoPixel leds(1, 5, NEO_GRB + NEO_KHZ800); //светодиод на пине 5
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// --- Переменные ---
int servoPin = 4;
float avgTemp = 0.0;
bool commandMeasure = false;

// --- Подключение WI-FI ---
void setup_wifi(){
  delay(100);
  Wifi.begin(ssid, password);
  while (WIFI.status() != WL_CONNECTED){
    delay(500);
  }
}

// --- Подключение к MQTT ---
void reconnect(){
  while (!client.connected()){
    if (client.connect("RobotClient")){
      client.subscribe("robot/commands");
    } else{
      delay(5000);
    }
  }
}

// --- Callback MQTT ---
void callback(char* topic, byte* payload, unsigned int length){
  String message;
  for (int i = 0; i < length; i++){
    message += (char)payload[i];
  }

  if (message == "измерь температуру"){
    commandMeasure = true;
  }
}

// ---Измерение и публикация температуры ---
void measureTemperature(){
  //усредняем 10 измерений
  float sum = 0;
  for (int i = 0; i < 10; i++){
    sum += mlx.readObjectTempC();
    delay(100);
  }
  avgTemp = sum / 10.0;

  //публикуем в топик
  char buf[16];
  dtostrf(avgTemp, 4, 2, buf);
  client.publish(topic_temp, buf);
}

// --- Алгоритм движения и подсветки ---
void executeSequence(){
  //влево -45°, красный
  servo.write(45);
  setColor(255, 0, 0);
  measureTemperature();
  delay(15000);

  //Вправо +45, желтый
  servo.write(135);
  setcolor(255, 255, 0);
  measureTemperature();
  delay(15000);

  //возврат в старт
  servo.write(90);
  setColor(0,0,0);
  commandMeasure = false;
}

// --- Setup ---
void setup(){
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  servo.attach(servoPin);
  leds.begin()
  mlx.begin();

  // Автоматический запуск голосового управления
  Serial.println("Голосовое управление активно");
  //(инициализация голосового модуля по UART/I2C)
}

// --- Loop ---
void loop(){
  if (!client.connected()){
    reconnect();
  }
  client.loop();

  if (commandMeasure){
    executeSequence();
  }
}
  }
}
