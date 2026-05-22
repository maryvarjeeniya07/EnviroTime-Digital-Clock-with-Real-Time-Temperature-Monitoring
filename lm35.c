#include "type.h"
#include "adc.h"

u32 Read_LM35_Temp(void)
{
    u32 adc_val;
    f32 voltage;
    u32 temp;

    adc_val = Read_ADC();

    voltage = (adc_val * 3.3) / 1023.0;
    temp = voltage * 100;

    return temp;
}
