/* Author: kvl@eti.uni-siegen.de
 * Created on July 25, 2025, 11:18 AM
 */
#include <xc.h>
#include "PIC24FStarter.h"

void delay(unsigned int milliseconds) {
    T1CONbits.TCKPS = 0b11; // Prescale 1:256
    PR1 = 47; TMR1 = 0; // Reset timer counter
    T1CONbits.TON = 1; // Turn on Timer1
    unsigned int count = 0;
    while (count < milliseconds) {
        while (!IFS0bits.T1IF); // Wait for Timer1 interrupt flag
        IFS0bits.T1IF = 0; // Clear Timer1 interrupt flag
        count++;
    }
    T1CONbits.TON = 0; // Turn off Timer1
}

int main(void) {
    INIT_CLOCK();
    uint16_t timeout=100;  // milliseconds
    INIT_RGB();
    SET_RGB(0,0,0);
    ResetDevice();
    ClearDevice();
    SetColor( WHITE );
    uint8_t x = 0, y = 17, xDelta = 1, yDelta = 1;
    while(1) {  // cycle through LEDs (non-PWM))
        PutPixel(x,y);
        if (x==127) xDelta = -1; if (x==0) xDelta = 1;
        if (y==63) yDelta = -1; if (y==0) yDelta = 1;
        x+=xDelta; y+=yDelta;
        delay(timeout);
        SET_RGB(1,0,0);
        delay(timeout);
        SET_RGB(0,1,0);
        delay(timeout);
        SET_RGB(0,0,1);
    }
}

