/*
 * HumiditySensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "HumiditySensor.h"

HumiditySensor::HumiditySensor(ControlType type, PubSubClient* mqttClient, char* topic) : Sensor(HUMIDITY, mqttClient, topic) {
}

HumiditySensor::~HumiditySensor() {
}

