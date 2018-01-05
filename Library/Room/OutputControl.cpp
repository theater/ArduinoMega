/*
 * OutputControl.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "OutputControl.h"
#include "Config.h"

OutputControl::OutputControl(short pinId, bool pinStatus, char * ocTopicCB, PubSubClient* mqttClient) {
	this->mqttClient = mqttClient;
	this->pinId = pinId;
	this->pinStatus = pinStatus;
	this->ocTopicCB = ocTopicCB;
	pinMode(pinId, OUTPUT); // sets pin as output
	setPin(pinStatus);
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
	}
	mqttClient->publish(ocTopicCB, getPinStatusToStr());

	logDebug("Pin has been set to status: " + String(getPinStatusToStr()));
}

OutputControl::~OutputControl() {
	// TODO Auto-generated destructor stub
}

