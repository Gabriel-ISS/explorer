# Explorer

## Descripción

Controlador de ESP para recibir señales a traves de MQTT y controlar un robot.

## Requisitos

- Placa: ESP8266 NodeMCU o ESP32 DevKit
- IDE: Visual Studio Code
- Plugins: PlatformIO y Wokwi (para simulación)

## Configuración

1. Crea el archivo `include/config.h` con la siguiente estructura:
    ```c++
    #ifndef CONFIG_H
    #define CONFIG_H

    // Configura tus credenciales de WiFi
    const char *ssid = "nombre_de_tu_red_wifi";
    const char *password = "contraseña_de_tu_red_wifi";

    // Configura el puerto UDP
    const int udpPort = 8888;

    #endif // CONFIG_H
    ```
1. Haz la build de tu proyecto con PlatformIO
1. Sube tu proyecto o pruébalo con Wokwi