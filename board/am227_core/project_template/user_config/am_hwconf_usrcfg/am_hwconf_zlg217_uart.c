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
 * \brief ZLG217 UART 用户配置文件
 * \sa am_zlg217l_hwconfig_uart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-10  ari, first implementation
 * \endinternal
 */

#include "am_gpio.h"
#include "am_zlg_uart.h"
#include "amhw_zlg_uart.h"
#include "am_clk.h"
#include "am_zlg217.h"
#include "amhw_zlg217_gpio.h"
#include "zlg217_periph_map.h"
#include "amhw_zlg217_rcc.h"
#include "zlg217_pin.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_uart
 * \copydoc am_hwconf_zlg217_uart.c
 * @{
 */

/** \brief 串口1平台初始化 */
static void __zlg217_plfm_uart1_init (void)
{
    am_gpio_pin_cfg(PIOA_9,  PIOA_9_UART1_TX_REMAP0 | PIOA_9_AF_PP );
    am_gpio_pin_cfg(PIOA_10, PIOA_10_UART1_RX_REMAP0| PIOA_10_INPUT_FLOAT);
}

/** \brief 解除串口1平台初始化 */
static void __zlg217_plfm_uart1_deinit (void)
{
    am_clk_disable(CLK_UART1);

    am_gpio_pin_cfg(PIOA_9, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_10,AM_GPIO_INPUT);
}

/** \brief 串口1设备信息 */
static const am_zlg_uart_devinfo_t __g_uart1_devinfo = {

    ZLG217_UART1_BASE,            /**< \brief 串口1 */
    INUM_UART1,                   /**< \brief 串口1的中断编号 */
    CLK_UART1,                    /**< \brief 串口1的时钟 */

    AMHW_ZLG_UART_DATA_8BIT |  /**< \brief 8位数据 */
    AMHW_ZLG_UART_PARITY_NO |  /**< \brief 无极性 */
    AMHW_ZLG_UART_STOP_1BIT,   /**< \brief 1个停止位 */

    115200,                       /**< \brief 设置的波特率 */

    0,                            /**< \brief 无其他中断 */

    NULL,                         /**< \brief UART1使用RS485 */
    __zlg217_plfm_uart1_init,     /**< \brief UART1的平台初始化 */
    __zlg217_plfm_uart1_deinit,   /**< \brief UART1的平台去初始化 */
};

/**< \brief 定义串口1 设备 */
static am_zlg_uart_dev_t  __g_uart1_dev;

/** \brief 串口2平台初始化 */
static void __zlg217_plfm_uart2_init (void)
{
    am_gpio_pin_cfg(PIOA_2, PIOA_2_UART2_TX | PIOA_2_AF_PP|PIOA_3_SPEED_2MHz);
    am_gpio_pin_cfg(PIOA_3, PIOA_3_UART2_RX | PIOA_3_INPUT_FLOAT);
}

/** \brief 解除串口2 平台初始化 */
static void __zlg217_plfm_uart2_deinit (void)
{

    /* 关闭UART2时钟 */
    am_clk_disable(CLK_UART2);

    am_gpio_pin_cfg(PIOA_3, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_2, AM_GPIO_INPUT);
}

/** \brief 串口2 设备信息 */
static const am_zlg_uart_devinfo_t __g_uart2_devinfo = {

    ZLG217_UART2_BASE,              /**< \brief 串口2 */
    INUM_UART2,                     /**< \brief 串口2的中断编号 */
    CLK_UART2,                      /**< \brief 串口2的时钟 */

    AMHW_ZLG_UART_DATA_8BIT |    /**< \brief 8位数据 */
    AMHW_ZLG_UART_PARITY_NO |    /**< \brief 无极性 */
    AMHW_ZLG_UART_STOP_1BIT,     /**< \brief 1个停止位 */

    115200,                         /**< \brief 设置的波特率 */

    0,                              /**< \brief 无其他中断 */

    NULL,                           /**< \brief UART2使用RS485 */
    __zlg217_plfm_uart2_init,       /**< \brief UART2的平台初始化 */
    __zlg217_plfm_uart2_deinit,     /**< \brief UART2的平台去初始化 */
};

/**< \brief 定义串口2设备 */
static am_zlg_uart_dev_t  __g_uart2_dev;

/** \brief 串口3平台初始化 */
static void __zlg217_plfm_uart3_init (void)
{
     am_gpio_pin_cfg(PIOB_10, PIOB_10_UART3_TX_REMAP0 | PIOB_10_AF_PP | PIOB_10_SPEED_10MHz);
     am_gpio_pin_cfg(PIOB_11, PIOB_11_UART3_RX_REMAP0 | PIOB_11_INPUT_FLOAT);
}

/** \brief 解除串口3 平台初始化 */
static void __zlg217_plfm_uart3_deinit (void)
{
    am_clk_disable(CLK_UART3);

    am_gpio_pin_cfg(PIOB_10, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_11, AM_GPIO_INPUT);
}

/** \brief 串口3 设备信息 */
static const am_zlg_uart_devinfo_t __g_uart3_devinfo = {

    ZLG217_UART3_BASE,              /**< \brief 串口3 */
    INUM_UART3,                     /**< \brief 串口2的中断编号 */
    CLK_UART3,                      /**< \brief 串口2的时钟 */

    AMHW_ZLG_UART_DATA_8BIT |    /**< \brief 8位数据 */
    AMHW_ZLG_UART_PARITY_NO |    /**< \brief 无极性 */
    AMHW_ZLG_UART_STOP_1BIT,     /**< \brief 1个停止位 */

    115200,                         /**< \brief 设置的波特率 */

    0,                              /**< \brief 无其他中断 */

    NULL,                           /**< \brief UART3使用RS485 */
    __zlg217_plfm_uart3_init,       /**< \brief UART3的平台初始化 */
    __zlg217_plfm_uart3_deinit,     /**< \brief UART3的平台去初始化 */
};

/**< \brief 定义串口2设备 */
static am_zlg_uart_dev_t  __g_uart3_dev;

/** \brief UART1实例初始化，获得uart1标准服务句柄 */
am_uart_handle_t am_zlg217_uart1_inst_init (void)
{
    return am_zlg_uart_init(&__g_uart1_dev, &__g_uart1_devinfo);
}

/** \brief UART1实例解初始化 */
void am_zlg217_uart1_inst_deinit (am_uart_handle_t handle)
{
    am_zlg_uart_deinit((am_zlg_uart_dev_t *)handle);
}

/** \brief UART2实例初始化，获得uart2标准服务句柄 */
am_uart_handle_t am_zlg217_uart2_inst_init (void)
{
    return am_zlg_uart_init(&__g_uart2_dev, &__g_uart2_devinfo);
}

/** \brief UART2实例解初始化 */
void am_zlg217_uart2_inst_deinit (am_uart_handle_t handle)
{
    am_zlg_uart_deinit((am_zlg_uart_dev_t *)handle);
}

/** \brief UART3实例初始化，获得uart3标准服务句柄 */
am_uart_handle_t am_zlg217_uart3_inst_init (void)
{
    return am_zlg_uart_init(&__g_uart3_dev, &__g_uart3_devinfo);
}

/** \brief UART3实例解初始化 */
void am_zlg217_uart3_inst_deinit (am_uart_handle_t handle)
{
    am_zlg_uart_deinit((am_zlg_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
