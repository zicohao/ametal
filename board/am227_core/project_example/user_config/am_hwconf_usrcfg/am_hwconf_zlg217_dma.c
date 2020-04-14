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
 * \brief ZLG217 DMA 用户配置文件
 * \sa am_hwconf_zlg217_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-22  fra, first implementation
 * \endinternal
 */

#include "am_clk.h"
#include "am_zlg217.h"
#include "amhw_zlg217_rcc.h"
#include "am_zlg_dma.h"
/**
 * \addtogroup am_if_src_hwconf_zlg217_dma
 * \copydoc am_hwconf_zlg217_dma.c
 * @{
 */

/**
 * \brief DMA 平台初始化。
 */
static void __zlg217_plfm_dma_init (void)
{
    am_clk_enable(CLK_DMA);
}

/**
 * \brief DMA 平台去初始化。
 */
static void __zlg217_plfm_dma_deinit (void)
{
    am_clk_disable(CLK_DMA);
}

/** \brief DMA 设备信息 */
static const am_zlg_dma_devinfo_t __g_dma_devinfo = {
    ZLG217_DMA_BASE,           /**< \brief 指向DMA寄存器块的指针 */
    INUM_DMA1_1,               /**< \brief DMA中断向量号开始 */
    INUM_DMA1_7,               /**< \brief DMA中断向量号结束 */
    __zlg217_plfm_dma_init,    /**< \brief DMA平台初始化 */
    __zlg217_plfm_dma_deinit   /**< \brief DMA平台解初始化 */
};

/** \brief DMA设备实例 */
static am_zlg_dma_dev_t __g_dma_dev;

/**
 * \brief DMA 实例初始化
 * \return 无
 */
int am_zlg217_dma_inst_init (void)
{
    //return am_zlg217_dma_init(&__g_dma_dev, &__g_dma_devinfo);
    return am_zlg_dma_init(&__g_dma_dev, &__g_dma_devinfo);
}

/**
 * \brief DMA 实例解初始化
 * \return 无
 */
void am_zlg217_dma_inst_deinit (void)
{
    am_zlg_dma_deinit();
}

/**
 * @}
 */

/* end of file */
