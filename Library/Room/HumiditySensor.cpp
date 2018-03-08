/*
 * HumiditySensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "HumiditySensor.h"

HumiditySensor::HumiditySensor(ControlType type, char* topic, bool directlyAttached) : Sensor(HUMIDITY, topic, directlyAttached) {
}

HumiditySensor::~HumiditySensor() {
}
