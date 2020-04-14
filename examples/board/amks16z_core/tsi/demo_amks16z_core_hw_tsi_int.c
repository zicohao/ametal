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
 * \brief   TSI触摸中断检测，硬件层实现
 *
 *  实验现象：
 *  1.当手不接触PIOA_1引脚时，输出检测到的基本值
 *  2.当触摸PIOA_1引脚后，电容检测大于阀值上限1000时，进入中断，LED1状态翻转
 *
 *  注意：
 *  1.运行该例程时PIOA_1不能配置成串口引脚。
 *
 * \par 源代码
 * \snippet demo_amks16z_core_hw_tsi_int.c src_amks16z_core_hw_tsi_int
 *
 * \internal
 * \par Modification History
 * - 1.00 15-10-26  xjc, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_hw_tsi_int
 * \copydoc demo_amks16z_core_hw_tsi_int.c
 */
 
/** [src_amks16z_core_hw_tsi_int] */
#include "ametal.h"
#include "hw/amhw_kl26_sim.h"
#include "hw/amhw_fsl_tsi.h"
#include "am_int.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_led.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"
#include "demo_amks16z_core_all_entries.h"

/**
 * \brief 主函数入口
 */
void demo_amks16z_core_hw_tsi_int_entry(void)
{  
    AM_DBG_INFO("demo amks16z_core hw tsi int!\r\n");

    /* 使能tsi相关外设时钟 */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_TSI);

    /* 配置PIOA_1引脚为TSI0_CH2 */
    am_gpio_pin_cfg(PIOA_1, PIOA_1_TSI0_CH2);

    demo_fsl_hw_tsi_int_entry(KL26_TSI, INUM_TSI0);

}

/** [src_amks16z_core_hw_tsi_int] */
 
/* end of file */

