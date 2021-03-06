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
#include "UART.h"
#include <stdio.h>
#include <libpic30.h>
//#include <delay.h>
#define FYC 40000000
void delay1(void);

void delay_xm(int m);
void init_LCD(void);
void initClock(void);
void WriteLetter2Width(uint8_t letter[]);
void WriteLetter6Width(uint8_t letter[]);
void WriteLetter5Width(uint8_t letter[]);
void WriteLetter9Width(uint8_t letter[]);
void WriteLetter5Width_2dimensional(const uint8_t letter[][5],uint8_t index);
void data_wr(uint8_t data);
void DD_RAM_Address(uint8_t addr);
 int m; 
//struct __FILE {
//    int dummy;
//};
//
//FILE __stdout;
//
//int fputc(int ch, FILE *f) {
//    /* Do your stuff here */
//    /* Send your custom byte */
//    /* Send byte to USART */
//    //TM_USART_Putc(USART1, ch);
//    put_string((char *) &ch);
//    // HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,0xFFFF);
//    /* If everything is OK, you have to return character written */
//    return ch;
//    /* If character is not correct, you can return EOF (-1) to stop writing */
//    //return -1;
//}


const uint8_t fonts [][5]=
{
 {0x7F, 0x88, 0x88, 0x88, 0x7F}, //  A
 {0xFF, 0x91, 0x91, 0x91, 0x6E}, //  B
{0x7E, 0x81, 0x81, 0x81, 0x42},//  C
{0xFF, 0x81, 0x81, 0x42, 0x3C}, //\\  D
{0xFF, 0x91, 0x91, 0x91, 0x81}, //\\  E
{0xFF, 0x90, 0x90, 0x90, 0x80}, //\\  F
{0x7E, 0x81, 0x89, 0x89, 0x4E}, //\\  G
{0xFF, 0x10, 0x10, 0x10, 0xFF}, //\\  H
{0x81, 0x81, 0xFF, 0x81, 0x81}, //\\  I
{0x06, 0x01, 0x01, 0x01, 0xFE}, //\\  J
{0xFF, 0x18, 0x24, 0x42, 0x81}, //\\  K
{0xFF, 0x01, 0x01, 0x01, 0x01}, //\\  L
{0xFF, 0x40, 0x30, 0x40, 0xFF}, //\\  M
{0xFF, 0x40, 0x30, 0x08, 0xFF}, //\\  N
{0x7E, 0x81, 0x81, 0x81, 0x7E}, //\\  O
{0xFF, 0x88, 0x88, 0x88, 0x70}, //\\  P
{0x7E, 0x81, 0x85, 0x82, 0x7D}, //\\  Q
{0xFF, 0x88, 0x8C, 0x8A, 0x71}, //\\  R
{0x61, 0x91, 0x91, 0x91, 0x8E}, //\\  S
{0x80, 0x80, 0xFF, 0x80, 0x80}, //\\  T
{0xFE, 0x01, 0x01, 0x01, 0xFE}, //\\  U
{0xF0, 0x0C, 0x03, 0x0C, 0xF0}, //\\  V
{0xFF, 0x02, 0x0C, 0x02, 0xFF}, //\\  W
{0xC3, 0x24, 0x18, 0x24, 0xC3}, //\\  X
{0xE0, 0x10, 0x0F, 0x10, 0xE0}, //\\  Y
{0x83, 0x85, 0x99, 0xA1, 0xC1}, //\\  Z
{0x06, 0x29, 0x29, 0x29, 0x1F}, //\\  a
{0xFF, 0x09, 0x11, 0x11, 0x0E}, //\\  b
{0x1E, 0x21, 0x21, 0x21, 0x12}, //\\  c
{0x0E, 0x11, 0x11, 0x09, 0xFF}, //\\  d
{0x0E, 0x15, 0x15, 0x15, 0x0C}, //\\  e
{0x08, 0x7F, 0x88, 0x80, 0x40}, //\\  f
{0x30, 0x49, 0x49, 0x49, 0x7E}, //\\  g
{0xFF, 0x08, 0x10, 0x10, 0x0F}, //\\  h
{0x00, 0x00, 0x5F, 0x00, 0x00}, //\\  i
{0x02, 0x01, 0x21, 0xBE, 0x00}, //\\  j
{0xFF, 0x04, 0x0A, 0x11, 0x00}, //\\  k
{0x00, 0x81, 0xFF, 0x01, 0x00}, //\\  l
{0x3F, 0x20, 0x18, 0x20, 0x1F}, //\\  m
{0x3F, 0x10, 0x20, 0x20, 0x1F}, //\\  n
{0x0E, 0x11, 0x11, 0x11, 0x0E}, //\\  o
{0x3F, 0x24, 0x24, 0x24, 0x18}, //\\  p
{0x10, 0x28, 0x28, 0x18, 0x3F}, //\\  q
{0x1F, 0x08, 0x10, 0x10, 0x08}, //\\  r
{0x09, 0x15, 0x15, 0x15, 0x02}, //\\  s
{0x20, 0xFE, 0x21, 0x01, 0x02}, //\\  t
{0x1E, 0x01, 0x01, 0x02, 0x1F}, //\\  u
{0x1C, 0x02, 0x01, 0x02, 0x1C}, //\\  v
{0x1E, 0x01, 0x0E, 0x01, 0x1E}, //\\  w
{0x11, 0x0A, 0x04, 0x0A, 0x11}, //\\  x
{0x00, 0x39, 0x05, 0x05, 0x3E}, //\\  y
{0x11, 0x13, 0x15, 0x19, 0x11}, //\\  z
{0x00, 0x41, 0xFF, 0x01, 0x00}, //\\  1
{0x43, 0x85, 0x89, 0x91, 0x61}, //\\  2
{0x42, 0x81, 0x91, 0x91, 0x6E}, //\\  3
{0x18, 0x28, 0x48, 0xFF, 0x08}, //\\  4
{0xF2, 0x91, 0x91, 0x91, 0x8E}, //\\  5
{0x1E, 0x29, 0x49, 0x89, 0x86}, //\\  6
{0x80, 0x8F, 0x90, 0xA0, 0xC0}, //\\  7
{0x6E, 0x91, 0x91, 0x91, 0x6E}, //\\  8
{0x70, 0x89, 0x89, 0x8A, 0x7C}, //\\  9
{0x60, 0x80, 0x8D, 0x90, 0x60}, //\\  ?
{0x00, 0x00, 0xFD, 0x00, 0x00}, //\\  !
{0x7E, 0x89, 0x91, 0xA1, 0x7E}, //\\  0
{0x66, 0x89, 0x8F, 0x81, 0x7E}, //\\  @
{0x24, 0xFF, 0x24, 0xFF, 0x24}, //\\  #
{0x76, 0x89, 0x95, 0x62, 0x05}, //\\  &
{0x00, 0x3C, 0x42, 0x81, 0x00}, //\\  (
{0x00, 0x81, 0x42, 0x3C, 0x00}, //\\  )
{0x08, 0x08, 0x3E, 0x08, 0x08}, //\\  "+"
{0x08, 0x08, 0x08, 0x08, 0x08}, //\\  -
{0x14, 0x14, 0x14, 0x14, 0x14}, //\\  =
{0x10, 0x10, 0x54, 0x38, 0x10},// \\  R arrow
{0x08, 0x1C, 0x2A, 0x08, 0x08},// \\  L arrow
{0x12, 0x2A, 0x7F, 0x2A, 0x24},// \\  $
{0x44, 0x02, 0x12, 0x02, 0x44},// \\  smile
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF}// \\  5x8 block
//{0x08, 0x04, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01}, //\\  lower sinewave
//{0x10, 0x20, 0x40, 0x80, 0x80, 0x02, 0x02, 0x02}, //\\  upper sinewave
//{0x99, 0x24, 0x42, 0x99, 0x99, 0x42, 0x24, 0x99}, //\\  round pattern
//{0xFF, 0x81, 0xBD, 0xA5, 0xA5, 0xBD, 0x81, 0xFF}, //\\  box pattern inner
//{0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA}, //\\  fine checkers
//{0x33, 0x33, 0xCC, 0xCC, 0x33, 0x33, 0xCC, 0xCC}, //\\  big checkers
//{0x42, 0xC3, 0x24, 0x18, 0x18, 0x24, 0xC3, 0x42}, //\\  X pattern
//{0xFD, 0x85, 0xB5, 0xA5, 0xA5, 0xBD, 0x81, 0xFF}, //\\  sprial
//{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},// \\  8x8 block
//{0xFF, 0x7E, 0x7E, 0x7E, 0x7E, 0x42, 0x24, 0x18},// \\  bullet Right
//{0x18, 0x18, 0x3C, 0x66, 0x66, 0x3C, 0x18, 0x18},// \\  chain link
//{0x78, 0x78, 0x18, 0xFF, 0xFF, 0x0C, 0x3C, 0x3C},// \\  cactus
//{0xF2, 0x82, 0x12, 0x3A, 0x10, 0xC0, 0xC4, 0x0E},// \\  tetris
//{0x7F, 0x84, 0xA7, 0x84, 0xA7, 0x84, 0x7F, 0x00}, //\\  pacman ghost
//{0x3C, 0x42, 0x81, 0xA1, 0x89, 0x95, 0xA5, 0x42}, //\\  pacman
//{0x07, 0x2F, 0x1C, 0x3E, 0x3C, 0x30, 0x30, 0x30}, //\\  gun
//{0x5A, 0x99, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18}, //\\  gun bullets
//{0x82, 0x41, 0x82, 0x41, 0x82, 0x41, 0x82, 0x41}, //\\  checkers edges
//{0x00, 0x01, 0x06, 0x7E, 0xDF, 0x7E, 0x06, 0x01}, //\\  rocket
//{0x04, 0x0F, 0x1F, 0x3C, 0x3C, 0x1F, 0x0F, 0x04}, //\\  house
//{0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00}, //\\  vertical stripes
//{0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55}, //\\  horizontal strips
//{0x49, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92}, //\\  diag strips left
//{0x92, 0x49, 0x24, 0x92, 0x49, 0x24, 0x92, 0x49}, //\\  diag strips rights
//{0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, //  arrow shaft
//{0x18, 0x18, 0x3C, 0x5A, 0x99, 0x3C, 0x42, 0x81}, //  arrow tail
//{0x18, 0x3C, 0x7E, 0xFF, 0x18, 0x18, 0x18, 0x18}, //  arrow head
//{0x81, 0x42, 0x24, 0x18, 0x81, 0x42, 0x24, 0x18}, //  carrots L
//{0x18, 0x24, 0x42, 0x81, 0x18, 0x24, 0x42, 0x81}, //  carrots R
//{0x81, 0x42, 0x24, 0x99, 0x5A, 0x3C, 0x18, 0x18}, //  tail good
//{0x18, 0x18, 0x18, 0x18, 0xFF, 0x7E, 0x3C, 0x18} //  head good


};



 //uint8_t F[]={0xFF,0x90,0x90,0x90,0x80,0x00,0x00};
 uint8_t F[]={0xFF,0x09,0x09,0x09,0x01,0x00,0x00};// for reverse on padister fan clock wise print
 uint8_t A[]={0xFE,11,0x11,0x11,0xFE,0x00};// for reverse on padister fan clock wise print
 uint8_t R[]={0xFF,0x19,0x39,0x59,0x9F,0x00};// for reverse on padister fan clock wise print
 uint8_t H[]={0xFF,0x10,0x10,0x10,0xFF,0x00};// for reverse on padister fan clock wise print
 //uint8_t A[]={0xFF,0x90,0x90,0x90,0x80,0x00,0x00};
 uint8_t N[]={0xFF,0x03,0x08,0x20,0xFF,0x00};// for reverse on padister fan clock wise print
 uint8_t space[]={0x00,0x00};
 
 uint8_t custom[]={0b00000001,0b00000011,0b00000110,0b00001100,0b00000101,0b01111100,0b11000000,0b11000000,0b10111111,0b00000000,0b00110000,0b01001000,0b01111111,0b00000001,0b00011111,0b00000001,0b01111111,0b00000000,0b01111111}; // 8x9
 
int main(void) {
    //initClock();
    __delay32(10000);
    //Delay_5mS_Cnt();
   InitPins();
 
//int timer =1100;    
//int U18 = 3;
int State = 0;         
int lastState = 0; 
 int incre=0,count=0,pos=0;
  while(1)
  {
 //EN=0;
 //delay1();
      
 //init_LCD();
 //delay1();
      
      
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
                   LATB=0x00;

    
                     }     */
      /*********************First Line display********************/
//                    LATB = 0b00000000;
//                    T2CONbits.TON = 1; //Start Timer1 with prescaler settings at 1:1 and
//                    while (timer_set == 0);
//                    T2CONbits.TON = 0; //Start Timer1 with prescaler settings at 1:1 and  
//                    LATB = 0b11111111;
//                    delay1();
//                    LATB = 0b00000000;
//                    timer_set = 0;
/********************************************************************************************/

 /*********************Nest Line display********************/
//                    TMR2 = 0x00; //Clear contents of the timer register
//                    // T2CONbits.TCKPS = 0b11; //prescaler set to 256
//                    //50us
//                    PR2 = 20000; //Fosc/2000UL  	//Load the Period register with 1mSec counter    
//                    T2CONbits.TON = 1; //Start Timer1 with prescaler settings at 1:1 and
//                    while (timer_set == 0);
//                     T2CONbits.TON = 0; //Start Timer1 with prescaler settings at 1:1 and  
//                    LATB = 0b11111111;
//                    delay1();
//                    LATB = 0b00000000;  
//                     timer_set = 0;
/********************************************************************************************/                     
                   /*********************Nest Line display********************/
//                    TMR2 = 0x00; //Clear contents of the timer register
//                    // T2CONbits.TCKPS = 0b11; //prescaler set to 256
//                    //50us
//                    PR2 = 20000; //Fosc/2000UL  	//Load the Period register with 1mSec counter    
//                    T2CONbits.TON = 1; //Start Timer1 with prescaler settings at 1:1 and
//                    while (timer_set == 0);
//                     T2CONbits.TON = 0; //Start Timer1 with prescaler settings at 1:1 and  
//                    LATB = 0b11111111;
//                    delay1();
//                    LATB = 0b00000000;  
//                     timer_set = 0;
/********************************************************************************************/  
     int i=0;
     
     for(i=0;i<=58;i++)
     {
 /*********************Nest Line display********************/
                    TMR2 = 0x00; //Clear contents of the timer register
                    // T2CONbits.TCKPS = 0b11; //prescaler set to 256
                    //50us
                    PR2 = 12000; //Fosc/2000UL  	//Load the Period register with 1mSec counter    
                    T2CONbits.TON = 1; //Start Timer1 with prescaler settings at 1:1 and
                    while (timer_set == 0);
                     T2CONbits.TON = 0; //Start Timer1 with prescaler settings at 1:1 and  
//                     if(count==290 && i==10)
//                     if(i==pos)
//                     {
//                        if(count==25 || incre==1)
//                        {
//                         
//                    LATB = 0b01100000;
//                    delay1();
//                    delay1();
//                     LATB = 0b00000000;
//                     incre=1;
//                        }
//                        
//                     else
//                        {
//                         
//                    LATB = 0b01111111;
//                    delay1();
//                    delay1();
//                     LATB = 0b00000000;
//                     incre=1;
//                        }
//                        
//                        
//                     }
//                     else{ 
            if(i==0 || i==15 || i==32 || i== 50)         
            {
                     
                if(i==0)    
                {
                     WriteLetter5Width_2dimensional(fonts,52);
                     WriteLetter5Width_2dimensional(fonts,53);
                     incre++;
                }
                else{
                WriteLetter5Width_2dimensional(fonts,incre+52); 
                     incre++;
                     if(incre==4)
                     {
                         incre=0;
                     }
                }
            }      
                     
                     
                    LATB = 0b11111111;
                    delay1();
                    delay1();
//                    delay1();
                    LATB = 0b00000000;
                    // }
                     timer_set = 0;
                     
/********************************************************************************************/  
     }
                     
 count++;                    
  if(count>=50)
  {
      count=0;
              incre=0;
              pos=pos+1;
  }
                     
                     
////     
////      WriteLetter6Width(N);
////      WriteLetter2Width(space);
////       WriteLetter6Width(A);
////      WriteLetter2Width(space);
////           WriteLetter6Width(H);
////      WriteLetter2Width(space);
////      
////          WriteLetter6Width(R);
////      WriteLetter2Width(space);
////           WriteLetter6Width(A);
//      WriteLetter2Width(space); 
//            WriteLetter6Width(F);
//      WriteLetter2Width(space);
//      delay_xm(incre*2);
//    WriteLetter5Width_2dimensional(fonts,incre); 
//      WriteLetter2Width(space);
//      WriteLetter2Width(space);
//
//     // WriteLetter9Width(custom);
//      WriteLetter2Width(space);
//      WriteLetter2Width(space);
//      WriteLetter2Width(space);
     
//delay1();
//delay1();
  
            

  }
}
lastState = State;
 
/*
int k=0;
for(k=0;k<=3000;k++)
{
    delay1();
}*/
//LATB=0xFF;
//k=0;
 }


 
//delay1();

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

void WriteLetter5Width(uint8_t letter[]){
    int n;
     m=0;
  for ( n=0; n<=4; n++){
  
   LATB= letter[m];
    
    m=m+1;
  delay_xm(3);
}
}    
 void WriteLetter6Width(uint8_t letter[]){
    int n;//=54/60;
     m=0;
  for ( n=0; n<=5; n++){
  
   LATB= letter[m];
    
    m=m+1;
   
      delay_xm(10);  
    
}    
 }   

 
 void WriteLetter9Width(uint8_t letter[]){
    int n;
     m=0;
  for ( n=0; n<=18; n++){
  
   LATB= letter[m];
    
    m=m+1;
  delay_xm(2);
}
}
 
 
 
void WriteLetter2Width(uint8_t letter[]){
    int n;
     m=0;
  for ( n=0; n<=1; n++){
  
   LATB= letter[m];
    
    m=m+1;
  delay_xm(3);
}
}


void WriteLetter5Width_2dimensional(const uint8_t letter[][5],uint8_t index){
    int n;
     m=0;
  for ( n=0; n<=4; n++){
  
   LATB= letter[index][m];
    
    m=m+1;
  delay_xm(1);
}
} 