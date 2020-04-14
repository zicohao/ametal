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
 * \brief MiniPort-LED 例程，通过标准接口实现
 *
 * - 操作步骤
 *   1. 将 MiniPort-LED 板子直接与 aml166-Core 的 MiniPort接口相连接。
 *
 * - 实验现象：
 *   1. 流水灯现象。
 *
 * - 注意：
 *   1. 要使用该例程，需要在 am_prj_config.h 里面将 AM_CFG_LED_ENABLE 定义为 0。
 *
 * \par 源代码
 * \snippet demo_aml166_core_miniport_led.c src_aml166_core_miniport_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml166_core_miniport_led
 * \copydoc demo_aml166_core_miniport_led.c
 */

/** [src_aml166_core_miniport_led] */
#include <am_aml166_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_aml166_core_miniport_led_entry (void)
{
    AM_DBG_INFO("demo aml166_core miniport led!\r\n");

    am_miniport_led_inst_init();

    demo_std_led_water_light_entry (2, 8);
}
/** [src_aml166_core_miniport_led] */

/* end of file */
