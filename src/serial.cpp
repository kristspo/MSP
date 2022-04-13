
#include <msp430.h>
#include "serial.h"

Serial::Serial() {
     get = 0;
     put = 0;

     UCA0CTL1 = (0xC0 | UCSWRST);  // USCI clock source SMCLK
     UCA0MCTL = 0;            // oversampling disabled
     UCA0BR0 = 26;
     UCA0BR1 = 0;
     P1SEL  = (BIT1 | BIT2); // P1.1 and P1.2 peripheral module function selected
     P1SEL2 = (BIT1 | BIT2);
     UCA0CTL1 &= ~UCSWRST; // clear reset bit

     IE2 |= UCA0RXIE;    // USCI recieve interrupt enabled

}

void Serial::output() {

}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI_RX(void)
{
     UCA0TXBUF = UCA0RXBUF; // reading RX clears UCB0RXIFG
     P1OUT ^= 0x40;
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCI_TX(void)
{

}
