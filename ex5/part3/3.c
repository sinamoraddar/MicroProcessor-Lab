#include <mega32.h>
#include <delay.h>

int a=0;
int j=0;
bit b=0,en=0;
int m=0,n=0;;
int state=0;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{ 
if(en==1){ 
   m++;    
   if(state==0){
  if(a==1)  {PORTA=0x09; }
  if(a==2)  {PORTA=0x05; }
  if(a==3)  {PORTA=0x06; }
  if(a==4)  {PORTA=0x0A;   a=0;}     
  if(m>=200){m=0;n++; a++; if(n>=5){n=0; state++; }}   
  }  
  
   if(state==1){
  if(a==1)  {PORTA=0x09; }
  if(a==2)  {PORTA=0x05; }
  if(a==3)  {PORTA=0x06; }
  if(a==4)  {PORTA=0x0A;   a=0;}     
  if(m>=100){m=0;n++; a++; if(n>=10){n=0; state++; }}    
  } 
  
  if(state==2){
  if(a==1)  {PORTA=0x09; }
  if(a==2)  {PORTA=0x05; }
  if(a==3)  {PORTA=0x06; }
  if(a==4)  {PORTA=0x0A;   a=0;}     
  if(m>=50){m=0;n++; a++; if(n>=20){n=0; state++;;}}    
  } 
  
  if(state==3){
  if(a==1)  {PORTA=0x09; }
  if(a==2)  {PORTA=0x05; }
  if(a==3)  {PORTA=0x06; }
  if(a==4)  {PORTA=0x0A;   a=0;}     
  if(m>=20){m=0;n++; a++; if(n>=50){n=0; state++;}}    
  }   
  
  if(state==4){
  if(a==1)  {PORTA=0x09; }
  if(a==2)  {PORTA=0x05; }
  if(a==3)  {PORTA=0x06; }
  if(a==4)  {PORTA=0x0A;   a=0;}     
  if(m>=50){m=0;n++; a++; if(n>=20){n=0; state++;;}}    
  } 
  
  if(state==5){
  if(a==1)  {PORTA=0x09; }
  if(a==2)  {PORTA=0x05; }
  if(a==3)  {PORTA=0x06; }
  if(a==4)  {PORTA=0x0A;   a=0;}     
  if(m>=100){m=0;n++; a++; if(n>=10){n=0; state++; }}    
  }                                                      
  
  if(state==6){
  if(a==1)  {PORTA=0x09; }
  if(a==2)  {PORTA=0x05; }
  if(a==3)  {PORTA=0x06; }
  if(a==4)  {PORTA=0x0A;   a=0;}     
  if(m>=200){m=0;n++; a++; if(n>=5){n=0; state=8; }}   
  } 
  

  
  
   if(state==8){
  if(a==1)  {PORTA=0x0A; }
  if(a==2)  {PORTA=0x06; }
  if(a==3)  {PORTA=0x05; }
  if(a==4)  {PORTA=0x09;   a=0;}    
  if(m>=200){m=0;n++; a++; if(n>=5){n=0; state++; }}   
  }  
  
   if(state==9){
  if(a==1)  {PORTA=0x0A; }
  if(a==2)  {PORTA=0x06; }
  if(a==3)  {PORTA=0x05; }
  if(a==4)  {PORTA=0x09;   a=0;}   
  if(m>=100){m=0;n++; a++; if(n>=10){n=0; state++; }}    
  } 
  
  if(state==10){
  if(a==1)  {PORTA=0x0A; }
  if(a==2)  {PORTA=0x06; }
  if(a==3)  {PORTA=0x05; }
  if(a==4)  {PORTA=0x09;   a=0;}    
  if(m>=50){m=0;n++; a++; if(n>=20){n=0; state++;;}}    
  } 
  
  if(state==11){
  if(a==1)  {PORTA=0x0A; }
  if(a==2)  {PORTA=0x06; }
  if(a==3)  {PORTA=0x05; }
  if(a==4)  {PORTA=0x09;   a=0;}   
  if(m>=20){m=0;n++; a++; if(n>=50){n=0; state++;}}    
  }   
  
  if(state==12){
 if(a==1)  {PORTA=0x0A; }
  if(a==2)  {PORTA=0x06; }
  if(a==3)  {PORTA=0x05; }
  if(a==4)  {PORTA=0x09;   a=0;}     
  if(m>=50){m=0;n++; a++; if(n>=20){n=0; state++;;}}    
  } 
  
  if(state==13){
  if(a==1)  {PORTA=0x0A; }
  if(a==2)  {PORTA=0x06; }
  if(a==3)  {PORTA=0x05; }
  if(a==4)  {PORTA=0x09;   a=0;}     
  if(m>=100){m=0;n++; a++; if(n>=10){n=0; state++; }}    
  }                                                      
  
  if(state==14){
  if(a==1)  {PORTA=0x0A; }
  if(a==2)  {PORTA=0x06; }
  if(a==3)  {PORTA=0x05; }
  if(a==4)  {PORTA=0x09;   a=0;}     
  if(m>=200){m=0;n++; a++; if(n>=5){n=0; state=0; }}   
  } 
  
  }  
  TCNT0=0x64;
}

void main(void)
{

DDRA=0xFF;
PORTA=0x0A;

DDRC=0x01;
PORTC=0x04;


TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (0<<CS00);
TCNT0=0x64;
OCR0=0x00;

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

#asm("sei")

while (1)
      {    
      if(PINC.2==0 && b==0)  {b=1;  en=!en; state=0; }
     if(PINC.2==1) b=0;   
   
      }
}