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
 * \brief 定时器 TIMING 例程，通过 HW 层接口实现
 *
 * - 实验现象：
 *   1. 在中断时调试串口打印信息。
 *
 * \note
 *    1. 如需观察串口打印的调试信息，需要将 PIOA_9 引脚连接 PC 串口的 RXD；
 *    2. 16 位定时器定时计数值不为 65536 的倍数，则定时会有一些偏差。
 *
 * \par 源代码
 * \snippet demo_zmf159_core_hw_tim_timing.c src_zmf159_core_hw_tim_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_zmf159_core_hw_tim_timing
 * \copydoc demo_zmf159_core_hw_tim_timing.c
 */

/** [src_zmf159_core_hw_tim_timing] */
#include <demo_zmf159_core_entries.h>
#include "ametal.h"
#include "am_clk.h"
#include "am_vdebug.h"
#include "am_zmf159.h"
#include "am_zmf159_clk.h"
#include "zmf159_inum.h"
#include "demo_zlg_entries.h"

/**
 * \brief 例程入口
 */
void demo_zmf159_core_hw_tim_timing_entry (void)
{
    AM_DBG_INFO("demo zmf159_core hw tim timing!\r\n");

    /* 使能定时器时钟 */
    am_clk_enable(CLK_TIM2);

    /* 复位定时器 */
    am_zmf159_clk_reset(CLK_TIM2);

    demo_zlg_hw_tim_timing_entry(ZMF159_TIM2,
                                 AMHW_ZLG_TIM_TYPE1,
                                 am_clk_rate_get(CLK_TIM2),
                                 INUM_TIM2);
}
/** [src_zmf159_core_hw_tim_timing] */

/* end of file */
