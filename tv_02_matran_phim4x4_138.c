//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//NGUYEN DINH PHU SU PHAM KY THUAT TP HCM
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

unsigned int key_nhan()               
{     
   unsigned int8 maphim,hang,cot;      
   maphim=hang=0xff;
   for(cot=0;cot<4;cot++)                    
   {   
     output_bit(pin_b7,cot&0x02); // Xu?t mã quét c?t ra IC74138
     output_bit(pin_b6,cot&0x01); // Xu?t mã quét c?t ra IC74138
      if     (!input(pin_b2)) {hang=3; break;}
      else if(!input(pin_b3)) {hang=2; break;}       
      else if(!input(pin_b4)) {hang=1; break;}
      else if(!input(pin_b5)) {hang=0; break;}
   }          
   if(hang!=0xff) maphim = cot*4 + hang;
   return(maphim);
}     
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham quet ma tran phim va chong doi tich cuc khi nhan phim
//cach 1             
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                        
unsigned int key_4x4_dw()
{     
   unsigned int8 mp1, mp2;  
   mp1=key_nhan();      
   if(mp1!=0xff)                
   {  
      delay_ms(20);                                           
      mp1=key_nhan();
      do              
      {         
         delay_ms(5); 
         mp2=key_nhan();     
      }                    
      while(mp2==mp1); 
   }             
   return(mp1);
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham quet ma tran phim va chong doi tich cuc khi nhan phim
//cach 2
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx         
unsigned int key_4x4_dw_c2(usi8 dl)
{     
   unsigned int8 mp;  
   mp=key_nhan();         
   if(mp!=0xff)                                   
   {  
      dl_btn++; delay_ms(1);        
      if(dl_btn>=dl) 
      {  
         dl_btn=0; 
         return mp;
      }               
      else  return 0xff; 
   }
   else  return 0xff;     
} 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham quet ma tran phim va chong doi tich cuc khi nha phim
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
unsigned int key_4x4_up()
{                    
   unsigned int8 mp1,mp2;  
   mp1=key_nhan();
   if(mp1!=0xff)   
   {                       
      if(mp2==0xff)             
      {                                                        
         delay_ms(20);   //chong doi
         mp1=key_nhan();
         if(mp1!=0xff)   mp2=mp1;
         return(mp1);    //phim moi                  
      }  
      else               
      {                                                                                                             
         do
         {                                                    
            mp2=key_nhan();
            delay_ms(5); 
         } while(mp2!=0xff);                                                     
         return(mp2);     //thoat khi nha phim          
      }                
   }           
   else                  
   {
      mp2=mp1;
      return(mp1);     //thoat vi khong nhan  
   }      
}
