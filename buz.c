#include "H/Function_Init.H"
#include "buz.h"
#include "buz_config.h"

static unsigned int buz_toggle_count = 0; // 还需翻转次数
static unsigned char buz_int_count   = 0; // 中断次数计数
static unsigned char buz_beep_times  = 0; // 剩余响声次数
static unsigned int buz_gap_timer    = 0; // 两声之间的间隔计时

/*-------------------------------
 * 蜂鸣器初始化
 *------------------------------*/
void Buz_Init(void)
{
    P2CON |= (1 << 6);
    P2PH &= ~(1 << 6);
    BUZ_PIN = 1; // 默认关闭
}

/*-------------------------------
 * 启动蜂鸣器响指定时间
 *------------------------------*/
static void Buz_Start(unsigned int duration_ms)
{
    buz_toggle_count = duration_ms * 10; // 100us中断 ×10 = 1ms
    buz_int_count    = 0;
}

/*-------------------------------
 * 停止蜂鸣器
 *------------------------------*/
static void Buz_Stop(void)
{
    buz_toggle_count = 0;
    BUZ_PIN          = 1;
}

/*-------------------------------
 * 每次100us定时中断调用
 *------------------------------*/
void Buz_TimerTick(void)
{
    if (buz_toggle_count > 0) {
        buz_int_count++;
        if (buz_int_count >= BUZ_TURN_TIMES) { // 每 (n +1) * 100us翻转一次
            BUZ_PIN       = !BUZ_PIN;
            buz_int_count = 0;
            buz_toggle_count--;
        }
    } else if (buz_beep_times > 0) {
        // 两声之间的间隔计时
        if (buz_gap_timer > 0) {
            buz_gap_timer--;
        } else {
            // 开始下一声
            buz_beep_times--;
            if (buz_beep_times > 0) {
                Buz_Start(BEEP_ON_TIME);
                buz_gap_timer = BEEP_GAP_TIME * 10; // ms → 100us tick
            }
        }
    }
}

/*-------------------------------
 * 发出一声蜂鸣（约200ms）
 *------------------------------*/
void beep(void)
{
    Buz_Start(BEEP_ON_TIME);
}

/*-------------------------------
 * 发出 n 声蜂鸣
 * 例：Beep_Times(2); // 响两声
 *------------------------------*/
void Beep_Times(unsigned char times)
{
    if (times == 0) return;
    buz_beep_times = times;
    Buz_Start(BEEP_ON_TIME);
    buz_gap_timer = BEEP_GAP_TIME * 10; // 设置间隔时间（单位：tick）
}
