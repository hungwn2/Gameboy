################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/src/button.c \
../Core/drivers/src/ili9341.c \
../Core/drivers/src/joystick.c 

OBJS += \
./Core/drivers/src/button.o \
./Core/drivers/src/ili9341.o \
./Core/drivers/src/joystick.o 

C_DEPS += \
./Core/drivers/src/button.d \
./Core/drivers/src/ili9341.d \
./Core/drivers/src/joystick.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/src/%.o Core/drivers/src/%.su Core/drivers/src/%.cyclo: ../Core/drivers/src/%.c Core/drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-drivers-2f-src

clean-Core-2f-drivers-2f-src:
	-$(RM) ./Core/drivers/src/button.cyclo ./Core/drivers/src/button.d ./Core/drivers/src/button.o ./Core/drivers/src/button.su ./Core/drivers/src/ili9341.cyclo ./Core/drivers/src/ili9341.d ./Core/drivers/src/ili9341.o ./Core/drivers/src/ili9341.su ./Core/drivers/src/joystick.cyclo ./Core/drivers/src/joystick.d ./Core/drivers/src/joystick.o ./Core/drivers/src/joystick.su

.PHONY: clean-Core-2f-drivers-2f-src

