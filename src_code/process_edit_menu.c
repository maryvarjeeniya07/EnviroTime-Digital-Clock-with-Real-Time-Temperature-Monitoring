#include "Intial.h"

extern s8 default_password[5];

void process_edit_menu(void)
{
    u32 select;

    while(1)
    {
        select=open_edit_menu();

        if(select==3)
            return;

        switch(select)
        {
            case 0:
                edit_rtc_settings();
                break;

            case 1:
                alarm_time_setting();
                break;

            case 2:
                update_password(default_password);
                break;
        }
    }
}