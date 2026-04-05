/*
 * File:   lcd_i2c_usart.c
 * Author: Mark Anthony
 *
 * Created on March 30, 2026
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define LCD_ADDR 0x27 

void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1<<TXEN0);
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void USART_Transmit(unsigned char data) {
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

void USART_Print(char *str) {
    while(*str) USART_Transmit(*str++);
}

void I2C_Init(void) {
    TWSR = 0x00;
    TWBR = ((F_CPU/100000UL)-16)/2; 
    TWCR = (1<<TWEN);
}

void I2C_Start(uint8_t addr) {
    TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
    while (!(TWCR & (1<<TWINT)));
    TWDR = addr<<1; 
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

void I2C_Write(uint8_t data) {
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

void I2C_Stop(void) {
    TWCR = (1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
    _delay_ms(1);
}

void LCD_Write4(uint8_t nibble, uint8_t rs) {
    uint8_t data = 0;

    data |= (nibble & 0x0F) << 4;
    if(rs) data |= (1 << 0);      
    data |= (1 << 3);              

    I2C_Start(LCD_ADDR);
    I2C_Write(data | (1 << 2));
    _delay_us(500);
    I2C_Write(data & ~(1 << 2));   
    I2C_Stop();

    _delay_us(50);
}

void LCD_Command(uint8_t cmd) {
    LCD_Write4(cmd >> 4, 0);
    LCD_Write4(cmd & 0x0F, 0);
}

void LCD_Data(uint8_t data) {
    LCD_Write4(data >> 4, 1);
    LCD_Write4(data & 0x0F, 1);
}

void LCD_Init(void) {
    _delay_ms(50);       
    LCD_Command(0x33);   
    _delay_ms(5);
    LCD_Command(0x32);   
    _delay_ms(5);
    LCD_Command(0x28);   
    LCD_Command(0x0C);  
    LCD_Command(0x06);  
    LCD_Command(0x01);   
    _delay_ms(5);
}

void LCD_SetCursor(uint8_t line, uint8_t pos) {
    uint8_t addr = (line == 1 ? 0x00 : 0x40) + pos;
    LCD_Command(0x80 | addr);
}

void LCD_Print(char *str) {
    while(*str) LCD_Data(*str++);
}

int main(void) {
    USART_Init(MYUBRR);
    USART_Print("Starting LCD + USART demo...\r\n");

    I2C_Init();
    LCD_Init();

    LCD_SetCursor(1,0);
    LCD_Print("HELLO");
    LCD_SetCursor(2,0);
    LCD_Print("WORLD");

    USART_Print("HELLO WORLD displayed on LCD\r\n");

    while(1) {
    }
}