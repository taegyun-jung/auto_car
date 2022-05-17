#include<mega328p.h>//bt_ev2.c
#include<delay.h>
#include<io.h>

#define MOTOR_CW  0b01110000// PC4=1, PC7=0, PC5=1, PC6=1
#define MOTOR_CCW 0b11100000// PC4=0, PC7=1, PC5=1, PC6=1
#define MOTOR_STOP 0b10010000// PC4=1, PC7=1, PC5=0, PC6=0
#define LOW  120
#define MID  170
#define HIGH  250

unsigned char data=0x00;
interrupt[USART_RXC]void usart(void)
{
  data = UDR0;
  UDR0 = data; // for test, echo back
 }
void putchar(char c)
{
 while(!(UCSR0A & (1<<UDRE0)));
 UDR0=c;
}

void main(void)
{
 DDRD=0b11111111;
 
 //** PWM 설정**//
 TCCR0A=0xA3;//고속 PWM 모드
 TCCR0B=0x01;//1분주
 ;
 TCNT0=0x00;//타이머/카운터0 레지스터 초기값
 //blooth 통신
 UCSR0A = 2;
 UCSR0B = 0x18;
 UCSR0B |= 0x80;
 UBRR0L = 16;

 #asm("sei") 
 while(1){
 switch(data){
 case '1':
          PORTD = MOTOR_CW;//전진 
          OCR0B=HIGH;
          OCR0A=HIGH;
          break; 
 case '2':
          PORTD = MOTOR_CCW; //후진
          OCR0B=HIGH; 
          OCR0A=HIGH;
          break;
 case '3':
          PORTD = MOTOR_CW; //좌회전
          OCR0B=HIGH; 
          OCR0A=MID;
          break;
 case '4':
          PORTD = MOTOR_CW; //우회전
          OCR0B=HIGH; 
          OCR0A=MID;
          break;
 case '5':
          PORTD = MOTOR_CW;//저속
          OCR0B=LOW;
          OCR0A=LOW;
          break;           
 case '6':
          PORTD = MOTOR_CW;//중속
          OCR0B=MID;
          OCR0A=MID;
          break;           
 case '7':
          PORTD = MOTOR_CW;//고속
          OCR0B=HIGH;
          OCR0A=HIGH;
          break;           
                   
 case '8':
          PORTD = MOTOR_STOP;//정지
          OCR0B=0;
          OCR0A=0;
          break;  
 } 

 }
}
    

                                                