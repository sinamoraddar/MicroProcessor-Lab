#include <mega32.h>
int i=0;

unsigned char seg[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
PORTC=0xF7;
PORTD=seg[i];
i++;  if(i>=10) i=0;
TCNT1H=0xC2F7 >> 8;
TCNT1L=0xC2F7 & 0xff;


}

void main(void)
{
     
DDRC=0xFF;
PORTC=0xFF;
DDRD=0xFF;
PORTD=0x00;

TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10);
TCNT1H=0xC2;
TCNT1L=0xF7;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;


TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);
#asm("sei")

while (1)
      {
     

      }
}
