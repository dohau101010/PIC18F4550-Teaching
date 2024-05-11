#include <tv_09_font.c>

const unsigned int16 mqc_do[8]={
0x0200,0x0800,0x2000,0x8000,0x0040,0x0010,0x0004,0x0001};
const unsigned int16 mqc_xanh[]={
0x0100,0x0400,0x1000,0x4000,0x0080,0x0020,0x0008,0x0002};
const unsigned int16 mqc_cam[]={
0x0300,0x0c00,0x3000,0xc000,0x00c0,0x0030,0x000c,0x0003};

#define tg_delay 100                      
#define slkt_hthi 40
unsigned int8 dl_hthi[6*slkt_hthi];
unsigned int8 slkt,mtb0,mtb1,mtb2;              
unsigned int16 ma_hang, mqc_led0, mqc_led1, mqc_led2;
unsigned int32 tt_qc=1; 

unsigned int8 doi_1_bit_1_sang_thutu(usi8 bx)
{             
   unsigned int8 ttcot=0;
   bx= bx>>1;
   while(bx!=0)
   {                   
      ttcot++;  bx= bx>>1;
   }   
   return(ttcot);
}

void lay_ma_ky_tu(usi8 slkt_x)
{                                                            
   unsigned int8 kytu,i,n,j;   
   n=0;        
   for(i=0;i<slkt_x;i++)
   {
      kytu = chuoi_hthi[i];
      for(j=0;j<6 ;j++,n++)  
      dl_hthi[n]=hieu_chinh_4bit_cao(mt_kytu[kytu][j]);
   }
}

void lay_ma_quet_24_cot_xanh()
{   
   mtb0 = tt_qc;
   mtb1 = tt_qc>>8;
   mtb2 = tt_qc>>16;
   if (mtb0!=0)  
   {  
      mtb0=doi_1_bit_1_sang_thutu(mtb0);
      mqc_led0 = mqc_xanh[mtb0];
      mqc_led1 = 0;
      mqc_led2 = 0;
   }
   else if (mtb1!=0)  
   {        
      mtb1=doi_1_bit_1_sang_thutu(mtb1);
      mqc_led0 = 0;
      mqc_led1 = mqc_xanh[mtb1];
      mqc_led2 = 0;
   }                 
   else if (mtb2!=0)  
   {        
      mtb2=doi_1_bit_1_sang_thutu(mtb2);
      mqc_led0 = 0;
      mqc_led1 = 0;
      mqc_led2 = mqc_xanh[mtb2];
   }   
}

void lay_ma_quet_24_cot_do()
{   
   mtb0 = tt_qc;
   mtb1 = tt_qc>>8;
   mtb2 = tt_qc>>16;
   if (mtb0!=0)  
   {  
      mtb0=doi_1_bit_1_sang_thutu(mtb0);
      mqc_led0 = mqc_do[mtb0];
      mqc_led1 = 0;
      mqc_led2 = 0;
   }
   else if (mtb1!=0)  
   {        
      mtb1=doi_1_bit_1_sang_thutu(mtb1);
      mqc_led0 = 0;
      mqc_led1 = mqc_do[mtb1];
      mqc_led2 = 0;
   }                 
   else if (mtb2!=0)  
   {        
      mtb2=doi_1_bit_1_sang_thutu(mtb2);
      mqc_led0 = 0;      
      mqc_led1 = 0;
      mqc_led2 = mqc_do[mtb2];
   }   
}

void lay_ma_quet_24_cot_cam()
{   
   mtb0 = tt_qc;
   mtb1 = tt_qc>>8;
   mtb2 = tt_qc>>16;
   if (mtb0!=0)  
   {  
      mtb0=doi_1_bit_1_sang_thutu(mtb0);
      mqc_led0 = mqc_cam[mtb0];
      mqc_led1 = 0;
      mqc_led2 = 0;
   }
   else if (mtb1!=0)  
   {        
      mtb1=doi_1_bit_1_sang_thutu(mtb1);
      mqc_led0 = 0;
      mqc_led1 = mqc_cam[mtb1];
      mqc_led2 = 0;
   }                 
   else if (mtb2!=0)  
   {        
      mtb2=doi_1_bit_1_sang_thutu(mtb2);
      mqc_led0 = 0;      
      mqc_led1 = 0;
      mqc_led2 = mqc_cam[mtb2];
   }   
}
void lay_so_luong_ky_tu_chuoi()
{   
   slkt=0;                                
   while(chuoi_hthi[slkt])
   {
      slkt++;
   }
}                   

void quet_4kytu_mau_xanh(usi8 sck,vitri)
{
   unsigned int8 ck, j;
   for (ck=0;ck<sck;ck++)
   {
      tt_qc = 1;
      for(j=vitri;j<vitri+24;j++)                          
      {
         lay_ma_quet_24_cot_xanh();
         ma_hang = dl_hthi[j];
         xuat_matranled(ma_hang,mqc_led2,mqc_led1,mqc_led0);
         delay_us(tg_delay);   
         xuat_matranled(0,0,0,0);
         tt_qc = tt_qc << 1;         
      }                                             
   }
}        
    

void quet_4kytu_mau_do(usi8 sck,vitri)
{   
   unsigned int8 ck, j;
   for (ck=0;ck<sck;ck++)
   {     
      tt_qc = 1;
      for(j=vitri;j<vitri+24;j++)
      {
         lay_ma_quet_24_cot_do();
         ma_hang = dl_hthi[j];
         xuat_matranled(ma_hang,mqc_led2,mqc_led1,mqc_led0);     
         delay_us(tg_delay);
         xuat_matranled(0,0,0,0);
         tt_qc = tt_qc <<1;
      }
   }
}  

void quet_4kytu_mau_cam(usi8 sck,vitri)
{   
   unsigned int8 ck, j;
   for (ck=0;ck<sck;ck++)
   {     
      tt_qc = 1;
      for(j=vitri;j<vitri+24;j++)
      {                   
         lay_ma_quet_24_cot_cam();
         ma_hang = dl_hthi[j];
         xuat_matranled(ma_hang,mqc_led2,mqc_led1,mqc_led0);     
         delay_us(tg_delay);           
         xuat_matranled(0,0,0,0);
         tt_qc = tt_qc <<1;
      }                                                  
   }
}  


