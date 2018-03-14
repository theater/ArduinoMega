// Do not remove the include below
#include "JustMain.h"


//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200);
// Add your initialization code here
}

// The loop function is called in an endless loop
void loop()
{
	Serial.println("Message");
	delay(5000);
}
