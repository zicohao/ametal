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
 * \brief MX25XX 例程
 *
 * - 实验现象：
 *   1. 串口打印出测试结果。
 *
 * \par 源代码
 * \snippet demo_mx25xx.c src_mx25xx
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_mx25xx
 * \copydoc demo_mx25xx.c
 */

/** [src_mx25xx] */
#include "ametal.h"
#include "am_delay.h"
#include "am_mx25xx.h"
#include "am_vdebug.h"

#define __BUF_SIZE 16 /**< \brief 缓冲区大小 */

/**
 * \brief 例程入口
 */
void demo_mx25xx_entry (am_mx25xx_handle_t mx25xx_handle, int32_t test_lenth)
{
    int     ret;
    uint8_t i;
    uint8_t wr_buf[__BUF_SIZE] = {0}; /* 写数据缓存定义 */
    uint8_t rd_buf[__BUF_SIZE] = {0}; /* 读数据缓存定义 */

    if (__BUF_SIZE < test_lenth) {
        test_lenth = __BUF_SIZE;
    }

    /* 填充发送缓冲区 */
    for (i = 0;i < test_lenth; i++) {
        wr_buf[i] = i;
    }

    /* 擦除扇区 */
    am_mx25xx_erase(mx25xx_handle, 0x001000, test_lenth);

    /* 写数据 */
    ret = am_mx25xx_write(mx25xx_handle, 0x001000, &wr_buf[0], test_lenth);

    if (ret != AM_OK) {
        AM_DBG_INFO("am_mx25xx_write error(id: %d).\r\n", ret);
        return;
    }
    am_mdelay(5);

    /* 读数据 */
    ret = am_mx25xx_read(mx25xx_handle, 0x001000, &rd_buf[0], test_lenth);

    if (ret != AM_OK) {
        AM_DBG_INFO("am_mx25xx_read error(id: %d).\r\n", ret);
        return;
    }

    /* 校验写入和读取的数据是否一致 */
    for (i = 0; i < test_lenth; i++) {
        AM_DBG_INFO("Read FLASH the %2dth data is %2x\r\n", i ,rd_buf[i]);

        /* 校验失败 */
        if(wr_buf[i] != rd_buf[i]) {
            AM_DBG_INFO("verify failed at index %d.\r\n", i);
            break;
        }
    }

    if (test_lenth == i) {
        AM_DBG_INFO("verify success!\r\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_mx25xx] */

/* end of file */
