/*
 * BigBathroom.h
 *
 *  Created on: 26.06.2016 �.
 *      Author: theater
 */

#ifndef MODEL_BIGBATHROOM_H_
#define MODEL_BIGBATHROOM_H_

#include <Room.h>

#include "../Config/Config.h"

class BigBathroom: public Room {
public:
	const static RoomId id = BIG_BATHROOM;

		OutputControl* radiatorOne;
		OutputControl* radiatorTwo;
		OutputControl* fan;

		//TODO: ugly - fix it somehow later
		const static int length = 6;
		const char * topics[length] = { RAD_BIGBATH_01,
										RAD_BIGBATH_02,
										FAN_BIGBATH,
										DESIRED_TEMP_BIGBATH_01,
										DESIRED_HUM_BIGBATH_01,
										MODE_BIGBATH };
public:
	BigBathroom(PubSubClient* mqttClient, bool DEBUG=false);
	virtual ~BigBathroom();
	void updateOutputControllers();
	void mqttReceive(const char* strTopic, const char* strPayload);
	void heatOutputs(bool state);
	void chillOutputs(bool state) {};
	void humidityOutputs(bool state);
};

#endif /* MODEL_BIGBATHROOM_H_ */