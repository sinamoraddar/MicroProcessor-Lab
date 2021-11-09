#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>

#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))

unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
delay_us(10);
ADCSRA|=(1<<ADSC);
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

float temp;
char str[30];
bit b,state;

void main(void)
{
DDRB=0x00;
PORTB=0x08;


ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

lcd_init(16);

while (1)
      { 
      if(PINB.3==0 && b==0) {b=1; state=!state; lcd_clear();}
      else b=0;
       
      temp=read_adc(0)*500.0/1023.0;   
      lcd_gotoxy(0,0);
      if(state){
        temp=temp*1.8+32;
        sprintf(str,"Temp = %.2f F",temp);       
        lcd_puts(str);
       } 
       else{
        sprintf(str,"Temp = %.2f \xdf%c",temp,'C');   
        lcd_puts(str);
        
       }
        
      
      delay_ms(200);    

      }
}
