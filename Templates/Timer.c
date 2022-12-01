unsigned char cuenta;

void main(){
OPTION_REG.T0CS=0; //Contador Intemo (Modo Timer).
OPTION_REG.T0SE=1; //Flanco de Bajada.
OPTION_REG.PSA=0; //Asignación del Pre-escalador al TMRO por lo tanto el pre-escalador no funciona para el WDT.

OPTION_REG.PS2=1; //Debido a lo anterior se toma la Pre-escala 1:256
OPTION_REG.PS1=1; //Tiempo= (Fosc/4) x 256(pre-escala) x 256 (TMRO)
OPTION_REG.PS0=1; //Tiempo= (Fosc/4) x 65536

INTCON.GIE=1; //Habilitación Global de Interrupciones.
INTCON.T0IE=1; //Habilitación de la Interrupción Local.
TMR0=0x00; //Inicialización del TMRO

TRISC.RC0=0; //Bit O del Puerto C como salida
PORTC.RC0=0; //Limpieza del Puerto C

while(1) PORTC=TMR0; //Valor del TMRO en el PORTC
}

void interrupt (){
if (INTCON.TMR0IF){ //Evalúa si se presenta la activación de Overflow en TMRO
    cuenta++; //incremento de la variable cuenta
    if(cuenta==7){
	cuenta=0;
	PORTC.RC0=~PORTC.RC0; //Invertir el estado del BIT RCO
	INTCON.TMR0IF=0;//Limpiar Bandera de Interrupción del TMR0
        }
    INTCON.TMR0IF=0; //Limpiar Bandera de Interrupción del TMR0
    }
}
