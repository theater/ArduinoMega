/*
 * Sensor.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <Util.h>
#include <PubSubClient.h>

class Sensor {
	private:
		char * topic;
		float value;
		ControlType type;
		bool directlyAttached;

	public:
		Sensor(ControlType type, char* topic, bool directlyAttached);
		void sensorToMqttData();
		virtual ~Sensor();
		void mqttToSensor(const char* topic, const char* value);

		//getters/setters
		ControlType getType() const;
		void setType(ControlType type);
		float getValue() const;
		void setValue(const char* topic, float value);
		char* getTopic() const;
		void setTopic(char* topic);
};

#endif /* SENSOR_H_ */
