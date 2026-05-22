/* ALARM.C */

#include "Intial.h"
#include <lpc21xx.h>
#include "lcd.h"
#include "rtc.h"
#include "lcd_defines.h"
#include "delay.h"
#include "type.h"

#define BUZZER_PIN 25

extern u32 alarm_hour, alarm_min;
extern u32 alarm_flag;

void alarm_time_setting(void)
{
    CmdLCD(CLEAR_LCD);
    StrLCD("ALARM HOUR");
    alarm_hour = get_hour_from_user();

    CmdLCD(CLEAR_LCD);
    StrLCD("ALARM MIN");
    alarm_min = get_min_from_user();

    CmdLCD(CLEAR_LCD);
    StrLCD("ALARM SAVED");
    delay_ms(1000);
    CmdLCD(CLEAR_LCD);
}

void check_alarm(void)
{
    s32 h, m, s;
    static u32 alarm_done = 0;

    GetRTCTimeInfo(&h, &m, &s);

    /* trigger only once */
    if((h == alarm_hour) &&
       (m == alarm_min) &&
       (alarm_done == 0))
    {
        alarm_flag = 1;

        IOSET0 = (1 << BUZZER_PIN);

        alarm_done = 1;
    }

    /* reset for next day/alarm */
    if((h != alarm_hour) || (m != alarm_min))
    {
        alarm_done = 0;
    }
}