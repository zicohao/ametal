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
 * \brief RTC 例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. 串口打印出设置的时间，以后每秒打印一次时间。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIOA_10 引脚连接 PC 串口的 TXD，
 *    PIOA_9 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_zmf159_std_rtc.c src_zmf159_std_rtc
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-30  lqy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_std_rtc
 * \copydoc demo_zmf159_std_rtc.c
 */

/** [src_zmf159_std_rtc] */

#include <demo_zmf159_core_entries.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_zmf159_inst_init.h"

/**
 * \brief 例程入口
 */
void demo_zmf159_core_std_rtc_entry (void)
{
    AM_DBG_INFO("demo am159_core rtc entry!\r\n");

    demo_std_rtc_entry(am_zmf159_rtc_inst_init());
}
/** [src_zmf159_std_rtc] */

/* end of file */
