/*
 * Sensor.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "../Model/Util.h"

class Sensor {
	private:
		float value;
		ControlType type;
	public:
		Sensor();
		Sensor(ControlType type);
		Sensor(ControlType type,float value );
		virtual ~Sensor();

		ControlType getType() const {
			return type;
		}

		void setType(ControlType type) {
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
