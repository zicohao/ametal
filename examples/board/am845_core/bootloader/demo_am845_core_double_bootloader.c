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
 * \brief bootloader 双区例程
 *
 *
  * - 操作步骤（本地升级）：
 *
 *   1. 连接开发板和上位机串口助手，波特率设置为9600。（例程使用串口1）
 *   
 *   2. 给开发板下载本工程编译的程序，复位程序运行。
 *
 *   3. 串口助手打印5秒倒计时，在5秒内通过串口助手发送任意数据给开发板，开发板准备接收固件。
 *
 *   4. 将处理好的固件通过串口助手发送给开发板（如果在发送的过程出错，将重新接收固件，上位机重新发送）。
 *
 *   5. 接收成功，程序跳转到应用程序执行，串口打印出应用程序信息，LED灯闪烁。
 *
 * - 操作步骤（应用中升级）：
 *
 *   应用中升级的前提条件是已经通过本地升级的方式将双区应用程序固件下载到了开发板中，并成功运行。
 *
 *   1. 发送升级命令：0x5a 0xa6 0x11 0x66 0x0d（命令是以16进制的形式发送，注意设置串口助手）
 *   
 *   2. 等待串口助手打印已经准备接收固件信息后，发送固件。
 *
 *   3. 固件发送成功，开发板重启，5秒延时后进去新的应用程序（延时时间内不要发送任何数据）。
 *
 *
 *
 * \note
 *    固件处理：
 *
 *    打开在ametal/tools/bootloader/固件校验/ 文件夹，目录下有一个bin_chek_sum.bin的执行文件，
 *    将测试的应用工程编译出的bin文件拷贝到和bin_chek_sum.bin同一个目录下，
 *    在该目录下打开cmd，在命令行中依次输入：
 *         bin_chek_sum.bin  xxx.bin（编译后的bin文件名称） xxx.bin（目标输出文件，名字任意取）
 *
 *    执行命令后会生成一个由用户自己取名的目标输出文件，这个文件就是需要发送的固件。
 *
 *
 * \par 源代码
 * \snippet demo_am845_core_double_bootloader.c src_am845_core_double_bootloader
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-09  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_double_bootloader
 * \copydoc demo_am845_core_double_bootloader.c
 */

/** [src_am845_core_double_bootloader] */
#include "am_bootconf_double_lpc84x.h"
#include "am_uart.h"
#include "am_vdebug.h"
#include "am_boot_firmware.h"
#include "am_boot_flash.h"
#include "demo_boot_entries.h"
#include "am_lpc84x_inst_init.h"
#include "am_boot_enter_check_uart.h"
#include "am_boot_firmware_recv_uart.h"

void demo_am845_core_double_bootloader_uart_entry (void)
{
    am_uart_handle_t           uart_handle;
    am_boot_firmware_handle_t  firmware_handle;


    /* bootloader 标准接口初始化  */
    am_lpc84x_boot_inst_init();

    firmware_handle = am_lpc84x_boot_firmware_flash_inst_init();

    uart_handle = am_lpc84x_usart0_inst_init();
    am_debug_init(uart_handle, 9600);
    //check_handle = am_boot_enter_check_key_init(PIOC_7, AM_GPIO_INPUT | AM_GPIO_PULLUP);

    demo_std_double_bootloader_entry(
        am_boot_firwa_recv_uart_init(firmware_handle, uart_handle),
        am_boot_enter_check_uart_init(uart_handle),
        am_lpc84x_boot_msg_flag_inst_init());
}
/** [src_am845_core_double_bootloader] */

/* end of file */
