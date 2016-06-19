/*
 * Sensor.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "../Model/Util.h"
#include "PubSubClient.h"

class Sensor {
	private:
		PubSubClient* mqttClient;
		char * topic;
		float value;
		ControlType type;
	public:
		Sensor(ControlType type, PubSubClient* mqttClient, char* topic);
		virtual ~Sensor();

		//getters/setters
		void setMqttClient(PubSubClient* const mqttClient);
		PubSubClient* getMqttClient() const;
		ControlType getType() const;
		void setType(ControlType type);
		float getValue() const;
		void setValue(float value);
		char* getTopic() const;
		void setTopic(char* topic);
};

#endif /* SENSOR_H_ */
