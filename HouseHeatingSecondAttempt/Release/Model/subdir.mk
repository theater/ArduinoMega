################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Model/MotionSensor.cpp \
../Model/Sensor.cpp \
../Model/TemperatureSensor.cpp 

LINK_OBJ += \
./Model/MotionSensor.cpp.o \
./Model/Sensor.cpp.o \
./Model/TemperatureSensor.cpp.o 

CPP_DEPS += \
./Model/MotionSensor.cpp.d \
./Model/Sensor.cpp.d \
./Model/TemperatureSensor.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
Model/MotionSensor.cpp.o: ../Model/MotionSensor.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\HomeAutomation\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"D:\HomeAutomation\Arduino\hardware\arduino\avr\cores\arduino" -I"D:\HomeAutomation\Arduino\hardware\arduino\avr\variants\mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

Model/Sensor.cpp.o: ../Model/Sensor.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\HomeAutomation\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"D:\HomeAutomation\Arduino\hardware\arduino\avr\cores\arduino" -I"D:\HomeAutomation\Arduino\hardware\arduino\avr\variants\mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

Model/TemperatureSensor.cpp.o: ../Model/TemperatureSensor.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\HomeAutomation\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"D:\HomeAutomation\Arduino\hardware\arduino\avr\cores\arduino" -I"D:\HomeAutomation\Arduino\hardware\arduino\avr\variants\mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


