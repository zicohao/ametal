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
 * \brief SPI 回环例程（中断方式），通过标准接口实现
 *
 * - 操作步骤：
 *   1. 短接 SPI 的 MOSI(PIO0_18) 和 MISO(PIO0_19)；
 *
 * - 实验现象：
 *   1. 主机发起一次传输，并校验发送的数据与接收的数据是否一致；
 *
 * \note
 *    1. 如需观察串口打印的调试信息，需要将 PIO1_2 引脚连接 PC 串口的 TXD，
 *       PIO1_0 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_am845_core_std_spi_master_int.c src_am845_core_std_spi_master_int
 *
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_spi_master_int
 * \copydoc demo_am845_core_std_spi_master_int.c
 */

/** [src_am845_core_std_spi_master_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc84x.h"
#include "am_lpc84x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief 例程入口
 */
void demo_am845_core_std_spi_master_int_entry (void)
{
    am_kprintf("demo am845 std spi master int!\r\n");
  
    am_spi_handle_t spi_handle = am_lpc84x_spi0_int_inst_init();
    demo_std_spi_master_entry(spi_handle, PIO0_10);
}
/** [src_am845_core_std_spi_master_int] */

/* end of file */
