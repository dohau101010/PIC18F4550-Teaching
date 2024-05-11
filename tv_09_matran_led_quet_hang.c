#include <tv_09_font.c>     
const unsigned int8 mq_hang[8]={0x01,0x02,0x04,0x08,0x80,0x40,0x20,0x10};
#define  slkt_hthi 60
unsigned int8  dl_hthi[6*slkt_hthi+24+24];
unsigned int16 slkt;

unsigned int8  dl_cot_cd[48]={};
unsigned int8  dl_cot_dich[48]={};
unsigned int8  dl_cot_cd_do[24]={};
unsigned int8  dl_cot_cd_xanh[24]={};
unsigned int8  dl_cot_dich_d[24]={};
unsigned int8  dl_cot_dich_x[24]={};
unsigned int16 vtkt1;
                                        
unsigned int8 doi_1_bit_1_sang_thutu(usi8 bx)
{   
   unsigned int8 ttcot=0;
   bx= bx>>1;
   while(bx!=0)
   {
      ttcot++; bx= bx>>1;
   }   
   return(ttcot);
}

void lay_so_luong_ky_tu_chuoi()
{   
   slkt=0;
   while(chuoi_hthi[slkt]) slkt++;
}

void xoa_dl_hienthi()
{   
   unsigned int16  j;     
   for(j=0;j<6*slkt_hthi ;j++)  
   dl_hthi[j]=0;
}

void lay_ma_1_so_matran(usi8 so,vitri_luu)
{   
   unsigned int8  j; 
   so = so + 0x30; 
   for(j=0;j<6 ;j++)    
   dl_hthi[j+vitri_luu*6]=mt_kytu[so][j];
}

void lay_ma_ky_tu(usi8 slkt_x)
{   
   unsigned int8 kytu,i,n,j;
   n=0;
   for(i=0;i<24;i++)
      dl_hthi[i]=0;
   for(i=0;i<slkt_x;i++)
   {
      kytu = chuoi_hthi[i];      
      for(j=0;j<6 ;j++,n++)  
      dl_hthi[n+24]=mt_kytu[kytu][j];
   }   
   for(i=0;i<24;i++)
      dl_hthi[n+24+i]=0;
}

//sap xep cac ky tu mau xanh 1,2,3,4
void ky_tu_xanh_so_1(usi8 k)
{
   dl_cot_cd[1]=dl_hthi[k+3]; dl_cot_cd[3]=dl_hthi[k+2];
   dl_cot_cd[5]=dl_hthi[k+1]; dl_cot_cd[7]=dl_hthi[k+0];      
   dl_cot_cd[8]=dl_hthi[k+4]; dl_cot_cd[10]=dl_hthi[k+5];
}
void ky_tu_xanh_so_2(usi8 k)
{
   dl_cot_cd[12]=dl_hthi[k+6];  dl_cot_cd[14]=dl_hthi[k+7];      
   dl_cot_cd[17]=dl_hthi[k+11]; dl_cot_cd[19]=dl_hthi[k+10];
   dl_cot_cd[21]=dl_hthi[k+9];  dl_cot_cd[23]=dl_hthi[k+8];       
}
void ky_tu_xanh_so_3(usi8 k)
{
   dl_cot_cd[24]=dl_hthi[k+12];  dl_cot_cd[26]=dl_hthi[k+13];
   dl_cot_cd[28]=dl_hthi[k+14];  dl_cot_cd[30]=dl_hthi[k+15];      
   dl_cot_cd[37]=dl_hthi[k+17];  dl_cot_cd[39]=dl_hthi[k+16]; 
}
void ky_tu_xanh_so_4(usi8 k)
{    
   dl_cot_cd[33]=dl_hthi[k+19];  dl_cot_cd[35]=dl_hthi[k+18];
   dl_cot_cd[40]=dl_hthi[k+20];  dl_cot_cd[42]=dl_hthi[k+21];
   dl_cot_cd[44]=dl_hthi[k+22];  dl_cot_cd[46]=dl_hthi[k+23];       
}

//sap xep cac ky tu mau do 1,2,3,4
void ky_tu_do_so_1(usi8 k)
{
   dl_cot_cd[0]=dl_hthi[k+3];   dl_cot_cd[2]=dl_hthi[k+2];
   dl_cot_cd[4]=dl_hthi[k+1];   dl_cot_cd[6]=dl_hthi[k+0];      
   dl_cot_cd[9]=dl_hthi[k+4];   dl_cot_cd[11]=dl_hthi[k+5];
}
void ky_tu_do_so_2(usi8 k)
{
   dl_cot_cd[13]=dl_hthi[k+6];  dl_cot_cd[15]=dl_hthi[k+7];      
   dl_cot_cd[16]=dl_hthi[k+11]; dl_cot_cd[18]=dl_hthi[k+10];
   dl_cot_cd[20]=dl_hthi[k+9];  dl_cot_cd[22]=dl_hthi[k+8];
}
void ky_tu_do_so_3(usi8 k)
{      
   dl_cot_cd[25]=dl_hthi[k+12]; dl_cot_cd[27]=dl_hthi[k+13];
   dl_cot_cd[29]=dl_hthi[k+14]; dl_cot_cd[31]=dl_hthi[k+15];      
   dl_cot_cd[36]=dl_hthi[k+17]; dl_cot_cd[38]=dl_hthi[k+16]; 
}
void ky_tu_do_so_4(usi8 k)
{
   dl_cot_cd[32]=dl_hthi[k+19]; dl_cot_cd[34]=dl_hthi[k+18]; 
   dl_cot_cd[41]=dl_hthi[k+20]; dl_cot_cd[43]=dl_hthi[k+21];
   dl_cot_cd[45]=dl_hthi[k+22]; dl_cot_cd[47]=dl_hthi[k+23]; 
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void ky_tu_xanh_hoac_do_so_1(usi8 k)
{     
   k=k+5;      
   if(dl_hthi[vtkt1]==0)
   {
      dl_cot_cd[1]=dl_hthi[k+3];  dl_cot_cd[3]=dl_hthi[k+2];
      dl_cot_cd[5]=dl_hthi[k+1];  dl_cot_cd[7]=dl_hthi[k+0];      
      dl_cot_cd[8]=dl_hthi[k+4];  dl_cot_cd[10]=dl_hthi[k+5];
   }
   else
   {
      dl_cot_cd[0]=dl_hthi[k+3];  dl_cot_cd[2]=dl_hthi[k+2];
      dl_cot_cd[4]=dl_hthi[k+1];  dl_cot_cd[6]=dl_hthi[k+0];      
      dl_cot_cd[9]=dl_hthi[k+4];  dl_cot_cd[11]=dl_hthi[k+5];     
   }
}
void ky_tu_xanh_hoac_do_so_2(usi8 k)
{
   if(dl_hthi[vtkt1+6]==0)
   {
      dl_cot_cd[12]=dl_hthi[k+6];   dl_cot_cd[14]=dl_hthi[k+7];      
      dl_cot_cd[17]=dl_hthi[k+11];  dl_cot_cd[19]=dl_hthi[k+10];
      dl_cot_cd[21]=dl_hthi[k+9];   dl_cot_cd[23]=dl_hthi[k+8];     
   }
   else
   {
      dl_cot_cd[13]=dl_hthi[k+6];  dl_cot_cd[15]=dl_hthi[k+7];      
      dl_cot_cd[16]=dl_hthi[k+11]; dl_cot_cd[18]=dl_hthi[k+10];
      dl_cot_cd[20]=dl_hthi[k+9];  dl_cot_cd[22]=dl_hthi[k+8];
   }
}
void ky_tu_xanh_hoac_do_so_3(usi8 k)
{
   if(dl_hthi[vtkt1+12]==0)
   {
      dl_cot_cd[24]=dl_hthi[k+12];  dl_cot_cd[26]=dl_hthi[k+13];
      dl_cot_cd[28]=dl_hthi[k+14];  dl_cot_cd[30]=dl_hthi[k+15];      
      dl_cot_cd[37]=dl_hthi[k+17];  dl_cot_cd[39]=dl_hthi[k+16]; 
   }
   else
   {
      dl_cot_cd[25]=dl_hthi[k+12]; dl_cot_cd[27]=dl_hthi[k+13];
      dl_cot_cd[29]=dl_hthi[k+14]; dl_cot_cd[31]=dl_hthi[k+15];      
      dl_cot_cd[36]=dl_hthi[k+17]; dl_cot_cd[38]=dl_hthi[k+16]; 
   }
}
void ky_tu_xanh_hoac_do_so_4(usi8 k)
{                                                           
   if(dl_hthi[vtkt1+18]==0)
   {
      dl_cot_cd[33]=dl_hthi[k+19];  dl_cot_cd[35]=dl_hthi[k+18];
      dl_cot_cd[40]=dl_hthi[k+20];  dl_cot_cd[42]=dl_hthi[k+21];
      dl_cot_cd[44]=dl_hthi[k+22];  dl_cot_cd[46]=dl_hthi[k+23];       
   }
   else  
   {
      dl_cot_cd[32]=dl_hthi[k+19]; dl_cot_cd[34]=dl_hthi[k+18]; 
      dl_cot_cd[41]=dl_hthi[k+20]; dl_cot_cd[43]=dl_hthi[k+21];
      dl_cot_cd[45]=dl_hthi[k+22]; dl_cot_cd[47]=dl_hthi[k+23]; 
   }
}

void sapxep_vitri_48byte_mau_theo_kytu(usi8 k1)
{
   ky_tu_xanh_hoac_do_so_1(k1);  
   ky_tu_xanh_hoac_do_so_2(k1);
   ky_tu_xanh_hoac_do_so_3(k1);
   ky_tu_xanh_hoac_do_so_4(k1);         
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void sapxep_vitri_48byte_cot_xanh(usi8 k1)
{
   ky_tu_xanh_so_1(k1);   ky_tu_xanh_so_2(k1);
   ky_tu_xanh_so_3(k1);   ky_tu_xanh_so_4(k1);                   
}
void sapxep_vitri_48byte_cot_do(usi8 k1)
{   
   ky_tu_do_so_1(k1);  ky_tu_do_so_2(k1);
   ky_tu_do_so_3(k1);  ky_tu_do_so_4(k1);     
}

void sapxep_vitri_xanh_do_xanh_do(usi8 k1)
{
   ky_tu_xanh_so_1(k1);  ky_tu_do_so_2(k1);
   ky_tu_xanh_so_3(k1);  ky_tu_do_so_4(k1);
}
void sapxep_vitri_do_xanh_do_xanh(usi8 k1)
{
   ky_tu_do_so_1(k1);  ky_tu_xanh_so_2(k1);
   ky_tu_do_so_3(k1);  ky_tu_xanh_so_4(k1);
}

void sapxep_vitri_xanh_xanh_do_do(usi8 k1)
{
   ky_tu_xanh_so_1(k1);  ky_tu_xanh_so_2(k1);
   ky_tu_do_so_3(k1);     ky_tu_do_so_4(k1);
}
void sapxep_vitri_do_do_xanh_xanh(usi8 k1)
{
   ky_tu_do_so_1(k1);  ky_tu_do_so_2(k1);
   ky_tu_xanh_so_3(k1);  ky_tu_xanh_so_4(k1);
}

void xoa_dl_48_cot()
{
   unsigned int8 j;
   for(j=0;j<48;j++) dl_cot_cd[j]=0;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void  copy_48_cot_hienthi()
{     
   unsigned int8 i;
   for(i=0;i<48;i++) dl_cot_dich[i]=dl_cot_cd[i];
}

void xuat_1bit_cua_48_cot_hienthi()
{     
   unsigned int8 i;
   for(i=0;i<48;i++)   
   dl_cot_dich[i]=xuat_1bit(dl_cot_dich[i]);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void  copy_24_cot_hienthi_xanh(usi8 k)
{     
   unsigned int8 i;
   for(i=0;i<24;i++)   
   dl_cot_cd_xanh[i+k]=dl_hthi[i+k];
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void  copy_24_cot_hienthi_do(usi8 k)
{     
   unsigned int8 i;
   for(i=0;i<24;i++)   
      dl_cot_cd_do[i+k]=dl_hthi[i+k];
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void  copy_24_cot_hienthi_xanh_do_de_dich()
{     
   unsigned int8 i;
   for(i=0;i<48;i++)   
   {
      dl_cot_dich_d[i]=dl_cot_cd_do[i];
      dl_cot_dich_x[i]=dl_cot_cd_xanh[i];     
   }
} 
void xoa_dl_24_cot_xanh_do()
{
   unsigned int8 j;
   for (j=0;j<24;j++) 
      dl_cot_cd_do[j]=0;dl_cot_cd_xanh[j]=0;
}

void xuat_dulieu_hienthi_matran()
{    
   mo_led_matran;
   mo_ic_74573_b_thong_dl();
   output_high(rck_matranled); output_low(rck_matranled); 
   chot_ic_74573_b_goi_du_lieu;  
}

void xuat_1bit_cua_48_cot_hienthi_c2()
{     
   signed i;
   for(i=3;i>-1;i--)
   {
      dl_cot_dich_d[i]=xuat_1bit(dl_cot_dich_d[i]);
      dl_cot_dich_x[i]=xuat_1bit(dl_cot_dich_x[i]);
   }
   for(i=4;i<8;i++)
   {
      dl_cot_dich_d[i]=xuat_1bit(dl_cot_dich_d[i]);
      dl_cot_dich_x[i]=xuat_1bit(dl_cot_dich_x[i]);
      }
   for(i=11;i>7;i--)
   {
      dl_cot_dich_d[i]=xuat_1bit(dl_cot_dich_d[i]);
      dl_cot_dich_x[i]=xuat_1bit(dl_cot_dich_x[i]);
   }
   for(i=12;i<16;i++)
   {
      dl_cot_dich_d[i]=xuat_1bit(dl_cot_dich_d[i]);
      dl_cot_dich_x[i]=xuat_1bit(dl_cot_dich_x[i]);
   }   
   for(i=19;i>15;i--)
   {
      dl_cot_dich_d[i]=xuat_1bit(dl_cot_dich_d[i]);
      dl_cot_dich_x[i]=xuat_1bit(dl_cot_dich_x[i]);
   }
   for(i=20;i<24;i++)
   {
      dl_cot_dich_d[i]=xuat_1bit(dl_cot_dich_d[i]);
      dl_cot_dich_x[i]=xuat_1bit(dl_cot_dich_x[i]);
   }      
}

void hien_thi_ma_tran_quet_hang(usi8 ck)
{
   unsigned int8 j,i;
   for (i=0;i<ck;i++)
   {
      copy_48_cot_hienthi();
      for(j=0;j<8;j++)
      {
         xuat_1bit_cua_48_cot_hienthi();
         xuat_2byte(mq_hang[j]);                  
         xuat_dulieu_hienthi_matran();                                                                      
         delay_us(500); 
         xuat_matranled(0,0,0,0);
      }
   }
}

       
 
