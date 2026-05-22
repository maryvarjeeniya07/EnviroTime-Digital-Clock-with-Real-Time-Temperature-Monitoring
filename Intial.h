#ifndef INITAL_H
#define INITAL_H

#include "type.h"

void Init_system(void);
void process_edit_menu(void);

void display_envirotime(void);

u32 password(void);
void update_password(s8 *);
void get_password_from_user(s8 *);

u32 open_edit_menu(void);

void alarm_time_setting(void);
void check_alarm(void);

void edit_rtc_settings(void);

u32 rtc_edit_menu(void);

void set_rtc_hour(u32 *);
void set_rtc_minute(u32 *);
void set_rtc_second(u32 *);

void set_rtc_day(u32 *);
void set_rtc_date(u32 *);
void set_rtc_month(u32 *);
void set_rtc_year(u32 *);

u32 days_in_month(u32,u32);

u32 get_number_from_keypad(void);
u32 get_hour_from_user(void);
u32 get_min_from_user(void);

u32 select_time_edit_option(void);

#endif

