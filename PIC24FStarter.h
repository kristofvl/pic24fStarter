/* Author: kvl@eti.uni-siegen.de
 * Created on July 26, 2025, 10:17 AM
 */
#ifndef P24FS_H
#define	P24FS_H

// Configuration bits
#pragma config WPFP = WPFP511    // Write Protection Flash Page Segment Boundary->Highest Page (same as page 170)
#pragma config WPDIS = WPDIS     // Segment Write Protection Disable bit->Segmented code protection disabled
#pragma config WPCFG = WPCFGDIS  // Configuration Word Code Page Protection Select bit->Last page(at the top of program memory) and Flash configuration words are not protected
#pragma config WPEND = WPENDMEM  // Segment Write Protection End Page Select bit->Write Protect from WPFP to the last page of memory
#pragma config POSCMOD = HS      // Primary Oscillator Select->HS oscillator mode selected
#pragma config DISUVREG = OFF    // Internal USB 3.3V Regulator Disable bit->Regulator is disabled
#pragma config IOL1WAY = ON      // IOLOCK One-Way Set Enable bit->Write RP Registers Once
#pragma config OSCIOFNC = ON     // Primary Oscillator Output Function->OSCO functions as port I/O (RC15)
#pragma config FCKSM = CSECMD    // Clock Switching and Monitor->Clock switching is enabled, Fail-safe Clock Monitor is disabled
#pragma config FNOSC = PRIPLL    // Oscillator Select->PRIPLL /FRC
#pragma config PLL_96MHZ = ON    // 96MHz PLL Disable->Enabled
#pragma config PLLDIV = DIV3     // USB 96 MHz PLL Prescaler Select bits->Oscillator input divided by 3 (12MHz input)
#pragma config IESO = OFF        // Internal External Switch Over Mode->IESO mode (Two-speed start-up)disabled
#pragma config FWDTEN = OFF      // Watchdog Timer disabled
#pragma config ICS = PGx2        // Comm Channel Select->Emulator functions are shared with PGEC1/PGED1
#pragma config BKBUG = OFF       // Background Debug->Device resets into Operational mode
#pragma config GWRP = OFF        // General Code Segment Write Protect->Writes to program memory are allowed
#pragma config GCP = OFF         // General Code Segment Code Protect->Code protection is disabled
#pragma config JTAGEN = OFF      // JTAG Port Enable->JTAG port is disabled

#include "SH1101A.h"

#define INIT_CLOCK() OSCCON = 0x3302; CLKDIV = 0x0000;

// RGB LEDs
#define INIT_RGB() TRISFbits.TRISF5 = TRISGbits.TRISG9 = TRISGbits.TRISG7 = 0;
#define SET_RGB(rS,gS,bS) LATFbits.LATF5=!rS; LATGbits.LATG9=!gS; LATGbits.LATG7=!bS; 

#endif	/* P24FS_H */
