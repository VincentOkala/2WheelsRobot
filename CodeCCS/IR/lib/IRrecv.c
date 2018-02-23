/******************************************************************************
 *
 * www.payitforward.edu.vn
 *
 ******************************************************************************/

/******************************************************************************
 *
 * TI LAUNCH PAD CODING
 *
 ******************************************************************************/

/******************************************************************************
 *
 *    Module       : IRrecv
 *    Description  :
 *
 *  Tool           : CCS 7.4
 *  Chip           : MSP430G2xx3 (MCU that haves USCI_A0 module)
 *  History        : 12/2/2018
 *  Version        : 1.0
 *
 *  Author         : Nguyen Khoi Nguyen (knguyentnh98@gmail.com)
 *  Notes          :
 *      To apply these functions, you must include the header file uart.h and
 *      add this code file to your project.
 *
 *
******************************************************************************/

 /****************************************************************************
 * IMPORT
******************************************************************************/
#include "IRrecv.h"

/****************************************************************************
* FUNCTIONS
******************************************************************************/
//uint8_t digitalRead(uint8_t port, uint8_t pin)
//{
//    if(port == 1)
//        if(P1IN & pin)
//            return 1;
//        else return 0;
//    else if(port == 2)
//        if(P2IN & pin)
//            return 1;
//        else return 0;
//}

void Config_stop_WDT(void)
{
    WDTCTL = WDTPW + WDTHOLD;
}
void Clock_Init(void)
{
    DCOCTL = 0;
    BCSCTL1 = CALBC1_16MHZ;          // set range
    DCOCTL = CALDCO_16MHZ;           // set DCO step + moudulation
}
void Timer_Init(void)
{
    TA0CCR0 = SAMPLING_TIME;
    TA0CTL = TASSEL_2 + MC_1 + TAIE ;                       // SMCLK, Up mode, Overflow interrupt
    TA0CCTL0 &= ~CCIFG;
    _BIS_SR(GIE);
    // Initialize state machine variables
    irparams.rcvstate = STATE_IDLE;
    irparams.rawlen = 0;
}
void GPIO_Init(void)
{
    P1SEL  &= ~(BTN1 + LED_GREEN);
    P1SEL2 &= ~(BTN1 + LED_GREEN);
    //Init button
    P1DIR  &= ~BTN1;
    P1REN  |= BTN1;
    P1OUT  |= BTN1;
#ifdef DEBUG
    P1IE   |= BTN1;
    P1IES  |= BTN1;
    P1IFG  &= ~BTN1;
#endif
    //Init LED GREEN
    P1DIR |= LED_GREEN;
    P1OUT &= ~LED_GREEN;
}



#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR(void)
{
    switch( TA0IV )
    {
    case  2:                            // CCR1 not used
        break;
    case  4:                            // CCR2 not used
        break;
    case 10:                            // overflow
        // Read if IR Receiver -> SPACE [xmt LED off] or a MARK [xmt LED on]
        // digitalRead() is very slow. Optimisation is possible, but makes the code unportable
        // unsigned char irdata;
        if (P1IN & PIN_IN)
            irdata = 1;
        else irdata =0;

        irparams.timer++;  // One more 50uS tick
        if (irparams.rawlen >= RAWBUF)  irparams.rcvstate = STATE_OVERFLOW ;  // Buffer overflow

        switch(irparams.rcvstate) {
            //......................................................................
            case STATE_IDLE: // In the middle of a gap
                if (irdata == MARK) {
                    if (irparams.timer < GAP_TICKS)  {  // Not big enough to be a gap.
                        irparams.timer = 0;

                    } else {
                        // Gap just ended; Record duration; Start recording transmission
                        irparams.overflow                  = flase;
                        irparams.rawlen                    = 0;
                        irparams.rawbuf[irparams.rawlen++] = irparams.timer;
                        irparams.timer                     = 0;
                        irparams.rcvstate                  = STATE_MARK;
                    }
                }
                break;
            //......................................................................
            case STATE_MARK:  // Timing Mark
                if (irdata == SPACE) {   // Mark ended; Record time
                    irparams.rawbuf[irparams.rawlen++] = irparams.timer;
                    irparams.timer                     = 0;
                    irparams.rcvstate                  = STATE_SPACE;
                }
                break;
            //......................................................................
            case STATE_SPACE:  // Timing Space
                if (irdata == MARK) {  // Space just ended; Record time
                    irparams.rawbuf[irparams.rawlen++] = irparams.timer;
                    irparams.timer                     = 0;
                    irparams.rcvstate                  = STATE_MARK;

                } else if (irparams.timer > GAP_TICKS) {  // Space
                        // A long Space, indicates gap between codes
                        // Flag the current code as ready for processing
                        // Switch to STOP
                        // Don't reset timer; keep counting Space width
                        irparams.rcvstate = STATE_STOP;
                }
                break;
            //......................................................................
            case STATE_STOP:  // Waiting; Measuring Gap
                if (irdata == MARK)  irparams.timer = 0 ;  // Reset gap timer
                break;
            //......................................................................
            case STATE_OVERFLOW:  // Flag up a read overflow; Stop the State Machine
                irparams.overflow = true;
                irparams.rcvstate = STATE_STOP;
                break;
        }
        P1OUT ^= LED_GREEN;
        break;
    }
}

/******************************************************************************
 * END OF IRrecv.c
*******************************************************************************/

