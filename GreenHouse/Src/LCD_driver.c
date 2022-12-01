#include "LCD_driver.h"

void LCD_confi(void){
  LCD_port();
  LCD_reset();
  LCD_function_set(DL_8, NL_2, F5_8);
  LCD_function_set(DL_8, NL_2, F5_8);
  LCD_dislpay_ctrl(DSP_ON, CUR_OFF, BLK_OFF);
  LCD_clear();
  LCD_entry_mode_set(ID, SH);
}

void LCD_port(void){
  ANSEL=0;
  LCD_ctrl_data &= (0<<RS|0<<RW|0<<E);
  LCD_bus_data = 0x30;
  LCD_ctrl_port &= (0<<RS|0<<RW|0<<E);
  LCD_bus_port=0;
}

void LCD_reset(void){
  delay_ms(50);
}

void LCD_write(unsigned char DB){
  LCD_bus_data = DB;
  LCD_ctrl_data |= (1<<E);
  delay_ms(2);
  LCD_ctrl_data &= ~((1<<E));
  delay_ms(2);
}

void LCD_function_set(unsigned char DATA_lenght, unsigned char NUM_L, unsigned char FONT){
  unsigned char DB=0;

  DB = (1<<DB5)|(DATA_lenght<<DB4)|(NUM_L<<DB3)|(FONT<<DB2);
  LCD_write(DB);
}

void LCD_dislpay_ctrl(unsigned char DISPLAY ,unsigned char CURSOR, unsigned char BLINK){
  unsigned char DB=0;

  DB = (1<<DB3)|(DISPLAY<<DSP)|(CURSOR<<CUR)|(BLINK<<BLK);
  LCD_write(DB);
}

void LCD_entry_mode_set(unsigned char ID_mode, unsigned char SHIFT){
  unsigned char DB=0;

  DB = (1<<DB2)|(ID_mode<<ID)|(SHIFT<<S);
  LCD_write(DB);
}

void LCD_clear(void){
  unsigned char DB=0;

  DB = (1<<DB0);
  LCD_write(DB);
}

void LCD_set_DDRAM(unsigned char ADDR){
  unsigned char DB=0;

  DB = (1<<DB7)|ADDR;
  LCD_write(DB);
}

void LCD_print(unsigned char ADDR, unsigned char SBUFFER[]){
  unsigned char i=0;

  LCD_set_DDRAM(ADDR);

  PORTE |= (1<<RS);

  while((SBUFFER[i]!='\n')){
    LCD_write(SBUFFER[i]);
    i++;
  }

  PORTE &=~((1<<RS));
}