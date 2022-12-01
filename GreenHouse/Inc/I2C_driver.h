// Asignacion de terminales y puertos
#define SCL_D           TRISC.RC3
#define SCL             PORTC.RC3
#define SDA_D           TRISC.RC4
#define SDA             PORTC.RC4

// Bits de configuracion
#define Slave_10bits_ss 0x0F
#define Slave_7bits_ss  0x0E
#define Master_clock    0x08
#define Slave_10bits    0x07

// Velocidad I2X
#define FOSC            4000000
#define I2C_speed       100000
#define SSPADD_speed    ((FOSC/(4*I2C_speed))-1)

//Bits de direccion
#define R               1
#define W               0


void I2C_config(void);
void I2C_start(void);
void I2C_stop(void);
void I2C_reset(void);
void I2C_wait(void);
void I2C_write(unsigned char ADATA);
unsigned char I2C_read(unsigned char ACK);