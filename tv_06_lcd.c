//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//NGUYEN DINH PHU SU PHAM KY THUAT TP HCM
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//dinh nghia bien dieu khien LCD va cac bit cua bien
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
unsigned int8 lcd_ctrl = 0xff;                     
#bit lcd_p  = lcd_ctrl.3                                       
#bit lcd_rs = lcd_ctrl.2
#bit lcd_rw = lcd_ctrl.1                                          
#bit lcd_e  = lcd_ctrl.0             
                                                           
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Dinh nghia cac lenh dieu khien cua LCD
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
#define lcd_clear_display      0x01    
#define lcd_cursor_home        0x02                                                                                 
//Lenh function set co nhieu bit lua chon
#define lcd_fs_function_set    0x20   //constant 
#define fs_8bit                0x10                
#define fs_2line               0x08
#define fs_5x10                0x04
//Lenh dieu khien hien thi 
#define lcd_dc_display_control 0x08  //constant
#define dc_display_on          0x04  
#define dc_cursor_on           0x02
#define dc_blink_on            0x01                                                          
//Lenh display entry mode */  
#define lcd_em_entry_mode      0x04  //constant 
#define em_shift_inc           0x01                      
#define em_left                0x02                                                

/* Flags for display/cursor shift */                           
#define lcd_cd_cursor_display  0x10   //constant              
#define cd_display_move        0x08
#define cd_move_right          0x04

#define lcd_shift_left         0x18 
#define lcd_shift_right        0x1C 

#define lcd_ddram_addr         0x80
#define lcd_cgram_addr         0x40
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
void lcd_goto_xy(usi8 x,usi8 y);
void lcd_xuat_8bit(int8 db);
void lcd_command(int8 db);
void lcd_data(int8 db);
void lcd_puts(usi8 x, usi8 y, char* str);                 
void lcd_setup();                                        
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 604: ham xuat 8bit ra lcd
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
void lcd_xuat(int8 db) 
{                                                     
   lcd_e=1; xuat_lcd(lcd_ctrl,db);   
   delay_us(20);                       
   lcd_e=0; xuat_lcd(lcd_ctrl,db);     
}                                                              
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    
//ham 605: ham xuat ma lenh dk lcd
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_command(int8 db)   
{
   lcd_rs = 0; lcd_xuat(db);                                       
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 606: ham xuat du lieu ra lcd
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_data(int8 db)       
{
   lcd_rs = 1; lcd_xuat(db);
}                                        
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 607: ham khoi tao lcd
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_setup()
{                     
   lcd_e  = 0;   lcd_rw = 0; 
   lcd_rs = 1;   lcd_p  = 0;
   lcd_command(lcd_fs_function_set|fs_8bit|fs_2line);         
   delay_us(40);  
   lcd_command(lcd_dc_display_control|dc_display_on);   
   delay_us(40);
   lcd_command(lcd_clear_display);      
   delay_ms(2);      
   lcd_command(lcd_em_entry_mode|em_left);       
   delay_us(40);                
}            
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 608: di chuyen con tro den toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_goto_xy(usi8 x,usi8 y) 
{                      
   const unsigned int8 lcd_vitri[]={0x80,0xc0,0x94,0xd4};
   lcd_command(lcd_vitri[x]+y);    //delay_us(20);
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx           
//ham 609: ham xoa man hinh LCD
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_clear() 
{                      
   lcd_command(lcd_clear_display);      
   delay_ms(2);
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 609: ham mo den backlight lcd 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
void lcd_back_light_on()
{
   lcd_p = 0; xuat_lcd(lcd_ctrl,0x00);   
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 610: tat den backlight lcd 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
void lcd_back_light_off()
{
   lcd_p = 1;  xuat_lcd(lcd_ctrl,0x00);    
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 611: hien thi mang trên lcd tai x,y (hang,cot)
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_puts(usi8 x, usi8 y, unsigned  char* str) 
{                 
   while (*str) 
   {
      if(y>=20) 
      {
         y = 0;   x++;
      }
      if(x>=4) x = 0;
      lcd_goto_xy(x,y);      
      if (*str == '\n') 
      {                   
         x++;
         lcd_goto_xy(x,y);
      } 
      else if (*str == '\r') 
      {
         lcd_goto_xy(0,y);
      } 
      else 
         {
            lcd_data(*str);
            y++;                      
            
         }
      str++;
   }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//mang so to cua LCD
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
const unsigned int8 lcd_so_to[10][6] ={
                  0,1,2,4,3,5,    // so 0
                  1,2,32,3,7,3,   // so 1
                  6,6,2,4,3,3,    // so 2
                  6,6,2,3,3,5,    // so 3
                  7,3,7,32,32,7,  // so 4
                  7,6,6,3,3,5,    // so 5                               
                  0,6,6,4,3,5,    // so 6
                  1,1,7,32,32,7,  // so 7
                  0,6,2,4,3,5,    // so 8
                  0,6,2,3,3,5};   // so 9
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//mang tung doan so to cua LCD
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                   
const unsigned int8 lcd_ma_8doan[] = {
   0x07,0x0f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,  //doan f - 0
   0x1f,0x1f,0x1f,0x00,0x00,0x00,0x00,0x00,  //doan a - 1
   0x1c,0x1e,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,  //doan b - 2
   0x00,0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,  //doan d - 3
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x0f,0x07,  //doan e - 4
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1e,0x1c,  //doan c - 5      
   0x1f,0x1f,0x1f,0x00,0x00,0x00,0x1f,0x1f,  //doan g+d-6 
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f}; //doan i  -7     
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 612: copy mang so to vao cgram
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                                  
void lcd_khoi_tao_cgram_so_to()                                                  
{                                                                      
   usi8 i;
   lcd_command(lcd_cgram_addr);
   for(i=0;i<64;i++)  
     lcd_data(lcd_ma_8doan[i]);  
}         
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 613: hien thi so to tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_hien_thi_so_to(si8 so, x, y) 
{                        
   usi8 i;
   lcd_goto_xy(x,y);
   for(i=0;i<6;i++)
   {                                                           
      if(i==3) lcd_goto_xy(x+1,y);
      lcd_data(lcd_so_to[so][i]);
   }                        
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 614: xoa so to tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_xoa_so_to(si8 x, y)
{  
   usi8 i;
   lcd_goto_xy(x,y);         
   for(i=0;i<6;i++)
   {            
      if(i==3) lcd_goto_xy(x+1,y);    
      lcd_data(' ');
   }
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 615: hien thi so hex toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_hthi_byte(usi8 sh,x,y) 
{  
   usi8 bh,bl;
   lcd_goto_xy(x,y);
   bh=sh/16; bl=sh%16;                                                
   if(bh>9) lcd_data(bh+0x37);
   else     lcd_data(bh+0x30);
   if(bl>9) lcd_data(bl+0x37);
   else     lcd_data(bl+0x30);
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 616: giai ma hien thi 2 so tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_gm_ht_2so_nho_xvn(usi16 so,usi8 x,usi8 y,int1 xvn)      
{                           
   usi8 ch,dv;          
   lcd_goto_xy(x,y);                   
   ch = so/10%10+0x30;  dv = so%10+0x30;
   if(xvn) 
   {
      if(ch==0x30) ch=" ";
   }
   lcd_data(ch);  
   lcd_data(dv);   
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 617: giai ma hien thi 3 so tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_gm_ht_3so_nho_xvn(usi16 so,usi8 x,usi8 y,int1 xvn)      
{                           
   usi8 tr,ch,dv;          
   lcd_goto_xy(x,y);                   
   tr = so/100%10+0x30; 
   ch = so/10%10+0x30;        
   dv = so%10+0x30;
   if(xvn) 
   {
      if(tr==0x30)
      {     
         tr=" ";
         if(ch==0x30) ch=" ";
      }
   }
   lcd_data(tr);    
   lcd_data(ch);  
   lcd_data(dv);   
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 618: giai ma hien thi 4 so tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_gm_ht_4so_nho_xvn(usi16 so,usi8 x,usi8 y,int1 xvn)      
{                           
   usi8 ng,tr,ch,dv;          
   lcd_goto_xy(x,y);                
   ng = so/1000%10+0x30;    
   tr = so/100%10+0x30; 
   ch = so/10%10+0x30;        
   dv = so%10+0x30;
   if(xvn) 
   {
      if(ng==0x30)
      {  
         ng=" ";
         if(tr==0x30)
         {     
            tr=" ";
            if(ch==0x30) ch=" ";
         }
      }
   }
   lcd_data(ng);  lcd_data(tr);    
   lcd_data(ch);  lcd_data(dv);   
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 619: giai ma hien thi 5 so tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_gm_ht_5so_nho_xvn(usi16 so,usi8 x,usi8 y)      
{                           
   usi8 cn,ng,tr,ch,dv;          
   lcd_goto_xy(x,y);
   cn = so/10000%10+0x30;    
   ng = so/1000%10+0x30;    
   tr = so/100%10+0x30; 
   ch = so/10%10+0x30;        
   dv = so%10+0x30;
   if(cn==0x30)
   {
     cn=" ";
     if(ng==0x30)
      {  
        ng=" ";
        if(tr==0x30)
        {     
        tr=" ";
        if(ch==0x30) ch=" ";
      }
      }
   }
   lcd_data(cn);
   lcd_data(ng);  lcd_data(tr);    
   lcd_data(ch);  lcd_data(dv);   
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 620: giai ma hien thi 2 so to tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_gm_ht_2so_to_xvn(usi16 so,usi8 x,usi8 y,int1 xvn)
{ 
   usi8 ch,dv;    
   lcd_goto_xy(x,y);
   ch = so/10%10;        
   dv = so%10;
   lcd_hien_thi_so_to(ch,x,y);               
   lcd_hien_thi_so_to(dv,x,y+3);  
   if((ch==0)&&(xvn)) lcd_xoa_so_to(x,y);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 621: giai ma hien thi 3 so to tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_gm_ht_3so_to_xvn(usi16 so,usi8 x,usi8 y,int1 xvn)
{ 
   usi8 tr,ch,dv;          
   lcd_goto_xy(x,y);                   
   tr = so/100%10; 
   ch = so/10%10;        
   dv = so%10;
   lcd_hien_thi_so_to(tr,x,y);               
   lcd_hien_thi_so_to(ch,x,y+3);  
   lcd_hien_thi_so_to(dv,x,y+6);
   if((tr==0)&&(xvn))
   {     
      lcd_xoa_so_to(x,y);
      if(ch==0) lcd_xoa_so_to(x,y+3);
   }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 622: giai ma hien thi 4 so to tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_gm_ht_4so_to_xvn(usi16 so,usi8 x,usi8 y,int1 xvn)
{ 
   usi8 ng,tr,ch,dv;          
   lcd_goto_xy(x,y);                   
   ng = so/1000%10; 
   tr = so/100%10; 
   ch = so/10%10;        
   dv = so%10;
   lcd_hien_thi_so_to(ng,x,y);               
   lcd_hien_thi_so_to(tr,x,y+3);  
   lcd_hien_thi_so_to(ch,x,y+6);
   lcd_hien_thi_so_to(dv,x,y+9);  
   if((ng==0)&&(xvn))
   {     
      lcd_xoa_so_to(x,y);
      if(tr==0) 
     {
      lcd_xoa_so_to(x,y+3);
      if(ch==0) lcd_xoa_so_to(x,y+6);
     }
   }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 623: giai ma hien thi 4 so to tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_gm_ht_5so_to_xvn(usi16 so,usi8 x,usi8 y,int1 xvn)
{ 
   usi8 cn,ng,tr,ch,dv; 

      lcd_goto_xy(x,y);
      ng = so/1000%10; 
      ng = so/1000%10; 
      tr = so/100%10; 
      ch = so/10%10;        
      dv = so%10;
      lcd_hien_thi_so_to(cn,x,y);               
      lcd_hien_thi_so_to(ng,x,y+3);  
      lcd_hien_thi_so_to(tr,x,y+6);
      lcd_hien_thi_so_to(ch,x,y+9); 
      lcd_hien_thi_so_to(dv,x,y+12);
      if((cn==0)&&(xvn))
      {     
         lcd_xoa_so_to(x,y);
         if(ng==0) 
         {
            lcd_xoa_so_to(x,y+3);
            if(tr==0) 
            {
               lcd_xoa_so_to(x,y+6);
               if(ch==0) lcd_xoa_so_to(x,y+9);
            }
         }
      }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//ham 624: giai ma hien thi 4 so to tai toa do x,y
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void lcd_hien_thi_2so_tp_nho(usi8 tp,usi8 x, y)
{   
   lcd_goto_xy(x,y);
   lcd_data(".");                                        
   lcd_data(tp/10%10+0x30);
   lcd_data(tp%10+0x30);   
}  

void lcd_hien_thi_3so_tp_nho(usi16 tp,usi8 x, y)
{   
   lcd_goto_xy(x,y);
   lcd_data(".");   
   lcd_data(tp/100+0x30);
   lcd_data(tp/10%10+0x30);
   lcd_data(tp%10+0x30);   
}

void lcd_hien_thi_1so_tp_nho(usi8 tp,usi8 x, y)
{   
   lcd_goto_xy(x,y);
   lcd_data(".");                                        
   //lcd_data(tp/10%10+0x30);
   lcd_data(tp%10+0x30);   
}  

