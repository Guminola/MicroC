#include "I2C_driver.h"

void I2C_config(void){
  SCL_D = 1;
  SDA_D = 1;

  SSPCON |= Master_clock;
  SSPCON.SSPEN=1;

  SSPADD = SSPADD_speed;
  SSPSTAT = 0x80;
}

void I2C_start(void){
  SSPCON2.SEN=1;
  I2C_wait();
}

void I2C_stop(void){
  SSPCON2.PEN=1;
  I2C_wait();
}

void I2C_reset(void){
  SSPCON2.RCEN=1;
  I2C_wait();
}

void I2C_wait(void){
  while(SSPSTAT.R_W | SSPCON2.ACKEN | SSPCON2.RCEN |SSPCON2.PEN | SSPCON2.RSEN | SSPCON2.SEN);
  return;
}

void I2C_write(unsigned char ADATA){
  SSPBUF=ADATA;
  I2C_wait();
}

unsigned char I2C_read(unsigned char ACK){
  unsigned char buffer;
  I2C_wait();
  SSPCON2.RCEN = 1;
  I2C_wait();

  buffer = SSPBUF;
  I2C_wait();
  SSPCON2.ACKDT = ACK?0:1;
  SSPCON2.ACKEN = 1;
  return buffer;
}