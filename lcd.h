#ifndef LCD_H_
#define LCD_H_

#define LCDPORT         GPIO_PORTB_BASE
#define LCDPORTENABLE   SYSCTL_PERIPH_GPIOB
#define RS              GPIO_PIN_0
#define E               GPIO_PIN_1
#define D4              GPIO_PIN_4
#define D5              GPIO_PIN_5
#define D6              GPIO_PIN_6
#define D7              GPIO_PIN_7


void LCD_ayar();
void LCD_komut(unsigned char c);
void LCD_karaktergir(unsigned char d);
void LCD_temizle();
void LCD_yaz(char *s,int x,int y);
void LCD_cursor(char x, char y);

#endif /* LCD_H_ */
