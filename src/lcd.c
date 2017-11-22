/*
 * lcd.c
 *
 *  Created on: Sep 17, 2016
 *  Based on Circle OS display functions and Adafruit GFX
 */

#include "lcd.h"
#include <stdio.h>
#include <string.h>

const unsigned char  font[] = {
    0x00, 0x00, 0x00, 0x00, 0x00,
	0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
	0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
	0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
	0x18, 0x3C, 0x7E, 0x3C, 0x18,
	0x1C, 0x57, 0x7D, 0x57, 0x1C,
	0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
	0x00, 0x18, 0x3C, 0x18, 0x00,
	0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
	0x00, 0x18, 0x24, 0x18, 0x00,
	0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
	0x30, 0x48, 0x3A, 0x06, 0x0E,
	0x26, 0x29, 0x79, 0x29, 0x26,
	0x40, 0x7F, 0x05, 0x05, 0x07,
	0x40, 0x7F, 0x05, 0x25, 0x3F,
	0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
	0x7F, 0x3E, 0x1C, 0x1C, 0x08,
	0x08, 0x1C, 0x1C, 0x3E, 0x7F,
	0x14, 0x22, 0x7F, 0x22, 0x14,
	0x5F, 0x5F, 0x00, 0x5F, 0x5F,
	0x06, 0x09, 0x7F, 0x01, 0x7F,
	0x00, 0x66, 0x89, 0x95, 0x6A,
	0x60, 0x60, 0x60, 0x60, 0x60,
	0x94, 0xA2, 0xFF, 0xA2, 0x94,
	0x08, 0x04, 0x7E, 0x04, 0x08,
	0x10, 0x20, 0x7E, 0x20, 0x10,
	0x08, 0x08, 0x2A, 0x1C, 0x08,
	0x08, 0x1C, 0x2A, 0x08, 0x08,
	0x1E, 0x10, 0x10, 0x10, 0x10,
	0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
	0x30, 0x38, 0x3E, 0x38, 0x30,
	0x06, 0x0E, 0x3E, 0x0E, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x5F, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x07, 0x00,
	0x14, 0x7F, 0x14, 0x7F, 0x14,
	0x24, 0x2A, 0x7F, 0x2A, 0x12,
	0x23, 0x13, 0x08, 0x64, 0x62,
	0x36, 0x49, 0x56, 0x20, 0x50,
	0x00, 0x08, 0x07, 0x03, 0x00,
	0x00, 0x1C, 0x22, 0x41, 0x00,
	0x00, 0x41, 0x22, 0x1C, 0x00,
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
	0x08, 0x08, 0x3E, 0x08, 0x08,
	0x00, 0x80, 0x70, 0x30, 0x00,
	0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x00, 0x60, 0x60, 0x00,
	0x20, 0x10, 0x08, 0x04, 0x02,
	0x3E, 0x51, 0x49, 0x45, 0x3E,
	0x00, 0x42, 0x7F, 0x40, 0x00,
	0x72, 0x49, 0x49, 0x49, 0x46,
	0x21, 0x41, 0x49, 0x4D, 0x33,
	0x18, 0x14, 0x12, 0x7F, 0x10,
	0x27, 0x45, 0x45, 0x45, 0x39,
	0x3C, 0x4A, 0x49, 0x49, 0x31,
	0x41, 0x21, 0x11, 0x09, 0x07,
	0x36, 0x49, 0x49, 0x49, 0x36,
	0x46, 0x49, 0x49, 0x29, 0x1E,
	0x00, 0x00, 0x14, 0x00, 0x00,
	0x00, 0x40, 0x34, 0x00, 0x00,
	0x00, 0x08, 0x14, 0x22, 0x41,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x00, 0x41, 0x22, 0x14, 0x08,
	0x02, 0x01, 0x59, 0x09, 0x06,
	0x3E, 0x41, 0x5D, 0x59, 0x4E,
	0x7C, 0x12, 0x11, 0x12, 0x7C,
	0x7F, 0x49, 0x49, 0x49, 0x36,
	0x3E, 0x41, 0x41, 0x41, 0x22,
	0x7F, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x49, 0x49, 0x49, 0x41,
	0x7F, 0x09, 0x09, 0x09, 0x01,
	0x3E, 0x41, 0x41, 0x51, 0x73,
	0x7F, 0x08, 0x08, 0x08, 0x7F,
	0x00, 0x41, 0x7F, 0x41, 0x00,
	0x20, 0x40, 0x41, 0x3F, 0x01,
	0x7F, 0x08, 0x14, 0x22, 0x41,
	0x7F, 0x40, 0x40, 0x40, 0x40,
	0x7F, 0x02, 0x1C, 0x02, 0x7F,
	0x7F, 0x04, 0x08, 0x10, 0x7F,
	0x3E, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x09, 0x09, 0x09, 0x06,
	0x3E, 0x41, 0x51, 0x21, 0x5E,
	0x7F, 0x09, 0x19, 0x29, 0x46,
	0x26, 0x49, 0x49, 0x49, 0x32,
	0x03, 0x01, 0x7F, 0x01, 0x03,
	0x3F, 0x40, 0x40, 0x40, 0x3F,
	0x1F, 0x20, 0x40, 0x20, 0x1F,
	0x3F, 0x40, 0x38, 0x40, 0x3F,
	0x63, 0x14, 0x08, 0x14, 0x63,
	0x03, 0x04, 0x78, 0x04, 0x03,
	0x61, 0x59, 0x49, 0x4D, 0x43,
	0x00, 0x7F, 0x41, 0x41, 0x41,
	0x02, 0x04, 0x08, 0x10, 0x20,
	0x00, 0x41, 0x41, 0x41, 0x7F,
	0x04, 0x02, 0x01, 0x02, 0x04,
	0x40, 0x40, 0x40, 0x40, 0x40,
	0x00, 0x03, 0x07, 0x08, 0x00,
	0x20, 0x54, 0x54, 0x78, 0x40,
	0x7F, 0x28, 0x44, 0x44, 0x38,
	0x38, 0x44, 0x44, 0x44, 0x28,
	0x38, 0x44, 0x44, 0x28, 0x7F,
	0x38, 0x54, 0x54, 0x54, 0x18,
	0x00, 0x08, 0x7E, 0x09, 0x02,
	0x18, 0xA4, 0xA4, 0x9C, 0x78,
	0x7F, 0x08, 0x04, 0x04, 0x78,
	0x00, 0x44, 0x7D, 0x40, 0x00,
	0x20, 0x40, 0x40, 0x3D, 0x00,
	0x7F, 0x10, 0x28, 0x44, 0x00,
	0x00, 0x41, 0x7F, 0x40, 0x00,
	0x7C, 0x04, 0x78, 0x04, 0x78,
	0x7C, 0x08, 0x04, 0x04, 0x78,
	0x38, 0x44, 0x44, 0x44, 0x38,
	0xFC, 0x18, 0x24, 0x24, 0x18,
	0x18, 0x24, 0x24, 0x18, 0xFC,
	0x7C, 0x08, 0x04, 0x04, 0x08,
	0x48, 0x54, 0x54, 0x54, 0x24,
	0x04, 0x04, 0x3F, 0x44, 0x24,
	0x3C, 0x40, 0x40, 0x20, 0x7C,
	0x1C, 0x20, 0x40, 0x20, 0x1C,
	0x3C, 0x40, 0x30, 0x40, 0x3C,
	0x44, 0x28, 0x10, 0x28, 0x44,
	0x4C, 0x90, 0x90, 0x90, 0x7C,
	0x44, 0x64, 0x54, 0x4C, 0x44,
	0x00, 0x08, 0x36, 0x41, 0x00,
	0x00, 0x00, 0x77, 0x00, 0x00,
	0x00, 0x41, 0x36, 0x08, 0x00,
	0x02, 0x01, 0x02, 0x04, 0x02,
	0x3C, 0x26, 0x23, 0x26, 0x3C,
	0x1E, 0xA1, 0xA1, 0x61, 0x12,
	0x3A, 0x40, 0x40, 0x20, 0x7A,
	0x38, 0x54, 0x54, 0x55, 0x59,
	0x21, 0x55, 0x55, 0x79, 0x41,
	0x21, 0x54, 0x54, 0x78, 0x41,
	0x21, 0x55, 0x54, 0x78, 0x40,
	0x20, 0x54, 0x55, 0x79, 0x40,
	0x0C, 0x1E, 0x52, 0x72, 0x12,
	0x39, 0x55, 0x55, 0x55, 0x59,
	0x39, 0x54, 0x54, 0x54, 0x59,
	0x39, 0x55, 0x54, 0x54, 0x58,
	0x00, 0x00, 0x45, 0x7C, 0x41,
	0x00, 0x02, 0x45, 0x7D, 0x42,
	0x00, 0x01, 0x45, 0x7C, 0x40,
	0xF0, 0x29, 0x24, 0x29, 0xF0,
	0xF0, 0x28, 0x25, 0x28, 0xF0,
	0x7C, 0x54, 0x55, 0x45, 0x00,
	0x20, 0x54, 0x54, 0x7C, 0x54,
	0x7C, 0x0A, 0x09, 0x7F, 0x49,
	0x32, 0x49, 0x49, 0x49, 0x32,
	0x32, 0x48, 0x48, 0x48, 0x32,
	0x32, 0x4A, 0x48, 0x48, 0x30,
	0x3A, 0x41, 0x41, 0x21, 0x7A,
	0x3A, 0x42, 0x40, 0x20, 0x78,
	0x00, 0x9D, 0xA0, 0xA0, 0x7D,
	0x39, 0x44, 0x44, 0x44, 0x39,
	0x3D, 0x40, 0x40, 0x40, 0x3D,
	0x3C, 0x24, 0xFF, 0x24, 0x24,
	0x48, 0x7E, 0x49, 0x43, 0x66,
	0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
	0xFF, 0x09, 0x29, 0xF6, 0x20,
	0xC0, 0x88, 0x7E, 0x09, 0x03,
	0x20, 0x54, 0x54, 0x79, 0x41,
	0x00, 0x00, 0x44, 0x7D, 0x41,
	0x30, 0x48, 0x48, 0x4A, 0x32,
	0x38, 0x40, 0x40, 0x22, 0x7A,
	0x00, 0x7A, 0x0A, 0x0A, 0x72,
	0x7D, 0x0D, 0x19, 0x31, 0x7D,
	0x26, 0x29, 0x29, 0x2F, 0x28,
	0x26, 0x29, 0x29, 0x29, 0x26,
	0x30, 0x48, 0x4D, 0x40, 0x20,
	0x38, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x38,
	0x2F, 0x10, 0xC8, 0xAC, 0xBA,
	0x2F, 0x10, 0x28, 0x34, 0xFA,
	0x00, 0x00, 0x7B, 0x00, 0x00,
	0x08, 0x14, 0x2A, 0x14, 0x22,
	0x22, 0x14, 0x2A, 0x14, 0x08,
	0xAA, 0x00, 0x55, 0x00, 0xAA,
	0xAA, 0x55, 0xAA, 0x55, 0xAA,
	0x00, 0x00, 0x00, 0xFF, 0x00,
	0x10, 0x10, 0x10, 0xFF, 0x00,
	0x14, 0x14, 0x14, 0xFF, 0x00,
	0x10, 0x10, 0xFF, 0x00, 0xFF,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x14, 0x14, 0x14, 0xFC, 0x00,
	0x14, 0x14, 0xF7, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x14, 0x14, 0xF4, 0x04, 0xFC,
	0x14, 0x14, 0x17, 0x10, 0x1F,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0x1F, 0x00,
	0x10, 0x10, 0x10, 0xF0, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0x1F, 0x10,
	0x10, 0x10, 0x10, 0xF0, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x10,
	0x10, 0x10, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0xFF, 0x10,
	0x00, 0x00, 0x00, 0xFF, 0x14,
	0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x1F, 0x10, 0x17,
	0x00, 0x00, 0xFC, 0x04, 0xF4,
	0x14, 0x14, 0x17, 0x10, 0x17,
	0x14, 0x14, 0xF4, 0x04, 0xF4,
	0x00, 0x00, 0xFF, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0xF7, 0x00, 0xF7,
	0x14, 0x14, 0x14, 0x17, 0x14,
	0x10, 0x10, 0x1F, 0x10, 0x1F,
	0x14, 0x14, 0x14, 0xF4, 0x14,
	0x10, 0x10, 0xF0, 0x10, 0xF0,
	0x00, 0x00, 0x1F, 0x10, 0x1F,
	0x00, 0x00, 0x00, 0x1F, 0x14,
	0x00, 0x00, 0x00, 0xFC, 0x14,
	0x00, 0x00, 0xF0, 0x10, 0xF0,
	0x10, 0x10, 0xFF, 0x10, 0xFF,
	0x14, 0x14, 0x14, 0xFF, 0x14,
	0x10, 0x10, 0x10, 0x1F, 0x00,
	0x00, 0x00, 0x00, 0xF0, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
	0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
	0x38, 0x44, 0x44, 0x38, 0x44,
	0x7C, 0x2A, 0x2A, 0x3E, 0x14,
	0x7E, 0x02, 0x02, 0x06, 0x06,
	0x02, 0x7E, 0x02, 0x7E, 0x02,
	0x63, 0x55, 0x49, 0x41, 0x63,
	0x38, 0x44, 0x44, 0x3C, 0x04,
	0x40, 0x7E, 0x20, 0x1E, 0x20,
	0x06, 0x02, 0x7E, 0x02, 0x02,
	0x99, 0xA5, 0xE7, 0xA5, 0x99,
	0x1C, 0x2A, 0x49, 0x2A, 0x1C,
	0x4C, 0x72, 0x01, 0x72, 0x4C,
	0x30, 0x4A, 0x4D, 0x4D, 0x30,
	0x30, 0x48, 0x78, 0x48, 0x30,
	0xBC, 0x62, 0x5A, 0x46, 0x3D,
	0x3E, 0x49, 0x49, 0x49, 0x00,
	0x7E, 0x01, 0x01, 0x01, 0x7E,
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
	0x44, 0x44, 0x5F, 0x44, 0x44,
	0x40, 0x51, 0x4A, 0x44, 0x40,
	0x40, 0x44, 0x4A, 0x51, 0x40,
	0x00, 0x00, 0xFF, 0x01, 0x03,
	0xE0, 0x80, 0xFF, 0x00, 0x00,
	0x08, 0x08, 0x6B, 0x6B, 0x08,
	0x36, 0x12, 0x36, 0x24, 0x36,
	0x06, 0x0F, 0x09, 0x0F, 0x06,
	0x00, 0x00, 0x18, 0x18, 0x00,
	0x00, 0x00, 0x10, 0x10, 0x00,
	0x30, 0x40, 0xFF, 0x01, 0x01,
	0x00, 0x1F, 0x01, 0x01, 0x1E,
	0x00, 0x19, 0x1D, 0x17, 0x12,
	0x00, 0x3C, 0x3C, 0x3C, 0x3C,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

#define abs(X) ( ( (X) < 0 ) ? -(X) : (X) )
#define sgn(X) ( ( (X) < 0 ) ? -1 : 1 )

const uint8_t width = 128;
const uint8_t height = 160;
uint8_t madctl;
uint8_t lcd_initialized=0;
uint16_t background_color = color_black;


void set_background_color ( uint16_t color )
{
	background_color = color;
}


void lcd_delay_pool(uint16_t time2delay)
{
	volatile uint32_t dummy = 0;

	for (dummy = time2delay*500; dummy > 0 ; dummy--);
}


void lcd_backligth_on( void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
}

void lcd_backlight_off( void )
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
}

void lcd_init ( void )
{

	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	if (lcd_initialized == 0)
	{
		/*RCC do GPIOB e GPIOD*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);

		//Backlight
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
		//  	GPIO_InitTypeDef GPIO_InitStructure;

		/* Enable GPIOA clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);


		/* Configure the SPI */

		/*GPIOA5  SCK  Alternate Function*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/*GPIOA7  SDA MOSI Alternate Function*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/*GPIOA8 - RS Out Push-pull*/
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/*GPIOA4 SS  Out Push-pull*/
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);  /*ativar o SS*/

		GPIO_PinRemapConfig ( GPIO_Remap_SWJ_NoJTRST, ENABLE ) ;
		/*GPIOB4 RESET  Out Push-pull*/
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);


		/*RCC do SPI2*/
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
		SPI_Init(SPI1, &SPI_InitStructure);

		SPI_Cmd(SPI1, ENABLE);



		/*Initialize the display*/
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);

		GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_SET);

		//vTaskDelay( ( TickType_t ) 500 / portTICK_PERIOD_MS ); //delay(500);
		//_delay_ms ((double) 500);
		lcd_delay_pool(500);

		GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_RESET);

		// vTaskDelay( ( TickType_t ) 500 / portTICK_PERIOD_MS );   //delay(500);
		//_delay_ms ((double) 500);
		lcd_delay_pool(500);

		GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_SET);
		//_delay_ms ((double) 500);
		// 	vTaskDelay( ( TickType_t ) 500 / portTICK_PERIOD_MS );   //delay(500);
		lcd_delay_pool(500);

		lcd_send_commnad(ST7735_SWRESET); // software reset
		// 	vTaskDelay( ( TickType_t ) 150 / portTICK_PERIOD_MS );
		//_delay_ms ((double) 150);
		lcd_delay_pool(150);

		lcd_send_commnad(ST7735_SLPOUT);  // out of sleep mode
		// 	vTaskDelay( ( TickType_t ) 500 / portTICK_PERIOD_MS );//delay(500);
		//_delay_ms ((double) 500);
		lcd_delay_pool(500);

		lcd_send_commnad(ST7735_FRMCTR1);  // frame rate control - normal mode
		lcd_send_data(0x01);  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
		lcd_send_data(0x2C);
		lcd_send_data(0x2D);

		lcd_send_commnad(ST7735_FRMCTR2);  // frame rate control - idle mode
		lcd_send_data(0x01);  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
		lcd_send_data(0x2C);
		lcd_send_data(0x2D);

		lcd_send_commnad(ST7735_FRMCTR3);  // frame rate control - partial mode
		lcd_send_data(0x01); // dot inversion mode
		lcd_send_data(0x2C);
		lcd_send_data(0x2D);
		lcd_send_data(0x01); // line inversion mode
		lcd_send_data(0x2C);
		lcd_send_data(0x2D);

		lcd_send_commnad(ST7735_INVCTR);  // display inversion control
		lcd_send_data(0x07);  // no inversion

		lcd_send_commnad(ST7735_PWCTR1);  // power control
		lcd_send_data(0xA2);
		lcd_send_data(0x02);      // -4.6V
		lcd_send_data(0x84);      // AUTO mode

		lcd_send_commnad(ST7735_PWCTR2);  // power control
		lcd_send_data(0xC5);      // VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD

		lcd_send_commnad(ST7735_PWCTR3);  // power control
		lcd_send_data(0x0A);      // Opamp current small
		lcd_send_data(0x00);      // Boost frequency

		lcd_send_commnad(ST7735_PWCTR4);  // power control
		lcd_send_data(0x8A);      // BCLK/2, Opamp current small & Medium low
		lcd_send_data(0x2A);

		lcd_send_commnad(ST7735_PWCTR5);  // power control
		lcd_send_data(0x8A);
		lcd_send_data(0xEE);

		lcd_send_commnad(ST7735_VMCTR1);  // power control
		lcd_send_data(0x0E);

		lcd_send_commnad(ST7735_INVOFF);    // don't invert display

		lcd_send_commnad(ST7735_MADCTL);  // memory access control (directions)
		lcd_send_data(0xC0);  // row address/col address, bottom to top refresh
		madctl = 0xC0;

		lcd_send_commnad(ST7735_COLMOD);  // set color mode
		lcd_send_data(0x05);        // 16-bit color

		lcd_send_commnad(ST7735_CASET);  // column addr set
		lcd_send_data(0x00);
		lcd_send_data(0x00);   // XSTART = 0
		lcd_send_data(0x00);
		lcd_send_data(0x7F);   // XEND = 127

		lcd_send_commnad(ST7735_RASET);  // row addr set
		lcd_send_data(0x00);
		lcd_send_data(0x00);    // XSTART = 0
		lcd_send_data(0x00);
		lcd_send_data(0x9F);    // XEND = 159

		lcd_send_commnad(ST7735_GMCTRP1);
		lcd_send_data(0x0f);
		lcd_send_data(0x1a);
		lcd_send_data(0x0f);
		lcd_send_data(0x18);
		lcd_send_data(0x2f);
		lcd_send_data(0x28);
		lcd_send_data(0x20);
		lcd_send_data(0x22);
		lcd_send_data(0x1f);
		lcd_send_data(0x1b);
		lcd_send_data(0x23);
		lcd_send_data(0x37);
		lcd_send_data(0x00);
		lcd_send_data(0x07);
		lcd_send_data(0x02);
		lcd_send_data(0x10);
		lcd_send_commnad(ST7735_GMCTRN1);
		lcd_send_data(0x0f);
		lcd_send_data(0x1b);
		lcd_send_data(0x0f);
		lcd_send_data(0x17);
		lcd_send_data(0x33);
		lcd_send_data(0x2c);
		lcd_send_data(0x29);
		lcd_send_data(0x2e);
		lcd_send_data(0x30);
		lcd_send_data(0x30);
		lcd_send_data(0x39);
		lcd_send_data(0x3f);
		lcd_send_data(0x00);
		lcd_send_data(0x07);
		lcd_send_data(0x03);
		lcd_send_data(0x10);

		lcd_send_commnad(ST7735_DISPON);
		//_delay_ms ((double) 100);
		// vTaskDelay( ( TickType_t ) 100 / portTICK_PERIOD_MS );//delay(100);
		lcd_delay_pool(100);

		lcd_send_commnad(ST7735_NORON);  // normal display on
		//_delay_ms ((double) 10);
		//vTaskDelay( ( TickType_t ) 10 / portTICK_PERIOD_MS );//delay(10);
		lcd_delay_pool(10);

		lcd_draw_fillrect(0, 0 , LCD_WIDTH, LCD_HEIGHT, 0x0000) ;

		lcd_initialized=1;

	}
}

 void lcd_send_commnad(  uint8_t txCommand )
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
	lcd_spi_send(txCommand);
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);

}

 void lcd_send_data( uint8_t txData )
{

	GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
	lcd_spi_send(txData);
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
}

uint8_t lcd_spi_send( uint8_t txByte )
{
	/* Loop while DR register in not emplty */
	while( SPI_I2S_GetFlagStatus( SPI1, SPI_I2S_FLAG_TXE ) == RESET );
	/* Send byte through the SPI2 peripheral */
	SPI_I2S_SendData( SPI1, txByte );
	/* Wait to receive a byte */
	while( SPI_I2S_GetFlagStatus( SPI1, SPI_I2S_FLAG_RXNE ) == RESET );
	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData( SPI1 );
}

 void lcd_draw_string(uint8_t x, uint8_t y, unsigned char *c, uint16_t color, uint8_t size)
{
	while (c[0] != 0)
	{
		lcd_draw_char(x, y, c[0], color, size);
		x += size*6;
		c++;
		if (x + 5 >= width)
		{
			y += 10;
			x = 0;
		}
	}
}

 void lcd_draw_pixel(uint8_t x, uint8_t y, uint16_t color)
{
	if ((x >= width) || (y >= height)) return;
	lcd_setAddrWindow(x,y,x+1,y+1);

	GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);

	lcd_spi_send(color >> 8);
	lcd_spi_send(color);

	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);

}

 void lcd_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color)
 {

	 int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

	 lcd_setAddrWindow(x1, y1, x2, y2);
	 GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
	 GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);

	 if ( x1==x2 )  //Vertical Line
	 {
		 if ( y1 > y2 ) //We assume y2>y1 and invert if not
		 {
			 i = y2;
			 y2 = y1;
			 y1 = i;
		 }
		 lcd_draw_fillrect( x1, y1, 1, y2-y1+1, color );
		 return;
	 }
	 else if ( y1==y2 )  //Horizontal Line
	 {
		 if ( x1 > x2 ) //We assume x2>x1 and we swap them if not
		 {
			 i = x2;
			 x2 = x1;
			 x1 = i;
		 }
		 lcd_draw_fillrect( x1, y1, x2-x1+1, 1, color );
		 return;
	 }

	 dx=x2-x1;      /* the horizontal distance of the line */
	 dy=y2-y1;      /* the vertical distance of the line */
	 dxabs=abs(dx);
	 dyabs=abs(dy);
	 sdx=sgn(dx);
	 sdy=sgn(dy);
	 x=dyabs>>1;
	 y=dxabs>>1;
	 px=x1;
	 py=y1;

	 if (dxabs>=dyabs) /* the line is more horizontal than vertical */
	 {
		 for(i=0;i<dxabs;i++)
		 {
			 y+=dyabs;
			 if (y>=dxabs)
			 {
				 y-=dxabs;
				 py+=sdy;
			 }
			 px+=sdx;
			 lcd_draw_pixel(px,py,color);
		 }
	 }
	 else /* the line is more vertical than horizontal */
	 {
		 for(i=0;i<dyabs;i++)
		 {
			 x+=dxabs;
			 if (x>=dyabs)
			 {
				 x-=dyabs;
				 px+=sdx;
			 }
			 py+=sdy;
			 lcd_draw_pixel(px,py,color);
		 }
	 }

	 GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
 }

 void lcd_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color)
 {

   lcd_setAddrWindow(x, y, x+w-1, y+h-1);

   GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
   GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);

   lcd_draw_line( x, y, x+w, y,color);
   lcd_draw_line( x, y, x, y+h,color);
   lcd_draw_line( x+w, y, x+w, y+h,color);
   lcd_draw_line( x, y+h, x+w, y+h,color);

   GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
 }

void lcd_draw_fillrect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color)
{

  lcd_setAddrWindow(x, y, x+w-1, y+h-1);

  GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
  GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);

  for (x=0; x < w; x++) {
    for (y=0; y < h; y++) {
      lcd_spi_send(color>>8 );
      lcd_spi_send(color);
    }
  }
  GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
}


void lcd_setAddrWindow( uint8_t x,uint8_t y,uint8_t x1,uint8_t y1 )
{
	lcd_send_commnad(ST7735_CASET);
	lcd_send_data(0x00);
	lcd_send_data(x+0);
	lcd_send_data(0x00);
	lcd_send_data(x1+0);

	lcd_send_commnad(ST7735_RASET);
	lcd_send_data(0x00);
	lcd_send_data(y+0);
	lcd_send_data(0x00);
	lcd_send_data(y1+0);
	lcd_send_commnad(ST7735_RAMWR);
}

void lcd_draw_pixelFromChar(uint8_t x, uint8_t y, uint16_t color)
{
	//if ((x >= width) || (y >= height)) return;
	lcd_setAddrWindow(x,y,x+1,y+1);

	GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);

	lcd_spi_send(color >> 8);
	lcd_spi_send(color);

	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);

}

void lcd_draw_char(uint8_t x, uint8_t y, unsigned char c, uint16_t color, uint8_t size)
{

	//lcd_setAddrWindow(x,y,x+10,y+16);

	 for(int8_t i=0; i<6; i++ ) {
	      uint8_t line;
	      if(i < 5) line = (uint8_t) font[(c*5)+i];
	      else      line = 0x0;
	      for(int8_t j=0; j<8; j++, line >>= 1) {
	        if(line & 0x1) {
	          if(size == 1) lcd_draw_pixelFromChar(x+i, y+j, color);
	          else          lcd_draw_fillrect(x+i*size, y+j*size, size, size, color);
	        } else /*if(0x0000 != color)*/ {
	          if(size == 1) lcd_draw_pixelFromChar(x+i, y+j, background_color);
	          else          lcd_draw_fillrect(x+i*size, y+j*size, size, size, background_color);
	        }
	      }
	}
}




void lcd_draw_circle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  lcd_draw_pixel(x0 , y0+r, color);
  lcd_draw_pixel(x0 , y0-r, color);
  lcd_draw_pixel(x0+r, y0 , color);
  lcd_draw_pixel(x0-r, y0 , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    lcd_draw_pixel(x0 + x, y0 + y, color);
    lcd_draw_pixel(x0 - x, y0 + y, color);
    lcd_draw_pixel(x0 + x, y0 - y, color);
    lcd_draw_pixel(x0 - x, y0 - y, color);
    lcd_draw_pixel(x0 + y, y0 + x, color);
    lcd_draw_pixel(x0 - y, y0 + x, color);
    lcd_draw_pixel(x0 + y, y0 - x, color);
    lcd_draw_pixel(x0 - y, y0 - x, color);
  }
}


static void prvSendMessageUSART2(char *message)
{
uint16_t cont_aux=0;

    while(cont_aux != strlen(message))
    {
        USART_SendData(USART2, (uint8_t) message[cont_aux]);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
        {
        }
        cont_aux++;
    }
}

void rcc_lcd_info(void)
{
    char buffer_lcd[32];
    uint8_t clock_source;
    RCC_ClocksTypeDef RCC_Clocks;
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Display init*/
    lcd_init();

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);

    /* get the clock values*/
    RCC_GetClocksFreq(&RCC_Clocks);

    /*print them to LCD*/
    sprintf(buffer_lcd, "SYSCLK %d MHz", (int) RCC_Clocks.SYSCLK_Frequency/1000000 );
    //DRAW_DisplayString(10, 100, buffer_lcd, strlen(buffer_lcd));
	lcd_draw_string(10, 10 , (unsigned char *) buffer_lcd, 0x07F0 , 1);
	strcat(buffer_lcd, "\r\n"); prvSendMessageUSART2(buffer_lcd);
    sprintf(buffer_lcd, "HCLK %d MHz", (int) RCC_Clocks.HCLK_Frequency /1000000 );
  //  DRAW_DisplayString(10, 80, buffer_lcd, strlen(buffer_lcd));
    lcd_draw_string(10, 20 , (unsigned char *) buffer_lcd, 0x07F0 , 1);
    strcat(buffer_lcd, "\r\n"); prvSendMessageUSART2(buffer_lcd);
    sprintf(buffer_lcd, "PCLK1 %d MHz", (int) RCC_Clocks.PCLK1_Frequency /1000000 );
   // DRAW_DisplayString(10, 60, buffer_lcd, strlen(buffer_lcd));
    lcd_draw_string(10, 30 , (unsigned char *) buffer_lcd, 0x07F0 , 1);
    strcat(buffer_lcd, "\r\n"); prvSendMessageUSART2(buffer_lcd);
    sprintf(buffer_lcd, "PCLK2 %d MHz", (int) RCC_Clocks.PCLK2_Frequency /1000000 );
   // DRAW_DisplayString(10, 40, buffer_lcd, strlen(buffer_lcd));
    lcd_draw_string(10, 40 , (unsigned char *) buffer_lcd, 0x07F0 , 1);
    strcat(buffer_lcd, "\r\n"); prvSendMessageUSART2(buffer_lcd);
  //  sprintf(buffer_lcd, "PCLK2 %d MHz", RCC_Clocks. /1000000 );
   // DRAW_DisplayString(10, 10, buffer_lcd, strlen(buffer_lcd));
   // lcd_draw_string(10, 10 , (unsigned char *) buffer_lcd, 0x07F0 , 1);

    clock_source = RCC_GetSYSCLKSource();
    if(clock_source == 0x00)
        sprintf(buffer_lcd, "Using HSI.");
    else if(clock_source == 0x04)
        sprintf(buffer_lcd, "Using HSE.");
    else if(clock_source == 0x08)
        sprintf(buffer_lcd, "Using PLL.");
 //   DRAW_DisplayString(10, 10, buffer_lcd, strlen(buffer_lcd));
    lcd_draw_string(10, 60 , (unsigned char *) buffer_lcd, 0x07F0 , 1);
    strcat(buffer_lcd, "\r\n"); prvSendMessageUSART2(buffer_lcd);


    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, DISABLE);
    USART_DeInit(USART2);

}



