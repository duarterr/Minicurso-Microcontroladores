/* -------------------------------------------------------------------------------------------------------------------- */
// TivaC PWM project
/* -------------------------------------------------------------------------------------------------------------------- */
/*                                                                                                                      */
/* Author:      Renan R. Duarte                                                                                         */
/* Date:        22/06/2016                                                                                              */
/* Device:      CORTEX M4F TM4C123GH6PM Tiva C Launchpad                                                                */
/*                                                                                                                      */
/* -------------------------------------------------------------------------------------------------------------------- */
/*                                                                                                                      */
/* Predefined Symbols:                                                                                                  */
/*                                                                                                                      */
/*              PART_TM4C123GH6PM - To use pin_map.h                                                                    */
/*              TARGET_IS_TM4C129_RA0 - To use the include files in ROM of the Tiva device                              */
/*                                                                                                                      */
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
/* Includes                                                                                                             */
/* -------------------------------------------------------------------------------------------------------------------- */

// Standard libraries
#include <stdint.h>
#include <stdbool.h>
#include "stdlib.h"

// TivaC hardware related libraries
#include "inc/hw_memmap.h"

// TivaC driver libraries
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"

/* -------------------------------------------------------------------------------------------------------------------- */
/* Definitions                                                                                                          */
/* -------------------------------------------------------------------------------------------------------------------- */

// Frequency of the PWM
#define PWM_FREQUENCY   5000

/* -------------------------------------------------------------------------------------------------------------------- */
/* Functions Prototypes                                                                                                 */
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
/* Variables                                                                                                            */
/* -------------------------------------------------------------------------------------------------------------------- */

// CPU clock - Hz
unsigned long CpuClock = 0;

// Timer period - Clock ticks
unsigned long PwmPeriod = 0;

// Duty cycles - 0 to 1
float PwmDutyR = 0.5;
float PwmDutyG = 0.5;
float PwmDutyB = 0.5;

/* -------------------------------------------------------------------------------------------------------------------- */
/* Main function                                                                                                        */
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

    // Configure PF1, PF2 and PF3 as PWM outputs
    GPIOPinTypePWM (GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinConfigure (GPIO_PF1_M1PWM5);
    GPIOPinConfigure (GPIO_PF2_M1PWM6);
    GPIOPinConfigure (GPIO_PF3_M1PWM7);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure PWM
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Enable peripheral clocks
    SysCtlPeripheralEnable (SYSCTL_PERIPH_PWM1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1));

    // Configure PWM Options
    PWMGenConfigure (PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_DBG_RUN);
    PWMGenConfigure (PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_DBG_RUN);

    // Set the Period (expressed in clock ticks)
    PwmPeriod = (CpuClock/PWM_FREQUENCY) - 1;
    PWMGenPeriodSet (PWM1_BASE, PWM_GEN_2, PwmPeriod);
    PWMGenPeriodSet (PWM1_BASE, PWM_GEN_3, PwmPeriod);

    // Set PWM duty
    PWMPulseWidthSet (PWM1_BASE, PWM_OUT_5, PwmPeriod / 2); // Red
    PWMPulseWidthSet (PWM1_BASE, PWM_OUT_6, PwmPeriod / 2); // Blue
    PWMPulseWidthSet (PWM1_BASE, PWM_OUT_7, PwmPeriod / 2); // Green

    // Turn on the output pins
    PWMOutputState (PWM1_BASE, PWM_OUT_5_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);

    // Enable the PWM generator
    PWMGenEnable (PWM1_BASE, PWM_GEN_2);
    PWMGenEnable (PWM1_BASE, PWM_GEN_3);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Main loop
    /* ---------------------------------------------------------------------------------------------------------------- */

    while (1)
    {
        // Generate random duty cycles between 0 and 1
        PwmDutyR = (float)(rand() % 1001) / 1000.0;
        PwmDutyG = (float)(rand() % 1001) / 1000.0;
        PwmDutyB = (float)(rand() % 1001) / 1000.0;

        // Change PWM duty
        PWMPulseWidthSet (PWM1_BASE, PWM_OUT_5, PwmDutyR * PwmPeriod);
        PWMPulseWidthSet (PWM1_BASE, PWM_OUT_7, PwmDutyG * PwmPeriod);
        PWMPulseWidthSet (PWM1_BASE, PWM_OUT_6, PwmDutyB * PwmPeriod);

        // Delay
        SysCtlDelay (10000000);
    }
}

/* -------------------------------------------------------------------------------------------------------------------- */
