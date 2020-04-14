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
 * \brief 传感器 BMP280 驱动文件
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-28  yrz, first implementation.
 * \endinternal
 */

#include "am_sensor_bmp280.h"
#include "am_vdebug.h"
#include "am_delay.h"

/*******************************************************************************
 * 宏定义
 ******************************************************************************/  
#define  __BMP280_REG_T_XLSB        0XFC    /**< \brief 温度低字节地址        */   
#define  __BMP280_REG_T_LSB         0XFB    /**< \brief 温度次低字节地址      */   
#define  __BMP280_REG_T_MSB         0XFA    /**< \brief 温度高字节地址        */ 
#define  __BMP280_REG_P_XLSB        0XF9    /**< \brief 气压低字节地址        */
#define  __BMP280_REG_P_LSB         0XF8    /**< \brief 气压次低字节地址      */
#define  __BMP280_REG_P_MSB         0XF7    /**< \brief 气压高字节地址        */
#define  __BMP280_REG_CONFIG        0XF5    /**< \brief 配置寄存器地址        */
#define  __BMP280_REG_CTRL_MEAS     0XF4    /**< \brief 控制测量寄存器地址    */
#define  __BMP280_REG_STATUS        0XF3    /**< \brief 状态寄存器地址        */
#define  __BMP280_REG_RESET         0XE0    /**< \brief 复位寄存器地址        */
#define  __BMP280_REG_ID            0XD0    /**< \brief ID寄存器地址          */
#define  __BMP280_MY_ID             0x58    /**< \brief 设备ID                */
#define  __BMP280_CMD_RESET        	0xB6    /**< \brief 设备复位命令          */
                                              
#define  __BMP280_REG_DIG_T1        0x88    /**< \brief 温度校准值1地址       */
#define  __BMP280_REG_DIG_T1_LEN    2       /**< \brief 温度校准值1地址长度   */
#define  __BMP280_REG_DIG_T2        0x8A    /**< \brief 温度校准值2地址       */
#define  __BMP280_REG_DIG_T2_LEN    2       /**< \brief 温度校准值2地址长度   */
#define  __BMP280_REG_DIG_T3        0x8C    /**< \brief 温度校准值3地址       */
#define  __BMP280_REG_DIG_T3_LEN    2       /**< \brief 温度校准值3地址长度   */
                                              
#define  __BMP280_REG_DIG_P1        0x8E    /**< \brief 压力校准值1地址       */
#define  __BMP280_REG_DIG_P1_LEN    2       /**< \brief 压力校准值1地址长度   */
#define  __BMP280_REG_DIG_P2        0x90    /**< \brief 压力校准值2地址       */
#define  __BMP280_REG_DIG_P2_LEN    2       /**< \brief 压力校准值2地址长度   */
#define  __BMP280_REG_DIG_P3        0x92    /**< \brief 压力校准值3地址       */
#define  __BMP280_REG_DIG_P3_LEN    2       /**< \brief 压力校准值3地址长度   */
#define  __BMP280_REG_DIG_P4        0x94    /**< \brief 压力校准值4地址       */
#define  __BMP280_REG_DIG_P4_LEN    2       /**< \brief 压力校准值4地址长度   */
#define  __BMP280_REG_DIG_P5        0x96    /**< \brief 压力校准值5地址       */
#define  __BMP280_REG_DIG_P5_LEN    2       /**< \brief 压力校准值5地址长度   */
#define  __BMP280_REG_DIG_P6        0x98    /**< \brief 压力校准值6地址       */
#define  __BMP280_REG_DIG_P6_LEN    2       /**< \brief 压力校准值6地址长度   */
#define  __BMP280_REG_DIG_P7        0x9A    /**< \brief 压力校准值7地址       */
#define  __BMP280_REG_DIG_P7_LEN    2       /**< \brief 压力校准值7地址长度   */
#define  __BMP280_REG_DIG_P8        0x9C    /**< \brief 压力校准值8地址       */
#define  __BMP280_REG_DIG_P8_LEN    2       /**< \brief 压力校准值8地址长度   */
#define  __BMP280_REG_DIG_P9        0x9E    /**< \brief 压力校准值9地址       */
#define  __BMP280_REG_DIG_P9_LEN    2       /**< \brief 压力校准值9地址长度   */


/** \brief 获取DATA状态位 */
#define __BMP280_GET_DATA_STATUS(reg)   (((reg) >> 3) & 0x1)

/** \brief 将两个int8转换为一个int16类型 */
#define __BMP280_UINT8_TO_UINT16(buff) ((int16_t)((buff[1] << 8) | buff[0]))

/** \brief 将三个int8转换为一个20bit类型 */
#define __BMP280_UINT8_TO_UINT32(buff) \
                       (int32_t)(((int32_t)(buff[0]) << 12) \
                               | ((int32_t)(buff[1]) << 4)  \
                               | ((int32_t)(buff[2]) >> 4))
/** \brief 利用校准值t1，t2，t3计算出传入t的温度实际值 并扩大10^6倍 */ 
#define __BMP280_GET_TEM_VALUE(t, t1, t2, t3) \
                (((((((double)t) / 16384.0 - ((double) t1) / 1024.0) * \
                  ((double) t2)) + (((((double)t) / 131072.0 - ((double) t1) / \
                  8192.0) * (((double)t) / 131072.0 - ((double) t1) / \
                  8192.0)) * ((double) t3))) * 1000000) / 5120)
/** \brief 利用校准值t1，t2，t3计算出气压校准的参数t_define */ 
#define __BMP280_GET_T_DEFINE(t, t1, t2, t3) \
                (((((double)t) / 16384.0 - ((double) t1) / 1024.0) * \
                  ((double) t2)) + (((((double)t) / 131072.0 - ((double) t1) / \
                  8192.0) * (((double)t) / 131072.0 - ((double) t1) / \
                  8192.0)) * ((double) t3)))
 
/** \brief 模块工作 */
#define __BMP280_NORMAL                   (0x3<<0)
/** \brief 模块睡眠 */
#define __BMP280_SLEEP                    (~(0x3<<0))
/** \brief 打开压强测量 */ 
#define __BMP280_PRESS_START              (0x2<<2)
/** \brief 关闭压强测量 */ 
#define __BMP280_PRESS_CLOSE              (~(0x2<<2))                   
/** \brief 打开温度测量 */ 
#define __BMP280_TEMP_START               (0x2<<5)
/** \brief 关闭温度测量 */ 
#define __BMP280_TEMP_CLOSE               (~(0x2<<5))                  
/*******************************************************************************
 * 本地函数声明
 ******************************************************************************/
/** \brief 获取该传感器某一通道的类型 */
am_local am_err_t __pfn_type_get (void *p_drv, int id);

/** \brief 获取传感器通道采样数据 */
am_local am_err_t __pfn_data_get (void            *p_drv,
                                  const int       *p_ids,
                                  int              num,
                                  am_sensor_val_t *p_buf);

/** \brief 使能传感器通道 */
am_local am_err_t __pfn_enable (void            *p_drv,
                                const int       *p_ids,
                                int              num,
                                am_sensor_val_t *p_result);

/** \brief 禁能传感器通道 */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result);

/** \brief 配置传感器通道属性 */
am_local am_err_t __pfn_attr_set (void                  *p_drv,
                                  int                    id,
                                  int                    attr,
                                  const am_sensor_val_t *p_val);

/** \brief 获取传感器通道属性 */
am_local am_err_t __pfn_attr_get (void            *p_drv,
                                  int              id,
                                  int              attr,
                                  am_sensor_val_t *p_val);
                                  
/** \brief 设置触发，一个通道仅能设置一个触发回调函数 */
am_local am_err_t __pfn_trigger_cfg (void                   *p_drv,
                                     int                     id,
                                     uint32_t                flags,
                                     am_sensor_trigger_cb_t  pfn_cb,
                                     void                   *p_arg);

/** \brief 打开触发 */
am_local am_err_t __pfn_trigger_on (void *p_drv, int id);

/** \brief 关闭触发 */
am_local am_err_t __pfn_trigger_off (void *p_drv, int id);
                                     
/** \brief 传感器标准服务 */
am_local am_const struct am_sensor_drv_funcs __g_sensor_bmp280_funcs = {
        __pfn_type_get,
        __pfn_data_get,
        __pfn_enable,
        __pfn_disable,
        __pfn_attr_set,
        __pfn_attr_get,
        __pfn_trigger_cfg,
        __pfn_trigger_on,
        __pfn_trigger_off
};
/*******************************************************************************
  Local functions
*******************************************************************************/
/**
 * \brief bmp280 写数据
 */
am_local am_err_t __bmp280_write (am_sensor_bmp280_dev_t *p_this,
                                  uint32_t                subaddr,
                                  uint8_t                *p_buf,
                                  uint32_t                nbytes)
{
    return am_i2c_write(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/**
 * \brief bmp280 读数据
 */
am_local am_err_t __bmp280_read (am_sensor_bmp280_dev_t *p_this,
                                 uint32_t                subaddr,
                                 uint8_t                *p_buf,
                                 uint32_t                nbytes)
{
    return am_i2c_read(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/**
 * \brief 获取压力校准值
 */
am_local am_err_t __bmp280_get_press_cal (am_sensor_bmp280_dev_t *p_this)
{
    uint8_t buff[2] = {0};

    am_err_t ret = AM_OK;

    /**
     * \brief 以下为获取压力校准的9组数据
     */
    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_P1,
                        buff,
                        __BMP280_REG_DIG_P1_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p1 = __BMP280_UINT8_TO_UINT16(buff);

    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_P2,
                        buff,
                        __BMP280_REG_DIG_P2_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p2 = __BMP280_UINT8_TO_UINT16(buff);    

    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_P3,
                        buff,
                        __BMP280_REG_DIG_P3_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p3 = __BMP280_UINT8_TO_UINT16(buff);     
 
    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_P4,
                        buff,
                        __BMP280_REG_DIG_P4_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p4 = __BMP280_UINT8_TO_UINT16(buff); 

    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_P5,
                        buff,
                        __BMP280_REG_DIG_P5_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p5 = __BMP280_UINT8_TO_UINT16(buff); 

    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_P6,
                        buff,
                        __BMP280_REG_DIG_P6_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p6 = __BMP280_UINT8_TO_UINT16(buff);
    
    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_P7,
                        buff,
                        __BMP280_REG_DIG_P7_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p7 = __BMP280_UINT8_TO_UINT16(buff);    
    
    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_P8,
                        buff,
                        __BMP280_REG_DIG_P8_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p8 = __BMP280_UINT8_TO_UINT16(buff);  

    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_P9,
                        buff,
                        __BMP280_REG_DIG_P9_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p9 = __BMP280_UINT8_TO_UINT16(buff);
    
    return ret;
}

/**
 * \brief 获取温度校准值
 */
am_local am_err_t __bmp280_get_tem_cal (am_sensor_bmp280_dev_t *p_this)
{
    uint8_t buff[2] = {0};
    
    am_err_t ret = AM_OK;

    /**
     * \brief 以下为获取温度校准的3组数据
     */
    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_T1,
                        buff,
                        __BMP280_REG_DIG_T1_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_t1 = __BMP280_UINT8_TO_UINT16(buff);

    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_T2,
                        buff,
                        __BMP280_REG_DIG_T2_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_t2 = __BMP280_UINT8_TO_UINT16(buff); 

    ret = __bmp280_read(p_this,
                        __BMP280_REG_DIG_T3,
                        buff,
                        __BMP280_REG_DIG_T3_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_t3 = __BMP280_UINT8_TO_UINT16(buff);    
    
    return ret;
}

/** \brief 计算气压 */
am_local int32_t __bmp280_press_cal (am_sensor_bmp280_dev_t *p_this,
                                     int32_t                 press)
{
    int32_t var1 = 0;
    int32_t var2 = 0;
    int32_t t_fine = 0;

    /* 校准参数指针 */
    am_bmp280_calibration_data_t *p_cal = &(p_this->cal_val);
    
    t_fine = p_cal->t_fine; 

    /* 转换成实际气压值 */             
    var1 = ((double)t_fine / 2.0)-64000.0;
    var2 = var1 * var1 * ((double)p_cal->dig_p6) / 32768.0;
    var2 = var2 + var1 * ((double)p_cal->dig_p5) * 2.0;
    var2 = (var2 / 4.0) + (((double)p_cal->dig_p4) * 65536.0);
    var1 = (((double)p_cal->dig_p3) * var1 * var1 / 524288.0
         + ((double)p_cal->dig_p2) * var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0) * ((double)p_cal->dig_p1);
    press = 1048576.0 - (double)press;
    press = (press - (var2 / 4096.0)) * 6250.0 / var1;
    var1 = ((double)p_cal->dig_p9) * press * press / 2147483648.0;
    var2 = press * ((double)p_cal->dig_p8) / 32768.0;
    press = press + (var1 + var2 + ((double)p_cal->dig_p7)) / 16.0;
    
    return  press;             
}

/** \brief 获取该传感器某一通道的类型 */
am_local am_err_t __pfn_type_get (void *p_drv, int id)
{
    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (id == AM_BMP280_CHAN_1) {
        return AM_SENSOR_TYPE_PRESS;
    } else if (id == AM_BMP280_CHAN_2) {
        return AM_SENSOR_TYPE_TEMPERATURE;
    } else {
        return -AM_ENODEV;
    }
}

/** \brief 获取传感器通道采样数据 */
am_local am_err_t __pfn_data_get (void            *p_drv,
                                  const int       *p_ids,
                                  int              num,
                                  am_sensor_val_t *p_buf)
{
    am_sensor_bmp280_dev_t* p_this = (am_sensor_bmp280_dev_t*)p_drv;

    am_bmp280_calibration_data_t *p_cal = &p_this->cal_val;

    am_err_t ret        = AM_OK;
    uint8_t status_val  = 0;
    uint8_t reg_data[3] = {0};
    int32_t tem_data    = 0;

    int cur_id = 0;
    int i      = 0;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (AM_BIT_GET(p_this->trigger, 7) != 1) {
        return -AM_EPERM;
    }

    for (i = 0; i < num; i++) {
        p_buf[i].unit = AM_SENSOR_UNIT_INVALID;
    }

    /** \brief 获取可读状态值 */
    do {
        ret = __bmp280_read(p_this, __BMP280_REG_STATUS, &status_val, 1);
        if (ret != AM_OK) {
            return ret;
        }
    } while (__BMP280_GET_DATA_STATUS(status_val) != 0x1);

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {
            
            /** \brief 获取温度寄存器值 */
            ret = __bmp280_read(p_this, __BMP280_REG_T_MSB, reg_data, 3);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __BMP280_UINT8_TO_UINT32(reg_data);
           
            /** \brief 根据温度值计算气压校准参数 */
            p_cal->t_fine = __BMP280_GET_T_DEFINE(tem_data,
                                                  p_cal->dig_t1,
                                                  p_cal->dig_t2,
                                                  p_cal->dig_t3);
            /** \brief 获取压力值 */
            ret = __bmp280_read(p_this, __BMP280_REG_P_MSB, reg_data, 3);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __BMP280_UINT8_TO_UINT32(reg_data);
           
            /** \brief 压力 */
            p_buf[i].val = __bmp280_press_cal(p_this, tem_data); 
            p_buf[i].unit = AM_SENSOR_UNIT_BASE; /*< \brief 单位默认为0:10^(0)*/

        } else if (cur_id == 1) {

            /** \brief 获取温度 */
            ret = __bmp280_read(p_this, __BMP280_REG_T_MSB, reg_data, 3);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __BMP280_UINT8_TO_UINT32(reg_data);
           
            /** \brief 温度 */
            p_buf[i].val = __BMP280_GET_TEM_VALUE(tem_data,
                                                  p_cal->dig_t1,
                                                  p_cal->dig_t2,
                                                  p_cal->dig_t3); 
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief 单位默认为-6:10^(-6)*/

        } else {
            return -AM_ENODEV;  /*< \brief 若此次通道不属于该传感器，直接返回 */
        }
    }
    
    return ret;
}

/** \brief 使能传感器通道 */
am_local am_err_t __pfn_enable (void            *p_drv,
                                const int       *p_ids,
                                int              num,
                                am_sensor_val_t *p_result)
{
    am_sensor_bmp280_dev_t* p_this = (am_sensor_bmp280_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    uint8_t ctrl_meas = 0;

    am_err_t ret = -AM_ENODEV;
    am_err_t cur_ret = AM_OK;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            if (p_result != NULL) {
                p_result[i].val = AM_OK;
            }
            AM_BIT_SET(p_this->trigger, 6);           
            ret = AM_OK;

        } else if (cur_id == 1) {
 
            if (p_result != NULL) {
                p_result[i].val = AM_OK;
            }
            AM_BIT_SET(p_this->trigger, 5);           
            ret = AM_OK;

        } else {
            if (p_result != NULL) {
                p_result[i].val = -AM_ENODEV;
            }
            cur_ret = -AM_ENODEV;
        }
    }

    if (ret != AM_OK) {    /**< \breif 如果本次没有该传感器的通道传入，则退出 */
        return cur_ret;
    }

    if ((AM_BIT_GET(p_this->trigger, 6) == 1)
            || (AM_BIT_GET(p_this->trigger, 5) == 1)) {  
        ret = __bmp280_read(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        /** \brief 进入工作模式 */
        ctrl_meas |= __BMP280_NORMAL;
        ret = __bmp280_write(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    }  

    if (AM_BIT_GET(p_this->trigger, 5) == 1) {

        ret = __bmp280_read(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        /** \brief 使能该通道 */
        ctrl_meas |= __BMP280_TEMP_START;
        ret = __bmp280_write(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    } 
    
    if (AM_BIT_GET(p_this->trigger, 6) == 1) {

        ret = __bmp280_read(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        /** \brief 使能该通道 */
        ctrl_meas |= __BMP280_PRESS_START;
        ret = __bmp280_write(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    } 

    if (ret == AM_OK) {
        AM_BIT_SET(p_this->trigger, 7);
    }

    return cur_ret;
}

/** \brief 禁能传感器通道 */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result)
{
    am_sensor_bmp280_dev_t* p_this = (am_sensor_bmp280_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t ctrl_meas = 0;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            AM_BIT_CLR(p_this->trigger, 6);
            ret = AM_OK;

        } else if (cur_id == 1) {

            AM_BIT_CLR(p_this->trigger, 5);
            ret = AM_OK;

        } else {
            ret = -AM_ENODEV;
        }

        if (p_result != NULL) {
            p_result[i].val = ret;
        }
    }

    if ((AM_BIT_GET(p_this->trigger, 6) == 0)
            && (AM_BIT_GET(p_this->trigger, 5) == 0)) {

        ret = __bmp280_read(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        /** \brief 进入睡眠模式，关闭通道 */
        ctrl_meas &= __BMP280_SLEEP & __BMP280_PRESS_CLOSE & __BMP280_TEMP_CLOSE;
        ret = __bmp280_write(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        if (cur_ret == AM_OK) {
            AM_BIT_CLR(p_this->trigger, 7);
        }
    } else if (AM_BIT_GET(p_this->trigger, 6) == 0) {

        ret = __bmp280_read(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        /** \brief 关闭该通道 */
        ctrl_meas &= __BMP280_PRESS_CLOSE;
        ret = __bmp280_write(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }
    } else if (AM_BIT_GET(p_this->trigger, 5) == 0) {

        ret = __bmp280_read(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        /** \brief 关闭该通道 */
        ctrl_meas &= __BMP280_TEMP_CLOSE;
        ret = __bmp280_write(p_this, __BMP280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }
    } 
        
    return cur_ret;
}

/** \brief 配置传感器通道属性 */
am_local am_err_t __pfn_attr_set (void                  *p_drv,
                                  int                    id,
                                  int                    attr,
                                  const am_sensor_val_t *p_val)
{
    return -AM_ENOTSUP;
}

/** \brief 获取传感器通道属性 */
am_local am_err_t __pfn_attr_get (void            *p_drv,
                                  int              id,
                                  int              attr,
                                  am_sensor_val_t *p_val)
{
    return -AM_ENOTSUP;
}

/** \brief 设置触发，一个通道仅能设置一个触发回调函数 */
am_local am_err_t __pfn_trigger_cfg (void                   *p_drv,
                                     int                     id,
                                     uint32_t                flags,
                                     am_sensor_trigger_cb_t  pfn_cb,
                                     void                   *p_arg)
{
    return -AM_ENOTSUP;
}

/** \brief 打开触发 */
am_local am_err_t __pfn_trigger_on (void *p_drv, int id)
{
    return -AM_ENOTSUP;
}

/** \brief 关闭触发 */
am_local am_err_t __pfn_trigger_off (void *p_drv, int id)
{
    return -AM_ENOTSUP;
}
/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief 传感器 BMP280 初始化
 */
am_sensor_handle_t am_sensor_bmp280_init (
        am_sensor_bmp280_dev_t           *p_dev,
        const am_sensor_bmp280_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle)
{
    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;
    
    uint8_t  reset = __BMP280_CMD_RESET;
    uint8_t bmp280_id = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->bmp280_dev.p_drv   = p_dev;
    p_dev->bmp280_dev.p_funcs = &__g_sensor_bmp280_funcs;
    p_dev->dev_info           = p_devinfo;

    p_dev->trigger            = 0;
    p_dev->data[0].val        = 0;
    p_dev->data[0].unit       = AM_SENSOR_UNIT_INVALID;
    p_dev->data[1].val        = 0;
    p_dev->data[1].unit       = AM_SENSOR_UNIT_INVALID;

    /* 复位BMP280 */
    ret = __bmp280_read(p_dev, __BMP280_REG_RESET, &reset, 1); 
    if (ret != AM_OK) {
        cur_ret = ret;
    }
    /* 等待复位完成 */
    am_mdelay(50);    
    
    /* 读取ID */
    ret = __bmp280_read(p_dev, __BMP280_REG_ID, &bmp280_id, 1);
    if (ret != AM_OK || bmp280_id != __BMP280_MY_ID) {
        cur_ret = ret;
    } else {

        /* 获取压力校准值 */
        ret = __bmp280_get_press_cal(p_dev);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        /* 获取温度校准值 */
        ret = __bmp280_get_tem_cal(p_dev);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    }

    if (cur_ret != AM_OK) {
        am_kprintf("\r\nSensor bmp280 Init is ERROR! \r\n");
        return NULL;
    }

    return &(p_dev->bmp280_dev);
}

/**
 * \brief 传感器 bmp280 去初始化
 */
am_err_t am_sensor_bmp280_deinit (am_sensor_handle_t handle)
{
    am_sensor_bmp280_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->bmp280_dev.p_drv   = NULL;
    p_dev->bmp280_dev.p_funcs = NULL;
    p_dev->dev_info           = NULL;

    return AM_OK;
}


/* end of file */
