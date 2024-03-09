#include "SSD1306Wire.h"

#define DISPLAY_DURATION 3000
long timeSinceLastModeSwitch = 0;
bool currentMode = false;

class DisplayModule
{
public:
    DisplayModule(uint8_t sda_pin, uint8_t scl_pin) : sda_pin(sda_pin), scl_pin(scl_pin), display(0x3c, sda_pin, scl_pin) {}
    ~DisplayModule() {}

    void init()
    {
        this->display.init();
        this->display.flipScreenVertically();
        this->display.setFont(ArialMT_Plain_10);
    }

    void draw(String humidity, String temperature)
    {
        this->display.clear();
        this->display.setTextAlignment(TEXT_ALIGN_CENTER);
        this->display.setFont(ArialMT_Plain_16);

        if (millis() - timeSinceLastModeSwitch > DISPLAY_DURATION)
        {
            currentMode = !currentMode;
            timeSinceLastModeSwitch = millis();
        }

        if (currentMode)
        {
            humidity.concat("%");
            drawData("Humidity", humidity);
        }
        else
        {
            temperature.concat("ºC");
            drawData("Temperature", temperature);
        }

        this->display.display();
    }

private:
    uint8_t sda_pin;
    uint8_t scl_pin;
    SSD1306Wire display;

    void drawData(String label, String data)
    {
        this->display.drawString(63, 14, label);
        this->display.drawString(63, 30, data);
    }
};