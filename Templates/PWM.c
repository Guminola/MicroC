//prototipado
void PWM_CFG(); //Configuracién de los registros de PWM
void Ancho_Pulso(int ancho_useg); //Ancho de Pulso
void Periodo(int t_useg); //Período de la señal

void main(){
int i;
PWM_CFG();
Periodo(256);
while(1){
    for(i=0;i<=1000;i=i+100){
        Ancho_Pulso(i);
        delay_ms(500);
        }
    }
}

void PWM_CFG()
{
CCP1CON.P1M1=0; //PWM Single output, P1A modulada;P1B,P1C y P1D como I/O.
CCP1CON.P1M0=0;
CCP1CON.CCP1M3=1; //Modo PWM P1A.P1C.P1B.P1D activas en Alto.
CCP1CON.CCP1M2=1; //Pre-escala del Timer2 1:1
PIR1.TMR2IF=0; //Limpieza de la Bandera de interrupcién del TMR2
T2CON.TMR2ON=1; //Activación del TMR2
TRISC.RC2=0;
}
void Ancho_Pulso(int ancho){ //Ancho de Pulso
//De 0 a 1023 partes equivalentes de 0 a 100%
//La frecuencia en el oscilador es de 4MHZ
//Se considera la pre-escala de TMR2 1:1
CCP1CON|=((ancho&0x0003)<<4);
CCPR1L=ancho>>=2;
}

void Periodo(int t_useg){ //Periodo de la señal
//De 1 useg a 256 usegs
//La frecuencia en el oscilador es de 4MHZ
//Se considera la pre-escala de TMR2 1:1
PR2=(t_useg-1);
}