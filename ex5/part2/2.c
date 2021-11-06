#include <mega32.h>

int a=0;
int i=0;
bit b=0,en=0;


interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{ 
if(i%2==0 && en==1){
   a++; 
  if(a==1)  PORTA=0x09;
  if(a==2)  PORTA=0x05;
  if(a==3)  PORTA=0x06;
  if(a==4)  {PORTA=0x0A;   a=0;}  
  }  
  
  if(i%2==1){
   a++; 
  if(a==1)  PORTA=0x0A;
  if(a==2)  PORTA=0x06;
  if(a==3)  PORTA=0x05;
  if(a==4)  {PORTA=0x09;   a=0;}  
  }
  
  
 
  TCNT0=0x64;
}

void main(void)
{

DDRA=0xFF;
PORTA=0x01;

DDRC=0x00;
PORTC=0x04;


TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x64;
OCR0=0x00;

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

#asm("sei")

while (1)
      {    
      if(PINC.2==0 && b==0)  {b=1; a=0; i++; en=1; }
      if(PINC.2==1) b=0;
      }
}
