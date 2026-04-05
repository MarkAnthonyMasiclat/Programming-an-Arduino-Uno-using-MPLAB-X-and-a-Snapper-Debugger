/* 
 * File:   newmain1.c
 * Author: markanthony.masiclat
 *
 * Created on March 23, 2026, 7:43 PM
 */

#include <avr/io.h>
#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1<<TXEN0);
    UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void USART_Transmit(unsigned char data) {
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

int main(void)
{
    USART_Init(MYUBRR);

    while(1)
    {
        USART_Transmit('H');
        USART_Transmit('E');
        USART_Transmit('L');
        USART_Transmit('L');
        USART_Transmit('O');
    }
}