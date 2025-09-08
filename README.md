# Explorer

## Descripción

Controlador de ESP8266 NodeMCU V3 para recibir señales a traves de UDP y controlar un robot.

## Requisitos

- Placa: ESP8266 NodeMCU V3
- IDE: Visual Studio Code
- Plugins: PlatformIO

## Configuración

1. Crea el archivo `include/config.h` con la siguiente estructura:
    ```c++
    #ifndef CONFIG_H
    #define CONFIG_H

    // Configura tus credenciales de WiFi
    const char *ssid = "nombre_de_tu_red_wifi";
    const char *password = "contraseña_de_tu_red_wifi";

    // Configura el puerto UDP
    const int udpPort = 8000;

    #endif // CONFIG_H 
    ```
1. Haz la build de tu proyecto y subelo con PlatformIO. Recuerda configurar correctamente el puerto de la placa en `platformio.ini`. Puedes visualizar el IP y puerto de conexión en el monitor serial y hacer pruebas a traves de `Packet Sender`.

## Roadmap
- [ ] Modificar para recibir direccion y velocidad para cada rueda
- [ ] Implementar funcion para mover rueda
