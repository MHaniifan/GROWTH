#include "uart.h"
#include <avr/io.h>
#include <stdio.h>

void UARTInit(void){
  
  UBRR0H = BAUDH;
  UBRR0L = BAUDL;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = (3 << UCSZ00);
}

volatile unsigned char UARTGetChar(void){
  while (!(UCSR0A & (1 << RXC0)));
  return UDR0;
}

int UARTPutChar(char c, FILE *stream){
  if (c == '\n') {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = '\r';
  }
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = c;
  return 0;
}