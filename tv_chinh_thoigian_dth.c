int1 tt_htg=1;
signed int8 gt_mod=0, tg_chinh=0;
//signed int8  gt_mod=0, tg_chinh=0;
#define tang 0
#define giam 1

/*Ham co chuc nang nhan dia chi va du lieu de luu vao dia chi tuong ung roi thuc hien*/
void ds1307_luu_vao_ds(us8 dcdt,dt)
{
   i2c_start();
   i2c_write(ds13_addr_wr);
   i2c_write(dcdt); //dia chi doi tuong
   i2c_write(dt); //goi doi tuong (giay_ds) ra ds1307
   i2c_stop();
}

unsigned int8 tang_or_giam_so_bcd(us8 x, int1 sel)
{
   unsigned int8 y,dv,ch,v;
   ch=(x>>4);  dv=x&0x0f;
   y=ch*10+dv;
   if(sel==0)  y++;
   else        y--;
   ch=y/10; dv=y%10;
   v=(ch<<4)|dv;
   return(v);
}
void clr_lcd()
{
   lcd_goto(0,0);
   lcd_data("                    ");
   lcd_goto(1,0);
   lcd_data("                    ");
   lcd_goto(2,0);
   lcd_data("                    ");
   lcd_goto(3,0);
   lcd_data("                    ");
}
void hienthi_background()
{
   lcd_goto(0,0);
   lcd_data("  DO HOANG THANG  ");
   lcd_goto(1,0);
   lcd_data(" CON KU 20 CM" );
}
void phim_mod_chinh()
{
   if(phim_mod())
   {
      gt_mod++;
      if(gt_mod==8)
     { clr_lcd(); hienthi_background();   while(input(mod));};
  
      if(gt_mod>8) 
      {gt_mod=0;clr_lcd();}
   }
}
void tang_giay()
{
   if(giay_ds==0x59) giay_ds=0;
   else giay_ds=tang_or_giam_so_bcd(giay_ds,tang);
   ds1307_luu_vao_ds(0,giay_ds); //0-la dia chi cua giay; tham so giay_ds moi vua tang xong
   //trao 2 tham so: ... thong so 2 la gia tri cua giay can luu tru vao o nho co dia chi 0
}
void tang_phut()
{
   if(phut_ds==0x59) phut_ds=0;
   else phut_ds=tang_or_giam_so_bcd(phut_ds,tang);
   ds1307_luu_vao_ds(1,phut_ds); //1-dia chi cua phut
}

void tang_gio()
{
   if(gio_ds==0x23) gio_ds=0;
   else gio_ds=tang_or_giam_so_bcd(gio_ds,tang);
   ds1307_luu_vao_ds(2,gio_ds); //2-dia chi cua gio
}
void chinh_tang_gpg()
{
   switch(gt_mod)
   {
      case 3: tang_giay();
              break;
      case 2: tang_phut();
              break;
      case 1: tang_gio();
              break;
      default:break;
   }
}

void tang_nam()
{
   if(nam_ds==0x99) nam_ds=0;
   else nam_ds=tang_or_giam_so_bcd(nam_ds,tang);
   ds1307_luu_vao_ds(6,nam_ds); 
}
void tang_thang()
{
   if(thang_ds==0x12) thang_ds=1;
   else thang_ds=tang_or_giam_so_bcd(thang_ds,tang);
   ds1307_luu_vao_ds(5,thang_ds); 
}

void tang_ngay()
{
   if(ngay_ds==0x31) ngay_ds=1;
   else ngay_ds=tang_or_giam_so_bcd(ngay_ds,tang);
   ds1307_luu_vao_ds(4,ngay_ds); 
}

void chinh_tang_ntn()
{
   switch(gt_mod)
   {
      case 6: tang_nam();    break;
      case 5: tang_thang();  break;
      case 4: tang_ngay();   break;
      default: break;
   }
}

void chinh_tang_thu()
{
   if(thu_ds==8)  thu_ds=2;
   else           thu_ds++;
   ds1307_luu_vao_ds(3,thu_ds);
}

void phim_up_chinh()
//duoc hieu chinh lai de chon hien thi
//giay so to theo yeu cau de bai va 
//cap nhat chinh cac thong so o LCD
{
   if(phim_up())
   {
      if(gt_mod!=0)
      {
         tg_chinh=0;
         if(gt_mod<4)         chinh_tang_gpg();
         else if(gt_mod<7)    chinh_tang_ntn();
         else if(gt_mod==7)   chinh_tang_thu();
         hienthi_lcd_all();
      }
      else tt_htg=1;
   }
}

void giam_giay()
{
   if(giay_ds==0) giay_ds=0x59;
   else giay_ds=tang_or_giam_so_bcd(giay_ds,giam); //tra ve so BCD bang giay_ds(bCD) tang len 1
   ds1307_luu_vao_ds(0,giay_ds); //0-la dia chi giay; tham so giay_ds moi vua tang xong
}

void giam_phut()
{
   if(phut_ds==0) phut_ds=0x59;
   else phut_ds=tang_or_giam_so_bcd(phut_ds,giam);
   ds1307_luu_vao_ds(1,phut_ds); //1-la dia chi giay; tham so giay_ds moi vua tang xong
}

void giam_gio()
{
   if(gio_ds==0) gio_ds=0x23;
   else gio_ds=tang_or_giam_so_bcd(gio_ds,giam);
   ds1307_luu_vao_ds(2,gio_ds); //2-la dia chi giay; tham so giay_ds moi vua tang xong
}

void chinh_giam_gpg()
{
   switch(gt_mod)
   {
      case 3: giam_giay();
              break;
      case 2: giam_phut();
              break;
      case 1: giam_gio();
              break;
      default:break;
   }
}

void giam_nam()
{
   if(nam_ds==0) nam_ds=0x99;
   else nam_ds=tang_or_giam_so_bcd(nam_ds,giam);
   ds1307_luu_vao_ds(6,nam_ds); 
}
void giam_thang()
{
   if(thang_ds==1) thang_ds=0x12;
   else thang_ds=tang_or_giam_so_bcd(thang_ds,giam);
   ds1307_luu_vao_ds(5,thang_ds); 
}

void giam_ngay()
{
   if(ngay_ds==1) ngay_ds=0x31;
   else ngay_ds=tang_or_giam_so_bcd(ngay_ds,giam);
   ds1307_luu_vao_ds(4,ngay_ds); 
}

void chinh_giam_ntn()
{
   switch(gt_mod)
   {
      case 6: giam_nam();    break;
      case 5: giam_thang();  break;
      case 4: giam_ngay();   break;
      default: break;
   }
}

void chinh_giam_thu()
{
   if(thu_ds==2)  thu_ds=8;
   else           thu_ds--;
   ds1307_luu_vao_ds(3,thu_ds);
}

void phim_dw_chinh()
//duoc hieu chinh lai de chon hien thi
//giay so nho theo yeu cau de bai va 
//cap nhat chinh cac thong so o LCD
{
   if(phim_dw())
   {
      if(gt_mod!=0)
      {
         tg_chinh=0;
         if(gt_mod<4)         chinh_giam_gpg();
         else if(gt_mod<7)    chinh_giam_ntn();
         else if(gt_mod==7)   chinh_giam_thu();   
         hienthi_lcd_all();
      }
      else tt_htg=0;
   }
}
