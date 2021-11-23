#include <mega32.h>
#include <alcd.h>
#include <stdio.h>
#include "keypad.h"
#include <eeprom.h>
#include <delay.h>

unsigned char str[20];
unsigned int temp; 
int mode=0,i=0,cn=0;
unsigned char ebyte;
unsigned int data=0,data1=0,data2=0;
unsigned int key_data(void){
           data=0;
           a:
            while(key_released());  
            temp=key_scan(); 
            PORTC=temp;
            if(temp<10){  
               data=data*10+temp; 
               sprintf(str,"%d",temp);
               lcd_puts(str);
             goto a;
             }
             if(temp==15){ 
               //lcd_clear(); 
               return data;
             } 
             if(temp==10){  
               return 0;
             }  
}    

void main(void)
{
DDRC=0xFF;

UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (1<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x33;


lcd_init(16);
lcd_gotoxy(0,0);
keypad_init();


/*lcd_gotoxy(0,0);
sprintf(str,"%d",eeprom_read_byte(0));
lcd_puts(str); 
delay_ms(500);

lcd_gotoxy(0,1);
sprintf(str,"%d   %d",eeprom_read_word(1),eeprom_read_word(3));
lcd_puts(str); 
delay_ms(500); 

lcd_clear();
sprintf(str,"%d   %d",eeprom_read_word(5),eeprom_read_word(7));
lcd_puts(str); 
delay_ms(500);

lcd_clear();
sprintf(str,"%d   %d",eeprom_read_word(7),eeprom_read_word(9));
lcd_puts(str); 
delay_ms(500);
 */
//eeprom_write_byte(0,0);
   
while (1) 
      { 
                  
         if(eeprom_read_byte(0)<1){  
            PORTC &= ~(3<<4);  
            lcd_clear();
            lcd_puts("Set Admin ID:");  
            lcd_gotoxy(0,1); 
            data1=key_data();
            if(data1!=0){ 
              eeprom_write_word(1,data1);
              lcd_clear();
              lcd_puts("Set Admin pass:");  
              lcd_gotoxy(0,1); 
              data1=key_data();
                if(data1!=0){
                eeprom_write_word(3,data1);
                }
              eeprom_write_byte(0,1); 
              lcd_clear();
              mode=1;  /// admin mode
            } 
          }
          
          if(mode==1){ 
              PORTC &= ~(3<<4);
              PORTC.4=1;
              b:
              lcd_clear();
              lcd_putsf("set speed:"); 
              lcd_gotoxy(10,1);
              lcd_putsf("Next>");
              lcd_gotoxy(11,0); 
               data=0; 
               e:
               while(key_released());  
               temp=key_scan(); 
               if(temp<10){  
               data=data*10+temp; 
               sprintf(str,"%d",temp);
               lcd_puts(str);
               goto e;
               }
              if(temp==15){  
               printf("%d\r\n",data);
               lcd_gotoxy(0,1);
               lcd_putsf("send");
               lcd_gotoxy(11,0); 
               lcd_putsf("     ");
               data=0;
               lcd_gotoxy(11,0);
               goto e;
               } 
               
             if(temp==13){  
               goto b;
             }
              if(temp==10){  
                mode=0;
             } 
                
              else if(temp==14) { 
              lcd_clear();
              lcd_putsf("create new user?"); 
              lcd_gotoxy(0,10);
              lcd_putsf("Next>"); 
              while(key_released());  
              temp=key_scan();
              if(temp==15) mode = 2; // create user mode   
              else if(temp==10) mode=0;    //user mode 
              else if(temp==14) {
               lcd_clear();
               lcd_putsf("Edit user?"); 
               while(key_released()); 
               temp=key_scan(); 
               if(temp==15) {
                     mode = 3; // Edit/delete user
                     lcd_clear();
                     lcd_puts("use up/down"); 
                      delay_ms(2000);  
                     } 
               else if(temp==10) mode=0;    //user mode 
               else if(temp==14 || temp==13)  goto b;
              }
              } 
          }
          
          
          if(mode==0){     //user mode
          
            PORTC &= ~(3<<4); 
            lcd_clear();
            lcd_puts("Enter User ID:");  
            lcd_gotoxy(0,1); 
            data1=key_data();
            if(data1!=0){
          
              lcd_clear();
              lcd_puts("Set User pass:");  
              lcd_gotoxy(0,1); 
              data2=key_data();
                if(data2!=0){
                 for(i=0;i<200;i++){
                    if(data1==eeprom_read_word(i*4+1) &&  data2==eeprom_read_word(i*4+3)){
                      if(i==0) mode=1;  //admin mode
                      else mode=10;       //user ok mode  
                      break;
                      } 
                 }
                 if(i==200){
                    PORTC.5=1;
                 } 
                }
                delay_ms(1000);
            }  
               
          }
          
          
          if(mode==2){     //create user    
            PORTC &= ~(3<<4); 
            lcd_clear();
            lcd_puts("Set User ID:");  
            lcd_gotoxy(0,1); 
            data1=key_data();
            if(data1!=0){ 
              eeprom_write_word(eeprom_read_byte(0)*4+1,data1);
              lcd_clear();
              lcd_puts("Set User pass:");  
              lcd_gotoxy(0,1); 
              data1=key_data();
                if(data1!=0){
                eeprom_write_word(eeprom_read_byte(0)*4+3,data1);
                }
              lcd_clear();
              sprintf(str,"user:%d Pass:%d    saved", eeprom_read_word(eeprom_read_byte(0)*4+1), eeprom_read_word(eeprom_read_byte(0)*4+3) );
              lcd_puts(str);
              delay_ms(1000);
              eeprom_write_byte(0,eeprom_read_byte(0)+1); 
              mode=0;  /// admin mode
            }
          } 
          
          
          if(mode==3){
            while(key_released());  
            temp=key_scan(); 
            
            if(temp==14){
                       //edit or delete user  
             d:
             lcd_clear();
             lcd_puts("edit ID?"); 
             while(key_released());  
             temp=key_scan();
             if(temp==15){ 
               mode =5; //edit id mode            
             }
             
             if(temp==14){ 
                lcd_clear();
                lcd_puts("edit password?");  
                while(key_released());  
                temp=key_scan();
                if(temp==15){ 
                  mode =6; //edit pass mode            
                }
                if(temp==14){ 
                   lcd_clear();
                   lcd_puts("delete user?");  
                   while(key_released());  
                   temp=key_scan(); 
                   if(temp==15){ 
                    mode =7; //delete user           
                   }
                   if(temp == 14)  goto d;
                   else if(temp==10) mode=1;  
                }
                else if(temp==10) mode=1; 
             }
             else if(temp==10) mode=1; 
                         
            }
            
            if(temp==11) {  
                lcd_clear(); 
                sprintf(str,"user:%d", eeprom_read_word(cn*4+1));
                lcd_puts(str);
                lcd_gotoxy(0,1);
                sprintf(str,"pass:%d", eeprom_read_word(cn*4+3));
                lcd_puts(str); 
                delay_ms(1000);
                cn++;
            }
            if(temp==12){
                
                lcd_clear(); 
                sprintf(str,"user:%d", eeprom_read_word(cn*4+1));
                lcd_puts(str);
                lcd_gotoxy(0,1);
                sprintf(str,"pass:%d", eeprom_read_word(cn*4+3));
                lcd_puts(str);
                cn--;
            } 
            if(temp==10)  mode=1;
            if(cn<0) cn=eeprom_read_byte(0); 
            if(cn>eeprom_read_byte(0)) cn=0;
            
             
          
          }
          
          if(mode==5){               //change user id 
                lcd_clear(); 
                sprintf(str,"user:%d", eeprom_read_word((cn-1)*4+1));
                lcd_puts(str);
                lcd_gotoxy(0,1); 
                data1=key_data();
                if(data1!=0){
                  eeprom_write_word((cn-1)*4+1,data1);
                  lcd_clear();
                  lcd_puts("saved"); 
                  delay_ms(1000);
                  mode=3;
                }    
          }   
          
          
           if(mode==6){               //change user password 
                lcd_clear(); 
                sprintf(str,"pass:%d", eeprom_read_word((cn-1)*4+3));
                lcd_puts(str);
                lcd_gotoxy(0,1); 
                data1=key_data();
                if(data1!=0){
                  eeprom_write_word((cn-1)*4+3,data1);
                  lcd_clear();
                  lcd_puts("saved"); 
                  delay_ms(1000);
                  mode=3;
                }    
          } 
          
          
          if(mode==7){               //change user password 
                lcd_clear(); 
                sprintf(str,"user id:%d", eeprom_read_word((cn-1)*4+1));
                lcd_puts(str);
                lcd_gotoxy(0,1); 
                lcd_puts("delete?"); 
                while(key_released());  
                temp=key_scan(); 
                if(temp==15) {
                     eeprom_write_word((cn-1)*4+1,0x0000);
                     eeprom_write_word((cn-1)*4+3,0x0000);
                     mode=3;
                     lcd_clear();
                }
                if(temp==10) {
                   mode=3;
                   lcd_clear();
                }   
          }
          
          if(mode==10){               //user success logged in
              PORTC &= ~(3<<4);
              PORTC.4=1; 
              g:
              lcd_clear();
              lcd_puts("set speed:"); 
              lcd_gotoxy(10,1);
              lcd_putsf("Next>");
              lcd_gotoxy(11,0); 
               data=0; 
               f:
               while(key_released());  
               temp=key_scan(); 
               if(temp<10){  
               data=data*10+temp; 
               sprintf(str,"%d",temp);
               lcd_puts(str);
               goto f;
               }
              if(temp==15){  
               printf("%d\r\n",data);
               lcd_gotoxy(0,1);
               lcd_putsf("send");
               lcd_gotoxy(11,0); 
               lcd_putsf("     ");
               data=0;
               lcd_gotoxy(11,0);
               goto f;
               } 
               
             if(temp==13){  
               goto g;
             }
              if(temp==10){  
                mode=0;
             } 
          }
      
      }
}
