//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//NGUYEN DINH PHU SU PHAM KY THUAT TP HCM
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//ham xuat 2 byte
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void xuat_2byte(unsigned int16 v)
{
   int8 i;
   #bit msb = v.15
   for(i=0;i<16;i++)
   {                                                 
      output_bit(ssdo,msb);    
      output_low(ssck);   
      output_high(ssck);
      v= v<<1;         
   }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//chuong trinh con xuat ra led ma tran
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void xuat_matranled( usi16 mahang,usi16 macot1,
                     usi16 macot2,usi16 macot3)
{      
   xuat_2byte(macot3);  
   xuat_2byte(macot2);
   xuat_2byte(macot1);  
   xuat_2byte(mahang);
      
   output_high(rck_mtl); 
   output_low(rck_mtl);
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//chuong trinh con xuat ra led ma tran
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// void tat_matranled()
// {      
   // xuat_2byte(0); xuat_2byte(0);
   // xuat_2byte(0); xuat_2byte(0);           
   // output_high(rck_matranled); 
   // output_low(rck_matranled);
// }
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//hieu chinh 4bit cao
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
unsigned  int8 hieu_chinh_4bit_cao(unsigned int8 xzy)
{
   int1  btg;
   unsigned int8   bx;   
   #bit bit4  = bx.4
   #bit bit5  = bx.5
   #bit bit6  = bx.6
   #bit bit7  = bx.7
   bx=xzy;
   btg=bit4;   bit4=bit7;  bit7=btg;
   btg=bit5;   bit5=bit6;  bit6=btg;      
   return(bx);  
}   
