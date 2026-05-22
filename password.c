#include "lcd.h"
#include "type.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "delay.h"
#include<string.h>

#define PASSWORD_LENGTH 4
s8 default_password[PASSWORD_LENGTH+1]="1234";

u32 password(void)
{
        s8 entered[PASSWORD_LENGTH+1],key;
        u32 i=0;

        CmdLCD(CLEAR_LCD);
        delay_ms(2);
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD("Enter Password:");
        delay_ms(100);
        clear_line2();
        CmdLCD(GOTO_LINE2_POS0);
        while(i < PASSWORD_LENGTH)
        {
                key = KeyScan();
                if(key == 'B')
                {
                    if(i>0)
                     {
                        i--; // reduce count
                        entered[i]='\0'; // remove last char
                        CmdLCD(GOTO_LINE2_POS0+i); // move cursor back 1 position
                        CharLCD(' '); // overwrite previous * with space
                        CmdLCD(GOTO_LINE2_POS0+i);
                     }
                }
                else
                {
                        entered[i] = key;
                        CharLCD(entered[i]);
                        delay_ms(150);
                        CmdLCD(GOTO_LINE2_POS0+i);
                        CharLCD('*');
                        i++;
                }
                delay_ms(300);
        }
        entered[i]='\0';

        if(strcmp(entered,default_password)==0)
        {
                CmdLCD(CLEAR_LCD);
                delay_ms(2);
                StrLCD("ACCEPTED");
                delay_ms(1000);
                CmdLCD(CLEAR_LCD);
                delay_ms(2);
                return 1;
        }
        else
        {
                CmdLCD(CLEAR_LCD);
                delay_ms(2);
                StrLCD("Invalid password");
                delay_ms(1000);
                CmdLCD(CLEAR_LCD);
                delay_ms(2);
                return 0;
        }

} 
