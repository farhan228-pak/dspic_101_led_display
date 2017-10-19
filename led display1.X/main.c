/*
 * File:   main.c
 * Author: farala
 *
 * Created on October 16, 2017, 1:38 PM
 */

//void initClock(void);
//#include "xc.h"
#include "config_bits.h"
#include "stdio.h"
#include "user.h"
#include <libpic30.h>
//#define FYC 40000000



int main(void) {
    //initClock();
    InitPins();
  while(1)
  {
   //int x;
   //float f;
   //f=x;
   LEDb5=1;
   LATB=0x00;
 //__delay_ms(10);
   LEDb5=0;
  // __delay_ms(10);
  }
    return 0;
}


void initClock(void)
{
	/* Configure Oscillator to operate the device at 40Mhz
	   Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
 	   Fosc= 7.37*(43)/(2*2)=80Mhz for Fosc, Fcy = 40Mhz */

	/* Configure PLL prescaler, PLL postscaler, PLL divisor */
	PLLFBD=41; 				/* M = PLLFBD + 2 */
	CLKDIVbits.PLLPOST=0;   /* N1 = 2 */
	CLKDIVbits.PLLPRE=0;    /* N2 = 2 */

	//__builtin_write_OSCCONL(0x20);
	//__builtin_write_OSCCONH(0x01);			/* New Oscillator FRC w/ PLL */
   // __builtin_write_OSCCONL(0x01);  		/* Enable Switch */

	while(OSCCONbits.COSC != 0b001);		/* Wait for new Oscillator to become FRC w/ PLL */ 	

    while(OSCCONbits.LOCK != 0b1);			/* Wait for Pll to Lock */

	/* Now setup the ADC and PWM clock for 120MHz
	   ((FRC * 16) / APSTSCLR ) = (7.37 * 16) / 1 = ~ 120MHz*/

	ACLKCONbits.ASRCSEL = 1;				/* FRC provides input for Auxiliary PLL (x16) */
	ACLKCONbits.FRCSEL = 1;
	ACLKCONbits.SELACLK = 1;				/* Auxiliary Oscillator provides clock source for PWM & ADC */
	ACLKCONbits.APSTSCLR = 7;				/* Divide Auxiliary clock by 1 */
	ACLKCONbits.ENAPLL = 1;					/* Enable Auxiliary PLL */

	while(ACLKCONbits.APLLCK != 1);			/* Wait for Auxiliary PLL to Lock */

    
}