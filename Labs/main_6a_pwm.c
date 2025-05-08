/* -------------------------------------------------------------------------------------------------------------------- */
// TivaC PWM project
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
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"

/* -------------------------------------------------------------------------------------------------------------------- */
/* Definitions																											*/
/* -------------------------------------------------------------------------------------------------------------------- */

// Frequency of the PWM
#define PWM_FREQUENCY	5000

/* -------------------------------------------------------------------------------------------------------------------- */
/* Functions Prototypes																									*/
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
/* Variables																											*/
/* -------------------------------------------------------------------------------------------------------------------- */

// CPU clock - Hz
unsigned long CpuClock = 0;

// Timer period - Clock ticks
unsigned long PwmPeriod = 0;

/* -------------------------------------------------------------------------------------------------------------------- */
/* Main function																										*/
/* -------------------------------------------------------------------------------------------------------------------- */

void main (void)
{
	/* ---------------------------------------------------------------------------------------------------------------- */
	// CPU settings
	/* ---------------------------------------------------------------------------------------------------------------- */

	// Configure clock - 80 MHz - 200 MHz (PLL) / 2.5
	SysCtlClockSet (SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    // Get CPU clock
	CpuClock = SysCtlClockGet();

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure output pins
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Enable peripheral clocks
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
	
	// Configure PF1 as PWM output
    GPIOPinTypePWM (GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinConfigure (GPIO_PF1_M1PWM5);
	
    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure PWM
    /* ---------------------------------------------------------------------------------------------------------------- */
	
    // Enable peripheral clocks
    SysCtlPeripheralEnable (SYSCTL_PERIPH_PWM1);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1));

	// Configure PWM Options
	PWMGenConfigure (PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_DBG_RUN);

	// Set the Period (expressed in clock ticks)
	PwmPeriod = (CpuClock/PWM_FREQUENCY) - 1;
	PWMGenPeriodSet (PWM1_BASE, PWM_GEN_2, PwmPeriod);

	// Set PWM duty
	PWMPulseWidthSet (PWM1_BASE, PWM_OUT_5, PwmPeriod / 2);

	// Turn on the output pins
	PWMOutputState (PWM1_BASE, PWM_OUT_5_BIT , true);

	// Enable the PWM generator
	PWMGenEnable (PWM1_BASE, PWM_GEN_2);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Main loop
    /* ---------------------------------------------------------------------------------------------------------------- */

	while (1)
	{
		// Change PWM duty
		PWMPulseWidthSet (PWM1_BASE, PWM_OUT_5, PwmPeriod / 10);

		// Delay
		SysCtlDelay (10000000);

		// Change PWM duty
		PWMPulseWidthSet (PWM1_BASE, PWM_OUT_5, PwmPeriod -10);

		// Delay
		SysCtlDelay (10000000);
	}
}

/* -------------------------------------------------------------------------------------------------------------------- */
