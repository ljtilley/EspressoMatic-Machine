#include <Arduino.h>

#ifdef DEBUG_INTERFACE_H_
#define DEBUG_INTERFACE_H_

#define AUTO_PRINT_INTERVAL 200  // milliseconds
#define MAX_DELTA  100
#define MIN_DELTA  0.01
#define PRINT_PLACES_AFTER_DECIMAL 2
#define BANNER "EspressoMatic Machine 1.0"

extern int incomingByte;
extern float delta;
extern bool autoupdate;
extern bool printmode;

extern unsigned long lastUpdateTime;

// Serial interface init
extern void setupSerialInterface();

extern void printHelp();

// Execute serial commands from buffer
extern void updateSerialInterface();

// Print computer-parseable status
extern void printStatusForGraph();

// Print the current status to the serial console
extern void printStatus();


#endif
