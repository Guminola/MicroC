#define  DB0    0
#define  DB1    1
#define  DB2    2
#define  DB3    3
#define  DB4    4
#define  DB5    5
#define  DB6    6
#define  DB7    7

#define  ID     1
#define  S      0
#define  BLK    0
#define  CUR    1
#define  DSP    2
#define  F      2
#define  N      3
#define  DL     3
#define  Busy   7
#define  RS     0
#define  RW     1
#define  E      2
#define  SC     3
#define  RL     2

#define  DL_4   0
#define  DL_8   1
#define  NL_1   0
#define  NL_2   1
#define  F5_8   0
#define  F5_10  1

#define  DSP_ON     1
#define  CUR_ON     1
#define  BLK_ON     1
#define  DSP_OFF    0
#define  CUR_OFF    0
#define  BLK_OFF    0

#define  ID     1
#define  SH     0

#define  LCD_ctrl_port     TRISE
#define  LCD_ctrl_data     PORTE

#define  LCD_bus_port      TRISD
#define  LCD_bus_data      PORTD

#define  LCD1              0
#define  LCD2              1


//void LCD(void);
void LCD_confi(void);
void LCD_port(void);
void LCD_reset(void);
void LCD_enable(unsigned char DB);

void LCD_write(unsigned char DB);

void LCD_function_set(unsigned char DATA_lenght, unsigned char NUM_L, unsigned char FONT);

//configuracion del LCD
void LCD_dislpay_ctrl(unsigned char DISPLAY ,unsigned char CURSOR, unsigned char BLINK);

//Activacion LCD
void LCD_entry_mode_set(unsigned char ID_mode, unsigned char SHIFT);
void LCD_clear(void);
void LCD_set_DDRAM(unsigned char ADDR);

void LCD_print(unsigned char ADDR, unsigned char SBUFFER[]);