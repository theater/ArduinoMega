/*
 * Wardrobe.h
 *
 *  Created on: 27.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_WARDROBE_H_
#define MODEL_WARDROBE_H_

#include <Room.h>
#include "../Config/Config.h"

class Wardrobe: public Room {
	const static RoomId id = WARDROBE;

	OutputControl* radiatorOne;

	//TODO: ugly - fix it somehow later
	const static int length = 3;
	const char * topics[length] = { RAD_WARDROBE,
	DESIRED_TEMP_WARDROBE_01,
	MODE_WARDROBE };
public:
	Wardrobe(PubSubClient* mqttClient, bool DEBUG = false);
	virtual ~Wardrobe();
	void updateOutputControllers();
	void mqttReceive(const char* strTopic, const char* strPayload);
	void heatOutputs(bool state);
	void chillOutputs(bool state) {};
	void humidityOutputs(bool state, bool fanSpeed) {};
	;
};

#endif /* MODEL_WARDROBE_H_ */
