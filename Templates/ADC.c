void main() {
TRISC=0x00;     //Puerto C como salida - mostrar� el ADRESL
TRISD.RD0=0;    //Bit O del Puerto C como salida - Mostrar�n el ADRESH
TRISD.RD1=0;    //Bit 1 del Puerto C como salida

TRISA.RA0=1;    //Bit O del Puerto A como entrada
ANSEL.RA0=1;    //BitO del Puerto A como entrada analoga

ADCON0.ADCS1=1; //Selecci�n del Oscilador Interno FRC
ADCON0.ADCS0=1; //Selecci�n del canal 0 de forma predeterminada.

ADCON1.ADFM=1;  //Justificado a la Derecha. Selecci�n predefinada del Vref (VDD a VSS)

ADCON0.ADON=1;  //Encendido del ADC.

while(1){
    delay_ms(100);     //Tiempo de Muestreo
    ADCON0.GO_DONE=1;  //Inicio de Conversi�n
    
    while(ADCON0.GO_DONE){
        //Espera de la conversi�n "poleo"
        }
        
    PORTC=ADRESL;      //Muestra los 10 bits de Conversion.
    PORTD=ADRESH;
    }
}