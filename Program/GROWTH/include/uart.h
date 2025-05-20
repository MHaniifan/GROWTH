#ifndef UART_H_
#define UART_H_
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
#define BAUDRATE 9600
#define VBAUDRATE (F_CPU/((unsigned long) BAUDRATE*16)-1)
#define BAUDH VBAUDRATE / 256
#define BAUDL VBAUDRATE % 256

void UARTInit(void);
volatile unsigned char UARTGetChar(void);
int UARTPutChar(char c, FILE *stream);

#ifdef __cplusplus
}
#endif

#endif
