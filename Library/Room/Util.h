/*
 * Util.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */
// test merge1
#ifndef UTIL_H_
#define UTIL_H_

#include <DallasTemperature.h>
#include <WString.h>

void log(String severity, String data);
void logInfo(String data);
void logDebug(String data);
void logError(String data);
void printOneWireAddresses(DallasTemperature* owSensors);
char* createCallbackTopic(char* topic);

enum ControlType {
	HUMIDITY,
	TEMPERATURE,
	MOTION
};

#define SensorType ControlType

enum ModeType {
	ALL_OFF,
	MANUAL,
	AUTO
};

enum RoomId {
	LIVING_ROOM,
	TECH_ROOM,
	STORAGE_ROOM,
	FLOOR1_BATH,
	ROOM_COUNT = FLOOR1_BATH
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

struct DS18B20ConfigDefinition
{
    const DeviceAddress address;
    const char* mqttTopic;
};

#endif /* UTIL_H_ */
