################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/UIPEthernet/utility/subdir.mk
-include libraries/UIPEthernet/subdir.mk
-include libraries/Timer/subdir.mk
-include libraries/Room/subdir.mk
-include libraries/OneWire/subdir.mk
-include libraries/MQTT/subdir.mk
-include libraries/EmonLib/subdir.mk
-include libraries/Dallas\ Temperature/subdir.mk
-include libraries/DHT/subdir.mk
-include core/core/subdir.mk
-include Model/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
arduino.ar \

ELF += \
HouseHeatingFloor2.elf \

EEP += \
HouseHeatingFloor2.eep \

FLASH_IMAGE += \
HouseHeatingFloor2.hex \


# All Target
all: HouseHeatingFloor2

# Tool invocations
HouseHeatingFloor2: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-size" -A "D:/src/ArduinoMega/HouseHeatingFloor2/Release/HouseHeatingFloor2.elf"
	@echo 'Finished building target: $@'
	@echo ' '

arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-ar" rcs     arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

HouseHeatingFloor2.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-gcc" -Os -Wl,--gc-sections,--relax -mmcu=atmega2560  -o "D:/src/ArduinoMega/HouseHeatingFloor2/Release/HouseHeatingFloor2.elf"   $(LINK_OBJ) $(AR)    "-LD:/src/ArduinoMega/HouseHeatingFloor2/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

HouseHeatingFloor2.eep: $(ELF)
	@echo 'Create eeprom image'
	"C:\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "D:/src/ArduinoMega/HouseHeatingFloor2/Release/HouseHeatingFloor2.elf" "D:/src/ArduinoMega/HouseHeatingFloor2/Release/HouseHeatingFloor2.eep"
	@echo 'Finished building: $@'
	@echo ' '

HouseHeatingFloor2.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"C:\eclipse\arduinoPlugin\tools\arduino\avr-gcc\4.8.1-arduino5/bin/avr-objcopy" -O ihex -R .eeprom  "D:/src/ArduinoMega/HouseHeatingFloor2/Release/HouseHeatingFloor2.elf" "D:/src/ArduinoMega/HouseHeatingFloor2/Release/HouseHeatingFloor2.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS) HouseHeatingFloor2
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
