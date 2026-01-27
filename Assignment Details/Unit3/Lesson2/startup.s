.global reset
reset:
	ldr  sp, =stack_ptr
	bl main
stop:
	b stop
