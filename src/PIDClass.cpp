#include "PIDClass.h"
#include <Arduino.h>
#include "PID_v2.h"

#include "Settings.h"
#include "Status.h"
#include "PWM.h"


double _Kp = 45;
double _Ki = 0.3;
double _Kd = 500;

PIDClass::PIDClass() : _pid(&_input, &_output, &_setpoint, _Kp, _Ki, _Kd, DIRECT) {
        //set up relevant info for pid
        _setpoint = double(Settings.getBrewTemp()); //TODO: this class shouldn't be concerned with brew/steam temp, only the set point. Move this to the State Machine handler
        _pid.SetOutputLimits(0,1000);
        _pid.SetMode(AUTOMATIC);
        delay(500); // wait for MAX chip to stabilize
        _input = double(Status.getTemp()); //initial temp reading
}

void PIDClass::updatePID() {
    _timeOld = _timeNew;
    _timeNew = millis(); // Don't poll the temperature sensor too quickly
    _timer += abs(_timeOld - _timeNew);

    // Run low-frequency updates
    if(_timer>300){
    _input = double(Status.getTemp()); // update LCD to reflect temp changes
    _timer=0;
    }

    _pid.Compute();
    PWM.setHeatPowerPercentage(_output);
    PWM.updateHeater();
}

void PIDClass::setSetpoint(double new_setpoint) {
    _setpoint = new_setpoint;
}

double PIDClass::getSetpoint() {
    return _setpoint;
}

PIDClass PID;
