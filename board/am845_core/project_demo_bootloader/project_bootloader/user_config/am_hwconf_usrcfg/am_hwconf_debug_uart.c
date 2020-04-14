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
 * \brief 调试串口用户配置文件
 * \sa am_hwconf_debug_uart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-20  pea, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_uart.h"
#include "am_vdebug.h"
#include "am_lpc84x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_debug_uart
 * \copydoc am_hwconf_debug_uart.c
 * @{
 */

/** \brief 使用的调试串口 0: UART0  1: UART1  2: UART2 */
#define __DEBUG_UART            0

/** \brief 配置调试串口输出的波特率 */
#define __DEBUG_BAUDRATE        115200

/**
 * \brief 调试串口实例初始化
 */
am_uart_handle_t am_debug_uart_inst_init (void)
{
    am_uart_handle_t handle = NULL;

#if (__DEBUG_UART == 0)
    handle = am_lpc84x_usart0_inst_init();   /* 串口初始化 */
    am_debug_init(handle, __DEBUG_BAUDRATE); /* 调试初始化 */
#elif (__DEBUG_UART == 1)
    handle = am_lpc84x_usart1_inst_init();   /* 串口初始化 */
    am_debug_init(handle, __DEBUG_BAUDRATE); /* 调试初始化 */
#elif (__DEBUG_UART == 2)
    handle = am_lpc84x_usart2_inst_init();   /* 串口初始化 */
    am_debug_init(handle, __DEBUG_BAUDRATE); /* 调试初始化 */
#elif (__DEBUG_UART == 3)
    handle = am_lpc84x_usart3_inst_init();   /* 串口初始化 */
    am_debug_init(handle, __DEBUG_BAUDRATE); /* 调试初始化 */
#elif (__DEBUG_UART == 4)
    handle = am_lpc84x_usart4_inst_init();   /* 串口初始化 */
    am_debug_init(handle, __DEBUG_BAUDRATE); /* 调试初始化 */
#endif
    return handle;
}

/**
 * @}
 */

/* end of file */
