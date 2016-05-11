#include <SM.h>
#include <Arduino.h>
#include "StateMachine.h"
#include "PIDClass.h"
#include "Settings.h"
#include "HardwareDefines.h"
#include "Status.h"

SM BrewState(STATE_BREW_HEAT_ENTER, STATE_BREW_HEAT);

static void checkSteamButton() {
    if(digitalRead(STEAM_SW) == 0) {
        if(Status.getState() != BREW_HEAT || Status.getState() != BREW_READY) {
            BrewState.Set(STATE_BREW_HEAT_ENTER, STATE_BREW_HEAT);
        }
    }
    else {
        if(Status.getState() != STEAM_HEAT || Status.getState() != STEAM_READY) {
            BrewState.Set(STATE_BREW_HEAT_ENTER, STATE_BREW_HEAT);
        }
    }
}

State STATE_BREW_HEAT_ENTER() {
    Status.setState(BREW_HEAT);
    digitalWrite(STATE_LED, 0);
    //HeaterPID.setSetpoint(double(Settings.getBrewTemp()));
    Serial.println("Entering BREW HEAT");
}

State STATE_BREW_HEAT() {
    //HeaterPID.updatePID();
    if(Settings.getBrewTemp() - Status.getTemp() <= 3 && Settings.getBrewTemp() - Status.getTemp() >= -3) {
        BrewState.Set(STATE_BREW_READY_ENTER, STATE_BREW_READY);
    }
    // checkSteamButton();
}

State STATE_BREW_READY_ENTER() {
    Serial.println("Entering BREW READY");
    Status.setState(BREW_READY);
    digitalWrite(STATE_LED, 1);
}

State STATE_BREW_READY() {
    // HeaterPID.updatePID();
    if(!(Settings.getBrewTemp() - Status.getTemp() <= 3 && Settings.getBrewTemp() - Status.getTemp() >= -3)) {
        BrewState.Set(STATE_BREW_HEAT_ENTER, STATE_BREW_HEAT);
    }
    // // checkSteamButton();
}

State STATE_STEAM_HEAT_ENTER() {
    Status.setState(STEAM_HEAT);
    digitalWrite(STATE_LED, 0);
    HeaterPID.setSetpoint(double(Settings.getSteamTemp()));
}

State STATE_STEAM_HEAT() {
    //HeaterPID.updatePID();
    if(Settings.getSteamTemp() - Status.getTemp() <= 3 && Settings.getSteamTemp() - Status.getTemp() >= -3) {
        BrewState.Set(STATE_STEAM_READY_ENTER, STATE_STEAM_READY);
    }
    // checkSteamButton();
}

State STATE_STEAM_READY_ENTER() {
    Status.setState(STEAM_READY);
    digitalWrite(STATE_LED, 1);
}

State STATE_STEAM_READY() {
    //HeaterPID.updatePID();
    if(Settings.getSteamTemp() - Status.getTemp() >= 3 && Settings.getSteamTemp() - Status.getTemp() <= -3) {
        BrewState.Set(STATE_STEAM_HEAT_ENTER, STATE_STEAM_HEAT);
    }
    // checkSteamButton();
}
