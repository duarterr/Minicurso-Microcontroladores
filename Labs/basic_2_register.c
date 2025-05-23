/* -------------------------------------------------------------------------------------------------------------------- */
// Tiva C Blink with direct register access
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
#include "inc/tm4c123gh6pm.h"

/* -------------------------------------------------------------------------------------------------------------------- */
// Main function
/* -------------------------------------------------------------------------------------------------------------------- */

int main(void)
{
    volatile uint32_t ui32Loop;

    // Enable the GPIO port that is used for the on-board LED
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

    // Delay for a bit
    for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);

    // Enable the GPIO pin for the LED (PF1). Set the direction as output, and enable the GPIO pin for digital function
    GPIO_PORTF_DIR_R = 0b00000000000000000000000000000010;
    GPIO_PORTF_DEN_R = 0b00000000000000000000000000000010;

    // Loop forever
    while(1)
    {
        // Toggle the LED
        GPIO_PORTF_DATA_R ^= 0b00000000000000000000000000000010;

        // Delay for a bit
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++);
    }
}

/* -------------------------------------------------------------------------------------------------------------------- */
// End of code
/* -------------------------------------------------------------------------------------------------------------------- */
