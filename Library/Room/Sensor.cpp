/*
 * Sensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <Sensor.h>
#include <MqttUtil.h>

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

void Sensor::setType(ControlType type) {
	this->type = type;
}

float Sensor::getValue() const {
	return value;
}

void Sensor::setValue(const char* id, float value) {
	String stringId = String(id);
	if(value <= -30) {
		logDebug("Sensor " + stringId + " temperature out of range");
		return;
	}

	if (strcmp(id, this->getId()) == 0) {
		this->value = value;
		char sensorCharValue[10];
		dtostrf(this->getValue(), 5, 2, sensorCharValue);
		MqttUtil::publish(this->getId(), sensorCharValue);
		logDebug("Updated sensor " + stringId + " data to value: " + String(value));
	}
}

char* Sensor::getId() const {
	return id;
}

void Sensor::setId(char* topic) {
	this->id = topic;
}

