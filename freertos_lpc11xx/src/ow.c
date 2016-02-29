/*
 * ow.c
 *
 *  Created on: May 7, 2012
 *      Author: peterz
 */

#include "LPC11xx.h"

#include "FreeRTOS.h"
#include "task.h"

#include "small_gpio.h"
#include "debug.h"
#include "ow.h"



void ow_reset()		// procedura reset
{
	//OW_CLR(ow->grp,ow->number);
	// stan niski na linii 1wire
	//DelayUS(480); // op�nienie ok 480us
	//OW_SET(ow->grp,ow->number);
	// stan wysoki na linii 1wire
	//DelayUS(480); // op��nienie ok 480 us

	SetGPIOOut(3, 3);	//P3.3
	SetGPIOBit(3,3);
	vTaskDelay (480/portTICK_RATE_MS);

	ClrGPIOBit(3,3);
}


/*
 * Convert command to ds18b20. After this command You have to wait
 * approx 750ms until sensor finish converting of temperature to
 * discreet value.
 */

//void ds18b20Convert(struct PinDesc *ow)
void ds18b20Convert()
{
	ow_reset();
	//ow_write_byte(ow,0xCC);	//command is going to every sensor on the one-wire
	//ow_write_byte(ow,0x44);	//convert temperature
}


void vTaskOW(void *pvParameters)
{

	vTaskDelay (5000/portTICK_RATE_MS);

	LPC_IOCON->PIO3_3 = 0x000000C0;	/* disconnect build in pull-up on the 1wire pin */


	LCDGotoXY(0,0);	/* Put the cursor in first line, first character */
	LCDPutString("TEST LPC1114/301 and");

	LCDGotoXY(0,1);	/* Put the cursor in first line, first character */
	LCDPutString("LCD HD44780");

	ds18b20Convert();

	while(1)
	{
		vTaskDelay (100/portTICK_RATE_MS);
	}

}
