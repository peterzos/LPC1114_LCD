/*
 * lcd.c
 *
 *  Created on: Feb 24, 2012
 *      Author: peterz
 */

#include "LPC11xx.h"

#include "FreeRTOS.h"
#include "task.h"

#include "small_gpio.h"
#include "debug.h"
#include "lcd.h"

#define CLR_E()		ClrGPIOBit(1,8)
#define SET_E()		SetGPIOBit(1,8)

#define CLR_RS()	ClrGPIOBit(1,5)
#define SET_RS()	SetGPIOBit(1,5)

#define CLR_DB7()	ClrGPIOBit(3,2)
#define SET_DB7()	SetGPIOBit(3,2)

#define CLR_DB6()	ClrGPIOBit(3,1)
#define SET_DB6()	SetGPIOBit(3,1)

#define CLR_DB5()	ClrGPIOBit(3,0)
#define SET_DB5()	SetGPIOBit(3,0)

#define CLR_DB4()	ClrGPIOBit(0,6)
#define SET_DB4()	SetGPIOBit(0,6)


void LCDWriteByte(char x)
{
	SET_E();
	if (x & (1<<4))
		SET_DB4();
	else
		CLR_DB4();
	if (x & (1<<5))
		SET_DB5();
	else
		CLR_DB5();
	if (x & (1<<6))
		SET_DB6();
	else
		CLR_DB6();
	if (x & (1<<7))
		SET_DB7();
	else
		CLR_DB7();
	CLR_E();
	vTaskDelay (1/portTICK_RATE_MS);	//DelayUS(1);
	SET_E();
	if (x & (1<<0))
		SET_DB4();
	else
		CLR_DB4();
	if (x & (1<<1))
		SET_DB5();
	else
		CLR_DB5();
	if (x & (1<<2))
		SET_DB6();
	else
		CLR_DB6();
	if (x & (1<<3))
		SET_DB7();
	else
		CLR_DB7();
	CLR_E();
	vTaskDelay (10/portTICK_RATE_MS);	//DelayMS(10);
}

void LCDWriteCmd(char x)
{
	CLR_RS();
	LCDWriteByte(x);
}

void LCDPutChar(char x)
{
	SET_RS();
	LCDWriteByte(x);
}

void my_lcd_init()
{

//	LPC_GPIO0->DIR = 0x0FFF; //All GPIO0 pins as output
//	LPC_GPIO0->DATA = 0x0000; //All GPIO0 pins low
//	LPC_GPIO0->MASKED_ACCESS[(1<<3)|(1<<5)] = (1<<3)|(1<<5); //Now set only PIO0.3 & PIO0.5 high
//	LPC_GPIO0->DATA = 0x0FFF; //All GPIO0 pins high
//	LPC_GPIO0->MASKED_ACCESS[(1<<3)|(1<<5)] = 0; //Now clear only PIO0.3 & PI

	SetGPIOOut(3, 2);	//P3.2  = D7
	SetGPIOOut(3, 1);	//P3.1  = D6
	SetGPIOOut(3, 0);	//P3.0  = D5
	SetGPIOOut(0, 6);	//P0.6  = D4
	SetGPIOOut(1, 8);	//P1.8  = E
	SetGPIOOut(1, 5);	//P1.5  = RS
	vTaskDelay (15/portTICK_RATE_MS);


	CLR_E();
	CLR_RS();
	uint8_t i;
	for (i = 0; i < 3; i++)
	{
		SET_E();
		SET_DB4();
		SET_DB5();
		CLR_DB6();
		CLR_DB7();
		CLR_E();
		vTaskDelay (5/portTICK_RATE_MS);	//DelayMS(5);

	}
	SET_E();
	CLR_DB4();
	SET_DB5();
	CLR_DB6();
	CLR_DB7();
	CLR_E();
	vTaskDelay (1/portTICK_RATE_MS);	//DelayMS(1);
	LCDWriteCmd(0x28); /* 2 line mode, 4 bit interface */
	LCDWriteCmd(0x08); /* Display off, cursor off, blinking character at cursor off */
	LCDWriteCmd(0x01); /* Clear the display */
	LCDWriteCmd(0x06); /* Cursor move on next char, after write */
	LCDWriteCmd(0x0C); /* Display on, cursor off, blinking character at cursor off */







	vTaskDelay (10/portTICK_RATE_MS);

}

void LCDClear(void)
{
	LCDWriteCmd(0x01);
}

void LCDGotoXY(uint8_t x, uint8_t y)
{
	switch(y)
	{
	case 0:
		LCDWriteCmd(x|0x80);
		break;
	case 1:
		LCDWriteCmd((0x40+x)|0x80);
		break;
	}
//	LCDWriteCmd((0x20* y+x)|0x80);
}

void LCDPutChars(uint8_t *buff,uint8_t length)
{
	uint8_t i;
	for(i = 0;i<length;i++)
		LCDPutChar(buff[i]);
}

void LCDPutString(uint8_t* _buff)
{
	while(*_buff)
	{
		LCDPutChar(*_buff++);
	}
}
void LCDPutDecByte(uint8_t value)
{
	if (value < 100)
		LCDPutChar(' ');
	else
		LCDPutChar('0'+ value / 100);
	if (value <10)
		LCDPutChar(' ');
	else
		LCDPutChar(((value % 100) / 10) + '0');
	LCDPutChar(value % 10 + '0');
}
void LCDPutFloat(float _f)
{
	if (_f <= -0.1)
	{
		LCDPutChar('-');
		_f = -_f;
	}
	if (_f >= 1000)
	{
		LCDPutString((uint8_t*)"ERR"); //Not needed for temperature
		return;
	}
	else if (_f >= 100)
	{
		LCDPutChar('0' + (int)_f / 100);
		LCDPutChar('0' + ((int)_f % 100) / 10 );
	}
	else if (_f >= 10)
	{
			LCDPutChar('0' + (int)_f / 10 );
	}
	LCDPutChar('0' + (int)_f % 10);
	LCDPutChar('.');
	_f*=10;
	LCDPutChar('0' + (int)_f % 10);
}

void vTaskLCD(void *pvParameters)
{

	my_lcd_init();
	LCDPutString("MEN DELA - 987");

	while(1)
	{
		vTaskDelay (100/portTICK_RATE_MS);
	}
}

