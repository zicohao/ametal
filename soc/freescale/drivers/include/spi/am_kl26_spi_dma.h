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
 * \brief SPI驱动，服务SPI标准接口
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-23  sky, modified.
 * - 1.00 15-07-07  aii, first implementation.
 * \endinternal
 */

#ifndef __AM_KL26_SPI_DMA_H
#define __AM_KL26_SPI_DMA_H

#include "am_types.h"
#include "am_spi.h"
#include "am_int.h"
#include "am_kl26_dma.h"
#include "hw/amhw_kl26_dma.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_kl26_if_spi_dma
 * \copydoc am_kl26_spi_dma.h
 * @{
 */

/** \brief 停止模式SPI继续工作 */
#define AM_KL26_SPI_DMA_CFG_WIAT_EN        (AM_BIT(28) | AM_SBF(0,3))

/** \brief 停止模式SPI不工作 */
#define AM_KL26_SPI_DMA_CFG_WIAT_DIS       (AM_BIT(28) | AM_SBF(1,3))

/**
 * \brief SPI 设备信息结构体
 */
typedef struct am_kl26_spi_dma_devinfo {
    uint32_t          spi_regbase;       /**< \brief SPI寄存器块的基地址 */
    uint32_t          flags;             /**< \brief SPI 配置标识  */

    uint32_t          dma_chan_tx;       /**< \brief DMA发送通道号 */
    uint32_t          dma_chan_rx;       /**< \brief DMA接收通道号 */
    uint32_t          dma_src_tx;  /**< \brief DMA发送源 */
    uint32_t          dma_src_rx;  /**< \brief DMA接收源 */

    /** \brief SPI平台初始化函数，如打开时钟，配置引脚等工作 */
    void     (*pfn_plfm_init)(void);

    /** \brief SPI平台解初始化函数 */
    void     (*pfn_plfm_deinit)(void);

} am_kl26_spi_dma_devinfo_t;

/**
 * \brief SPI 设备
 */
typedef struct am_kl26_spi_dma_dev {

    am_spi_serv_t                  spi_serve;   /**< \brief SPI标准服务句柄 */
    const am_kl26_spi_dma_devinfo_t   *p_devinfo;   /**< \brief SPI设备信息的指针 */

    struct am_list_head        msg_list;        /**< \brief SPI控制器消息队列 */

    /** \brief 指向SPI消息结构体的指针,同一时间只能处理一个消息 */
    am_spi_message_t          *p_cur_msg;

    /** \brief 指向SPI传输结构体的指针,同一时间只能处理一个传输 */
    am_spi_transfer_t         *p_cur_trans;

    am_spi_device_t           *p_cur_spi_dev;   /**< \brief 当前传输的SPI设备 */
    am_spi_device_t           *p_tgl_dev;       /**< \brief 当前自锁的SPI设备 */

    uint32_t                   nbytes_to_recv;  /**< \brief 待接收的字节数 */
    uint32_t                   data_ptr;        /**< \brief 数据传输计数 */

    am_bool_t                     busy;            /**< \brief SPI忙标识 */
    uint32_t                   state;           /**< \brief SPI控制器状态机状态 */

    uint16_t                   tx_rx_trash;

    __attribute__((aligned(16)))
    amhw_kl26_dma_xfer_desc_t       g_desc[2];  /**< \brief DMA通道描述符 */

} am_kl26_spi_dma_dev_t;

/**
 * \brief SPI 初始化
 *
 * \param[in] p_dev     : 指向SPI设备结构体的指针
 * \param[in] p_devinfo : 指向SPI设备信息结构体的指针
 *
 * \return SPI标准服务操作句柄
 */
am_spi_handle_t am_kl26_spi_dma_init (am_kl26_spi_dma_dev_t           *p_dev,
                                      const am_kl26_spi_dma_devinfo_t *p_devinfo);

/**
 * \brief 解除SPI初始化
 * \param[in] handle : SPI标准服务操作句柄
 * \return 无
 */
void am_kl26_spi_dma_deinit (am_spi_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_KL26_SPI_DMA_H */

/*end of file */
