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
    INIT_CLOCK(); CTMUInit(); RGBMapColorPins();
    uint16_t timeout=10;  // milliseconds
    RGBTurnOnLED();
    ResetDevice();
    ClearDevice();
    SetColor( WHITE );
    uint8_t x = 2, y = 17, xDelta = 1, yDelta = 1;
    int16_t aggr[3];
    while(1) { 
        ReadCTMU();  // fills _potADC and buttons
        PutPixel(x,y);
        if (x==127) xDelta = -1; if (x==2) xDelta = 1;
        if (y==63) yDelta = -1; if (y==2) yDelta = 1;
        x+=xDelta; y+=yDelta;
        delay(timeout);
        for (uint8_t i=0; i<3; i++) {
            if (buttons[i]) aggr[i]++; else aggr[i]--;
            if (aggr[i] < 0) aggr[i]=0; if (aggr[i]>127) aggr[i]=127;
        }
        SetRGBs(aggr[0],aggr[1],aggr[2]);
    }
    RGBTurnOffLED();
}
