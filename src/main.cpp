#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

  DCOCTL = 0x00;         // Reset to lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ; // Set range select
  DCOCTL = CALDCO_1MHZ;  // Set DCO step and modulation
  BCSCTL2 = DIVS_1;      // Set SMCLK = DCOCLK / 2
  P1DIR = 0x01 + 0x40;   // P1.0 and P1.6 outputs
  P1OUT = 0x01;

  // Timer clock: source SMCLK, divider 8 (62.5 Khz)
  // Timer mode: Up to CCR0
  TACTL = TASSEL_2 + ID_3 + MC_1;
  TACCTL0 = CCIE; // CCTL0
  TACCR0 = 31250 * 2; // CCR0

  // Enter LPM0 with interrupt
  _BIS_SR(CPUOFF + GIE);
  while (1);

  return 1;
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
  P1OUT ^= 0x01 + 0x40; // Toggle P1.0 and P1.6
}

// USCI interrupts
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI_RX(void)
{
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCI_TX(void)
{
}
