/*
 * Sensor.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "util.h"

class Sensor {
private:
	float value;
	SensorType type;
public:
	Sensor();
	virtual ~Sensor();
};

#endif /* SENSOR_H_ */
