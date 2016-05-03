#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#include "Status.h"
#include "Settings.h"

#define RADIO_CE 9
#define RADIO_CS 10

const uint64_t read_pipe = 0xF0F0F0F0E1LL;
const uint64_t write_pipe = 0xF0F0F0F0D2LL;

class RadioClass {
public:
    RadioClass();
    bool sendStatus();
    bool recvSettings();
private:
    static RF24 _radio;
    settings_t _settings;
};

extern RadioClass Radio;
