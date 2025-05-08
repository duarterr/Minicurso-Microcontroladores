/* -------------------------------------------------------------------------------------------------------------------- */
// TivaC Interrupt project
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
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

// TivaC driver libraries
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"

/* -------------------------------------------------------------------------------------------------------------------- */
/* Definitions																											*/
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
/* Functions Prototypes																									*/
/* -------------------------------------------------------------------------------------------------------------------- */

// GPIOF interrupt handler
void GPIOF_Int_Handler (void);

/* -------------------------------------------------------------------------------------------------------------------- */
/* Variables																											*/
/* -------------------------------------------------------------------------------------------------------------------- */

// Counter
volatile long IntCounter = 0;

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
	GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2);

	// Configure pins - 8mA drive with slew rate control and push-pull mode
	GPIOPadConfigSet (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);

	// Set output state - Off
	GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0x00);

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

	// Interrupt trigger on falling edge
	GPIOIntTypeSet (GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_FALLING_EDGE);

	// Register interrupt handler
	GPIOIntRegister(GPIO_PORTF_BASE, GPIOF_Int_Handler);

	// Enable interrupt on PF0 and PF4
	GPIOIntEnable (GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

	// Enable peripheral interrupt
	IntEnable (INT_GPIOF);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Enable interrupts at a global level
    /* ---------------------------------------------------------------------------------------------------------------- */

	// Enable CPU interrupts
	IntMasterEnable ();

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Main loop
    /* ---------------------------------------------------------------------------------------------------------------- */

	while (1);
}

/* -------------------------------------------------------------------------------------------------------------------- */
// GPIOF interrupt handler
/* -------------------------------------------------------------------------------------------------------------------- */

void GPIOF_Int_Handler (void)
{
	// Variables
	unsigned long IntStatus;

	// Increase interrupt counter
	IntCounter++;

	// Get the interrupt status
	IntStatus = GPIOIntStatus (GPIO_PORTF_BASE, true);

	if (IntStatus == GPIO_PIN_0)
	{
		// Set output state - On
		GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0xFF);
	}

	else if (IntStatus == GPIO_PIN_4)
	{
		// Set output state - Off
		GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0x00);
	}

	// Clear the asserted interrupts
	GPIOIntClear (GPIO_PORTF_BASE, IntStatus);
}

/* -------------------------------------------------------------------------------------------------------------------- */
