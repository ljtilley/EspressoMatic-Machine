#include <Arduino.h>
#include "DebugInterface.h"

int incomingByte = 0;
float delta = 1.0;
bool autoupdate;
bool printmode = 0;

unsigned long lastUpdateTime = 0;

// Serial interface init
void setupSerialInterface()  {
  Serial.begin(115200);
  Serial.print("\nWelcome to ");
  Serial.println(BANNER);
  Serial.println("Send back one or more characters to setup the controller.");
  Serial.println("Enter '?' for help.  Here's to a great cup!");
  //printStatus();
}

void printHelp() {
  Serial.println("Send these characters for control:");
  Serial.println("<space> : print status now");
  Serial.println("u : toggle periodic status update");
  Serial.println("g : toggle update style between human and graphing mode");
  Serial.println("R : reset/initialize PID gain values");
  Serial.println("b : print PID debug values");
  Serial.println("? : print help");
  Serial.println("+/- : adjust delta by a factor of ten");
  Serial.println("P/p : up/down adjust p gain by delta");
  Serial.println("I/i : up/down adjust i gain by delta");
  Serial.println("D/d : up/down adjust d gain by delta");
  Serial.println("T/t : up/down adjust brew set temp by delta");
  Serial.println("a : engage autotune");
  //Serial.println("S/s : up/down adjust steam set temp by delta\n");

}

// Execute serial commands from buffer
void updateSerialInterface() {
  while(Serial.available()){
    incomingByte = Serial.read();
    if (incomingByte == 'R') {
      boiler_pid.SetTunings(Kp, Ki, Kd);
      setpoint = 200.0; // here too
    }
    if (incomingByte == 'P') {
      boiler_pid.SetTunings(boiler_pid.GetKp() + delta, boiler_pid.GetKi(), boiler_pid.GetKd());
    }
    if (incomingByte == 'p') {
      boiler_pid.SetTunings(boiler_pid.GetKp() - delta, boiler_pid.GetKi(), boiler_pid.GetKd());
    }
    if (incomingByte == 'I') {
      boiler_pid.SetTunings(boiler_pid.GetKp(), boiler_pid.GetKi() + delta, boiler_pid.GetKd());
    }
    if (incomingByte == 'i') {
      boiler_pid.SetTunings(boiler_pid.GetKp(), boiler_pid.GetKi() - delta, boiler_pid.GetKd());
    }
    if (incomingByte == 'D') {
      boiler_pid.SetTunings(boiler_pid.GetKp(), boiler_pid.GetKi(), boiler_pid.GetKd() + delta);
    }
    if (incomingByte == 'd' ){
      boiler_pid.SetTunings(boiler_pid.GetKp(), boiler_pid.GetKi(), boiler_pid.GetKd() - delta);
    }
    if (incomingByte == 'T') {
      setpoint = setpoint + delta;
      Serial.print("Brew temp: ");
      Serial.print(setpoint);
      //printFloat(readFloat(ESPRESSO_TEMP_ADDRESS),PRINT_PLACES_AFTER_DECIMAL);
      Serial.println("");
    }
    if (incomingByte == 't') {
      if (setpoint - delta >= 0) {
        setpoint = setpoint - delta;
      }
      Serial.print("Brew temp: ");
      Serial.print(setpoint);
      //printFloat(readFloat(ESPRESSO_TEMP_ADDRESS),PRINT_PLACES_AFTER_DECIMAL);
      Serial.println("");
    }
    /*if (incomingByte == 'S') {
      setSteamTargetTemp(getSteamTargetTemp() + delta);
      Serial.print("Steam temp: ");
      printFloat(readFloat(STEAM_TEMP_ADDRESS),PRINT_PLACES_AFTER_DECIMAL);
      Serial.println("");
    }
    if (incomingByte == 's') {
      setSteamTargetTemp(getSteamTargetTemp() - delta);
      Serial.print("Steam temp: ");
      printFloat(readFloat(STEAM_TEMP_ADDRESS),PRINT_PLACES_AFTER_DECIMAL);
      Serial.println("");
    }*/
    if (incomingByte == '+') {
      delta *= 10.0;
      if (delta > MAX_DELTA)
        delta = MAX_DELTA;
    }
    if (incomingByte == '-') {
      delta /= 10.0;
      if (delta < MIN_DELTA)
        delta = MIN_DELTA;
    }
    if (incomingByte == 'u') {
      // toggle updating
      autoupdate = not autoupdate;
    }
    if (incomingByte == 'g') {
      // toggle updating
      printmode = not printmode;
    }
    if (incomingByte == ' ') {
      // toggle updating
      printStatus();
    }
    if (incomingByte == '?') {
      printHelp();
    }
    if (incomingByte == 'b') {
      Serial.print("P: ");
      Serial.println(boiler_pid.GetKp());
      Serial.print("I: ");
      Serial.println(boiler_pid.GetKi());
      Serial.print("D: ");
      Serial.println(boiler_pid.GetKd());
      Serial.print("Output: ");
      Serial.println(output);
      Serial.println();
    }
  }
  if (millis() < lastUpdateTime) {
    lastUpdateTime = 0;
  }
  if ((millis() - lastUpdateTime) > AUTO_PRINT_INTERVAL) {
    // this is triggers every slightly more than a second from the delay between these two millis() calls
    lastUpdateTime += AUTO_PRINT_INTERVAL;
    if (autoupdate) {
      if (printmode) {
        printStatusForGraph();
      }
      else {
        printStatus();
      }
    }
  }
}

// Print the current status to the serial console
void printStatus() {
  // A means for getting feedback on the current system status and controllable parameters
  Serial.print("Brew temp:");
  Serial.println(setpoint);
  //printFloat(readFloat(ESPRESSO_TEMP_ADDRESS),PRINT_PLACES_AFTER_DECIMAL);
  //Serial.print(" Steam temp:");
 // printFloat(readFloat(STEAM_TEMP_ADDRESS),PRINT_PLACES_AFTER_DECIMAL);

  //Serial.print(" Current temp goal:");
 // printFloat(targetTemp,PRINT_PLACES_AFTER_DECIMAL);
  Serial.print("Current temp:");
  Serial.println(input);

  Serial.print("P: ");
  Serial.print(boiler_pid.GetKp());
  Serial.print(", I: ");
  Serial.print(boiler_pid.GetKi());
  Serial.print(", D: ");
  Serial.print(boiler_pid.GetKd());
  Serial.print(", Output: ");
  Serial.print(output);
  Serial.print(", Delta: ");
  Serial.println(delta);
  Serial.println();
  Serial.println(" \n");
}

// Print computer-parseable status
void printStatusForGraph() {
  Serial.print(setpoint);
  //printFloat(targetTemp,PRINT_PLACES_AFTER_DECIMAL);
  Serial.print(", ");
  Serial.print(input);
  //printFloat(getLastTemp(),PRINT_PLACES_AFTER_DECIMAL);
  Serial.print(", ");
  Serial.print(boiler_pid.GetKp());
  //printFloat(getP(),PRINT_PLACES_AFTER_DECIMAL);
  Serial.print(", ");
  Serial.print(boiler_pid.GetKi());
  //printFloat(getI(),PRINT_PLACES_AFTER_DECIMAL);
  Serial.print(", ");
  Serial.print(boiler_pid.GetKd());
  //printFloat(getD(),PRINT_PLACES_AFTER_DECIMAL);
  Serial.print(", ");
  Serial.print(getHeatCycles());
  Serial.println();
}
