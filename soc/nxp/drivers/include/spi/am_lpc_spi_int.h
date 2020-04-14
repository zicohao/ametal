/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief SPI drivers for standard interface 
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-15  jon, first implementation.
 * \endinternal
 */

#ifndef __AM_LPC_SPI_INT_H
#define __AM_LPC_SPI_INT_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"    
#include "am_spi.h"
#include "hw/amhw_lpc_spi.h"
#include "am_int.h"

/**
 * \addtogroup am_lpc_if_spi_int
 * \copydoc am_lpc_spi_int.h
 * @{
 */
 
/**
 * \brief SPI 设备信息结构体
 */
typedef struct am_lpc_spi_int_devinfo {
    uint32_t           spi_regbase;       /**< \brief SPI寄存器块的基地址 */
    uint16_t           inum;              /**< \brief SPI 中断编号    */
    uint32_t           clk_id;            /**< \brief SPI clk id */

    /** \brief SPI平台初始化函数，如打开时钟，配置引脚等工作 */
    void     (*pfn_plfm_init)(void);

    /** \brief SPI平台解初始化函数 */
    void     (*pfn_plfm_deinit)(void);

} am_lpc_spi_int_devinfo_t;

/**
 * \brief SPI 设备
 */
typedef struct am_lpc_spi_int_dev {

    am_spi_serv_t              spi_serve;       /**< \brief SPI标准服务句柄.   */
    const am_lpc_spi_int_devinfo_t *p_devinfo;  /**< \brief SPI设备信息的指针. */

    struct am_list_head        msg_list;        /**< \brief SPI控制器消息队列 . */

    /** \brief 指向SPI消息结构体的指针,同一时间只能处理一个消息 */
    am_spi_message_t          *p_cur_msg;

    /** \brief 指向SPI传输结构体的指针,同一时间只能处理一个传输 */
    am_spi_transfer_t         *p_cur_trans;

    am_spi_device_t           *p_cur_spi_dev;   /**< \brief 当前传输的SPI设备. */
    am_spi_device_t           *p_tgl_dev;       /**< \brief 当前自锁的SPI设备. */

    uint32_t                   nbytes_to_recv;  /**< \brief 待接收的字节数.    */
    uint32_t                   data_ptr;        /**< \brief 数据传输计数.      */

    am_bool_t                  busy;            /**< \brief SPI忙标识.        */
    uint32_t                   state;           /**< \brief SPI控制器状态机状态. */

} am_lpc_spi_int_dev_t;

/**
 * \brief SPI 初始化
 *
 * \param[in] p_dev     : 指向SPI设备结构体的指针
 * \param[in] p_devinfo : 指向SPI设备信息结构体的指针
 *
 * \return SPI标准服务操作句柄
 */
am_spi_handle_t am_lpc_spi_int_init (am_lpc_spi_int_dev_t           *p_dev,
                                          const am_lpc_spi_int_devinfo_t *p_devinfo);

/**
 * \brief 解除SPI初始化
 * \param[in] handle : SPI标准服务操作句柄
 * \return 无
 */
void am_lpc_spi_int_deinit (am_spi_handle_t handle);




/** 
 * @} am_lpc_if_spi_int
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LPC_SPI_INT_H */

/*end of file */
