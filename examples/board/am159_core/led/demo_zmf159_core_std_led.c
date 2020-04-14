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
 * \brief LED 例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 短接 J9 和 J10 跳线帽，PIOC_9 和 PIOA_8 分别控制 LED0 和 LED1。
 *
 * - 实验现象：
 *   1. LED0 和 LED1 以 0.3s 的时间间隔闪烁。
 *
 * \note
 *    测试本 Demo 必须在 am_prj_config.h 内将 AM_CFG_LED_ENABLE 定义为 1
 *    但这些宏已经默认配置为 1， 用户不必再次配置；
 *
 * \par 源代码
 * \snippet demo_zmf159_std_led.c src_std_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_std_led
 * \copydoc demo_zmf159_std_led.c
 */

/** [src_std_led] */
#include <demo_zmf159_core_entries.h>
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"

/**
 * \brief 例程入口
 */
void demo_zmf159_core_std_led_entry (void)
{
    AM_DBG_INFO("demo zmf159_core std led!\r\n");

    demo_std_led_entry(LED0);
}
/** [src_std_led] */

/* end of file */
