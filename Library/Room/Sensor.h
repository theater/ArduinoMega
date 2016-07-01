/*
 * Sensor.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Util.h"
#include <PubSubClient.h>

class Sensor {
	private:
		PubSubClient* mqttClient;
		char * topic;
		float value;
		ControlType type;
		bool directlyAttached;

		bool DEBUG;

	public:
		Sensor(ControlType type, PubSubClient* mqttClient, char* topic, bool directlyAttached, bool DEBUG=false);
		void sensorToMqttData(PubSubClient* mqttClient);
		virtual ~Sensor();
		void mqttToSensor(const char* topic, const char* value);

		//getters/setters
		void setMqttClient(PubSubClient* const mqttClient);
		PubSubClient* getMqttClient() const;
		ControlType getType() const;
		void setType(ControlType type);
		float getValue() const;
		void setValue(float value);
		char* getTopic() const;
		void setTopic(char* topic);
		bool Debug() const;
		void setDebug(bool debug);
};

#endif /* SENSOR_H_ */
