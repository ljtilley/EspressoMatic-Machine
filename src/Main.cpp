#include <Arduino.h>

#include "Radio.h"
#include "Status.h"
#include "printf.h"

void setup() {
    Serial.begin(9600);
    printf_begin();
    Serial.println("trying to start the radio");
    delay(500);
    Radio.radioInit();
    delay(100);
    Serial.println("Radio started, trying to print debug info");
    Radio.radioDebug();
}

void loop() {
    // if(Radio.recvSettings() == true) {
    //     Serial.println("We got some settings:");
    //     Serial.print("Brew Temp: ");
    //     Serial.println(Settings.getBrewTemp());
    //     Serial.print("Steam Temp: ");
    //     Serial.println(Settings.getSteamTemp());
    //     Serial.print("Temp Offset: ");
    //     Serial.println(Settings.getTempOffset());
    // }

}
