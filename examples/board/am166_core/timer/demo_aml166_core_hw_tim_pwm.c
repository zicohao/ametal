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
 * \brief 定时器 PWM 输出例程，通过 HW 层接口实现
 *
 * - 实验现象：
 *   1. PIOA_0(TIM2_CH1) 输出 4KHz 的 PWM，占空比为 50%。
 *
 * \par 源代码
 * \snippet demo_aml166_core_hw_tim_pwm.c src_aml166_core_hw_tim_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_aml166_core_hw_tim_pwm
 * \copydoc demo_aml166_core_hw_tim_pwm.c
 */

/** [src_aml166_core_hw_tim_pwm] */
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zlg116.h"
#include "am_zlg116_clk.h"
#include "demo_zlg_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_aml166_core_hw_tim_pwm_entry (void)
{
    AM_DBG_INFO("demo aml166_core hw tim pwm!\r\n");

    /* 初始化引脚 */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_TIM2_CH1_ETR | PIOA_0_AF_PP);

    /* 使能定时器时钟 */
    am_clk_enable(CLK_TIM2);

    /* 复位定时器 */
    am_zlg116_clk_reset(CLK_TIM2);

    demo_zlg_hw_tim_pwm_entry(ZLG116_TIM2,
                                 AMHW_ZLG_TIM_TYPE1,
                                 0,
                                 am_clk_rate_get(CLK_TIM2),
                                 INUM_TIM2);
}
/** [src_aml166_core_hw_tim_pwm] */

/* end of file */
