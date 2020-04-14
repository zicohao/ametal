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
 * \brief MicroPort FLASH 例程，通过标准接口实现。
 *
 * - 操作步骤:
 *   1. 将 MicroPort FLASH 配板连接到 AMKS16RFID 的 MicroPort 接口。
 *
 * - 实验现象:
 *   1. 主机写数据到 FLASH；
 *   2. 主机从 FLASH 读取数据，并通过串口打印处理；
 *   3. 串口打印出测试结果。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIOA_1 引脚连接 PC 串口的 TXD，
 *    PIOA_2 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_microport_flash.c src_microport_flash
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_microport_flash
 * \copydoc demo_microport_flash.c
 */

/** [src_microport_flash] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_hwconf_microport.h"
#include "demo_components_entries.h"
#include "am_kl26_inst_init.h"
#include "demo_amks16z_core_all_entries.h"

/**
 * \brief MicroPort FLASH 例程，通过标准接口实现
 *
 * \param 无
 *
 * \return 无
 */
void demo_amks16z_core_microport_flash_entry (void)
{
    AM_DBG_INFO("demo amks16z_core microport flash!\r\n");

    demo_mx25xx_entry(am_microport_flash_inst_init(), 8);
}

/** [src_microport_flash] */

/* end of file */
