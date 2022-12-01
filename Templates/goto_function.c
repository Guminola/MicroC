int cuenta;
unsigned char TABLA[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
void PAUSE(){
     while(PORTB.RC1==0)
          delay_ms(100);
     }
void main() {
     TRISC=0x00;
     OPTION_REG=OPTION_REG & 0x7F;
     ANSELH=0x00;
     PORTB=0xFF;
     while(1){
          for(cuenta=0;;cuenta++){
               if (cuenta==10)
                  cuenta=0;
               ASCEND: PORTC=TABLA[cuenta];
               delay_ms(500);
               if(PORTB.RC1==0)
                  PAUSE();
               if (PORTB.RC0==1)
                  goto DESCEND;
          }
          for(cuenta=9;;cuenta--){
               if (cuenta<0)
                  cuenta=9;
               DESCEND:PORTC=TABLA[cuenta];
               delay_ms(500);
               if(PORTB.RC1==0)
                  PAUSE();
               if (PORTB.RC0==0)
                   goto ASCEND;
          }
     }
}