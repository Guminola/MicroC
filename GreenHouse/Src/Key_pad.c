#include  "Key_Pad.h"

unsigned char KEY_pad(void){
  const code unsigned char CASCADA[4]={0x01,0x02,0x04,0x08};
  unsigned char i, KEY_return;
  KEY_return=0x00;
  delay_ms(500);
  while(KEY_return==0x00){
  for(i=0;i<4;i++){
    KEY_PAD_PORT = CASCADA[i];
    switch(KEY_PAD_PORT){
      case D1: KEY_return = 0x11; break;
      case D2: KEY_return = 0x11; break;
      //case D3: KEY_return = '=';  break;
      //case D4: KEY_return = '+';  break;

      case C1: KEY_return = 0x01; break;
      case C2: KEY_return = 0x02; break;
      case C3: KEY_return = 0x03; break;
      //case C4: KEY_return = '-';  break;

      case B1: KEY_return = 0x04; break;
      case B2: KEY_return = 0x05; break;
      case B3: KEY_return = 0x06; break;
      //case B4: KEY_return = '*';  break;

      case A1: KEY_return = 0x07; break;
      case A2: KEY_return = 0x08; break;
      case A3: KEY_return = 0x09; break;
      //case A4: KEY_return = '/';  break;
      
      //default: KEY_return = 0x00; break;
    }
  }
  }
  return KEY_return;
}