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
 * \brief ³ÌÐòÇåµ¥ 9.52
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  ipk, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "am_hwconf_key_gpio.h"
#include "app_led_control.h"

int am_main (void)
{
    am_zm516x_handle_t zm516x_handle = am_zm516x_inst_init();
    am_key_gpio_inst_init();
	  app_led_control(zm516x_handle, 0x2001, 0x2002);
	  while (1) {
	  }
}

/* end of file */
