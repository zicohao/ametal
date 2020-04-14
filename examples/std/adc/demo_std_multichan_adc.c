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
 * \brief ADC例程，利用查询方式获取ADC多个通道转换结果，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 将指定ADC通道对应的引脚连接模拟输入。
 *
 * - 实验现象：
 *   1. 串口输出电压采样值。
 *
 * \par 源代码
 * \snippet demo_std_multichan_adc.c src_std_multichan_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 19-02-28  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_multichan_adc
 * \copydoc demo_std_multichan_adc.c
 */

/** [src_std_multichan_adc] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_adc.h"

/**
 * \brief 获取 ADC 转换值
 */
static uint32_t __adc_code_get (am_adc_handle_t handle, int chan)
{
    int      adc_bits = am_adc_bits_get(handle, chan);
    int      i;
    uint32_t sum;

    /*
     * 启动ADC转换器，采集12次 CODE 值
     *
     * 实际应用中，所使用的 ADC 位数是确定的，无需这样分多种情况考虑
     */
    if (adc_bits <= 8) {
        uint8_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* 均值处理 */
            sum += val_buf[i];
        }
    } else if (adc_bits <= 16) {
        uint16_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* 均值处理 */
            sum += val_buf[i];
        }
    } else {
        uint32_t val_buf[12];
        am_adc_read(handle, chan, val_buf, 12);
        for (sum = 0, i = 0; i < 12; i++) {       /* 均值处理 */
            sum += val_buf[i];
        }
    }
    return (sum / 12);
}

/**
 * \brief 例程入口
 */
void demo_std_multichan_adc_entry (am_adc_handle_t handle, int *p_chan, int chan_num)
{
    if (p_chan == NULL || chan_num <= 0) {
        return;
    }

    int adc_bits = am_adc_bits_get(handle , p_chan[0]);        /* 获取ADC转换精度 */
    int adc_vref = am_adc_vref_get(handle , p_chan[0]);

    uint32_t i = 0;
    uint32_t adc_code;                                    /* 采样 Code 值   */
    uint32_t adc_mv;                                      /* 采样电压 */

    if (adc_bits < 0 || adc_bits >= 32) {
        am_kprintf("The ADC  channel is error, Please check! \r\n");
        return;
    }

    while (1) {

        if (i > chan_num - 1) {
            i = 0;
            am_kprintf("\r\n");
            am_mdelay(500);
        }

        adc_code = __adc_code_get(handle, p_chan[i]);
        adc_mv   = adc_code * adc_vref / ((1UL << adc_bits) - 1);

        /* 串口输出采样电压值 */
        am_kprintf("chan : %d, Sample : %d, Vol: %d mv\r\n", p_chan[i], adc_code, adc_mv);

        i++;
    }
}
/** [src_std_multichan_adc] */

/* end of file */
