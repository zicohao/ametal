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
 * \brief TIM2 定时器 CAP 例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 使用杜邦线，将 PIOB_3 与 PIOA_0 连接。
 *
 * - 实验现象：
 *   1. TIM3 通过 PIOB_3 引脚输出 2KHz 的 PWM；
 *   2. TIM2 捕获输入通道 1 使用 PIOA_0 引脚捕获；
 *   3. 串口打印出利用捕获功能得到的 PWM 信号的周期和频率。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIOA_9 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_aml166_core_std_tim2_cap.c src_aml166_core_std_tim2_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 16-04-22  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml166_core_std_tim2_cap
 * \copydoc demo_aml166_core_std_tim2_cap.c
 */

/** [src_aml166_core_std_tim2_cap] */
#include "am_aml166_inst_init.h"
#include "ametal.h"
#include "am_pwm.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_aml166_core_std_tim2_cap_entry (void)
{
    am_pwm_handle_t pwm_handle = am_zlg116_tim3_pwm_inst_init();

    AM_DBG_INFO("demo aml166_core std tim2 cap!\r\n");

    /* TIM3 输出频率为 2KHz 的 PWM */
    am_pwm_config(pwm_handle, 2, 500000 / 2, 500000);
    am_pwm_enable(pwm_handle, 2);

    demo_std_timer_cap_entry(am_zlg116_tim2_cap_inst_init(), 1);
}
/** [src_aml166_core_std_tim2_cap] */

/* end of file */
