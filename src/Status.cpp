#include "Status.h"

StatusClass::StatusClass() : _tempsensor(CSK, CS, SO) {

}

void StatusClass::refresh() {
    if(millis() - _last_send_time >= 200) {
        _status.temp = (short)_tempsensor.readFarenheit(); // have to convert readFarenheit output to short to fit in the status packet
    }
}

short StatusClass::getTemp() {
    refresh();
    return _status.temp;
}

void StatusClass::setState(short state) {
    _status.state = state;
}

short StatusClass::getState() {
    refresh();
    return _status.state;
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
