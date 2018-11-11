/*
 * File:   UART.h
 * Author: SEPS
 *
 * Created on den 10 juni 2014, 14:13
 */

#ifndef UART_H
#define	UART_H
//#include "system.h"
//#define SYS_FREQ        40000000L
//#define FCY             SYS_FREQ/2
#define BAUDRATE 115200
#define BRGVAL   ((40000000/BAUDRATE)/16)-1

#define uart_tx_length 32
#if uart_tx_length != 32 && uart_tx_length != 64 && uart_tx_length != 128
	#error "UART buffer length must be 32, 64 or 128 bytes!"
#endif

#define UART_BUFFER_SIZE 10


void InitUART1(void);
void put_byte(char);
_Bool get_uart_rx_flag(void);
void get_string(char *);
void put_string(char *);
void uart_print(char *);
void dec_print_byte(unsigned int);
void uart_print_byte(char);
void bcd_print_word(int);
unsigned char UART1_Receive(void);
void options_list(void);
void secodary_options(void);
void primary_options(void);
void USB_command(uint8_t command);
void module_status(void);
extern uint8_t command;

#endif
