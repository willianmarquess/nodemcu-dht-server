#include "DHTesp.h"

struct DHTSensorResponse
{
    float humidity;
    float temperature;
    String status;
};

class DHTSensor
{
public:
    DHTSensor(uint8_t pin, unsigned long delay = 0) : pin(pin), delay(delay) {}
    ~DHTSensor() {}

    void init()
    {
        this->dht.setup(this->pin, DHTesp::DHT11);
    }

    unsigned long getDelay()
    {
        return this->delay > 0 ? this->delay : dht.getMinimumSamplingPeriod();
    }

    DHTSensorResponse getData()
    {
        DHTSensorResponse response;
        response.humidity = dht.getHumidity();
        response.temperature = dht.getTemperature();
        response.status = dht.getStatusString();

        return response;
    }

    void printData()
    {
        auto data = this->getData();
        Serial.printf("Status: #%s,  Humidity: #%.1f, Temperature: #%.1f\n", data.status.c_str(), data.humidity, data.temperature);
    }

private:
    DHTesp dht;
    uint8_t pin;
    unsigned long delay;
};