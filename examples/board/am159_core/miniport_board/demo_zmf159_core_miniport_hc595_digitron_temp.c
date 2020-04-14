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
 * \brief MiniPort-View + MiniPort-595 温度显示（使用底板LM75BD读取温度） 
 *        例程，通过标准接口实现
 *
 * - 操作步骤
 *   1. 要使用底板（AM217BLE）上的 LM75 温度传感器，需要短接 J11 和 J13；
 *   2. 先将 MiniPort-595 板子直接与 AM217BLE 的 MiniPort 相连接；
 *   3. 将 MiniPort-View 板子与 MiniPort-595 接口相连接。
 *
 * - 实验现象：
 *   1. 可以看到数码管显示当前温度，若J14跳冒选择短接 KEY 和 RES，则按下底板上的
 *      KEY/RES 按键功率电阻会发热，导致温度传感器采集到的温度升高。
 *
 * \par 源代码
 * \snippet demo_miniport_hc595_digitron_temp.c src_miniport_hc595_digitron_temp
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_hc595_digitron_temp
 * \copydoc demo_miniport_hc595_digitron_temp.c
 */

/** [src_miniport_hc595_digitron_temp] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_temp_lm75.h"
#include "am_zmf159_inst_init.h"
#include "demo_std_entries.h"
#include "demo_zmf159_core_entries.h"
#include "am_hwconf_miniport.h"

/**
 * \brief 例程入口 
 */
void demo_zmf159_core_miniport_hc595_digitron_temp_entry (void)
{
    AM_DBG_INFO("demo zmf159_core miniport hc595 digitron temp!\r\n");

    am_miniport_view_595_inst_init();

    demo_std_digitron_temp_entry(0, am_temp_lm75_inst_init());
}
/** [src_miniport_hc595_digitron_temp] */

/* end of file */
