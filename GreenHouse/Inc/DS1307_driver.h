#define DS_ADDR            0x68
#define DS_ADDR_R          ((DS_ADDR<<1)+R)
#define DS_ADDR_W          ((DS_ADDR<<1)+W)

#define ADD_sec            0
#define ADD_min            1
#define ADD_hour           2
#define ADD_day            4
#define ADD_month          5
#define ADD_year           6

void DS1307_read(void);
void DS1307_write(unsigned char ADDR, unsigned char DATA);
void DS1307_bcd2dec(void);
void DS1307_set(unsigned char MODE);
void DS1307_display(void);