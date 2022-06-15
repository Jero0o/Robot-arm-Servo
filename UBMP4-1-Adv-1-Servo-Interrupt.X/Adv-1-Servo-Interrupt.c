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
unsigned char servo2_pos = 128;
unsigned char servo3_pos = 0;
unsigned char servo4_pos = 0;
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
            servo_pulse(SERVO2, servo2_pos);
            servo_pulse(SERVO3, servo3_pos);
            servo_pulse(SERVO4, servo4_pos);
        }
	}
}

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
    
    // Servo output pin configuration
    TRISC = 0b11110000;         // Set H1 as output for Servo1
	
    while(1)
	{
        // Pulse timing test code
//        servo_pulse(SERVO1,servo1Pos);
        
        // Read pushbuttons and adjust servo position
        if(SW3 == 0 && servo1_pos > 0)
        {
            servo1_pos --;
        }
        
        if(SW2 == 0 && servo1_pos < 255)
        {
            servo1_pos ++;
        }

        if(SW5 == 0 && servo2_pos > 0)
        {
            servo2_pos --;
        }

        if(SW4 == 0 && servo2_pos < 255)
        {
            servo2_pos ++;
        } 
        
        if(H6IN == 1 && servo3_pos > 0)   //these pins increment fast, add a delay after the delay to make it slow.
        {
            servo3_pos ++;
        }

        if(H5IN == 1 && servo3_pos < 255)
        {
            servo3_pos --;
        }

        if(H8IN == 1 && servo4_pos > 0)
        {
            servo4_pos ++;
        }

        if(H7IN == 1 && servo4_pos < 255)
        {
            servo4_pos --;
        }

//        // Delay between servo pulses
//        __delay_ms(15);
        
        // Delay between pushbutton updates
        __delay_ms(4);

        __delay_ms(10);
        
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
 //H2OUT = 0
//H1OUT = 0