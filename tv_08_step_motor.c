//thu vien dieu khien dong co buoc 
//nguyen dinh phu - dai hoc su pham ky thuat tp hcm
//cac ham dieu khien step motor                
                                    
unsigned int16 stepmotor_fs[]={0x1d,0x17,0x1b,0x0f};
unsigned int16 stepmotor_hs[]={0x1d,0x15,0x17,0x13,0x1b,0x0b,0x0f,0x0d};
                                                                
unsigned int8 stepmotor_i=0;
int1 stepmotor_tn=0;
int1 stepmotor_fh=1;            
                              
void step_motor_quay_thuan_fs()                                    
{                                                     
   rbdc=rbdc & 0xffe0;           
   rbdc=rbdc|stepmotor_fs[stepmotor_i];
   xuat_buzzer_relay();      
   stepmotor_i++;
   stepmotor_i = stepmotor_i & 0x03;
}
void step_motor_quay_nghich_fs()
{
   rbdc=rbdc & 0xffe0;           
   rbdc=rbdc|stepmotor_fs[stepmotor_i];
   xuat_buzzer_relay();
   stepmotor_i--;
   stepmotor_i = stepmotor_i & 0x03;
}                                               
void step_motor_run_tn_fs()
{
   if(stepmotor_tn) step_motor_quay_thuan_fs();
   else             step_motor_quay_nghich_fs();           
}       
                                    
void step_motor_quay_thuan_hs()
{
   rbdc=rbdc & 0xffe0;           
   rbdc=rbdc|stepmotor_hs[stepmotor_i];
   xuat_buzzer_relay();
   stepmotor_i++;
   stepmotor_i = stepmotor_i & 0x07;
}                                               
void step_motor_quay_nghich_hs()
{     
   rbdc=rbdc & 0xffe0;
   rbdc=rbdc|stepmotor_hs[stepmotor_i];
   xuat_buzzer_relay();
   stepmotor_i--;
   stepmotor_i = stepmotor_i & 0x07;
}
void step_motor_run_tn_hs()
{  
   if(stepmotor_tn) step_motor_quay_thuan_hs();
   else             step_motor_quay_nghich_hs();
}                                                                           

void step_motor_run_fs_hs()
{
   if(stepmotor_fh) step_motor_run_tn_fs();
   else             step_motor_run_tn_hs();           
}  


      
