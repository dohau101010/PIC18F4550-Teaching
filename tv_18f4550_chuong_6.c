#include <18f4550.h>
#fuses   nowdt,put,hs,noprotect,nolvp,cpudiv1,NOUSBDIV,    
#use     delay(clock=20000000)     
//*******************************************************
#define  rs     pin_b0
#define  hs     pin_b1
#define  gh_u   pin_b2
#define  gh_d   pin_b3
//*********************************************************
#define lcd_rs       pin_e2
#define lcd_rw       pin_e1
#define lcd_e        pin_e0

#define output_lcd   output_d

#define function_set          0x38 
#define display_control       0x0c
#define clear_display         0x01
#define entry_mode            0x06
#define shift_left            0x18
#define shift_right           0x1c
#define line1                 0x80
#define line2                 0xc0

#define line3                 0x94
#define line4                 0xd4

void lcd_command(unsigned char mdk) 
{ 
    output_low(lcd_rs); 
    output_lcd(mdk);
    output_high(lcd_e);
    delay_us(200);
    output_low(lcd_e); 
    delay_us(200);
}
void lcd_data(unsigned char mht) //rs = 1
{ 
    output_high(lcd_rs); 
    output_lcd(mht);
    output_high(lcd_e); 
    delay_us(20);
    output_low(lcd_e);
    delay_us(20);
}
void lcd_setup()
{ 
    output_low(lcd_e); 
    output_low(lcd_rs); 
    output_low(lcd_rw);
    lcd_command(function_set); 
    delay_ms(1);
    lcd_command(display_control);
    lcd_command(clear_display); 
    delay_ms(2);
    lcd_command(entry_mode);
}
void lcd_goto_xy(unsigned int8 x,unsigned int8 y) 
{                      
   const unsigned int8 lcd_vitri[]={0x80,0xc0,0x94,0xd4};
   lcd_command(lcd_vitri[x]+y);    //delay_us(20);
} 
//***********************************************************
int1 phim_cd(int1 pin)   
{                    
   if (!input(pin))   
   {        
      delay_ms(20);                                     
      if (!input(pin))
      {
         while(!input(pin));
         return 1;
      }                      
      return 0;  
   }         
  return 0;
}  

