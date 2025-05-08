/* -------------------------------------------------------------------------------------------------------------------- */
// TivaC GPIO project
/* -------------------------------------------------------------------------------------------------------------------- */
/*																														*/
/* Author: 		Renan R. Duarte																							*/
/* Date: 		22/06/2016																								*/
/* Device:		CORTEX M4F TM4C123GH6PM	Tiva C Launchpad																*/
/*																														*/
/* -------------------------------------------------------------------------------------------------------------------- */
/*																														*/
/* Predefined Symbols:																									*/
/*																														*/
/* 				PART_TM4C123GH6PM - To use pin_map.h																	*/
/* 				TARGET_IS_TM4C129_RA0 - To use the include files in ROM of the Tiva device								*/
/*																														*/
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
/* Includes																												*/
/* -------------------------------------------------------------------------------------------------------------------- */

// Standard libraries
#include <stdint.h>
#include <stdbool.h>

// TivaC hardware related libraries
#include "inc/hw_memmap.h"

// TivaC driver libraries
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

/* -------------------------------------------------------------------------------------------------------------------- */
/* Definitions																											*/
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
/* Functions Prototypes																									*/
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
/* Variables																											*/
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
/* Main function																										*/
/* -------------------------------------------------------------------------------------------------------------------- */

void main (void)
{
	/* ---------------------------------------------------------------------------------------------------------------- */
	// CPU settings
	/* ---------------------------------------------------------------------------------------------------------------- */

	// Configure clock - 80 MHz - 200 MHz (PLL) / 2.5
	SysCtlClockSet (SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_2_5);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure output pins
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Enable peripheral clock
	SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

	// Configure pins as outputs
	GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

	// Configure pins - 8mA drive with slew rate control and push-pull mode
	GPIOPadConfigSet (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);

	// Set output state - Off
	GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure input pins
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Enable peripheral clock - Not necessary as we already did for the outputs
    // SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	// while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

	// Unlock used pins (has no effect if pin is not protected by the GPIOCR register
	GPIOUnlockPin(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

	// Configure pins as input
	GPIOPinTypeGPIOInput (GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

	// Enable pull-up resistor
	GPIOPadConfigSet (GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Main loop
    /* ---------------------------------------------------------------------------------------------------------------- */

	while (1)
	{
		// Read GPIOF0
		if (GPIOPinRead (GPIO_PORTF_BASE, GPIO_PIN_0) == 0)
		{
			// Set output state - On
			GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0xFF);
		}

		// Read GPIOF4
		else if (GPIOPinRead (GPIO_PORTF_BASE, GPIO_PIN_4) == 0)
		{
			// Set output state - Off
			GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
		}
	}
}

/* -------------------------------------------------------------------------------------------------------------------- */
