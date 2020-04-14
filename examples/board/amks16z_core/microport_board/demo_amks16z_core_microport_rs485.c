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
 * \brief MicroPort RS485 例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 将 MicroPort RS485 配板连接到 AMKS16RFID 的 MicroPort 接口。
 *
 * - 实验现象：
 *   1. 串口输出"RS485 Test:"；
 *   2. 串口输出接收到的字符串。
 *
 * \note
 *   1. TP8485E 为 RS485 转串口芯片；
 *   2. 例程使用 USART0，与 DEBUG 调试使用串口相同。
 *   3. 每次测试发送的字符数应不超过64个。
 *
 * \par 源代码
 * \snippet demo_microport_rs485.c src_microport_rs485
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_rs485
 * \copydoc demo_microport_rs485.c
 */

/** [src_microport_rs485] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_kl26_inst_init.h"
#include "am_hwconf_microport.h"
#include "demo_std_entries.h"
#include "demo_amks16z_core_all_entries.h"

/**
 * \brief MicroPort RS485 例程，通过标准接口实现
 *
 * \param 无
 *
 * \return 无
 */
void demo_amks16z_core_microport_rs485_entry (void)
{
    AM_DBG_INFO("demo amks16z_core microport rs485!\r\n");

    demo_std_uart_rs485_entry(am_microport_rs485_inst_init());
}

/** [src_microport_rs485] */

/* end of file */
