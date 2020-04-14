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
 * \brief MicroPort RS485 用户配置文件
 * \sa am_hwconf_microport_rs485.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-16  pea, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "am_zmf159.h"
#include "am_zlg_uart.h"

/**
 * \addtogroup am_if_src_hwconf_microport_rs485
 * \copydoc am_hwconf_microport_rs485.c
 * @{
 */

/** \brief RS485方向控制引脚 */
#define __MICROPORT_RS485_DIR_PIN    PIOC_2

/**
 * \brief RS485 方向控制函数
 *
 * \param[in] is_txmode AM_TRUE: 发送模式， AM_FALSE: 接收模式
 */
void __microport_rs485_dir (am_bool_t is_txmode)
{
    am_gpio_set(__MICROPORT_RS485_DIR_PIN, (int)is_txmode);
}

/** \brief MicroPort RS485平台初始化 */
am_local void __microport_rs485_plfm_init (void)
{
    am_gpio_pin_cfg(PIOA_9,  PIOA_9_UART1_TX | PIOA_9_AF_PP);
    am_gpio_pin_cfg(PIOA_10, PIOA_10_UART1_RX| PIOA_10_INPUT_FLOAT);

    am_gpio_pin_cfg(__MICROPORT_RS485_DIR_PIN, AM_GPIO_OUTPUT_INIT_LOW);
}

/** \brief MicroPort RS485 设备信息 */
static const am_zlg_uart_devinfo_t __g_microport_rs485_devinfo = {

    ZMF159_UART1_BASE,            /**< \brief 串口1 */
    INUM_UART1,                   /**< \brief 串口1的中断编号 */
    CLK_UART1,                    /**< \brief 串口1的时钟 */

    AMHW_ZLG_UART_DATA_8BIT |  /**< \brief 8位数据 */
    AMHW_ZLG_UART_PARITY_NO |  /**< \brief 无极性 */
    AMHW_ZLG_UART_STOP_1BIT,   /**< \brief 1个停止位 */

    115200,                       /**< \brief 设置的波特率 */

    0,                            /**< \brief 无其他中断 */

    __microport_rs485_dir,        /**< \brief UART1使用RS485 */
    __microport_rs485_plfm_init,  /**< \brief UART1的平台初始化函数 */
    (void (*)(void))-1,           /**< \brief 无平台去初始化函数 */
};

/** \brief 定义MicroPort RS485 设备 */
am_local am_zlg_uart_dev_t __g_microport_rs485_dev;

/** \brief MicroPort RS485 实例初始化，获得 UART 标准服务句柄 */
am_uart_handle_t am_microport_rs485_inst_init (void)
{
    am_uart_handle_t handle;
    handle = am_zlg_uart_init(&__g_microport_rs485_dev,
                                 &__g_microport_rs485_devinfo);
    if (NULL != handle) {
        am_uart_ioctl(handle, AM_UART_RS485_SET, (void *)AM_TRUE);
    }

    return handle;
}

/**
 * @}
 */

/* end of file */
