#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"
#include "lm35.h"

void display_envirotime(void)
{
    s32 hour, min, sec;
    s32 date, month, year;
    s32 day;
    u32 temp;

    GetRTCTimeInfo(&hour, &min, &sec);
    GetRTCDateInfo(&date, &month, &year);
    GetRTCDay(&day);

    temp = Read_LM35_Temp();

    /******** LINE 1: HH:MM:SS T:27C ********/
    CmdLCD(GOTO_LINE1_POS0);

    DisplayRTCTime(hour, min, sec);

    CmdLCD(GOTO_LINE1_POS0 + 9);
    StrLCD("T:");

    if(temp < 10)
    {
        CharLCD('0');
        CharLCD(temp + '0');
    }
    else
    {
        CharLCD((temp / 10) + '0');
        CharLCD((temp % 10) + '0');
    }

    CharLCD(0xDF);
    CharLCD('C');

    /******** LINE 2: DD/MM/YYYY WED ********/
    CmdLCD(GOTO_LINE2_POS0);

    DisplayRTCDate(date, month, year);

    CmdLCD(GOTO_LINE2_POS0 + 11);

    DisplayRTCDay(day);
}