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
 * \brief 定时器 CAP 捕获例程，通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. 使用杜邦线，将 PIOA_8 与 PIOB_4 连接。
 *
 * - 实验现象：
 *   1. TIM1 通过 PIOA_8 引脚输出 2KHz 的 PWM；
 *   2. TIM3 捕获输入通道 1 使用 PIOB_4 引脚捕获；
 *   3. 串口打印出利用捕获功能得到的 PWM 信号的周期和频率。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIOA_9 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_zmf159_core_hw_tim_cap.c src_zmf159_core_hw_tim_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 16-04-22  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_core_hw_tim_cap
 * \copydoc demo_zmf159_core_hw_tim_cap.c
 */

/** [src_zmf159_core_hw_tim_cap] */
#include <demo_zmf159_core_entries.h>
#include "ametal.h"
#include "am_clk.h"
#include "am_pwm.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zmf159.h"
#include "zmf159_inum.h"
#include "am_zmf159_clk.h"
#include "am_zmf159_inst_init.h"
#include "demo_zlg_entries.h"

/**
 * \brief 例程入口
 */
void demo_zmf159_core_hw_tim_cap_entry (void)
{
    am_pwm_handle_t pwm_handle = am_zmf159_tim1_pwm_inst_init();

    AM_DBG_INFO("demo zmf159_core hw tim cap!\r\n");

    /* TIM1 输出频率为 2KHz 的 PWM */
    am_pwm_config(pwm_handle, 0, 500000 / 2, 500000);
    /* TIM1通道1使能 */
    am_pwm_enable(pwm_handle, 0);

    /* 初始化引脚 */
    am_gpio_pin_cfg(PIOB_4, PIOB_4_TIM3_CH1 | PIOB_4_INPUT_FLOAT);

    /* 使能定时器时钟 */
    am_clk_enable(CLK_TIM3);

    /* 复位定时器 */
    am_zmf159_clk_reset(CLK_TIM3);

    demo_zlg_hw_tim_cap_entry(ZMF159_TIM3,
                              AMHW_ZLG_TIM_TYPE1,
                              0,
                              am_clk_rate_get(CLK_TIM3),
                              INUM_TIM3);
}
/** [src_zmf159_core_hw_tim_cap] */

/* end of file */
