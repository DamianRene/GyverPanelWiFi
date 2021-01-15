// ****************** ПРОФИЛИ УСТРОЙСТВ *******************

// ВНИМАНИЕ!!! 

// Для плат Wemos D1 mini / Wemos D1 pro в настройках компиляции выбирайте "NodeMCU 1.0(ESP-12E Module)"
// --------------------------------------------------------
// При использовании платы микроконтроллера Wemos D1 (xxxx) и выбранной в менеджере плат "Wemos D1 (xxxx)"
// прошивка скорее всего нормально работать не будет. 
// Наблюдались следующие сбои у разных пользователей:
// - нестабильная работа WiFi (постоянные отваливания и пропадание сети) - попробуйте варианты с разным значением параметров компиляции IwIP в Arduino IDE
// - прекращение вывода контрольной информации в Serial.print()
// - настройки в EEPROM не сохраняются
// Думаю все эти проблемы из-за некорректной работы ядра ESP8266 для платы (варианта компиляции) Wemos D1 (xxxx) в версии ядра ESP8266
// --------------------------------------------------------
//
// Если вы собираетесь испорльзовать возможность сохранения нарисованных в WiFiPlayer картинок в файловой системе микроконтроллера,
// в меню "Инструменты" Arduino IDE в настройке распределения памяти устройства выберите вариант:
//   Для микроконтроллеров ESP8266 с 4МБ флэш-памяти рекомендуется вариант "Flash Size: 4MB(FS:2MB OTA:~1019KB)"
//   Для микроконтроллеров ESP32   с 4МБ флэш-памяти рекомендуется вариант "Partition scheme: Default 4MB with spiff(1.2MB APP/1.5MB SPIFFS)"; 
// Также для ESP32 требуется дополнительно установить библиотеку 'LittleFS_esp32'
//
// --------------------------------------------------------
//
// Текущая версия ядра ESP32 не видит SD-карты более 4GB
//
// --------------------------------------------------------
//
// Ниже в этом файле размещены профили устройств, реально существующие в природе, 
// которые поддерживаются автром - прошивка в них периодически обновлется по мере развития проекта.
//
// Вам не нужно ориентироваться на устройства, имеющиеся у автора - вы должны определить параметры для ВАШЕГО собственного устройства,
// с ВАШИМ набором оборудования (или отсутстивем оного), набором возможностей, размером матирицы и параметрами подключения к ней. 
//
// В вашем проекте на ESP8266 рекомендуется использовать DEVICE_ID 0 и в этом профиле указать параметры ВАШЕГО проекта в блоке #if (DEVICE_ID == 0) ... #endif
// Если вы используете микроконтроллер ESP32 - используйте DEVICE_ID 0 и определяйте параметры ВАШЕГО проекта в блоке строк 383-413 внутри #if defined(ESP32) ... #endif
//
// --------------------------------------------------------

// Профиль устройства, под которое выполняется компиляция и сборка проекта
#define HOST_NAME   F("WiFiPanel")
#define DEVICE_ID   0               // 0 - тестовый стенд
                                    // 1 - часы на кухне
                                    // 2 - часы на столе
                                    // 3 - панель на стене
                                    // 4 - гирлянда на балконе
                                    // 5 - часы у Даши
                                    // 6 - часы в фоторамке

// ================== Тестовый стенд =====================

#if (DEVICE_ID == 0)
/*
 * Wemos D1 mini
 * Физическое подключение:
 * Матрица зигзаг, левый верхний угол, направление вниз
 * Пин ленты    - D2
 * Пин кнопки   - D4
 * 
 * В менеджере плат выбрано NodeMCU v1.0 (ESP-12E)
 */
#if defined(ESP8266)
#define WIDTH 48              // ширина матрицы
#define HEIGHT 16             // высота матрицы
#define DEVICE_TYPE 1         // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define MATRIX_TYPE 0         // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 1    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 3     // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
#define USE_SD 1              // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 0             // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 0          // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 0           // 1 - использовать отключение питания матрицы через MOSFET / реле; 0 - не использовать 
#define USE_MQTT 0            // 1 - использовать управление по MQTT-каналу; 0 - не использовать 
#define USE_WEATHER 1         // 1 - использовать получение информации о текущей погоде; 0 - не использовать 

#define A_DEF_PASS 1          // 1 - Настройки MQTT и API KEY OpenWeatherMap в отдельном файле a_def_pass.h     (пароли и ключи доступа как приватные данные в отдельном файле)
                              // 0 - Настройки MQTT и API KEY OpenWeatherMap в скетче в a_def_soft.h в строках: (пароли и ключи доступа определены в тексте скетча)
                              //   299 - DEFAULT_MQTT_SERVER // Требуется если в a_def_hard.h ваша настройка USE_MQTT == 1
                              //   303 - DEFAULT_MQTT_USER   // Требуется если в a_def_hard.h ваша настройка USE_MQTT == 1
                              //   307 - DEFAULT_MQTT_PASS   // Требуется если в a_def_hard.h ваша настройка USE_MQTT == 1
                              //   311 - DEFAULT_MQTT_PORT   // Требуется если в a_def_hard.h ваша настройка USE_MQTT == 1
                              //   315 - DEFAULT_MQTT_PREFIX // Требуется если в a_def_hard.h ваша настройка USE_MQTT == 1
                              //   319 - MQTT_SEND_DELAY     // Требуется если в a_def_hard.h ваша настройка USE_MQTT == 1
                              //   426 - WEATHER_API_KEY     // Требуется если в a_def_hard.h ваша настройка USE_WEATHER == 1 для погоды с OpenWeatherMap
                              // Файл a_def_pass.h в комплект не входит, нужно создать, скопировать туда указанные строки

#define LED_PIN  2            // D2 пин ленты
#define PIN_BTN D4            // кнопка подключена сюда (D4 --- КНОПКА --- GND)
#define POWER_PIN D1          // D1 управляющий пин вкл/выкл матрицы через MOSFET / реле; POWER_ON - HIGH, POWER_OFF - LOW
#define SD_CS_PIN D8          // пин выбора SD карты - ChipSelect; Также SD карта использует D5 (CLK), D6 (MISO), D7 (MOSI)
#define SRX D3                // к TX MP3 DFPlayer - требуется для компиляции скетча (USE_MP3 == 1)
#define STX D4                // к RX MP3 DFPlayer - требуется для компиляции скетча (USE_MP3 == 1)
#define DIO D5                // D5 TM1637 display DIO pin - требуется для компиляции скетча (USE_TM1637 == 1)
#define CLK D7                // D7 TM1637 display CLK pin - требуется для компиляции скетча (USE_TM1637 == 1)

#endif
#endif

// =================== Часы на кухне ====================

#if (DEVICE_ID == 1)
/*
 * Wemos D1 mini
 * Физическое подключение:
 * Матрица зигзаг, правый нижний угол, направление вверх
 * Пин ленты    - D3
 * Пин кнопки   - D2
 * MP3Player    - не подключен
 * TM1637       - не подключен
 * В менеджере плат выбрано NodeMCU v1.0 (ESP-12E)
 */ 
#if defined(ESP8266)
#define WIDTH 16              // ширина матрицы
#define HEIGHT 16             // высота матрицы
#define DEVICE_TYPE 1         // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define MATRIX_TYPE 0         // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 3    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 1     // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
#define USE_SD 0              // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 0             // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 0          // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 0           // 1 - использовать отключение питания матрицы через MOSFET; 0 - не использовать 
#define USE_MQTT 0            // 1 - использовать управление по MQTT-каналу; 0 - не использовать 
#define USE_WEATHER 1         // 1 - использовать получение информации о текущей погоде; 0 - не использовать 

#define A_DEF_PASS 1          // 1 - Настройки MQTT и API KEY OpenWeatherMap в отдельном файле a_def_pass.h
                              // 0 - Настройки MQTT и API KEY OpenWeatherMap в скетче в a_def_soft.h в строках:
                              // Смотри комментарий к блоку DEVICE_ID == 0

#define LED_PIN 3             // пин ленты
#define PIN_BTN 4             // кнопка подключена сюда (PIN --- КНОПКА --- GND)
#define POWER_PIN D1          // D1 управляющий пин вкл/выкл матрицы через MOSFET
/*
#define SD_CS_PIN D8          // пин выбора SD карты - ChipSelect; Также SD карта использует D5 (CLK), D6 (MISO), D7 (MOSI)
*/
#define SRX D4                // не используется, но требуется для компиляции скетча (USE_MP3==1)
#define STX D3                // не используется, но требуется для компиляции скетча (USE_MP3==1)
/*
#define DIO D5                // D5 TM1637 display DIO pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
#define CLK D7                // D7 TM1637 display CLK pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
*/
#endif
#endif

// =================== Часы на столе ====================

#if (DEVICE_ID == 2)
/*
 * NodeMCU v1.0 (ESP-12E)
 * Физическое подключение:
 * Матрица зигзаг, левый нижний угол, направление вправо
 * Пин ленты    - D2
 * Пин кнопки   - D6
 * MP3Player    - D3 к RX, D4 к TX плеера 
 * TM1637       - не подключен
 * В менеджере плат выбрано NodeMCU v1.0 (ESP-12E)
 */ 
#if defined(ESP8266)
#define WIDTH 16              // ширина матрицы
#define HEIGHT 16             // высота матрицы
#define DEVICE_TYPE 1         // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define MATRIX_TYPE 0         // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 0    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 0     // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
#define USE_SD 0              // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 1             // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 0          // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 0           // 1 - использовать отключение питания матрицы через MOSFET; 0 - не использовать 
#define USE_MQTT 0            // 1 - использовать управление по MQTT-каналу; 0 - не использовать 
#define USE_WEATHER 1         // 1 - использовать получение информации о текущей погоде; 0 - не использовать 

#define A_DEF_PASS 1          // 1 - Настройки MQTT и API KEY OpenWeatherMap в отдельном файле a_def_pass.h
                              // 0 - Настройки MQTT и API KEY OpenWeatherMap в скетче в a_def_soft.h в строках:
                              // Смотри комментарий к блоку DEVICE_ID == 0

#define LED_PIN 2             // пин ленты
#define PIN_BTN D6            // кнопка подключена сюда (PIN --- КНОПКА --- GND)
#define POWER_PIN D1          // D1 управляющий пин вкл/выкл матрицы через MOSFET
/*
#define SD_CS_PIN D8          // пин выбора SD карты - ChipSelect; Также SD карта использует D5 (CLK), D6 (MISO), D7 (MOSI)
*/
#define SRX D4                // не используется, но требуется для компиляции скетча (USE_MP3==1)
#define STX D3                // не используется, но требуется для компиляции скетча (USE_MP3==1)
/*
#define DIO D5                // D5 TM1637 display DIO pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
#define CLK D7                // D7 TM1637 display CLK pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
*/
#endif
#endif

// ============= Панель на стене ====================

#if (DEVICE_ID == 3)
/*
 * Wemos D1 mini
 * Физическое подключение:
 * Матрица зигзаг, левый нижний угол, направление вправо
 * Пин ленты    - D2
 * Пин кнопки   - D4
 * В менеджере плат выбрано NodeMCU v1.0 (ESP-12E)
 */ 
#if defined(ESP8266)
#define WIDTH 50              // ширина матрицы
#define HEIGHT 20             // высота матрицы
#define DEVICE_TYPE 1         // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define MATRIX_TYPE 0         // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 0    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 0     // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
#define USE_SD 1              // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 0             // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 0          // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 1           // 1 - использовать отключение питания матрицы через MOSFET; 0 - не использовать 
#define USE_MQTT 1            // 1 - использовать управление по MQTT-каналу; 0 - не использовать 
#define USE_WEATHER 1         // 1 - использовать получение информации о текущей погоде; 0 - не использовать 

#define A_DEF_PASS 1          // 1 - Настройки MQTT и API KEY OpenWeatherMap в отдельном файле a_def_pass.h
                              // 0 - Настройки MQTT и API KEY OpenWeatherMap в скетче в a_def_soft.h в строках:
                              // Смотри комментарий к блоку DEVICE_ID == 0

#define LED_PIN 2             // D2 пин ленты
#define PIN_BTN D4            // кнопка подключена сюда (D4 --- КНОПКА --- GND)
#define POWER_PIN D1          // D1 управляющий пин вкл/выкл матрицы через MOSFET; POWER_ON - HIGH, POWER_OFF - LOW
#define SD_CS_PIN D8          // пин выбора SD карты - ChipSelect; Также SD карта использует D5 (CLK), D6 (MISO), D7 (MOSI)
/*
#define SRX D4                // не используется, но требуется для компиляции скетча (USE_MP3==1)
#define STX D3                // не используется, но требуется для компиляции скетча (USE_MP3==1)
#define DIO D5                // D5 TM1637 display DIO pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
#define CLK D7                // D7 TM1637 display CLK pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
*/
#endif
#endif

// ============= Гирлянда на балконе V2 ====================

#if (DEVICE_ID == 4)
/*
 * Wemos D1 mini
 * Физическое подключение:
 * Матрица зигзаг, левый нижний угол, направление вправо
 * Пин ленты    - D2
 * Пин кнопки   - D4
 * В менеджере плат выбрано NodeMCU v1.0 (ESP-12E)
 */ 
#if defined(ESP8266)
#define WIDTH 50              // ширина матрицы
#define HEIGHT 20             // высота матрицы
#define DEVICE_TYPE 1         // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define MATRIX_TYPE 0         // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 0    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 0     // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
#define USE_SD 1              // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 0             // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 0          // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 1           // 1 - использовать отключение питания матрицы через MOSFET; 0 - не использовать 
#define USE_MQTT 0            // 1 - использовать управление по MQTT-каналу; 0 - не использовать (на матрице 50x20 видимо из за нехватки памяти - не работает - соединение постоянно отваливается, команды не принимает)
#define USE_WEATHER 1         // 1 - использовать получение информации о текущей погоде; 0 - не использовать 

#define A_DEF_PASS 1          // 1 - Настройки MQTT и API KEY OpenWeatherMap в отдельном файле a_def_pass.h
                              // 0 - Настройки MQTT и API KEY OpenWeatherMap в скетче в a_def_soft.h в строках:
                              // Смотри комментарий к блоку DEVICE_ID == 0

#define LED_PIN 2             // D2 пин ленты
#define PIN_BTN D4            // кнопка подключена сюда (D4 --- КНОПКА --- GND)
#define POWER_PIN D1          // D1 управляющий пин вкл/выкл матрицы через MOSFET; POWER_ON - HIGH, POWER_OFF - LOW
#define SD_CS_PIN D8          // пин выбора SD карты - ChipSelect; Также SD карта использует D5 (CLK), D6 (MISO), D7 (MOSI)
/*
#define SRX D4                // не используется, но требуется для компиляции скетча (USE_MP3==1)
#define STX D3                // не используется, но требуется для компиляции скетча (USE_MP3==1)
#define DIO D5                // D5 TM1637 display DIO pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
#define CLK D7                // D7 TM1637 display CLK pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
*/
#endif
#endif

// ================== Часы у Даши ====================

#if (DEVICE_ID == 5)
/*
 * NodeMCU v1.0 (ESP-12E)
 * Физическое подключение:
 * Матрица зигзаг, левый нижний угол, направление вправо
 * Пин ленты    - D2
 * Пин кнопки   - D6
 * MP3Player    - D3 к RX, D4 к TX плеера 
 * TM1637       - не подключен
 * В менеджере плат выбрано NodeMCU v1.0 (ESP-12E)
 */ 
#if defined(ESP8266)
#define WIDTH 16              // ширина матрицы
#define HEIGHT 16             // высота матрицы
#define SEGMENTS 1            // диодов в одном "пикселе" (для создания матрицы из кусков ленты)
#define DEVICE_TYPE 1         // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define MATRIX_TYPE 0         // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 0    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 0     // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
#define USE_SD 0              // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 1             // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 0          // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 0           // 1 - использовать отключение питания матрицы через MOSFET; 0 - не использовать 
#define USE_MQTT 0            // 1 - использовать управление по MQTT-каналу; 0 - не использовать 
#define USE_WEATHER 1         // 1 - использовать получение информации о текущей погоде; 0 - не использовать 

#define A_DEF_PASS 1          // 1 - Настройки MQTT и API KEY OpenWeatherMap в отдельном файле a_def_pass.h
                              // 0 - Настройки MQTT и API KEY OpenWeatherMap в скетче в a_def_soft.h в строках:
                              // Смотри комментарий к блоку DEVICE_ID == 0

#define LED_PIN 2             // пин ленты
#define PIN_BTN D6            // кнопка подключена сюда (PIN --- КНОПКА --- GND)
#define POWER_PIN D1          // D1 управляющий пин вкл/выкл матрицы через MOSFET
/*
#define SD_CS_PIN D8          // пин выбора SD карты - ChipSelect; Также SD карта использует D5 (CLK), D6 (MISO), D7 (MOSI)
*/
#define SRX D4                // D4 is RX of ESP8266, connect to TX of DFPlayer
#define STX D3                // D3 is TX of ESP8266, connect to RX of DFPlayer module
/*
#define DIO D5                // D5 TM1637 display DIO pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
#define CLK D7                // D7 TM1637 display CLK pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
*/
#endif
#endif

// ================== Часы в фоторамке ====================

#if (DEVICE_ID == 6)
/*
 * Wemos d1 mini
 * Физическое подключение:
 * Матрица зигзаг, левый нижний угол, направление вправо
 * Пин ленты    - D2
 * Пин кнопки   - D6 на плате
 * MP3Player    - D3 к RX, D4 к TX плеера 
 * TM1637       - не подключен
 * В менеджере плат выбрано NodeMCU v1.0 (ESP-12E)
 */ 
#if defined(ESP8266)
#define WIDTH 17              // ширина матрицы
#define HEIGHT 11             // высота матрицы
#define SEGMENTS 1            // диодов в одном "пикселе" (для создания матрицы из кусков ленты)
#define DEVICE_TYPE 1         // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define MATRIX_TYPE 0         // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 0    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 0     // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
#define USE_SD 0              // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 1             // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 0          // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 0           // 1 - использовать отключение питания матрицы через MOSFET; 0 - не использовать 
#define USE_MQTT 0            // 1 - использовать управление по MQTT-каналу; 0 - не использовать 
#define USE_WEATHER 1         // 1 - использовать получение информации о текущей погоде; 0 - не использовать 

#define A_DEF_PASS 1          // 1 - Настройки MQTT и API KEY OpenWeatherMap в отдельном файле a_def_pass.h
                              // 0 - Настройки MQTT и API KEY OpenWeatherMap в скетче в a_def_soft.h в строках:
                              // Смотри комментарий к блоку DEVICE_ID == 0

#define LED_PIN 2             // пин ленты
#define PIN_BTN D3            // кнопка подключена сюда (PIN D6 --- КНОПКА --- GND)  В3 на nodeMCU соответствует D6 на Wemos d1 mini+-
#define POWER_PIN D1          // D1 управляющий пин вкл/выкл матрицы через MOSFET
/*
#define SD_CS_PIN D8          // пин выбора SD карты - ChipSelect; Также SD карта использует D5 (CLK), D6 (MISO), D7 (MOSI)
*/
#define SRX D3                // D4 is RX of ESP8266, connect to TX of DFPlayer
#define STX D4

// D3 is TX of ESP8266, connect to RX of DFPlayer module
/*
#define DIO D5                // D5 TM1637 display DIO pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
#define CLK D7                // D7 TM1637 display CLK pin - не используется, но требуется для компиляции скетча (USE_TM1637 == 1)
*/
#endif
#endif

// =======================================================

/*
 * NodeMCU ESP32
 * Физическое подключение:
 * Матрица зигзаг, левый нижний угол, направление вапрво
 * Пин ленты    - 13
 * Пин кнопки   - 15
 * MP3Player    - 17 к RX, 16 к TX плеера 
 * TM1637       - 33 к DIO, 32 к CLK
 * SD-карта     - 5 - CS, 18 (CLK), 19 (MISO), 23 (MOSI)  - у SD-card wemos d1 shield - D8 (CS), D5 (CLK), D6 (MISO), D7 (MOSI)
 * В менеджере плат выбрано "ESP32 Dev Module"
 */ 
#if defined(ESP32)
#define WIDTH 48              // ширина матрицы
#define HEIGHT 16             // высота матрицы
#define DEVICE_TYPE 1         // Использование матрицы: 0 - свернута в трубу для лампы; 1 - плоская матрица в рамке   
#define MATRIX_TYPE 0         // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 1    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 3     // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
#define USE_SD 1              // поставьте 0, если у вас нет SD-card модуля
#define USE_MP3 0             // поставьте 0, если у вас нет звуковой карты MP3 плеера
#define USE_TM1637 0          // поставьте 1, если используется дополнительный индикатор TM1637, 0 если индикатора нет
#define USE_POWER 1           // 1 - использовать отключение питания матрицы через MOSFET; 0 - не использовать 
#define USE_MQTT 1            // 1 - использовать управление по MQTT-каналу; 0 - не использовать 
#define USE_WEATHER 1         // 1 - использовать получение информации о текущей погоде; 0 - не использовать 

#define A_DEF_PASS 1          // 1 - Настройки MQTT и API KEY OpenWeatherMap в отдельном файле a_def_pass.h
                              // 0 - Настройки MQTT и API KEY OpenWeatherMap в скетче в a_def_soft.h в строках:
                              // Смотри комментарий к блоку DEVICE_ID == 0

// Схема подключения для ESP32 - в папке Schemes, файл 'ESP32+ALL.JPG'
 
#define LED_PIN (2U)          // пин ленты
#define PIN_BTN (15U)         // кнопка подключена сюда (PIN --- КНОПКА --- GND)
#define POWER_PIN (26U)       // G26 управляющий пин вкл/выкл матрицы через MOSFET или реле
#define SD_CS_PIN (5U)        // G5 пин выбора (ChipSelect) SD карты. Также SD карта использует G18 (CLK), G19 (MISO), G23 (MOSI) // на SD-shild: D8 (CS), D5 (CLK), D6 (MISO), D7 (MOSI)

#define SRX (16U)             // G16 RX пин ESP32, подключен в TX пин (3) модуля DFPlayer
#define STX (17U)             // G17 TX пин ESP32, подключен в RX пин (2) модуля DFPlayer
#define DIO (33U)             // TM1637 display DIO pin
#define CLK (32U)             // TM1637 display CLK pin

#endif

// =======================================================

// ************** ИСПОЛЬЗУЕМЫЕ БИБЛИОТЕКИ ****************

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#endif

#if defined(ESP32)
  #include <ESPmDNS.h>
#endif

#if (USE_MQTT == 1)
#include <PubSubClient.h>        // Библиотека для работы с MQTT
#endif

#include <ArduinoOTA.h>          // Библиотека обновления "по воздуху"
#include <WiFiUdp.h>             // Библиотека поддержки WiFi
#include <TimeLib.h>             // Библиотека поддержки функций времени
#include <EEPROM.h>              // Библиотека поддержки постоянной памяти
#include <FastLED.h>             // Установите в менеджере библиотек стандартную библиотеку FastLED
#include <ArduinoJson.h>         // Библиотека для работы с JSON (погода, mqtt, состояние системы)

#if (USE_TM1637 == 1)
#include "TM1637Display.h"       // Внимание!!! Библиотека в папке проекта libraries изменена - константы букв и цифр переименованы с вида _1, _A на _1_, _A_ из-за ошибок компиляции для ESP32
#endif 

#include "timerMinim.h"          // Библиотека таймеров
#include "GyverButton.h"         // Библиотека поддержки кнопок
#include "fonts.h"               // Шрифты, определенные для бегущей строки и часов

#if (USE_MP3 == 1)
#include <SoftwareSerial.h>      // Установите в менеджере библиотек "EspSoftwareSerial" для ESP8266/ESP32 https://github.com/plerup/espsoftwareserial/
#include "DFRobotDFPlayerMini.h" // Установите в менеджере библиотек стандартную библиотеку DFRobotDFPlayerMini ("DFPlayer - A Mini MP3 Player For Arduino" )
#endif

#if (USE_SD == 1)
#include <SPI.h>                 // Библиотеки поддержки работы с SD-картой
#include <SD.h>
#endif

#include "FS.h"                  // Работа с внутренней файловой системой чипа ESP8266/ESP32
#if defined(ESP32)
  #define   LittleFS LITTLEFS
  #include <LITTLEFS.h>
#else
  #include <LittleFS.h>
#endif

// =======================================================

#if A_DEF_PASS == 1         
#include "a_def_pass.h"     // Если здесь ошибка - смотри комментарий к определению A_DEF_PASS выше в блоке с соответствующим DEVICE_ID
#endif
