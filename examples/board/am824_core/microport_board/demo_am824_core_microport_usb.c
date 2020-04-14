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
 * \brief MicroPort USB(XR21V141x) 例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 将 MicroPort USB 扩展板连接到 AM824-Core 的 MicroPort 接口；
 *   2. 将  MicroPort USB 扩展板上的 USB 接口与 PC 连接并通过串口助手打开。
 *
 * - 实验现象：
 *   1. 串口输出"MicroPort USB Test:"；
 *   2. 串口输出接收到的字符串。
 *
 * \note
 *   1. XR21V141x 为 USB 转串口芯片，使用前需要安装驱动程序。用户可以在 EXAR
 *      官方网站(http://www.exarcorp.cn/design-tools/software-drivers)下载；
 *   2. 例程使用 USART0，与 DEBUG 调试使用串口相同，如需观察串口打印的调试信息，需
 *      要将 PIO0_0 引脚连接 PC 串口的 TXD，PIO0_4 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_microport_usb.c src_microport_usb
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_usb
 * \copydoc demo_microport_usb.c
 */

/** [src_microport_usb] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief 例程入口
 */
void demo_am824_core_microport_usb_entry (void)
{

    AM_DBG_INFO("demo am824_core microport usb!\r\n");

    demo_std_uart_polling_entry(am_lpc82x_usart0_inst_init());
}
/** [src_microport_usb] */

/* end of file */
