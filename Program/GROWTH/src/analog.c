#include "analog.h"
#include <util/delay.h>
unsigned char i;
unsigned int ADCIN(unsigned char channel){
  ADMUX |= ( 0 << ADLAR ) | _BV(REFS0) | channel;
  ADCSRA |= ( 1 << ADSC );
  while (!(ADCSRA&(1<<ADIF)));
  ADCSRA |= (1<<ADIF); 
  
  uint16_t low  = ADCL;
  uint16_t high = ADCH;
  return (high << 8) | low;
}

void ADCInit(void){
  ADCSRA |= (1<< ADEN)|(1<<ADSC)|(1<<ADPS2)|(1<<ADPS1);
  ADCSRA |= (1<<ADSC);
  ADCSRB=0;
  while (!(ADCSRA&(1<<ADIF))); 
  ADCSRA |= (1<<ADIF); 
}