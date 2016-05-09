#include <Arduino.h>
#include "PWM.h"


bool heaterState = 0;

unsigned long heatCurrentTime, heatLastTime;

void setupHeater() {
  pinMode(HEAT_RELAY_PIN , OUTPUT);
}


void updateHeater() {
  heatCurrentTime = millis();
  if(heatCurrentTime - heatLastTime >= 1000 or heatLastTime > heatCurrentTime) { //second statement prevents overflow errors
    // begin cycle
    _turnHeatElementOnOff(1);  //
    heatLastTime = heatCurrentTime;
  }
  if (heatCurrentTime - heatLastTime >= heatcycles) {
    _turnHeatElementOnOff(0);
  }
}

void setHeatPowerPercentage(float power) {
  if (power <= 0.0) {
    power = 0.0;
  }
  if (power >= 1000.0) {
    power = 1000.0;
  }
  heatcycles = power;
}
//
float getHeatCycles() {
  return heatcycles;
}

void _turnHeatElementOnOff(boolean on) {
  digitalWrite(HEAT_RELAY_PIN, on);	//turn pin high
  heaterState = on;
}

// End Heater Control
