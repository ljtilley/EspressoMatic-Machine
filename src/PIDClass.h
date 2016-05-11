#include <Arduino.h>
#include "Status.h"
#include <PID_v2.h>

#ifndef PIDCLASS_H_
#define PIDCLASS_H_

#define TEMP_SENSOR_INTERVAL 200
#define PID_UPDATE_INTERVAL 200

class PIDClass {
public:
    PIDClass();
    void updatePID();
    void setSetpoint(double new_setpoint);
    double getSetpoint();
private:
    double _setpoint, _input, _output;
    double _Kp;
    double _Ki;
    double _Kd;
    PID _pid;
    long _timeOld, _timeNew, _timer;
};

extern PIDClass HeaterPID;

#endif
