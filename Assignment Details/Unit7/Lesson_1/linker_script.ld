MEMORY
{
    FLASH (RX) : ORIGIN = 0x08000000, LENGTH = 128K
    SRAM  (RWX): ORIGIN = 0x20000000, LENGTH = 20K
}

_stack_size = 0x1000;

SECTIONS
{
    .text :
    {
        KEEP(*(.vectors*))
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT > FLASH
    _sidata = LOADADDR(.data);

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM

    _estack = ORIGIN(SRAM) + LENGTH(SRAM);
}

_total_ram_used = SIZEOF(.data) + SIZEOF(.bss);
ASSERT(_total_ram_used <= LENGTH(SRAM), "ERROR: .data + .bss exceeds SRAM!");