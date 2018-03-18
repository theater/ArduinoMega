/*
 * MqttUpdateHandler.h
 *
 *  Created on: Mar 18, 2018
 *      Author: theater
 */
#include <Arduino.h>
#include <Util.h>
#include <WString.h>

#ifndef LIBRARIES_ROOM_UPDATEHANDLER_H_
#define LIBRARIES_ROOM_UPDATEHANDLER_H_

class UpdateHandler {
	protected:
		char * id;
		float value;
	public:
		UpdateHandler(char* id);
		virtual ~UpdateHandler();

		bool updateValue(const char* id, const char* value);
		bool virtual isSensorValueValid(const char* value);

		float getValue() const;
		char* getId() const;
};

#endif /* LIBRARIES_ROOM_UPDATEHANDLER_H_ */
