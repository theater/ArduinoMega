/*
 * MotionSensor.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_MOTIONSENSOR_H_
#define MODEL_MOTIONSENSOR_H_

#include "Sensor.h"

class MotionSensor: public Sensor {
	private:
		bool value;

	public:
		MotionSensor(ControlType type, PubSubClient* mqttClient, char* topic, bool directlyAttached);
		virtual ~MotionSensor();

		bool isValue() const {
			return value;
		}

		void setValue(bool value) {
			this->value = value;
		}
};

#endif /* MODEL_MOTIONSENSOR_H_ */
