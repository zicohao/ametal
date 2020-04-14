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
 * \brief MiniPort-ZLG72128 配置文件
 * \sa am_hwconf_miniport_zlg72128.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg116_inst_init.h"
#include "am_zlg72128_std.h"
#include "zlg116_pin.h"
#include "am_input.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_zlg72128
 * \copydoc am_hwconf_miniport_zlg72128.c
 * @{
 */

/*******************************************************************************
    Local global variables
*******************************************************************************/

static const int __g_key_codes[]    = {
    KEY_0, KEY_1,
    KEY_2, KEY_3
};

static am_zlg72128_std_dev_t           __g_miniport_zlg72128;
static const am_zlg72128_std_devinfo_t __g_miniport_zlg72128_info = {
    {
        {
            0x30,
            PIOB_5,                     /* 复位引脚 todo */
            AM_FALSE,                   /* 使用中断引脚 */
            PIOB_3,                     /* 中断引脚 todo */
            5,                          /* 查询时间间隔，使用中断引脚时，该值无意义 */
            am_zlg116_i2c1_inst_init,   /* I2C句柄获取函数*/
            am_zlg116_i2c1_inst_deinit  /* I2C解初始化函数*/
        }
    },
    {
        0                           /* 数码管显示器的编号 */
    },
    500,                            /* 一个闪烁周期内，点亮的时间为500ms */
    500,                            /* 一个闪烁周期内，熄灭的时间为500ms */
    AM_ZLG72128_STD_KEY_ROW_0 | AM_ZLG72128_STD_KEY_ROW_3,
    AM_ZLG72128_STD_KEY_COL_0 | AM_ZLG72128_STD_KEY_COL_1,
    __g_key_codes,                  /* 按键编码， KEY_0 ~ KEY3 */
    2                               /* 数码管个数为2 */
};

/*******************************************************************************
    Public functions
*******************************************************************************/

/* MiniPort-ZLG72128 实例初始化 */
int am_miniport_zlg72128_inst_init (void)
{
    return  am_zlg72128_std_init(&__g_miniport_zlg72128,
                                 &__g_miniport_zlg72128_info);
}

/**
 * @}
 */

/* end of file */
