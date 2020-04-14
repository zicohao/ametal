/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief TIM1 定时器 CAP 例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 使用杜邦线，将 PIOA_0 与 PIOA_11 连接。
 *
 * - 实验现象：
 *   1. TIM2 通过 PIOA_0 引脚输出 2KHz 的 PWM；
 *   2. TIM1 捕获输入通道 4 使用 PIOA_11 引脚捕获；
 *   3. 串口打印出利用捕获功能得到的 PWM 信号的周期和频率。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIOA_9 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_am116_core_std_tim1_cap.c src_am116_core_std_tim1_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 16-04-22  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am116_core_std_tim1_cap
 * \copydoc demo_am116_core_std_tim1_cap.c
 */

/** [src_am116_core_std_tim1_cap] */
#include "ametal.h"
#include "am_pwm.h"
#include "am_vdebug.h"
#include "am_zlg116_inst_init.h"
#include "demo_std_entries.h"
#include "demo_am116_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_am116_core_std_tim1_cap_entry (void)
{
    am_pwm_handle_t pwm_handle = am_zlg116_tim2_pwm_inst_init();

    AM_DBG_INFO("demo am116_core std tim1 cap!\r\n");

    /* TIM2 输出频率为 2KHz 的 PWM */
    am_pwm_config(pwm_handle, 0, 500000 / 2, 500000);
    am_pwm_enable(pwm_handle, 0);

    demo_std_timer_cap_entry(am_zlg116_tim1_cap_inst_init(), 3);
}
/** [src_am116_core_std_tim1_cap] */

/* end of file */
