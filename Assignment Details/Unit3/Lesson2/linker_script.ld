ENTRY(reset)

MEMORY
{
    RAM (rwx) : ORIGIN = 0x00010000, LENGTH = 64M
}

SECTIONS
{
    . = 0x00010000;

    .startup . :
    {
        startup.o(.text)
    } > RAM

    .text :
    {
        *(.text*)
    } > RAM

    .data :
    {
        *(.data*)
    } > RAM

    .bss :
    {
        *(.bss*)
        *(COMMON)
    } > RAM

    . += 0x1000;
    stack_ptr = .;
}
