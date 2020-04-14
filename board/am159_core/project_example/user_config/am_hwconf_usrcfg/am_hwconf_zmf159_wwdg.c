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
 * \brief ZMF159 WWDT 用户配置文件
 * \sa am_hwconf_zmf159_wwdg.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-24  zcb, first implementation
 * \endinternal
 */

#include "am_zlg_wwdg.h"
#include "am_zmf159.h"
#include "am_zmf159_clk.h"
#include "hw/amhw_zmf159_rcc.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_wwdg
 * \copydoc am_hwconf_zmf159_wwdg.c
 * @{
 */

/** \brief WWDT 平台初始化 */
static void __zmf159_wwdg_plfm_init (void)
{
    am_clk_enable(CLK_WWDG);
    am_zmf159_clk_reset(CLK_WWDG);

    /* 检查复位是否由看门狗造成的 */
    if (amhw_zmf159_rcc_reset_flag() & AMHW_ZMF159_RCC_CSR_WWDGRSTF) {
        amhw_zmf159_rcc_reset_flag_clear();
    }
}

/** \brief 解除WWDT 平台初始化 */
static void __zmf159_wwdg_plfm_deinit (void)
{
    am_clk_disable(CLK_WWDG);
}

/** \brief WWDT 设备信息 */
static const am_zlg_wwdg_devinfo_t  __g_wwdg_devinfo = {
    ZMF159_WWDG_BASE,          /**< \brief WWDT寄存器基址 */
    CLK_WWDG,                  /**< \brief 时钟ID */
    __zmf159_wwdg_plfm_init,   /**< \brief WWDT 平台初始化 */
    __zmf159_wwdg_plfm_deinit, /**< \brief 解除WWDT 平台初始化 */
};

/** \brief WWDT设备实例 */
static am_zlg_wwdg_dev_t __g_wwdg_dev;

/**
 * \brief WWDT 实例初始化，获得WDT标准服务句柄
 */
am_wdt_handle_t am_zmf159_wwdg_inst_init (void)
{
    return am_zlg_wwdg_init(&__g_wwdg_dev, &__g_wwdg_devinfo);
}

/**
 * \brief WWDT 实例解初始化
 */
void am_zmf159_wwdg_inst_deinit (am_wdt_handle_t handle)
{
    am_zlg_wwdg_deinit(handle);
}

/**
 * @}
 */

/* end of file */
