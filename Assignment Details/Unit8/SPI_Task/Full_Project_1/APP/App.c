#include "SPI.h"
#include "UART.h"

//#define SPI_MASTER_MODE_ON   1
#define SPI_SLAVE_MODE_ON   1


/* ================== Global Variables ================== */
SPI_Config_t SPI1_Config;
UART_ConfigPin_t UART_CFG;
GPIO_Config_Pin_t pin_cf;
uint8_t ch;
/* ================== CALL Back Variables ================== */
void UARTCALLBACK()
{
#if SPI_MASTER_MODE_ON
	UART_Receive_Data(&UART_CFG, &ch);
	UART_Send_Data(&UART_CFG, &ch);
	//send to SPI
    GPIO_WritePin(PORTA, GPIO_PIN4, GPIO_LOW);
    SPI_TransmitReceive(&SPI1_Config, &ch, 1);
    GPIO_WritePin(PORTA, GPIO_PIN4, GPIO_HIGH);
#endif


}
void SPICALLBACK(SPI_IRQ_Source_t irq)
{
#if SPI_SLAVE_MODE_ON
	if(irq.RXNE)
	{
		ch=0xF;
		SPI_TransmitReceive(&SPI1_Config, &ch, 1);
		UART_Send_Data(&UART_CFG, &ch);
	}
#endif


}


/* ================== Application Init ================== */


void APP_Init(void)
{
    /* --- Initialize UART for debug printing --- */
    UART_CFG.BaudRate     = UART_BaudRate_115200;
    UART_CFG.HW_FlowCTL   = UART_HW_FlowCTL_NONE;
    UART_CFG.IRQ_Enable   = UART_IRQ_Enable_RXNE;
    UART_CFG.Mode         = UART_Mode_TX_RX;
    UART_CFG.Parity       = UART_Parity_NONE;
    UART_CFG.Payload_Length = UART_Payload_Length_8B;
    UART_CFG.StopBits     = UART_StopBits_1;
    UART_CFG.UART         = UART1;
    UART_CFG.p_IRQ_CallBack = UARTCALLBACK; // No UART IRQ callback needed
    UART_Init(&UART_CFG);

    /* --- Initialize SPI1 as Master, Full Duplex, 16-bit --- */
    SPI1_Config.Instance       = SPI1;


    SPI1_Config.Direction      = SPI_DIRECTION_FULL_DUPLEX;
    SPI1_Config.DataSize       = SPI_DATASIZE_8BIT;
    SPI1_Config.ClockPolarity  = SPI_POLARITY_HIGH;
    SPI1_Config.ClockPhase     = SPI_PHASE_2EDGE;
    SPI1_Config.BaudRate       = SPI_BAUDRATE_DIV8;
    SPI1_Config.FrameFormat    = SPI_FIRSTBIT_MSB;

#if SPI_MASTER_MODE_ON

    SPI1_Config.Mode           = SPI_MODE_MASTER;
    SPI1_Config.NSS            = SPI_NSS_HW_MASTER_ENABLE;
    SPI1_Config.IRQ_Enable     = SPI_IRQ_NONE;
    SPI1_Config.Callback       = NULL;
    // NSS output & high PA4
       pin_cf.PORTx = PORTA;
       pin_cf.Pin_Number = GPIO_PIN4;
       pin_cf.mode = GPIO_MODE_Output_AF_PP;
       pin_cf.Speed = GPIO_SPEED_10M;
       GPIO_InitPin(&pin_cf);
       GPIO_WritePin(PORTA, GPIO_PIN4, GPIO_HIGH);
#endif

#if SPI_SLAVE_MODE_ON

    SPI1_Config.Mode           = SPI_MODE_SLAVE;
    SPI1_Config.NSS            = SPI_NSS_HW_SLAVE;
    SPI1_Config.IRQ_Enable     = SPI_IRQ_RXNE;
    SPI1_Config.Callback       = SPICALLBACK;
    // NSS output & high PA4
       pin_cf.PORTx = PORTA;
       pin_cf.Pin_Number = GPIO_PIN4;
       pin_cf.mode = GPIO_MODE_Output_AF_PP;
       pin_cf.Speed = GPIO_SPEED_10M;
       GPIO_InitPin(&pin_cf);
       GPIO_WritePin(PORTA, GPIO_PIN4, GPIO_HIGH);
#endif
    SPI_Init(&SPI1_Config);




}

/* ================== Application Mode ================== */
void APP_Mode(void)
{

}


