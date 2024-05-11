//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//NGUYEN DINH PHU SU PHAM KY THUAT TP HCM
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//dinh nghia chan giao tiep, thu vien, cac lenh ds13b20      
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
#define  touch_pin pin_a5  
#include <touch.c>                              
#define  search_rom       0xf0
#define  read_rom         0x33
#define  match_rom        0x55    
#define  skip_rom         0xcc
#define  alarm_search     0xec
#define  read_scratchpad  0xbe 
#define  write_scratchpad 0x4e                               
#define  copy_scratchpad  0x48  
#define  convert_t        0x44 

//tu chon do phan giai
void ds18b20_khoi_tao_dpg(usi8 dpg)
{                         
   const unsigned int8 res[]={0x1f,0x3f,0x5f,0x7f}; 
   touch_present();
   touch_write_byte(skip_rom);      
   touch_write_byte(write_scratchpad);                     
   touch_write_byte(0x0);       
   touch_write_byte(0x0);    
   touch_write_byte(res[dpg-9]); //12 bit

   touch_present();   
   touch_write_byte(skip_rom);
   touch_write_byte(convert_t);     
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Thong bao khong co ds13b20      
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void ds18b20_no_ds18b() 
{   
   lcd_goto_xy(0,0);       
   lcd_data("NO DS18B20"); 
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham khoi tao ds13b20      
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void ds18b20_khoi_tao()
{                         
   touch_present();
   touch_write_byte(skip_rom);      
   touch_write_byte(write_scratchpad);                     
   touch_write_byte(0x0);       
   touch_write_byte(0x0);    
   touch_write_byte(0x7f); //12 bit

   touch_present();   
   touch_write_byte(skip_rom);
   touch_write_byte(convert_t);     
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//doc nhiet do tu ds13b20, tra ve nhiet do la 16 bit    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                                                 
unsigned int16 ds18b20_read_temp()                                        
{                                    
   unsigned int8  bl,bh;                                                             
   unsigned int16 w; 
   touch_write_byte(skip_rom);
   touch_write_byte(read_scratchpad);                 
   bl = touch_read_byte();
   bh = touch_read_byte();                             
   w  = make16(bh,bl);                                                          
                                                        
   touch_present();   
   touch_write_byte(skip_rom);
   touch_write_byte(convert_t); 
   return w;
}  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham doc ma ROM cua DS18b20 va hien thi tai hang x, cot y 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    
void ds18b20_doc_rom(usi8 x,y)  
{    
   unsigned int8 rom_code[8];       
   unsigned int8 xh,xl;
   signed int8 i;
   if(touch_present())
   {
      touch_write_byte(read_rom);                                                                            
      for(i=0;i<8;i++)                 
      rom_code[i] = touch_read_byte();                                 
      lcd_goto_xy(x,y);     
      for(i=7;i>-1;i--) 
      {
         xh=rom_code[i]/16;              
         if(xh>9) xh=xh+0x37;
         else     xh=xh+0x30;          
         xl=rom_code[i]%16;              
         if(xl>9) xl=xl+0x37;
         else     xl=xl+0x30;
                       
         lcd_data(xh);
         lcd_data(xl);         
      }        
   }
   else ds18b20_no_ds18b();     
}
