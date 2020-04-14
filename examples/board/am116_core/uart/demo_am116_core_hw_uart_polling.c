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
 * \brief UART 轮询方式例程，通过 HW 层接口实现
 *
 *
 * - 实验现象：
 *   1. 串口输出 "HW example---UART test in polling mode:"；
 *   2. 串口输出接收到的字符串。
 *
 * \note
 *    1. 如需观察串口打印的调试信息，需要将 PIOA_9 引脚连接 PC 串口的 RXD；
 *    2. 如果调试串口使用与本例程相同，则不应在后续继续使用调试信息输出函数
 *      （如：AM_DBG_INFO()）。
 *
 * \par 源代码
 * \snippet demo_am116_core_hw_uart_polling.c src_am116_core_hw_uart_polling
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  ari, first implementation
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_am116_core_hw_uart_polling
 * \copydoc demo_am116_core_hw_uart_polling.c
 */

/** [src_am116_core_hw_uart_polling] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zlg116.h"
#include "demo_zlg_entries.h"
#include "demo_am116_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_am116_core_hw_uart_polling_entry (void)
{
    AM_DBG_INFO("demo am116_core hw uart polling!\r\n");

    /* 初始化引脚 */
    am_gpio_pin_cfg(PIOA_9, PIOA_9_UART1_TX | PIOA_9_AF_PP);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_UART1_RX| PIOA_10_INPUT_FLOAT);

    /* 使能时钟 */
    am_clk_enable(CLK_UART1);

    demo_zlg_hw_uart_polling_entry(ZLG116_UART1, am_clk_rate_get(CLK_UART1));
}
/** [src_am116_core_hw_uart_polling] */

/* end of file */
