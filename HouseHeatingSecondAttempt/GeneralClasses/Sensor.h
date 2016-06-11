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
		Sensor(SensorType type);
		Sensor(SensorType type,float value );
		virtual ~Sensor();

		SensorType getType() const {
			return type;
		}

		void setType(SensorType type) {
			this->type = type;
		}

		float getValue() const {
			return value;
		}

		void setValue(float value) {
			this->value = value;
		}
};

#endif /* SENSOR_H_ */
