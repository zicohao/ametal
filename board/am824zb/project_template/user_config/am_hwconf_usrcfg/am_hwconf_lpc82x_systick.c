/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC82X SYSTICK 用户配置库文件
 * \sa am_hwconf_lpc82x_systick.c
 *
 * \internal
 * \par Modification History
 * - 1.00 15-08-  win, first implementation.
 * \endinternal
 */

#include "am_arm_systick.h"
#include "am_lpc82x.h"
#include "hw/amhw_arm_systick.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_systick
 * \copydoc am_hwconf_lpc82x_systick.c
 * @{
 */

/**
 * \brief SYSTICK 设备信息
 * \note 时钟源分为系统时钟（#AMHW_LPC82X_SYSTICK_CONFIG_CLKSRC_SYSTEM）和系统时钟的1/2
 *       （#AMHW_LPC82X_SYSTICK_CONFIG_CLKSRC_SYSTEM_HALF）
 */
static const am_arm_systick_devinfo_t __g_systick_devinfo = {
    LPC82X_SYSTICK_BASE,                      /**< \brief 指向SYSTICK寄存器块指针 */
    CLK_SYSTEM,                               /**< \brief SYSTICK时钟ID, 来源于主时钟 */
    AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM,    /**< \brief SYSTICK时钟选择系统时钟 */

    NULL,                                     /**< \brief 无需平台初始化 */
    NULL                                      /**< \brief 无需平台去初始化 */
};

/** \brief SYSTICK 设备 */
static am_arm_systick_dev_t __g_systick_dev;


/** \brief SYSTICK 实例初始化，获得systick标准服务句柄 */
am_timer_handle_t am_lpc82x_systick_inst_init (void)
{
    return am_arm_systick_init(&__g_systick_dev, &__g_systick_devinfo);
}

/** \brief SYSTICK 实例解初始化 */
void am_lpc82x_systick_inst_deinit (am_timer_handle_t handle)
{
    am_arm_systick_deinit(handle);
}

/**
 * @}
 */

/* end of file */
