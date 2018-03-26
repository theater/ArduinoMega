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
int freeMemory();

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

struct DS18B20ConfigDefinition
{
    const DeviceAddress address;
    const char* mqttTopic;
};

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

#endif /* UTIL_H_ */
