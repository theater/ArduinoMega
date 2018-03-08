/*
 * TemperatureSensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(ControlType type, char* topic, bool directlyAttached) : Sensor(TEMPERATURE, topic, directlyAttached) {
}

TemperatureSensor::~TemperatureSensor() {
}
