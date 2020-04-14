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
 * \brief
 *
 * - 实验现象：
 *   1. 连接好串口，将PT100电阻接入RTDC与RTDB之间，并短接RTDA。
 *   2. 串口将会打印出PT100测量温度值
 *
 * \par 源代码
 * \snippet demo_aml166_core_adc24_pt100_measure.c src_aml166_core_adc24_pt100_measure
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-17  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_aml166_core_adc24_pt100_measure
 * \copydoc demo_aml166_core_adc24_pt100_measure.c
 */

/** [src_aml166_core_adc24_pt100_measure] */

#include "string.h"
#include "am_zml166_adc.h"
#include "am_zlg_flash.h"
#include "zlg116_periph_map.h"
#include "demo_components_entries.h"
#include "demo_aml166_core_entries.h"
#include "am_aml166_inst_init.h"
#include "am_hwconf_zml166_adc.h"
#include "demo_zlg_entries.h"
/**
 * \brief ZML166 24位ADC  PT100测温例程
 */
void demo_aml166_core_zml166_adc_pt100_measure (void)
{
    float para[2];
    am_zml166_adc_handle_t  handle = am_zml166_adc_inst_init();
    /* 从flash中获取PT100电阻的修正系数 */
    am_zlg_flash_init(ZLG116_FLASH);
    memcpy((void *)para, (uint32_t *)PT100_PARA_SAVE_ADDRESS, 4 * 2);
    /* 若flash中未保存系数 */
    if(!(para[0] < 1.02 && para[0] > 0.98)){
        para[0] = 1;
    }
    if(!(para[1] < 0.15 && para[1] > -0.15)){
        para[1] = 0;
    }
    demo_zml166_adc_pt100_measure_entry((void *)handle, para);
}

/** [src_aml166_core_adc24_pt100_measure] */

/* end of file */
