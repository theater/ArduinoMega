/*
 * BigBathroom.h
 *
 *  Created on: 26.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_BIGBATHROOM_H_
#define MODEL_BIGBATHROOM_H_

#include <Room.h>

#include "../Config/Config.h"
#include "Fan.h"

class BigBathroom: public Room {
public:
	const static RoomId id = BIG_BATHROOM;

		OutputControl* radiatorOne;
		OutputControl* radiatorTwo;
		Fan* fan;

		//TODO: ugly - fix it somehow later
		const static int length = 9;
		const char * topics[length] = { RAD_BIGBATH_01,
										RAD_BIGBATH_02,
										FAN_SWITCH_BIGBATH,
										FAN_SPEED_BIGBATH,
										DESIRED_TEMP_BIGBATH_01,
										DESIRED_HUM_BIGBATH_01,
										MODE_BIGBATH,
										SENSOR_BIGBATH_01,
										SENSOR_BIGBATH_02};
public:
	BigBathroom(PubSubClient* mqttClient);
	virtual ~BigBathroom();
	void updateOutputControllers();
	void mqttReceive(const char* strTopic, const char* strPayload);
	void heatOutputs(bool state);
	void chillOutputs(bool state) {};
	void humidityControl(bool state, bool fanSpeed);
};

#endif /* MODEL_BIGBATHROOM_H_ */
