#include <Arduino.h>

#include "Radio.h"
#include "Status.h"
#include "Settings.h"
#include "StateMachine.h"
#include "HardwareDefines.h"

void setup() {
    pinMode(STATE_LED, OUTPUT);
    Serial.begin(57600);
    delay(500);
    Serial.println("Here are the settings that are loaded:");
    Serial.print("Brew Temp: ");
    Serial.println(Settings.getBrewTemp());
    Serial.print("Steam Temp: ");
    Serial.println(Settings.getSteamTemp());
    Serial.print("Temp Offset: ");
    Serial.println(Settings.getTempOffset());
    Serial.println("trying to start the radio");
    Radio.radioInit();
    delay(500);
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
    EXEC(BrewState);
    // udpate the debug & tuning interface
    if (millis() - Status.getLastSendTime() >= 200) {
        Serial.print("Current Status: ");
        Serial.print(Status.getTemp());
        Serial.print(", ");
        Serial.println(Status.getState());
        if(Radio.sendStatus() == true) {
            Serial.println("Sent status successfully");
        }
        else {
            Serial.println("Could not send status");
        }
        Status.setLastSendTime(millis());
    }
    // send the status every 1 second
}
