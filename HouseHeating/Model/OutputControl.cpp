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

OutputControl::~OutputControl() {
	// TODO Auto-generated destructor stub
}

