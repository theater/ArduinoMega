/*
 * HumiditySensor.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_HUMIDITYSENSOR_H_
#define MODEL_HUMIDITYSENSOR_H_

#include "Sensor.h"

class HumiditySensor: public Sensor {
	public:
		HumiditySensor(ControlType type, PubSubClient* mqttClient, char* topic, bool directlyAttached);
		virtual ~HumiditySensor();
};

#endif /* MODEL_HUMIDITYSENSOR_H_ */
