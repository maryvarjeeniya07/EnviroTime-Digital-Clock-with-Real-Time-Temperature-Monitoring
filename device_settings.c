#include "kpm.h"
#include "lcd.h"
#include "delay.h"
#include "type.h"
#include "lcd_defines.h"

u32 get_number_from_keypad(void)
{
    char buf[3] = {0,0,0};
    char key;
    u32 value = 0;
    int pos = 0;

    CmdLCD(GOTO_LINE2_POS0);

    while(1)
    {
        key = KeyScan();
        delay_ms(120);

        if(key >= '0' && key <= '9')
        {
            if(pos < 2)
            {
                buf[pos] = key;
                CmdLCD(GOTO_LINE2_POS0 + pos);
                CharLCD(key);
                pos++;
            }
        }
        else if(key == 'B')
        {
            if(pos > 0)
            {
                pos--;
                buf[pos] = '\0';
                CmdLCD(GOTO_LINE2_POS0 + pos);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0 + pos);
            }
        }
        else if(key == 'S')
        {
            if(pos == 1)
            {
                value = buf[0] - '0';
                return value;
            }
            else if(pos == 2)
            {
                value = ((buf[0]-'0') * 10) + (buf[1]-'0');
                return value;
            }
        }
    }
}

u32 get_hour_from_user(void)
{
    u32 h;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        delay_ms(300);
        StrLCD("Enter Hour 0-23");

        h = get_number_from_keypad();

        if(h <= 23)
            return h;

        CmdLCD(CLEAR_LCD);
        StrLCD("Invalid Hour!");
        delay_ms(1000);
    }
}

u32 get_min_from_user(void)
{
    u32 m;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        delay_ms(300);
        StrLCD("Enter Min 0-59");

        m = get_number_from_keypad();

        if(m <= 59)
            return m;

        CmdLCD(CLEAR_LCD);
        StrLCD("Invalid Minute!");
        delay_ms(800);
    }
}

u32 select_time_edit_option(void)
{
    char opt[][16] = {
        "1.HOUR",
        "2.MINUTE",
        "3.HOUR+MIN",
        "4.EXIT"
    };

    u32 s = 0;
    char key;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD(opt[s]);
        delay_ms(200);

        key = KeyScan();

        if(key == 'U')
        {
            if(s == 0)
                s = 3;
            else
                s--;
        }
        else if(key == 'D')
        {
            if(s == 3)
                s = 0;
            else
                s++;
        }
        else if(key == 'S')
        {
            return s;
        }
    }
}
