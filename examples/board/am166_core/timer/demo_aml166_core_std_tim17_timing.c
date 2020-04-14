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
 * \brief TIM17 定时器 TIMING 例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. 调试串口输出定时器的相关信息
 *   2. 定时周期到达(默认为 2Hz)，调试串口会输出 The timing frq is 2Hz;
 *
 * \note
 *    16 位定时器定时计数值不为 65536 的倍数，则定时会有一些偏差。
*
 * \par 源代码
 * \snippet demo_aml166_core_std_tim17_timing.c src_aml166_core_std_tim17_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_aml166_core_std_tim17_timing
 * \copydoc demo_aml166_core_std_tim17_timing.c
 */

/** [src_aml166_core_std_tim17_timing] */
#include <am_aml166_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_aml166_core_std_tim17_timing_entry (void)
{
    AM_DBG_INFO("demo aml166_core std tim17 timing!\r\n");

    demo_std_timer_timing_entry(am_zlg116_tim17_timing_inst_init(), 0);
}
/** [src_aml166_core_std_tim17_timing] */

/* end of file */
