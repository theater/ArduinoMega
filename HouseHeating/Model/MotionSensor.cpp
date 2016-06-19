/*
 * MotionSensor.cpp
 *
 *  Created on: 11.06.2016 �.
 *      Author: theater
 */

#include "MotionSensor.h"

MotionSensor::MotionSensor(ControlType type, PubSubClient* mqttClient, char* topic) : Sensor(MOTION, mqttClient, topic) {

}

MotionSensor::~MotionSensor() {
}

