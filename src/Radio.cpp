#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include "Radio.h"

#include "Status.h"
#include "Settings.h"



RF24 RadioClass::_radio(9, 10);

RadioClass::RadioClass() {

}

bool RadioClass::sendStatus() {
    return true;
}

bool RadioClass::recvSettings() {
    return true;
}

RadioClass Radio;
