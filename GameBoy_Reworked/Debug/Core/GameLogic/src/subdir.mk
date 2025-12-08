################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/GameLogic/src/aabb.c \
../Core/GameLogic/src/components.c \
../Core/GameLogic/src/my_vector.c 

OBJS += \
./Core/GameLogic/src/aabb.o \
./Core/GameLogic/src/components.o \
./Core/GameLogic/src/my_vector.o 

C_DEPS += \
./Core/GameLogic/src/aabb.d \
./Core/GameLogic/src/components.d \
./Core/GameLogic/src/my_vector.d 


# Each subdirectory must supply rules for building sources it contributes
Core/GameLogic/src/%.o Core/GameLogic/src/%.su Core/GameLogic/src/%.cyclo: ../Core/GameLogic/src/%.c Core/GameLogic/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-GameLogic-2f-src

clean-Core-2f-GameLogic-2f-src:
	-$(RM) ./Core/GameLogic/src/aabb.cyclo ./Core/GameLogic/src/aabb.d ./Core/GameLogic/src/aabb.o ./Core/GameLogic/src/aabb.su ./Core/GameLogic/src/components.cyclo ./Core/GameLogic/src/components.d ./Core/GameLogic/src/components.o ./Core/GameLogic/src/components.su ./Core/GameLogic/src/my_vector.cyclo ./Core/GameLogic/src/my_vector.d ./Core/GameLogic/src/my_vector.o ./Core/GameLogic/src/my_vector.su

.PHONY: clean-Core-2f-GameLogic-2f-src

