#include "type.h"
#include "delay.h"
#include "lcd.h"
#include "Intial.h"
#include "rtc.h"
#include "kpm.h"
#include "lcd_defines.h"

extern u32 h,mi,s,d,mo,y,da;
void edit_rtc_settings(void)
{
    u32 choice;

    while(1)
    {
        choice = rtc_edit_menu();
        if(choice == 7)
        {
                while(ColScan()==0);
                delay_ms(150);

                SetRTCTimeInfo(h,mi,s);
                SetRTCDateInfo(da,mo,y);
                SetRTCDay(d);

                CmdLCD(CLEAR_LCD);
                StrLCD("RTC UPDATED");
                delay_ms(600);
                CmdLCD(CLEAR_LCD);

                display_envirotime();
                delay_ms(800);
                return;
        }


        switch(choice)
        {
            case 0: set_rtc_hour(&h);      break;
            case 1: set_rtc_minute(&mi);   break;
            case 2: set_rtc_second(&s);    break;
            case 3: set_rtc_day(&d);       break;
            case 4: set_rtc_date(&da);     break;
            case 5: set_rtc_month(&mo);    break;
            case 6: set_rtc_year(&y);      break;
        }
    }
} 
u32 rtc_edit_menu(void)
{
    char menu[][15]={"1.HOUR","2.Minute","3.Second" ,"4.Day","5.Date","6.Month","7.Year","8.Exit"};
    u32 selected = 0;
    char key;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD(menu[selected]);
                                delay_ms(200);
        key = KeyScan();

        if(key == 'U')
        {
            if(selected == 0)
                selected = 7;
            else
                selected--;
        }
        else if(key == 'D')
        {
            if(selected == 7)
                selected = 0;
            else
                selected++;
        }
        else if(key == 'S')
        {
            return selected;
        }
    }
}

void set_rtc_hour(u32 *h)
{
    u32 temp;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        delay_ms(500);
        StrLCD("Enter Hour 0-23");

        temp = get_number_from_keypad();

        if(temp <= 23)
      {
            *h=temp;
            CmdLCD(CLEAR_LCD);
            delay_ms(2);
            StrLCD("HOUR UPDATED");
            delay_ms(600);
            return;
        }

        CmdLCD(CLEAR_LCD);
        StrLCD("Invalid Hour!");
        delay_ms(600);
    }
}

void set_rtc_minute(u32 *mi)
{
    u32 temp;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
         delay_ms(500);
        StrLCD("Enter Min 0-59");

        temp = get_number_from_keypad();

        if(temp <= 59)
        {
            *mi=temp;
            CmdLCD(CLEAR_LCD);
            delay_ms(2);
            StrLCD("MIN UPDATED");
            delay_ms(600);
            return;
        }

        CmdLCD(CLEAR_LCD);
        StrLCD("Invalid Minute!");
        delay_ms(600);
    }
} void set_rtc_second(u32 *s)
{
    u32 temp;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        delay_ms(500);
        StrLCD("Enter Sec 0-59");

        temp = get_number_from_keypad();

        if(temp<= 59)
        {
            *s=temp;
            CmdLCD(CLEAR_LCD);
            delay_ms(2);
            StrLCD("SEC UPDATED");
            delay_ms(600);
            return;
        }

        CmdLCD(CLEAR_LCD);
        StrLCD("Invalid Second!");
        delay_ms(600);
    }
}

void set_rtc_day(u32 *d)
{
    u32 temp;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        delay_ms(500);
        StrLCD("Day 0-6:");

        temp = get_number_from_keypad();

        if(temp <= 6)
        {
            *d=temp;
            CmdLCD(CLEAR_LCD);
            delay_ms(2);
            StrLCD("DAY UPDATED");
            delay_ms(600);
            return;
        }

        CmdLCD(CLEAR_LCD);
        StrLCD("Invalid Day!");
        delay_ms(600);
    }
}

void set_rtc_year(u32 *y)
{
    char yr[5];
    u32 index;
    u32 temp;
    char key;
    int i;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        delay_ms(200);
        StrLCD("YEAR 2000-2099");

        index = 0;
        for(i = 0; i < 5; i++)
            yr[i] = 0;

        CmdLCD(GOTO_LINE2_POS0);

        while(1)
        {
            key = KeyScan(); 
         if(key==0)
                continue;
            if(key >= '0' && key <= '9')
            {
                if(index < 4)
                {
                    yr[index] = key;
                    CharLCD(key);
                    index++;
                }
            }

            else if(key == 'B')
            {
                if(index > 0)
                {
                    index--;
                    yr[index] = 0;
                    CmdLCD(GOTO_LINE2_POS0 + index);
                    CharLCD(' ');
                    CmdLCD(GOTO_LINE2_POS0 + index);
                }
            }

            else if(key == 'S')
            {
                if(index == 4)
                    break;
            }

            delay_ms(150);
        }

        temp = (yr[0]-'0')*1000 +
               (yr[1]-'0')*100 +
               (yr[2]-'0')*10 +
               (yr[3]-'0');

        if(temp >= 2000 && temp <= 2099) 
        {
            *y = temp;
            CmdLCD(CLEAR_LCD);
            StrLCD("YEAR UPDATED");
            delay_ms(600);
            CmdLCD(CLEAR_LCD);
            return;
        }
        else
        {
            CmdLCD(CLEAR_LCD);
            StrLCD("Invalid Year!");
            delay_ms(700);
        }
    }
}


void set_rtc_month(u32 * mo)
{
    u32 temp;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        delay_ms(500);
        StrLCD("Month 1-12:");

        temp = get_number_from_keypad();

        if(temp >= 1 && temp <= 12)
        {
            *mo=temp;
            CmdLCD(CLEAR_LCD);
            delay_ms(2);
            StrLCD("MONTH UPDATED");
            delay_ms(500);
            return;
        }

        CmdLCD(CLEAR_LCD);
        StrLCD("Invalid Month!");
        delay_ms(500);
    }
}
u32 days_in_month(u32 month, u32 year)
{
    switch(month)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;

        case 4: case 6: case 9: case 11:
            return 30;

        case 2:
            // leap year check
            if( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) )
                return 29;
            else
                return 28;

        default:
            return 31;
    }
}

void set_rtc_date(u32 *da)
{
    u32 tmp, max_days;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        delay_ms(500);
        StrLCD("Enter Date (1-31)");
        CmdLCD(GOTO_LINE2_POS0);

        tmp = get_number_from_keypad();


        max_days = days_in_month(mo, y);

        if(tmp >= 1 && tmp <= max_days)
        {
            *da = tmp;
            CmdLCD(CLEAR_LCD);
            StrLCD("DATE UPDATED");
            delay_ms(600);
            return;
        }

        CmdLCD(CLEAR_LCD);
        StrLCD("Invalid Date!");
        delay_ms(600);    
		}
	}
