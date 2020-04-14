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
 * \brief ADC 例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. PIOA_4 (ADC 通道 4) 连接模拟输入。
 *
 * - 实验现象：
 *   1. 串口输出电压采样值。
 *
 * \note
 *    1. 使用 ADC 模块功能，必须保证 ADC 模块上电；
 *    2. 如需观察串口打印的调试信息，需要将 PIOA_10 引脚连接 PC 串口的 TXD，
 *       PIOA_9 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_zlg217_std_adc.c src_std_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-29  fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg217_std_adc
 * \copydoc demo_zlg217_std_adc.c
 */

/** [src_std_adc] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_zlg217_inst_init.h"
#include "demo_std_entries.h"
#include "demo_am217_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_zlg217_core_std_adc_entry (void)
{
    AM_DBG_INFO("demo am217_core std adc int!\r\n");

    demo_std_adc_entry(am_zlg217_adc1_inst_init(), 4);

}
/** [src_std_adc] */

/* end of file */
