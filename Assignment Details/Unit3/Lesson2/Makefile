CC=arm-none-eabi-
CFLAGS=-g -mcpu=arm926ej-s
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
ASM=$(wildcard *.s)
ASMOBJ=$(ASM:.s=.o)
Project_Name=learn_in_depth

all: $(Project_Name).bin
	@echo "============= Build is done ==========="

# Assemble startup
startup.o: startup.s
	$(CC)as $(CFLAGS) $< -o $@

# Compile C files
%.o: %.c
	$(CC)gcc -c $(CFLAGS) $(INCS) $< -o $@

# Link ELF
$(Project_Name).elf: $(OBJ) $(ASMOBJ)
	$(CC)ld -T linker_script.ld $(LIBS) $(OBJ) $(ASMOBJ) -o $@

# Convert ELF to BIN
$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy -O binary $< $@

# Clean all
clear_all:
	rm -f *.o *.elf *.bin

clear:
	rm -f *.elf *.bin

