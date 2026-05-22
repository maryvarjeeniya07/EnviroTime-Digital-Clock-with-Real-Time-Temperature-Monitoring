#include "lcd.h"
#include "type.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "delay.h"
#include <string.h>
#include "Intial.h"

#define PASSWORD_LENGTH 4
extern s8 default_password[PASSWORD_LENGTH+1];

void update_password(s8 *saved_pass)
{
    s8 old_entered[5];
    s8 new_password[5];
    s8 confirm_password[5];

    //ASK OLD PASSWORD
    CmdLCD(CLEAR_LCD);
    delay_ms(2);
    StrLCD("ENTER OLD PASSWORD");
                delay_ms(200);
    CmdLCD(GOTO_LINE2_POS0);

    get_password_from_user(old_entered);

    if(strcmp(old_entered, saved_pass) != 0)
    {
        CmdLCD(CLEAR_LCD);
        delay_ms(2);
        StrLCD("WRONG PASSWORD");
        delay_ms(800);
        return;     // exit without update
    }

    //ENTER NEW PASSWORD
    CmdLCD(CLEAR_LCD);
    delay_ms(2);
    StrLCD("ENTER NEW PASSWORD");
    CmdLCD(GOTO_LINE2_POS0);

    get_password_from_user(new_password);

    //CONFIRM PASSWORD
    CmdLCD(CLEAR_LCD);
    delay_ms(2);
    StrLCD("CONFIRM NEW PASSWORD");
    CmdLCD(GOTO_LINE2_POS0);

    get_password_from_user(confirm_password);
    if(strcmp(new_password, confirm_password) == 0)
    {
        strcpy(default_password, new_password);   // update global password

        CmdLCD(CLEAR_LCD);
        StrLCD("PASSWORD UPDATED");
        delay_ms(800);
                CmdLCD(0x01);
    }
    else
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("PASSWORD MISMATCH");
        delay_ms(800);
    }
}
void get_password_from_user(s8 *buffer)
{
    s8 key;
    u32 i = 0;

    CmdLCD(GOTO_LINE2_POS0);

    while(i < PASSWORD_LENGTH)
    {
        key = KeyScan();

        if(key >= '0' && key <= '9')
        {
            buffer[i] = key;

            CharLCD('*');

            i++;
        }
        else if(key == 'B')
        {
            if(i > 0)
            {
                i--;
                buffer[i] = '\0';

                CmdLCD(GOTO_LINE2_POS0 + i);
                CharLCD(' ');
                CmdLCD(GOTO_LINE2_POS0 + i);
            }
        }

        delay_ms(200);
    }

    buffer[i] = '\0';
}