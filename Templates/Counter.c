void main() {
     OPTION_REG.T0CS=1; //Contador Externo.
     OPTION_REG.T0SE=1; //Flanco de Bajada.
     OPTION_REG.PSA=1;  //Asignación del Pre-escalador al WDT por lo tanto el pre-escalador no funciona para el TMRO.

     OPTION_REG.PS2=0;  //Debido a lo anterior Pre-escala 1:1
     OPTION_REG.PS1=0;
     OPTION_REG.PS0=0;
     
     TRISC=0x00;        //Puerto C como salida
     PORTC=0x00;        //Limpieza del Puerto C
     TMR0=0x00;         //inicialización del TMR0
     while(1)
          PORTC=TMR0;   //Valor del TMR0 en el PORTC
}