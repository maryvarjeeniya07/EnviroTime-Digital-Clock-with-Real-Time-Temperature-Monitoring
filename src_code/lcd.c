#include <lpc21xx.h>

#include "type.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"

void WriteLCD(u8 byte)
{
    /******** RW = 0 ********/
    IOCLR0 = 1 << LCD_RW;

    /******** CLEAR LCD DATA PINS P0.8-P0.15 ********/
    IOCLR0 = 0xFF << LCD_DATA;

    /******** WRITE DATA TO P0.8-P0.15 ********/
    IOSET0 = byte << LCD_DATA;

    /******** ENABLE PULSE ********/
    IOSET0 = 1 << LCD_EN;
    delay_us(1);
    IOCLR0 = 1 << LCD_EN;

    delay_ms(2);
}

void CmdLCD(u8 CmdByte)
{
    /******** RS = 0 FOR COMMAND ********/
    IOCLR0 = 1 << LCD_RS;

    WriteLCD(CmdByte);
}

void Init_LCD(void)
{
    /******** LCD DATA + CONTROL PINS AS OUTPUT ********/
    IODIR0 |= 0xFF << LCD_DATA;      // P0.8 to P0.15

    IODIR0 |= 1 << LCD_RS;

    IODIR0 |= 1 << LCD_RW;

    IODIR0 |= 1 << LCD_EN;

    delay_ms(15);

    CmdLCD(MODE_8BIT_1LINE);
    delay_us(4100);

    CmdLCD(MODE_8BIT_1LINE);
    delay_us(100);

    CmdLCD(MODE_8BIT_1LINE);

    CmdLCD(MODE_8BIT_2LINE);

    CmdLCD(DISP_ON_CUR_OFF);

    CmdLCD(CLEAR_LCD);

    CmdLCD(SHIFT_CUR_RIGHT);
}

void CharLCD(u8 asciiVal)
{
    /******** RS = 1 FOR DATA ********/
    IOSET0 = 1 << LCD_RS;

    WriteLCD(asciiVal);
}

void StrLCD(s8 *p)
{
    while(*p)
    {
        CharLCD(*p++);
    }
}

void U32LCD(u32 n)
{
    u8 digit[10];
    s32 i = 0;

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        while(n > 0)
        {
            digit[i++] = (n % 10) + '0';
            n = n / 10;
        }

        for(--i; i >= 0; i--)
        {
            CharLCD(digit[i]);
        }
    }
}

void S32LCD(s32 n)
{
    if(n < 0)
    {
        CharLCD('-');
        n = -n;
    }

    U32LCD(n);
}

void F32LCD(f32 fn,u32 nop)
{
    u32 n,i;

    if(fn < 0.0)
    {
        CharLCD('-');
        fn = -fn;
    }

    n = fn;

    U32LCD(n);

    CharLCD('.');

    for(i=0; i<nop; i++)
    {
        fn = (fn - n) * 10;
        n = fn;
        CharLCD(n + '0');
    }
}

void BuildCGRAM(u8 *p,u8 nBytes)
{
    u32 i;

    CmdLCD(GOTO_CGRAM_START);

    IOSET0 = 1 << LCD_RS;

    for(i=0; i<nBytes; i++)
    {
        WriteLCD(p[i]);
    }

    CmdLCD(GOTO_LINE1_POS0);
}

void clear_line2(void)
{
    CmdLCD(GOTO_LINE2_POS0);

    StrLCD("                ");

    CmdLCD(GOTO_LINE2_POS0);
}