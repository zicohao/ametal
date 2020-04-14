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
 * \brief zsn60x LED测试程序
 *
 * - 操作步骤：
 *   1. 正确连接并配置好串口；
 *
 * - 实验现象：
 *   1. ZSN600的LED灯将会闪烁，若执行错误则会打印响应的错误标识号 ；
 *
 * \par 源代码
 * \snippet demo_zsn60x_led_test.c src_zsn60x_led_test
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-18  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn60x_led_test
 * \copydoc demo_zsn60x_led_test.c
 */

/** [src_zsn60x_led_test] */
#include "zsn60x.h"
#include "ametal.h"
#include "am_vdebug.h"
/* ZSN60x  LED测试程序 */
void demo_zsn60x_led_test_entry (zsn60x_handle_t handle)
{
    unsigned char ret = 0;
    ret = zsn60x_control_led (handle,  ZSN60X_CONTROL_LED_ON);
    if(ret == 0){
        am_kprintf("led on !\r\n");
    }else{
        am_kprintf("led control beacuse error 0x%02x", ret);
    }
    ret = zsn60x_control_led (handle,  ZSN60X_CONTROL_LED_OFF);
    if(ret == 0){
        am_kprintf("led off !\r\n");
    }else{
        am_kprintf("led control beacuse error 0x%02x", ret);
    }
}
/** [src_zsn60x_led_test] */

/* end of file */
