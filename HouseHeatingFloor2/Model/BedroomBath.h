/*
 * BedroomBath.h
 *
 *  Created on: 27.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_BEDROOMBATH_H_
#define MODEL_BEDROOMBATH_H_

#include <Room.h>

#include "../Config/Config.h"
#include "Fan.h"

class BedroomBath: public Room {
public:
	const static RoomId id = BEDROOM_BATH;

		OutputControl* radiatorOne;
		Fan* fan;

		//TODO: ugly - fix it somehow later
		const static int length = 6;
		const char * topics[length] = { RAD_BEDROOM_BATH,
										FAN_SWITCH_BEDROOM_BATH,
										FAN_SPEED_BEDROOM_BATH,
										DESIRED_TEMP_BEDROOM_BATH_01,
										DESIRED_HUM_BEDROOM_BATH_01,
										MODE_BEDROOM_BATH };
public:
	BedroomBath(PubSubClient* mqttClient);
	virtual ~BedroomBath();
	void updateOutputControllers();
	void mqttReceive(const char* strTopic, const char* strPayload);
	void heatOutputs(bool state);
	void chillOutputs(bool state) {};
	void humidityControl(bool state, bool fanSpeed);
};

#endif /* MODEL_BEDROOMBATH_H_ */
