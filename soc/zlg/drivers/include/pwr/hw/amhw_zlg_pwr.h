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
 * \brief 电源管理接口
 *
 * \internal
 * \par History
 * - 1.00 17-04-17  nwt, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG_PWR_H
#define __AMHW_ZLG_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_zlg_if_pwr
 * \copydoc amhw_zlg_pwr.h
 * @{
 */

/**
 * \name 清除待机位与唤醒位清除
 * @{
 */

#define AM_ZLG_STANDBY_FLAG_CLEAR  (1UL << 3)
#define AM_ZLG_WAKEUP_FLAG_CLEAR   (1UL << 2)

/** @} */

/**
 * \name 掉电深度睡眠模式
 * @{
 */

#define AM_ZLG_PDDS_STANDBY_MODE  1
#define AM_ZLG_PDDS_STOP_MODE     0

/** @} */

/**
 * \name 源电压监测器（PVD）使能
 * @{
 */
#define AM_ZLG_PVDE_ENABLE        1
#define AM_ZLG_PVDE_DISABLE       0

/** @} */

/**
 * \name BKP备份寄存器访问使能
 * @{
 */
#define AM_ZLG_BKP_ENABLE         1
#define AM_ZLG_BKP_DISABLE        0

/** @} */

/**
 * \name WAKE_UP唤醒引脚使能
 * @{
 */
#define AM_ZLG_WAKEUP_ENABLE      1
#define AM_ZLG_WAKEUP_DISABLE     0

/** @} */

/**
  * \brief 系统控制寄存器块结构体
  */
typedef struct amhw_zlg_pwr {
    __IO  uint32_t cr;          /**< \brief 电源控制寄存器 */
    __IO  uint32_t csr;         /**< \brief 电源控制/状态寄存器 */
} amhw_zlg_pwr_t;

/**
 * \brief PVD电平选择
 */
typedef enum amhw_zlg_pvd_lever_set {
    AMHW_ZLG_PVD_LEVER_1_8V  = 0,  /**< \brief 1.8V PVD监测电压 */
    AMHW_ZLG_PVD_LEVER_2_1V  = 1,  /**< \brief 2.1V PVD监测电压 */
    AMHW_ZLG_PVD_LEVER_2_4V  = 2,  /**< \brief 2.4V PVD监测电压 */
    AMHW_ZLG_PVD_LEVER_2_7V  = 3,  /**< \brief 2.7V PVD监测电压 */
    AMHW_ZLG_PVD_LEVER_3_0V  = 4,  /**< \brief 3.0V PVD监测电压 */
    AMHW_ZLG_PVD_LEVER_3_3V  = 5,  /**< \brief 3.3V PVD监测电压 */
    AMHW_ZLG_PVD_LEVER_3_6V  = 6,  /**< \brief 3.6V PVD监测电压 */
    AMHW_ZLG_PVD_LEVER_3_9V  = 7,  /**< \brief 3.9V PVD监测电压 */
    AMHW_ZLG_PVD_LEVER_4_2V  = 8,  /**< \brief 4.2V PVD监测电压 */
    AMHW_ZLG_PVD_LEVER_4_5V  = 9,  /**< \brief 4.5V PVD监测电压 */
    AMHW_ZLG_PVD_LEVER_4_8V  = 10, /**< \brief 4.8V PVD监测电压 */
} amhw_zlg_pvd_lever_set_t;

/**
 * \brief 电源控制状态标志
 */
typedef enum amhw_zlg_pwr_status_flag {
    AMHW_ZLG_PVD_OUTPUT_FLAG  = (1UL << 2),  /**< \brief PVD输出标志位 */
    AMHW_ZLG_PVD_SBF_FLAG     = (1UL << 1),  /**< \brief 待机标志位 */
    AMHW_ZLG_PVD_WUF_FLAG     = (1UL << 0),  /**< \brief 唤醒标志位 */
} amhw_zlg_pwr_status_flag_t;

/**
 * \brief 深度掉电模式选择
 *
 * \param[in] pdds_mode ： 深度掉电模式类型,值为  AM_ZLG_PDDS_*_MODE 这一类宏
 *                         (# AM_ZLG_PDDS_STOP_MODE)
 * \param[in] p_hw_pwr  ： 指向电源控制寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_zlg_pwr_pdds_mode_set (amhw_zlg_pwr_t *p_hw_pwr, uint8_t pdds_mode)
{
    AM_BITS_SET(p_hw_pwr->cr, 0, 2, (pdds_mode << 1));
}

/**
 * \brief PVD电压监测使能
 *
 * \param[in] p_hw_pwr    ：指向电源控制寄存器块的指针
 * \param[in] pvd_enable  ：电压监测使能，值为  AM_ZLG_PVDE_* 这一类宏
 *                           (# AM_ZLG_PVDE_ENABLE)
 *
 * \return 无
 */
am_static_inline
void amhw_zlg_pwr_pvd_detect_enable (amhw_zlg_pwr_t *p_hw_pwr, uint8_t pvd_enable)
{
    AM_BIT_MODIFY(p_hw_pwr->cr, 4, pvd_enable);
}

/**
 * \brief 访问备份寄存器使能
 *
 * \param[in] p_hw_pwr    ：指向电源控制寄存器块的指针
 * \param[in] bkp_enable  ：电压监测使能，值为  AM_ZLG_BKP_* 这一类宏
 *                           (# AM_ZLG_BKP_ENABLE)
 *
 * \return 无
 */
am_static_inline
void amhw_zlg_pwr_bkp_access_enable (amhw_zlg_pwr_t *p_hw_pwr, uint8_t bkp_enable)
{
    AM_BIT_MODIFY(p_hw_pwr->cr, 8, bkp_enable);
}

/**
 * \brief 清除待机标志位与唤醒位
 *
 * \param[in] p_hw_pwr    ：指向电源控制寄存器块的指针
 * \param[in] status_flg  ：标志位清除选择，值为  AM_ZLG_*_FLAG_CLEAR 这一类宏
 *                           (# AM_ZLG_STANDBY_FLAG_CLEAR)
 *
 * \return 无
 */
am_static_inline
void amhw_zlg_pwr_stauts_flag_clear (amhw_zlg_pwr_t *p_hw_pwr, uint8_t status_flg)
{
    AM_BIT_SET_MASK(p_hw_pwr->cr, status_flg);
}

/**
 * \brief PV监测电压选择
 *
 * \param[in] p_hw_pwr ：指向电源控制寄存器块的指针
 * \param[in] pvd_lever：电压监测范围选择, 值为 amhw_zlg_pvd_lever_set_t 这一枚举类型的值
 *
 * \return 无
 */
am_static_inline
void amhw_zlg_pvd_lever_set (amhw_zlg_pwr_t *p_hw_pwr, uint8_t pvd_lever)
{
    AM_BITS_SET(p_hw_pwr->cr, 9, 4, pvd_lever);
}

/**
 * \brief 使能WAKE_UP引脚
 *
 * \param[in] p_hw_pwr ：指向电源控制寄存器块的指针
 * \param[in] wakeup_en：唤醒引脚使能与否，值为 AM_ZLG_WAKEUP_* 这一类宏，
 *                      (# AM_ZLG_WAKEUP_ENABLE)
 *
 * \return 无
 */
am_static_inline
void amhw_zlg_wake_up_enable (amhw_zlg_pwr_t *p_hw_pwr, uint8_t wakeup_en)
{
    p_hw_pwr->csr |= (wakeup_en << 8);
}

/**
 * \brief 获取电源控制相关状态位
 *
 * \param[in] p_hw_pwr   ：指向电源控制寄存器块的指针
 * \param[in] status_flag：电源控制状态位，值为 amhw_zlg_pwr_status_flag_t 这一枚举类型
 *
 * \return 当返回值不为0时，代表该标志位置1
 */
am_static_inline
uint32_t amhw_zlg_pwr_csr_status_get (amhw_zlg_pwr_t *p_hw_pwr, uint8_t status_flag)
{
    return p_hw_pwr->csr & status_flag;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZLG_PWR_H */

/* end of file */
