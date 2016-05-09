#include "Status.h"

StatusClass::StatusClass() : _tempsensor(CSK, CS, SO) {

}

void StatusClass::refresh() {
    _status.temp = (short)_tempsensor.readFarenheit(); //have to convert readFarenheit output to short
}

short StatusClass::getTemp() {
    return _status.temp;
}

short StatusClass::getState() {
    return BREW_HEAT;
    // when the radio is implemented this section should go something like this:
    // if (last update received time < 2 seconds ago) {
    //   return _status.state;
    // }
    // else {
    //   return -1;
    // }
}

StatusPacket StatusClass::getStatusPacket() {
    return _status;
}

StatusClass Status;
