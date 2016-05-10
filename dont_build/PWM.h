#include <Arduino.h>

#ifndef PWM_H_
#define PWM_H_

#define HEAT_RELAY_PIN 4

class PWMClass {
public:
    PWMClass();
    void setupHeater();
    void updateHeater();
    void setHeatPowerPercentage(float power);
    float getHeatCycles();
    void _turnHeatElementOnOff(boolean on);
private:
    float heatcycles; // the number of millis out of 1000 for the current heat amount (percent * 10)
    bool heaterState;
    unsigned long heatCurrentTime, heatLastTime;
};

extern PWMClass PWM;

#endif
