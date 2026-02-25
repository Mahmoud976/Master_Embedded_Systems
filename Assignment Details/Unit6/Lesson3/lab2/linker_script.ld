/* Linker script - Cortex-M3
   Copyright: Mahmoud.Saleh
*/

MEMORY
{
    FLASH (RX) : ORIGIN = 0x08000000, LENGTH = 128K
    SRAM  (RWX): ORIGIN = 0x20000000, LENGTH = 20K
}

/* Stack size definition - OUTSIDE SECTIONS */
_stack_size = 0x1000;  /* 4 KB stack */

/* Sections */
SECTIONS
{
    /* Vector table + code + rodata in Flash */
    .text : 
    {
        KEEP(*(.vectors*))        /* Vector table at start */
        *(.text*)                 /* Code */
        *(.rodata*)               /* Read-only data */
    } > FLASH

    /* Initialized data in SRAM, loaded from Flash */
    .data : 
    {
        . = ALIGN(8);             /* ensure start aligned */
        _sdata = .;               /* start of .data in SRAM */
        *(.data*)                 /* all .data sections */
        . = ALIGN(8);             /* align end of .data */
        _edata = .;               /* end of .data in SRAM */
    } > SRAM AT > FLASH
    _sidata = LOADADDR(.data);    /* flash address for initial values */

    /* Zero-initialized data (BSS) in SRAM */
    .bss : 
    {
        . = ALIGN(8);             /* ensure start aligned */
        _sbss = .;                /* start of BSS */
        *(.bss*)                  /* all .bss sections */
        *(COMMON)                 /* any COMMON variables */
        . = ALIGN(8);             /* align end of .bss */
        _ebss = .;                /* end of BSS */
    } > SRAM
    
/* Stack top symbol - INSIDE SECTIONS */
    _estack = . + 0x1000;
}




/* --------------------------------------------------
   RAM usage safety check (OUTSIDE SECTIONS)
-------------------------------------------------- */
_total_ram_used = SIZEOF(.data) + SIZEOF(.bss);
ASSERT(_total_ram_used <= LENGTH(SRAM),
       "ERROR: .data + .bss exceeds SRAM size!");
