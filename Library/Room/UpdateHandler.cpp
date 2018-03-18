/*
 * MqttUpdateHandler.cpp
 *
 *  Created on: Mar 18, 2018
 *      Author: theater
 */

#include <UpdateHandler.h>
#include <MqttUtil.h>


UpdateHandler::UpdateHandler(char* id) {
	this->id = id;

}

UpdateHandler::~UpdateHandler() {
	// TODO Auto-generated destructor stub
}

bool UpdateHandler::updateValue(const char* id, const char* value) {
	String stringId = String(id);
	float sensorValue = atof(value);
	if(isSensorValueValid(value)) {
		if (strcmp(id, this->getId()) == 0) {
			this->value = sensorValue;
			logDebug("Updated sensor " + stringId + " data to value: " + String(value));
			return true;
		}
	}
	return false;
}

bool UpdateHandler::isSensorValueValid(const char* value) {
	// this is to ignore warning that parameter is not used :)
	(void)value;

	return true;
}

float UpdateHandler::getValue() const {
	return value;
}

char* UpdateHandler::getId() const {
	return id;
}
