#include <mega32.h>
#include <alcd.h>
#include <stdio.h>
int min=0,hour=0,sec=0;
char str[20];
bit b1,b2,b0;
interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
  sec++; 
  if(sec>=60) {sec=0; min++; }
  if(min>=60) {min=0; hour++; }
  if(hour>=24) {hour=0;  }  
   
}

void main(void)
{
DDRB=0x00;
PORTB=0x07;

ASSR=1<<AS2;
TCCR2=(0<<PWM2) | (0<<COM21) | (0<<COM20) | (0<<CTC2) | (1<<CS22) | (0<<CS21) | (1<<CS20);
TCNT2=0x00;
OCR2=0x00;

TIMSK=(0<<OCIE2) | (1<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

lcd_init(16);
#asm("sei")

while (1)
      {  
      if(PINB.0==0 & b0==0){ b0=1; sec++; if(sec>=60) sec=0;}     if(PINB.0==1) b0=0;
      if(PINB.1==0 & b1==0){ b1=1; min++; if(min>=60) min=0;}     if(PINB.1==1) b1=0;
      if(PINB.2==0 & b2==0){ b2=1; hour++; if(hour>=21) hour=0;}  if(PINB.2==1) b2=0;
      
      lcd_gotoxy(0,0);
      sprintf(str,"%02d:%02d:%02d",hour,min,sec);
      lcd_puts(str);
      }
}
