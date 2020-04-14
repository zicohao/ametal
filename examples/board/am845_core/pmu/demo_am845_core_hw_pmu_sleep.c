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
 * \brief PMU 睡眠模式例程，通过 HW 层接口实现
 *
 * - 实验步骤：
 *   1. 用杜邦线将 PIO0_23 与 GND 连接，把电平拉低。
*
 * - 实验现象：
 *   1. 运行程序，一秒后 LED0 闪烁一次后进入睡眠模式；
 *   2. 当 PIO0_23 与 GND 的连接断开时，CPU 被唤醒，LED0 不断闪烁。
 *
 * \note
 *    1. 由于 MRT 默认作为系统滴答使用，使用测试本 Demo 前需要将 am_prj_config.h 中
 *       的 AM_CFG_SOFTIMER_ENABLE、 AM_CFG_SYSTEM_TICK_ENABLE 以及
 *       AM_CFG_KEY_GPIO_ENABLE 定义为 0，不使用软件定时器、系统嘀嗒、板载独立按键，
 *       防止进入睡眠模式后被 MRT 定时器中断唤醒；
 *    2. 使用该程序后，会导致下次程序烧写的时候检测不到芯片（由于芯片进入睡眠
 *       模式将 SWD 调试模式关闭），下次下载时将 P0_12 拉低或按动复位键之后一秒内
 *       即可正常下载调试。
 *
 * \par 源代码
 * \snippet demo_am845_core_hw_pmu_sleep.c src_am845_core_hw_pmu_sleep
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-21  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_pmu_sleep
 * \copydoc demo_am845_core_hw_pmu_sleep.c
 */

/** [src_am845_core_hw_pmu_sleep] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc84x_iocon.h"
#include "demo_nxp_entries.h"
#include "lpc84x_periph_map.h"
#include "lpc84x_pin.h"

/**
 * \brief 例程入口
 */
void demo_am845_core_hw_pmu_sleep_entry (void)
{

    am_kprintf("demo am845_core hw pmu sleep!\r\n");

    /* 延时一秒，方便下次下载程序 */
    am_mdelay(1000);

    /* 配置 PIO0_23 方向为输入 */
    amhw_lpc84x_gpio_pin_dir_input(LPC84X_GPIO, PIO0_23);

    /* 配置 PIO0_23 上拉 */
    amhw_lpc84x_iocon_mode_set(LPC84X_IOCON,
                               PIO0_23,
                               AMHW_LPC84X_IOCON_MODE_PULLUP);

    /* 配置睡眠模式 */
    demo_lpc845_hw_pmu_sleep_entry(LPC84X_PMU, PIO0_23);
}
/** [src_am845_core_hw_pmu_sleep] */

/* end of file */
