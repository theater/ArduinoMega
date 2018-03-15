/*
 * Sensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include <WString.h>
#include <Sensor.h>

Sensor::Sensor(ControlType type, char* topic, bool directlyAttached) {
	this->type = type;
	this->id = topic;
	this->directlyAttached = directlyAttached;
}


Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

// getters and setters
ControlType Sensor::getType() const {
	return type;
}

float Sensor::getValue() const {
	return value;
}

void Sensor::updateValue(const char* id, const char* value) {
	String stringId = String(id);
	float sensorValue = atof(value);
	if (sensorValue <= -30) {
		logDebug("Sensor " + stringId + " temperature out of range");
		return;
	}

	if (strcmp(id, this->getId()) == 0) {
		this->value = sensorValue;
		logDebug("Updated sensor " + stringId + " data to value: " + String(value));

		if (directlyAttached) {
			MqttUtil::publish(this->getId(), value);
		}
	}
}

char* Sensor::getId() const {
	return id;
}
