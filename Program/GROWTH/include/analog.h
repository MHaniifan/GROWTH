#ifndef ANALOG_H
#define ANALOG_H
#include <avr/io.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned int ADCIN( unsigned char channel );
void ADCInit(void);

#ifdef __cplusplus
}
#endif

#endif
