#include <lpc21xx.h>

#include "type.h"
#include "kpm.h"
#include "lcd.h"
#include "rtc.h"
#include "lcd_defines.h"
#include "kpm_defines.h"
#include "Intial.h"
#include "delay.h"
#include "adc.h"
#include "lm35.h"

#define BUZZER_PIN      25
#define EDIT_SW         0
#define ALARM_STOP_SW   1

extern s8 default_password[5];

u32 h = 12;
u32 mi = 30;
u32 s = 0;

u32 d = 3;
u32 mo = 5;
u32 y = 2026;
u32 da = 1;

u32 alarm_hour = 12;
u32 alarm_min  = 31;

u32 wrong_count = 0;
u32 alarm_flag = 0;

int main()
{
    Init_system();

    /* P0.25 as GPIO output for buzzer/LED */
    PINSEL1 &= ~(3 << 18);
    IODIR0  |=  (1 << BUZZER_PIN);

    CmdLCD(CLEAR_LCD);
    StrLCD("ENVIRO TIME");

    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("CLOCK & TEMP");

    delay_ms(1500);
    CmdLCD(CLEAR_LCD);

    while(1)
    {
        display_envirotime();

        check_alarm();

        /******** EDIT SWITCH ********/
        if(((IOPIN0 >> EDIT_SW) & 1) == 0)
        {
            delay_ms(50);

            if(((IOPIN0 >> EDIT_SW) & 1) == 0)
            {
                while(((IOPIN0 >> EDIT_SW) & 1) == 0);

                if(wrong_count >= 3)
                {
                    u32 sec_count, beep;

                    /* buzzer beeps 3 times */
                    for(beep = 0; beep < 3; beep++)
                    {
                        IOSET0 = 1 << BUZZER_PIN;
                        delay_ms(200);

                        IOCLR0 = 1 << BUZZER_PIN;
                        delay_ms(200);
                    }

                    CmdLCD(CLEAR_LCD);
                    delay_ms(5);

                    CmdLCD(GOTO_LINE1_POS0);
                    StrLCD("SYSTEM LOCKED");

                    for(sec_count = 45; sec_count > 0; sec_count--)
                    {
                        CmdLCD(GOTO_LINE2_POS0);
                        StrLCD("WAIT: ");

                        CharLCD((sec_count / 10) + '0');
                        CharLCD((sec_count % 10) + '0');

                        StrLCD(" SEC   ");

                        delay_ms(1000);
                    }

                    wrong_count = 0;

                    CmdLCD(CLEAR_LCD);
                    delay_ms(5);

                    continue;
                }

                if(password())
                {
                    wrong_count = 0;
                    process_edit_menu();
                }
                else
                {
                    wrong_count++;

                    CmdLCD(CLEAR_LCD);
                    StrLCD("ACCESS DENIED");
                    delay_ms(500);

                    IOSET0 = 1 << BUZZER_PIN;
                    delay_ms(1000);
                    IOCLR0 = 1 << BUZZER_PIN;

                    CmdLCD(CLEAR_LCD);
                    delay_ms(5);
                }
            }
        }

        /******** ALARM STOP SWITCH ********/
        if(alarm_flag == 1 &&
           (((IOPIN0 >> ALARM_STOP_SW) & 1) == 0))
        {
            IOCLR0 = 1 << BUZZER_PIN;
            alarm_flag = 0;

            while(((IOPIN0 >> ALARM_STOP_SW) & 1) == 0);
        }

        delay_ms(200);
    }
}