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
 * \brief 定时器通道比较匹配引脚翻转例程，通过 HW 层接口实现
 *
 * - 实验现象：
 *   1. PIOB_8 引脚以 10Hz 的频率进行翻转。
 *
 * \note
 *    由于 TIM4 默认初始化并作为系统滴答使用，使用本 Demo 之前必须在
 *    am_prj_config.h 内将 AM_CFG_KEY_GPIO_ENABLE、AM_CFG_SOFTIMER_ENABLE
 *    和 AM_CFG_SYSTEM_TICK_ENABLE 定义为 0。
 *
 * \par 源代码
 * \snippet demo_zmf159_core_hw_tim_cmp_toggle.c src_zmf159_core_hw_tim_cmp_toggle
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_core_hw_tim_cmp_toggle
 * \copydoc demo_zmf159_core_hw_tim_cmp_toggle.c
 */

/** [src_zmf159_core_hw_tim_cmp_toggle] */
#include <demo_zmf159_core_entries.h>
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zmf159.h"
#include "zmf159_inum.h"
#include "am_zmf159_clk.h"
#include "demo_zlg_entries.h"

/**
 * \brief 例程入口
 */
void demo_zmf159_core_hw_tim_cmp_toggle_entry (void)
{
    AM_DBG_INFO("demo zmf159_core hw tim cmp toggle!\r\n");

    /* 初始化引脚 */
    am_gpio_pin_cfg(PIOB_8, PIOB_8_TIM4_CH3 | PIOB_8_AF_PP);

    /* 使能定时器时钟 */
    am_clk_enable(CLK_TIM4);

    /* 复位定时器 */
    am_zmf159_clk_reset(CLK_TIM4);

    demo_zlg_hw_tim_cmp_toggle_entry(ZMF159_TIM4,
                                     AMHW_ZLG_TIM_TYPE1,
                                     2,
                                     am_clk_rate_get(CLK_TIM4),
                                     INUM_TIM4);
}
/** [src_zmf159_core_hw_tim_cmp_toggle] */

/* end of file */
