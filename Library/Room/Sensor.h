/*
 * Sensor.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <Util.h>
#include <MqttUtil.h>

class Sensor {
	private:
		char * id;
		float value;
		ControlType type;
		bool directlyAttached;

	public:
		Sensor(ControlType type, char* id, bool directlyAttached);
		virtual ~Sensor();

		//getters/setters
		ControlType getType() const;
		float getValue() const;
		char* getId() const;
		void updateValue(const char* id, const char* value);
};

#endif /* SENSOR_H_ */

