#ifndef __BUZ_CONFIG_H
#define __BUZ_CONFIG_H

#include "H/Function_Init.H"

// 蜂鸣器引脚
#define BUZ_PIN P26 
// 每次响声持续时间(ms)
#define BEEP_ON_TIME   200 
// 声与声之间间隔(ms)
#define BEEP_GAP_TIME  200 
/*
* 间隔多少时间翻转 0 5.0 kHz 1 2.5 kHz 2 1.25 kHz 3 0.83  kHz
* 每次 Buz_TimerTick() 调用间隔 = 100 ?s
* | BUZ_TURN_TIMES | 翻转间隔 (?s) | 周期 (?s) | 频率 f (Hz) | 频率约等于 (kHz) |
* | -------------- | --------- | ------- | --------- | ----------- |
* | 0              | 100       | 200     | 5000 Hz   | 5.0 kHz     |
* | 1              | 200       | 400     | 2500 Hz   | 2.5 kHz     |
* | 2              | 400       | 800     | 1250 Hz   | 1.25 kHz    |
* | 3              | 600       | 1200    | 833 Hz    | 0.83 kHz    |
* | -------------- | --------- | ------- | --------- | ----------- |
*/

#define BUZ_TURN_TIMES 1 


#endif