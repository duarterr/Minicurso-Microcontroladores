/* -------------------------------------------------------------------------------------------------------------------- */
// Tiva C Timer project
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
#include "driverlib/timer.h"

/* -------------------------------------------------------------------------------------------------------------------- */
/* Definitions																											*/
/* -------------------------------------------------------------------------------------------------------------------- */

#define TIMER_FREQUENCY 	1221

/* -------------------------------------------------------------------------------------------------------------------- */
/* Functions Prototypes																									*/
/* -------------------------------------------------------------------------------------------------------------------- */

// Timer interrupt handler
void Timer_Int_Handler (void);

/* -------------------------------------------------------------------------------------------------------------------- */
/* Variables																											*/
/* -------------------------------------------------------------------------------------------------------------------- */

// CPU clock - Hz
unsigned long CpuClock = 0;

// Timer period - Clock ticks
unsigned long TimerPeriod = 0;

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

    // Get CPU clock
	CpuClock = SysCtlClockGet();
	
    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure output pins
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Enable peripheral clock
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

	// Configure pins as outputs
	GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2);

	// Set output state - Off
	GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2, 0x00);

	/* ---------------------------------------------------------------------------------------------------------------- */
    // Configure timer
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Enable peripheral clock
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));

	// Configure timer mode
	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);

	// Set timer period
	TimerPeriod = (CpuClock/TIMER_FREQUENCY) - 1;
	TimerLoadSet(TIMER0_BASE, TIMER_A, TimerPeriod);

	// Enable interrupt on timer timeout
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	IntEnable(INT_TIMER0A);

	// Register interrupt handler
	TimerIntRegister (TIMER0_BASE, TIMER_A, Timer_Int_Handler);

	// Start timer
	TimerEnable(TIMER0_BASE, TIMER_A);

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
// Timer interrupt handler
/* -------------------------------------------------------------------------------------------------------------------- */

void Timer_Int_Handler (void)
{
    // Invert LED
    if (GPIOPinRead (GPIO_PORTF_BASE, GPIO_PIN_1) == 0x00)
        GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1, 0xFF);
    else
        GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);

    // Clear interrupt flag
    TimerIntClear (TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

/* -------------------------------------------------------------------------------------------------------------------- */
