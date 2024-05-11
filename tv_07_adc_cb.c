//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//NGUYEN DINH PHU SU PHAM KY THUAT TP HCM
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 701: chuyen doi theo kenh va so lan, tra ve T/F 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
//dinh nghia cac kenh ADC noi voi cac cam bien 
#define chan_lm35a   0                        
#define chan_lm35b   1
#define chan_cbkc    2
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
float h701_adc_read(usi8 solan,chan_i)                      
{
   float kq_adc;
   set_adc_channel(chan_i);               
   delay_us(20);                                          
   kq_adc = 0;             
   for(int8 i=0;i<solan;i++)  
   {
      kq_adc = kq_adc + read_adc();                        
   }
   kq_adc = kq_adc/solan;     
   return kq_adc; 
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 702: tach so thuc thanh phan nguyen va thap phan
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
usi16 so_ng,so_tp;
void float_to_ng_2so_tp(float st)                      
{   
   so_ng = st/1;       //nguyen                          
   st = st-so_ng;      //tphan
   st = st*100;                                                         
   so_tp = st/1;   
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 703: do nhiet lm35a, lm35b, dkhien den, bao dong
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   
//!#define nd_tren  34                                                      
//!#define nd_duoi  32    
unsigned int16 nd_tren=34, nd_duoi=32;
int1 ttqn=0,buz_ena=0;             
void so_sanh_1nd_dk_buzzer(usi16 nd1)                        
{                                   
   if((nd1>nd_tren)&&(ttqn==0))        
   {
      ttqn = 1;                                                              
      if(buz_ena)   buzzer_on();                                   
      triac_2_off(); 
   }                                                                           
   else if((nd1<nd_tren)&&(ttqn==1))
   {
      ttqn = 0; 
      buzzer_off();
   }
   else if((nd1<nd_duoi)&&(ttqn==0))  
      triac_2_on();
}   

void so_sanh_1nd(usi16 nd1)
{
   if((nd1>nd_tren)&&(ttqn==0))        
   {
      ttqn = 1;                                                              
      if(buz_ena)   buzzer_on();                                   
      triac_2_off(); //triac 2 dieu khien den gia nhiet
   }                                                                           
   else if((nd1<nd_tren)&&(ttqn==1))
   {
      ttqn = 0; 
      if(buz_ena)   buzzer_off();//tat bao dong
   }
   else if((nd1<nd_duoi)&&(ttqn==0))  
      triac_2_on(); //mo den gia nhiet
   xuat_32led_don_1dw(0x000ff000);
}

void so_sanh_and_2nd(usi16 nd1, usi16 nd2)
{
   if((nd1>nd_tren)&&(nd2>nd_tren)&&(ttqn==0))        
   {
      ttqn = 1;                                                              
      if(buz_ena)   buzzer_on();                                   
      triac_2_off(); //triac 2 dieu khien den gia nhiet
   }                                                                           
   else if((nd1<nd_tren)&&(nd2<nd_tren)&&(ttqn==1))
   {
      ttqn = 0; 
      if(buz_ena)   buzzer_off();//tat bao dong
   }
   else if((nd1<nd_duoi)&&(nd2<nd_duoi)&&(ttqn==0))  
      triac_2_on(); //mo den gia nhiet
   xuat_32led_don_1dw(0x000ff000);
}

void so_sanh_or_2nd(usi16 nd1, usi16 nd2)
{
   if(((nd1>nd_tren)||(nd2>nd_tren))&&(ttqn==0))        
   {
      ttqn = 1;                                                              
      if(buz_ena)   buzzer_on();                                   
      triac_2_off(); //triac 2 dieu khien den gia nhiet
   }                                                                           
   else if(((nd1<nd_tren)&&(nd2<nd_tren))&&(ttqn==1))
   {
      ttqn = 0; 
      if(buz_ena)   buzzer_off();//tat bao dong
   }
   else if(((nd1<nd_duoi)||(nd2<nd_duoi))&&(ttqn==0))  
      triac_2_on(); //mo den gia nhiet
   xuat_32led_don_1dw(0x000ff000);
}

//ham so sanh nhiet do dieu khien buzzer, den (nd1,nd2,sel)
void so_sanh_nd_dk_buzzer(usi16 nd1, usi16 nd2, int8 sel)
{
   if(sel==1)        so_sanh_1nd(nd1);
   else if(sel==2)   so_sanh_and_2nd(nd1,nd2);
   else if(sel==3)   so_sanh_or_2nd(nd1,nd2);
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//bai 711: doc gia tri cua joystick hien thi lcd          
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   
//!void h711_lcd_hien_thi_joystick(usi8 x,y)                                 
//!{                                             
//!   lcd_goto_xy(0,0);                                                        
//!   lcd_data("JOYSTICK");
//!   lcd_goto_xy(1,4);                                                        
//!   lcd_data("VRX:");
//!   lcd_goto_xy(3,4);                                                        
//!   lcd_data("VRY:");
//!} 
//!
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//vrx noi kenh thu 1 AN1, vry noi voi an2
//cho phep hien thi 2 so thap phan tuy thuoc vao http
//dung bien nguyen tam de khi bang thi khong can hthi lai
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!usi16 vrx_ng,vrx_ngt;
//!void h711_adc_js_vrx_doc_xuly(usi8 solan)                                     
//!{                                              
//!   float vrx;
//!   vrx=h701_adc_read(solan,chan_js_vrx);
//!   h701_foat_to_ng_2so_tp(vrx);      
//!   vrx_ng = so_ng;
//!}
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!void h711_adc_js_vrx_ht_lcd_7doan(usi8 x,y,z,int1 ht_l7d,ht_lcd)                                     
//!{                                                 
//!   if(vrx_ngt!=vrx_ng)
//!   {
//!      vrx_ngt=vrx_ng;
//!      if(ht_l7d)  
//!      {
//!         giaima_bin_4so_vitri_vn(vrx_ng,z,cx_vn);  //4
//!         xuat_8led_7doan(); 
//!      }
//!      if(ht_lcd) lcd_gm_ht_4so_to_xvn(vrx_ng,x,y,kx_vn);//0,8
//!   }          
//!}  
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!void h711_adc_js_vrx_all(usi8 solan, x,y,z,int1 ht_l7d,ht_lcd)                                     
//!{                                                 
//!     h711_adc_js_vrx_doc_xuly(solan);
//!     h711_adc_js_vrx_ht_lcd_7doan(x,y,z,ht_l7d,ht_lcd);
//!}  
//!
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!usi16 vry_ng,vry_ngt;
//!void h712_adc_js_vry_doc_xuly(usi8 solan)                                     
//!{                                           
//!   float vry;  
//!   vry=h701_adc_read(solan,chan_js_vry);
//!   h701_foat_to_ng_2so_tp(vry);      
//!   vry_ng = so_ng;
//!}
//!
//!void h712_adc_js_vry_ht_lcd_7doan(usi8 x,y,z,int1 ht_l7d,ht_lcd)                                     
//!{                                             
//!   if(vry_ngt!=vry_ng)
//!   {
//!      vry_ngt=vry_ng;
//!      if(ht_l7d)  
//!      {  
//!         giaima_bin_4so_vitri_vn(vry_ng,z,cx_vn);//0
//!         xuat_8led_7doan();
//!      }                  
//!      if(ht_lcd) lcd_gm_ht_4so_to_xvn(vry_ng,x,y,kx_vn);//2,8
//!   }                             
//!}  
//! 
//!void h712_adc_js_vry_all(usi8 solan,x,y,z,int1 ht_l7d,ht_lcd )                                     
//!{ 
//!   h712_adc_js_vry_doc_xuly(solan);
//!   h712_adc_js_vry_ht_lcd_7doan(x,y,z,ht_l7d,ht_lcd);
//!}     

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham kiem tra phim on                          
//neu co nhan thi dao bit tt_on_off va tra ve co nhan
//neu khong nhan tra ve tt khong nhan
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx     
//!int1 phim_on_off_btn_joy()   
//!{                     
//!   if(phim_bt_joy_c1(c_ktnp,0)==co_nhan)   
//!   {
//!      tt_on_off = ~tt_on_off;
//!      return co_nhan;   
//!   }                                    
//!   else   return khong_nhan;                   
//!}  
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!void h713_32led_on_off_btj()       
//!{                              
//!   tt_1btn = phim_on_off_btn_joy();
//!   if(tt_1btn==co_nhan)              
//!      h323_dk_32led_theo_tt_on_off();
//!}            


//!void b711_adc_joystick(usi8 solan,x,y,z,int1 ht_l7d,ht_lcd)                                     
//!{                                           
//!   h711_adc_js_vrx_all(solan,x,y,z,ht_l7d,ht_lcd);                                                                
//!   h711_adc_js_vry_all(solan);                      
//!   h711_32led_on_off_btj();             
//!}  

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//bai 711: doc gia tri cua joystick hien thi lcd          
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham kiem tra phim on                          
//neu co nhan thi dao bit tt_on_off va tra ve co nhan
//neu khong nhan tra ve tt khong nhan
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                                                   
                                                                   
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 712: do nhiet lm35a, dkhien den, bao dong          
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!void b712_adc_lm35a_lm35b_joystick()                                     
//!{
//!         
//!} 
//! 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx      
//ham 712: do nhiet lm35a, lm35b, dkhien den, bao dong
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   
    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 721: do nhiet lm35a, lm35b, dkhien den, bao dong
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
//!void h721_lcd_ht_text_cbkc_gp2d12()                            
//!{                                             
//!   lcd_goto_xy(0,0);                                                        
//!   lcd_data("Cam bien khoang cach"); 
//!   lcd_goto_xy(1,0);                                                        
//!   lcd_data("SHARP GP2D12:10-80cm");    
//!}  
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
//!usi16 kc_ng,kc_tp,kc_ngt=0;
//!void h721_adc_cbkc_gp2d12_doc_xuly(usi8 sl)                                     
//!{                
//!   float kc;  
//!   kc=h701_adc_read(sl,chan_cbkc);
//!   kc = pow(4277/kc,1.106);                                    
//!   if(kc>80) kc=80;  
//!   h701_foat_to_ng_2so_tp(kc);      
//!   kc_ng = so_ng;                              
//!   kc_tp = so_tp; 
//!}    
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!void h721_adc_cbkc_gp2d12_ht_lcd_7doan(usi8 x,y,z,int1 ht_l7d,ht_lcd,ht_tp)                                     
//!{                
//!   if(kc_ngt!=kc_ng)
//!   {
//!      kc_ngt=kc_ng;      
//!      if(ht_l7d) 
//!      {
//!         giaima_bin_2so_vitri_vn(kc_ng,z,cx_vn);//3
//!         xuat_8led_7doan();
//!      }
//!      if(ht_lcd) lcd_gm_ht_2so_to_xvn(kc_ng,x,y,kx_vn);//2,0
//!   }
//!   if(ht_tp) lcd_hien_thi_2so_tp_nho(kc_tp,x+1,y+6);  
//!}
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!void b721_adc_cbkc_gp2d12_all(usi8 solan,x,y,z,int1 ht_l7d,ht_lcd,ht_tp)                                     
//!{
//!   h721_adc_cbkc_gp2d12_doc_xuly(solan);
//!   h721_adc_cbkc_gp2d12_ht_lcd_7doan(x,y,z,ht_l7d,ht_lcd,ht_tp);
//!}    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 721: do nhiet lm35a, lm35b, dkhien den, bao dong
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
 
//!void b722_adc_lm35a_lm35a_joystick_cbkc()                                     
//!{                                                        
//!      giaima_bin_2so_vitri_vn(lm35b/1,2,kx_vn);                                              
//!      giaima_bin_2so_vitri_vn(lm35a/1,0,kx_vn);                
//!      xuat_8led_7doan();                                                 
//!      h701_lcd_hien_thi_so_tp(lm35a,1,0,sole_1);  
//!      h701_lcd_hien_thi_so_tp(lm35b,1,7,sole_1);    
//!      h701_lcd_hien_thi_so_tp(vrx,3,0,sole_1);         
//!      h701_lcd_hien_thi_so_tp(vry,3,7,sole_1);          
//!      h701_lcd_hien_thi_so_tp(cb_kc,1,14,sole_1);                          
//!}     
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 721: do nhiet lm35a, lm35b, dkhien den, bao dong
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!void h731_lcd_hien_thi_hcsr04(usi8 x,y)                            
//!{                                             
//!   lcd_goto_xy(x,y);                                                        
//!   lcd_data("HCSR04");                                           
//!}              
//!void h731_hcsr04_do_khoangcach()                              
//!{                                                             
//!   output_high(trig);      
//!   delay_us(20);   
//!   output_low(trig);          
//!                                           
//!   set_timer3(0);                                          
//!   while(!(input(echo)));         
//!   setup_timer_3(t3_internal|t3_div_by_8);  
//!                                
//!   while(input(echo));                                   
//!   setup_timer_3(t3_disabled);
//!                                                 
//!}
//!
//!usi16 gt_t3,kcsa_ng,kcsa_tp,kcsa_ngt=0;
//!void h731_cbkc_hc04_do_xuly()                                     
//!{                  
//!   float kcsa;  
//!   h731_hcsr04_do_khoangcach();
//!   gt_t3 = get_timer3();
//! 
//!   kcsa = gt_t3*1.6;                                              
//!   kcsa = (kcsa/58);
//!   
//!   h701_foat_to_ng_2so_tp(kcsa);      
//!   kcsa_ng = so_ng;
//!   kcsa_tp = so_tp; 
//!}
//!
//!void h731_cbkc_hc04_ht_lcd_7doan(usi8 x,y,z,int1 ht_l7d,ht_lcd)                                     
//!{                    
//!   if(kcsa_ngt!=kcsa_ng)
//!   {
//!      kcsa_ngt=kcsa_ng;
//!      if(ht_l7d)        
//!      {  
//!         giaima_bin_4so_vitri_vn(kcsa_ng,z,cx_vn); //0
//!         xuat_8led_7doan();
//!      }
//!      if(ht_lcd)lcd_gm_ht_4so_to_xvn(kcsa_ng,x,y,kx_vn);//2,8
//!   }  
//!}
//!
//!void h731_cbkc_hc04_all(usi8 x,y,z,int1 ht_l7d,ht_lcd)                                     
//!{    
//!   h731_cbkc_hc04_do_xuly();
//!   h731_cbkc_hc04_ht_lcd_7doan(x,y,z,ht_l7d,ht_lcd);
//!}
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!void b761_ket_hop_5_module()                            
//!{                                                                  
//!     //b622_glcd_dem_giay_kim_c1();     
//!     //b536_lcd_dem_xung_timer0_so_to();
//!     b424_gpg_3bt(20,10);                 
//!     b351_32led_4yc_tu_dong_if();            
     //h761_adc_lm35a_lm35b_joystick_cbkc_hc04();  
//!}                                                 
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//!//bai 643: ham chinh ket hop 32 led, 8 led 7doan, lcd, glcd        
//!//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//!void b742_lcd_dem_xung_timer0_so_to()                                                  
//!{                                                                      
//!   t0 = get_timer0();                                      
//!   if(t0!=t0_tam)              
//!   {                                                         
//!      giaima_bin_3so_vitri_vn(t0,0,cx_vn);           
//!      h536_giai_ma_ht_so_to(t0); 
//!      //h603_glcd_giai_ma_hien_thi(glcd_addr_line1,t0); 
//!      t0_tam = t0;                   
//!   }                                                                               
//!   if (t0>=120)   set_timer0(0);                                                 
//!} 
//! 
//!void b742_ket_hop_5_module()                            
//!{                                                                  
//!     //b622_glcd_dem_giay_kim_c1();
//!     
//!     b742_lcd_dem_xung_timer0_so_to();
//!     b424_gpg_3bt(20,10);                 
//!     b351_32led_4yc_tu_dong_if();                                              
//!}
//! 
//!          
