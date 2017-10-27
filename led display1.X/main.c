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

void delay_xm(int m);
void init_LCD(void);
void initClock(void);
void WriteLetter2Width(uint8_t letter[]);
void WriteLetter6Width(uint8_t letter[]);
void data_wr(uint8_t data);
void DD_RAM_Address(uint8_t addr);
 int m; 
 uint8_t F[]={0xFF,0x90,0x90,0x90,0x80,0x00,0x00};
 uint8_t A[]={0x7F,0x88,0x88,0x88,0x7F,0x00};
 uint8_t R[]={0xFF,0x98,0x9c,0x9A,0xF9,0x00,0x00};
 uint8_t H[]={0xFF,0x08,0x08,0x08,0xFF,0x00,0x00};
 //uint8_t A[]={0xFF,0x90,0x90,0x90,0x80,0x00,0x00};
 uint8_t N[]={0xFF,0xc0,0x10,0x04,0xFF,0x00,0x00};
 uint8_t space[]={0x00,0x00};
int main(void) {
    //initClock();
    __delay32(10000);
    //Delay_5mS_Cnt();
   InitPins();
//int timer =1100;    
//int U18 = 3;
int State = 0;         
int lastState = 0; 
 
   
  while(1)
  {
 EN=0;
 delay1();
 
 init_LCD();
 delay1();

 while(1)
 {
     State= hall;
if (State != lastState){
  if (State == 1){
//delayMicroseconds(5000);
//delayMicroseconds(10000);

//delay(500);

//WriteLetter3Width(A);
 /*int n;
     m=0;
  for ( n=0; n<=5; n++){
  
   LATB=F[n];
    
    m=m+1;
delay_xm(20);
//LATB=0x00;

    
  }     */
      WriteLetter6Width(F);
      WriteLetter2Width(space);
      WriteLetter6Width(A);
      WriteLetter2Width(space);
      WriteLetter6Width(R);
       WriteLetter2Width(space);
       WriteLetter6Width(H);
       WriteLetter2Width(space);
       WriteLetter6Width(A);
       WriteLetter2Width(space);
       WriteLetter6Width(N);
       WriteLetter2Width(space);
delay1();
delay1();
delay1();
  }
}
lastState = State;
 
/*
int k=0;
for(k=0;k<=3000;k++)
{
    delay1();
}*/
//LATB=0x00;
//k=0;
 }


 
delay1();

/**********************************************/
 

   
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

void delay_xm(int m)
{
      int k=0;
for(k=0;k<=m;k++)
{
    //delay1();
    delay1();
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

void WriteLetter6Width(uint8_t letter[]){
    int n;
     m=0;
  for ( n=0; n<=4; n++){
  
   LATB= letter[m];
    
    m=m+1;
  delay_xm(15);
}
}
void WriteLetter2Width(uint8_t letter[]){
    int n;
     m=0;
  for ( n=0; n<=2; n++){
  
   LATB= letter[m];
    
    m=m+1;
  delay_xm(15);
}
}