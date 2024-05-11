//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//NGUYEN DINH PHU SU PHAM KY THUAT TP HCM
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//khai bao mang va dnh nghia cac bien cho module 4led 7 doan
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
unsigned int8 dl_4l7d[4]= {0xff,0xff,0xff,0xff};
#define ngan4  dl_4l7d[0]
#define tram4  dl_4l7d[1]
#define chuc4  dl_4l7d[2]
#define donvi4 dl_4l7d[3]            
                                          
#define l7d_43 dl_4l7d[0]
#define l7d_42 dl_4l7d[1]
#define l7d_41 dl_4l7d[2]
#define l7d_40 dl_4l7d[3]            
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 401: xuat 4 byte ra 4 led 7 doan
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void xuat_4led_7doan_4so()
{                                                                  
   xuat_1byte(dl_4l7d[3]);   
   xuat_1byte(dl_4l7d[2]);
   xuat_1byte(dl_4l7d[1]);   
   xuat_1byte(dl_4l7d[0]);
                                   
   output_low(rck_4l7d);   
   output_high(rck_4l7d);
}                                                  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 402: giai ma so x 2 so, luu o led thu y, tuy chon xoa vn
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void md4l7d_giaima_2so_vitri_vn(usi8 x,y, int1 xvn)
{                                        
   dl_4l7d[y]   = ma7doan[x%10];       
   dl_4l7d[y-1] = ma7doan[x/10%10];              
   if(xvn==true)                                                   
   {                                                           
      if(dl_4l7d[y-1]==maso0) dl_4l7d[y-1]=0xff;                                 
   }                                                      
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 403: giai ma so x 3 so, luu o led thu y, tuy chon xoa vn
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
void md4l7d_giaima_3so_vitri_vn(usi16 x, usi8 y, int1 xvn)
{                                        
   dl_4l7d[y]   = ma7doan[x%10];       
   dl_4l7d[y-1] = ma7doan[x/10%10];
   dl_4l7d[y-2] = ma7doan[x/100%10];
   if(xvn==true)         
   {
      if(dl_4l7d[y-2]==maso0)
      {                               
         dl_4l7d[y-2]=0xff;
         if(dl_4l7d[y-1]==maso0) dl_4l7d[y-1]=0xff;
      }
   }            
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 404: giai ma so x 4 so, luu o led thu y, tuy chon xoa vn
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void md4l7d_giaima_4so_vitri_vn(usi16 x, usi8 y, int1 xvn)
{                                        
   dl_4l7d[y]   = ma7doan[x%10];       
   dl_4l7d[y-1] = ma7doan[x/10%10];
   dl_4l7d[y-2] = ma7doan[x/100%10];
   dl_4l7d[y-3] = ma7doan[x/1000%10];
   if(xvn==true)                                  
   {
      if(dl_4l7d[y-3]==maso0) 
      {                       
         dl_4l7d[y-3]=0xff;
         if(dl_4l7d[y-2]==maso0) 
         {
            dl_4l7d[y-2]=0xff; 
            if(dl_4l7d[y-1]==maso0) dl_4l7d[y-1]=0xff;   
         }
      }                        
   }          
}  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 405: giai ma so x 2 so, luu o led thu y, tuy chon xoa vn
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void md4l7d_gma_so_bcd_vitri_vn(usi8 x,y, int1 xvn)
{                                        
   dl_4l7d[y]   = ma7doan[x%16];       
   dl_4l7d[y-1] = ma7doan[x/16];              
   if(xvn==true)                                                   
   {                                                           
      if(dl_4l7d[y-1]==maso0) dl_4l7d[y-1]=0xff;                                 
   }                                                      
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham 406: hien thi du lieu 2byte tren 4 led 7 doan
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void xuat_4led_7doan_2so_4led (unsigned int8 bh,bl)
{         
   dl_4l7d[3] = ma7doan[bh/10%10];
   dl_4l7d[2] = ma7doan[bh%10];  
   dl_4l7d[1] = ma7doan[bl/10%10];
   dl_4l7d[0] = ma7doan[bl%10]; 
   xuat_4led_7doan_4so();
}                                 
