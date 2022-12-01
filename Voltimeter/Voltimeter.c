unsigned char TABLE[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned int value;

void multiplex();
void bin2bcd(unsigned int value);

struct {
unsigned char unit;
unsigned char decen;
unsigned char cent;
unsigned char mil;
} display;

void main() {
TRISD = 0xF0;

TRISA.RA0=1;    //Bit O del Puerto A como entrada
ANSEL.RA0=1;    //BitO del Puerto A como entrada analoga

ADCON0.ADCS1=1; //Selección del Oscilador Interno FRC
ADCON0.ADCS0=1; //Selección del canal 0 de forma predeterminada.

ADCON1.ADFM=1;  //Justificado a la Derecha. Selección predefinada del Vref (VDD a VSS)
ADCON0.ADON=1;  //Encendido del ADC.


TRISC=0x00;        //Puerto C como salida
PORTC=0x00;        //Limpieza del Puerto C

while(1){
    delay_ms(30);     //Tiempo de Muestreo
    ADCON0.GO_DONE=1;  //Inicio de Conversión
    while(ADCON0.GO_DONE){
        //Espera de la conversión "poleo"
        }

    value=(ADRESL)*4.882;

    bin2bcd(value);
    multiplex();
    }
}

void multiplex(){
PORTC=TABLE[display.unit];
PORTD.RD3=1;
delay_ms(1);
PORTD.RD3=0;
PORTC=TABLE[display.decen];
PORTD.RD2=1;
delay_ms(1);
PORTD.RD2=0;
PORTC=TABLE[display.cent];
PORTD.RD1=1;
delay_ms(1);
PORTD.RD1=0;
PORTC=TABLE[display.mil];
PORTD.RD0=1;
delay_ms(1);
PORTD.RD0=0;
}

void bin2bcd(unsigned int value){
if (value>1000) value=0;
display.mil = value/1000;
display.cent = (value%1000)/100;
display.decen = ((value%1000)%100)/10;
display.unit = ((value%1000)%100)%10;
}