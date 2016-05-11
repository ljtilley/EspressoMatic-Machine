/*
 * Status.h
 *
 *  Created on: Feb 23, 2016
 *      Author: luke
 */
#include <Arduino.h>
#include <MAX6675.h>

#ifndef STATUS_H_
#define STATUS_H_

#define DISCONNECTED -1
#define IDLE 0
#define BREW_HEAT 1
#define BREW_READY 2
#define STEAM_HEAT 3
#define STEAM_READY 4

// MAX6675 pins & setup
#define SO A0
#define CS A1
#define CSK A2

struct StatusPacket {
	short temp, state;
};

class StatusClass {
public:
	//public stuff
	StatusClass();
	void refresh();
	short getTemp();
	void setState(short state);
	short getState();
    StatusPacket getStatusPacket();
	long getLastSendTime();
	void setLastSendTime(long time);
private:
	StatusPacket _status;
	MAX6675 _tempsensor;
	long _last_send_time;
	//private stuff;
};

extern StatusClass Status;

#endif /* STATUS_H_ */
