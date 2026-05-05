#ifndef SYSTEM_MYMCU_H
#define SYSTEM_MYMCU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* ================= Vector Table Type ================= */
typedef void(*VECTOR_TABLE_Type)(void);

/* ================= System Clock ================= */

/* Default system clock (مثلاً 8 MHz internal RC) */
#define HSI_VALUE    (8000000UL)

/* ممكن تضيف external لو حابب */
#define HSE_VALUE    (16000000UL)

/* System Core Clock Variable */
extern uint32_t SystemCoreClock;


/* ================= Function Prototypes ================= */

/**
  * @brief  Initialize system
  *         - Setup clock
  *         - Setup vector table location
  */
void SystemInit(void);

/**
  * @brief  Update SystemCoreClock variable
  */
void SystemCoreClockUpdate(void);


#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_MYMCU_H */
