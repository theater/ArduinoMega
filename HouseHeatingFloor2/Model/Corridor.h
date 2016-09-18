/*
 * Corridor.h
 *
 *  Created on: 26.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_CORRIDOR_H_
#define MODEL_CORRIDOR_H_

#include <Room.h>
#include "../Config/Config.h"

class Corridor: public Room {
private:
	const static RoomId id = CORRIDOR;

	OutputControl* radiatorOne;
	OutputControl* radiatorTwo;

	//TODO: ugly - fix it somehow later
	const static int length = 4;
	const char * topics[length] = { RAD_CORRIDOR_01,
									RAD_CORRIDOR_02,
									DESIRED_TEMP_CORRIDOR_01,
									MODE_CORRIDOR };
public:
	Corridor(PubSubClient* mqttClient, bool DEBUG=false);
	virtual ~Corridor();
	void updateOutputControllers();
	void mqttReceive(const char* strTopic, const char* strPayload);
	void heatOutputs(bool state);
	void chillOutputs(bool state) {};
	void humidityControl(bool state, bool fanSpeed) {};
};

#endif /* MODEL_CORRIDOR_H_ */
