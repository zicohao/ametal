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
 * \brief MicroPort-FLASH 例程，通过 FTL 标准接口实现
 *
 * 由于使用 MX25XX 标准接口和 MTD 接口需要在每次写入数据前，确保相应的存
 * 储空间已经被擦除，势必会给编程带来很大麻烦。于此同时，由于 MX25L1606
 * 的某一地址段擦除次数超过 10 万次的上限，相应段地址空间存储数据将不再
 * 可靠。所以 AMetal 提供 FTL 标准接口给用户使用，降低编程难度。
 *
 * - 操作步骤：
 *   1. 将 MicroPort-FLASH 扩展板连接到 AM845-Core 的 MicroPort 接口。
 *
 * - 实验现象：
 *   1. 主机写数据到 FLASH；
 *   2. 主机从 FLASH 读取数据，并通过串口打印处理；
 *   3. 串口打印出测试结果。
 *
 * \note
 *    1. 如需观察串口打印的调试信息，需要将 PIO1_2 引脚连接 PC 串口的 TXD，
 *       PIO1_0 引脚连接 PC 串口的 RXD；
 *    2. 使用 FTL 接口需要消耗一定的 RAM 空间以及一定数量的逻辑块。
 *
 * \par 源代码
 * \snippet demo_microport_flash_ftl.c src_microport_flash_ftl
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_flash_ftl
 * \copydoc demo_microport_flash_ftl.c
 */

/** [src_microport_flash_ftl] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc84x_inst_init.h"
#include "demo_components_entries.h"

/**
 * \brief 例程入口
 */
void demo_am845_core_microport_flash_ftl_entry (void)
{
    AM_DBG_INFO("demo am845_core microport flash ftl!\r\n");

    demo_ftl_entry(am_microport_flash_ftl_inst_init(), 8);
}
/** [src_microport_flash_ftl] */

/* end of file */
