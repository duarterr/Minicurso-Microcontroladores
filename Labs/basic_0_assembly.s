; -------------------------------------------------------------------------------------------------------------------- ;
; Tiva C Blink
; -------------------------------------------------------------------------------------------------------------------- ;
;                                                                                                                      ;
; Author:      Renan R. Duarte                                                                                         ;
; Date:        22/11/2023                                                                                              ;
; Device:      CORTEX M4F TM4C123GH6PM Tiva C Launchpad                                                                ;
;                                                                                                                      ;
; -------------------------------------------------------------------------------------------------------------------- ;

	.def main
	.sect .text

	.align 4
SYSCTL_RCGC2_R:   .bits   0x400FE108, 32    ; Address of the System Control: Run-Mode Clock Gating Control 2 register

	.align 4
GPIO_PORTF_DIR_R: .bits   0x40025400, 32    ; Address of the GPIO Port F Data Direction register

	.align 4
GPIO_PORTF_DEN_R: .bits   0x4002551C, 32    ; Address of the GPIO Port F Digital Enable register

	.align 4
GPIO_PORTF_DATA_R: .bits  0x400253FC, 32    ; Address of the GPIO Port F Data register

	.align 4
Delay: .bits 0x30D40, 32                    ; Delay value (4x + 1 cycle)

; -------------------------------------------------------------------------------------------------------------------- ;
; Main function
; -------------------------------------------------------------------------------------------------------------------- ;

	.global main

main:
	; Enable the GPIO port that is used for the on-board LED
    LDR R1, SYSCTL_RCGC2_R   	; Load the address of the System Control: Run-Mode Clock Gating Control 2 register into R1
    MOVS R0, #32             	; Move the value 32 into R0 (enable GPIO Port F)
    STR R0, [R1]             	; Store the value in R0 into the address pointed by R1 (enable clock to GPIO Port F)

	; Delay for a bit
    LDR R0, Delay             	; Load the initial delay value into R0
delay_startup:
    SUBS R0, R0, #1           	; Subtract 1 from R0
    CMP R0, #0                	; Compare the result with 0
    BNE delay_startup         	; Branch back to delay_startup if R0 is not zero

	; Set the direction of PF1 as output
    LDR R1, GPIO_PORTF_DIR_R  	; Load the address of the GPIO Port F Data Direction register into R1
    MOVS R0, #2               	; Move the value 2 into R0 (configure pins as output)
    STR R0, [R1, #0]           	; Store the value in R0 into the address pointed by R1 (set pins as output)

	; Enable PF0 GPIO pin for digital function
    LDR R1, GPIO_PORTF_DEN_R  	; Load the address of the GPIO Port F Digital Enable register into R1
    MOVS R0, #2               	; Move the value 2 into R0 (enable digital functionality)
    STR R0, [R1, #0]           	; Store the value in R0 into the address pointed by R1 (enable digital functionality)

	; Loop forever
while_loop:
	; Toggle the LED
    LDR R1, GPIO_PORTF_DATA_R 	; Load the address of the GPIO Port F Data register into R1
    LDR R0, [R1, #0]           	; Load the value from the address pointed by R1 into R0
    EOR R0, R0, #2            	; Toggle bit 1 of the GPIO Port F Data register
    STR R0, [R1, #0]           	; Store the modified value back into the address pointed by R1

	; Delay for a bit
    LDR R0, Delay              	; Load the delay value into R0 (2 cycles)
delay_loop:
    SUBS R0, R0, #1           	; Subtract 1 from R0 (1 cycle)
    CMP R0, #0                	; Compare the result with 0 (1 cycle)
    BNE delay_loop            	; Branch back to delay_loop if R0 is not zero (1 cycle)

    B while_loop              	; Branch back to while_loop (infinite loop)

; -------------------------------------------------------------------------------------------------------------------- ;
; End of code
; -------------------------------------------------------------------------------------------------------------------- ;

    BX LR                      	; Branch and Exchange - return from the function - Unreachable
