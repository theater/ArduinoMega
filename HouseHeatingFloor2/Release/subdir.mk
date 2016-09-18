################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HouseHeatingFloor2.cpp 

LINK_OBJ += \
./HouseHeatingFloor2.cpp.o 

CPP_DEPS += \
./HouseHeatingFloor2.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
HouseHeatingFloor2.cpp.o: ../HouseHeatingFloor2.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"C:\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.5\cores\arduino" -I"C:\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.5\variants\mega" -I"D:\HomeAutomation\ArduinoLibs\EmonLib" -I"D:\HomeAutomation\ArduinoLibs\OneWire" -I"D:\HomeAutomation\ArduinoLibs\Timer" -I"D:\HomeAutomation\ArduinoLibs\UIPEthernet" -I"D:\HomeAutomation\ArduinoLibs\UIPEthernet\utility" -I"D:\HomeAutomation\ArduinoLibs\MQTT" -I"D:\src\ArduinoMega\Library\Room" -I"D:\HomeAutomation\ArduinoLibs\Dallas Temperature" -I"D:\HomeAutomation\ArduinoLibs\DHT" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


