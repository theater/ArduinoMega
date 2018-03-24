/*
 * OutputControl.h
 *
 *  Created on: 11.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_OUTPUTCONTROL_H_
#define MODEL_OUTPUTCONTROL_H_

#include <stdbool.h>
#include "PubSubClient.h"
#include "Config.h"
#include <Util.h>

class OutputControl {
	private:
		ControlType type;
		char * id;
		char * callbackTopic;
		short pinId;
	public:
		OutputControl();
		OutputControl(ControlType type, char* id, short pinId, char* value);

		bool updateValue(char* id, char* value);
		short transformValue(char* value) const;
		char* getCallbackTopic() const;
		char* getId() const;
		short getPinId() const;
		ControlType getType() const;
		bool getPinStatus() const;
		const char * getPinStatusToStr() const;
};

#endif /* MODEL_OUTPUTCONTROL_H_ */
