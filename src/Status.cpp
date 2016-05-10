#include "Status.h"

StatusClass::StatusClass() : _tempsensor(CSK, CS, SO) {

}

void StatusClass::refresh() {
    _status.temp = (short)_tempsensor.readFarenheit(); //have to convert readFarenheit output to short
    _status.state = BREW_HEAT;
}

short StatusClass::getTemp() {
    refresh();
    return _status.temp;
}

short StatusClass::getState() {
    refresh();
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
    refresh();
    return _status;
}

long StatusClass::getLastSendTime() {
    return _last_send_time;
}

void StatusClass::setLastSendTime(long time) {
    _last_send_time = time;
}

StatusClass Status;
