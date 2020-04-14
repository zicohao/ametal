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
 * \brief IAP 例程，通过 HW 层接口实现
 *
 * - 实验现象：
 *   1. 输出 UID, PID, Boot 代码版本号和签名；
 *   2. 拷贝 RAM 到 FLASH，输出相关页数据；
 *   3. 如果蜂鸣器响，说明 IAP 指令在执行产生错误。
 *
 *       在扇区和指定扇区号可进行 IAP 和 ISP 指令操作。另外，可进行页擦除。扇区大小
 *       为 1KB，页大小为 64 字节，一个扇区包含 16 页，扇区 0 和页 0 位于 0x0000 0000
 *       地址。16KB flash 仅包含扇区 0-15，32KB flash 包含扇区 0-31.
 *
 *       扇区编号       |    扇区大小[kB]      |    页编号      |         地址范围
 *    ------------- | ---------------- | ----------- | -------------------------
 *           0      |        1         |    0 -  15  | 0x0000 0000 - 0x0000 03ff
 *           1      |        1         |   16 -  31  | 0x0000 0400 - 0x0000 07ff
 *           2      |        1         |   32 -  47  | 0x0000 0800 - 0x0000 0bff
 *           3      |        1         |   48 -  63  | 0x0000 0c00 - 0x0000 0fff
 *           4      |        1         |   64 -  79  | 0x0000 1000 - 0x0000 13ff
 *           5      |        1         |   80 -  95  | 0x0000 1400 - 0x0000 17ff
 *           6      |        1         |   96 - 111  | 0x0000 1800 - 0x0000 1bff
 *           7      |        1         |  112 - 127  | 0x0000 1c00 - 0x0000 1fff
 *           8      |        1         |  128 - 143  | 0x0000 2000 - 0x0000 23ff
 *           9      |        1         |  144 - 159  | 0x0000 2400 - 0x0000 27ff
 *          10      |        1         |  160 - 175  | 0x0000 2800 - 0x0000 2bff
 *          11      |        1         |  176 - 191  | 0x0000 2c00 - 0x0000 2fff
 *          12      |        1         |  192 - 207  | 0x0000 3000 - 0x0000 33ff
 *          13      |        1         |  208 - 223  | 0x0000 3400 - 0x0000 37ff
 *          14      |        1         |  224 - 239  | 0x0000 3800 - 0x0000 3bff
 *          15      |        1         |  240 - 255  | 0x0000 3c00 - 0x0000 3fff
 *          16      |        1         |  256 - 271  | 0x0000 4000 - 0x0000 43ff
 *          17      |        1         |  272 - 287  | 0x0000 4400 - 0x0000 47ff
 *          18      |        1         |  288 - 303  | 0x0000 4800 - 0x0000 4bff
 *          19      |        1         |  304 - 319  | 0x0000 4c00 - 0x0000 4fff
 *          20      |        1         |  320 - 335  | 0x0000 5000 - 0x0000 53ff
 *          21      |        1         |  336 - 351  | 0x0000 5400 - 0x0000 57ff
 *          22      |        1         |  352 - 367  | 0x0000 5800 - 0x0000 5bff
 *          23      |        1         |  368 - 383  | 0x0000 5c00 - 0x0000 5fff
 *          24      |        1         |  384 - 399  | 0x0000 6000 - 0x0000 63ff
 *          25      |        1         |  400 - 415  | 0x0000 6400 - 0x0000 67ff
 *          26      |        1         |  416 - 431  | 0x0000 6800 - 0x0000 6bff
 *          27      |        1         |  432 - 447  | 0x0000 6c00 - 0x0000 6fff
 *          28      |        1         |  448 - 463  | 0x0000 7000 - 0x0000 73ff
 *          29      |        1         |  464 - 479  | 0x0000 7400 - 0x0000 77ff
 *          30      |        1         |  480 - 495  | 0x0000 7800 - 0x0000 7bff
 *          31      |        1         |  496 - 511  | 0x0000 7c00 - 0x0000 7fff
 *
 * \note
 *    1. LED0 需要短接 J9 跳线帽，才能被 PIO0_20 控制；
 *    2. 蜂鸣器需要短接 J7 跳线帽，才能被 PIO0_24 控制。而且必须在 am_prj_config.h
 *       内将 AM_CFG_BUZZER_ENABLE 定义为 1。但该宏已经默认配置为 1， 用户不必再次
 *       配置；
 *    3. 如需观察串口打印的调试信息，需要将 PIO0_0 引脚连接 PC 串口的 TXD，
 *       PIO0_4 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_am824_hw_iap.c src_am824_hw_iap
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-12  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_hw_iap
 * \copydoc demo_am824_hw_iap.c
 */

/** [src_am824_hw_iap] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_nxp_entries.h"

/**
 * \brief 例程入口
 */
void demo_am824_core_hw_iap_entry (void)
{
    am_kprintf("demo am824 hw iap!\r\n");
    demo_lpc824_hw_iap_entry();
}
/** [src_am824_hw_iap] */

/* end of file */
