/*
 * PWMLED.h
 * --------
 * func: 关于闹钟和PWM呼吸灯的接口
 */

 #ifndef _PWMLED_H
 #define _PWMLED_H

 #ifndef _PWMLED_C
 //extern
 #endif

void ConfigTimerTwo();
void ConfigPWM(unsigned int fr, uint8 dc);

 #endif