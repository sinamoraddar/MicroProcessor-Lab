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
bit b0,b1,b2;
int menu=0,up_temp=27,hysteresis=2;
bit motor=0;

void main(void)
{
DDRB=0x00;
PORTB=0x0F;


ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

lcd_init(16);

while (1)
      { 
      if(PINB.0==0 && b0==0) {
        b0=1; menu++;
        if(menu==3) menu=0;
        lcd_clear();}
      else b0=0;
      
      if(PINB.1==0 && b1==0) {
        b1=1; 
        if(menu==1){if(up_temp<=60) up_temp++;  }  
        if(menu==2){if(hysteresis<=30) hysteresis++;  }
        } 
        
      else b1=0;
      
      if(PINB.2==0 && b2==0) {
        b2=1;
        if(menu==1){if(up_temp>=0) up_temp--;  }   
        if(menu==2){if(hysteresis>=0) hysteresis--;  }
        } 
      else b2=0;
       
      temp=read_adc(0)*500.0/1023.0;   
      lcd_gotoxy(0,0); 
      sprintf(str,"Temp = %.2f \xdf%c",temp,'C');   
      lcd_puts(str);
      if(menu==0){
        lcd_gotoxy(0,1);
        sprintf(str,"up=%d H=%d M:",up_temp,hysteresis);   
        lcd_puts(str);        
        if(motor) lcd_putsf("ON "); 
        else  lcd_putsf("OFF");
      }
         
      if(menu==1){   
        lcd_gotoxy(0,1);
        sprintf(str,"Up_Temp = %d  ",up_temp);   
        lcd_puts(str);
      } 
      if(menu==2){   
        lcd_gotoxy(0,1);
        sprintf(str,"hysteresis = %d  ",hysteresis);   
        lcd_puts(str);
      }  
      
      if(temp >up_temp)  motor=1;  
      else if(temp > (up_temp-hysteresis)  && motor==1) motor=1;  
      else motor=0;     
      
      delay_ms(200);    

      }
}
