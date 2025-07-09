################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/storage/src/adc.c \
../Core/storage/src/dma.c \
../Core/storage/src/rom_load.c 

OBJS += \
./Core/storage/src/adc.o \
./Core/storage/src/dma.o \
./Core/storage/src/rom_load.o 

C_DEPS += \
./Core/storage/src/adc.d \
./Core/storage/src/dma.d \
./Core/storage/src/rom_load.d 


# Each subdirectory must supply rules for building sources it contributes
Core/storage/src/%.o Core/storage/src/%.su Core/storage/src/%.cyclo: ../Core/storage/src/%.c Core/storage/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-storage-2f-src

clean-Core-2f-storage-2f-src:
	-$(RM) ./Core/storage/src/adc.cyclo ./Core/storage/src/adc.d ./Core/storage/src/adc.o ./Core/storage/src/adc.su ./Core/storage/src/dma.cyclo ./Core/storage/src/dma.d ./Core/storage/src/dma.o ./Core/storage/src/dma.su ./Core/storage/src/rom_load.cyclo ./Core/storage/src/rom_load.d ./Core/storage/src/rom_load.o ./Core/storage/src/rom_load.su

.PHONY: clean-Core-2f-storage-2f-src

