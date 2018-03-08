/*
 * MotionSensor.cpp
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#include "MotionSensor.h"

MotionSensor::MotionSensor(ControlType type, char* topic, bool directlyAttached) : Sensor(MOTION, topic, directlyAttached) {

}

MotionSensor::~MotionSensor() {
}
