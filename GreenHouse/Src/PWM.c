/*------------------------------------------------
Dise�ado por: Mtro. Alberto de la Mora G�lvez
         M.C. Jos� Miguel Mor�n loza
         M.C. Alicia Garcia Arreola
------------------------------------------------*/
#include  "PWM.h"

void PWM_CFG()
{
CCP1CON.P1M1=0;   //PWM Single output, P1A modulada;P1B,P1C y P1D como I/O.
CCP1CON.P1M0=0;
CCP1CON.CCP1M3=1; //Modo PWM P1A.P1C.P1B.P1D activas en Alto.
CCP1CON.CCP1M2=1; //Pre-escala del Timer2 1:1
PIR1.TMR2IF=0;    //Limpieza de la Bandera de interrupci�n del TMR2
T2CON.TMR2ON=1;   //Activaci�n del TMR2
TRISC.RC2=0;
}
void Ancho_Pulso(int ancho){ //Ancho de Pulso de 0 a 1023 partes equivalentes de 0 a 100%
//La frecuencia en el oscilador es de 4MHZ
//Se considera la pre-escala de TMR2 1:1
CCP1CON|=((ancho&0x0003)<<4);
CCPR1L=ancho>>=2;
}

void Periodo(int t_useg){ //Periodo de la se�al de 1 useg a 256 usegs
//La frecuencia en el oscilador es de 4MHZ
//Se considera la pre-escala de TMR2 1:1
PR2=(t_useg-1);
}