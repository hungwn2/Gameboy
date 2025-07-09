################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/device_drivers/src/button.c \
../Core/device_drivers/src/joystick.c 

OBJS += \
./Core/device_drivers/src/button.o \
./Core/device_drivers/src/joystick.o 

C_DEPS += \
./Core/device_drivers/src/button.d \
./Core/device_drivers/src/joystick.d 


# Each subdirectory must supply rules for building sources it contributes
Core/device_drivers/src/%.o Core/device_drivers/src/%.su Core/device_drivers/src/%.cyclo: ../Core/device_drivers/src/%.c Core/device_drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-device_drivers-2f-src

clean-Core-2f-device_drivers-2f-src:
	-$(RM) ./Core/device_drivers/src/button.cyclo ./Core/device_drivers/src/button.d ./Core/device_drivers/src/button.o ./Core/device_drivers/src/button.su ./Core/device_drivers/src/joystick.cyclo ./Core/device_drivers/src/joystick.d ./Core/device_drivers/src/joystick.o ./Core/device_drivers/src/joystick.su

.PHONY: clean-Core-2f-device_drivers-2f-src

