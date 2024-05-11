//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//NGUYEN DINH PHU SU PHAM KY THUAT TP HCM
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//dinh nghia cac trang thai co nhan va khong nhan phim
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
#define co_nhan      1            
#define khong_nhan   0           
#define c_ktnp       1  //co kiem tra nha phim          
#define k_ktnp       0  //khong kiem tra nha phim 
// #define sole_1       false            
// #define sole_2       true   
                              
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
//chuong trinh kiem tra phim bt1
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
unsigned int16 dl_btn=0; 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//phim bt0-cach 1: co chong doi, delay 20ms, cho nha phim
//dinh nghia them 1 so ten khac     
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                       
#define phim_on_c1  phim_bt0_c1    
#define phim_run_c1 phim_bt0_c1 
#define phim_up_c1  phim_bt0_c1       

int1 phim_bt0_c1(int1 ktnp,usi16 dl)   
{                    
   if (!input(bt0))   
   {        
      delay_ms(20);                                     
      if (!input(bt0))
      {
         if(ktnp) while(!input(bt0));
         delay_ms(dl);
         return co_nhan;      
      }                      
      return khong_nhan;   
   }         
  return khong_nhan;  
}     
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//phim bt1-cach 1: co chong doi, delay 20ms, cho nha phim
//dinh nghia them 1 so ten khac      
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
#define phim_off_c1   phim_bt1_c1   
#define phim_mode_c1  phim_bt1_c1 
#define phim_stop_c1  phim_bt1_c1 
#define phim_clr_c1   phim_bt1_c1
int1 phim_bt1_c1(int1 ktnp,usi16 dl)                                               
{
   if(!input(bt1))   
   {                       
      delay_ms(20);
      if(!input(bt1))
      {
         if(ktnp) while(!input(bt1));    
         delay_ms(dl);
         return co_nhan;
      } 
      return khong_nhan;
   }
   return khong_nhan;  
}       
     
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//phim bt2-cach 1: co chong doi, delay 20ms, cho nha phim
//dinh nghia them 1 so ten khac      
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
#define phim_inv_c1 phim_bt2_c1   
#define phim_dw_c1  phim_bt2_c1                  

int1 phim_bt2_c1(int1 ktnp,usi16 dl)      
{
   if(!input(bt2))   
   {        
      delay_ms(20);                
      if(!input(bt2))
      {
         if(ktnp) while(!input(bt2));    
         delay_ms(dl);
         return co_nhan;
      }                                     
      return khong_nhan; 
   }
   return khong_nhan;  
}      
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//phim bt3-cach 1: co chong doi, delay 20ms, cho nha phim
//dinh nghia them 1 so ten khac      
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx     

#define phim_ud_c1    phim_bt3_c1


int1 phim_bt3_c1(int1 ktnp,usi16 dl)      
{                       
   if(!input(bt3))   
   {                                        
      delay_ms(20);                       
      if(!input(bt3))
      {                      
         if(ktnp) while(!input(bt3));    
         delay_ms(dl);
         return co_nhan;
      } 
      return khong_nhan;   
      }                       
   return khong_nhan;  
}  
      
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
//cac ham con cua cac phim nhan don theo cach 2
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  
//phim bt0-cach 2: nhan so lan thuc hien la bien dl
//kiem tra neu co nhan thi tang bien dem dl_btn,delay 1ms.   
//Neu bien dl_btn = dl thi reset dl_btn = 0,
//xem nhu co nhan va ket thuc. 
//con lai thi xem nhu chua nhan hoac chua du thoi gian nhan
//moi chu ky thuc hien lon nhat la 1ms - khong cho nha phim 
//dinh nghia them 1 so ten khac  
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    
#define phim_on_c2  phim_bt0_c2                    
#define phim_run_c2 phim_bt0_c2      
#define phim_up_c2  phim_bt0_c2  

int1 phim_bt0_c2(usi16 dl)  
{                      
   if(!input(bt0))                       
   {   
      dl_btn++;   delay_us(500);               
      if(dl_btn>=dl) 
      {  
         dl_btn=0;
         return co_nhan;
      }     
      else  return khong_nhan; 
   }
   else  return khong_nhan;    
} 
    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham chong doi cach 2 cho phim bt1
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx      
#define phim_off_c2   phim_bt1_c2   
#define phim_stop_c2  phim_bt1_c2  
#define phim_mode_c2  phim_bt1_c2
#define phim_clr_c2   phim_bt3_c2

int1 phim_bt1_c2(usi16 dl)
{                      
   if(!input(bt1))   
   {           
      dl_btn++;  delay_us(500);  
      if(dl_btn >= dl)    
      {  
         dl_btn =0;
         return co_nhan;
      }     
      else return khong_nhan; 
   }
   else return khong_nhan;    
}     

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham chong doi cach 2 cho phim bt2
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
#define phim_inv_c2   phim_bt2_c2  
#define phim_dw_c2    phim_bt2_c2  

int1 phim_bt2_c2(usi16 dl)
{                      
   if(!input(bt2))   
   {                                  
      dl_btn++;  delay_us(500);  
      if(dl_btn >= dl) 
      {  
         dl_btn =0;
         return co_nhan;   
      }     
      else return khong_nhan; 
   }
   else return khong_nhan;    
}                                       
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham chong doi cach 1 cho phim bt3
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx        
//#define phim_mode_c2  phim_bt3_c2  
#define phim_ud_c2    phim_bt3_c2  
                         
int1 phim_bt3_c2(usi16 dl) 
{                      
   if(!input(bt3))    
   {                         
      dl_btn++;    delay_us(500);                                                
      if(dl_btn >= dl) 
      {  
         dl_btn =0;                                 
         return co_nhan; 
      }     
      else return khong_nhan; 
   }
   else return khong_nhan;    
}           
