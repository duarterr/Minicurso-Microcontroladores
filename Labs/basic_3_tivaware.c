/* -------------------------------------------------------------------------------------------------------------------- */
// Tiva C Blink with TivaWare API calls
/* -------------------------------------------------------------------------------------------------------------------- */
/*                                                                                                                      */
/* Author:      Renan R. Duarte                                                                                         */
/* Date:        22/11/2023                                                                                              */
/* Device:      CORTEX M4F TM4C123GH6PM Tiva C Launchpad                                                                */
/*                                                                                                                      */
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
// Includes
/* -------------------------------------------------------------------------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

/* -------------------------------------------------------------------------------------------------------------------- */
// Main function
/* -------------------------------------------------------------------------------------------------------------------- */

int main(void)
{
    // Enable the GPIO port that is used for the on-board LED
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF);

    // Delay for a bit
    SysCtlDelay (200000);

    // Enable the GPIO pin for the LED (PF1). Set the direction as output, and enable the GPIO pin for digital function
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_1);

    // Loop forever
    while(1)
    {
        // Turn on the LED
        GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1, 0xFF);

        // Delay for a bit
        SysCtlDelay (200000);

        // Turn off the LED
        GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);

        // Delay for a bit
        SysCtlDelay (200000);
    }
}

/* -------------------------------------------------------------------------------------------------------------------- */
// End of code
/* -------------------------------------------------------------------------------------------------------------------- */
