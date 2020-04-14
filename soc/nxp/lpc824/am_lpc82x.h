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
 * \brief LPC82X 芯片特性相关头文件定义
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-07  cyl, first implementation.
 * \endinternal
 */
 
#ifndef __AM_LPC82X_H
#define __AM_LPC82X_H

#ifdef __cplusplus
extern "C" {    
#endif
    

/** \brief 芯片引脚定义 */ 
#include "lpc82x_pin.h"    
    
/** \brief 芯片中断编号定义 */    
#include "lpc82x_inum.h"

/** \brief 芯片外设寄存器基址定义 */
#include "lpc82x_regbase.h"

/** \brief 芯片外设映射 */
#include "lpc82x_periph_map.h"

/** \brief 时钟ID定义 */
#include "lpc82x_clk.h"

/** \brief DMA通道及参数定义 */
#include "lpc82x_dma_chan.h"


/**
 * \name Cortex-M0+ 内核处理器和外设设置
 * @{
 */
#ifndef AM_CORTEX_M0

#define AM_CORTEX_M0             1

#endif

#if defined AM_CORTEX_M0

#define __MPU_PRESENT            0  /**< \brief M0+核无MPU              */
#define __NVIC_PRIO_BITS         2  /**< \brief M0+核为2                */
#define __Vendor_SysTickConfig   0  /**< \brief 设置为1 可以配置SysTick  */

#include "core_cm0plus.h"

#endif

/** @} */
    
#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC82X_H */

/* end of file */
