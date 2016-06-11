/*
 * Sensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "../Model/Sensor.h"

Sensor::Sensor() {
}

Sensor::Sensor(SensorType type) {
	this->type = type;
}

Sensor::Sensor(SensorType type, float value) {
	this->type = type;
	this->value = value;
}

Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

