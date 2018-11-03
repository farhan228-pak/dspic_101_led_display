/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
#include <xc.h>
#elif defined(__C30__)
#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif
#endif

#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */


/******************************************************************************/
/* User Functions                                                             */

/******************************************************************************/
volatile unsigned int pulse_count = 0;
volatile int frequency = 2;
int Pulse = 40;
int Period = 100;
bool PowerOn=false;
/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitPins() {
    /* Initialize peripherals */
    //Frequency Select LEDs
    _TRISB0 = 0;
    _TRISB1 = 0;
    _TRISB2 = 0;
    _TRISB3 = 0;
     _TRISB4 = 0;
      _TRISB5 = 0;
       _TRISB6 = 0;
        _TRISB7 = 0;
    
    
    _TRISA0 = 0;
    _TRISA1 = 0;
    _TRISA2 = 0;
    _TRISA3 = 1;
    _TRISB15 = 1;
}

void InitTimers() {
    /* The following code example will enable Timer1 interrupts, load the Timer1
       Period register and start Timer1.
       When a Timer1 period match interrupt occurs, the interrupt service
       routine must clear the Timer1 interrupt status flag in software.  */
    //Initialize Timer 1
    /*
    T1CON = 0x00; //Stops the Timer1 and reset control reg.
    TMR1 = 0x00; //Clear contents of the timer register
    PR1 = 0xFFFF; //Fosc/2000UL  	//Load the Period register with 1mSec counter
    IPC0bits.T1IP = 0x01; //Setup Timer1 interrupt for desired priority level
    // (This example assigns level 1 priority)
    IFS0bits.T1IF = 0; //Clear the Timer1 interrupt status flag
    IEC0bits.T1IE = 1; //Enable Timer1 interrupts
    T1CONbits.TON = 1; //Start Timer1 with prescaler settings at 1:1 and
    //clock source set to the internal instruction cycle

    /**************************************************************/
    /*
    T2CON = 0x00; //Stops the Timer1 and reset control reg.
    TMR2 = 0x00; //Clear contents of the timer register
    PR2 = 1; //Fosc/2000UL  	//Load the Period register with 1mSec counter
    IPC1bits.T2IP = 0x02; //Setup Timer1 interrupt for desired priority level
    // (This example assigns level 1 priority)
    IFS0bits.T2IF = 0; //Clear the Timer1 interrupt status flag
    IEC0bits.T2IE = 0; //Enable Timer1 interrupts
    T2CONbits.TON = 0; //Start Timer1 with prescaler settings at 1:1 and
    //clock source set to the internal instruction cycle
    */
}




