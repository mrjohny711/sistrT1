/*
 * André Gomes 	- 1130743
 * João Azevedo - 1111476
 */

#include "stm32f10x.h"
#include <stdint.h>
#include <lcd.h>

volatile uint8_t flag_tx=0;

void RCC_Config_HSE_PLL_Max();
void NVIC_Config();
void GPIO_Config();
void TIM3_Config();
void USART2_Config();
void SPI_Config();

int main(void)
{
	RCC_Config_HSE_PLL_Max();
	GPIO_Config();
	USART2_Config();
	NVIC_Config();
	TIM3_Config();
    /* Infinite loop */

	GPIO_WriteBit(GPIOB,GPIO_Pin_1, 1);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    while(1){
    	while(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)==RESET);
    	flag_tx=1;
    	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE)==RESET);
    	USART_SendData(USART2, 'a');
    	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    }
}

void SPI_Config(){
	RCC_APB1PeriphClkCmd(RCC_APB1Periph_SPI2, ENABLE);

	SPI_InitTypeDef SPI_InitStructure;

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	SPI_Init(SPI2, &SPI_InitStructure);

	SPI_Cmd(SPI2, ENABLE);
}

void RCC_Config_HSE_PLL_Max(){
	RCC_DeInit();

	RCC_HSEConfig(RCC_HSE_ON);

	ErrorStatus HSEStartUpStatus;

	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS){
		FLASH_SetLatency(FLASH_Latency_2);
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		RCC_HCLKConfig(RCC_SYSCLK_Div1); //AHB prescaler 1
		RCC_PCLK1Config(RCC_HCLK_Div2); //APB1 prescaler 2 - max 36 MHz
		RCC_PCLK2Config(RCC_HCLK_Div1); //APB2 prescaler 1

		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_6);
		RCC_PLLCmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);


		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() != 0x08);
	}
	else
		while(1);
}

void NVIC_Config(){
	/*
	 * NVIC Config
	 * PriorityGroup1 - USART2
	 */

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/*
	 * Interrupção global da USART2 com prioridade 0
	 * e sub-prioridade 0
	 */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/*
	 * Ativação da interrupção do fim de registo
	 * de transmissão vazio
	 * TXE - Transmission Interrupt
	 */

	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE);

	/*
	 * Ativação da interrupção da receção de dados
	 * RXNE - Receive Interrupt
	 */

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/*
	 * Ativação da interrupção do fim de transmissão
	 * completa
	 * TC- Transmission Complete
	 */
	//USART_ITConfig(USART2, USART_IT_TC, ENABLE);
}

void GPIO_Config(){
	/*
	 * Enable do GPIOA e GPIOB
	 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	/*
	 * Rx (GPIOA10)
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*
	 * Tx (GPIOA9)
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*
	 * LED (GPIOB1)
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*
	 * SPI2
	 * SCK 	- GPIOB13
	 * MISO - GPIOB14
	 * MOSI	- GPIOB15
	 */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_

}

void TIM3_Config(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/*
	 * Counter Mode Up  1 Hz (1000 ms)
	    /|   /|
	   / |  / |
	  /  | /  |
	 /   |/   |
	|----|----|
	   T

	 *   (PSC+1)*(ARR+1)
	 * T=---------------- , CK_INT = 72 MHz ; PSC=35999 ; ARR = 1999;
	 *       CK_INT
	 */

	TIM_TimeBaseStructure.TIM_Period = 1999 ;//auto reload
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_Prescaler = 35999; //prescaler
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_Cmd(TIM3, ENABLE);
}

void USART2_Config(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitTypeDef USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART2, &USART_InitStructure);

	USART_Cmd(USART2, ENABLE);
}
