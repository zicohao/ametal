/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LED 配置文件（GPIO直接驱动）
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  tee, first implementation.
 * \endinternal
 */
#ifndef __AM_HWCONF_LED_GPIO_H
#define __AM_HWCONF_LED_GPIO_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief LED 实例初始化（GPIO直接驱动）
 *
 * \retval  AW_OK  初始化成功
 * \retval   < 0   初始化失败，请检查C文件中各配置项是否合法
 */
int am_led_gpio_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
