//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//NGUYEN DINH PHU SU PHAM KY THUAT TP HCM
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 301: chuong trinh con xuat 4 byte ra 32 led don
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void xuat_32led_don_4byte(usi8 bld3,bld2,bld1,bld0)
{     
   xuat_1byte(bld3);  xuat_1byte(bld2);
   xuat_1byte(bld1);  xuat_1byte(bld0);            
                     
   output_high(rck_32led);    
   output_low(rck_32led);      
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 302: chuong trinh con xuat 2 word 16 bitra 32 led don
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void xuat_32led_don_2word(usi16 wld1,usi16 wld0)
{     
   unsigned int8  b3,b2,b1,b0;
   b3 = wld1>>8;  b2 = wld1; 
   b1 = wld0>>8;  b0 = wld0;
   xuat_32led_don_4byte(b3,b2,b1,b0);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 303: chuong trinh con xuat 1 double word ra 32 led don
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void xuat_32led_don_1dw(usi32 dwld)
{     
   unsigned int16  wd1,wd0;
   wd1 = dwld>>16;  wd0 = dwld;
   xuat_32led_don_2word(wd1,wd0);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 304: chuong trinh con xuat 1 byte ra 32 led don
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void xuat_32led_don_1byte(usi8 b0)
{     
   xuat_32led_don_4byte(0,0,0,b0);
}  
