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
 * \brief EXTI 接口
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZMF159_EXTI_H
#define __AMHW_ZMF159_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_zlg_exti.h"

/*
 * \brief 匿名结构体段的开始
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_zmf159_if_exti
 * \copydoc amhw_zmf159_exti.h
 * @{
 */

/**
 * \brief EXTI寄存器块结构体
 */
typedef amhw_zlg_exti_t amhw_zmf159_exti_t;

/**
 * \brief 线编号枚举
 */
typedef enum {
    AMHW_ZMF159_LINE_NUM0  = (1ul << 0),    /**< \brief 线0 */
    AMHW_ZMF159_LINE_NUM1  = (1ul << 1),    /**< \brief 线1 */
    AMHW_ZMF159_LINE_NUM2  = (1ul << 2),    /**< \brief 线2 */
    AMHW_ZMF159_LINE_NUM3  = (1ul << 3),    /**< \brief 线3 */
    AMHW_ZMF159_LINE_NUM4  = (1ul << 4),    /**< \brief 线4 */
    AMHW_ZMF159_LINE_NUM5  = (1ul << 5),    /**< \brief 线5 */
    AMHW_ZMF159_LINE_NUM6  = (1ul << 6),    /**< \brief 线6 */
    AMHW_ZMF159_LINE_NUM7  = (1ul << 7),    /**< \brief 线7 */
    AMHW_ZMF159_LINE_NUM8  = (1ul << 8),    /**< \brief 线8 */
    AMHW_ZMF159_LINE_NUM9  = (1ul << 9),    /**< \brief 线9 */
    AMHW_ZMF159_LINE_NUM10 = (1ul << 10),   /**< \brief 线10 */
    AMHW_ZMF159_LINE_NUM11 = (1ul << 11),   /**< \brief 线11 */
    AMHW_ZMF159_LINE_NUM12 = (1ul << 12),   /**< \brief 线12 */
    AMHW_ZMF159_LINE_NUM13 = (1ul << 13),   /**< \brief 线13 */
    AMHW_ZMF159_LINE_NUM14 = (1ul << 14),   /**< \brief 线14 */
    AMHW_ZMF159_LINE_NUM15 = (1ul << 15),   /**< \brief 线15 */
    AMHW_ZMF159_LINE_NUM16 = (1ul << 16),   /**< \brief 线16连接到 PVD 输出 */
    AMHW_ZMF159_LINE_NUM17 = (1ul << 17),   /**< \brief 线17连接到RTC闹钟事件 */
    AMHW_ZMF159_LINE_NUM18 = (1ul << 18),   /**< \brief 线18链接到USB唤醒事件 */
    AMHW_ZMF159_LINE_NUM19 = (1ul << 19),   /**< \brief 线19连接到比较器1输出 */
    AMHW_ZMF159_LINE_NUM20 = (1ul << 20),   /**< \brief 线20连接到比较器2输出 */
    AMHW_ZMF159_LINE_NUM21 = (1ul << 21),   /**< \brief 线21连接到IWDG中断 */

}amhw_zmf159_exti_line_num_t;

/**
 * \brief 中断/事件触发枚举
 */
typedef enum
{
    AMHW_ZMF159_EXTI_TRIGGER_RISING         = 0x08,
    AMHW_ZMF159_EXTI_TRIGGER_FALLING        = 0x0C,
    AMHW_ZMF159_EXTI_TRIGGER_RISING_FALLING = 0x10
}amwh_zmf159_extitrigger_type_t;

/**
 * \brief 开放来自线 x上的中断请求
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]   num : 线编号
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_exti_imr_set(amhw_zmf159_exti_t     *p_hw_exti,
                              amhw_zmf159_exti_line_num_t  num)
{
    p_hw_exti->imr |= (num & 0x3fffff);
}

/**
 * \brief 屏蔽来自线 x上的中断请求
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]   num : 线编号
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_exti_imr_clear(amhw_zmf159_exti_t     *p_hw_exti,
                                amhw_zmf159_exti_line_num_t  num)
{
    p_hw_exti->imr &= ~(num & 0x3fffff);
}

/**
 * \brief 开放来自线 x上的事件请求
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]    num : 线编号
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_exti_emr_set(amhw_zmf159_exti_t    *p_hw_exti,
                              amhw_zmf159_exti_line_num_t num)
{
    p_hw_exti->emr |= (num & 0x3fffff);
}

/**
 * \brief 屏蔽来自线 x上的事件请求
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]   num : 线编号
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_exti_emr_clear(amhw_zmf159_exti_t     *p_hw_exti,
                                amhw_zmf159_exti_line_num_t  num)
{
    p_hw_exti->emr &= ~(num & 0x3fffff);
}

/**
 * \brief 允许输入线 x上的上升沿触发（中断和事件）
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]   num : 线编号
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_exti_rtsr_set(amhw_zmf159_exti_t     *p_hw_exti,
                               amhw_zmf159_exti_line_num_t  num)
{
    p_hw_exti->rtsr |= (num & 0x3fffff);
}

/**
 * \brief 禁止输入线 x上的上升沿触发（中断和事件）
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]   num : 线编号
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_exti_rtsr_clear(amhw_zmf159_exti_t     *p_hw_exti,
                                 amhw_zmf159_exti_line_num_t  num)
{
    p_hw_exti->rtsr &= ~(num & 0x3fffff);
}

/**
 * \brief 允许输入线 x上的下降沿触发（中断和事件）
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]   num : 线编号
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_exti_ftsr_set(amhw_zmf159_exti_t     *p_hw_exti,
                               amhw_zmf159_exti_line_num_t  num)
{
    p_hw_exti->ftsr |= (num & 0x3fffff);
}

/**
 * \brief 禁止输入线 x上的下降沿触发（中断和事件）
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]   num : 线编号
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_exti_ftsr_clear(amhw_zmf159_exti_t     *p_hw_exti,
                                 amhw_zmf159_exti_line_num_t  num)
{
    p_hw_exti->ftsr &= ~(num & 0x3fffff);
}

/**
 * \brief 产生线 x上的软件中断
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]   num : 线编号
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_exti_swier_set(amhw_zmf159_exti_t     *p_hw_exti,
                                amhw_zmf159_exti_line_num_t  num)
{
    p_hw_exti->swier |= (num & 0x3fffff);
}

/**
 * \brief 清除中断标志
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]   num : 线编号
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_exti_pending_clear(amhw_zmf159_exti_t     *p_hw_exti,
                                    amhw_zmf159_exti_line_num_t  num)
{
    p_hw_exti->pr |= (num & 0x3fffff);
}

/**
 * \brief 获取外部中断标志
 *
 * \param[in]   p_hw_exti : 指向外部中断/事件控制块的指针
 * \param[in]   num : 线编号
 *
 * \return 产生的中断标志
 *              AMHW_ZMF159_LINE_NUM* 宏值或
 *              多个AMHW_ZMF159_LINE_NUM*宏的或值
 *              如:
 *               - AMHW_ZMF159_LINE_NUM0
 *               - AMHW_ZMF159_LINE_NUM0 | AMHW_ZMF159_LINE_NUM1
 *
 */
am_static_inline
uint32_t amhw_zmf159_exti_pr_read(amhw_zmf159_exti_t     *p_hw_exti,
                                  amhw_zmf159_exti_line_num_t  num)
{
    return (p_hw_exti->pr & num);
}
/**
 * @}
 */
/*
 * \brief 匿名结构体段的结束
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __AMHW_ZMF159_EXTI_H */

#endif

/* end of file */
