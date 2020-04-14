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
 * \brief 按键输入演示例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 将 J14 的 KEY 和 PIOC_7 短接在一起。
 *
 * - 实验现象:
 *   1. 按下按键时 LED0 亮，松开按键时 LED0 灭。
 *
 * \note
 *    1. LED0 需要短接 J9 跳线帽，才能被 PIOC_9 控制；
 *    2. 如需观察串口打印的调试信息，需要将 PIOA_10 引脚连接 PC 串口的 TXD，
 *       PIOA_9 引脚连接 PC 串口的 RXD。
 *    3. 测试本 Demo 必须在 am_prj_config.h 内将 AM_CFG_KEY_GPIO_ENABLE、
 *       AM_CFG_KEY_ENABLE 和 AM_CFG_SOFTIMER_ENABLE 定义为 1。但这些宏
 *       已经默认配置为 1， 用户不必再次配置；
 *
 * \par 源代码
 * \snippet demo_zlg217_std_key_input_event.c src_zlg217_std_key_input_event
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-8  hbt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_key_input_event
 * \copydoc demo_zlg217_std_key_input_event.c
 */

/** [src_zlg217_std_key_input_event] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_am217_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_zlg217_core_std_key_input_event_entry (void)
{
    AM_DBG_INFO("demo am217_core std input event!\r\n");

    demo_std_key_entry();
}
/** [src_zlg217_std_key_input_event] */

/* end of file */
