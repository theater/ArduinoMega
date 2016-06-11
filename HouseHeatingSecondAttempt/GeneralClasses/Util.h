/*
 * Util.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef UTIL_H_
#define UTIL_H_

enum SensorType {
	HUMIDITY, TEMPERATURE, MOTION
};

namespace Util {

	static const char* getSensorTypeToStr(SensorType type) {
		switch (type) {
		case HUMIDITY:
			return "Humidity";
		case TEMPERATURE:
			return "Temperature";
		case MOTION:
			return "Motion";
		default:
			return "";
		}
	}
}

#endif /* UTIL_H_ */
