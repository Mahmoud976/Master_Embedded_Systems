/*
 * startup.c - Cortex-M3 Startup File
 * Author: Mahmoud Saleh
 * Description: This file sets up the vector table, initializes .data and .bss sections,
 *              and then calls main().
 */

#include <stdint.h>

 /* Symbols defined in the linker script */
extern uint32_t _sidata;   /* Start address of initialized data in FLASH */
extern uint32_t _sdata;    /* Start address of .data section in SRAM */
extern uint32_t _edata;    /* End address of .data section in SRAM */
extern uint32_t _sbss;     /* Start address of .bss section in SRAM */
extern uint32_t _ebss;     /* End address of .bss section in SRAM */
extern uint32_t _estack;   /* End of stack (top of stack) */

extern int main(void);     /* Main application entry point */

/* Forward declarations of interrupt handlers */
void Reset_Handler(void);
void Default_Handler(void);

/* Weak aliases for fault handlers to Default_Handler */
void NMI_Handler(void)         __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));

/* Vector table placed at the start of FLASH */
__attribute__((section(".vectors")))
void (* const vectors[])(void) = {
    (void (*)(void)) & _estack,   /* Initial Stack Pointer */
    Reset_Handler,               /* Reset Handler */
    NMI_Handler,                 /* NMI Handler */
    HardFault_Handler,           /* Hard Fault Handler */
    MemManage_Handler,           /* MPU Fault Handler */
    BusFault_Handler,            /* Bus Fault Handler */
    UsageFault_Handler           /* Usage Fault Handler */
};

/* Default interrupt handler - infinite loop */
void Default_Handler(void) {
    Reset_Handler(); /* Hang here if unexpected interrupt occurs*/
   // while (1); /* Hang here if unexpected interrupt occurs */
}

/* Reset Handler - executed on system reset */
void Reset_Handler(void) {
    uint32_t* src;
    uint32_t* dst_data;
    uint32_t size_data = (uint32_t)&_edata - (uint32_t)&_sdata;

    /* Copy initialized .data section from FLASH to SRAM */
    src = &_sidata;
    dst_data = &_sdata;

    for (int i = 0; i < size_data; i++)
    {
        *dst_data++ = *src++;
    }

    /* Zero initialize .bss section in SRAM */
    uint32_t* dst_bss;
    uint32_t size_bss = (uint32_t)&_ebss - (uint32_t)&_sbss;
    dst_bss = &_sbss;

    for (int i = 0; i < size_bss; i++)
    {
        *dst_bss++ = 0;
    }

    /* Call the application's entry point */
    main();

    /* If main() returns, loop forever */
    while (1);
}
