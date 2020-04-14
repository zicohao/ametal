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
 * \brief USART 例程（轮询方式），通过标准接口实现
 *
 * - 实验现象：
 *   1. 串口输出 "USART poll mode test:"；
 *   2. 串口输出接收到的字符串。
 *
 * \note
 *    1. 例程使用 USART0，与 DEBUG 调试使用串口相同；
 *    2. 如需观察串口打印的调试信息，需要将 PIO0_0 引脚连接 PC 串口的 TXD，
 *       PIO0_4 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_am824_std_usart_poll.c src_am824_std_usart_poll
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_usart_poll
 * \copydoc demo_am824_std_usart_poll.c
 */

/** [src_am824_std_usart_poll] */
#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"
#include "am_vdebug.h"
/**
 * \brief 例程入口
 */
void demo_am824_core_std_usart_poll_entry (void)
{

    AM_DBG_INFO("demo am824_core std uart polling!\r\n");
  
    demo_std_uart_polling_entry(am_lpc82x_usart0_inst_init());
}
/** [src_am824_std_usart_poll] */

/* end of file */
