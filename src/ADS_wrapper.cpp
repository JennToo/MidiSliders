#include <Adafruit_ADS1X15.h>
#include <Wire.h>

Adafruit_ADS1015 ads;
MbedI2C myi2c(p16,p17);

void ads_begin() {
    myi2c.begin();
    if (ads.begin(0x48, &myi2c))
    {
        Serial.println("Device found. I2C connections are good.");
    }
    else
    {
        while (1) {
            Serial.println("Device not found. Check wiring.");
        }
    }
}

uint16_t ads_read(uint16_t channel) {
    uint32_t raw_value = ads.readADC_SingleEnded(channel) << 2;
    if(raw_value > 4095) {
        raw_value = 4095;
    }
    return raw_value;
}
