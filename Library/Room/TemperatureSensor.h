/*
 * TemperatureSensor.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_TEMPERATURESENSOR_H_
#define MODEL_TEMPERATURESENSOR_H_

#include "Sensor.h"
#include "PubSubClient.h"
class TemperatureSensor : public Sensor {
	public:
		TemperatureSensor(ControlType type, PubSubClient* mqttClient, char* topic, bool directlyAttached);
		virtual ~TemperatureSensor();
};

#endif /* MODEL_TEMPERATURESENSOR_H_ */
