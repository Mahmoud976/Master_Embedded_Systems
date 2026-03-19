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
	volatile uint32_t EXTICR1 ;
	volatile uint32_t EXTICR2 ;
	volatile uint32_t EXTICR3 ;
	volatile uint32_t EXTICR4 ;
	volatile uint32_t RESERVED ;
	volatile uint32_t MAPR2 ;
}AFIO_TypeDef;



/* function like macro */
#define RCC_GPIOA_CLK_EN()   (RCC->APB2ENR |=1<<2)
#define RCC_GPIOB_CLK_EN()   (RCC->APB2ENR |=1<<3)

#define RCC_GPIOC_CLK_EN()   (RCC->APB2ENR |=1<<4)
#define RCC_GPIOD_CLK_EN()   (RCC->APB2ENR |=1<<5)

#define RCC_GPIOE_CLK_EN()   (RCC->APB2ENR |=1<<6)

#endif //end MCU_Config_H
