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
 * \brief SCT 作为 2 个 16 位定时器输出 PWM 例程，通过 HW 层接口实现
 *
 * - 实验现象：
 *   1. PIO0_23(SCT_OUT0) 输出 4KHz 的 PWM，占空比为 50%；
 *   2. PIO0_27(SCT_OUT2) 输出 1KHz 的 PWM，占空比为 25%。
 *
 * \note
 *    1. LED0 需要短接 J9 跳线帽，才能被 PIO0_20 控制；
 *    2. SCT 使用 32 位计数器，只能产生一组独立的 PWM，所有 PWM 输出使用同一频率，
 *       计数器和最大匹配值为 0xFFFFFFFF；
 *    3. SCT 使用 16 位计数器，可以产生 2 组独立的 PWM，每一组 PWM 的输出使用同一
 *       频率，计数器和最大匹配值为 0xFFFF；
 *    4. 由于 SCT 默认作为驱动蜂鸣器，使用测试本 Demo 前需要将 am_prj_config.h 中
 *       的 AM_CFG_BUZZER_ENABLE 定义为 0，不使用蜂鸣器。
 *
 * \par 源代码
 * \snippet demo_am845_core_hw_sct_2_16bit_pwm.c src_am845_core_hw_sct_2_16bit_pwm
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-19  hgo, modified
 * - 1.00 15-07-13  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_sct_2_16bit_pwm
 * \copydoc demo_am845_core_hw_sct_2_16bit_pwm.c
 */

/** [src_am845_core_hw_sct_2_16bit_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc84x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief 例程入口
 */
void demo_am845_core_hw_sct_2_16bit_pwm_entry (void)
{
    uint32_t frq = 0;
    am_kprintf("demo am845_core hw sct 2_16bit pwm \r\n");

    AM_DBG_INFO("The PIO0_23(SCT_OUT0) PWM: freq is 4kHz, "
                "The duty ratio is 50%% \r\n");
    AM_DBG_INFO("The PIO0_27(SCT_OUT4) PWM: freq is 1kHz, "
                "The duty ratio is 25%% \r\n");

    /* 平台初始化 */
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_SCT);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_SCT);

    /* PIO0_23 关联到 SCT 的输出通道 0、PIO0_27 关联到 SCT 的输出通道 2 */
    am_gpio_pin_cfg(PIO0_23, PIO_FUNC_SCT_OUT1);
    am_gpio_pin_cfg(PIO0_27, PIO_FUNC_SCT_OUT2);

    frq = amhw_lpc84x_clk_system_clkrate_get();
  
    demo_lpc_hw_sct_2_16bit_pwm_entry(LPC84X_SCT0, frq);
    
}
/** [src_am845_core_hw_sct_2_16bit_pwm] */

/* end of file */
