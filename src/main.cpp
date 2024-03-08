#include <Arduino.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include "modules/sensor/DHTSensor.h"
#include "modules/server/ServerModule.h"
#include "modules/wifi/WifiModule.h"

const uint8_t DHT_PIN = D4;

JSONVar json;
ServerModule server;
DHTSensor dhtSensor(DHT_PIN, 2000);

const char *ssid = "";
const char *password = "";
WifiModule wifi(ssid, password);

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
}

void loop()
{
  delay(dhtSensor.getDelay());

  dhtSensor.printData();

  auto data = dhtSensor.getData();
  json["humidity"] = String(data.humidity);
  json["temperature"] = String(data.temperature);

  server.notifyAll(JSON.stringify(json));
}