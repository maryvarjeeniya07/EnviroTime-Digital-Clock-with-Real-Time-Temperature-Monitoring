#include "type.h"
#include "delay.h"


void delay_ms(u32 DLYMS)
{
for(DLYMS*=12000;DLYMS>0;DLYMS--);
}

void delay_us(u32 DLYUS)
{
for(DLYUS*=12;DLYUS>0;DLYUS--);
}

void delay_s(u32 DLYS)
{
for(DLYS*=12000000;DLYS>0;DLYS--);
}
