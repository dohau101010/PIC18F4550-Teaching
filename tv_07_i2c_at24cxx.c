//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//NGUYEN DINH PHU SU PHAM KY THUAT TP HCM
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define at24_addr_wr 0xa0
#define at24_addr_rd 0xa1
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham reset 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void at24_reset()
{                
   i2c_start();         
   i2c_stop();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham khoi tao ghi
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void at24_khoi_tao_ghi(usi16 addr)
{                 
   i2c_start();                       
   i2c_write(at24_addr_wr);  
   i2c_write(addr>>8);         
   i2c_write(addr);         
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham khoi tao doc
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    
void at24_khoi_tao_doc(usi16 addr)
{   
   i2c_start();
   i2c_write(at24_addr_wr);  
   i2c_write(addr>>8);        
   i2c_write(addr);           
   i2c_start();                
   i2c_write(at24_addr_rd);  
}    
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham ghi 1byte
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void at24_ghi_1byte(usi16 addr,usi8 data_1byte)
{          
   i2c_start();                     
   i2c_write(at24_addr_wr);  
   i2c_write(addr>>8);         
   i2c_write(addr);   
   i2c_write(data_1byte);   
   i2c_stop();
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham doc 1 byte
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
unsigned int8 at24_doc_1byte(usi16 addr)
{   
   unsigned int8 data_1byte;
   i2c_start();           
   i2c_write(at24_addr_wr);  
   i2c_write(addr>>8);        
   i2c_write(addr);           
   i2c_start();                
   i2c_write(at24_addr_rd);  
   data_1byte = i2c_read(0);
   i2c_stop();
   return(data_1byte);
}  

