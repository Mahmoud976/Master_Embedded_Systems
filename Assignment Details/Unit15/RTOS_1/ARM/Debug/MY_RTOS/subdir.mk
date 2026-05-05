################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MY_RTOS/CortexMx_OS_Porting.c \
../MY_RTOS/My_RTOS_FIFO.c \
../MY_RTOS/scheduler.c 

OBJS += \
./MY_RTOS/CortexMx_OS_Porting.o \
./MY_RTOS/My_RTOS_FIFO.o \
./MY_RTOS/scheduler.o 

C_DEPS += \
./MY_RTOS/CortexMx_OS_Porting.d \
./MY_RTOS/My_RTOS_FIFO.d \
./MY_RTOS/scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
MY_RTOS/%.o MY_RTOS/%.su MY_RTOS/%.cyclo: ../MY_RTOS/%.c MY_RTOS/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit15/RTOS_1/ARM/MY_RTOS/inc" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit15/RTOS_1/ARM/MCAL/Interrupt_Driver" -I../Inc -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit15/RTOS_1/ARM/APP" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit15/RTOS_1/ARM/Utilities" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit15/RTOS_1/ARM/MCAL" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit15/RTOS_1/ARM/MCAL/GPIO_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MY_RTOS

clean-MY_RTOS:
	-$(RM) ./MY_RTOS/CortexMx_OS_Porting.cyclo ./MY_RTOS/CortexMx_OS_Porting.d ./MY_RTOS/CortexMx_OS_Porting.o ./MY_RTOS/CortexMx_OS_Porting.su ./MY_RTOS/My_RTOS_FIFO.cyclo ./MY_RTOS/My_RTOS_FIFO.d ./MY_RTOS/My_RTOS_FIFO.o ./MY_RTOS/My_RTOS_FIFO.su ./MY_RTOS/scheduler.cyclo ./MY_RTOS/scheduler.d ./MY_RTOS/scheduler.o ./MY_RTOS/scheduler.su

.PHONY: clean-MY_RTOS

