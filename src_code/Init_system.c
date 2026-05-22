#include <lpc21xx.h>

#include "Intial.h"
#include "lcd.h"
#include "rtc.h"
#include "kpm.h"
#include "adc.h"

#define BUZZER_PIN      25
#define EDIT_SW         0
#define ALARM_STOP_SW   1

extern u32 h,mi,s,d,mo,y,da;

void Init_system(void)
{
    PINSEL0 = 0;
    PINSEL1 = 0;

    Init_LCD();
    Init_RTC();
    Init_kpm();
    Init_ADC();

    /******** GPIO DIRECTIONS ********/
	
	IODIR0 |= 1 << BUZZER_PIN;   // P0.19 as output
  IOCLR0  = 1 << BUZZER_PIN;   // buzzer initially OFF


    IODIR0 &= ~(1 << EDIT_SW);       // edit switch input

    IODIR0 &= ~(1 << ALARM_STOP_SW); // alarm stop switch input

    SetRTCTimeInfo(h,mi,s);

    SetRTCDateInfo(da,mo,y);

    SetRTCDay(d);
}