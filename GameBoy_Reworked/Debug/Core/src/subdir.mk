################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/src/main.c \
../Core/src/stm32f4xx_hal_msp.c \
../Core/src/stm32f4xx_it.c \
../Core/src/syscalls.c \
../Core/src/sysmem.c \
../Core/src/system_stm32f4xx.c 

OBJS += \
./Core/src/main.o \
./Core/src/stm32f4xx_hal_msp.o \
./Core/src/stm32f4xx_it.o \
./Core/src/syscalls.o \
./Core/src/sysmem.o \
./Core/src/system_stm32f4xx.o 

C_DEPS += \
./Core/src/main.d \
./Core/src/stm32f4xx_hal_msp.d \
./Core/src/stm32f4xx_it.d \
./Core/src/syscalls.d \
./Core/src/sysmem.d \
./Core/src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/src/%.o Core/src/%.su Core/src/%.cyclo: ../Core/src/%.c Core/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-src

clean-Core-2f-src:
	-$(RM) ./Core/src/main.cyclo ./Core/src/main.d ./Core/src/main.o ./Core/src/main.su ./Core/src/stm32f4xx_hal_msp.cyclo ./Core/src/stm32f4xx_hal_msp.d ./Core/src/stm32f4xx_hal_msp.o ./Core/src/stm32f4xx_hal_msp.su ./Core/src/stm32f4xx_it.cyclo ./Core/src/stm32f4xx_it.d ./Core/src/stm32f4xx_it.o ./Core/src/stm32f4xx_it.su ./Core/src/syscalls.cyclo ./Core/src/syscalls.d ./Core/src/syscalls.o ./Core/src/syscalls.su ./Core/src/sysmem.cyclo ./Core/src/sysmem.d ./Core/src/sysmem.o ./Core/src/sysmem.su ./Core/src/system_stm32f4xx.cyclo ./Core/src/system_stm32f4xx.d ./Core/src/system_stm32f4xx.o ./Core/src/system_stm32f4xx.su

.PHONY: clean-Core-2f-src

