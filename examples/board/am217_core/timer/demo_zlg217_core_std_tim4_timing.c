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
 * \brief TIM4 定时器 TIMING 例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. LED0 以 10Hz 的频率翻转。
 *
 * \note
 *    1. LED0 需要短接 J9 跳线帽，才能被 PIOC_9 控制；
 *    2. 16 位定时器定时计数值不为 65536 的倍数，则定时会有一些偏差；
 *    3. 由于 TIM4 默认初始化并作为系统滴答使用，使用本 Demo 之前必须在
 *       am_prj_config.h 内将 AM_CFG_KEY_GPIO_ENABLE、AM_CFG_SOFTIMER_ENABLE
 *       和 AM_CFG_SYSTEM_TICK_ENABLE 定义为 0。
 *
 *
 * \par 源代码
 * \snippet demo_zlg217_std_tim4_timing.c src_zlg217_std_tim4_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-25  zcb, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_tim4_timing
 * \copydoc demo_zlg217_std_tim4_timing.c
 */

/** [src_zlg217_std_tim4_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg217_inst_init.h"
#include "demo_std_entries.h"
#include "demo_am217_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_zlg217_core_std_tim4_timing_entry (void)
{

    AM_DBG_INFO("demo am217_core std tim16 timing!\r\n");

    demo_std_timer_timing_entry(am_zlg217_tim4_timing_inst_init(), 0);

}
/** [src_zlg217_std_tim4_timing] */

/* end of file */
