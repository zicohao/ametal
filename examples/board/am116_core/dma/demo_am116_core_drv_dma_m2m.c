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
 * \brief DMA 内存到内存例程，通过驱动层接口实现
 *
 * - 实验现象：
 *   1. DMA 传输成功，打印 "transfer success";
 *   2. DMA 传输出错，打印 "transfer failure";
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIOA_9 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_am116_core_drv_dma_m2m.c src_am116_core_drv_dma_m2m
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-11 ari , first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am116_core_drv_dma_m2m
 * \copydoc demo_am116_core_drv_dma_m2m.c
 */

/** [src_am116_core_drv_dma_m2m] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg116.h"
#include "demo_zlg_entries.h"
#include "demo_am116_core_entries.h"

#define DMA_M2M_CH DMA_CHAN_1 /**< \brief DMA 通道号 */

/**
 * \brief 例程入口
 */
void demo_am116_core_drv_dma_m2m_entry (void)
{
    AM_DBG_INFO("demo am116_core drv dma m2m!\r\n");

    demo_zlg_drv_dma_m2m_entry(DMA_M2M_CH);
}
/** [src_am116_core_drv_dma_m2m] */

/* end of file */
