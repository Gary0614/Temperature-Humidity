################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/APP/esp32_comm.c \
../Core/APP/led_task.c \
../Core/APP/myuart.c 

OBJS += \
./Core/APP/esp32_comm.o \
./Core/APP/led_task.o \
./Core/APP/myuart.o 

C_DEPS += \
./Core/APP/esp32_comm.d \
./Core/APP/led_task.d \
./Core/APP/myuart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/APP/%.o Core/APP/%.su Core/APP/%.cyclo: ../Core/APP/%.c Core/APP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"E:/Code/CubeIDE/STM32F103C8T6_Structdemo/Core/APP" -I"E:/Code/CubeIDE/STM32F103C8T6_Structdemo/Drivers/BSP/UART" -I"E:/Code/CubeIDE/STM32F103C8T6_Structdemo/Drivers/BSP/LED" -I"E:/Code/CubeIDE/STM32F103C8T6_Structdemo/Drivers/BSP/SHT31" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-APP

clean-Core-2f-APP:
	-$(RM) ./Core/APP/esp32_comm.cyclo ./Core/APP/esp32_comm.d ./Core/APP/esp32_comm.o ./Core/APP/esp32_comm.su ./Core/APP/led_task.cyclo ./Core/APP/led_task.d ./Core/APP/led_task.o ./Core/APP/led_task.su ./Core/APP/myuart.cyclo ./Core/APP/myuart.d ./Core/APP/myuart.o ./Core/APP/myuart.su

.PHONY: clean-Core-2f-APP

