#include <Arduino.h>

#include "Radio.h"
#include "Status.h"

void setup() {
    Serial.begin(57600);
    delay(200);
    //printf_begin();
    Serial.println("trying to start the radio");
    delay(500);
    Radio.radioInit();
}

void loop() {
    if(Radio.recvSettings() == true) {
        Serial.println("We got some settings:");
        Serial.print("Brew Temp: ");
        Serial.println(Settings.getBrewTemp());
        Serial.print("Steam Temp: ");
        Serial.println(Settings.getSteamTemp());
        Serial.print("Temp Offset: ");
        Serial.println(Settings.getTempOffset());
    }
}
