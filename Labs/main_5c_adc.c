/* -------------------------------------------------------------------------------------------------------------------- */
// TivaC ADC project
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
#include "stdio.h"
#include "stdlib.h"

// TivaC hardware related libraries
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_timer.h"

// TivaC driver libraries
#include "driverlib/adc.h"
#include "driverlib/aes.h"
#include "driverlib/can.h"
#include "driverlib/comp.h"
#include "driverlib/crc.h"
#include "driverlib/des.h"
#include "driverlib/eeprom.h"
#include "driverlib/emac.h"
#include "driverlib/epi.h"
#include "driverlib/flash.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/hibernate.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "driverlib/lcd.h"
#include "driverlib/mpu.h"
#include "driverlib/onewire.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/qei.h"
#include "driverlib/rom.h"
#include "driverlib/shamd5.h"
#include "driverlib/ssi.h"
#include "driverlib/sw_crc.h"
#include "driverlib/sysctl.h"
#include "driverlib/sysexc.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "driverlib/usb.h"
#include "driverlib/watchdog.h"

/* -------------------------------------------------------------------------------------------------------------------- */
/* Definitions																											*/
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
/* Functions Prototypes																									*/
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
/* Variables																											*/
/* -------------------------------------------------------------------------------------------------------------------- */

// ADC conversion results
unsigned int 	AdcValue[8] = {0};

// ADC volts
float			AdcVolts[8] = {0};

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
    // Configure input pins
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Enable peripheral clock
	SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOE);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));

	// Configure PE3 as analog input - Channel 0
	GPIOPinTypeADC (GPIO_PORTE_BASE, GPIO_PIN_3);

	// Configure PE2 as analog input - Channel 1
	GPIOPinTypeADC (GPIO_PORTE_BASE, GPIO_PIN_2);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure ADC
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Enable peripheral clock
	SysCtlPeripheralEnable (SYSCTL_PERIPH_ADC0);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0));

	// Disable ADC0 sequence 0
	ADCSequenceDisable(ADC0_BASE, 0);

	// Configure ADC0 sequence 0
	ADCSequenceConfigure (ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);

	// Configure ADC0 sequence 0 steps - Channel 0 and 1
	ADCSequenceStepConfigure (ADC0_BASE, 0, 0, ADC_CTL_CH0);
	ADCSequenceStepConfigure (ADC0_BASE, 0, 1, ADC_CTL_CH0);
	ADCSequenceStepConfigure (ADC0_BASE, 0, 2, ADC_CTL_CH1);
	ADCSequenceStepConfigure (ADC0_BASE, 0, 3, ADC_CTL_CH1);
	ADCSequenceStepConfigure (ADC0_BASE, 0, 4, ADC_CTL_CH0);
	ADCSequenceStepConfigure (ADC0_BASE, 0, 5, ADC_CTL_CH0);
	ADCSequenceStepConfigure (ADC0_BASE, 0, 6, ADC_CTL_CH1);
	ADCSequenceStepConfigure (ADC0_BASE, 0, 7, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);

	// Configure hardware average - 2x, 4x, 8x, 16x, 32x or 64x
	ADCHardwareOversampleConfigure (ADC0_BASE, 32);	

	// Enable ADC0 sequence 0
	ADCSequenceEnable (ADC0_BASE, 0);

	// Clear the ADC0 sequence 0 interrupt flag
	ADCIntClear (ADC0_BASE, 0);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Main loop
    /* ---------------------------------------------------------------------------------------------------------------- */

	while (1)
	{
		// Trigger ADC0 sequence 0
		ADCProcessorTrigger (ADC0_BASE, 0);

		// Wait until the sample sequence has completed
		while (!ADCIntStatus (ADC0_BASE, 0, false));

		// Clear the ADC0 sequence 0 interrupt flag
		ADCIntClear (ADC0_BASE, 0);

		// Read ADC0 sequence 0 values
		ADCSequenceDataGet (ADC0_BASE, 0, AdcValue);

		// Convert result to volts
		AdcVolts[0] = AdcValue[0] * 3.3 / 4095;
		AdcVolts[1] = AdcValue[1] * 3.3 / 4095;
		AdcVolts[2] = AdcValue[2] * 3.3 / 4095;
		AdcVolts[3] = AdcValue[3] * 3.3 / 4095;
		AdcVolts[4] = AdcValue[4] * 3.3 / 4095;
		AdcVolts[5] = AdcValue[5] * 3.3 / 4095;
		AdcVolts[6] = AdcValue[6] * 3.3 / 4095;
		AdcVolts[7] = AdcValue[7] * 3.3 / 4095;

		// Delay
		SysCtlDelay (5000);
	}
}

/* -------------------------------------------------------------------------------------------------------------------- */
