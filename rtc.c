#include <lpc21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "type.h"

#define FOSC 12000000
#define CCLK (5 * FOSC)
#define PCLK (CCLK / 4)

#define PREINT_VAL  ((PCLK / 32768) - 1)
#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768))

#define RTC_ENABLE  (1 << 0)
#define RTC_RESET   (1 << 1)
#define RTC_CLKSRC  (1 << 4)

s8 week[][4] = {
    "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
};

void Init_RTC(void)
{
    PREINT = PREINT_VAL;
    PREFRAC = PREFRAC_VAL;

    CCR = RTC_RESET;     // reset RTC
    CCR = 0x00;          // release reset

    CCR = RTC_ENABLE;    // start RTC using PCLK
}

void SetRTCTimeInfo(u32 hour, u32 min, u32 sec)
{
    HOUR = hour;
    MIN = min;
    SEC = sec;
}

void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
    DOM = date;
    MONTH = month;
    YEAR = year;
}

void SetRTCDay(u32 day)
{
    DOW = day;
}

void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
    *hour = HOUR;
    *minute = MIN;
    *second = SEC;
}

void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
    *date = DOM;
    *month = MONTH;
    *year = YEAR;
}

void GetRTCDay(s32 *day)
{
    *day = DOW;
}

void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
    CharLCD((hour / 10) + '0');
    CharLCD((hour % 10) + '0');
    CharLCD(':');

    CharLCD((minute / 10) + '0');
    CharLCD((minute % 10) + '0');
    CharLCD(':');

    CharLCD((second / 10) + '0');
    CharLCD((second % 10) + '0');
}

void DisplayRTCDate(u32 date, u32 month, u32 year)
{
    CharLCD((date / 10) + '0');
    CharLCD((date % 10) + '0');
    CharLCD('/');

    CharLCD((month / 10) + '0');
    CharLCD((month % 10) + '0');
    CharLCD('/');

    U32LCD(year);
}

void DisplayRTCDay(u32 dow)
{
    if(dow <= 6)
    {
        StrLCD(week[dow]);
    }
    else
    {
        StrLCD("ERR");
    }
}