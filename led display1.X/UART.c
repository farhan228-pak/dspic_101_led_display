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

#include "UART.h"
#include <stdint.h>        /* Includes uint16_t definition   */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>       /* Includes true/false definition */
//#include "Define_PSFB.h"
//#include "Variables_PSFB.h"
//#include  "VT100.h"
#include "delay.h"

// Global Variable -------------------------------------------------------
volatile char uart_tx_buffer[uart_tx_length];
volatile unsigned int uart_tx_writep = 0;
volatile unsigned int uart_tx_readp = 0;
volatile _Bool uart_tx_full;

char uart_rx_buffer[UART_BUFFER_SIZE];	// receive buffer

volatile _Bool uart_rx_flag;		// receive complete
volatile _Bool uart_tx_flag;		// send complete
volatile _Bool uart_tx_byte;		// indicate to send a byte

uint8_t command =0;

// Functions -----------------------------
_Bool get_uart_rx_flag(void)
{
	return uart_rx_flag;
}

void set_uart_rx_flag(_Bool flag)
{
	uart_rx_flag = flag;
}
// get string
void get_string(char *daten)
{
    if (uart_rx_flag==1) {
      strcpy(daten, uart_rx_buffer);
      uart_rx_flag = 0;
   }
}


void put_byte(char daten)
{
	//if (uart_tx_full)	_LATB15 = 1;
	//else				_LATB15 = 0;

	//wait until space is free
	//while(uart_tx_full){}
	//disable tx interupt for asyncronous ISR operation
	//IEC0bits.U1TXIE = 0;	// Disable Transmit Interrupts
	//put byte into buffer
	//uart_tx_buffer[uart_tx_writep] = daten;
	//increment write pointer
	//++uart_tx_writep
	//if(uart_tx_writep >= uart_tx_length)
	//{
	//	uart_tx_writep = 0;
	//}
    U1TXREG = daten;
    //U1TXREG = (char)uart_tx_buffer[uart_tx_readp];
	//uart_tx_writep = (uart_tx_writep + 1) & (uart_tx_length - 1);
	//set full flag
	//uart_tx_full = (uart_tx_writep == uart_tx_readp);

	//enable tx interrupt
	//IEC0bits.U1TXIE = 1;	// Enable Transmit Interrupts
}


void put_string(char *daten)
{
	char cdata;
	while((cdata = *daten++) != '\0')
	{
		put_byte(cdata);
        Delay(1);
	}
}
void InitUART1() {
	// This is an EXAMPLE, so brutal typing goes into explaining all bit sets

	// configure U2MODE
	U1MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	//U2MODEbits.notimplemented;	// Bit14
	U1MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U1MODEbits.IREN = 0;	// Bit12 No IR translation
	U1MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
	//U2MODEbits.notimplemented;	// Bit10
	U1MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U1MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U1MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U1MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')
	U1MODEbits.URXINV = 0;	// Bit4 IdleState = 1  (for dsPIC)
	U1MODEbits.BRGH = 0;	// Bit3 16 clocks per bit period
	U1MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U1MODEbits.STSEL = 0;	// Bit0 One Stop Bit

	// Load a value into Baud Rate Generator.  Example is for 9600.
	// See section 19.3.1 of datasheet.
	//  U2BRG = (Fcy/(16*BaudRate))-1
	//  U2BRG = (37M/(16*9600))-1
	//  U2BRG = 240
	U1BRG = BRGVAL;		// 40Mhz osc, 9600 Baud

	// Load all values in for U1STA SFR
	U1STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
	U1STAbits.UTXINV = 0;	//Bit14 N/A, IRDA config
	U1STAbits.UTXISEL0 = 0;	//Bit13 Other half of Bit15
	//U2STAbits.notimplemented = 0;	//Bit12
	U1STAbits.UTXBRK = 0;	//Bit11 Disabled
	U1STAbits.UTXEN = 0;	//Bit10 TX pins controlled by periph
	U1STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
	U1STAbits.TRMT = 0;	//Bit8 *Read Only bit*
	U1STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
	U1STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	U1STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
	U1STAbits.PERR = 0;		//Bit3 *Read Only Bit*
	U1STAbits.FERR = 0;		//Bit2 *Read Only Bit*
	U1STAbits.OERR = 0;		//Bit1 *Read Only Bit*
	U1STAbits.URXDA = 0;	//Bit0 *Read Only Bit*

	IPC3bits.U1TXIP = 1;	//Lowest priority for Uart TX
    //IPC2bits.U1RXIP =3;
	//IPC3 = 0x4400;	// Mid Range Interrupt Priority level, no urgent reason

	IFS0bits.U1TXIF = 0;	// Clear the Transmit Interrupt Flag
	IEC0bits.U1TXIE = 0;	// Enable Transmit Interrupts

	IFS0bits.U1RXIF = 0;	// Clear the Recieve Interrupt Flag
	IEC0bits.U1RXIE = 0;	//dis Enable Recieve Interrupts


	//*************************************************************
	// Unlock Registers
	//*************************************************************
	__builtin_write_OSCCONL(OSCCON & ~(1<<6));

	//*******************************
	// Assign U1Rx To Pin RP25  
	//***************************
	//RPINR18bits.U1RXR = 25; //RPINR18 is the register dedecated for UART RX and its bits U1RXR decide which RP pin will get the funvtionality of RX
    RPINR2bits.T1CKR = 8;//for timer gate input on pin RP15 which is RB15 also;
	//***************************
	// Assign U1Tx To Pin RP9
	//***************************
	RPOR4bits.RP9R = 3;
        //RPOR0bits.RP0R = 0b010010;
	//*************************************************************
	// Lock Registers
	//*************************************************************
	__builtin_write_OSCCONL(OSCCON | (1<<6));


	uart_rx_flag = false;		// receive complete
	uart_tx_full = false;
	uart_tx_writep = false;
	uart_tx_readp = false;


	U1MODEbits.UARTEN = 1;	// And turn the peripheral on

	U1STAbits.UTXEN = 1;
	// I think I have the thing working now.
}

void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{

    IFS0bits.U1TXIF = 0;	// reset interrupt flag
	//take one byte from the buffer and put it to UART
	U1TXREG = (char)uart_tx_buffer[uart_tx_readp];
	//increment read pointer
	//++uart_tx_readp
	//if(uart_tx_readp >= uart_tx_length)
	//{
	//	uart_tx_readp = 0;
	//}
	uart_tx_readp = (uart_tx_readp + 1) & (uart_tx_length - 1);
	//check weather there is a byte left in buffer

	if(uart_tx_readp == uart_tx_writep)
	{
		IEC0bits.U1TXIE = 0;	// Disable Transmit Interrupts
	}
	//buffer isn't full any more...
	uart_tx_full = false;
}

unsigned char UART1_Receive(void)

{

unsigned char c;

//while(_U1RXIF==0);

_U1RXIF=0;

c = U1RXREG;

return c;

}

void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
	//LED_D5 =!LED_D5;
    IFS0bits.U1RXIF = 0;
	//static unsigned int uart_rx_cnt;     	// counter
	    char data;
	
	    data = U1RXREG;						// read data  
        command=data;
       // printf ("%c \n\r",data);
//	    if (!uart_rx_flag)					// buffer free for new data 			
//	        {
//			if (data=='\r')					// end of string (RETURN)?
//			{
//	            uart_rx_buffer[uart_rx_cnt]=0;              
//	            uart_rx_flag=1;				// buffer full
//	            uart_rx_cnt=0;				// reset counter
//	        }
//	        else if (uart_rx_cnt<(UART_BUFFER_SIZE-1)) {     
//	            uart_rx_buffer[uart_rx_cnt]=data;          
//	            uart_rx_cnt++;				// increase counter
//	        }
//	    }
  

	//LATA = U1RXREG;
	//_LATB15 = !_LATB15;
}


//void options_list(void)
//{
//    printf("enter number to select one of the options\n\r");
//    
//    printf("Case 1 = Turn Module ON\n\r");
//    
//    printf("Case 2 = Turn Module OFF\n\r");
//    
//    printf("Case 3 = Primary in Series\n\r");
//    
//    printf("Case 4 = Primary in Parallel\n\r");
//    
//    printf("Case 5 = Secondary in parallel\n\r");
//    
//    printf("Case 6 = Secondary in Series\n\r\n\r\t");
//    
//    printf("Current status\n\r\n\r");
//    
//    primary_options();
//    
//    secodary_options();
//    module_status();  
//}
//
//void module_status(void)
//{
//    if(module_state==System_OFF)
//    {
//    printf("\033[32;1;1m");// set color to Green
//    printf("Module Status = ");
//    printf("\033[31;1;1m");// set color to Red
//    printf("OFF");  
//    }
//    if(module_state==System_ON)
//    {
//    printf("\033[32;1;1m");// set color to Green
//    printf("Module Status = ");
//    printf("\033[31;1;1m");// set color to Red
//    printf("ON");  
//    }
     
    
    
//}
//void secodary_options(void)
//{
//    if(ssp1a==0 && ssp2a==0 && ssp1b==1 && ssp2b==1)
//    {
//        printf("\033[32;1;1m");// set color to Green
//        printf ("Secondary = ");
//        printf("\033[31;1;1m");//set color to Red
//        printf(" Parallel\n\r"); 
//    }
//
//        if(ssp1a==1 && ssp2a==1 && ssp1b==0 && ssp2b==0)
//    {
//        printf("\033[32;1;1m");// set color to Green
//        printf ("Secondary = ");
//        printf("\033[31;1;1m");//set color to Red
//        printf(" Series\n\r"); 
//    }


    
//}
//
//void primary_options(void)
//{
//      if(SerPar==0) 
//    {
//        printf("\033[32;1;1m");// set color to Green
//        printf ("Primary = ");
//        printf("\033[31;1;1m");//set color to Red
//        printf(" Series\n\r");        
//    }
//      if(SerPar==1) 
//    {
//        printf("\033[32;1;1m");// set color to Green
//        printf ("Primary = ");
//        printf("\033[31;1;1m");//set color to Red
//        printf(" Parallel\n\r");        
//    }   
//}
//
//void USB_command(uint8_t command) {
//
//    command = command - 48;
//    //printf("command=%d\n\r",command);
//    switch (command) {
//
//
//        case 1:
//            printf(Reset_term);
//            //printf(CLS);
//            printf(HOME);
//            //printf("command=%d",command);
//            LED_D5 = 1;
//            module_state = System_ON;
//
//            /* add code for PWM over ride or turn on*/
//            //PTCONbits.PTEN = 1; // enable the PWM module
//            TRISAbits.TRISA4 = 1; // Configure PWM1H/RA4 as digital input
//            // Ensure output is in safe state using pull-up or
//            // pull-down resistors
//            TRISAbits.TRISA3 = 1; // Configure PWM1L/RA3 as digital input
//            // Ensure output is in safe state using pull-up or
//            // pull-down resistors
//
//            TRISBbits.TRISB14 = 1; // Configure PWM1H/RA4 as digital input
//            // Ensure output is in safe state using pull-up or
//            // pull-down resistors
//            TRISBbits.TRISB13 = 1; // Configure PWM1L/RA3 as digital input
//            // Ensure output is in safe state using pull-up or
//            // pull-down resistors
//
//            IOCON1bits.PENH = 0; // Assign pin ownership of PWM1H/RA4 to GPIO module
//            IOCON1bits.PENL = 0; // Assign pin ownership of PWM1L/RA3 to GPIO module
//            IOCON1bits.OVRDAT = 0; // Configure override state of the PWM outputs to
//            // desired safe state.
//            IOCON2bits.PENH = 0; // Assign pin ownership of PWM1H/RA4 to GPIO module
//            IOCON2bits.PENL = 0; // Assign pin ownership of PWM1L/RA3 to GPIO module
//            IOCON2bits.OVRDAT = 0; // Configure override state of the PWM outputs to
//
//            IOCON1bits.OVRENH = 1; // Override PWM1H output
//            IOCON1bits.OVRENL = 1; // Override PWM1L output
//
//            IOCON2bits.OVRENH = 1; // Override PWM1H output
//            IOCON2bits.OVRENL = 1; // Override PWM1L output
//
//            PTCONbits.PTEN = 1; // Enable PWM module
//            //Delay_Us(2); // Introduce a delay greater than one full PWM cycle
//            IOCON1bits.OVRENH = 0; // Remove override for PWM1H output
//            IOCON1bits.OVRENL = 0; // Remove override for PWM1L output
//
//            IOCON2bits.OVRENH = 0; // Remove override for PWM1H output
//            IOCON2bits.OVRENL = 0; // Remove override for PWM1L output
//
//            Delay_Us(5); // Introduce a delay greater than one full PWM cycle
//            int i;
//            //for(i=0;i<=100;i++)
//            //{
//            //    Nop();
//            //}
//            IOCON1bits.PENH = 1; // Assign pin ownership of PWM1H/RA4 to PWM module
//            IOCON1bits.PENL = 1; // Assign pin ownership of PWM1L/RA3 to PWM module
//
//            IOCON2bits.PENH = 1; // Assign pin ownership of PWM1H/RA4 to PWM module
//            IOCON2bits.PENL = 1; // Assign pin ownership of PWM1L/RA3 to PWM module
//            LED_D5 = 0;
//
//            options_list();
//            break;
//
//        case 2:
//            printf(Reset_term);
//            //printf(CLS);
//            printf(HOME);
//            LED_D5 = 1;
//            module_state = System_OFF;
//            IOCON1bits.PENH = 0; // Assign pin ownership of PWM1H/RA4 to GPIO module
//            IOCON1bits.PENL = 0; // Assign pin ownership of PWM1L/RA3 to GPIO module
//            IOCON1bits.OVRDAT = 0; // Configure override state of the PWM outputs to
//            // desired safe state.
//            IOCON2bits.PENH = 0; // Assign pin ownership of PWM1H/RA4 to GPIO module
//            IOCON2bits.PENL = 0; // Assign pin ownership of PWM1L/RA3 to GPIO module
//            IOCON2bits.OVRDAT = 0; // Configure override state of the PWM outputs to
//
//            IOCON1bits.OVRENH = 1; // Override PWM1H output
//            IOCON1bits.OVRENL = 1; // Override PWM1L output
//
//            IOCON2bits.OVRENH = 1; // Override PWM1H output
//            IOCON2bits.OVRENL = 1; // Override PWM1L output
//
//
//
//
//            PTCONbits.PTEN = 0; // Disable the PWM module
//            LED_D5 = 0;
//            /*add code for over ride PWM or PTCON turn on*/
//            options_list();
//            break;
//
//        case 3:
//            printf(Reset_term);
//            //printf(CLS);
//            printf(HOME);
//            SerPar = 0; //primary in series
//            LED_D5 = 1;
//            IOCON1bits.OVRENH = 1; // Override PWM1H output
//            IOCON1bits.OVRENL = 1; // Override PWM1L output
//
//            IOCON2bits.OVRENH = 1; // Override PWM1H output
//            IOCON2bits.OVRENL = 1; // Override PWM1L output  
//
//
//            /*add code to change the state of MUX*/
//            LATBbits.LATB15 = 0; //Select Tr 5 and 6 
//            LATBbits.LATB1 = 1; //Enable Tr 3 and 4 
//            Delay_Us(4);
//            IOCON1bits.OVRENH = 0; // Override PWM1H output
//            IOCON1bits.OVRENL = 0; // Override PWM1L output
//
//            IOCON2bits.OVRENH = 0; // Override PWM1H output
//            IOCON2bits.OVRENL = 0; // Override PWM1L output
//            LED_D5 = 0;
//
//            options_list();
//            break;
//
//        case 4:
//            printf(Reset_term);
//            //printf(CLS);
//            printf(HOME);
//            SerPar = 1; // primary in prallel
//            LED_D5 = 1;
//            IOCON1bits.OVRENH = 1; // Override PWM1H output
//            IOCON1bits.OVRENL = 1; // Override PWM1L output
//
//            IOCON2bits.OVRENH = 1; // Override PWM1H output
//            IOCON2bits.OVRENL = 1; // Override PWM1L output  
//
//
//
//            LATBbits.LATB15 = 1; //Select Tr 5 and 6 
//            LATBbits.LATB1 = 0; //Enable Tr 3 and 4 
//            Delay_Us(4);
//            IOCON1bits.OVRENH = 0; // Override PWM1H output
//            IOCON1bits.OVRENL = 0; // Override PWM1L output
//
//            IOCON2bits.OVRENH = 0; // Override PWM1H output
//            IOCON2bits.OVRENL = 0; // Override PWM1L output
//            LED_D5 = 0;
//
//            /*add code to change Mux state*/
//            options_list();
//            break;
//
//        case 5:
//            printf(Reset_term);
//            //printf(CLS);
//            printf(HOME);
//            /*add code to swith off PWM and change Secondary configuration that should be parallel*/
//            ssp1a = 0; //          ssp1a       ssp2a       ssp1b       ssp2b
//            ssp2a = 0; //            0           0          1           1          parallel
//            ssp1b = 1; //            1           1          0           0          series
//            ssp2b = 1;
//            options_list();
//            break;
//
//        case 6:
//            printf(Reset_term);
//            //printf(CLS);
//            printf(HOME);
//            /*add code to swith off PWM and change Secondary configuration that should be Series*/
//            ssp1a = 0; //          ssp1a       ssp2a       ssp1b       ssp2b
//            ssp2a = 0; //            0           0          1           1          parallel
//            ssp1b = 0; //            1           1          0           0          series
//            ssp2b = 0;
//            
//            ssp1a = 1; //          ssp1a       ssp2a       ssp1b       ssp2b
//            ssp2a = 1; //            0           0          1           1          parallel
//            ssp1b = 0; //            1           1          0           0          series
//            ssp2b = 0;
//            options_list();
//            break;
//        default:
//            break;
//
//    }
//    command = 0;
//}