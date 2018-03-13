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
		char * id;
		float value;
		ControlType type;
		bool directlyAttached;

	public:
		Sensor(ControlType type, char* id, bool directlyAttached);
		void sensorToMqttData();
		virtual ~Sensor();
		void mqttToSensor(const char* id, const char* value);

		//getters/setters
		ControlType getType() const;
		void setType(ControlType type);
		float getValue() const;
		void setValue(const char* id, float value);
		char* getId() const;
		void setId(char* id);
};

#endif /* SENSOR_H_ */

