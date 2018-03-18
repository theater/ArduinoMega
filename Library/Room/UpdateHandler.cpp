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

bool UpdateHandler::updateValue(const char* id, const char* value, bool publishMqtt) {
	if (!strcmp(id, this->getId())) {
		if (isSensorValueValid(value)) {
			float sensorValue = atof(value);
			this->value = sensorValue;
			logDebug("Updated sensor " + String(id) + " data to value: " + String(value));
			if(publishMqtt) {
				MqttUtil::publish(id, value);
			}
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
