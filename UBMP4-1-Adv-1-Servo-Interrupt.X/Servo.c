/*==============================================================================
 Library: Servo
 Date: April 8, 2022
 
 Servo function to generate servo pulses on UBMP headers H1 - H8. The servo
 pulses generated by this function are 1-2ms typical of 90 degree hobby servos.
 Modify the code for other servo timings by changing the fixed and variable
 code delays.
 
 Before using the servo function, ensure that each servo header pin is set as
 a digital output by modifying the UBMP4_config() function in UBMP4.c or by 
 adding your own PORTC configuration code.
 
 Analog hobby servos require servo pulses to be received every 15-20ms. Ensure
 your main loop repeatedly transmits servo pulses at this rate, or use a timer
 interrupt and interrupt service routine to implement consistent pulse timing.
 =============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP410.h"         // Include UBMP4 constants and functions
#include    "Servo.h"           // Include UBMP4 servo definitions

// Create a servo pulse on the specified output (SERVO1 - 8), for a duration
// corresponding to the position value. Ensure PORTC servo pins are previously
// set as digital outputs.
void servo_pulse(unsigned char servo, unsigned char position)
{
    PORTC = PORTC | servo;      // Set servo pin high and make fixed delay
    __delay_us(984);            // (change this value for 180 degree servos) (try a range from 2000)
    for(position; position != 0; position--)   // Extend delay by position value
    {
        _delay(38);             // Clock cycle delay to make 1ms pulse (pos = 255)
    }                           // (change clock delay to modify pulse)
    PORTC = PORTC & (!servo);   // End pulse by resetting servo pin
}

void servo_pulseHS322HD(unsigned char servo, unsigned char position)
{
    PORTC = PORTC | servo;      // Set servo pin high and make fixed delay
    __delay_us(50);            // (change this value for 180 degree servos) (try a range from 2000)
    for(position; position != 0; position--)   // Extend delay by position value
    {
        _delay(90);             // Clock cycle delay to make 1ms pulse (pos = 255)
    }                           // (change clock delay to modify pulse)
    PORTC = PORTC & (!servo);   // End pulse by resetting servo pin
}

void servo_pulseMG995(unsigned char servo, unsigned char position)
{
    PORTC = PORTC | servo;      // Set servo pin high and make fixed delay
    __delay_us(650);            // (change this value for 180 degree servos) (try a range from 2000)
    for(position; position != 0; position--)   // Extend delay by position value
    {
        _delay(90);             // Clock cycle delay to make 1ms pulse (pos = 255)
    }                           // (change clock delay to modify pulse)
    PORTC = PORTC & (!servo);   // End pulse by resetting servo pin
}

void servo_pulseParallax(unsigned char servo, unsigned char position)
{
    PORTC = PORTC | servo;      // Set servo pin high and make fixed delay
    __delay_us(650);            // (change this value for 180 degree servos) (try a range from 2000)
    for(position; position != 0; position--)   // Extend delay by position value
    {
        _delay(90);             // Clock cycle delay to make 1ms pulse (pos = 255)
    }                           // (change clock delay to modify pulse)
    PORTC = PORTC & (!servo);   // End pulse by resetting servo pin
}

void servo_pulseMG9951(unsigned char servo, unsigned char position) //Change delays to make it behave differently
{
    PORTC = PORTC | servo;      // Set servo pin high and make fixed delay
    __delay_us(984);            // (change this value for 180 degree servos) (try a range from 2000)
    for(position; position != 0; position--)   // Extend delay by position value
    {
        _delay(45);             // Clock cycle delay to make 1ms pulse (pos = 255)
    }                           // (change clock delay to modify pulse)
    PORTC = PORTC & (!servo);   // End pulse by resetting servo pin
}