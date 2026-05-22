#ifndef _LCD_H_
 #define _LCD_H_

 #include "type.h"
 void Init_LCD(void);
 void CmdLCD(u8 CmdByte);
 void CharLCD(u8 asciiVal);
 void WriteLCD(u8 byte);
 void U32LCD(u32);
 void StrLCD(s8 *);
 void S32LCD(s32);
 void F32LCD(f32,u32);
 void BuildCGRAM(u8 *,u8);
 void clear_line2(void);

 #endif 
