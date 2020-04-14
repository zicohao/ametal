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
 * \brief ZLG217 I2C 从机用户配置文件
 * \sa am_hwconf_zlg217_i2c.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-07  vir, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg217.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zlg_i2c_slv.h"
#include "am_zlg217_clk.h"
#include "amhw_zlg_i2c.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_i2c_slv
 * \copydoc am_hwconf_zlg217_i2c_slv.c
 * @{
 */

/** \brief I2C1 平台初始化函数 */
static void __zlg_i2c1_plfm_init (void)
{
    am_gpio_pin_cfg(__I2C1_SCL, __GPIO_I2C1_SCL);
    am_gpio_pin_cfg(__I2C1_SDA, __GPIO_I2C1_SDA);

    am_clk_enable(CLK_I2C1);
    am_zlg217_clk_reset(CLK_I2C1);
}

/** \brief 解除I2C1 平台初始化函数 */
static void __zlg_i2c1_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C1);
}

/**
 * \name I2C1 控制器参数定义
 * @{
 */

/** @} */

/**
 * \brief I2C1 从机设备信息
 */
static const am_zlg_i2c_slv_devinfo_t __g_i2c1_devinfo = {

    ZLG217_I2C1_BASE,                 /**< \brief I2C1 寄存器块基址 */
    INUM_I2C1_EV,                     /**< \brief I2C1 中断编号 */

    __zlg_i2c1_plfm_init,             /**< \brief 平台初始化 */
    __zlg_i2c1_plfm_deinit            /**< \brief 平台去初始化 */
};

/**< \brief I2C1 设备实例 */
static am_zlg_i2c_slv_dev_t __g_i2c1_dev;

/** \brief I2C1 实例初始化，获得I2C标准服务句柄 */
am_i2c_slv_handle_t  am_zlg217_i2c1_slv_inst_init (void)
{
    return am_zlg_i2c_slv_init(&__g_i2c1_dev, &__g_i2c1_devinfo);
}

/** \brief I2C1 实例解初始化 */
void am_zlg217_i2c1_slv_inst_deinit (am_i2c_slv_handle_t handle)
{
    am_zlg_i2c_slv_deinit(handle);
}

/** \brief I2C2 平台初始化函数 */
static void __zlg_i2c2_plfm_init (void)
{
    am_gpio_pin_cfg(__I2C2_SCL, __GPIO_I2C2_SCL);
    am_gpio_pin_cfg(__I2C2_SDA, __GPIO_I2C2_SDA);

    am_clk_enable(CLK_I2C2);
    am_zlg217_clk_reset(CLK_I2C2);
}

/** \brief 解除I2C1 平台初始化函数 */
static void __zlg_i2c2_plfm_deinit (void)
{
    am_clk_disable(CLK_I2C2);
}

/**
 * \name I2C2 控制器参数定义
 * @{
 */

/** @} */

/**
 * \brief I2C2 从机设备信息
 */
static const am_zlg_i2c_slv_devinfo_t __g_i2c2_devinfo = {

    ZLG217_I2C2_BASE,                 /**< \brief I2C2寄存器块基址 */
    INUM_I2C2_EV,                     /**< \brief I2C2 中断编号 */

    __zlg_i2c2_plfm_init,             /**< \brief 平台初始化 */
    __zlg_i2c2_plfm_deinit            /**< \brief 平台去初始化 */
};

/**< \brief I2C2 设备实例 */
static am_zlg_i2c_slv_dev_t __g_i2c2_dev;

/** \brief I2C2 实例初始化，获得I2C标准服务句柄 */
am_i2c_slv_handle_t  am_zlg217_i2c2_slv_inst_init (void)
{
    return am_zlg_i2c_slv_init(&__g_i2c2_dev, &__g_i2c2_devinfo);
}

/** \brief I2C2 实例解初始化 */
void am_zlg217_i2c2_slv_inst_deinit (am_i2c_slv_handle_t handle)
{
    am_zlg_i2c_slv_deinit(handle);
}

/** @} */

/* end of file */
