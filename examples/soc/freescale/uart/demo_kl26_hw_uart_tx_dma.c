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
 * \brief UART0通过DMA方式接收数据，通过HW层的接口实现
 *
 * - 操作步骤：
 *   1. PIOA_1 引脚连接PC串口的TXD;
 *   2. PIOA_2 引脚连接PC串口的RXD;
 *   3. 配置上位机串口波特率为115200，8位数据长度 1位停止位 无奇偶校验;
 *
 * - 实验现象：
 *   1.串口打印提示字符 DMA tx transfer start:
 *   2. 然后串口交替打印一次内存定义的字符，分别为：
 *      uart tx dma test running
 *      uart tx dma test done
 *      
 *
 * \note 在DMA操作期间不要对串口数据寄存器UART_D进行操作
 *
 * \par 源代码
 * \snippet demo_kl26_hw_uart_tx_dma.c src_kl26_hw_uart_tx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.01 16-09-21  nwt, make some changes.
 * - 1.00 15-07-10  xym, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_hw_uart_tx_dma
 * \copydoc demo_kl26_hw_uart_tx_dma.c
 */

/** [src_kl26_hw_uart_tx_dma] */
#include "ametal.h"
#include "am_int.h"
#include "hw/amhw_fsl_uart.h"
#include "hw/amhw_kl26_sim.h"
#include "am_kl26_clk.h"
#include "am_kl26_dma.h"
#include "am_kl26_inst_init.h"
#include "am_board.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/am_kl26.h"

/*******************************************************************************
  宏定义
*******************************************************************************/
#define UART_CH            KL26_UART0  /**< \brief UART通道     */
#define UART_BAUDRATE      (115200)         /**< \brief 波特率       */

/*******************************************************************************
  全局变量
*******************************************************************************/

static volatile am_bool_t  __g_trans_done = AM_FALSE;                 /**< \brief 传输完成标志.  */

/**
 * \brief DMA中断服务程序。
 *
 * \param[in] p_arg : 用户自定义参数，通过 am_kl26_dma_isr_connect() 函数传递。
 * \param[in] flag  : DMA中断标志，由底层驱动传入，该参数的可能取值：
 *                    (#AM_KL26_DMA_INT_ERROR) 或 (#AM_KL26_DMA_INT_NORMAL)。
 * \return    无。
 */
static void uart_dma_isr (void *p_arg , uint8_t flag)
{
    int flag_chan  = (int)p_arg;

    if (flag == AM_KL26_DMA_INT_NORMAL) {
        if (flag_chan == DMA_CHAN_0) {
            /* 禁能UART发送.*/
            amhw_fsl_uart_c2_tx_disable(UART_CH);

            /* 禁能UART发送时使用DMA传输.*/
            if(UART_CH == KL26_UART0){
                amhw_fsl_uart_ver0_dma_tx_disable(UART_CH);
            }else {
                amhw_fsl_uart_ver1_dma_tx_disable(UART_CH);
            }

            /* 非uart0发送时DMA传输需要禁能中断 */
            if (UART_CH != KL26_UART0) {
               /* 禁能发送中断*/
               amhw_fsl_uart_int_disable(UART_CH, AMHW_FSL_UART_INT_C2_TIE);
            }

            /* 停止DMA通道. */
            am_kl26_dma_chan_stop(DMA_CHAN_0);

            __g_trans_done = AM_TRUE;
        }
    } else {
        /* 用户自定义执行代码 */
    }
}

static uint8_t uart_dma_src_request_set (void)
{
    if (UART_CH == KL26_UART0) {
        return DMA_REQUEST_MUX0_UART0TX;
    } else if (UART_CH == KL26_UART1) {
        return DMA_REQUEST_MUX0_UART1TX;
    } else {
        return DMA_REQUEST_MUX0_UART2TX;
    }
}

/**
 * \brief DMA传输配置。
 */
static int uart_tx_dma_tran_cfg (const uint8_t *p_txbuf, uint32_t dma_tran_len)
{
    uint32_t flags;
    static amhw_kl26_dma_xfer_desc_t desc;          /**< \brief DMA 重载描述符 */

    /* 连接DMA中断服务函数 */
    am_kl26_dma_isr_connect(DMA_CHAN_0, uart_dma_isr, (void *)0);

    /* DMA传输配置 */
    flags = KL26_DMA_DCR_PER_REQUEST_ENABLE     |  /* 外设请求源使能    */
            KL26_DMA_DCR_SINGLE_TRANSFERS       |  /* 单次传输          */
            KL26_DMA_DCR_AUTO_ALIGN_DISABLE     |  /* 自动对齐禁能      */
            KL26_DMA_DCR_SOURCE_SIZE_8_BIT      |  /* 源地址1字节读取   */
            KL26_DMA_DCR_DESTINATION_SIZE_8_BIT |  /* 目的地址1字节写入 */
            KL26_DMA_DCR_REQUEST_AFFECTED       |  /* 请求有影响        */
            KL26_DMA_DCR_NO_LINKING             |  /* 无通道连接        */
            KL26_DMA_DCR_INTERRUTP_ENABLE       |  /* DMA中断使能       */
            KL26_DMA_DCR_START_DISABLE    ;        /* DMA传输禁能       */

    /* 建立通道描述符 */
    am_kl26_dma_xfer_desc_build(&desc,                           /* 通道描述符   */
                                (uint32_t)(p_txbuf),               /* 源端数据缓冲 */
                                (uint32_t)(&(UART_CH->data)),      /* 目标数据缓冲 */
                                (uint32_t)dma_tran_len,            /* 传输字节数   */
                                flags);                            /* 传输配置     */

    am_kl26_dma_chan_cfg(DMA_CHAN_0,
                         KL26_DMA_TRIGGER_DISABLE |     /**< \brief DMA正常模式 */
                         uart_dma_src_request_set());        /**< \brief 请求源      */

    /* 启动DMA传输，马上开始传输 */
    if (am_kl26_dma_chan_start(&desc,
                               KL26_DMA_MER_TO_PER,    /* 内存到外设   */
                               (uint8_t)DMA_CHAN_0) == AM_ERROR) {
        return AM_ERROR;
    }

    return AM_OK;
}

/**
 * \brief UART时钟使能初始化
 * \param[in] p_hw_uart : 指向串口设备寄存器结构体, 如KL26_UART1.
 */
static void uart_clock_init (void *p_hw_uart)
{
    uint32_t base_addr = (uint32_t)(p_hw_uart);

    switch (base_addr) {

    /* 串口0时钟初始化 */
    case KL26_UART0_BASE:
        amhw_kl26_sim_uart0_src_set(KL26_SIM_UART0SRC_PLLFLLCLK);
        /* 开启UART0时钟                  */
        amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART0);
        break;

    /* 串口1时钟初始化 */
    case KL26_UART1_BASE:
        amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART1);
        break;

    /* 串口2时钟初始化 */
    case KL26_UART2_BASE:
        amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART2);
        break;
    }
}
/**
 * \brief UART引脚初始化
 * \param[in] p_hw_uart : 指向串口设备寄存器结构体, 如KL26_UART1.
 */
static void uart_pin_init (void *p_hw_uart)
{
    uint32_t base_addr = (uint32_t)(p_hw_uart);

    switch (base_addr) {

    case KL26_UART0_BASE:
        am_gpio_pin_cfg (PIOA_1,PIOA_1_UART0_RX);
        am_gpio_pin_cfg (PIOA_2,PIOA_2_UART0_TX);
        break;

    case KL26_UART1_BASE:
        /* 引脚初始化      PIOC_3_UART1_RX  PIOC_4_UART1_TX     */
        am_gpio_pin_cfg (PIOC_3,PIOC_3_UART1_RX);
        am_gpio_pin_cfg (PIOC_4,PIOC_4_UART1_TX);
        break;

    case KL26_UART2_BASE:
        /* 引脚初始化      PIOD_4_UART2_RX  PIOD_5_UART2_TX     */
        am_gpio_pin_cfg (PIOD_4,PIOD_4_UART2_RX);
        am_gpio_pin_cfg (PIOD_5,PIOD_5_UART2_TX);
        break;
    }
}

/**
 * \brief UART初始化
 */
static void uart_hw_init (void)
{
    /* 使能串口时钟模块 */
    uart_clock_init(UART_CH);

    /* 配置串口输入输出引脚 */
    uart_pin_init(UART_CH);

    amhw_fsl_uart_stop_bit_set (UART_CH, AMHW_FSL_UART_BDH_SBNS_STOP_1);
    amhw_fsl_uart_data_mode_set(UART_CH, AMHW_FSL_UART_C1_M_8BIT);
    amhw_fsl_uart_parity_set(UART_CH,  AMHW_FSL_UART_C1_PARITY_NO);

    /* 设置串口波特率 */
    if(UART_CH == KL26_UART0){
        amhw_fsl_uart_ver0_baudrate_set(UART_CH,
                                        am_kl26_clk_periph_rate_get((void *)(UART_CH)),
                                        UART_BAUDRATE);
    }else {
        amhw_fsl_uart_ver1_baudrate_set(UART_CH,
                                        am_kl26_clk_periph_rate_get((void *)(UART_CH)),
                                        UART_BAUDRATE);
    }
}


/**
 * \brief UART发送DMA传输初始化
 */
static void uart_hw_dma_init (void)
{
    /* 串口发送DMA传输使能  */
    if(UART_CH == KL26_UART0){
        amhw_fsl_uart_ver0_dma_tx_enable(UART_CH);
    }else {
        amhw_fsl_uart_ver1_dma_tx_enable(UART_CH);
    }

    /* 非uart0发送时DMA传输需要使能中断 */
    if (UART_CH != KL26_UART0) {
        /* 禁能发送完成中断*/
        amhw_fsl_uart_int_disable(UART_CH, AMHW_FSL_UART_INT_C2_TCIE);

       /* 使能发送中断，TDRE中断信号触发DMA传输 */
       amhw_fsl_uart_int_enable(UART_CH, AMHW_FSL_UART_INT_C2_TIE);
    }

    /* 使能串口 */
    amhw_fsl_uart_enable(UART_CH);
}

/**
 * \brief 例程入口
 */
void demo_kl26_hw_uart_tx_dma_entry (void)
{
    static uint8_t buf_dst[]  = "uart tx dma test running\r\n"; /**< \brief 目标端数据缓冲区 */
    static uint8_t buf_dst1[] = "uart tx dma test done\r\n";    /**< \brief 目标端数据缓冲区 */
    uint8_t i = 0;
    uint32_t key;

    /* DMA初始化 */
    am_kl26_dma_inst_init();

    /* UART初始化 */
    uart_hw_init();

    amhw_fsl_uart_poll_send(UART_CH, (uint8_t *)"DMA tx transfer start:\r\n",
                            sizeof("DMA tx transfer start:\r\n"));

    /* UART用DMA传输的初始化 */
    uart_hw_dma_init();

    /* 开始DMA传输 */
    uart_tx_dma_tran_cfg(buf_dst, sizeof(buf_dst)-1);

    while (1) {
        key = am_int_cpu_lock();
        if ((__g_trans_done == AM_TRUE) && (i == 0)) {
            __g_trans_done = AM_FALSE;
            am_int_cpu_unlock(key);

            i = 1;

            /* 串口发送DMA传输使能  */
            if(UART_CH == KL26_UART0){
                amhw_fsl_uart_ver0_dma_tx_enable(UART_CH);
            }else {
                amhw_fsl_uart_ver1_dma_tx_enable(UART_CH);
            }

            /* 非uart0发送时DMA传输需要使能中断 */
            if (UART_CH != KL26_UART0) {
               /* 使能发送中断，TDRE中断信号触发DMA传输 */
               amhw_fsl_uart_int_enable(UART_CH, AMHW_FSL_UART_INT_C2_TIE);
            }

            /* 使能UART发送.*/
            amhw_fsl_uart_c2_tx_enable(UART_CH);

            uart_tx_dma_tran_cfg(buf_dst1, sizeof(buf_dst1) - 1);
        } else {
            am_int_cpu_unlock(key);
        }

        am_mdelay(100);
        am_led_toggle(LED0);

        key = am_int_cpu_lock();
        if ((__g_trans_done == AM_TRUE) && (i == 1)) {
             __g_trans_done = AM_FALSE;
             am_int_cpu_unlock(key);

             i = 0;

             /* 串口发送DMA传输使能  */
             if(UART_CH == KL26_UART0){
                 amhw_fsl_uart_ver0_dma_tx_enable(UART_CH);
             }else {
                 amhw_fsl_uart_ver1_dma_tx_enable(UART_CH);
             }

             /* 非uart0发送时DMA传输需要使能中断 */
             if (UART_CH != KL26_UART0) {
                /* 使能发送中断，TDRE中断信号触发DMA传输 */
                amhw_fsl_uart_int_enable(UART_CH, AMHW_FSL_UART_INT_C2_TIE);
             }

             /* 使能UART发送.*/
             amhw_fsl_uart_c2_tx_enable(UART_CH);

             uart_tx_dma_tran_cfg(buf_dst, sizeof(buf_dst) - 1);
        } else {
            am_int_cpu_unlock(key);
        }
    }
}

/** [src_kl26_hw_uart_tx_dma] */

/* end of file */
