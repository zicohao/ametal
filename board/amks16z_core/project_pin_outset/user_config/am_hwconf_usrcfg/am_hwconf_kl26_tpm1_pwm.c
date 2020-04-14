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
 * \brief KL26 TPM1 用于PWM输出 用户配置文件
 * \sa am_fsl_hwconfig_tpm1_pwm.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-09-18  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "hw/amhw_kl26_sim.h"
#include "am_fsl_tpm_pwm.h"
#include "../../../../../soc/freescale/kl26/am_kl26.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_tpm1_pwm
 * \copydoc am_kl26_hwconfig_tpm1_pwm.c
 * @{
 */

/** \brief TPM1用于PWM输出 平台初始化 */
void __kl26_plfm_tpm1_pwm_init (void)
{
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TPM1);
    amhw_kl26_sim_tpm_src_set(KL26_SIM_TPMSRC_PLLFLLCLK);
}

/** \brief 解除TPM1平台初始化 */
void __kl26_plfm_tpm1_pwm_deinit (void)
{
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_TPM1);
}

/** \brief TPM1用于PWM功能的引脚配置信息列表 */
am_fsl_tpm_pwm_ioinfo_t __g_tpm1_pwm_ioinfo_list[] = {
    {__TPM1_CH0, __GPIO_TPM1_CH0, __PIO_GPIO | AM_GPIO_INPUT},  /**< \brief 通道0 */
    {__TPM1_CH1, __GPIO_TPM1_CH1, __PIO_GPIO | AM_GPIO_INPUT},  /**< \brief 通道1 */
};

/** \brief TPM1用于PWM设备信息 */
const am_fsl_tpm_pwm_devinfo_t  __g_tpm1_pwm_devinfo = {
    KL26_TPM1,                       /**< \brief 指向TPM1寄存器块的指针 */
    2,                               /**< \brief 2个PWM输出通道 */
    CLK_TPM1,                        /**< \brief 时钟号 */
    &__g_tpm1_pwm_ioinfo_list[0],
    __kl26_plfm_tpm1_pwm_init,       /**< \brief 平台初始化函数 */
    __kl26_plfm_tpm1_pwm_deinit      /**< \brief 平台解初始化函数 */
};

/** \brief TPM1用于PWM设备定义 */
am_fsl_tpm_pwm_dev_t  __g_tpm1_pwm_dev;

/** \brief tpm2 pwm 实例初始化，获得pwm标准服务句柄 */
am_pwm_handle_t am_kl26_tpm1_pwm_inst_init (void)
{
    return am_fsl_tpm_pwm_init(&__g_tpm1_pwm_dev,
                               &__g_tpm1_pwm_devinfo);
}

/** \brief tpm2 pwm 实例解初始化 */
void am_kl26_tpm1_pwm_inst_deinit (am_pwm_handle_t handle)
{
    am_fsl_tpm_pwm_deinit(handle);
}

/**
 * @}
 */

/* end of file */
