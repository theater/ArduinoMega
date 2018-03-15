/*
 * Mode.cpp
 *
 *  Created on: Mar 15, 2018
 *      Author: theater
 */

#include <Mode.h>

Mode::Mode(ModeType mode) : Mode(mode, NULL) {
}

Mode::Mode(ModeType mode, char * id ) {
	this->id = id;
	this->mode = mode;

	// Construct callback topic by creating same string + cb at the end:
	int size = strlen(id) + 4;
	this->callbackTopic = new char[size];
    strcpy(this->callbackTopic, id);
	logDebug("Set topic to :" + String(id));
	strcat(this->callbackTopic, "cb");
	logDebug("Callback topic is :" + String(callbackTopic));
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
