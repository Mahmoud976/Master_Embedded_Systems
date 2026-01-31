/*
 startup.s - Cortex-M3
 Copyright: Mahmoud.Saleh
*/

.syntax unified            /* Use unified ARM/Thumb syntax */
.cpu cortex-m3             /* Target CPU: Cortex-M3 */
.thumb                     /* Use Thumb instruction set */

/*--------------------------------------------------
 Global symbols
--------------------------------------------------*/
 


.global _reset             /* Make Reset Handler visible to linker */
.global Vectors_Handler    /* Make default interrupt handler global */
.extern main               /* main() function defined in C */

/* Symbols from linker script */

.extern _sidata            /* Start address of initialized data in FLASH */
.extern _sdata             /* Start address of .data section in SRAM */
.extern _edata             /* End address of .data section in SRAM */
.extern _sbss              /* Start address of .bss section in SRAM */
.extern _ebss              /* End address of .bss section in SRAM */
.global _estack            /* Top of stack (defined in linker script) */

/*--------------------------------------------------
 Vector Table
--------------------------------------------------*/

.section .vectors, "a", %progbits   /* Vector table stored in FLASH */
.word   _estack                /* Initial Stack Pointer */
.word   _reset                 /* Reset Handler */
.word   Vectors_Handler        /* NMI */
.word   Vectors_Handler        /* Hard Fault */
.word   Vectors_Handler        /* MemManage Fault */
.word   Vectors_Handler        /* Bus Fault */
.word   Vectors_Handler        /* Usage Fault */
.word   0                      /* Reserved */
.word   0                      /* Reserved */
.word   0                      /* Reserved */
.word   0                      /* Reserved */
.word   Vectors_Handler        /* SVCall */
.word   Vectors_Handler        /* Debug Monitor */
.word   0                      /* Reserved */
.word   Vectors_Handler        /* PendSV */
.word   Vectors_Handler        /* SysTick */
.word   Vectors_Handler        /* WWDG */
.word   Vectors_Handler        /* PVD */
.word   Vectors_Handler        /* TAMPER */
.word   Vectors_Handler        /* RTC */
.word   Vectors_Handler        /* FLASH */
.word   Vectors_Handler        /* RCC */
.word   Vectors_Handler        /* EXTI Line 10 */
.word   Vectors_Handler        /* EXTI Line 11 */
.word   Vectors_Handler        /* EXTI Line 12 */

/*--------------------------------------------------
 Reset Handler
--------------------------------------------------*/

.section .text
.thumb_func
_reset:
  /*ldr   SP, =_estack*/

/*--------------------------------------------------
 Copy initialized data from FLASH to SRAM (.data)
--------------------------------------------------*/

    ldr   r0, =_sidata       /* r0 = source address in FLASH */
    ldr   r1, =_sdata        /* r1 = destination address in SRAM */
    ldr   r2, =_edata        /* r2 = end of .data section in SRAM */

copy_data:
    cmp   r1, r2             /* Check if end of .data reached */
    itt   lt                 /* Execute next TWO instructions if r1 < r2 */
    ldrlt r3, [r0], #4       /* Load word from FLASH, increment r0 */
    strlt r3, [r1], #4       /* Store word to SRAM, increment r1 */
    blt   copy_data          /* Loop until all data is copied */
      /* #4 >> automatically increments the pointer to avoid overwriting the same memory location.*/
/*--------------------------------------------------
 Zero initialize .bss section
--------------------------------------------------*/

    ldr   r0, =_sbss         /* r0 = start of .bss */
    ldr   r1, =_ebss         /* r1 = end of .bss */

zero_bss:
    cmp   r0, r1             /* Check if end of .bss reached */
    itt   lt                 /* Execute next TWO instructions if r0 < r1 */
    movlt r2, #0             /* r2 = 0 */
    strlt r2, [r0], #4       /* Store zero, increment r0 */
    blt   zero_bss           /* Loop until .bss is cleared */

/*--------------------------------------------------
 Call main()
--------------------------------------------------*/

    bl main                  /* Jump to main() */

/* If main() returns, stay here */
_stop:
    b _stop                  /* Infinite loop */

/*--------------------------------------------------
 Default Interrupt Handler
--------------------------------------------------*/

.thumb_func
Vectors_Handler:
    b _reset                  /* Trap CPU on unexpected interrupt */
