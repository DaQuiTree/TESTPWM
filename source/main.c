#include "config.h"
#include "pwmled.h"

void main()
{
	uint16 i;
   EA = 1;     //�����ж�
   
   InitLED();	  

   while (1)
   {
	   LEDFlash();
	   for(i=0; i<60000; i++);
	   for(i=0; i<60000; i++);
	   for(i=0; i<60000; i++);
	   LEDBreath();
	   for(i=0; i<60000; i++);
	   for(i=0; i<60000; i++);
	   for(i=0; i<60000; i++);
	   LEDOff();
	   for(i=0; i<60000; i++);
	   for(i=0; i<60000; i++);
	   for(i=0; i<60000; i++);
   }
}