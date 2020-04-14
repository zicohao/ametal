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
 * \brief LPC84X I2C0 用户配置文件
 * \sa am_hwconf_lpc84x_i2c0.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

#include <am_lpc84x.h>
#include "ametal.h"
#include "am_lpc_i2c.h"
#include "hw/amhw_lpc84x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc84x_i2c0
 * \copydoc am_hwconf_lpc84x_i2c0.c
 * @{
 */

/**
 * \brief I2C0 平台初始化函数
 */
am_local void __lpc84x_i2c0_plfm_init (void)
{
    am_gpio_pin_cfg(__I2C0_SCL_PIN, AM_LPC84X_GPIO_FUNC_OTHER1);
    am_gpio_pin_cfg(__I2C0_SDA_PIN, AM_LPC84X_GPIO_FUNC_OTHER1);

    amhw_lpc84x_clk_i2c0_clk_sel_set (AMHW_LPC84X_CLK_DEVICE_FRG0CLK);
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_I2C0);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_I2C0);
}

/**
 * \brief I2C0 平台解初始化函数
 */
am_local void __lpc84x_i2c0_plfm_deinit (void)
{
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_I2C0);
    amhw_lpc84x_clk_periph_disable(AMHW_LPC84X_CLK_I2C0);
}

/** \brief I2C0 总线速率参数定义 */
#define __BUS_SPEED_I2C0     (10000)

/** \brief I2C0 设备信息 */
am_local am_const am_lpc_i2c_devinfo_t __g_lpc84x_i2c0_devinfo = {
    __BUS_SPEED_I2C0,           /* I2C0 总线速率 */
    LPC84X_I2C0_BASE,           /* I2C0 寄存器块基址 */
    INUM_I2C0,                  /* I2C0 中断号 */
    CLK_I2C0,                   /* I2C0 时钟号 */
    10,                         /* 超时时间 */
    __lpc84x_i2c0_plfm_init,    /* 平台初始化函数 */
    __lpc84x_i2c0_plfm_deinit   /* 平台解初始化函数 */
};

/** \brief I2C0 设备实例 */
am_local am_lpc_i2c_dev_t __g_lpc84x_i2c0_dev;

/**
 * \brief I2C0 实例初始化
 */
am_i2c_handle_t am_lpc84x_i2c0_inst_init (void)
{
    return am_lpc_i2c_init(&__g_lpc84x_i2c0_dev, &__g_lpc84x_i2c0_devinfo);
}

/**
 * \brief I2C0 实例解初始化
 */
void am_lpc84x_i2c0_inst_deinit (am_i2c_handle_t handle)
{
    am_lpc_i2c_deinit(handle);
}

/**
 * @}
 */

/* end of file */
