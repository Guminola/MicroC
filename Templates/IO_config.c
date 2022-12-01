void main() {
     TRISC = 0x00;      //Puerto C salida
     //TRISB = 0xFF;    Puerto B Entrada (ya es entrada por default)
     OPTION_REG = OPTION_REG & 0x7F; //weak-pull-up asegura un uno logico
     ANSELH = 0x00;     //Configura Entradas Digitales en PORTB.
     PORTB = 0xFF;      //Activa Pull-ups en puerto B
     while(1)           //¿que bandera utiliza?
         PORTC = PORTB; //Carga valores del puerto B al puerto C
}