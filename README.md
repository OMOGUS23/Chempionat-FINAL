# Модули
# ${\color{}Экспуатация ~Сервисных ~Ботов}$
## МОДУЛЬ А
### Подключение робота
1. Настройка wifi
    - Переходим в директорию на CD карте
    ```
    /etc/wpa_supplicant/wpa_supplicant.conf
    ```
    - Редактируем файл wpa_supplicant.conf
    ```
    network={
        ssid="WIFI_NETWORK_NAME"
        psk="wifipassword"
    }
    ```
    - Редактируем ssid (название сети) и psk (пароль сети)
2. Изменение имени робота
    - Переходим в директорию
    ```
    /etc
    ```
    - В ней находим hostname и редактирем его
    ```
    sudo nano hostname
    ```
    - Изменяем turelbroXX на номер своего робота
3. Если все сделано успешно пытаемся подключиться
    ```
    ssh pi@192.168.1.XX - где XX Ip робота
    или
    ssh pi@turtelbroXX.local
    ```
### Внесение данных в "Акт о приеме"
1. Название дистрибутива Linux и кодовое имя сборки Linux
    ```
    lsb_release -a
    ```
2. Версия библиотеки rospy
    ```
    rosservice rospy
    ```
3. Размер оперативной памяти (Мбайт)
    ```
    free -M
    ```
4. Допустимый диапазон частот подключения робота к сети 5 ГГц
    ```
    iwconfig
    ```
5. Что бы узнать напряжение из топика
    ```
    rostopic echo /bat
    ```
6. IMU датчик работает корректно
    ```
    rostopic echo /imu
    ```
    - Смотрим на показатель *W*
7. Для проверки кнопок D22-D25 переходим по
      [ссылке](https://github.com/voltbro/ws-sro/tree/main/Turtlebro-tester)
    - Переходим в скетч Turtlebro-tester.ino
    - Копируем его и вставляем в Arduino
### Внесение данных в "Инструкция по вводу робота в эксплуатацию"
1. Первая часть
    - Присвоенное имя робота в сети
    ```
    hostname
    ```
    - IP-адрес робота в сети роутера-полигона
    ```
    ifconfig
    ```
    - Текущая частота подключения робота к сети 5 ГГц
    ```
    iwconfig
    Для этого нужно быть подключенным к сети TurtleBro5G
    ```
    - Текущая частота подключения робота к сети 2.4 ГГц
    ```
    iwconfig
    Для этого нужно быть подключенным к сети TurtleBro
    ```
2. Вторая часть
    - Название дистрибутива Linux и кодовое имя Linux
    ```
    lsb_release -a
    ```
    - Версия интерпретатора Python3
    ```
    python3 -V
    ```
    - Версия библиотеки rospy
    ```
    rosversion rospy
    ```
    - Версия пакета turtlebro
    ```
    rosversion turtlebro
    ```
    - Версия прошивки микроконтроллера материнской платы
    ```
    rosservice call /board_info "request: {}"
    ```
    - Размер оперативной памяти (Мбайт)
    ```
    free -M
    ```
    - Текущий часовой пояс на роботе в формате “Time zone:Continent/City (XXX, +XXXX)”
    ```
    timedatectl | grep "Time zone"
    ```
    - Серийный номер Raspberry Pi 4
    ```
    cat /proc/cpuinfo | grep Serial
    ```
    - Топики из инструкции к роботу присутствуют на роботе
    ```
    rostopic list
    ```
3. Третья часть
    - Температура процессора в градусах (С)
    ```
    cat 
    ```
    - Текущее разрешение камеры (пикселей)
    ```
    v4l-ctl --all
    ```
    - Значение напряжения аккумуляторной сборки из топика батареи
    ```
    rostopic echo /bat
    ```
4. Четвертая часть
    - Камера работоспособна
    ```
    Переходим по:
    192.168.1.XX:8008
    ```
    - Одометрия корректна при линейном движении робота
    ```
    Для коррекного отображения значений нужно проехать по линейки определленное расстояние
    И сравнить его со значениями показанными в вед-интерфейсе (192.168.1.XX:8008)
    ```
    - Одометрия корректна при угловом вращении робота
    ```
     В левую сторону положительная, а в правую отрицательная
    ```
    - IMU датчик работает корректно
    ```
    rostopic echo /imu
    ```
    - Лидар работает корректно
    ```
    rostopic echo /scan
    ```
    - Стерео-акустическая система работает корректно
    ```
    echo "Однажды, в студеную зимнюю пору Я из лесу вышел. Был сильный мороз." | festival --tts --language russian
    ```
    - Сервопривод работает корректно [(ссылка)](https://github.com/HeT-HuKa/-/blob/main/Servo.ino)
    - Концевой выключатель работает корректно [(ссылка)](https://github.com/voltbro/ws-sro/blob/main/TB-limit_switch-tester/)
    - Нажимная кнопка работает корректно [(ссылка)](https://github.com/HeT-HuKa/-/blob/main/Button.ino)
    - Проверка светодиодной подсветки и кнопок D22-D25 [(ссылка)](https://github.com/voltbro/ws-sro/tree/main/Turtlebro-tester)
    - Связь контроллера расширения с ROS работает [(ссылка)](https://github.com/voltbro/ws-sro/tree/main/TB-ros-tester)
        - Проверяем его
        ```
        rostopic echo /arduino_connect_tester
        ```
    ## МОДУЛЬ Б
   1.Остановить процесс, чтобы не было сбоев в работе
     ```
     sudo systemctl stop robohead.service
     ```
   2.Открыть файл со списком фраз
     ```
     robohead_ws/src/robohead/robohead_controller/config/voice_recognizer_pocketsphinx/kwslist.txt
     ```
   3.Меняем
      ```
      эйголова/1e-40/ - меняем только фразу(цифры не трогаем)
      ```
   4.открываем файл
      ```
      robohead_ws/src/robohead/robohead_controller/config/voice_recognizer_pocketsphinx/dictionary.txt
      ```
   5. Вместо текущей ключевой фразы впишите новую ключевую фразу:
      ```
      # dictionary.txt
        эйголова - меняем на "Привет, Сири"
        покажи
        уши
        левое
        правое
        поздоровайся
        сделай
        фото
        следи
        за
        шариком
6. Сгенерировать файл с фонетическими записями командой:
   ```
       ~/robohead_ws/src/ru4sphinx/text2dict/dict2transcript.pl \
      ~/robohead_ws/src/robohead/robohead_controller/config/voice_recognizer_pocketsphinx/dictionary.txt \
      ~/robohead_ws/src/robohead/robohead_controller/config/voice_recognizer_pocketsphinx/dictionary.dict
   ``` 
      
     ## МОДУЛЬ Б2
   1.Добавление команды в список голосовых фраз(файл config/commands.json)
      ```
      {
        "commands": {
         "покажи глазки": "show_eyes",
         "поздоровайся": "say_hello",
         "покажи уши": "show_ears",
         "покажи левое ухо": "show_left_ear",
         "покажи правое ухо": "show_right_ear"
          }
        }
      ```
   2.В коде узла (например, src/voice_commands.cpp) нужно подписаться на топик распознавания и добавить новую реакцию:
     ```
     #include <ros/ros.h>
     #include <std_msgs/String.h>

        void commandCallback(const std_msgs::String::ConstPtr& msg) {
        std::string cmd = msg->data;

      if (cmd == "show_eyes") {
        ROS_INFO("Команда: покажи глазки");

        // 1. Показать изображение на экране
        system("rosrun robohead display_image.py images/eyes.png &");

        // 2. Проиграть фразу через динамик
        system("espeak -v ru \"Вот мои глазки\" &");

        // 3. Задействовать серво (шея и уши)
        system("rosrun robohead move_servos.py --neck --ears --time 10");

        // 4. Длительность < 15 секунд
        ros::Duration(10.0).sleep();
    }

    else if (cmd == "say_hello") {
        ROS_INFO("Команда: поздоровайся");
        // существующий код
    }

    // другие команды...

    int main(int argc, char** argv) {
        ros::init(argc, argv, "voice_command_handler");
        ros::NodeHandle nh;

        ros::Subscriber sub = nh.subscribe("/voice_commands", 10, commandCallback);

        ros::spin();
        return 0;
    }
    ```
   3.Запустить распознавание
     ```
     roslaunch robohead voice_recognition.launch
     ```
      ## МОДУЛЬ Б3
   1. Сначала пишем скрипт для подсчета и вывода команды "Осмотрись":
      ```
          #!/usr/bin/env python 3
          import sys

          if len(sys.argv) != 2:
              print("Использование: python count_osm.py log.txt")
              sys.exit(1)

       loggile = sys.argv[1]
        count = 0

        with open(logfile, "r", encoding="utf-8") as f:
            for line in f:
                if "Команда: осмотрись" in line.lower():
                    count += 1

      print(f"Количество вызовов команды 'осмотрись': {count}")

2. Теперь напишем скрипт для последовательности посещения комнат:
    ```
        #!/usr/bin/env python 3
        import sys
    
        if len(sys.argv) != 2:
        print("Использование: python rooms_seq.py log.txt")
        sys.exit(1)

    logfile = sys.argv[1]
    rooms = []

    with open(logfile, "r", encoding="utf-8") as f:
        for line in f:
            if "переход в комнату:" in line.lower():
                room = line.strip().split(":")[-1].strip()
                rooms.append(room)

    print("Последовательность посещение комнат:")
    print(" → ".join(rooms))
   ``` 
3. Последовательность запуска:
    1)Запусти скрипт для подсчета вызовов "Осмотрись":
    На экране появится число, например: "Количество вызовов команды 'осмотрись': 3"
    2)Запусти скрипт для анализа посещения комнат:
    python3 rooms_seq.py logs.txt
    
        
     
     

      
