#include  "LCD_driver.h"
#include  "I2C_driver.h"
#include  "Key_Pad.h"
#include  "DS1307_driver.h"
#include  "SHT21_driver.h"
#include  "PWM.h"

void menu(void);
void APDS9002(void);

unsigned char APDS_cont, APDS_flag;

void main(void){
  const code unsigned char CASCADA[4]={0x01,0x02,0x04,0x08};
  unsigned char i;

  //Configuracion puerto del teclado
  ANSELH=0x00;        //PORTB digital
  KEY_PAD_CONF=0xF0;  //4 bits entrada 4 bits salida
  
  //Configuracion bits de las valvulas
  TRISA.RA3=0;    ANSEL.RA3=0;   PORTA.RA3=0;   //Bit3 Puerto A salida digital
  TRISA.RA4=0;    ANSEL.RA4=0;   PORTA.RA3=0;   //Bit4 Puerto A salida digital
  TRISA.RA5=0;    ANSEL.RA5=0;   PORTA.RA3=0;   //Bit5 Puerto A salida digital
  
  //Configuracion bits del motor a pasos
  TRISC.RC0=0;    PORTC.RC0=0;
  TRISC.RC1=0;    PORTC.RC1=0;
  TRISC.RC5=0;    PORTC.RC5=0;
  TRISC.RC6=6;    PORTC.RC6=0;

  //Configuracion bits del APDS-9002
  TRISA.RA0=1;    //Bit0 Puerto A entrada
  ANSEL.RA0=1;    //Bit0 Puerto A analoga
  APDS_cont=5;    //variable de control
  APDS_flag=0;    //Bandera  de control
  
  //Configuracion ADC para lectura del APDS-9002
  ADCON0.ADCS1=1; //Selecci�n del Oscilador Interno FRC
  ADCON0.ADCS0=1; //Selecci�n del canal 0 de forma predeterminada.
  ADCON1.ADFM=0;  //Justificado a la izquierda. Selecci�n predefinada del Vref (VDD a VSS)
  ADCON0.ADON=1;  //Encendido del ADC.
  
  //Configuracion PWM para el motor DC
  PWM_CFG();      //Configuraci�n de los registros de PWM
  Periodo(256);   //Periodo de la se�al

  //Configuracion del I2C y el LCD
  I2C_config();
  LCD_confi();

  while(1){
     for(i=0;i<4;i++){
        KEY_PAD_PORT = CASCADA[i];
        if(KEY_PAD_PORT==D1) {
          LCD_clear(); delay_ms(500); menu();
        }
     }
     DS1307_read();     //Operacion del reloj
     SHT21_T_RH();      //Operacion del termometro
     
     for(i=0;i<4;i++){
        KEY_PAD_PORT = CASCADA[i];
        if(KEY_PAD_PORT==D1) {
          LCD_clear(); delay_ms(500); menu();
        }
     }
     DS1307_display();  //Mostrar datos del reloj
     SHT21_display();   //Mostrar datos del termometro
     
     for(i=0;i<4;i++){
        KEY_PAD_PORT = CASCADA[i];
        if(KEY_PAD_PORT==D1) {
          LCD_clear(); delay_ms(500); menu();
        }
     }
     APDS9002();       //Operacion del sensor de luz
  }
}

void menu(){
  unsigned char menu0[9]={"OPTIONS\n"};
  unsigned char menu1[12]={"1-Set Time\n"};
  unsigned char menu2[12]={"2-Set Date\n"};
  unsigned char KEY_return, i;
  
  //Mostrar menu en el LCD
  LCD_print(0x04,menu0);
  LCD_print(0x40,menu1);
  LCD_print(0x10,menu2);

  //Selecciona opcion
  KEY_return = KEY_pad();     //Funcion de seleccion
  if(KEY_return==0x01){
    DS1307_set(ADD_hour);     //Cambiar hora
    DS1307_set(ADD_min);      //Cambiar minutos
    DS1307_set(ADD_sec);      //Cambiar segundos
  }
  else if(KEY_return==0x02){
    DS1307_set(ADD_day);      //Cambiar dia
    DS1307_set(ADD_month);    //Cambiar mes
    DS1307_set(ADD_year);     //Cambiar a�o
  }
}

void APDS9002(void){
  unsigned char value;
 
  delay_ms(30);      //Tiempo de Muestreo
  ADCON0.GO_DONE=1;  //Inicio de Conversi�n
  while(ADCON0.GO_DONE){
  //Espera de la conversi�n "poleo"
  }
  
  //Manejo de bits para control del motor a pasos
  value=ADRESH;
  if(value>80 && APDS_cont==5){
    PORTC.RC0=1;
    delay_ms(20);
    PORTC.RC6=0;
    delay_ms(20);
    PORTC.RC1=1;
    delay_ms(20);
    PORTC.RC0=0;
    delay_ms(20);
    PORTC.RC5=1;
    delay_ms(20);
    PORTC.RC1=0;
    delay_ms(20);
    PORTC.RC6=1;
    delay_ms(20);
    PORTC.RC5=0;
    delay_ms(20);
    APDS_cont=4;
    APDS_flag=0;
  }
  else if(value<80 && value>50 && APDS_cont==4){
    PORTC.RC6=0;
    delay_ms(50);
    PORTC.RC5=1;
    delay_ms(50);
    PORTC.RC1=0;
    delay_ms(50);
    if(APDS_flag==0) APDS_cont=3;
    else if(APDS_flag==1) APDS_cont=5;
  }
  else if(value<50 && value>20 && APDS_cont==3){
    PORTC.RC5=0;
    delay_ms(50);
    PORTC.RC1=1;
    delay_ms(50);
    PORTC.RC0=0;
    delay_ms(50);
    if(APDS_flag==0) APDS_cont=2;
    else if(APDS_flag==1) APDS_cont=4;
  }
    else if(value<20 && value>5 && APDS_cont==2){
    PORTC.RC1=0;
    delay_ms(50);
    PORTC.RC0=1;
    delay_ms(50);
    PORTC.RC6=0;
    delay_ms(50);
    if(APDS_flag==0) APDS_cont=1;
    else if(APDS_flag==1) APDS_cont=3;
  }
    else if(value<5 && APDS_cont==1){
    PORTC.RC0=0;
    delay_ms(50);
    PORTC.RC6=1;
    delay_ms(50);
    PORTC.RC0=1;
    delay_ms(50);
    APDS_cont=2;
    APDS_flag=1;
  }
}