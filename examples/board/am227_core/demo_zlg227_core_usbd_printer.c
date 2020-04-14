/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB printer_counter 例程
 *
 * - 实验现象：
 * 1.将USB的另端点接入PC机。
 * 2.给板子烧录该例程，等待3秒(程序中有3秒延时，为了模拟USB拔出过程)，3秒后pc机会提示安装驱动，
 *   这里默认安装windows 通用打印机驱动，详细可看驱动安装说明文档，如果用户想要用自己的驱动，可以自行更新。
 * 3.在电脑桌面新建一个txt文件，输入字符串,之后点击文件打印，即在串口中可以看到文件内容.
 *
 * \par 源代码
 * \snippet demo_zlg227_core_usbd_printer.c src_zlg227_core_usbd_printer
 *
 * \internal
 * \par Modification History
 * - 1.00 19-05-28  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_demo_zlg227_core_usbd_printer
 * \copydoc demo_zlg227_core_usbd_printer.c
 */

/** [src_demo_zlg227_core_usbd_printer] */

#include "demo_zlg_entries.h"
#include "am_zlg217_inst_init.h"
#include "demo_am217_core_entries.h"

void demo_zlg227_usbd_printer_entry (void)
{

    AM_DBG_INFO("demo zlg227_core usbd printer!\r\n");

    /* usb打印机实例初始化*/
    am_usbd_printer_handle handle = am_zlg227_usbd_printer_inst_init();

    demo_usbd_printer_entry(handle);
}

/** [src_demo_zlg227_core_usbd_printer] */

/* end of file */
