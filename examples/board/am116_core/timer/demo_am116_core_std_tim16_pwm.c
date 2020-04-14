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
 * \brief TIM16 定时器 PWM 例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. PIOB_8(TIM16_CH1) PIOB_6(TIM16_CH1N)输出互补的 2KHz 的 PWM，占空比为 50%；
 *
 * \note
 *    由于 TIM16 默认初始化并作为蜂鸣器 PWM 使用，使用本 Demo 之前必须在
 *    am_prj_config.h 内将 AM_CFG_BUZZER_ENABLE 定义为 0。
 *
 * \par 源代码
 * \snippet demo_am116_core_std_tim16_pwm.c src_am116_core_std_tim16_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_am116_core_std_tim16_pwm
 * \copydoc demo_am116_core_std_tim16_pwm.c
 */

/** [src_am116_core_std_tim16_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg_tim_pwm.h"
#include "am_zlg116_inst_init.h"
#include "demo_std_entries.h"
#include "demo_am116_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_am116_core_std_tim16_pwm_entry (void)
{
    AM_DBG_INFO("demo am116_core std tim16 pwm!\r\n");

    demo_std_timer_pwm_entry(am_zlg116_tim16_pwm_inst_init(), AM_ZLG_TIM_PWM_CH1);
}
/** [src_am116_core_std_tim16_pwm] */

/* end of file */
