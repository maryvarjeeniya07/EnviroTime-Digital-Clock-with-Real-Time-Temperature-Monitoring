#include "rtc.h"
#include "lcd.h"

u32 time_limit(u32 sh, u32 sm, u32 eh, u32 em)
{
    s32 cur_h, cur_m, cur_s;
    u32 cur_total, start_total, end_total;
    GetRTCTimeInfo(&cur_h, &cur_m, &cur_s);

    cur_total   = cur_h * 60 + cur_m;
    start_total = sh   * 60 + sm;
    end_total   = eh   * 60 + em;
    if(start_total < end_total)
    {
        if(cur_total >= start_total && cur_total <= end_total)
            return 1;
        else
            return 0;
    }
    else
    {
        if(cur_total >= start_total || cur_total <= end_total)
            return 1;
        else
            return 0;
    }
}
