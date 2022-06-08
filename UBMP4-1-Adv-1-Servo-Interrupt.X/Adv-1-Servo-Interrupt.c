/*==============================================================================
 Project: Adv-1-Servo-Interrupt
 Date:    April 8, 2022
 
 This program implements an included servo output function and demonstrates the 
 use of an interrupt function for background servo pulse generation.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP410.h"         // Include UBMP4.1 constant and function definitions
#include    "Servo.h"           // Include servo function definitions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Program variable definitions
unsigned char servo1_pos = 128; // Servo 1 position variable
unsigned char timerPeriods = 3; // Interrupt timer periods counter (x5ms)

// Servo interrupt function using TMR0 to count 5ms intervals and generate 
// a new servo pulse every 15ms.
void __interrupt() servo(void)
{
	if(TMR0IF == 1 && TMR0IE == 1)	// Validate Timer 0 interrupt
	{
        TMR0IF = 0;				// Clear Timer 0 interrupt flag
        TMR0 = 21;              // Pre-set TMR0 for next 5ms period interval
        timerPeriods --;        // Count down 5ms timer periods
        if(timerPeriods == 0)
        {
            timerPeriods = 3;   // Reset timer period to 15ms servo pulse period
            servo_pulse(SERVO1, servo1_pos);    // Update servo1 position
        }
	}
}

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
    
    // Servo output pin configuration
    TRISC = 0b00001110;         // Set H1 as output for Servo1
	
    while(1)
	{
        // Pulse timing test code
//        servo_pulse(SERVO1,servo1Pos);
        
        // Read pushbuttons and adjust servo position
        if(SW5 == 0 && servo1_pos > 0)
        {
            servo1_pos --;
        }
        
        if(SW4 == 0 && servo1_pos < 255)
        {
            servo1_pos ++;
        }
        
//        // Delay between servo pulses
//        __delay_ms(15);
        
        // Delay between pushbutton updates
        __delay_ms(4);
        
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

/* Learn More - Program Analysis Activities
 * 
 * 1. 
 */