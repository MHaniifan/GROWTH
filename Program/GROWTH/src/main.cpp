#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "analog.h"
#include "uart.h"
#include "millis.h"

#define BAUDRATE 9600
#define VBAUDRATE (F_CPU/((unsigned long) BAUDRATE*16)-1)
#define BAUDH VBAUDRATE / 256
#define BAUDL VBAUDRATE % 256

#define DHT_PORT PORTE
#define DHT_DDR  DDRE
#define DHT_PINR PINE
#define DHT_BIT  4

// Wait for a logical level on DHT pin, return timeout flag
static uint8_t wait_level(uint8_t level, uint16_t timeout) {
    uint16_t count = 0;
    while (((DHT_PINR >> DHT_BIT) & 1) != level) {
        _delay_us(1);
        if (++count > timeout) return 1;
    }
    return 0;
}

// Read raw bits from DHT11
uint8_t dht11_read(uint8_t *humi, uint8_t *temp) {
    uint8_t data[5] = {0};

    // Start signal: pull low >18ms
    DHT_DDR |= (1 << DHT_BIT);       // output
    DHT_PORT &= ~(1 << DHT_BIT);     // drive low
    _delay_ms(20);

    // Release and switch to input
    DHT_DDR &= ~(1 << DHT_BIT);      // input
    DHT_PORT &= ~(1 << DHT_BIT);     // disable pull-up
    _delay_us(30);

    // Sensor response: low ~80us
    if (wait_level(0, 100)) return 1;
    // then high ~80us
    if (wait_level(1, 100)) return 2;

    // Read 40 bits
    for (uint8_t i = 0; i < 40; i++) {
        // Wait for start of bit (low ~50us)
        if (wait_level(0, 100)) return 3;
        // Wait for high and measure length
        uint16_t count = 0;
        while (((DHT_PINR >> DHT_BIT) & 1) == 0) ;
        while (((DHT_PINR >> DHT_BIT) & 1) == 1) {
            _delay_us(1);
            count++;
            if (count > 100) break;
        }
        // If high lasted >40us, bit is 1
        data[i/8] <<= 1;
        if (count > 40) data[i/8] |= 1;
    }

    // Checksum
    uint8_t sum = data[0] + data[1] + data[2] + data[3];
    if (sum != data[4]) return 4;

    *humi = data[0];
    *temp = data[2];
    return 0;
}

unsigned int dataADC = 0;
float kelembaban = 0;
char str[50];
uint8_t humidity = 0, temperature = 0;

int main(void){
  DDRB|=(1<<DDB6);
  DDRB|=(1<<DDB5);
  UARTInit();
  ADCInit();
  // millis_init(16000000);
  // millis_t lastTime = 0;
  stdout = fdevopen(UARTPutChar, NULL);
  while(1){
    dht11_read(&humidity, &temperature);
    dataADC = ADCIN(0);
    kelembaban = ((1023.0f - dataADC) * 100.0f) / 1023.0f;
    dtostrf(kelembaban, 4, 2, str);
    // printf("ADC = %d, Kelembaban = %s V\r\n", dataADC, str);
    printf("Kelembaban Tanah = %s, Kelembaban Udara = %d, Suhu = %d °C\r\n", str, humidity, temperature);
    if (kelembaban < 20){
      PORTB |= (1<<PB6);
    } else {
      PORTB &= ~(1<<PB6);
    }
    if (temperature > 30){
      PORTB |= (1<<PB5);
    } else {
      PORTB &= ~(1<<PB5);
    }
    // if((millis_t)(millis_get() - lastTime) > 5000){
    //   PORTB ^=(1<<7);
	  //   lastTime = millis_get();
	  // }
  }
  return 0;
}