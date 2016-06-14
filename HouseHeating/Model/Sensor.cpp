/*
 * Sensor.cpp
 *
 *  Created on: 11.06.2016 �.
 *      Author: theater
 */

#include "../Model/Sensor.h"

Sensor::Sensor() {
}

Sensor::Sensor(ControlType type) {
	this->type = type;
}

Sensor::Sensor(ControlType type, float value) {
	this->type = type;
	this->value = value;
}

Sensor::~Sensor() {
	// TODO Auto-generated destructor stub
}

