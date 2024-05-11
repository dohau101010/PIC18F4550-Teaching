#include <tv_kit_vdk_pic_all.c>
#include <math.h>
unsigned int8 mp, sp, gh, hsc;
int1 tt_rs;
void lcd_display()
{
   lcd_goto_xy(0,0);
   lcd_data(" TT VDK PIC 18F4550 ");
   lcd_goto_xy(1,0);
   printf(lcd_data, "HS CHIA:%1u GH DEM:%3u", hsc, gh);
   lcd_goto_xy(2,10);
   printf(lcd_data, "GT DEM: %02u", sp);
   lcd_goto_xy(3,0);
   lcd_data(" TRUONG DAI HOC SPKT");
}
void hsc_check()
{
   if(hsc == 1) setup_timer_0(t0_ext_l_to_h|t0_div_1);
   if(hsc == 2) setup_timer_0(t0_ext_l_to_h|t0_div_2);
   if(hsc == 4) setup_timer_0(t0_ext_l_to_h|t0_div_4);
   if(hsc == 8) setup_timer_0(t0_ext_l_to_h|t0_div_8);
}
void hsc_key()
{
   if(mp < 4) hsc = pow(2, mp);
   hsc_check();
}
void gh_key()
{
   if(mp == 0x0c) gh = 40;
   if(mp == 0x0d) gh = 60;
   if(mp == 0x0e) gh = 80;
   if(mp == 0x0f) gh = 100;
}
void stop_display()
{
   xuat_32led_don_1dw(0);
   lcd_goto_xy(2,0);
   lcd_data("TT:STOP");
}
void run_display()
{
   xuat_32led_don_1dw(0xffffffff);
   lcd_goto_xy(2,0);
   lcd_data("TT:RUN ");
}
void rs_key()
{
   if(mp == 0x0a) 
   {
      tt_rs = ~tt_rs;
      if(tt_rs)  
      {
         hsc_check();
         run_display();
      }
      else       
      {
         setup_timer_0(t0_off);
         stop_display();
      }
   }
}
void main()
{
   set_up_port();
   lcd_setup();
   setup_timer_0(t0_ext_l_to_h|t0_div_1);
   set_timer1(0);
   setup_timer_0(t0_off);
   sp = 0; tt_rs = 0; 
   hsc = 1; gh = 40;
   lcd_display();
   stop_display();
   while(true)
   {
      sp = get_timer0();
      if(sp == gh) set_timer0(0);
      mp = key_4x4_dw();
      if(mp!=0xff)
      {
        hsc_key();
        gh_key();
        rs_key();
      }
      lcd_display();
   }
}
