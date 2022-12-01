void main() {
     TRISC.RC0=0; //bit0 del puerto C salida
     while (1){
          PORTC.RC0^=1; //XOR en bit0 de PORTC, k=1
          delay_ms(250); //Retardo de 1/4 de segundo.
          }
}
//TRISC.RC0=0;
//delay_ms(100);
//TRISC.RC0=1;
//delay_ms(250);