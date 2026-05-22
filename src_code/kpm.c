#include "kpm_defines.h"
#include "type.h"
#include <lpc21xx.h>
#include "delay.h"

u32 kpmLUT[4][4]={
    {'7','8','9','U'},
    {'4','5','6','D'},
    {'1','2','3','C'},
    {'B','0','S','A'}
};

void Init_kpm(void)
{
    IODIR1 |= 15 << ROW0;      // rows output
    IODIR1 &= ~(15 << COL0);   // cols input

    IOCLR1 = 15 << ROW0;       // all rows low
}

u32 ColScan(void)
{
    if(((IOPIN1 >> COL0) & 15) < 15)
    {
        return 0;   // key pressed
    }
    else
    {
        return 1;   // no key pressed
    }
}

u32 RowCheck(void)
{
    u32 r;

    for(r=0; r<4; r++)
    {
        IOSET1 = 15 << ROW0;          // all rows high
        IOCLR1 = 1 << (ROW0 + r);     // selected row low

        delay_ms(1);

        if(ColScan() == 0)
            break;
    }

    IOCLR1 = 15 << ROW0;              // rows back low

    return r;
}

u32 ColCheck(void)
{
    u32 c;

    for(c=0; c<4; c++)
    {
        if(((IOPIN1 >> (COL0+c)) & 1) == 0)
            break;
    }

    return c;
}

u32 KeyScan(void)
{
    u32 r,c,key;

    Init_kpm();

    while(ColScan());        // wait for key press

    delay_ms(20);

    r = RowCheck();
    c = ColCheck();

    key = kpmLUT[r][c];

    while(ColScan() == 0);   // wait for release

    delay_ms(20);

    return key;
}