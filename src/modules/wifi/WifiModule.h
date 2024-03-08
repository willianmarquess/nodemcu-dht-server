#include <ESP8266WiFi.h>

class WifiModule
{
public:
  WifiModule(String ssid, String password) : ssid(ssid), password(password){};
  ~WifiModule(){};
  void init()
  {
    Serial.println('\n');

    WiFi.begin(this->ssid, this->password);

    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ...");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(1000);
      Serial.print(++i);
      Serial.print(' ');
    }

    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
  }

private:
  String ssid;
  String password;
};