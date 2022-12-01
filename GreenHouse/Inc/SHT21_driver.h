#define SHT_ADDR            0x40
#define SHT_ADDR_R          ((SHT_ADDR<<1)+R)
#define SHT_ADDR_W          ((SHT_ADDR<<1)+W)

#define TRIGER_T            0xF3 
#define TRIGER_RH           0xF5

void SHT21_T_RH(void);
void SHT21_read(unsigned char TRIGER);
void SHT21_display(void);