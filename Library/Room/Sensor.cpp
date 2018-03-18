/*
 * Sensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include <stdlib.h>
#include <Sensor.h>
#include <WString.h>

Sensor::Sensor(ControlType type, char* topic, bool directlyAttached) : UpdateHandler(topic){
	this->type = type;
	this->directlyAttached = directlyAttached;
}


Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

// getters and setters
ControlType Sensor::getType() const {
	return type;
}

bool Sensor::isSensorValueValid(const char* value) {
	float sensorValue = atof(value);
	if (sensorValue <= -30) {
		logDebug("Sensor " + String(getId()) + " temperature out of range");
		return false;
	}
}

bool Sensor::updateValue(const char* id, const char* value) {
	UpdateHandler::updateValue(id, value);
	if (directlyAttached) {
		MqttUtil::publish(this->getId(), value);
	}
}
