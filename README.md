# ArduinoMega
This is Arduino Mega based project for my house heating system. It uses object-oriented model for all relations and consumes more memory thus we use Arduino mega for it. All abstract / library classes are under Library/Room/Model folder. The particular implementation that creates the real objects is under the floors folders. 
It uses manager for handling the objects and adapter for handling the communication to the outside world(mqtt) or the real sensors.
