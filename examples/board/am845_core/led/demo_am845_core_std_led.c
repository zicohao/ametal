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
 * - 实验现象：
 *   1. LED0 和 LED1 以 0.5s 的时间间隔闪烁。
 *
 * \note
 *    1. 测试本例程必须在 am_prj_config.h 内将 AM_CFG_LED_ENABLE 定义为 1，但该宏
 *       已经默认配置为 1， 用户不必再次配置。
 *
 * \par 源代码
 * \snippet demo_am845_core_std_led.c src_am845_core_std_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_led
 * \copydoc demo_am845_core_std_led.c
 */

/** [src_am845_core_std_led] */
#include "ametal.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"

/**
 * \brief 例程入口
 */
void demo_am845_core_std_led_entry (void)
{
    am_kprintf("demo am845_core std led!\r\n");
  
    demo_std_led_entry(LED0);
}
/** [src_am845_core_std_led] */

/* end of file */
