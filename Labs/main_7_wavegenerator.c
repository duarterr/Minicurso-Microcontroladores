/* -------------------------------------------------------------------------------------------------------------------- */
// Tiva C PWM DA example - Change Waveform variable in debugger to change the waveform
/* -------------------------------------------------------------------------------------------------------------------- */
/*                                                                                                                      */
/* Author:      Renan R. Duarte                                                                                         */
/* Date:        23/11/2023                                                                                              */
/* Device:      CORTEX M4F TM4C123GH6PM Tiva C Launchpad                                                                */
/*                                                                                                                      */
/* -------------------------------------------------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------------------------------------------------- */
// Includes
/* -------------------------------------------------------------------------------------------------------------------- */

// Standard libraries
#include <stdint.h>
#include <stdbool.h>
#include "math.h"

// TivaC hardware related libraries
#include "inc/hw_memmap.h"

// TivaC driver libraries
#include "driverlib/adc.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

/* -------------------------------------------------------------------------------------------------------------------- */
/* Definitions                                                                                                          */
/* -------------------------------------------------------------------------------------------------------------------- */

// Frequency of the PWM
#define PWM_FREQUENCY       312500

// Frequency of the sample timer
#define SAMPLE_FREQUENCY    1000

// Waveform frequency limits
#define WAVE_FREQUENCY_MIN  10
#define WAVE_FREQUENCY_MAX  100

// Possible waveforms
typedef enum
{
    Sawtooth,
    Square,
    Sine,
    RectifiedSine
} waveform_t;

/* -------------------------------------------------------------------------------------------------------------------- */
/* Functions Prototypes                                                                                                 */
/* -------------------------------------------------------------------------------------------------------------------- */

// Systick interrupt handler
void SysTickIsr (void);

/* -------------------------------------------------------------------------------------------------------------------- */
/* Variables                                                                                                            */
/* -------------------------------------------------------------------------------------------------------------------- */

// Frequency of the output waveform
volatile unsigned int WaveformFrequency = WAVE_FREQUENCY_MAX;

// PWM period (clock ticks)
unsigned int PwmPeriod = 0;

// Sample counter (0 to SAMPLE_FREQUENCY/WaveformFrequency)
volatile unsigned int SampleCounter = 0;

// Sample value
volatile unsigned int SampleValue = 0;

// Waveform
volatile waveform_t Waveform = Sawtooth;

// ADC conversion result
unsigned int    AdcValue = 0;

/* -------------------------------------------------------------------------------------------------------------------- */
// Main function
/* -------------------------------------------------------------------------------------------------------------------- */

int main(void)
{
    /* ---------------------------------------------------------------------------------------------------------------- */
    // CPU settings
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Configure clock - 80 MHz - 200 MHz (PLL) / 2.5
    SysCtlClockSet (SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    // Enable CPU interrupts
    IntMasterEnable ();

    // Enable FPU - Is already enabled by default
    FPULazyStackingEnable();
    FPUEnable();

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure input pins
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Enable peripheral clock
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));

    // Configure PE3 as analog input - Channel 0
    GPIOPinTypeADC (GPIO_PORTE_BASE, GPIO_PIN_3);

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

    // Configure ADC0 sequence 0 steps - Channel 0
    ADCSequenceStepConfigure (ADC0_BASE, 0, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);

    // Configure hardware average - 2x, 4x, 8x, 16x, 32x or 64x
    ADCHardwareOversampleConfigure (ADC0_BASE, 32);

    // Enable ADC0 sequence 0
    ADCSequenceEnable (ADC0_BASE, 0);

    // Clear the ADC0 sequence 0 interrupt flag
    ADCIntClear (ADC0_BASE, 0);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure output pins
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Enable peripheral clocks
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    //Configure PF1 as PWM output
    GPIOPinTypePWM (GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinConfigure (GPIO_PF1_M1PWM5);

    // Configure PF2 as output - Used as a trigger source for the oscilloscope
    GPIOPinTypeGPIOOutput (GPIO_PORTF_BASE, GPIO_PIN_2);

    // Set output state - Off
    GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure PWM
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Calculate PwmPeriod
    PwmPeriod = (SysCtlClockGet () / PWM_FREQUENCY) - 1;

    // Enable peripheral clock
    SysCtlPeripheralEnable (SYSCTL_PERIPH_PWM1);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1));

    // Configure PWM Options
    PWMGenConfigure (PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_DBG_RUN);

    // Set the Period (expressed in clock ticks)
    PWMGenPeriodSet (PWM1_BASE, PWM_GEN_2, PwmPeriod);

    // Set PWM duty
    PWMPulseWidthSet (PWM1_BASE, PWM_OUT_5, 0);

    // Turn on the output pins
    PWMOutputState (PWM1_BASE, PWM_OUT_5_BIT , true);

    // Enable the PWM generator
    PWMGenEnable (PWM1_BASE, PWM_GEN_2);

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Configure Systick timer
    /* ---------------------------------------------------------------------------------------------------------------- */

    // Set timer period
    SysTickPeriodSet ((SysCtlClockGet()/SAMPLE_FREQUENCY) - 1);

    // Register interrupt handler
    SysTickIntRegister (SysTickIsr);

    // Enable timer interrupt
    SysTickIntEnable ();

    // Start timer
    SysTickEnable ();

    /* ---------------------------------------------------------------------------------------------------------------- */
    // Main loop
    /* ---------------------------------------------------------------------------------------------------------------- */

    while (1);
}

/* -------------------------------------------------------------------------------------------------------------------- */
// Systick interrupt handler
/* -------------------------------------------------------------------------------------------------------------------- */

void SysTickIsr (void)
{
    // Turn PF2 on
    GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_2, 0xFF);

    /* ---------------------------------------------------------------------------------------------------------------- */

    // Trigger ADC0 sequence 0
    ADCProcessorTrigger (ADC0_BASE, 0);

    // Wait until the sample sequence has completed
    while (!ADCIntStatus (ADC0_BASE, 0, false));

    // Clear the ADC0 sequence 0 interrupt flag
    ADCIntClear (ADC0_BASE, 0);

    // Read ADC0 sequence 0 value
    ADCSequenceDataGet (ADC0_BASE, 0, &AdcValue);

    // Calculate WaveformFrequency
    WaveformFrequency = WAVE_FREQUENCY_MIN + ((AdcValue * (WAVE_FREQUENCY_MAX - WAVE_FREQUENCY_MIN)) / 4095);

    /* ---------------------------------------------------------------------------------------------------------------- */

    // Define new sample value - Sawtooth waveform
    if (Waveform == Sawtooth)
        SampleValue = 1 + SampleCounter*((float)PwmPeriod/(SAMPLE_FREQUENCY/WaveformFrequency - 1));

    // Define new sample value - Square waveform
    else if (Waveform == Square)
    {
        if (SampleCounter == 0)
            SampleValue = 1;
        else if (SampleCounter == (SAMPLE_FREQUENCY/(2*WaveformFrequency)))
            SampleValue = PwmPeriod;
    }

    // Define new sample value - Sine waveform - Offset of PwmPeriod/2 + 1
    else if (Waveform == Sine)
        SampleValue = 1 + PwmPeriod/2 + (PwmPeriod/2)*(float)sin(6.28318530718*WaveformFrequency*SampleCounter/SAMPLE_FREQUENCY);

    // Define new sample value - Rectified sine waveform - Offset of PwmPeriod/2 + 1
    else if (Waveform == RectifiedSine)
        SampleValue = 1 + abs(PwmPeriod*(float)sin(6.28318530718*WaveformFrequency*SampleCounter/SAMPLE_FREQUENCY));

    // Change PWM duty
    PWMPulseWidthSet (PWM1_BASE, PWM_OUT_5, SampleValue);

    // Increase sample counter
    SampleCounter++;
    if (SampleCounter >= (SAMPLE_FREQUENCY/WaveformFrequency))
        SampleCounter = 0;

    /* ---------------------------------------------------------------------------------------------------------------- */

    // Turn PF2 off
    GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
}

/* -------------------------------------------------------------------------------------------------------------------- */
// End of code
/* -------------------------------------------------------------------------------------------------------------------- */
