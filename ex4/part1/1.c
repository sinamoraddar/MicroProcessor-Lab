#include <mega32.h>
#include <alcd.h>

void main(void)
{

lcd_init(16);
lcd_gotoxy(0,0);
lcd_putsf("Hello World");

while (1)
      {

      }
}
