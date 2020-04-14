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
 * \brief bootloader 单区例程。
 *
 * - 操作步骤（本地升级）：
 *   1. eclipse工程打开demo_am217_core_bootloader.ld文件，打开:
 *
 *       FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 28K   // single
 *
 *      的配置, 屏蔽其他flash配置。
 *
 *      keil工程打开demo_am217_core_bootloader.sct文件，打开单区的配置，屏蔽其他配置
 *
 *   2. 连接开发板和上位机串口助手，波特率设置为115200。（例程使用串口1）
 *   
 *   3. 给开发板下载本工程编译的程序，复位开发板运行。
 *
 *   4. 串口助手打印5秒倒计时，在5秒内通过串口助手发送任意数据给开发板，开发板准备接收固件。
 *
 *   5. 将处理好的固件通过串口助手发送给开发板（如果在发送的过程出错，将重新接收固件，上位机重新发送）。
 *
 *   6. 接收成功，程序跳转到应用程序执行，串口打印出应用程序信息，LED灯闪烁。
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
 * \internal
 * \par Modification History
 * - 1.00 19-6-06  yrh, first implementation
 * \endinternal
 */


#include "am_uart.h"
#include "am_vdebug.h"
#include "am_boot_firmware.h"
#include "am_boot_flash.h"
#include "am_bootconf_zlg217.h"
#include "am_zlg217_inst_init.h"
#include "am_boot_enter_check_uart.h"
#include "am_boot_firmware_recv_uart.h"
#include "demo_boot_entries.h"

void demo_zlg217_core_single_bootloader_uart_entry (void)
{
    am_uart_handle_t           uart_handle;
    am_boot_firmware_handle_t  firmware_handle;

    /* bootloader 标准接口初始化  */
    am_zlg217_boot_single_inst_init();

    firmware_handle = am_zlg217_boot_single_firmware_flash_inst_init();

    uart_handle = am_zlg217_uart1_inst_init();
    am_debug_init(uart_handle, 115200);

    //check_handle = am_boot_enter_check_key_init(PIOC_7, AM_GPIO_INPUT | AM_GPIO_PULLUP);

    demo_std_single_bootloader_entry(
        am_boot_firwa_recv_uart_init(firmware_handle, uart_handle),
        am_boot_enter_check_uart_init(uart_handle));
}

/* end of file */
