/*
 * Mode.cpp
 *
 *  Created on: Mar 15, 2018
 *      Author: theater
 */

#include <Mode.h>
#include <MqttUtil.h>

Mode::Mode(ModeType mode) : Mode(mode, NULL) {
}

Mode::Mode(ModeType mode, char * id ) {
	this->id = id;
	this->mode = mode;
	this->callbackTopic = createCallbackTopic(id);
	MqttUtil::subscribe(id);
}

void Mode::updateValue(const char* id, const char* value) {
	if (!strcmp(id, this->id)) {
		if (!strcmp(value, "ALL_OFF")) {
			setMode(ALL_OFF);
		} else if (!strcmp(value, "MANUAL")) {
			setMode(MANUAL);
		} else {
			setMode(AUTO);
		}
		logDebug("Updated MODE " + String(id) + " to value: " + String(value));
	}
}

Mode::~Mode() {
}

char* Mode::getId() {
	return id;
}

ModeType Mode::getMode() {
	return mode;
}

void Mode::setMode(ModeType mode) {
	this->mode = mode;
}
