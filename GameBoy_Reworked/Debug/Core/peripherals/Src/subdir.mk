################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/peripherals/Src/adc.c \
../Core/peripherals/Src/engine.c \
../Core/peripherals/Src/i2c.c \
../Core/peripherals/Src/spi.c \
../Core/peripherals/Src/tim.c \
../Core/peripherals/Src/uart.c 

OBJS += \
./Core/peripherals/Src/adc.o \
./Core/peripherals/Src/engine.o \
./Core/peripherals/Src/i2c.o \
./Core/peripherals/Src/spi.o \
./Core/peripherals/Src/tim.o \
./Core/peripherals/Src/uart.o 

C_DEPS += \
./Core/peripherals/Src/adc.d \
./Core/peripherals/Src/engine.d \
./Core/peripherals/Src/i2c.d \
./Core/peripherals/Src/spi.d \
./Core/peripherals/Src/tim.d \
./Core/peripherals/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/peripherals/Src/%.o Core/peripherals/Src/%.su Core/peripherals/Src/%.cyclo: ../Core/peripherals/Src/%.c Core/peripherals/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-peripherals-2f-Src

clean-Core-2f-peripherals-2f-Src:
	-$(RM) ./Core/peripherals/Src/adc.cyclo ./Core/peripherals/Src/adc.d ./Core/peripherals/Src/adc.o ./Core/peripherals/Src/adc.su ./Core/peripherals/Src/engine.cyclo ./Core/peripherals/Src/engine.d ./Core/peripherals/Src/engine.o ./Core/peripherals/Src/engine.su ./Core/peripherals/Src/i2c.cyclo ./Core/peripherals/Src/i2c.d ./Core/peripherals/Src/i2c.o ./Core/peripherals/Src/i2c.su ./Core/peripherals/Src/spi.cyclo ./Core/peripherals/Src/spi.d ./Core/peripherals/Src/spi.o ./Core/peripherals/Src/spi.su ./Core/peripherals/Src/tim.cyclo ./Core/peripherals/Src/tim.d ./Core/peripherals/Src/tim.o ./Core/peripherals/Src/tim.su ./Core/peripherals/Src/uart.cyclo ./Core/peripherals/Src/uart.d ./Core/peripherals/Src/uart.o ./Core/peripherals/Src/uart.su

.PHONY: clean-Core-2f-peripherals-2f-Src

