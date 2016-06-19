/*
 * TemperatureSensor.cpp
 *
 *  Created on: 11.06.2016 �.
 *      Author: theater
 */

#include "../Model/TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(ControlType type, PubSubClient* mqttClient, char* topic) : Sensor(TEMPERATURE, mqttClient, topic) {
}

TemperatureSensor::~TemperatureSensor() {
}

