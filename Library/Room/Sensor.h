/*
 * Sensor.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <UpdateHandler.h>
#include <Util.h>
#include <MqttUtil.h>

class Sensor : public UpdateHandler {
	private:
		ControlType type;
		bool directlyAttached;

	public:
		Sensor(ControlType type, char* id, bool directlyAttached);
		virtual ~Sensor();
		bool updateValue(const char* id, const char* value);
		bool isSensorValueValid(const char* value);

		//getters/setters
		ControlType getType() const;
};

#endif /* SENSOR_H_ */

