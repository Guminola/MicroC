#include  "DS1307_driver.h"
#include  "I2C_driver.h"
#include  "LCD_driver.h"
#include  "Key_Pad.h"

unsigned char i;
struct{
  unsigned char sec;
  unsigned char min;
  unsigned char hour;
  unsigned char date;
  unsigned char day;
  unsigned char month;
  unsigned char year;
}timer;

void DS1307_read(void){
  //Start i2c and conect the device
  I2C_start();
  I2C_write(DS_ADDR_W);
  I2C_write(0x00);
  I2C_stop();

  //Read the data from the DS1307
  I2C_start();
  I2C_write(DS_ADDR_R);
  timer.sec = I2C_read(1);     //Seconds register 0
  timer.min = I2C_read(1);     //Minutes register 1
  timer.hour = I2C_read(1);    //Hours register 2
  timer.date = I2C_read(1);    //Date register 3
  timer.day = I2C_read(1);     //Day register 4
  timer.month = I2C_read(1);   //Month register 5
  timer.year = I2C_read(0);    //Year register 6
  I2C_stop();
  
  //BCD to decimal converion
  DS1307_bcd2dec();
}

void DS1307_write(unsigned char ADDR, unsigned char DATA){
  I2C_start();                  
  I2C_write(DS_ADDR_W);
  I2C_write(ADDR);        //Set register address
  I2C_write(DATA);        //Load data to selected address
  I2C_stop();
}

void DS1307_bcd2dec(void){
  //BCD to decimal
  timer.sec = (timer.sec>>4)*10+(timer.sec&0x0F);
  timer.min = (timer.min>>4)*10+(timer.min&0x0F);
  timer.hour = (timer.hour>>4)*10+(timer.hour&0x0F);
  timer.date = (timer.date>>4)*10+(timer.date&0x0F);
  timer.day = (timer.day>>4)*10+(timer.day&0x0F);
  timer.month = (timer.month>>4)*10+(timer.month&0x0F);
  timer.year = (timer.year>>4)*10+(timer.year&0x0F);
  
  //Check valves condition
  //Water valve. Every day, 8:00am to 8:30am
  if((timer.hour==8) && (timer.min<30))
    PORTA.RA3=1;
  else PORTA.RA3=0;
  //Fertilizer valve. Every 7 days, 9:00am to 9:15am
  if(((timer.day%7)==0) &&(timer.hour==9) && (timer.min<15))
    PORTA.RA4=1;
  else PORTA.RA4=0;
  //Insecticide valve. Every 15 days, 12:00am to 12:15am
  if((timer.day%15==0) &&(timer.hour==12) && (timer.min>15))
    PORTA.RA5=1;
  else PORTA.RA5=0;
}

void DS1307_display(void){
unsigned char time[]={"TIME:  :  :   \n"};
unsigned char calendar[]={"DATE:  /  /20  \n"};

  //Load readed values to text chains
  time[12] = timer.sec%10+48;
  time[11] = timer.sec/10+48;
  time[9] = timer.min%10+48;
  time[8] = timer.min/10+48;
  time[6] = timer.hour%10+48;
  time[5] = timer.hour/10+48;
  calendar[14] = timer.year%10+48;
  calendar[13] = timer.year/10+48;
  calendar[9] = timer.month%10+48;
  calendar[8] = timer.month/10+48;
  calendar[6] = timer.day%10+48;
  calendar[5] = timer.day/10+48;

  //Display time and date on the LCD
  LCD_print(0x00,time);
  LCD_print(0x40,calendar);

}

void DS1307_set(unsigned char MODE){
  unsigned char KEY_return, flag, DATA;
  unsigned char year_flag=0;
  unsigned char time[4]={"00\n"};
  unsigned char sec[9]={"Seconds\n"};
  unsigned char min[9]={"Minutes\n"};
  unsigned char hour[6]={"Hour\n"};
  unsigned char day[5]={"Day\n"};
  unsigned char month[7]={"Month\n"};
  unsigned char year[6]={"Year\n"};

  LCD_clear();
  LCD_print(0x47,time);

  switch(MODE){
    case 0: LCD_print(0x05,sec);     break;
    case 1: LCD_print(0x05,min);     break;
    case 2: LCD_print(0x06,hour);    break;
    case 4: LCD_print(0x06,day);     break;
    case 5: LCD_print(0x05,month);   break;
    case 6: LCD_print(0x05,year);    break;
  }

  for(flag=0;flag<2;+flag++){
    KEY_return = KEY_pad();
    if(KEY_return == 0x11) KEY_return = 0x00;

    time[0+flag]=(0x30+KEY_return);

    if(flag==0){
        KEY_return = KEY_return*0x10;
        DATA=KEY_return;
        }
    else if(flag==1) DATA = KEY_return + DATA;

    LCD_print((0x47),time);
  }
    if(MODE==0 && DATA>0x59) DATA = 0x59;
    else if(MODE==1 && DATA>0x59) DATA = 0x59;
    else if(MODE==2 && DATA>0x23) DATA = 0x23;
    else if(MODE==4 && DATA>0x31) DATA = 0x31;
    else if(MODE==5 && DATA>0x12) DATA = 0x12;

    DS1307_write(MODE,DATA);
    delay_ms(500);
    LCD_clear();
    delay_ms(100);
}