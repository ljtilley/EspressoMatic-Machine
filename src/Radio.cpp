#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include "Radio.h"

#include "Status.h"
#include "Settings.h"
#include "printf.h" //needed for RF24 debug messages

//RF24 _radio = RF24(RADIO_CE, RADIO_CS);

RadioClass::RadioClass() {
    printf_begin(); //start the printf stuff
}

void RadioClass::radioInit() {
    _radio.begin();
    _radio.setRetries(15,15);
    _radio.setPayloadSize(sizeof(StatusPacket));
    _radio.openReadingPipe(1, read_pipe);
    _radio.openWritingPipe(write_pipe);
    _radio.startListening();
    _radio.printDetails();
}

bool RadioClass::sendStatus() {
    return true;
}

bool RadioClass::recvSettings() {
    if(_radio.available()) {
        Serial.println("We're receiving some stuff, hold on.");
        while(_radio.available()) {
            _radio.read(&_settings, sizeof(_settings));
        }

    }
    else {
        return false;
    }
    Serial.println("Got some settings:");
    Serial.print("Brew temp: ");
    Serial.println(_settings.brew_temp);
    Serial.print("Steam temp: ");
    Serial.println(_settings.steam_temp);
    Serial.print("Temp Offset: ");
    Serial.println(_settings.temp_offset);
    Settings.update(_settings.brew_temp, _settings.steam_temp, _settings.temp_offset);
    return true;
}

void RadioClass::radioDebug() {
    _radio.printDetails();
}

RadioClass Radio;
