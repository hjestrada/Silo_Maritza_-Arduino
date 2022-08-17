#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "ThingSpeak.h"

const char* ssid = "NODO-YAMBORO";
const char* password = "Tecno2548$$";


#define SECRET_CH_ID 1784904
#define SECRET_WRITE_APIKEY "YWTARWU52ITQU0IE"
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

float humidity, temperature;

void setup() {
  Serial.begin(115200);
  ThingSpeak.begin(client);
  connectToWifi();
}

void connectToWifi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Conectando");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a: ");
  Serial.println(ssid);
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
}

String splitString(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void loop() {

  if (Serial.available()) {
    String msg = "";
    while (Serial.available()) {
      msg += char(Serial.read());
      delay(50);
    }
    humidity = splitString(msg, ';', 0).toFloat();
    temperature = splitString(msg, ';', 1).toFloat();
      

    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (x == 200) {
      Serial.println("Actualización de canal exitosa.");

      Serial.print("Temperatura: ");
      Serial.print(temperature);
      Serial.print("Humedad: ");
      Serial.println(humidity);
    }
    else {
      Serial.println("Problema al actualizar el canal. Código de error HTTP" + String(x));
    }

  }
}
