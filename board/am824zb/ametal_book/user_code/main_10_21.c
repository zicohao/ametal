/******************************************************************************
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
 * \brief 程序清单10.21
 *
 * \note 该历程需要用到miniport拓展板
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_zm516x.h"
#include "am_vdebug.h"
#include "am_lpc82x_inst_init.h"
int am_main (void)
{
    uint8_t                   buf[20];
    am_zm516x_cfg_info_t    zm516x_cfg_info;
    am_zm516x_handle_t      zm516x_handle = am_zm516x_inst_init();

    // 获取ZM516X模块的配置信息
    if (am_zm516x_cfg_info_get(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
        return AM_ERROR;
    }
    // 修改ZM516X模块的配置信息，本地地址： 0x2002，目标地址：0x2001
    zm516x_cfg_info.my_addr[0]  = 0x20;
    zm516x_cfg_info.my_addr[1]  = 0x02;
    zm516x_cfg_info.dst_addr[0] = 0x20;
    zm516x_cfg_info.dst_addr[1] = 0x01;
    if (am_zm516x_cfg_info_set(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
        return AM_ERROR;
    }
    // 使ZM516X模块复位，以使设置生效
    am_zm516x_reset(zm516x_handle);
    am_mdelay(10);
    while (1) {
        int ret = am_zm516x_receive(zm516x_handle, buf, 100);
        if (ret > 0) {
            buf[ret] = '\0';                   // 末尾添加结束符
            am_kprintf("%s", buf);
        }
    }
}

/* end of file */
