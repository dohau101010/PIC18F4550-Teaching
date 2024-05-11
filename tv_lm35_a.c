float adc_doc_nhiet_do(us8 solan)                      
{
   float kq_adc;             
   delay_us(20);                                          
   kq_adc = 0;             
   for(int8 i=0;i<solan;i++)  
   {
      kq_adc = kq_adc + read_adc();                        
   }
   kq_adc = kq_adc/solan; 
   return kq_adc; 
}
us16 so_ng,so_tp;
void float_to_ng_2so_tp(float st)                      
{   
   so_ng = st/1;       //nguyen                          
   st = st-so_ng;      //tphan
   st = st*100;                                                         
   so_tp = st/1;   
}

void lm35a_doc_nhiet_do(us8 sl)
{
   float lm35; 
   lm35=adc_doc_nhiet_do(sl); 
   lm35 = lm35a/2.046;
   float_to_ng_2so_tp(lm35); 
   lm35_ng = so_ng;
   lm35_tp = so_tp;
}

