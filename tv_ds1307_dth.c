//dinh nghia dia chi ghi va dia chi doc ds1307
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                    
#define ds13_addr_wr 0xd0
#define ds13_addr_rd 0xd1

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//khai bao 2 mang: 
//mang ghi: giay-phut-gio-thu-ngay-thang-nam-madk_msds  
//mang doc: giay-phut-gio-thu-ngay-thang-nam-madk_msds  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx      
us8 time_w[9]={0x50,0x58,0x14,0x08,0x05,0x06,0x22,0x90,0x95};  
us8 time_r[9]={0x30,0x30,0x10,0x08,0x20,0x02,0x20,0x90,0x96};
#define giay_ds  time_r[0]              
#define phut_ds  time_r[1]                  
#define gio_ds   time_r[2]
#define thu_ds   time_r[3]
#define ngay_ds  time_r[4]
#define thang_ds time_r[5]                  
#define nam_ds   time_r[6]

#define ma_qd   time_w[8] 
#define ma_ds   time_r[8]                                       
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//cap nhat time: giay-phut-gio-thu-ngay-thang-nam-madk_msds  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
void ds1307_cap_nhat_time(int1 sel)                 
{         
   us8 i;   
   i2c_start();
   i2c_write(ds13_addr_wr);        
   i2c_write(0x00);    
   for(i=0;i<9;i++)                          
   {  
      if(sel)  i2c_write(time_w[i]);
      else     i2c_write(time_r[i]);
   }                                 
   i2c_stop();        
}                      
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//doc thoi gian   
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                             
void ds1307_thoi_gian(us8 j)     
{   
   us8 i; 
   i2c_start();
   i2c_write(ds13_addr_wr);
   i2c_write(0x00);                     
   i2c_start();                
                
   i2c_write(ds13_addr_rd);
   for(i=0;i<j;i++) time_r[i]=i2c_read();  
                                 
   i = i2c_read(0); //not ack, don't care i  
   i2c_stop();
}                                                                       
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//kiem tra ma da luu: sai thi cap nhat, dung thi thoat
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx           
void ds1307_setup()                               
{                                              
   ds1307_thoi_gian(9);          
   if(ma_qd!=ma_ds)   
   {
      ds1307_cap_nhat_time(1);
   }
}
