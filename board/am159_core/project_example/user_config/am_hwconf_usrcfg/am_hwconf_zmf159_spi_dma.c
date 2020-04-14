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
 * \brief ZMF159 SPI 用户配置文件
 * \sa am_hwconf_zlg116_spi_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-10-23  ari, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zmf159.h"
#include "am_zlg_spi_dma.h"
#include "am_gpio.h"
#include "hw/amhw_zlg_spi.h"
#include "am_clk.h"
#include "zmf159_dma_chan.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_spi_dma
 * \copydoc am_hwconf_zmf159_spi_dma.c
 * @{
 */

/** \brief SPI1 平台初始化 */
static void __zmf159_plfm_spi1_dma_init (void)
{
    am_gpio_pin_cfg(PIOB_3, PIOB_3_SPI1_SCK | PIOB_3_AF_PP);
    am_gpio_pin_cfg(PIOB_4, PIOB_4_SPI1_MISO | PIOB_4_INPUT_PU);
    am_gpio_pin_cfg(PIOB_5, PIOB_5_SPI1_MOSI | PIOB_5_AF_PP);
//    am_gpio_pin_cfg(PIOA_15, PIOA_15_SPI1_NSS | PIOA_15_AF_PP);

    am_clk_enable(CLK_SPI1);
}

/** \brief 解除SPI1 平台初始化 */
static void __zmf159_plfm_spi1_dma_deinit (void)
{

    /* 释放引脚为输入模式 */
    am_gpio_pin_cfg(PIOB_3, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_4, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_5, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI1);
}

/**
 * \brief SPI1 设备信息
 */
const  struct am_zlg_spi_dma_devinfo  __g_spi1_dma_devinfo = {
    ZMF159_SPI1_BASE,               /**< \brief SPI1寄存器指针 */
    CLK_SPI1,                       /**< \brief 时钟ID号 */
    INUM_SPI1,                      /**< \brief SPI1中断号 */
    0,                              /**< \brief SPI1配置标识 */
    DMA_CHAN_SPI1_TX,
    DMA_CHAN_SPI1_RX,
    __zmf159_plfm_spi1_dma_init,    /**< \brief SPI1平台初始化函数 */
    __zmf159_plfm_spi1_dma_deinit   /**< \brief SPI1平台解初始化函数 */
};

/** \brief SPI1 设备实例 */
static am_zlg_spi_dma_dev_t __g_spi1_dma_dev;

/** \brief SPI1 实例初始化，获得SPI标准服务句柄 */
am_spi_handle_t am_zmf159_spi1_dma_inst_init (void)
{
    return am_zlg_spi_dma_init(&__g_spi1_dma_dev, &__g_spi1_dma_devinfo);
}

/** \brief SPI1 实例解初始化 */
void am_zmf159_spi1_dma_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_dma_deinit(handle);
}

/*******************************************************************************/

/** \brief SPI2 平台初始化 */
static void __zmf159_plfm_spi2_dma_init (void)
{
    am_gpio_pin_cfg(PIOB_13, PIOB_13_SPI2_SCK | PIOB_13_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_14, PIOB_14_SPI2_MISO | PIOB_14_AF_PP);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI2_MOSI  | PIOB_15_AF_PP);

    am_clk_enable(CLK_SPI2);
}

/** \brief 解除 SPI2 平台初始化 */
static void __zmf159_plfm_spi2_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOB_13, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_14, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_15, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI2);
}

/**
 * \brief SPI2 设备信息
 */
static const struct am_zlg_spi_dma_devinfo  __g_spi2_dma_devinfo = {
    ZMF159_SPI2_BASE,                /**< \brief SPI2 寄存器指针 */
    CLK_SPI2,                        /**< \brief 时钟 ID 号 */
    INUM_SPI2,                       /**< \brief SPI2中断号 */
    0,                               /**< \brief SPI2 配置标识 */

    DMA_CHAN_SPI2_TX,
    DMA_CHAN_SPI2_RX,
    __zmf159_plfm_spi2_dma_init,     /**< \brief SPI2 平台初始化函数 */
    __zmf159_plfm_spi2_dma_deinit    /**< \brief SPI2 平台解初始化函数 */
};

/** \brief SPI2 设备实例 */
static am_zlg_spi_dma_dev_t __g_spi2_dma_dev;

/** \brief SPI2 实例初始化，获得 SPI 标准服务句柄 */
am_spi_handle_t am_zmf159_spi2_dma_inst_init (void)
{
    return am_zlg_spi_dma_init(&__g_spi2_dma_dev, &__g_spi2_dma_devinfo);
}

/** \brief SPI2 实例解初始化 */
void am_zlg_spi2_dma_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_dma_deinit(handle);
}

/*******************************************************************************/

/** \brief SPI3 平台初始化 */
static void __zmf159_plfm_spi3_dma_init (void)
{
    am_gpio_pin_cfg(PIOC_10, PIOC_10_SPI3_SCK  | PIOC_10_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOC_11, PIOC_11_SPI3_MISO | PIOC_11_AF_PP);
    am_gpio_pin_cfg(PIOC_12, PIOC_12_SPI3_MOSI | PIOC_12_AF_PP);

    am_clk_enable(CLK_SPI3);
}

/** \brief 解除 SPI3 平台初始化 */
static void __zmf159_plfm_spi3_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOC_10, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOC_11, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOC_12, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI3);
}

/**
 * \brief SPI3 设备信息
 */
static const struct am_zlg_spi_dma_devinfo  __g_spi3_dma_devinfo = {
    ZMF159_SPI3_BASE,                /**< \brief SPI3 寄存器指针 */
    CLK_SPI3,                        /**< \brief 时钟 ID 号 */
    INUM_SPI3,                       /**< \brief SPI3中断号 */
    0,                               /**< \brief SPI3 配置标识 */

    DMA_CHAN_SPI2_TX,
    DMA_CHAN_SPI2_RX,
    __zmf159_plfm_spi3_dma_init,     /**< \brief SPI3 平台初始化函数 */
    __zmf159_plfm_spi3_dma_deinit    /**< \brief SPI3 平台解初始化函数 */
};

/** \brief SPI3 设备实例 */
static am_zlg_spi_dma_dev_t __g_spi3_dma_dev;

/** \brief SPI3 实例初始化，获得 SPI 标准服务句柄 */
am_spi_handle_t am_zmf159_spi3_dma_inst_init (void)
{
    return am_zlg_spi_dma_init(&__g_spi3_dma_dev, &__g_spi3_dma_devinfo);
}

/** \brief SPI2 实例解初始化 */
void am_zlg_spi3_dma_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_dma_deinit(handle);
}


/**
 * @}
 */

/* end of file */
