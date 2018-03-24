/*
 * OutputControl.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include <OutputControl.h>
#include <Config.h>
#include <MqttUtil.h>
#include <Util.h>

OutputControl::OutputControl(ControlType type, char* id, short pinId, char* initialValue) {
	this->type = type;
	this->id = id;
	this->pinId = pinId;
	this->callbackTopic = createCallbackTopic(id);
	MqttUtil::subscribe(id);
	pinMode(pinId, OUTPUT); // sets pin as output
	updateValue(id, initialValue);
}

bool OutputControl::updateValue(char* id, char* value) {
	if (!strcmp(id, this->getId())) {

		short receivedValue = transformValue(value);

		if (getPinStatus() != receivedValue) {
			digitalWrite(this->pinId, receivedValue);
		}
		logDebug("Updated sensor " + String(id) + " data to value: " + String(value));

		MqttUtil::publish(callbackTopic, getPinStatusToStr());

		return true;
	}
	return false;
}

short OutputControl::transformValue(char* value) const {
	if (!strcmp(value, "ON")) {
		return 1;
	} else if (!strcmp(value, "OFF")) {
		return 0;
	} else {
		return atoi(value);
	}
}

char* OutputControl::getCallbackTopic() const {
	return callbackTopic;
}

char* OutputControl::getId() const {
	return id;
}

short OutputControl::getPinId() const {
	return pinId;
}

ControlType OutputControl::getType() const {
	return type;
}

const char * OutputControl::getPinStatusToStr() const {
	if (getPinStatus()) {
		return "ON";
	} else {
		return "OFF";
	}
}

bool OutputControl::getPinStatus() const {
	return digitalRead(pinId);
}

