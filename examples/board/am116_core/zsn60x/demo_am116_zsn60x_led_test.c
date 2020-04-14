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
 * \brief zsn60x LED测试程序
 *
 * - 操作步骤：
 *   1. 正确连接并配置好串口；
 *
 * - 实验现象：
 *   1. ZSN600的LED灯将会闪烁，若执行错误则会打印响应的错误标识号 ；
 *
 * \par 源代码
 * \snippet demo_am116_zsn60x_led_test.c src_am116_zsn60x_led_test
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-18  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_am116_if_zsn60x_led_test
 * \copydoc demo_am116_zsn60x_led_test.c
 */

/** [src_am116_zsn60x_led_test] */

#include "zsn60x.h"
#include "demo_components_entries.h"
#include "demo_am116_core_entries.h"
#include "am_hwconf_zsn60x_uart.h"

void demo_am116_zsn60x_led_test_entry()
{
    zsn60x_handle_t  handle = am_zsn60x_uart_inst_init();
    demo_zsn60x_led_test_entry(handle);
}
/** [src_am116_zsn60x_led_test] */

/* end of file */
