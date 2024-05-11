#include <tv_pic_16f887_define_dth.c>
#include <tv_lcd_20x4_dth.c>
#include <tv_ds1307_dth.c>
#include <tv_hienthi_ds1307_lcd_dth.c>
#include <tv_chinh_thoigian_dth.c>
#include <tv_lm35_dth.c>
us8 bdn;
#int_timer1
void interrupt_timer1()
{
   bdn++;
   set_timer1(3036);
}
void hienthi_nhietdo()
{
   lm35_doc_nhiet_do(100);
   lcd_goto(0,0);
   printf(lcd_data, "NHIET DO:    %02LU.%02LU", lm35_ng, lm35_tp);
   lcd_data(223);
   lcd_data('C');
}

void main()
{
   calender_setup();
   setup_timer_1(t1_internal|t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   bdn=0; gt_mod=0; 
   lcd_setup();
   lcd_soto_setup();
   ds1307_setup();
   hienthi_lcd_all();
   while(true)
   {
           hienthi_nhietdo();
           phim_up_chinh();
           phim_dw_chinh();
           phim_mod_chinh();
           lcd_goto(3,13);
           lcd_data(0x30+gt_mod);

           if(gt_mod==0)
           ds1307_thoi_gian(8);
           hienthi_lcd_all();
      }
     
   }
}
