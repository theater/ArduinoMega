// Do not remove the include below

#include "HouseHeating.h"

#include <Timer.h>

#include "Config/Config.h"
#include "Model/BedRoomKids.h"

short tempSensorReal = 22;
short humSensorReal = 80;

BedRoomKids bedRoomKids;
Timer trigger;


void triggerFunc(){
	bedRoomKids.updateSensors(tempSensorReal,humSensorReal);
	bedRoomKids.setOutputControllers();
}

//The setup function is called once at startup of the sketch
void setup()
{
	trigger.every(REOCCURRENCE,&triggerFunc);
}

// The loop function is called in an endless loop
void loop()
{
	trigger.update();
}
