#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "analog.h"
#include "uart.h"
#include "millis.h"

#define BAUDRATE 9600
#define VBAUDRATE (F_CPU / ((unsigned long)BAUDRATE * 16) - 1)
#define BAUDH VBAUDRATE / 256
#define BAUDL VBAUDRATE % 256

#define DHT_PORT PORTE
#define DHT_DDR DDRE
#define DHT_PINR PINE
#define DHT_BIT 4

// Wait for a logical level on DHT pin, return timeout flag
static uint8_t wait_level(uint8_t level, uint16_t timeout)
{
  uint16_t count = 0;
  while (((DHT_PINR >> DHT_BIT) & 1) != level)
  {
    _delay_us(1);
    if (++count > timeout)
      return 1;
  }
  return 0;
}

// Read raw bits from DHT11
uint8_t dht11_read(uint8_t *humi, uint8_t *temp)
{
  uint8_t data[5] = {0};

  // Start signal: pull low >18ms
  DHT_DDR |= (1 << DHT_BIT);   // output
  DHT_PORT &= ~(1 << DHT_BIT); // drive low
  _delay_ms(20);

  // Release and switch to input
  DHT_DDR &= ~(1 << DHT_BIT);  // input
  DHT_PORT &= ~(1 << DHT_BIT); // disable pull-up
  _delay_us(30);

  // Sensor response: low ~80us
  if (wait_level(0, 100))
    return 1;
  // then high ~80us
  if (wait_level(1, 100))
    return 2;

  // Read 40 bits
  for (uint8_t i = 0; i < 40; i++)
  {
    // Wait for start of bit (low ~50us)
    if (wait_level(0, 100))
      return 3;
    // Wait for high and measure length
    uint16_t count = 0;
    while (((DHT_PINR >> DHT_BIT) & 1) == 0)
      ;
    while (((DHT_PINR >> DHT_BIT) & 1) == 1)
    {
      _delay_us(1);
      count++;
      if (count > 100)
        break;
    }
    // If high lasted >40us, bit is 1
    data[i / 8] <<= 1;
    if (count > 40)
      data[i / 8] |= 1;
  }

  // Checksum
  uint8_t sum = data[0] + data[1] + data[2] + data[3];
  if (sum != data[4])
    return 4;

  *humi = data[0];
  *temp = data[2];
  return 0;
}

unsigned int dataADC = 0;
float kelembaban = 0;
char str[50];
uint8_t humidity = 0, temperature = 0;
bool pump = 0, fan = 0;

int main(void)
{
  DDRB |= (1 << DDB6); // Output untuk indikator kelembaban tanah
  DDRB |= (1 << DDB5); // Output untuk indikator suhu

  UARTInit();
  ADCInit();
  millis_init(F_CPU); // Aktifkan timer millis

  stdout = fdevopen(UARTPutChar, NULL);

  uint8_t humidity = 0, temperature = 0;
  unsigned int dataADC = 0;
  float kelembaban = 0;
  char str[50];

  millis_t lastSendTime = millis_get(); // Waktu pengiriman terakhir

  while (1)
  {
    // Cek apakah sudah lewat 500ms sejak terakhir kirim
    if ((millis_t)(millis_get() - lastSendTime) >= 500)
    {
      dht11_read(&humidity, &temperature); // Baca sensor DHT11
      dataADC = ADCIN(0);                  // Baca ADC
      kelembaban = ((1023.0f - dataADC) * 100.0f) / 1023.0f;
      dtostrf(kelembaban, 4, 2, str);

      // Kirim data via UART
      // printf("ADC = %d, Kelembaban = %s%%\r\n", dataADC, str);
      printf("Kelembaban Tanah = %s, Kelembaban Udara = %d, Suhu = %d, Pump = %d, Fan = %d\r\n",str, humidity, temperature, (int)pump, (int)fan);

      // Update waktu terakhir pengiriman
      lastSendTime = millis_get();

      // Logika kontrol sederhana
      if (kelembaban < 20)
      {
        PORTB |= (1 << PB6); // Nyalakan LED/Pompa jika kelembaban rendah
        pump = 1;
      }
      else
      {
        PORTB &= ~(1 << PB6);
        pump = 0;
      }

      if (temperature > 30)
      {
        PORTB |= (1 << PB5); // Nyalakan kipas/pendingin jika panas
        fan = 1;
      }
      else
      {
        PORTB &= ~(1 << PB5);
        fan = 0;
      }
    }

    // Di sini bisa tambahkan tugas lain yang non-blocking
  }

  return 0;
}