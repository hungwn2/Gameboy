################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/src/adc.c \
../Core/drivers/src/dac.c \
../Core/drivers/src/gpio.c \
../Core/drivers/src/i2c.c \
../Core/drivers/src/rcc.c \
../Core/drivers/src/spi.c \
../Core/drivers/src/uart.c 

OBJS += \
./Core/drivers/src/adc.o \
./Core/drivers/src/dac.o \
./Core/drivers/src/gpio.o \
./Core/drivers/src/i2c.o \
./Core/drivers/src/rcc.o \
./Core/drivers/src/spi.o \
./Core/drivers/src/uart.o 

C_DEPS += \
./Core/drivers/src/adc.d \
./Core/drivers/src/dac.d \
./Core/drivers/src/gpio.d \
./Core/drivers/src/i2c.d \
./Core/drivers/src/rcc.d \
./Core/drivers/src/spi.d \
./Core/drivers/src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/src/%.o Core/drivers/src/%.su Core/drivers/src/%.cyclo: ../Core/drivers/src/%.c Core/drivers/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-drivers-2f-src

clean-Core-2f-drivers-2f-src:
	-$(RM) ./Core/drivers/src/adc.cyclo ./Core/drivers/src/adc.d ./Core/drivers/src/adc.o ./Core/drivers/src/adc.su ./Core/drivers/src/dac.cyclo ./Core/drivers/src/dac.d ./Core/drivers/src/dac.o ./Core/drivers/src/dac.su ./Core/drivers/src/gpio.cyclo ./Core/drivers/src/gpio.d ./Core/drivers/src/gpio.o ./Core/drivers/src/gpio.su ./Core/drivers/src/i2c.cyclo ./Core/drivers/src/i2c.d ./Core/drivers/src/i2c.o ./Core/drivers/src/i2c.su ./Core/drivers/src/rcc.cyclo ./Core/drivers/src/rcc.d ./Core/drivers/src/rcc.o ./Core/drivers/src/rcc.su ./Core/drivers/src/spi.cyclo ./Core/drivers/src/spi.d ./Core/drivers/src/spi.o ./Core/drivers/src/spi.su ./Core/drivers/src/uart.cyclo ./Core/drivers/src/uart.d ./Core/drivers/src/uart.o ./Core/drivers/src/uart.su

.PHONY: clean-Core-2f-drivers-2f-src

