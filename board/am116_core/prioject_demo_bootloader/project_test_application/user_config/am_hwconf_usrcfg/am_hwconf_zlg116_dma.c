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
 * \brief ZLG116 DMA 用户配置文件
 * \sa am_hwconf_zlg116_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-20  ari, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_zlg116.h"
#include "am_zlg_dma.h"
#include "hw/amhw_zlg116_rcc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg116_dma
 * \copydoc am_hwconf_zlg116_dma.c
 * @{
 */

/**
 * \brief DMA 平台初始化。
 */
void __zlg116_plfm_dma_init (void)
{

    /* 时能DMA相关模块时钟或电源 */
    am_clk_enable(CLK_DMA);
}

/**
 * \brief EDMA 平台去初始化。
 */
void __zlg116_plfm_dma_deinit (void)
{

    /* 时能DMA相关模块时钟或电源 */
    am_clk_disable(CLK_DMA);
}

/** \brief DMA 设备信息 */
static const am_zlg_dma_devinfo_t __g_dma_devinfo = {
    ZLG116_DMA_BASE,         /**< \brief 指向DMA寄存器块的指针 */
    INUM_DMA1_1,             /**< \brief DMA中断向量号开始 */
    INUM_DMA1_4_5,           /**< \brief DMA中断向量号结束 */
    __zlg116_plfm_dma_init,  /**< \brief DMA平台初始化 */
    __zlg116_plfm_dma_deinit /**< \brief DMA平台解初始化 */
};

/** \brief DMA设备实例 */
static am_zlg_dma_dev_t __g_dma_dev;

/**
 * \brief DMA 实例初始化
 * \return 无
 */
int am_zlg116_dma_inst_init (void)
{
    return am_zlg_dma_init(&__g_dma_dev, &__g_dma_devinfo);
}

/**
 * \brief DMA 实例解初始化
 * \return 无
 */
void am_zlg116_dma_inst_deinit (void)
{
    am_zlg_dma_deinit();
}

/**
 * @}
 */

/* end of file */
