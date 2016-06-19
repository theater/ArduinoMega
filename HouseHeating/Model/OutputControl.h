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
#include "../Config/Config.h"

class OutputControl {
	private:
		short pinId;
		bool pinStatus;
		char * ocTopicCB;
		PubSubClient* mqttClient;
		bool DEBUG;
	public:
		OutputControl();
		OutputControl(short pinId, bool pinStatus, char * ocTopicCB, PubSubClient* mqttClient, bool DEBUG=false);
		bool outputIsOn();
		const char * getPinStatusToStr();
		virtual ~OutputControl();
		short getPinId() const;
		void setPinId(short pinId);bool getPinStatus() const;
		void setPin(bool pinStatus);
};

#endif /* MODEL_OUTPUTCONTROL_H_ */
