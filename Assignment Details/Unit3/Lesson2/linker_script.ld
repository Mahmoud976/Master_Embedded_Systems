ENTRY(reset);

MEMORY
{
	MEM(rwx) : ORIGIN = 0x00000000, LENGTH = 64M
}
SECTIONS
{
. = 0x10000;

.startup . :{startup.o (.text)}
.text : { *(.text) } > MEM
.data : { *(.data) } > MEM
.bss  : { *(.bss)  } > MEM
. += 0x1000;
stack_ptr = .;

}
