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
 * \brief 三轴磁传感器传感器 LIS3MDL 例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. 每过一秒，通过串口打印三轴磁传感器和温度的值
 *
 * \par 源代码
 * \snippet demo_std_lis3mdl.c src_std_lis3mdl
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-22  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_lis3mdl
 * \copydoc demo_std_lis3mdl.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_lis3mdl.h"
#include "am_delay.h"

/**
 * \brief 例程入口
 */
void demo_std_lis3mdl_entry (am_sensor_handle_t handle)
{
    uint8_t i = 0;
    
    /* LIS3MDL提供的所有通道ID列举 */
    const int id[4] = {AM_LIS3MDL_CHAN_1, AM_LIS3MDL_CHAN_2,
                       AM_LIS3MDL_CHAN_3, AM_LIS3MDL_CHAN_4};

    /* 储存四个通道数据的缓存 */
    am_sensor_val_t data[4];

    /*
     * 列出四个通道（磁传感器和温度）数据的名字和单位字符串，便于打印
     */
    const char *data_name_string[] = {"MAG_X", "MAG_Y", "MAG_Z", "temperature"};
//    const char *data_unit_string[] = {"gauss", "gauss", "gauss", "℃"};
    //TODO
    const char *data_unit_string[] = {"gauss", "gauss", "gauss", "C"};

    am_sensor_enable(handle, id, 4, data);

    while(1) {
        am_sensor_data_get(handle, id, 4, data);

        for (i = 0; i < 4; i++) {
            if (AM_SENSOR_VAL_IS_VALID(data[i])) { /* 该通道数据有效，可以正常使用 */

                /* 单位转换为 AM_SENSOR_UNIT_MICRO，以打印显示6位小数 */
                am_sensor_val_unit_convert(&data[i], 1, AM_SENSOR_UNIT_MICRO);
                am_kprintf("The %s is : %d.%06d %s.\r\n", 
                                    data_name_string[i],
                                   (data[i].val)/1000000,
                                   (uint32_t)(data[i].val)%1000000,
                                    data_unit_string[i]);
            } else {       //该通道数据无效，数据获取失败
                am_kprintf("The %s get failed!\r\n", data_name_string[i]);
            }
        }
        am_mdelay(1000);
    }
}

/* end of file */
