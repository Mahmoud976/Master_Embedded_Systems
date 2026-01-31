#=====================================================
#      Copyright (c) Mahmoud.Saleh
#     ARM Embedded Systems Makefile
#=====================================================

#-----------------------------------------------------
# Toolchain
#-----------------------------------------------------

# C compiler
CC=arm-none-eabi-gcc.exe

# Assembler
AS=arm-none-eabi-as.exe

# Linker
LD=arm-none-eabi-ld.exe

# Object copy tool (ELF -> BIN)
OBJCOPY=arm-none-eabi-objcopy.exe

#-----------------------------------------------------
# Compiler flags
#-----------------------------------------------------
# -mcpu : target CPU 
# -g : generate debug information 
# -gdwarf-2 : generate debug information compatible with proteus

CFLAGS=-gdwarf-2 -mcpu=cortex-m3 -mthumb

# Include directories
INCS=-I .

#-----------------------------------------------------
# Source files
#-----------------------------------------------------

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

ASM_SRC=$(wildcard *.s)
ASM_OBJ=$(ASM_SRC:.s=.o)

# Libraries (if required)
LIBS=

# Project name
Project_Name=learn_in_depth

#-----------------------------------------------------
# Build targets
#-----------------------------------------------------

all: $(Project_Name).hex
	@echo "============ build is done ============="

#-----------------------------------------------------
# Compile rules
#-----------------------------------------------------

# Assemble .s files into .o files
%.o: %.s
	$(AS) $(CFLAGS) $< -o $@

# Compile .c files into .o files
%.o: %.c
	$(CC) -c $(CFLAGS) $(INCS) $< -o $@

#-----------------------------------------------------
# Linking
#-----------------------------------------------------

# Link all object files into ELF using linker script
$(Project_Name).elf: $(OBJ) $(ASM_OBJ)
	$(LD) -T linker_script.ld $(LIBS) $(OBJ) $(ASM_OBJ) -o $@ -Map=Map_file.map

#-----------------------------------------------------
# Binary generation
#-----------------------------------------------------

# Convert ELF file to raw binary
$(Project_Name).bin: $(Project_Name).elf
	$(OBJCOPY) -O binary $< $@


#-----------------------------------------------------
# hexa generation
#-----------------------------------------------------

# Convert ELF file to raw hexa
$(Project_Name).hex: $(Project_Name).elf
	$(OBJCOPY) -O ihex $< $@

#-----------------------------------------------------
# Clean
#-----------------------------------------------------

# Remove all generated files
clean_all:
	rm -f *.o *.elf *.bin *.map *.asm  *.hex

# Remove only final output files (ELF & BIN)
clean:
	rm -f *.elf *.bin *.hex

