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
 * \brief zsn60x B类卡测试程序
 *
 * - 操作步骤：
 *   1. 正确连接并配置好串口；
 *   2. 将B类卡放置于天线感应区。
 *
 * - 实验现象：
 *   1. MCU将会打印出B类卡的相关信息
 *
 * \par 源代码
 * \snippet demo_am116_zsn60x_piccb_test.c src_am116_zsn60x_piccb_test
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-18  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_am116_if_zsn60x_piccb_test
 * \copydoc demo_am116_zsn60x_piccb_test.c
 */

/** [src_am116_zsn60x_piccb_test] */

#include "zsn60x.h"
#include "demo_components_entries.h"
#include "demo_am116_core_entries.h"
#include "am_hwconf_zsn60x_uart.h"

void demo_am116_zsn60x_piccb_test_entry()
{
    zsn60x_handle_t  handle = am_zsn60x_uart_inst_init();
    demo_zsn60x_piccb_active_test_entry(handle);
}
/** [src_am116_zsn60x_piccb_test] */

/* end of file */
