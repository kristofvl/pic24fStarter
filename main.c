/* Author: kvl@eti.uni-siegen.de
 * Created on July 25, 2025, 11:18 AM
 */

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

// helper function for drawing a circle
void plotPoints(uint8_t xctr, uint8_t yctr, uint8_t x, uint8_t y) {
    PutPixel(xctr + x, yctr + y ); PutPixel(xctr - x, yctr + y );
    PutPixel(xctr + x, yctr - y ); PutPixel(xctr - x, yctr - y );
    PutPixel(xctr + y, yctr + x ); PutPixel(xctr - y, yctr + x );
    PutPixel(xctr + y, yctr - x ); PutPixel(xctr - y, yctr - x );
}
// draw a circle at (x,y) with radius r
void drawCircle(uint8_t x1, uint8_t y1, uint8_t r) {
    uint8_t x = 0, y = r;
    uint8_t p = 1 - r;
    plotPoints(x1, y1, x, y);
    while (x < y) {
        x++;
        if (p < 0) p += 2 * x + 1;
        else p += 2 * (x - --y) + 1;
        plotPoints(x1, y1, x, y);
    }
}


int main(void) {
    INIT_CLOCK(); CTMUInit(); RGBMapColorPins();
    uint16_t timeout=10;  // milliseconds
    uint8_t x = 63, y = 32;  // circle middle
    RGBTurnOnLED();
    ResetDevice();
    ClearDevice();
    int16_t aggr[5]; aggr[0]=aggr[1]=aggr[2]=aggr[3]=0;
    while(1) { 
        ReadCTMU();  // fills _potADC and buttons
        SetColor(BLACK);  // erase old circle:
        drawCircle(x,y, 9);drawCircle(x,y, 8);drawCircle(x,y, 7);
        SetColor(WHITE);  // draw circle:
        x = 63 + aggr[1] - aggr[3]; y = 32 - aggr[0] + aggr[2];        
        drawCircle(x,y, 9);drawCircle(x,y, 8);drawCircle(x,y, 7);
        delay(timeout);
        for (uint8_t i=0; i<5; i++) {
            if (buttons[i]) aggr[i]++; else aggr[i]--;
            if (aggr[i] < 0) aggr[i]=0; 
            if (i==0 || i==2) { if (aggr[i]>22) aggr[i]=22; }
            else { if (aggr[i]>54) aggr[i]=54; }
        }
        SetRGBs(aggr[0]*4,aggr[1]*4,aggr[2]*4);
    }
    RGBTurnOffLED();
}
