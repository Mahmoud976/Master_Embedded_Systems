#ifndef MCU_Config_H
#define MCU_Config_H


#include <stddef.h>

//******************MACROS**********************************
#define RCC          ((RCC_TypeDef*) RCC_BASE  )
#define AFIO         ((AFIO_TypeDef*) AFIO_BASE )

//********************user define **************************
typedef struct{
	volatile uint32_t CR ;
	volatile uint32_t CFGR ;
	volatile uint32_t CIR ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;

}RCC_TypeDef;


//Alternative Function Peripherals Instance
typedef struct {
	volatile uint32_t EVCR ;
	volatile uint32_t MAPR ;
	volatile uint32_t EXTICR[4] ;
	volatile uint32_t RESERVED ;
	volatile uint32_t MAPR2 ;
}AFIO_TypeDef;

/* Macros*/
#define  EXTI0_IRQ           6
#define  EXTI1_IRQ           7
#define  EXTI2_IRQ           8
#define  EXTI3_IRQ           9
#define  EXTI4_IRQ           10
#define  EXTI5_IRQ           23
#define  EXTI6_IRQ           23
#define  EXTI7_IRQ           23
#define  EXTI8_IRQ           23
#define  EXTI9_IRQ           23
#define  EXTI10_IRQ          40
#define  EXTI11_IRQ          40
#define  EXTI12_IRQ          40
#define  EXTI13_IRQ          40
#define  EXTI14_IRQ          40
#define  EXTI15_IRQ          40



/* function like macro */
#define RCC_AFIO_CLK_EN()   (RCC->APB2ENR |=1<<0)

#define RCC_GPIOA_CLK_EN()   (RCC->APB2ENR |=1<<2)
#define RCC_GPIOB_CLK_EN()   (RCC->APB2ENR |=1<<3)

#define RCC_GPIOC_CLK_EN()   (RCC->APB2ENR |=1<<4)
#define RCC_GPIOD_CLK_EN()   (RCC->APB2ENR |=1<<5)

#define RCC_GPIOE_CLK_EN()   (RCC->APB2ENR |=1<<6)


/* NVIC Enable Macros for EXTI lines */
#define NVIC_EXTI0_Enable   (NVIC_ISER0 |= 1 << 6)
#define NVIC_EXTI1_Enable   (NVIC_ISER0 |= 1 << 7)
#define NVIC_EXTI2_Enable   (NVIC_ISER0 |= 1 << 8)
#define NVIC_EXTI3_Enable   (NVIC_ISER0 |= 1 << 9)
#define NVIC_EXTI4_Enable   (NVIC_ISER0 |= 1 << 10)

#define NVIC_EXTI5_Enable   (NVIC_ISER0 |= 1 << 23)
#define NVIC_EXTI6_Enable   (NVIC_ISER0 |= 1 << 23)
#define NVIC_EXTI7_Enable   (NVIC_ISER0 |= 1 << 23)
#define NVIC_EXTI8_Enable   (NVIC_ISER0 |= 1 << 23)
#define NVIC_EXTI9_Enable   (NVIC_ISER0 |= 1 << 23)

#define NVIC_EXTI10_Enable  (NVIC_ISER1 |= 1 << (40-32))
#define NVIC_EXTI11_Enable  (NVIC_ISER1 |= 1 << (40-32))
#define NVIC_EXTI12_Enable  (NVIC_ISER1 |= 1 << (40-32))
#define NVIC_EXTI13_Enable  (NVIC_ISER1 |= 1 << (40-32))
#define NVIC_EXTI14_Enable  (NVIC_ISER1 |= 1 << (40-32))
#define NVIC_EXTI15_Enable  (NVIC_ISER1 |= 1 << (40-32))

/* NVIC Disable Macros for EXTI lines */
#define NVIC_EXTI0_Disable   (NVIC_ICER0 |= 1 << 6)
#define NVIC_EXTI1_Disable   (NVIC_ICER0 |= 1 << 7)
#define NVIC_EXTI2_Disable   (NVIC_ICER0 |= 1 << 8)
#define NVIC_EXTI3_Disable   (NVIC_ICER0 |= 1 << 9)
#define NVIC_EXTI4_Disable   (NVIC_ICER0 |= 1 << 10)

#define NVIC_EXTI5_Disable   (NVIC_ICER0 |= 1 << 23)
#define NVIC_EXTI6_Disable   (NVIC_ICER0 |= 1 << 23)
#define NVIC_EXTI7_Disable   (NVIC_ICER0 |= 1 << 23)
#define NVIC_EXTI8_Disable   (NVIC_ICER0 |= 1 << 23)
#define NVIC_EXTI9_Disable   (NVIC_ICER0 |= 1 << 23)

#define NVIC_EXTI10_Disable  (NVIC_ICER1 |= 1 << (40-32))
#define NVIC_EXTI11_Disable  (NVIC_ICER1 |= 1 << (40-32))
#define NVIC_EXTI12_Disable  (NVIC_ICER1 |= 1 << (40-32))
#define NVIC_EXTI13_Disable  (NVIC_ICER1 |= 1 << (40-32))
#define NVIC_EXTI14_Disable  (NVIC_ICER1 |= 1 << (40-32))
#define NVIC_EXTI15_Disable  (NVIC_ICER1 |= 1 << (40-32))

#endif //end MCU_Config_H
