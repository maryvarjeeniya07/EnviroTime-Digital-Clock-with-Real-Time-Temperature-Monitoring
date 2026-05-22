#include <string.h>
#include "lcd.h"
#include "type.h"
#include "lcd_defines.h"
#include "delay.h"
#include "kpm.h"

char menu[4][16]={
    "1.EDIT RTC",
    "2.SET ALARM",
    "3.UPDATE PIN",
    "4.EXIT"
};

u32 open_edit_menu(void)
{
    u32 index=0;
    char key;

    while(1)
    {
        CmdLCD(CLEAR_LCD);

        StrLCD(menu[index]);

        key=KeyScan();

//delay_ms(200);
        if(key=='U')
        {
            if(index==0)
                index=3;
            else
                index--;
        }
        else if(key=='D')
        {
            if(index==3)
                index=0;
            else
                index++;
        }
        else if(key=='S')
        {
            return index;
        }
    }
}