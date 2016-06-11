// Do not remove the include below

#include "HouseHeating.h"

#include "Model/OutputControl.h"

OutputControl oc(50,0);

//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(50,OUTPUT);
}

// The loop function is called in an endless loop
void loop()
{
	oc.setPinStatus(!oc.getPinStatus());
	delay(5000);
}
