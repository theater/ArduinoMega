// Do not remove the include below

#include "HouseHeating.h"

#include <Timer.h>

#include "Config/Config.h"
#include "Model/BedRoomKids.h"

short tempSensorReal = 22; //simulation values
short humSensorReal = 80; //simulation values

BedRoomKids bedRoomKids;

Timer trigger;
void triggerFunc(){
	tempSensorReal = random(15,35);  //simulation values
	humSensorReal = random(40,100); //simulation values
	//TODO take out serial prints
	Serial.print("Temperature sensor value:"); Serial.println(tempSensorReal);
	Serial.print("Humidity sensor value:"); Serial.println(humSensorReal);
	bedRoomKids.updateSensors(tempSensorReal,humSensorReal);
	bedRoomKids.updateOutputControllers();
}

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
	trigger.every(REOCCURRENCE,&triggerFunc);
	triggerFunc();
}

// The loop function is called in an endless loop
void loop()
{
	trigger.update();
}
