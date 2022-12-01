#include  "SHT21_driver.h"
#include  "I2C_driver.h"
#include  "LCD_driver.h"
#include  "PWM.h"

struct{
  char MSB;
  char LSB;
  unsigned char checksum;
  unsigned int RH;
  int TEMP;
}termometer;


void SHT21_T_RH(void){
  SHT21_read(TRIGER_T);
  termometer.TEMP = (termometer.MSB<<8)|termometer.LSB;
  termometer.TEMP = -46.85+((175.72*termometer.TEMP)/65536);
  if(termometer.TEMP>0)termometer.TEMP=termometer.TEMP+1;

  SHT21_read(TRIGER_RH);
  termometer.RH = (termometer.MSB<<8)|termometer.LSB;
  termometer.RH = -6+((125.00*termometer.RH)/65536);
  
  if(termometer.TEMP>36) Ancho_Pulso(1000);
  else if (termometer.TEMP>32) Ancho_Pulso(800);
  else if (termometer.TEMP>26) Ancho_Pulso(400);
  else Ancho_Pulso(0);
}

void SHT21_read(unsigned char TRIGER){
  I2C_start();
  I2C_write(SHT_ADDR_W);
  I2C_write(TRIGER);
  I2C_stop();

  delay_ms(50);
  I2C_start();
  delay_ms(50);

  I2C_write(SHT_ADDR_R);
  termometer.MSB = I2C_read(1);
  termometer.LSB = I2C_read(1);
  termometer.checksum = I2C_read(0);
  I2C_stop();

  termometer.LSB=termometer.LSB>>2;
}

void SHT21_display(void){
  unsigned char temperature[]={"DEGREES:   \n"};
  unsigned char humidity[]={"HUMIDITY:  \n"};

  if(termometer.TEMP<0){
    termometer.TEMP=termometer.TEMP*-1;
    temperature[8] = 0x2D;
  }

  temperature[10] = termometer.TEMP%10+48;
  temperature[9] = termometer.TEMP/10+48;
  humidity[10] = termometer.RH%10+48;
  humidity[9] = termometer.RH/10+48;

  LCD_print(0x10,temperature);
  LCD_print(0x50,humidity);
}