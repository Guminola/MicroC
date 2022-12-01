unsigned char units, decens;
unsigned char TABLE[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void count_up();
void multiplex(unsigned char times);

void main() {
TRISC = 0x00;           //Puerto C salida
TRISD = 0xFC;           //Puerto D salida
OPTION_REG=OPTION_REG & 0x7F;
ANSELH = 0x00;          //Configura PORTB como entrada
PORTB = 0x01;           //Ativa pull-ups
while(1){
     if(PORTB&0x01)
          count_up();   //Funcion contador
     multiplex(25);     //Funcion multiplexado
     }
}

void count_up(){
units++;
if(units==10){
     units=0;
     decens++;
     if(decens==10)
          decens=0;
     }
}

void multiplex(unsigned char times){
PORTD.RD0=0;            //Catodos desabilitados
PORTD.RD1=0;
while(times){
    PORTC=TABLE[units];
    PORTD.RD1=1;        //Activa catodo unidades
    delay_ms(5);
    PORTD.RD1=0;
    PORTC=TABLE[decens];
    PORTD.RD0=1;        //Activa catodo decenas
    delay_ms(5);
    PORTD.RD0=0;
    times--;
    }
}