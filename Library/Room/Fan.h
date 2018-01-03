/*
 * Fan.h
 *
 *  Created on: 16.09.2016 ã.
 *      Author: theater
 */

#ifndef LIBRARIES_ROOM_FAN_H_
#define LIBRARIES_ROOM_FAN_H_

#include <Util.h>
#include "OutputControl.h"
#include "PubSubClient.h"
#include "util.h"

class OutputControl;
class PubSubClient;

class Fan {
public:
	Fan(FanControlType fanType, short fanSwitchPinId, bool fanSwitchPinStatus, char * fanSwitchTopicCB,
			 	 	 	 	 	short fanSpeedPinId, bool fanSpeedPinStatus, char * fanSpeedTopicCB,
								PubSubClient* mqttClient, bool DEBUG=false);
	Fan(FanControlType fanType, short fanSwitchPinId, bool fanSwitchPinStatus, char * fanSwitchTopicCB,
									PubSubClient* mqttClient, bool DEBUG=false);
	virtual ~Fan();
	void fanControl(bool state, bool speed);

private:
	FanControlType fanType;
	OutputControl* fanSwitch;
	OutputControl* fanSpeedControl;

// Getters and setters
public:
	FanControlType getFanType();
	void setFanType(FanControlType fanType);
	OutputControl* getFanSpeedControl();
	OutputControl* getFanSwitch();
};

#endif /* LIBRARIES_ROOM_FAN_H_ */
