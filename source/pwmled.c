#define _PWMLED_C

#include "config.h"

sbit PWMOUT = P3^3;

uint8 HighRH = 0;  //�ߵ�ƽ����ֵ�ĸ��ֽ�
uint8 HighRL = 0;  //�ߵ�ƽ����ֵ�ĵ��ֽ�
uint8 LowRH  = 0;  //�͵�ƽ����ֵ�ĸ��ֽ�
uint8 LowRL  = 0;  //�͵�ƽ����ֵ�ĵ��ֽ�

uint32 PeriodCnt = 0;

void ConfigTimerTwo() //��ʱ���� 50ms
{

	RCAP2H = (uint8)((65535 - SYS_CLK/20 + 12) >> 8); //���ö�ʱ����Ϊ��ʾ������ʱ��
	RCAP2L = (uint8)(65535 - SYS_CLK/20 + 12);

	T2CON = 0x00;

	TH2 = RCAP2H;
	TL2 = RCAP2L;

	TR2 = 1;
	//PT2 = 1;//����LED��ʾ��������ж����ȼ�
	ET2 = 1;
}

void ConfigPWM(uint16 fr, uint8 dc)
{
    uint16 high, low;
    
    PeriodCnt = (11059200/12) / fr; //����һ����������ļ���ֵ
    high = (PeriodCnt*dc) / 100;    //����ߵ�ƽ����ļ���ֵ
    low  = PeriodCnt - high;        //����͵�ƽ����ļ���ֵ
    high = 65536 - high + 12;       //����ߵ�ƽ�Ķ�ʱ������ֵ�������ж���ʱ
    low  = 65536 - low  + 12;       //����͵�ƽ�Ķ�ʱ������ֵ�������ж���ʱ
    HighRH = (uint8)(high>>8); //�ߵ�ƽ����ֵ���Ϊ�ߵ��ֽ�
    HighRL = (uint8)high;
    LowRH  = (uint8)(low>>8);  //�͵�ƽ����ֵ���Ϊ�ߵ��ֽ�
    LowRL  = (uint8)low;
    TMOD &= 0x0F;   //����T1�Ŀ���λ
    TMOD |= 0x10;   //����T1Ϊģʽ1
    TH1 = HighRH;   //����T1����ֵ
    TL1 = HighRL;
    ET1 = 1;        //ʹ��T1�ж�
    TR1 = 1;        //����T1
    PWMOUT = 1;     //����ߵ�ƽ
}
void AdjustDutyCycle(uint8 dc)
{
	uint16 high, low;

	high = (PeriodCnt*dc)/100;
	low = PeriodCnt - high;
	high = 65536 - high + 12;
	low = 65536 - low + 12;
	HighRH = (uint8)(high >> 8);
	HighRL = (uint8)high;
	LowRH = (uint8)(low >> 8);
	LowRL = (uint8)low;
}
void InterruptTimerOne() interrupt 3
{
    if (PWMOUT == 1)  //��ǰ���Ϊ�ߵ�ƽʱ��װ�ص͵�ƽֵ������͵�ƽ
    {
        TH1 = LowRH;
        TL1 = LowRL;
        PWMOUT = 0;
    }
    else              //��ǰ���Ϊ�͵�ƽʱ��װ�ظߵ�ƽֵ������ߵ�ƽ
    {
        TH1 = HighRH;
        TL1 = HighRL;
        PWMOUT = 1;
    }
}

void InterruptTimerTwo() interrupt 5
{
	uint8 code table[13] = {
	5, 18, 30, 41, 51, 60, 68, 75, 81, 86, 90, 93, 95
	};
	static bit dir = 0;
	static uint8 index = 0;

	TH2 = RCAP2H;
	TL2 = RCAP2L;

	AdjustDutyCycle(table[index]);
	if(dir == 0)
	{
		index++;
		if(index >= 12)
		{
			dir = 1;
		}
	}
	else
	{
		index--;
		if(index == 0)
		{
			dir = 0;
		}
	}
}