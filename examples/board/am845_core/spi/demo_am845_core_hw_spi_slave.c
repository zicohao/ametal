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
 * \brief SPI 从机接收数据例程，通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. 本例程作为从机 SPI，将主机与从机 SPI 进行物理连接。
 *
 * - 实验现象：
 *   1. SPI 接收到数据，通过串口将数据打印出来，并如果接收到的数据是 "nihao"，
 *      则 LED0 会闪烁。
 *
 * \note
 *    1. 本程序需要与 demo_am845_hw_spi_master.c 一同调试；
 *    2. 如需观察串口打印的调试信息，需要将 PIO1_2 引脚连接 PC 串口的 TXD，
 *       PIO1_0 引脚连接 PC 串口的 RXD；
 *    3. 由于 PIO0_12 拉低会导致单片机复位时进入 ISP 模式，所以 PIO0_12 应
 *       单片机复位后再连接。
 *
 * \par 源代码
 * \snippet demo_am845_core_hw_spi_slave.c src_am845_core_hw_spi_slave
 *
 * \internal
 * \par History
 * - 1.01 15-11-26  sky, modified
 * - 1.00 15-07-15  aii, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_spi_slave
 * \copydoc demo_am845_core_hw_spi_slave.c
 */

/** [src_am845_core_hw_spi_slave] */
#include "ametal.h"
#include <string.h>
#include "am_vdebug.h"
#include "hw/amhw_lpc84x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief 例程入口
 */
void demo_am845_core_hw_spi_slave_entry (void)
{
    uint32_t   clk = 0;
    am_kprintf("demo am845_core hw spi slave!\r\n");
    /* SPI0 引脚配置 */
    am_gpio_pin_cfg(PIO0_10, PIO_FUNC_SPI0_SSEL0);
    am_gpio_pin_cfg(PIO0_17, PIO_FUNC_SPI0_SCK);
    am_gpio_pin_cfg(PIO0_18, PIO_FUNC_SPI0_MOSI);
    am_gpio_pin_cfg(PIO0_19, PIO_FUNC_SPI0_MISO);

    /* 使能 SPI0 时钟 */
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_SPI0);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_SPI0);
    clk = amhw_lpc84x_clk_periph_freq_get(LPC84X_SPI0);

    demo_lpc_hw_spi_slave_entry(LPC84X_SPI0,
                                clk);
  
}
/** [src_am845_core_hw_spi_slave] */

/* end of file */
