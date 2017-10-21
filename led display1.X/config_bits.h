/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
// DSPIC33FJ06GS101 Configuration Bit Settings

// 'C' source line config statements

#include <p33Fxxxx.h>

 int FBS __attribute__((space(prog), address(0xF80000))) = 0xF ;
//_FBS(
//    BWRP_WRPROTECT_OFF & // Boot Segment Write Protect (Boot Segment may be written)
//    BSS_NO_BOOT_CODE     // Boot Segment Program Flash Code Protection (No Boot Segment)
//);
 int FGS __attribute__((space(prog), address(0xF80004))) = 0x7 ;
//_FGS(
//    GWRP_OFF &           // General Code Segment Write Protect (General Segment may be written)
//    GSS_OFF              // General Segment Code Protection (User program memory is not code-protected)
//);
 int FOSCSEL __attribute__((space(prog), address(0xF80006))) = 0x81 ;
//_FOSCSEL(
//    FNOSC_FRCPLL &       // Oscillator Source Selection (Internal Fast RC (FRC) with PLL)
//    IESO_ON              // Internal External Switch Over Mode (Start up device with FRC, then automatically switch to user-selected oscillator source)
//);
 int FOSC __attribute__((space(prog), address(0xF80008))) = 0xE3 ;
//_FOSC(
//    POSCMD_NONE &        // Primary Oscillator Source (Primary oscillator disabled)
//    OSCIOFNC_ON &        // OSC2 Pin Function (OSC2 is general purpose digital I/O pin)
//    IOL1WAY_ON &         // Peripheral Pin Select Configuration (Allow only one reconfiguration)
//    FCKSM_CSDCMD         // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled, Mon Disabled)
//);
 int FWDT __attribute__((space(prog), address(0xF8000A))) = 0xDF ;
//_FWDT(
//    WDTPOST_PS32768 &    // Watchdog Timer Postscaler (1:32,768)
//    WDTPRE_PR128 &       // WDT Prescaler (1:128)
//    WINDIS_OFF &         // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
//    FWDTEN_ON            // Watchdog Timer Enable (Watchdog timer always enabled)
//);
 int FPOR __attribute__((space(prog), address(0xF8000C))) = 0xF ;
//_FPOR(
//    FPWRT_PWR128         // POR Timer Value (128ms)
//);
 int FICD __attribute__((space(prog), address(0xF8000E))) = 0xC3 ;
//_FICD(
//    ICS_PGD1 &           // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
//    JTAGEN_OFF           // JTAG Port Enable (JTAG is disabled)
//);



    
    
    
    
    
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */



