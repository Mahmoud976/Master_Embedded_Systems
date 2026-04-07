################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/GPIO.c \
../Src/KeyPad.c \
../Src/LCD.c \
../Src/Led.c \
../Src/RCC.c \
../Src/UART.c \
../Src/main.c \
../Src/servo.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timer.c 

OBJS += \
./Src/GPIO.o \
./Src/KeyPad.o \
./Src/LCD.o \
./Src/Led.o \
./Src/RCC.o \
./Src/UART.o \
./Src/main.o \
./Src/servo.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timer.o 

C_DEPS += \
./Src/GPIO.d \
./Src/KeyPad.d \
./Src/LCD.d \
./Src/Led.d \
./Src/RCC.d \
./Src/UART.d \
./Src/main.d \
./Src/servo.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/MCAL" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/ECUAL/Led_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/ECUAL/LCD_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/ECUAL/KeyPad_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/ECUAL/ServoMotor_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/MCAL/Timer_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/ECUAL/EEPROM_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/MCAL/I2C_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/MCAL/SPI_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/MCAL/GPIO_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/MCAL/RCC_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/MCAL/UART_Driver" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/MCAL/Interrupt_Driver" -I../Inc -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/APP" -I"G:/concol/Learn_in_depth/Master_Embedded_Systems/Projects/Second_Term/Full_Project_2/Utilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/GPIO.cyclo ./Src/GPIO.d ./Src/GPIO.o ./Src/GPIO.su ./Src/KeyPad.cyclo ./Src/KeyPad.d ./Src/KeyPad.o ./Src/KeyPad.su ./Src/LCD.cyclo ./Src/LCD.d ./Src/LCD.o ./Src/LCD.su ./Src/Led.cyclo ./Src/Led.d ./Src/Led.o ./Src/Led.su ./Src/RCC.cyclo ./Src/RCC.d ./Src/RCC.o ./Src/RCC.su ./Src/UART.cyclo ./Src/UART.d ./Src/UART.o ./Src/UART.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/servo.cyclo ./Src/servo.d ./Src/servo.o ./Src/servo.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timer.cyclo ./Src/timer.d ./Src/timer.o ./Src/timer.su

.PHONY: clean-Src

