/*
 * MasterBedroom.h
 *
 *  Created on: 27.06.2016 ã.
 *      Author: theater
 */

#ifndef MODEL_MASTERBEDROOM_H_
#define MODEL_MASTERBEDROOM_H_

#include <Room.h>
#include "../Config/Config.h"

class MasterBedroom: public Room {
private:
	const static RoomId id = MASTER_BEDROOM;

	OutputControl* radiatorOne;

	//TODO: ugly - fix it somehow later
	const static int length = 3;
	const char * topics[length] = { RAD_MASTER_BEDROOM,
									DESIRED_TEMP_MASTER_BEDROOM_01,
									MODE_MASTER_BEDROOM };
public:
	MasterBedroom(PubSubClient* mqttClient, bool DEBUG = false);
	virtual ~MasterBedroom();
	void updateOutputControllers();
	void mqttReceive(const char* strTopic, const char* strPayload);
	void heatOutputs(bool state);
	void chillOutputs(bool state) {	};
	void humidityControl(bool state, bool fanSpeed) { };
};

#endif /* MODEL_MASTERBEDROOM_H_ */
