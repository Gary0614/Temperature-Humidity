################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/UART/uart_driver.c 

OBJS += \
./Drivers/BSP/UART/uart_driver.o 

C_DEPS += \
./Drivers/BSP/UART/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/UART/%.o Drivers/BSP/UART/%.su Drivers/BSP/UART/%.cyclo: ../Drivers/BSP/UART/%.c Drivers/BSP/UART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"E:/Code/CubeIDE/STM32F103C8T6_Structdemo/Core/APP" -I"E:/Code/CubeIDE/STM32F103C8T6_Structdemo/Drivers/BSP/UART" -I"E:/Code/CubeIDE/STM32F103C8T6_Structdemo/Drivers/BSP/LED" -I"E:/Code/CubeIDE/STM32F103C8T6_Structdemo/Drivers/BSP/SHT31" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-UART

clean-Drivers-2f-BSP-2f-UART:
	-$(RM) ./Drivers/BSP/UART/uart_driver.cyclo ./Drivers/BSP/UART/uart_driver.d ./Drivers/BSP/UART/uart_driver.o ./Drivers/BSP/UART/uart_driver.su

.PHONY: clean-Drivers-2f-BSP-2f-UART

