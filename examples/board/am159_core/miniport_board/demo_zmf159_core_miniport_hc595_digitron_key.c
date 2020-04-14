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
 * \brief MiniPort-View + MiniPort-595 + MiniPort-KEY 例程，通过标准接口实现
 *
 * - 操作步骤
 *   1. 先将 MiniPort-595 板子直接与 AM217BLE 的 MiniPort 相连接；
 *   2. 将 MiniPort-View 板子与 MiniPort-595 接口相连接；
 *   3. 将 MiniPort-KEY 与 MiniPort-View 连接。
 *
 * - 实验现象：
 *   1. 按下一个按键，两位数码管显示按键编号的二进制；
 *   2. 偶数编号时，数码管闪烁，奇数编号时，数码管不闪烁。
 *
 * \note
 *    测试本 Demo 必须在 am_prj_config.h 内将 AM_CFG_KEY_GPIO_ENABLE、
 *    AM_CFG_KEY_ENABLE 和 AM_CFG_SOFTIMER_ENABLE 定义为 1。但这些宏
 *    已经默认配置为 1， 用户不必再次配置。
 *
 * \par 源代码
 * \snippet demo_miniport_hc595_digitron_key.c src_miniport_hc595_digitron_key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_miniport_hc595_digitron_key
 * \copydoc demo_miniport_hc595_digitron_key.c
 */

/** [src_miniport_hc595_digitron_key] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_event_input_key.h"
#include "am_zmf159_inst_init.h"
#include "demo_std_entries.h"
#include "demo_zmf159_core_entries.h"
#include "am_hwconf_miniport.h"

/**
 * \brief 例程入口
 */
void demo_zmf159_core_miniport_hc595_digitron_key_entry (void)
{
    AM_DBG_INFO("demo zmf159_core miniport hc595 digitron key!\r\n");

    am_miniport_view_key_595_inst_init();

    demo_std_key_digitron_entry(0);
}
/** [src_miniport_hc595_digitron_key] */

/* end of file */
