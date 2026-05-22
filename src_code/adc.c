#include <lpc21xx.h>

#include "adc.h"

void Init_ADC(void)
{
    PINSEL1|=1<<24;

    ADCR=(1<<1)|
         (4<<8)|
         (1<<21);
}

u32 Read_ADC(void)
{
    ADCR|=1<<24;

    while(((ADDR>>31)&1)==0);

    return (ADDR>>6)&1023;
}