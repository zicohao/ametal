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
 * \brief ZLG116 ADC 用户配置文件
 * \sa am_hwconf_zlg116_adc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-13  ari, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_zlg116.h"
#include "am_gpio.h"
#include "am_zlg_adc.h"
#include "hw/amhw_zlg_adc.h"
#include "hw/amhw_zlg116_rcc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg116_adc
 * \copydoc am_hwconf_zlg116_adc.c
 * @{
 */

/** \brief ADC平台初始化 */
static void __zlg_plfm_adc_init (void)
{
    am_gpio_pin_cfg(__ADC_IN1_GPIO, __GPIO__ADC_IN);
    am_gpio_pin_cfg(__ADC_IN8_GPIO, __GPIO__ADC_IN);
    am_clk_enable(CLK_ADC1);
}

/** \brief 解除ADC平台初始化 */
static void __zlg_plfm_adc_deinit (void)
{
    am_gpio_pin_cfg(__ADC_IN1_GPIO, __PIO_GPIO);
    am_gpio_pin_cfg(__ADC_IN8_GPIO, __PIO_GPIO);
    am_clk_disable (CLK_ADC1);
}

/** \brief ADC设备信息 */
static const am_zlg_adc_devinfo_t __g_adc_devinfo = {

    ZLG116_ADC_BASE,                  /**< \brief ADC */
    INUM_ADC_COMP,                    /**< \brief ADC的中断编号 */
    CLK_ADC1,                         /**< \brief ADC时钟号 */

    3300,                             /**< \brief 参考电压 */
    AMHW_ZLG_ADC_DATA_VALID_12BIT, /**< \brief 转换精度 */

    __zlg_plfm_adc_init,              /**< \brief ADC的平台初始化 */
    __zlg_plfm_adc_deinit,            /**< \brief ADC的平台去初始化 */

};

static am_zlg_adc_dev_t  __g_adc_dev;   /**< \brief 定义ADC 设备 */

/** \brief ADC实例初始化，获得ADC标准服务句柄 */
am_adc_handle_t am_zlg116_adc_inst_init (void)
{
    return am_zlg_adc_init(&__g_adc_dev, &__g_adc_devinfo);
}

/** \brief ADC实例解初始化 */
void am_zlg116_adc_inst_deinit (am_adc_handle_t handle)
{
    am_zlg_adc_deinit(handle);
}

/**
 * @}
 */

/* end of file */
