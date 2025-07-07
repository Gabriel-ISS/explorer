#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#define ledPin 2
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#define ledPin D4
#endif
#include <WiFiUdp.h>
#include "config.h"
#include "globals.h"
#include "move_wheel.h"

WiFiClient espClient;
WiFiUDP udp;

void setupLED()
{
  pinMode(ledPin, OUTPUT);
}

void setupWiFi()
{
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  bool encendido = false;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");

    if (encendido)
    {
      digitalWrite(ledPin, LOW);
      encendido = false;
    } else {
      digitalWrite(ledPin, HIGH);
      encendido = true;
    }
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void setupUDP()
{
  // Configurar el puerto UDP
  udp.begin(udpPort);
  Serial.println("Escuchando UDP en puerto " + String(udpPort));
}

void setup()
{
  Serial.begin(9200);
  Serial.println("Iniciando...");

  setupLED();
  setupWiFi();
  setupUDP();
}


void turnOnLED()
{
  // Enciende el LED integrado
  // Se usa LOW porque el led integrado opera en modo "activo bajo"
  digitalWrite(ledPin, LOW);
}
void turnOfLED()
{
  // Enciende el LED integrado
  // Se usa HIGH porque el led integrado opera en modo "activo bajo"
  digitalWrite(ledPin, HIGH);
}

String lastMessage = "";
void handleMessage(String message)
{
  Serial.print("Mensaje recibido: ");
  Serial.println(message);

  // Extraer dirección y velocidad del mensaje
  int separatorIndex = message.indexOf(',');
  if (separatorIndex == -1)
  {
    Serial.println("No se encontró el separador");
    return;
  }
  int command = message.substring(0, separatorIndex).toInt();
  int velocity = message.substring(separatorIndex, message.length()).toInt();

  // controlar el robot
  if (message != lastMessage)
  {
    switch (command)
    {
    case LED_ON:
      turnOnLED();
      break;

    case LED_OFF:
      turnOfLED();
      break;
    
    case MOVE_FORWARD:
      moveWheel(LEFT, FORWARD, velocity);
      moveWheel(RIGHT, FORWARD, velocity);
      break;

    case TURN_LEFT:
      moveWheel(LEFT, BACKWARD, velocity);
      moveWheel(RIGHT, FORWARD, velocity);
      break;

    case MOVE_BACKWARD:
      moveWheel(LEFT, BACKWARD, velocity);
      moveWheel(RIGHT, BACKWARD, velocity);
      break;

    case TURN_RIGHT:
      moveWheel(LEFT, FORWARD, velocity);
      moveWheel(RIGHT, BACKWARD, velocity);
      break;

    case STOP:
      moveWheel(LEFT, FORWARD, 0);
      moveWheel(RIGHT, FORWARD, 0);
      break;
    }
  }
  lastMessage = message;
}

bool encendido = false;
void loop()
{
  int packSize = udp.parsePacket();
  if (packSize) {
    char buffer[8];  // Creamos un array de caracteres para almacenar el paquete con capacidad de 8 caracteres
    int len = udp.read(buffer, sizeof(buffer) - 1);
    if (len > 0) buffer[len] = '\0';  // Asegura que sea texto legible agregando el carácter '\0' al final del array que representa el carácter nulo o final de cadena
    handleMessage(String(buffer));
  }

  delay(100);
}
