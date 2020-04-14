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
 * \brief ZLG217 SPI INT 用户配置文件
 * \sa am_hwconf_zlg217_spi.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-8-22  fra, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg_spi_int.h"
#include "am_gpio.h"
#include "amhw_zlg_spi.h"
#include "am_clk.h"
#include "am_zlg217.h"
#include "zlg217_pin.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_spi_int
 * \copydoc am_hwconf_zlg217_spi_int.c
 * @{
 */

/** \brief SPI1 平台初始化 */
static void __zlg_plfm_spi1_int_init (void)
{
    am_gpio_pin_cfg(__SPI1_SCK , __GPIO_SPI1_SCK );
    am_gpio_pin_cfg(__SPI1_MISO, __GPIO_SPI1_MISO);
    am_gpio_pin_cfg(__SPI1_MOSI, __GPIO_SPI1_MOSI);

    am_clk_enable(CLK_SPI1);
}

/** \brief 解除SPI1 平台初始化 */
static void __zlg_plfm_spi1_int_deinit (void)
{
    am_gpio_pin_cfg(__SPI1_SCK , AM_GPIO_INPUT );
    am_gpio_pin_cfg(__SPI1_MISO, AM_GPIO_INPUT );
    am_gpio_pin_cfg(__SPI1_MOSI, AM_GPIO_INPUT );

    am_clk_disable(CLK_SPI1);
}

/** \brief SPI1 设备信息 */
const  struct am_zlg_spi_int_devinfo  __g_spi1_int_devinfo = {
    ZLG217_SPI1_BASE,                        /**< \brief SPI1寄存器指针 */
    CLK_SPI1,                                /**< \brief 时钟ID号 */
    INUM_SPI1,                               /**< \brief SPI1中断号 */
    PIOA_7_SPI1_MOSI_REMAP0 | PIOA_7_AF_PP,  /**< \brief SPI1配置标识 */
    PIOA_7,                                  /**< \brief MOSI引脚号 */
    __zlg_plfm_spi1_int_init,                /**< \brief SPI1平台初始化函数 */
    __zlg_plfm_spi1_int_deinit               /**< \brief SPI1平台解初始化函数 */
};

/** \brief SPI1 设备实例 */
static am_zlg_spi_int_dev_t __g_spi1_int_dev;

/** \brief SPI1 实例初始化，获得SPI标准服务句柄 */
am_spi_handle_t am_zlg217_spi1_int_inst_init (void)
{
    return am_zlg_spi_int_init(&__g_spi1_int_dev, &__g_spi1_int_devinfo);
}

/** \brief SPI1 实例解初始化 */
void am_zlg217_spi1_int_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_int_deinit(handle);
}

/** \brief SPI2 平台初始化 */
static void __zlg_plfm_spi2_int_init (void)
{
    am_gpio_pin_cfg(__SPI2_SCK , __GPIO_SPI2_SCK);
    am_gpio_pin_cfg(__SPI2_MISO, __GPIO_SPI2_MISO);
    am_gpio_pin_cfg(__SPI2_MOSI, __GPIO_SPI2_MOSI);

    am_clk_enable(CLK_SPI2);
}

/** \brief 解除SPI2 平台初始化 */
static void __zlg_plfm_spi2_int_deinit (void)
{
    am_gpio_pin_cfg(__SPI2_SCK , AM_GPIO_INPUT);
    am_gpio_pin_cfg(__SPI2_MISO, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__SPI2_MOSI, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI2);
}
/**
 * \brief SPI2 设备信息
 */
const  struct am_zlg_spi_int_devinfo  __g_spi2_int_devinfo = {
    ZLG217_SPI2_BASE,                      /**< \brief SPI2寄存器指针 */
    CLK_SPI2,                              /**< \brief 时钟ID号 */
    INUM_SPI2,                             /**< \brief SPI2中断号 */
    PIOB_15_SPI2_MOSI | PIOB_15_AF_PP,     /**< \brief SPI2配置标识 */
    PIOB_15,                               /**< \brief mosi引脚号 */
    __zlg_plfm_spi2_int_init,              /**< \brief SPI2平台初始化函数 */
    __zlg_plfm_spi2_int_deinit             /**< \brief SPI2平台解初始化函数 */
};

/** \brief SPI2 设备实例 */
static am_zlg_spi_int_dev_t __g_spi2_int_dev;

/** \brief SPI2 实例初始化，获得SPI标准服务句柄 */
am_spi_handle_t am_zlg217_spi2_int_inst_init (void)
{
    return am_zlg_spi_int_init(&__g_spi2_int_dev, &__g_spi2_int_devinfo);
}

/** \brief SPI2 实例解初始化 */
void am_zlg217_spi2_int_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_int_deinit(handle);
}

/**
 * @}
 */

/* end of file */
