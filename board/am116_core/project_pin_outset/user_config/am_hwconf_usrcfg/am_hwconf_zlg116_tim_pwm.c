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
 * \brief TIM用于PWM输出 用户配置文件
 * \sa am_hwconf_zlg116_tim_pwm.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-24  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg116.h"
#include "am_gpio.h"
#include "am_zlg_tim_pwm.h"
#include "am_clk.h"
#include "am_zlg116_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg116_tim_pwm
 * \copydoc am_hwconf_zlg116_tim_pwm.c
 * @{
 */

/*******************************************************************************
 * TIM1 配置
 ******************************************************************************/

/** \brief TIM1用于PWM输出 平台初始化 */
static void __zlg_plfm_tim1_pwm_init (void)
{
    /* 使能高级定时器1时钟 */
    am_clk_enable(CLK_TIM1);

    /* 复位高级定时器1 */
    am_zlg116_clk_reset(CLK_TIM1);
}

/** \brief 解除TIM1平台初始化 */
static void __zlg_plfm_tim1_pwm_deinit (void)
{
    /* 复位高级定时器1 */
    am_zlg116_clk_reset(CLK_TIM1);

    /* 禁能高级定时器1时钟 */
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1用于PWM功能的通道配置信息列表 */
static am_zlg_tim_pwm_chaninfo_t __g_tim1_pwm_chaninfo_list[] = {
    /** \brief 通道1引脚配置 */
    {AM_ZLG_TIM_PWM_CH1, __TIM1_CH1_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief 通道1互补引脚配置 */
    {AM_ZLG_TIM_PWM_CH1N, __TIM1_CH1N_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief 通道2引脚配置 */
    {AM_ZLG_TIM_PWM_CH2, __TIM1_CH2_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief 通道2互补引脚配置 */
    {AM_ZLG_TIM_PWM_CH2N, __TIM1_CH2N_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief 通道3引脚配置 */
    {AM_ZLG_TIM_PWM_CH3, __TIM1_CH3_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief 通道3互补引脚配置 */
    {AM_ZLG_TIM_PWM_CH3N, __TIM1_CH3N_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief 通道4引脚配置 */
    {AM_ZLG_TIM_PWM_CH4, __TIM1_CH4_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
};

/** \brief TIM1用于PWM设备信息 */
static const am_zlg_tim_pwm_devinfo_t  __g_tim1_pwm_devinfo = {
    ZLG116_TIM1_BASE,                          /**< \brief TIM1寄存器块的基地址    */
    CLK_TIM1,                                  /**< \brief TIM1时钟ID              */
    AM_NELEMENTS(__g_tim1_pwm_chaninfo_list),  /**< \brief 配置输出通道个数        */
    AMHW_ZLG_TIM_PWM_MODE2,                    /**< \brief PWM输出模式2            */
    0,                                         /**< \brief PWM输出高电平有效       */
    &__g_tim1_pwm_chaninfo_list[0],            /**< \brief 通道配置信息列表        */
    AMHW_ZLG_TIM_TYPE0,                        /**< \brief 定时器类型              */
    __zlg_plfm_tim1_pwm_init,                  /**< \brief 平台初始化函数          */
    __zlg_plfm_tim1_pwm_deinit                 /**< \brief 平台解初始化函数        */
};

/** \brief TIM1用于PWM设备定义 */
static am_zlg_tim_pwm_dev_t  __g_tim1_pwm_dev;
static am_pwm_handle_t       __g_tim1_pwm_handle = NULL;

/** \brief tim1 pwm 实例初始化，获得pwm标准服务句柄 */
am_pwm_handle_t am_zlg116_tim1_pwm_inst_init (void)
{
    if (__g_tim1_pwm_handle == NULL) {
        __g_tim1_pwm_handle = am_zlg_tim_pwm_init(&__g_tim1_pwm_dev,
                                                  &__g_tim1_pwm_devinfo);
    }
    
    return __g_tim1_pwm_handle;
}

/** \brief tim1 pwm 实例解初始化 */
void am_zlg116_tim1_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim1_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim1_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM2 配置
 ******************************************************************************/

/** \brief TIM2用于PWM输出 平台初始化 */
static void __zlg_plfm_tim2_pwm_init (void)
{
    /* 使能通用定时器2时钟 */
    am_clk_enable(CLK_TIM2);

    /* 复位通用定时器2 */
    am_zlg116_clk_reset(CLK_TIM2);
}

/** \brief 解除TIM2平台初始化 */
static void __zlg_plfm_tim2_pwm_deinit (void)
{
    /* 复位通用定时器2 */
    am_zlg116_clk_reset(CLK_TIM2);

    /* 禁能通用定时器2时钟 */
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2用于PWM功能的通道配置信息列表 */
static am_zlg_tim_pwm_chaninfo_t __g_tim2_pwm_chaninfo_list[] = {
        /** \brief 通道1引脚配置 */
        {AM_ZLG_TIM_PWM_CH1, __TIM2_CH1_ETR_GPIO, __GPIO_TIM2, __PIO_GPIO_TIM},
        /** \brief 通道2引脚配置 */
        {AM_ZLG_TIM_PWM_CH2, __TIM2_CH2_GPIO, __GPIO_TIM2, __PIO_GPIO_TIM},
        /** \brief 通道3引脚配置 */
        {AM_ZLG_TIM_PWM_CH3, __TIM2_CH3_GPIO, __GPIO_TIM2, __PIO_GPIO_TIM},
        /** \brief 通道4引脚配置 */
        {AM_ZLG_TIM_PWM_CH4, __TIM2_CH4_GPIO, __GPIO_TIM2, __PIO_GPIO_TIM},
};

/** \brief TIM2用于PWM设备信息 */
static const am_zlg_tim_pwm_devinfo_t  __g_tim2_pwm_devinfo = {
    ZLG116_TIM2_BASE,                          /**< \brief TIM2寄存器块的基地址    */
    CLK_TIM2,                                  /**< \brief TIM2时钟ID              */
    AM_NELEMENTS(__g_tim2_pwm_chaninfo_list),  /**< \brief 配置输出通道个数        */
    AMHW_ZLG_TIM_PWM_MODE2,                    /**< \brief PWM输出模式2            */
    0,                                         /**< \brief PWM输出高电平有效       */
    &__g_tim2_pwm_chaninfo_list[0],            /**< \brief 通道配置信息列表        */
    AMHW_ZLG_TIM_TYPE1,                        /**< \brief 定时器类型              */
    __zlg_plfm_tim2_pwm_init,                  /**< \brief 平台初始化函数          */
    __zlg_plfm_tim2_pwm_deinit                 /**< \brief 平台解初始化函数        */
};

/** \brief TIM2 用于PWM设备定义 */
static am_zlg_tim_pwm_dev_t  __g_tim2_pwm_dev;
static am_pwm_handle_t       __g_tim2_pwm_handle = NULL;

/** \brief tim2 pwm实例初始化，获得pwm标准服务句柄 */
am_pwm_handle_t am_zlg116_tim2_pwm_inst_init (void)
{
    if (__g_tim2_pwm_handle == NULL) {
        __g_tim2_pwm_handle = am_zlg_tim_pwm_init(&__g_tim2_pwm_dev,
                                                  &__g_tim2_pwm_devinfo);
    }
    
    return __g_tim2_pwm_handle;
}

/** \brief tim2 pwm实例解初始化 */
void am_zlg116_tim2_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim2_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim2_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM3 配置
 ******************************************************************************/

/** \brief TIM3用于PWM输出 平台初始化 */
static void __zlg_plfm_tim3_pwm_init (void)
{
    /* 使能通用定时器3时钟 */
    am_clk_enable(CLK_TIM3);

    /* 复位通用定时器3 */
    am_zlg116_clk_reset(CLK_TIM3);
}

/** \brief 解除TIM3 PWM平台初始化 */
static void __zlg_plfm_tim3_pwm_deinit (void)
{
    /* 复位通用定时器3 */
    am_zlg116_clk_reset(CLK_TIM3);

    /* 禁能通用定时器3时钟 */
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3用于PWM功能的通道配置信息列表 */
static am_zlg_tim_pwm_chaninfo_t __g_tim3_pwm_chaninfo_list[] = {
    /** \brief 通道1引脚配置 */
    {AM_ZLG_TIM_PWM_CH1, __TIM3_CH1_GPIO,  __GPIO_TIM3, __PIO_GPIO_TIM},
    /** \brief 通道2引脚配置 */
    {AM_ZLG_TIM_PWM_CH2, __TIM3_CH2_GPIO,  __GPIO_TIM3, __PIO_GPIO_TIM},
    /** \brief 通道3引脚配置 */
    {AM_ZLG_TIM_PWM_CH3, __TIM3_CH3_GPIO,  __GPIO_TIM3, __PIO_GPIO_TIM},
    /** \brief 通道4引脚配置 */
    {AM_ZLG_TIM_PWM_CH4, __TIM3_CH4_GPIO,  __GPIO_TIM3, __PIO_GPIO_TIM},
};

/** \brief TIM3用于PWM设备信息 */
static const am_zlg_tim_pwm_devinfo_t  __g_tim3_pwm_devinfo = {
    ZLG116_TIM3_BASE,                          /**< \brief TIM3寄存器块的基地址    */
    CLK_TIM3,                                  /**< \brief TIM3时钟ID              */
    AM_NELEMENTS(__g_tim3_pwm_chaninfo_list),  /**< \brief 配置输出通道个数        */
    AMHW_ZLG_TIM_PWM_MODE2,                    /**< \brief PWM输出模式2            */
    0,                                         /**< \brief PWM输出高电平有效       */
    &__g_tim3_pwm_chaninfo_list[0],            /**< \brief 通道配置信息列表        */
    AMHW_ZLG_TIM_TYPE1,                        /**< \brief 定时器类型              */
    __zlg_plfm_tim3_pwm_init,                  /**< \brief 平台初始化函数          */
    __zlg_plfm_tim3_pwm_deinit                 /**< \brief 平台解初始化函数        */
};

/** \brief TIM3用于PWM设备定义 */
static am_zlg_tim_pwm_dev_t  __g_tim3_pwm_dev;
static am_pwm_handle_t       __g_tim3_pwm_handle = NULL;

/** \brief tim3 pwm实例初始化，获得PWM标准服务句柄 */
am_pwm_handle_t am_zlg116_tim3_pwm_inst_init (void)
{
    if (__g_tim3_pwm_handle == NULL) {
        __g_tim3_pwm_handle = am_zlg_tim_pwm_init(&__g_tim3_pwm_dev,
                                                  &__g_tim3_pwm_devinfo);
    }
    return __g_tim3_pwm_handle;
}

/** \brief tim3 pwm 实例解初始化 */
void am_zlg116_tim3_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim3_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim3_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM14配置
 ******************************************************************************/

/** \brief TIM14用于PWM输出 平台初始化 */
static void __zlg_plfm_tim14_pwm_init (void)
{
    /* 使能通用定时器14时钟 */
    am_clk_enable(CLK_TIM14);

    /* 复位通用定时器14 */
    am_zlg116_clk_reset(CLK_TIM14);
}

/** \brief 解除TIM14 PWM平台初始化 */
static void __zlg_plfm_tim14_pwm_deinit (void)
{
    /* 复位通用定时器14 */
    am_zlg116_clk_reset(CLK_TIM14);

    /* 禁能通用定时器14时钟 */
    am_clk_disable(CLK_TIM14);
}

/** \brief TIM14用于PWM功能的通道配置信息列表 */
static am_zlg_tim_pwm_chaninfo_t __g_tim14_pwm_chaninfo_list[] = {
    /** \brief 通道1引脚配置 */
    {AM_ZLG_TIM_PWM_CH1, __TIM14_CH1_GPIO,  __GPIO_TIM14, AM_GPIO_INPUT | AM_GPIO_FLOAT},
};

/** \brief TIM14用于PWM设备信息 */
static const am_zlg_tim_pwm_devinfo_t  __g_tim14_pwm_devinfo = {
    ZLG116_TIM14_BASE,                          /**< \brief TIM14寄存器块的基地址   */
    CLK_TIM14,                                  /**< \brief TIM14时钟ID             */
    AM_NELEMENTS(__g_tim14_pwm_chaninfo_list) , /**< \brief 配置输出通道个数        */
    AMHW_ZLG_TIM_PWM_MODE2,                     /**< \brief PWM输出模式2            */
    0,                                          /**< \brief PWM输出高电平有效       */
    &__g_tim14_pwm_chaninfo_list[0],            /**< \brief 通道配置信息列表        */
    AMHW_ZLG_TIM_TYPE2,                         /**< \brief 定时器类型              */
    __zlg_plfm_tim14_pwm_init,                  /**< \brief 平台初始化函数          */
    __zlg_plfm_tim14_pwm_deinit                 /**< \brief 平台解初始化函数        */
};

/** \brief TIM14用于PWM设备定义 */
static am_zlg_tim_pwm_dev_t  __g_tim14_pwm_dev;
static am_pwm_handle_t       __g_tim14_pwm_handle = NULL;

/** \brief tim14 pwm实例初始化，获得PWM标准服务句柄 */
am_pwm_handle_t am_zlg116_tim14_pwm_inst_init (void)
{
    if (__g_tim14_pwm_handle == NULL) {
        __g_tim14_pwm_handle = am_zlg_tim_pwm_init(&__g_tim14_pwm_dev,
                                                   &__g_tim14_pwm_devinfo);
    }
    return __g_tim14_pwm_handle;
}

/** \brief tim14 pwm实例解初始化 */
void am_zlg116_tim14_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim14_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim14_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM16配置
 ******************************************************************************/

/** \brief TIM16用于PWM输出 平台初始化 */
static void __zlg_plfm_tim16_pwm_init (void)
{
    /* 使能通用定时器16时钟 */
    am_clk_enable(CLK_TIM16);

    /* 复位通用定时器16 */
    am_zlg116_clk_reset(CLK_TIM16);

}

/** \brief 解除TIM16 PWM平台初始化 */
static void __zlg_plfm_tim16_pwm_deinit (void)
{
    /* 复位通用定时器16 */
    am_zlg116_clk_reset(CLK_TIM16);

    /* 禁能通用定时器16时钟 */
    am_clk_disable(CLK_TIM16);
}


/** \brief TIM16用于PWM功能的通道配置信息列表 */
static am_zlg_tim_pwm_chaninfo_t __g_tim16_pwm_chaninfo_list[] = {
    /** \brief 通道1引脚配置 */
    {AM_ZLG_TIM_PWM_CH1, __TIM16_CH1_GPIO, __GPIO_TIM16_CH1, AM_GPIO_INPUT | AM_GPIO_FLOAT},
    /** \brief 通道1互补引脚配置 */
    {AM_ZLG_TIM_PWM_CH1N, __TIM16_CH1N_GPIO, __GPIO_TIM16_CH1N, AM_GPIO_INPUT | AM_GPIO_FLOAT},
};

/** \brief TIM16用于PWM设备信息 */
static const am_zlg_tim_pwm_devinfo_t  __g_tim16_pwm_devinfo = {
    ZLG116_TIM16_BASE,                          /**< \brief TIM16寄存器块的基地址   */
    CLK_TIM16,                                  /**< \brief TIM16时钟ID             */
    AM_NELEMENTS(__g_tim16_pwm_chaninfo_list),  /**< \brief 配置输出通道个数        */
    AMHW_ZLG_TIM_PWM_MODE2,                     /**< \brief PWM输出模式2            */
    0,                                          /**< \brief PWM输出高电平有效       */
    &__g_tim16_pwm_chaninfo_list[0],            /**< \brief 通道配置信息列表        */
    AMHW_ZLG_TIM_TYPE3,                         /**< \brief 定时器类型              */
    __zlg_plfm_tim16_pwm_init,                  /**< \brief 平台初始化函数          */
    __zlg_plfm_tim16_pwm_deinit                 /**< \brief 平台解初始化函数        */
};

/** \brief TIM16用于PWM设备定义 */
static am_zlg_tim_pwm_dev_t __g_tim16_pwm_dev;
static am_pwm_handle_t      __g_tim16_pwm_handle = NULL;

/** \brief tim16 pwm实例初始化，获得PWM标准服务句柄 */
am_pwm_handle_t am_zlg116_tim16_pwm_inst_init (void)
{
    if (__g_tim16_pwm_handle == NULL) {
        __g_tim16_pwm_handle = am_zlg_tim_pwm_init(&__g_tim16_pwm_dev,
                                                   &__g_tim16_pwm_devinfo);
    }

    return __g_tim16_pwm_handle;
}

/** \brief tim16 pwm实例解初始化 */
void am_zlg116_tim16_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim16_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim16_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM17配置
 ******************************************************************************/

/** \brief TIM17用于PWM输出 平台初始化 */
static void __zlg_plfm_tim17_pwm_init (void)
{
    /* 使能通用定时器17时钟 */
    am_clk_enable(CLK_TIM17);

    /* 复位通用定时器17 */
    am_zlg116_clk_reset(CLK_TIM17);
}

/** \brief 解除TIM17 PWM平台初始化 */
static void __zlg_plfm_tim17_pwm_deinit (void)
{
    /* 复位通用定时器17 */
    am_zlg116_clk_reset(CLK_TIM17);

    /* 禁能通用定时器17时钟 */
    am_clk_disable(CLK_TIM17);
}

/** \brief TIM17用于PWM功能的通道配置信息列表 */
static am_zlg_tim_pwm_chaninfo_t __g_tim17_pwm_chaninfo_list[] = {
    /** \brief 通道1引脚配置 */
    {AM_ZLG_TIM_PWM_CH1, PIOA_7,  PIOA_7_TIM17_CH1 | PIOA_7_AF_PP, PIOA_7_GPIO | PIOA_7_INPUT_FLOAT},
    /** \brief 通道1互补引脚配置 */
    {AM_ZLG_TIM_PWM_CH1N, PIOB_7, PIOB_7_TIM17_CH1N | PIOB_7_AF_PP, AM_GPIO_INPUT | AM_GPIO_FLOAT},
};

/** \brief TIM17用于PWM设备信息 */
static const am_zlg_tim_pwm_devinfo_t  __g_tim17_pwm_devinfo = {
    ZLG116_TIM17_BASE,                          /**< \brief TIM17寄存器块的基地址   */
    CLK_TIM17,                                  /**< \brief TIM17时钟ID             */
    AM_NELEMENTS(__g_tim17_pwm_chaninfo_list),  /**< \brief 配置输出通道个数        */
    AMHW_ZLG_TIM_PWM_MODE2,                     /**< \brief PWM输出模式2            */
    0,                                          /**< \brief PWM输出高电平有效       */
    &__g_tim17_pwm_chaninfo_list[0],            /**< \brief 通道配置信息列表        */
    AMHW_ZLG_TIM_TYPE3,                         /**< \brief 定时器类型              */
    __zlg_plfm_tim17_pwm_init,                  /**< \brief 平台初始化函数          */
    __zlg_plfm_tim17_pwm_deinit                 /**< \brief 平台解初始化函数        */
};

/** \brief TIM17用于PWM设备定义 */
static am_zlg_tim_pwm_dev_t  __g_tim17_pwm_dev;
static am_pwm_handle_t       __g_tim17_pwm_handle = NULL;

/** \brief tim17 pwm实例初始化，获得PWM标准服务句柄 */
am_pwm_handle_t am_zlg116_tim17_pwm_inst_init (void)
{
    if (__g_tim17_pwm_handle == NULL) {
        __g_tim17_pwm_handle = am_zlg_tim_pwm_init(&__g_tim17_pwm_dev,
                                                   &__g_tim17_pwm_devinfo);
    }
    return __g_tim17_pwm_handle;
}

/** \brief tim17 pwm实例解初始化 */
void am_zlg116_tim17_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim17_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim17_pwm_handle = NULL;
    }
}

/**
 * @}
 */

/* end of file */
