################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/App.c \
../Src/GPIO.c \
../Src/RCC.c \
../Src/UART.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/App.o \
./Src/GPIO.o \
./Src/RCC.o \
./Src/UART.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/App.d \
./Src/GPIO.d \
./Src/RCC.d \
./Src/UART.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit7/Lesson_4/Full_Project_1/MCAL" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit7/Lesson_4/Full_Project_1/MCAL/GPIO_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit7/Lesson_4/Full_Project_1/MCAL/RCC_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit7/Lesson_4/Full_Project_1/MCAL/UART_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit7/Lesson_4/Full_Project_1/MCAL/Interrupt_Driver" -I../Inc -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit7/Lesson_4/Full_Project_1/APP" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Assignment Details/Unit7/Lesson_4/Full_Project_1/Utilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/App.cyclo ./Src/App.d ./Src/App.o ./Src/App.su ./Src/GPIO.cyclo ./Src/GPIO.d ./Src/GPIO.o ./Src/GPIO.su ./Src/RCC.cyclo ./Src/RCC.d ./Src/RCC.o ./Src/RCC.su ./Src/UART.cyclo ./Src/UART.d ./Src/UART.o ./Src/UART.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

