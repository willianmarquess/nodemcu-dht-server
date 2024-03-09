#include <Arduino.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include "modules/sensor/DHTSensor.h"
#include "modules/server/ServerModule.h"
#include "modules/wifi/WifiModule.h"
#include "modules/display/DisplayModule.h"

JSONVar json;
ServerModule server;

const uint8_t DHT_PIN = D4;
DHTSensor dhtSensor(DHT_PIN, 2000);

const char *ssid = "";
const char *password = "";
WifiModule wifi(ssid, password);

const uint8_t SDA_PIN = D1;
const uint8_t SCL_PIN = D2;
DisplayModule display(SDA_PIN, SCL_PIN);

void setup()
{
  if (!LittleFS.begin())
  {
    Serial.println("An error has occurred while mounting LittleFS");
    return;
  }

  Serial.begin(115200);
  wifi.init();
  server.init();
  dhtSensor.init();
  display.init();
}

void loop()
{
  delay(dhtSensor.getDelay());

  dhtSensor.printData();

  auto data = dhtSensor.getData();

  String humidity = String(data.humidity);
  String temperature = String(data.temperature);

  json["humidity"] = humidity;
  json["temperature"] = temperature;

  server.notifyAll(JSON.stringify(json));

  display.draw(humidity, temperature);
}