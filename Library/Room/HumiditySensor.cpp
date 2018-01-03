/*
 * HumiditySensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "HumiditySensor.h"

HumiditySensor::HumiditySensor(ControlType type, PubSubClient* mqttClient, char* topic, bool directlyAttached) : Sensor(HUMIDITY, mqttClient, topic, directlyAttached) {
}

HumiditySensor::~HumiditySensor() {
}
