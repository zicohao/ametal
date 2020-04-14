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
 * \brief DMA驱动，服务DMA接口
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-23  mkr, first implementation.
 * \endinternal
 */

#ifndef __AMDR_DMA_H
#define __AMDR_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_kl26_dma.h"
#include "../../../kl26/kl26_dmamux_chan.h"

/**
 * \addtogroup am_kl26_if_dma
 * \copydoc am_kl26_dma.h
 * @{
 */

/**
 * \name 通道传输中断标志
 * \anchor am_kl26_dma_chan_cfg_flags
 * @{
 */

/** \brief 完成中断标识 */
#define AM_KL26_DMA_INT_NORMAL         0

/** \brief 错误中断标识 */
#define AM_KL26_DMA_INT_ERROR          1

/** @} */

/** \brief DMA中断回调函数类型 */
typedef void (*am_kl26_pfn_dma_isr_t)(void *p_arg, uint8_t flag);

/** \brief DMA中断回调函数信息 */
struct am_kl26_dma_int_info {

    /** \brief DMA触发回调函数 */
    am_kl26_pfn_dma_isr_t  pfn_isr;

    /** \brief 回调函数的第一个入口参数 */
    void                  *p_arg;
};

/** \brief DMA设备信息 */
typedef struct am_kl26_dma_devinfo {

    /** \brief 指向DMAMUX寄存器块的指针 */
    amhw_kl26_dmamux_t  *p_hw_dmamux;

    /** \brief 指向DMA寄存器块的指针 */
    amhw_kl26_dma_t     *p_hw_dma;

    /** \brief DMA中断号 */
    uint8_t         inum;

    /** \brief 平台初始化函数，如打开时钟，配置引脚等工作 */
    void     (*pfn_plfm_init)(void);

    /** \brief 平台解初始化函数 */
    void     (*pfn_plfm_deinit)(void);

} am_kl26_dma_devinfo_t;

/**
 * \brief DMA设备实例
 */
typedef struct am_kl26_dma_dev {

    /** \brief 指向DMA设备信息的指针 */
    const am_kl26_dma_devinfo_t *p_devinfo;

}am_kl26_dma_dev_t;

/**
 * \brief 配置DMA传输通道
 *
 * \param[in] chan  : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0)
 * \param[in] flags : 触发使能位以及对应通道的请求源设置
 *                    有对应的宏定义
 *
 * \retval AM_OK    : 配置成功
 * \retval AM_ERROR : 配置错误，该通道之前配置过
 */
int am_kl26_dma_chan_cfg(int chan, uint8_t flags);

/**
 * \brief 停止通道传输
 * \param[in] chan : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0) 或
 *
 * \retval AM_OK   : 操作成功
 */
int am_kl26_dma_chan_stop(int chan);

/**
 * \brief 建立传输描述符
 *
 * \param[in] p_desc   : 指向DMA传输描述符的指针
 * \param[in] src_addr : 源端首地址
 * \param[in] dst_addr : 目标端首地址
 * \param[in] nbytes   : 传输字节数
 * \param[in] flags    : 配置参数
 *
 * \retval  AM_OK      : 建立成功
 * \retval -AM_EINVAL  : 未对齐，无效参数
 */
int am_kl26_dma_xfer_desc_build (amhw_kl26_dma_xfer_desc_t *p_desc,
                                 uint32_t                   src_addr,
                                 uint32_t                   dst_addr,
                                 uint32_t                   nbytes,
                                 uint32_t                   flags);

/**
 * \brief 设置目的地址缓冲区大小
 *
 * \param[in] size     : 枚举体定义 ，缓冲区大小设置
 * \param[in] chan     : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0)
 *
 * \return 无
 */
void am_kl26_dma_xfer_desc_buffer_set (amhw_kl26_dma_buffer_size_set_t size,
                                       uint8_t                         chan);

/**
 * \brief 设置源地址缓冲区大小
 *
 * \param[in] size     : 枚举体定义 ，缓冲区大小设置
 * \param[in] chan     : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0)
 *
 * \return 无
 */
void am_kl26_dma_xfer_source_buffer_set (amhw_kl26_dma_buffer_size_set_t size,
                                         uint8_t                         chan);

/**
 * \brief 开始DMA传输
 *
 * \param[in] p_desc  : 指向DMA传输描述符的指针
 * \param[in] type    : DMA传输模式设置 ：有对应的枚举体dma_transfer_type_t
 * \param[in] chan    : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0)
 *
 * \retval  AM_OK     : 操作成功
 * \retval -AM_EINVAL : 参数无效
 */
int am_kl26_dma_chan_start (amhw_kl26_dma_xfer_desc_t    *p_desc,
                            amhw_kl26_dma_transfer_type_t type,
                            uint8_t                       chan);

/**
 * \brief 连接DMA回调函数
 *
 * \attention 该回调函数的第二个参数可从驱动获得，该参数的取值范围是 AM_KL26_DMA_INT*
 *            (#AM_KL26_DMA_INT_ERROR)或(#AM_KL26_DMA_INT_NORMAL)
 *
 * \param[in] chan    : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0) 或
 * \param[in] pfn_isr : 回调函数指针
 * \param[in] p_arg   : 回调函数的第一个入口参数 ，在连接过程中，对应通道写上对应数字，
 *                      例如DMA0通道，则该参数为(void *)0
 *
 * \retval  AM_OK     : 连接成功
 * \retval -AM_EPERM  : 参数错误
 */
int am_kl26_dma_isr_connect(int                    chan,
                            am_kl26_pfn_dma_isr_t  pfn_isr,
                            void                  *p_arg);

/**
 * \brief 删除DMA回调函数的连接
 *
 * \attention 该回调函数的第二个参数可从驱动获得，该参数的取值范围是 AM_KL26_DMA_INT*
 *            (#AM_KL26_DMA_INT_ERROR)或(#AM_KL26_DMA_INT_NORMAL)
 *            该回调函数的第三个参数是产生中断的通道，其取值范围是DMA_CHAN_* (#DMA_CHAN_0)
 *
 * \param[in] chan    : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0) 或
 * \param[in] pfn_isr : 回调函数指针
 * \param[in] p_arg   : 回调函数的第一个入口参数，在连接过程中，对应通道写上对应数字，
 *                      例如DMA0通道，则该参数为(void *)0
 *
 * \retval  AM_OK     : 删除成功
 * \retval -AM_EPERM  : 参数错误
 */
int am_kl26_dma_isr_disconnect(int                    chan,
                               am_kl26_pfn_dma_isr_t  pfn_isr,
                               void                  *p_arg);

/**
 * \brief DMA初始化
 *
 * \param[in] p_dev         : 指向DMA设备的指针
 * \param[in] p_dma_devinfo : 指向DMA设备信息的指针
 *
 * \retval  AM_OK       : 初始化成功
 */
int am_kl26_dma_init(am_kl26_dma_dev_t           *p_dev,
                     const am_kl26_dma_devinfo_t *p_dma_devinfo);


/**
 * \brief DMA去初始化
 *
 * \return  无
 */
void am_kl26_dma_deinit(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* __AM_KL26_DMA_H */

/* end of file */
