#include <Arduino.h>

#ifndef PWM_H_
#define PWM_H_

#define HEAT_RELAY_PIN 4

extern float heatcycles; // the number of millis out of 1000 for the current heat amount (percent * 10)

extern bool heaterState;

extern unsigned long heatCurrentTime, heatLastTime;

void setupHeater();
void updateHeater();
void setHeatPowerPercentage(float power);
float getHeatCycles();
void _turnHeatElementOnOff(boolean on);

#endif
