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
 * \brief LM75 配置文件
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */
#ifndef __AM_HWCONF_LM75_H
#define __AM_HWCONF_LM75_H

#include "ametal.h"
#include "am_temp.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief LM75实例初始化
 * \return 温度标准服务句柄，若为NULL，表明初始化失败
 */
am_temp_handle_t am_temp_lm75_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif
