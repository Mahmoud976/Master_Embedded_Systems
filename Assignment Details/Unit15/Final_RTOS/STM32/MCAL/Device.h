#ifndef MYMCU_H
#define MYMCU_H

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================= */
/* ============           Interrupt Number Definition           ============ */
/* ========================================================================= */

typedef enum IRQn
{
  /* Cortex-M3 Exceptions */
  Reset_IRQn             = -15,
  NonMaskableInt_IRQn    = -14,
  HardFault_IRQn         = -13,
  MemoryManagement_IRQn  = -12,
  BusFault_IRQn          = -11,
  UsageFault_IRQn        = -10,
  SVCall_IRQn            =  -5,
  DebugMonitor_IRQn      =  -4,
  PendSV_IRQn            =  -2,
  SysTick_IRQn           =  -1,

  /* Device Specific Interrupts */
  TIM0_IRQn              = 0,
  TIM1_IRQn              = 1,
  TIM2_IRQn              = 2,
  UART0_IRQn             = 3,
  GPIO_IRQn              = 4

} IRQn_Type;


/* ========================================================================= */
/* ============      Processor and Core Peripheral Section      ============ */
/* ========================================================================= */

/* Cortex-M3 Configuration */
#define __CM3_REV               0x0201U
#define __NVIC_PRIO_BITS        4U
#define __Vendor_SysTickConfig  0U
#define __VTOR_PRESENT          1U
#define __MPU_PRESENT           1U
#define __FPU_PRESENT           0U   /* M3 مفيهوش FPU */
#define __DSP_PRESENT           0U   /* مفيش DSP instructions زي M4 */


/* CMSIS Core */
#include "core_cm3.h"
#include "system_mymcu.h"


/* ========================================================================= */
/* ============       Device Specific Peripheral Section        ============ */
/* ========================================================================= */

/* ===================== TIMER ===================== */
typedef struct
{
  __IOM uint32_t LOAD;
  __IM  uint32_t VALUE;
  __IOM uint32_t CONTROL;
  __OM  uint32_t INTCLR;
  __IM  uint32_t RIS;
  __IM  uint32_t MIS;
  __IOM uint32_t BGLOAD;
} MY_TMR_TypeDef;


/* CONTROL Register Bits */
#define MY_TMR_CONTROL_ENABLE_Pos      7
#define MY_TMR_CONTROL_ENABLE_Msk     (1UL << MY_TMR_CONTROL_ENABLE_Pos)

#define MY_TMR_CONTROL_MODE_Pos        6
#define MY_TMR_CONTROL_MODE_Msk       (1UL << MY_TMR_CONTROL_MODE_Pos)

#define MY_TMR_CONTROL_IE_Pos          5
#define MY_TMR_CONTROL_IE_Msk         (1UL << MY_TMR_CONTROL_IE_Pos)


/* ========================================================================= */
/* ============     Device Specific Peripheral Address Map      ============ */
/* ========================================================================= */

#define MY_FLASH_BASE       (0x00000000UL)
#define MY_SRAM_BASE        (0x20000000UL)
#define MY_PERIPH_BASE      (0x40000000UL)

/* Timers */
#define MYTIM0_BASE         (MY_PERIPH_BASE + 0x0000)
#define MYTIM1_BASE         (MY_PERIPH_BASE + 0x0800)
#define MYTIM2_BASE         (MY_PERIPH_BASE + 0x1000)


/* ========================================================================= */
/* ============             Peripheral declaration              ============ */
/* ========================================================================= */

#define MY_TIM0   ((MY_TMR_TypeDef *) MYTIM0_BASE)
#define MY_TIM1   ((MY_TMR_TypeDef *) MYTIM1_BASE)
#define MY_TIM2   ((MY_TMR_TypeDef *) MYTIM2_BASE)


#ifdef __cplusplus
}
#endif

#endif /* MYMCU_H */
