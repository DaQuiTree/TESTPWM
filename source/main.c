#include "config.h"
#include "pwmled.h"

void main()
{
   EA = 1;     //�����ж�
	  
   ConfigPWM(100, 10);  //���ò�����PWM
   ConfigTimerTwo();    //��T2��ʱ����ռ�ձ�
    while (1);
}