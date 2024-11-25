#include <Control_Surface.h>

// The Control Surface library defines PinList, which breaks the use of Wire.h
// in the ADS library.
#include "ADS_wrapper.hpp"

class AdsIo : public StaticSizeExtendedIOElement<4> {
    void pinModeBuffered(pin_int_t pin, PinMode_t mode) override {}
    void digitalWriteBuffered (pin_int_t pin, PinStatus_t state) override {}
    PinStatus_t digitalReadBuffered(pin_int_t pin) override { return LOW; }
    void analogWriteBuffered(pin_int_t, analog_t) override {}
    analog_t analogReadBuffered(pin_int_t pin) override {
        return ads_read(pin);
    }
    void begin() override {}
    void updateBufferedOutputs() override {}
    void updateBufferedInputs() override {}
};

AdsIo adsIo;
USBMIDI_Interface midi;
CCPotentiometer pot[8] { 
    {A0, MIDI_CC::Sound_Controller_1},
    {A1, MIDI_CC::Sound_Controller_2},
    {A2, MIDI_CC::Sound_Controller_3},
    {A3, MIDI_CC::Sound_Controller_4},
    {adsIo.pin(0), MIDI_CC::General_Purpose_Controller_1},
    {adsIo.pin(1), MIDI_CC::General_Purpose_Controller_2},
    {adsIo.pin(2), MIDI_CC::General_Purpose_Controller_3},
    {adsIo.pin(3), MIDI_CC::General_Purpose_Controller_4}
};

void setup() {
    Serial.begin(9600);
    ads_begin();
    Control_Surface.begin();
}
void loop() {
    Serial.print(ads_read(0));
    Serial.print(" ");
    Serial.print(ads_read(1));
    Serial.print(" ");
    Serial.print(ads_read(2));
    Serial.print(" ");
    Serial.println(ads_read(3));
    Control_Surface.loop();
}
