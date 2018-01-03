/*
 * TemperatureSensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(ControlType type, PubSubClient* mqttClient, char* topic, bool directlyAttached) : Sensor(TEMPERATURE, mqttClient, topic, directlyAttached) {
}

TemperatureSensor::~TemperatureSensor() {
}
