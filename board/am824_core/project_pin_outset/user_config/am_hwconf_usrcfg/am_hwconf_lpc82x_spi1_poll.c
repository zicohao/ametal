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
 * \brief LPC82X SPI (轮询方式) 用户配置文件
 * \sa am_hwconf_lpc82x_spi1_poll.c
 *
 * \pollernal
 * \par Modification history
 * - 1.02 19-01-21  htf, first implementation
 * \endpollernal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc_spi_poll.h"
#include "am_lpc82x_spi_dma.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_spi1_poll
 * \copydoc am_hwconf_lpc82x_spi1_poll.c
 * @{
 */

/**
 * \brief SPI1 平台初始化
 */
am_local void __lpc82x_spi1_poll_plfm_init (void)
{
    am_gpio_pin_cfg(PIO0_11, PIO_FUNC_SPI1_SCK);
    am_gpio_pin_cfg(PIO0_10, PIO_FUNC_SPI1_MOSI);
    am_gpio_pin_cfg(PIO0_9, PIO_FUNC_SPI1_MISO);

    /* CS_Pin 由用户调用 STD 函数时自行传入，此处不需配置 */

    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SPI1);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SPI1);
}

/**
 * \brief SPI1 平台解初始化
 */
am_local void __lpc82x_spi1_poll_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SPI1);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_SPI1);

    am_gpio_pin_cfg(PIO0_11, AM_GPIO_PULLUP | AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO0_10, AM_GPIO_PULLUP | AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO0_9, AM_GPIO_PULLUP | AM_GPIO_INPUT);
}

/** \brief SPI1 (轮询方式) 设备信息 */
am_local am_const struct am_lpc_spi_poll_devinfo __g_lpc82x_spi1_poll_devinfo = {
    LPC82X_SPI1_BASE,                /* SPI1 寄存器块基地址 */
    INUM_SPI1,                       /* SPI1 轮询号 */
    CLK_SPI1,                        /* SPI1 时钟号 */
    __lpc82x_spi1_poll_plfm_init,     /* 平台初始化函数 */
    __lpc82x_spi1_poll_plfm_deinit    /* 平台解初始化函数 */
};

/** \brief SPI1 (轮询方式) 设备实例 */
am_local am_lpc_spi_poll_dev_t __g_lpc82x_spi1_poll_dev;

/**
 * \brief SP0I (轮询方式) 实例初始化
 */
am_spi_handle_t am_lpc82x_spi1_poll_inst_init (void)
{
    return am_lpc_spi_poll_init(&__g_lpc82x_spi1_poll_dev,
                                &__g_lpc82x_spi1_poll_devinfo);
}

/**
 * \brief SPI1 (轮询方式) 实例解初始化
 */
void am_lpc82x_spi1_poll_inst_deinit (am_spi_handle_t handle)
{
    am_lpc_spi_poll_deinit(handle);
}

/**
 * @}
 */

/* end of file */
