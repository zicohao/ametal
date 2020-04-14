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
 * \brief MicroPort-DS1302 例程，通过 RTC 标准接口实现
 *
 * - 操作步骤：
 *   1. 将 MicroPort-DS1302 扩展板连接到 AM824-Core 的 MicroPort 接口。
 *
 * - 实验现象：
 *   1. 串口将每一秒的时间信息打印出来。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIO0_0 引脚连接 PC 串口的 TXD，
 *    PIO0_4 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_microport_ds1302.c src_microport_ds1302
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-16  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_ds1302
 * \copydoc demo_microport_ds1302.c
 */

/** [src_microport_ds1302] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc84x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief 例程入口
 */
void demo_am824_core_microport_ds1302_entry (void)
{
    AM_DBG_INFO("demo am116_core microport ds1302!\r\n");

    demo_std_rtc_entry(am_microport_ds1302_rtc_inst_init());
}
/** [src_microport_ds1302] */

/* end of file */
