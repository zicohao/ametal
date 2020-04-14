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
 * \brief ZMF159 中断号定义
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-21  ipk, first implementation
 * \endinternal
 */

#ifndef __ZMF159_INUM_H
#define __ZMF159_INUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \addtogroup zmf159_if_inum
 * \copydoc zmf159_inum.h
 * @{
 */

/**
 * \name ZMF159 CPU 中断号
 * @{
 */

#define INUM_WWDG_IWDG            0    /**< \brief 看门狗中断 */
#define INUM_PVD                  1    /**< \brief 电源电压检测中断 */
#define INUM_TAMPER               2    /**< \brief 侵入检测中断 */
#define INUM_RTC                  3    /**< \brief 实时时钟（RTC）全局中断 */
#define INUM_FLASH                4    /**< \brief 闪存全局中断 */
#define INUM_RCC                  5    /**< \brief 复位和时钟控制（RCC）中断 */

#define INUM_EXTI0                6    /**< \brief EXTI线0中断 */
#define INUM_EXTI1                7    /**< \brief EXTI线1中断 */
#define INUM_EXTI2                8    /**< \brief EXTI线2中断 */
#define INUM_EXTI3                9    /**< \brief EXTI线3中断 */
#define INUM_EXTI4                10   /**< \brief EXTI线4中断 */

#define INUM_DMA1_1               11   /**< \brief DMA1通道1全局中断 */
#define INUM_DMA1_2               12   /**< \brief DMA1通道2全局中断 */
#define INUM_DMA1_3               13   /**< \brief DMA1通道3全局中断 */
#define INUM_DMA1_4               14   /**< \brief DMA1通道4全局中断 */
#define INUM_DMA1_5               15   /**< \brief DMA1通道5全局中断 */
#define INUM_DMA1_6               16   /**< \brief DMA1通道6全局中断 */
#define INUM_DMA1_7               17   /**< \brief DMA1通道7全局中断 */

#define INUM_ADC1_2               18   /**< \brief ADC1和ADC2的全局中断 */
#define INUM_FlASH_CACHE          19   /**< \brief FlashCache中断 */

#define INUM_CAN_RX1              21   /**< \brief CAN接收1中断 */

#define INUM_EXTI9_5              23   /**< \brief EXTI线[9：5]中断 */
#define INUM_TIM1_BRK             24   /**< \brief TIM1刹车中断 */
#define INUM_TIM1_UP              25   /**< \brief TIM1更新中断 */
#define INUM_TIM1_TRG_COM         26   /**< \brief TIM1触发和通信中断 */
#define INUM_TIM1_CC              27   /**< \brief TIM1捕获比较中断 */
#define INUM_TIM2                 28   /**< \brief TIM2全局中断 */
#define INUM_TIM3                 29   /**< \brief TIM3全局中断 */
#define INUM_TIM4                 30   /**< \brief TIM14全局中断 */

#define INUM_I2C1_EV              31   /**< \brief I2C1事件中断 */

#define INUM_I2C2_EV              33   /**< \brief I2C2事件中断 */

#define INUM_SPI1                 35   /**< \brief SPI1全局中断 */
#define INUM_SPI2                 36   /**< \brief SPI2全局中断 */

#define INUM_UART1                37   /**< \brief UART1全局中断 */
#define INUM_UART2                38   /**< \brief UART2全局中断 */
#define INUM_UART3                39   /**< \brief UART3全局中断 */

#define INUM_EXTI15_10            40   /**< \brief EXTI线[15：10]中断 */
#define INUM_RTC_ALARM            41   /**< \brief 连到EXTI17的RTC闹钟中断 */
#define INUM_USB_WK               42   /**< \brief 连到EXTI18的从USB待机唤醒中断 */

#define INUM_TIM8_BRK             43   /**< \brief TIM8刹车中断 */
#define INUM_TIM8_UP              44   /**< \brief TIM8更新中断 */
#define INUM_TIM8_TRG_COM         45   /**< \brief TIM8 触发、更新中断 */
#define INUM_TIM8_CC              46   /**< \brief TIM8捕获比较中断 */

#define INUM_SDIO                 49   /**< \brief SDIO全局中断 */
#define INUM_TIM5                 50   /**< \brief TIM5全局中断 */
#define INUM_SPI3                 51   /**< \brief SPI3全局中断 */
#define INUM_UART4                52   /**< \brief UART4全局中断 */
#define INUM_UART5                53   /**< \brief UART5全局中断 */
#define INUM_TIM6                 54   /**< \brief TIM6全局中断 */
#define INUM_TIM7                 55   /**< \brief TIM7全局中断 */
#define INUM_DMA2_1               56   /**< \brief DMA2通道1全局中断 */
#define INUM_DMA2_2               57   /**< \brief DMA2通道2全局中断 */
#define INUM_DMA2_3               58   /**< \brief DMA2通道3全局中断 */
#define INUM_DMA2_4               59   /**< \brief DMA2通道4全局中断 */
#define INUM_DMA2_5               60   /**< \brief DMA2通道5全局中断 */

#define INUM_COMP1_2              64   /**< \brief 连接EXTI的比较器1/2中断 */

#define INUM_USB_FS               67   /**< \brief USB_FS全局中断 */

#define INUM_UART6                71   /**< \brief UART6全局中断 */

#define INUM_UART7                82   /**< \brief UART7全局中断 */
#define INUM_UART8                83   /**< \brief UART8全局中断 */

/** @} */

/**
 * \brief 最大中断号为： INUM_UART6
 */
#define INUM_INTERNAL_MAX        INUM_UART6

/** \brief 最小中断号: INUM_WWDT */
#define INUM_INTERNAL_MIN        INUM_WWDG_IWDG

/**
 * \brief 总中断数为：(INUM_INTERNAL_MAX - INUM_INTERNAL_MIN + 1),
 *
 */
#define INUM_INTERNAL_COUNT     (INUM_INTERNAL_MAX - INUM_INTERNAL_MIN + 1)


/**
 * \cond
 * 中断号定义，为 core_cm3.h文件保留
 */
typedef enum {

    /* ----------------------  Cortex-M3核异常号  ------------------- */

    /** \brief 2  不可屏蔽中断, 不能被停止或抢占 */
    NonMaskableInt_IRQn      = -14,

    /** \brief 3  硬件错误中断 */
    HardFault_IRQn           = -13,

    /** \brief 11  系统服务调用通过SVC指令 */
    SVCall_IRQn              =  -5,

    /** \brief 14  系统的挂起请求 */
    PendSV_IRQn              =  -2,

    /** \brief 15  系统滴答定时器 */
    SysTick_IRQn             =  -1,

    /******  ZMF159 Specific Interrupt Numbers *******************************************************/
    WWDG_IWDG_IRQn            =0,         /**< \brief 看门狗定时器中断 */
    PVD_IRQn                  =1,         /**< \brief 电源电压检测中断 */
    TAMPER_IRQn               =2,         /**< \brief 侵入检测中断 */
    RTC_IRQn                  =3,         /**< \brief 实时时钟（RTC）全局中断 */
    FLASH_IRQn                =4,         /**< \brief 闪存全局中断 */
    RCC_IRQn                  =5,         /**< \brief 复位和时钟控制（RCC）中断 */
    EXTI0_IRQn                =6,         /**< \brief EXTI线0中断 */
    EXTI1_IRQn                =7,         /**< \brief EXTI线1中断 */
    EXTI2_IRQn                =8,         /**< \brief EXTI线2中断 */
    EXTI3_IRQn                =9,         /**< \brief EXTI线3中断 */
    EXTI4_IRQn                =10,        /**< \brief EXTI线4中断 */
    DMA1_1_IRQn               =11,        /**< \brief DMA1通道1全局中断 */
    DMA1_2_IRQn               =12,        /**< \brief DMA1通道2全局中断 */
    DMA1_3_IRQn               =13,        /**< \brief DMA1通道3全局中断 */
    DMA1_4_IRQn               =14,        /**< \brief DMA1通道4全局中断 */
    DMA1_5_IRQn               =15,        /**< \brief DMA1通道5全局中断 */
    DMA1_6_IRQn               =16,        /**< \brief DMA1通道6全局中断 */
    DMA1_7_IRQn               =17,        /**< \brief DMA1通道7全局中断 */
    ADC1_2_IRQn               =18,        /**< \brief ADC1的全局中断 */
    FlASH_CACHE_IRQn          =19,        /**< \brief FlASH_CACHE中断 */
    Reserved0                 =20,        /**< \brief RESERVED */
    CAN_RX1_IRQn              =21,        /**< \brief CAN接收1中断 */
    Reserved1                 =22,        /**< \brief RESERVED */
    EXTI9_5_IRQn              =23,        /**< \brief EXTI线[9：5]中断 */
    TIM1_BRK_IRQn             =24,        /**< \brief TIM1断开中断 */
    TIM1_UP_IRQn              =25,        /**< \brief TIM1更新中断 */
    TIM1_TRG_COM_IRQn         =26,        /**< \brief TIM1触发和通信中断 */
    TIM1_CC_IRQn              =27,        /**< \brief TIM1捕获比较中断 */
    TIM2_IRQn                 =28,        /**< \brief TIM2全局中断 */
    TIM3_IRQn                 =29,        /**< \brief TIM3全局中断 */
    TIM4_IRQn                 =30,        /**< \brief TIM14全局中断 */
    I2C1_EV_IRQn              =31,        /**< \brief I2C1事件中断 */
    Reserved2                 =32,        /**< \brief RESERVED */
    I2C2_EV_IRQn              =33,        /**< \brief I2C1事件中断 */
    Reserved3                 =34,        /**< \brief RESERVED */
    SPI1_IRQn                 =35,        /**< \brief SPI1全局中断 */
    SPI2_IRQn                 =36,        /**< \brief SPI2全局中断 */
    UART1_IRQn                =37,        /**< \brief UART1全局中断 */
    UART2_IRQn                =38,        /**< \brief UART2全局中断 */
    UART3_IRQn                =39,        /**< \brief UART3全局中断 */
    EXTI15_10_IRQn            =40,        /**< \brief EXTI线[15：10]中断 */
    RTCAlarm_IRQn             =41,        /**< \brief 连到EXTI17的RTC闹钟中断 */
    USB_WK_IRQn               =42,        /**< \brief 连到EXTI18的从USB待机唤醒中断 */
    TIM8_BRK_IRQn             =43,        /**< \brief TIM8刹车中断 */
    TIM8_UP_IRQn              =44,        /**< \brief TIM8更新中断 */
    TIM8_TRG_COM_IRQn         =45,        /**< \brief TIM8 触发、更新中断 */
    TIM8_CC_IRQn              =46,        /**< \brief TIM8捕获比较中断 */
    Reserved4                 =47,        /**< \brief RESERVED */
    Reserved5                 =48,        /**< \brief RESERVED */
    SDIO_IRQn                 =49,        /**< \brief SDIO全局中断 */
    TIM5_IRQn                 =50,        /**< \brief TIM5全局中断 */
    SPI3_IRQn                 =51,        /**< \brief SPI3全局中断 */
    UART4_IRQn                =52,        /**< \brief UART4全局中断 */
    UART5_IRQn                =53,        /**< \brief UART5全局中断 */
    TIM6_IRQn                 =54,        /**< \brief TIM6全局中断 */
    TIM7_IRQn                 =55,        /**< \brief TIM7全局中断 */
    DMA2_CH1_IRQn             =56,        /**< \brief DMA通道1全局中断 */
    DMA2_CH2_IRQn             =57,        /**< \brief DMA通道2全局中断 */
    DMA2_CH3_IRQn             =58,        /**< \brief DMA通道3全局中断 */
    DMA2_CH4_IRQn             =59,        /**< \brief DMA通道4全局中断 */
    DMA2_CH5_IRQn             =60,        /**< \brief DMA通道5全局中断 */
    Reserved6                 =61,        /**< \brief RESERVED */
    Reserved7                 =62,        /**< \brief RESERVED */
    Reserved8                 =63,        /**< \brief RESERVED */
    COMP1_2_IRQn              =64,        /**< \brief 连接EXTI的比较器1/2中断 */
    Reserved9                 =65,        /**< \brief RESERVED */
    Reserved10                =66,        /**< \brief RESERVED */
    USB_FS_IRQn               =67,        /**< \brief USB_FS全局中断 */
    Reserved11                =68,        /**< \brief RESERVED */
    Reserved12                =69,        /**< \brief RESERVED */
    Reserved13                =70,        /**< \brief RESERVED */
    UART6_IRQn                =71,        /**< \brief UART6全局中断 */
    Reserved14                =72,        /**< \brief RESERVED */
    Reserved15                =73,        /**< \brief RESERVED */
    Reserved16                =74,        /**< \brief RESERVED */
    Reserved17                =75,        /**< \brief RESERVED */
    Reserved18                =76,        /**< \brief RESERVED */
    Reserved19                =77,        /**< \brief RESERVED */
    Reserved20                =78,        /**< \brief RESERVED */
    Reserved21                =79,        /**< \brief RESERVED */
    Reserved22                =80,        /**< \brief RESERVED */
    Reserved23                =81,        /**< \brief RESERVED */
    UART7_IRQn                =82,        /**< \brief UART7全局中断 */
    UART8_IRQn                =83         /**< \brief UART8全局中断 */

} IRQn_Type;

/**
 * \endcond
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZMF159_INUM_H */

/* end of file */
