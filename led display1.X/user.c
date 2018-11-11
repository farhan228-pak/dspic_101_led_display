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
volatile unsigned int timePeriod=0;
volatile int frequency = 2;
int Pulse = 40;
int Period = 100;
bool PowerOn=false;
uint16_t t1,t2,t3,t4;
uint8_t first=0;
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
    _TRISB14=1;
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
    
    T2CON = 0x00; //Stops the Timer1 and reset control reg.
    TMR2 = 0x00; //Clear contents of the timer register
    T2CONbits.TCKPS = 0b11;
    PR2 = 65530; //Fosc/2000UL  	//Load the Period register with 1mSec counter
    //IPC1bits.T2IP = 0x02; //Setup Timer1 interrupt for desired priority level
    // (This example assigns level 1 priority)
    //IFS0bits.T2IF = 0; //Clear the Timer1 interrupt status flag
    //IEC0bits.T2IE = 0; //Enable Timer1 interrupts
    T2CONbits.TON = 0; //Start Timer1 with prescaler settings at 1:1 and
    //clock source set to the internal instruction cycle
    
}

void init_timer()
{
T1CONbits.TON = 0; // Disable Timer
T1CONbits.TCS = 0; // Select internal instruction cycle clock
T1CONbits.TGATE = 1; // Enable Gated Timer mode
T1CONbits.TCKPS = 0b11; // Select 1:1 Prescaler
TMR1 = 0x00; // Clear timer register
PR1 = 65535; // Load the period value
IPC0bits.T1IP = 0x01; // Set Timer1 Interrupt Priority Level
IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
IEC0bits.T1IE = 1; // Enable Timer1 interrupt
T1CONbits.TON = 1; // Start Timer
/* Example code for Timer1 ISR */
}
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
/* Interrupt Service Routine code goes here */
//LATAbits.LATA2=!LATAbits.LATA2;
    LATAbits.LATA2=1;
    if (first == 0) {
         T2CONbits.TON = 1;
       // t1 = TMR1;
        first = 1;

    }        //unsigned int t1,t2;
    else if(first == 1) {
         T2CONbits.TON = 0;
        //if (first == 1) {
           // t2 = TMR1;

            //if (t2 > t1) {
               // timePeriod = t2 - t1+TMR2;
                timePeriod = TMR2;

            //}
            //if (t1 > t2) {
                //timePeriod = t1 - t2+TMR2;
            timePeriod = TMR2;
            //}
            first = 0;
            IEC0bits.T1IE = 0;
        //}
        T1CONbits.TON = 0; // Start Timer
        TMR1 = 0x00; // Clear timer register
     T2CONbits.TON = 0; // Start Timer
     TMR2=0;
    
    }
    

IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
LATAbits.LATA2=0;


}

