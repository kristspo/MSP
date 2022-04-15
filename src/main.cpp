
#include <msp430.h>
#include "serial.h"

Serial s;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    DCOCTL = 0x00;         // Reset to lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ; // Set range select
    DCOCTL = CALDCO_1MHZ;  // Set DCO step and modulation
    BCSCTL2 = DIVS_0;      // SMCLK Divider 0
    P1DIR = 0x01 + 0x40;   // P1.0 and P1.6 outputs
    P1OUT = 0x00;

    // Timer clock: source SMCLK, divider 8 (125 Khz)
    // Timer mode: Up to CCR0
    TACTL = TASSEL_2 + ID_3 + MC_1;
    TACCTL0 = CCIE;  // CCTL0
    TA0CCR0 = 62500; // set CCR0

    // Setup USCI
    UCA0CTL1 = (0xC0 | UCSWRST); // USCI clock source SMCLK
    UCA0MCTL = 0;                // oversampling disabled
    UCA0BR0 = 26;
    UCA0BR1 = 0;
    P1SEL = (BIT1 | BIT2); // P1.1 and P1.2 peripheral module function selected
    P1SEL2 = (BIT1 | BIT2);
    UCA0CTL1 &= ~UCSWRST; // clear reset bit

    IE2 |= UCA0RXIE; // USCI recieve interrupt enabled

    // Enter LPM0 with interrupt
    _BIS_SR(CPUOFF + GIE);
    while (1)
    {
    };
    return 1;
}

// Timer A0 interrupt
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    P1OUT ^= 0x01; // Toggle P1.0 every 0.5 s
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI_RX(void)
{
    uint8_t rx = UCA0RXBUF; // reading RX clears UCB0RXIFG
    s.put_char(rx);
    P1OUT |= 0x40;
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCI_TX(void)
{
}
