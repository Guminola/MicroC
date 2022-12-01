#define A1      0x11
#define B1      0x12
#define C1      0x14
#define D1      0x18
#define A2      0x21
#define B2      0x22
#define C2      0x24
#define D2      0x28
#define A3      0x41
#define B3      0x42
#define C3      0x44
#define D3      0x48
#define A4      0x81
#define B4      0x82
#define C4      0x84
#define D4      0x88

#define KEY_PAD_CONF    TRISB
#define KEY_PAD_PORT    PORTB

unsigned char KEY_pad(void);