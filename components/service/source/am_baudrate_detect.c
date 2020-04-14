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
 * \brief 实现自动波特率服务
 *
 *
 * \par 源代码
 * \snippet am_baudrate_detect.c src_am_baudrate_detect
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  ipk, first implementation
 * \endinternal
 */

/** [src_am_baudrate_detect] */

#include "am_baudrate_detect.h"
#include "ametal.h"
#include "am_vdebug.h"
#include "am_timer.h"
#include "am_gpio.h"
#include "am_int.h"
#include "string.h"
#include "am_softimer.h"

/*******************************************************************************
  宏定义
*******************************************************************************/

#define  __TIMER_OVERFLOW(count1, count2, width)  \
         (count2 < count1 ? (count2 + (1ul << width) - 1) : count2);

/*******************************************************************************
  静态函数
*******************************************************************************/

/**
 * \brief 捕获回调函数
 */
static void __cap_callback (void *p_arg, unsigned int cap_now_val)
{
#if 0
    handle->uart_data <<= 1;
    if (am_gpio_get(handle->cap_pin)) {
        handle->uart_data |= 0x01;
    }
#endif
    am_baudrate_detect_dev_t *p_dev = (am_baudrate_detect_dev_t *)p_arg;
    /* 只需要处理一个字节  */
    if (p_dev->data_edge <= 9) {
        p_dev->data_pulse_width[p_dev->data_edge++] = cap_now_val;
    }

    p_dev->cap_flag = AM_TRUE;
    p_dev->time_out_ms = 0;
}

/**
 * \brief 定时器回调函数
 */
static void __softimer_callback (void *p_arg)
{
    am_baudrate_detect_dev_t *p_dev = (am_baudrate_detect_dev_t *)p_arg;
    p_dev->time_out_ms++;

    if (p_dev->time_out_ms >= p_dev->p_devinfo->timer_out) {

        p_dev->data_pulses = p_dev->data_edge;

        p_dev->data_edge  = 0;
        p_dev->time_out_ms = 0;
    }
}

/**
 * \brief 获取波特率函数
 */
static int __baudrate_get (am_baudrate_detect_dev_t *p_dev,
                           uint32_t               *p_baudrate)
{
    int      key;
    uint16_t i;
    uint32_t tmp;
    uint32_t time_ns;
    uint32_t min_pulse_width = 1;

    key = am_int_cpu_lock();

    for (i = 0; i < p_dev->data_pulses - 1; i++) {


        tmp = __TIMER_OVERFLOW(p_dev->data_pulse_width[i],
                               p_dev->data_pulse_width[i + 1],
                               p_dev->p_devinfo->timer_width);

        am_cap_count_to_time(p_dev->cap_handle,
                             p_dev->p_devinfo->cap_chanel,
                             p_dev->data_pulse_width[i],
                             tmp,
                             (unsigned int *)&time_ns);

        p_dev->data_pulse_width[i] = time_ns;

        if (i == 0) {
            min_pulse_width = p_dev->data_pulse_width[0];
        } else {
            if (p_dev->data_pulse_width[i] < min_pulse_width) {
                min_pulse_width = p_dev->data_pulse_width[i];
            }
        }
    }

    for (i = 0; i < p_dev->data_pulses - 1; i++) {
        tmp = p_dev->data_pulse_width[i] * 10 / min_pulse_width;
        if ((tmp >= 14 ) && (tmp <= 16)) {
            min_pulse_width /= 2;
        }
    }

    /* 去掉一位停止位 */
    p_dev->uart_data  = p_dev->uart_data >> 1;

    //__data_analysis(handle, data_pulses - 1, min_pulse_width);
    am_int_cpu_unlock(key);

    memset(p_dev->data_pulse_width, 0, sizeof(p_dev->data_pulse_width));

    p_dev->uart_data = 0;

    /* 不支持的范围 */
    if (min_pulse_width < 2000 || min_pulse_width > 1000000) {
        return AM_ERROR;
    }

    *p_baudrate = 1000000000ul / min_pulse_width;

    p_dev->cap_flag = AM_FALSE;

    return AM_OK;
}

/*******************************************************************************
  接口函数
*******************************************************************************/

/**
 * \brief 获取波特率函数接口
 */
int am_baudrate_get (am_baudrate_detect_handle_t handle, uint32_t *p_baudrate)
{
    am_baudrate_detect_dev_t *p_dev = (am_baudrate_detect_dev_t *)handle;

    if ((p_dev->cap_flag   == AM_TRUE) &&
        (p_dev->data_edge  == 0)       &&
        (p_dev->data_pulses > 0)) {
        return __baudrate_get(p_dev, p_baudrate);
    }
    return AM_ERROR;
}



/**
 * \brief 自动波特率初始化函数
 */
am_baudrate_detect_handle_t am_baudrate_detect_init (am_baudrate_detect_dev_t     *p_dev,
                                                     am_baudrate_detect_devinfo_t *p_devinfo,
                                                     am_cap_handle_t               cap_handle)
{
    if (p_dev      == NULL ||
        p_devinfo  == NULL ||
        cap_handle == NULL) {
        return NULL;
    }


    p_dev->uart_data     = 0;
    p_dev->data_edge     = 0;
    p_dev->time_out_ms   = 0;
    p_dev->data_pulses   = 0;
    p_dev->cap_flag      = AM_FALSE;

    p_dev->cap_handle   = cap_handle;

    p_dev->cap_pin = p_devinfo->cap_pin;

    p_dev->p_devinfo  = p_devinfo;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    /* 捕获输入配置 */
    am_cap_config(cap_handle,
                  p_devinfo->cap_chanel,
                  p_devinfo->cap_trigger,
                  __cap_callback,
                  (void *)p_dev);

    am_cap_enable(cap_handle, p_devinfo->cap_chanel);

    am_softimer_init(&(p_dev->softimer),
                     __softimer_callback,
                     (void *)p_dev);
    am_softimer_start(&(p_dev->softimer), 1);


    return p_dev;
}

/**
 * \brief 自动波特率初解始化函数
 */
void am_baudrate_detect_deinit (am_baudrate_detect_handle_t handle)
{

    am_baudrate_detect_dev_t *p_dev = (am_baudrate_detect_dev_t *)handle;

    am_softimer_stop(&(p_dev->softimer));

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/** [src_am_boot_auto_baudrate] */

/* end of file */
