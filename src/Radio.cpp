#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include "Radio.h"

#include "Status.h"
#include "Settings.h"



RF24 RadioClass::_radio(9, 10);

RadioClass::RadioClass() {
    _radio.begin();
    _radio.setRetries(15,15);
    _radio.setPayloadSize(sizeof(StatusPacket));
    _radio.openReadingPipe(1, read_pipe);
    _radio.openWritingPipe(write_pipe);
    _radio.startListening();
}

bool RadioClass::sendStatus() {
    return true;
}

bool RadioClass::recvSettings() {
    if(_radio.available()) {
        _radio.read(&_settings, sizeof(_settings));
    }
    else {
        return false;
    }
    Settings.update(_settings.brew_temp, _settings.steam_temp, _settings.temp_offset);
    return true;
}

RadioClass Radio;
