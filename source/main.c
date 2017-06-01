#include "config.h"
#include "pwmled.h"

void main()
{
   EA = 1;     //开总中断
	  
   ConfigPWM(100, 10);  //配置并启动PWM
   ConfigTimerTwo();    //用T2定时调整占空比
    while (1);
}