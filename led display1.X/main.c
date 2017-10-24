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
#include <stdint.h>
#include "user.h"
#include <libpic30.h>
#include <delay.h>
#define FYC 40000000
void delay1(void);
void init_LCD(void);
void initClock(void);

void data_wr(uint8_t data);
void DD_RAM_Address(uint8_t addr);

int main(void) {
    //initClock();
    __delay32(10000);
    //Delay_5mS_Cnt();
   InitPins();
  while(1)
  {
 EN=0;
 delay1();
 
 init_LCD();
 delay1();
//line_sel();
//delay1();
uint8_t count= 0x00;
//DD_RAM_Address(0xA0);
uint8_t j=0;
for (j=0;j<=80;j++)
{
//DD_RAM_Address(count+j);
data_wr((count+j)+0x21);
int k=0;
for(k=0;k<=30000;k++)
{
    delay1();
}

delay1();
}
while(1);
DD_RAM_Address(line2);
delay1();
data_wr('2');
delay1();
DD_RAM_Address(line3);
delay1();
data_wr('3');
delay1();
DD_RAM_Address(line4);
delay1();
data_wr('4');
delay1();

/**********************************************/
 
  while(1)
  {
     // init_4bit();
  }
   
   
  }
    return 0;
}

void delay1(void)
{
      int i=0;
   for(i=0;i<=120;i++)
   {
       Nop();
   }
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
void DD_RAM_Address(uint8_t addr)
{
    //LATB=(addr | 0b10000000);
   LATB=(addr);// | 0b10000000);
    // DB7=1;
   RW =0;
   RS=0;
   EN=1;
   delay1();
   EN=0;
   delay1();
}

void init_LCD(void)
{
   //LATB=0b00111100;
   LATB=inter_8bit;
   RW =0;
   RS=0;
   EN=1;
    delay1();
   EN=0;
   delay1();
  
   LATB=line_4;
   RW =0;
   RS=0;
   EN=1;
   delay1();
   EN=0;
   delay1();
   
   LATB=RE_0_8bit;//4 line mode
   RW =0;
   RS=0;
   EN=1;
    delay1();
   EN=0;
     delay1(); 
    
   LATB=D_C_ON;//4 line mode
   RW =0;
   RS=0;
   EN=1;
    delay1();
   EN=0;
   delay1(); 
  
   LATB=CLR;//4 line mode
   RW =0;
   RS=0;
   EN=1;
    delay1();
   EN=0;
   delay1(); 
 
  LATB=inc_courser;//4 line mode
   RW =0;
   RS=0;
   EN=1;
    delay1();
   EN=0;
   delay1();   
  
}


void data_wr(uint8_t data)
{
   LATB=data;
   RW =0;
   RS=1;
   EN=1;
   delay1();
   EN=0;
   delay1(); 
}

