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
 * \brief TIM1 定时器 PWM 例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. PIOA_11(TIM1_CH4)输出 2KHz 的 PWM，占空比为 50%；
 *
 * \par 源代码
 * \snippet demo_aml166_core_std_tim1_pwm.c src_aml166_core_std_tim1_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_aml166_core_std_tim1_pwm
 * \copydoc demo_aml166_core_std_tim1_pwm.c
 */

/** [src_aml166_core_std_tim1_pwm] */
#include <am_aml166_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg_tim_pwm.h"
#include "demo_std_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_aml166_core_std_tim1_pwm_entry (void)
{
    AM_DBG_INFO("demo aml166_core std tim1 pwm!\r\n");

    demo_std_timer_pwm_entry(am_zlg116_tim1_pwm_inst_init(), AM_ZLG_TIM_PWM_CH3);
}
/** [src_aml166_core_std_tim1_pwm] */

/* end of file */
