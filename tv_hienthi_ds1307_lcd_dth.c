void hienthi_lcd_all()
{
    us8 giay, phut, gio; 
    us8 ngay, thang, nam;
    giay=giay_ds/16*10  +giay_ds%16;
    phut=phut_ds/16*10  +phut_ds%16;
    gio=gio_ds/16*10    +gio_ds%16;
    
    lcd_soto(gio/10, 1, 0);
    lcd_soto(gio%10, 1, 3);
    lcd_soto(phut/10, 1, 7);
    lcd_soto(phut%10, 1, 10);
    lcd_soto(giay/10, 1, 14);
    lcd_soto(giay%10, 1, 17);

    ngay=ngay_ds/16*10    +ngay_ds%16;
    thang=thang_ds/16*10  +thang_ds%16;
    nam=nam_ds/16*10   +nam_ds%16;
    lcd_goto(3,0);
    printf(lcd_data, "%02U/%02U/20%02U", ngay, thang, nam);
    lcd_goto(3,17);
   SWITCH (thu_ds)
   {
      CASE 1: lcd_data ("SUN"); break;
      CASE 2: lcd_data ("MON"); break;
      CASE 3: lcd_data ("TUE"); break;
      CASE 4: lcd_data ("WED"); break;
      CASE 5: lcd_data ("THU"); break;
      CASE 6: lcd_data ("FRI"); break;
      CASE 7: lcd_data ("SAT"); break;
      DEFAULT: break;
   }
   
}
