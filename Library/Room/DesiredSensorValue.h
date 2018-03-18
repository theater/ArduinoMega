/*
 * DesiredValue.h
 *
 *  Created on: Mar 18, 2018
 *      Author: theater
 */

#ifndef LIBRARIES_ROOM_DESIREDSENSORVALUE_H_
#define LIBRARIES_ROOM_DESIREDSENSORVALUE_H_

#include <UpdateHandler.h>
#include <Util.h>

class DesiredSensorValue : public UpdateHandler {
	private:
		ControlType type;
		char * callbackTopic;
	public:
		DesiredSensorValue(ControlType type, char* topic, float initialValue);
		virtual ~DesiredSensorValue();
};

#endif /* LIBRARIES_ROOM_DESIREDSENSORVALUE_H_ */
