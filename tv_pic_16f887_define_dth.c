#include <16f887.h>
#device adc=10
#fuses nowdt,put,hs,noprotect,nolvp
#use delay(clock=20M)
#use i2c(master,slow,sda=pin_c4,scl=pin_c3) 
#define s8      signed int8
#define us8     unsigned int8
#define s16     signed int16
#define us16    unsigned int16
#define s32     signed int32
#define us32    unsigned int32

#define up  pin_c5
#define dw  pin_c6
#define mod pin_c7

void calender_setup()
{
   set_tris_d(0);
   set_tris_e(0);
   set_tris_c(0xff);
   setup_adc(adc_clock_div_32);        
   setup_adc_ports(san0|vss_vdd); 
   set_adc_channel(0);
}
int1 phim_up()   
{                    
   if (!input(up))   
   {        
      delay_ms(200);                                     
      if (!input(up))
      {
         while(!input(up));
         return 1;      
      }                      
      return 0;   
   }         
  return 0;  
} 
int1 phim_dw()   
{                    
   if (!input(dw))   
   {        
      delay_ms(200);                                     
      if (!input(dw))
      {
         while(!input(dw));
         return 1;      
      }                      
      return 0;   
   }         
  return 0;  
} 
int1 phim_mod()   
{                    
   if (!input(mod))   
   {        
      delay_ms(20);                                     
      if (!input(mod))
      {
         while(!input(mod));
         return 1;      
      }                      
      return 0;   
   }         
  return 0;  
} 
