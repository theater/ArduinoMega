/*
 * MotionSensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "MotionSensor.h"

MotionSensor::MotionSensor(ControlType type, PubSubClient* mqttClient, char* topic, bool directlyAttached) : Sensor(MOTION, mqttClient, topic, directlyAttached) {

}

MotionSensor::~MotionSensor() {
}
