/* -------------------------------------------------------------------------------------------------------------------- */
// Tiva C clock settings
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

// TivaC driver libraries
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

// CPU clock value
unsigned long CpuClock = 0;

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
    // Set variables
    /* ---------------------------------------------------------------------------------------------------------------- */

	// Get CPU clock
	CpuClock = SysCtlClockGet();

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Main loop
    /* ---------------------------------------------------------------------------------------------------------------- */

	while (1);
}

/* -------------------------------------------------------------------------------------------------------------------- */