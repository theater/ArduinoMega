/*
 * Util.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef UTIL_H_
#define UTIL_H_

enum ControlType {
	HUMIDITY,
	TEMPERATURE,
	MOTION
};

#define SensorType ControlType

enum Mode {
	ALL_OFF,
	MANUAL,
	AUTO
};

enum RoomId {
	KIDS_BEDROOM,
	MASTER_BEDROOM,
	BEDROOM_BATH,
	CORRIDOR,
	WARDROBE,
	BIG_BATHROOM
};

enum FanControlType {
	NONE,
	NORMAL,
	DUAL_SPEED
};

namespace Util {

	static const char* getSensorTypeToStr(ControlType type) {
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
