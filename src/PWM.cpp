#include <Arduino.h>
#include "PWM.h"

PWMClass::PWMClass() {
    heaterState = 0;
}

void PWMClass::setupHeater() {
  pinMode(HEAT_RELAY_PIN , OUTPUT);
}


void PWMClass::updateHeater() {
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

void PWMClass::setHeatPowerPercentage(float power) {
  if (power <= 0.0) {
    power = 0.0;
  }
  if (power >= 1000.0) {
    power = 1000.0;
  }
  heatcycles = power;
}

float PWMClass::getHeatCycles() {
  return heatcycles;
}

void PWMClass::_turnHeatElementOnOff(boolean on) {
  digitalWrite(HEAT_RELAY_PIN, on);	//turn pin high
  heaterState = on;
}

PWMClass PWM;
// End Heater Control
