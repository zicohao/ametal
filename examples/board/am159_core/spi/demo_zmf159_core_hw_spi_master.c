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
 * \brief SPI 主机例程，通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. 将 SPI 的 MOSI 引脚和 MISO 引脚用线相连，模拟从机设备，回环测试。
 *
 * - 实验现象：
 *   1. 主机通过 MISO 发送数据，发出的数据从 MOSI 读回；
 *   2. 比较发出和读回的数据，如果相同 LED0 长亮,否则以 200ms 时间间隔闪烁。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIOA_10 引脚连接 PC 串口的 TXD，
 *    PIOA_9 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_zmf159_hw_spi_master.c src_zmf159_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.00 17-04-27  ari, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_hw_spi_master
 * \copydoc demo_zmf159_hw_spi_master.c
 */

/** [src_zmf159_hw_spi_master] */
#include <demo_zmf159_core_entries.h>
#include "ametal.h"
#include "am_zmf159.h"
#include "am_zmf159_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "demo_zlg_entries.h"
#include "am_zmf159_inst_init.h"

/**
 * \brief 例程入口
 */
void demo_zmf159_core_hw_spi_master_entry (void)
{
    am_kprintf("demo zmf159_core hw spi master!\r\n");

    /* 开启时钟 */
    am_clk_enable(CLK_SPI1);

    /* 配置引脚 */
    am_gpio_pin_cfg(PIOB_3, PIOB_3_SPI1_SCK | PIOB_3_AF_PP);

    am_gpio_pin_cfg(PIOB_4, PIOB_4_SPI1_MISO | PIOB_4_INPUT_PU);
    am_gpio_pin_cfg(PIOB_5, PIOB_5_SPI1_MOSI | PIOB_5_AF_PP);
    am_gpio_pin_cfg(PIOA_15, PIOA_15_SPI1_NSS | PIOA_15_AF_PP);

    demo_zlg_hw_spi_master_entry(ZMF159_SPI1,
                                 PIOA_15,
                                 am_clk_rate_get(CLK_SPI1));
}
/** [src_zmf159_hw_spi_master] */

/* end of file */
