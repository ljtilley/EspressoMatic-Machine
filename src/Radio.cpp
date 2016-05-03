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
    }
    else {
        return false;
    }
    return true;
}

RadioClass Radio;
