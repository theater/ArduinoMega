/*
 * OutputControl.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "OutputControl.h"

OutputControl::OutputControl(short pinId, bool pinStatus) {
	this->pinId = pinId;
	this->pinStatus = pinStatus;
	pinMode(pinId, OUTPUT);
}

//TODO: check if 1 is on and 0 is off, otherwise return !pinstatus
bool OutputControl::outputIsOn() {
	return pinStatus;
}

const char * OutputControl::getPinStatusToStr() {
	if (outputIsOn()) {
		return "ON";
	} else {
		return "OFF";
	}
}

short OutputControl::getPinId() const {
	return pinId;
}

void OutputControl::setPinId(short pinId) {
	this->pinId = pinId;
}

bool OutputControl::getPinStatus() const {
	return pinStatus;
}

void OutputControl::setPin(bool pinStatus) {
	this->pinStatus = pinStatus;
	if (digitalRead(pinId) != pinStatus) {
		digitalWrite(pinId, pinStatus);
		//TODO take out serial prints
		Serial.print("Setting pin ");Serial.print(pinId);Serial.print(" to ");Serial.println(pinStatus);
	}
}

OutputControl::~OutputControl() {
	// TODO Auto-generated destructor stub
}

