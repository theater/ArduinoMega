/*
 * MotionSensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "MotionSensor.h"

MotionSensor::MotionSensor() : Sensor(MOTION){

}

MotionSensor::MotionSensor(bool value) {
	Sensor(MOTION);
	this->value = value;
}

MotionSensor::~MotionSensor() {
}

