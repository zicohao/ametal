/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC84X 外设映射
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-07  cyl, first implementation.
 * \endinternal
 */
 
#ifndef __LPC84X_PERIPH_MAP_H
#define __LPC84X_PERIPH_MAP_H

#ifdef __cplusplus
extern "C" {    
#endif 

#include "lpc84x_regbase.h"

#include "hw/amhw_lpc_i2c.h"
#include "hw/amhw_lpc_mrt.h"
#include "hw/amhw_lpc_sct.h"
#include "hw/amhw_lpc_spi.h"
#include "hw/amhw_lpc_usart.h"
#include "hw/amhw_lpc_wkt.h"

#include "hw/amhw_lpc84x_capt.h"
#include "hw/amhw_lpc84x_adc.h"
#include "hw/amhw_lpc84x_dma.h"
#include "hw/amhw_lpc84x_gpio.h"
#include "hw/amhw_lpc84x_inmux.h"
#include "hw/amhw_lpc84x_iocon.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc84x_swm.h"
#include "hw/amhw_lpc84x_acmp.h"

/** 
 * \addtogroup lpc82x_if_periph_map
 * \copydoc lpc82x_periph_map.h
 * @{
 */

/**
 * \name 外设定义
 * @{
 */

/** \brief  系统滴答时钟(SYSTICK)寄存器块指针   */
#define LPC84X_SYSTICK     ((amhw_arm_systick_t    *)LPC84X_SYSTICK_BASE)
                                                        
/** \brief  IO控制(IOCON)寄存器块指针           */                               
#define LPC84X_IOCON       ((amhw_lpc84x_iocon_t   *)LPC84X_IOCON_BASE  )
                                                        
/** \brief  通用输入输出(GPIO)寄存器块指针      */                               
#define LPC84X_GPIO        ((amhw_lpc84x_gpio_t    *)LPC84X_GPIO_BASE   )
                                                        
/** \brief  引脚中断(PINT)寄存器块指针          */                               
#define LPC84X_PINT        ((amhw_lpc82x_pint_t    *)LPC84X_PINT_BASE   )
                                                        
/** \brief  开关矩阵(SWM)寄存器块指针           */
#define LPC84X_SWM         ((amhw_lpc84x_swm_t     *)LPC84X_SWM_BASE    )
                                                        
/** \brief  输入复用控制(INMUX)寄存器块指针     */                               
#define LPC84X_INMUX       ((amhw_lpc84x_inmux_t   *)LPC84X_INMUX_BASE  )
                                                        
/** \brief  DMA控制器(DMA)寄存器块指针          */                               
#define LPC84X_DMA         ((amhw_lpc82x_dma_t     *)LPC84X_DMA_BASE    )
                                                        
/** \brief  多频率定时器(MRT)寄存器块指针       */                               
#define LPC84X_MRT         ((amhw_lpc_mrt_t     *)LPC84X_MRT_BASE       )
                                                        
/** \brief 状态可配置定时器(SCT0)寄存器块指针   */                              
#define LPC84X_SCT0        ((amhw_lpc_sct_t     *)LPC84X_SCT0_BASE      )

/** \brief 系统配置(SYSCON)寄存器块指针         */
#define LPC84X_SYSCON      ((amhw_lpc84x_syscon_t  *)LPC84X_SYSCON_BASE )
                                                        
/** \brief 串行外设接口(SPI0)寄存器块指针       */                               
#define LPC84X_SPI0        ((amhw_lpc_spi_t     *)LPC84X_SPI0_BASE   )
                                                                               
/** \brief 串行外设接口(SPI1)寄存器块指针       */                                                      
#define LPC84X_SPI1        ((amhw_lpc_spi_t     *)LPC84X_SPI1_BASE   )
                                                        
/** \brief I2C总线控制器(I2C0)寄存器块指针      */                               
#define LPC84X_I2C0        ((amhw_lpc_i2c_t     *)LPC84X_I2C0_BASE   )
                                                                             
/** \brief I2C总线控制器(I2C1)寄存器块指针      */                                                    
#define LPC84X_I2C1        ((amhw_lpc_i2c_t     *)LPC84X_I2C1_BASE   )
                                                                             
/** \brief I2C总线控制器(I2C2)寄存器块指针      */                                                    
#define LPC84X_I2C2        ((amhw_lpc_i2c_t     *)LPC84X_I2C2_BASE   )
                                                        
/** \brief I2C总线控制器(I2C3)寄存器块指针      */                                                      
#define LPC84X_I2C3        ((amhw_lpc_i2c_t     *)LPC84X_I2C3_BASE   )
   
/** \brief 串口(UART0)寄存器块指针              */
#define LPC84X_USART0      ((amhw_lpc_usart_t   *)LPC84X_USART0_BASE )
                                                        
/** \brief 串口(UART1)寄存器块指针              */                               
#define LPC84X_USART1      ((amhw_lpc_usart_t   *)LPC84X_USART1_BASE )
                                                        
/** \brief 串口(UART2)寄存器块指针              */                               
#define LPC84X_USART2      ((amhw_lpc_usart_t   *)LPC84X_USART2_BASE )
                                                      
/** \brief 循环冗余校验(CRC)寄存器块指针        */                             
#define LPC84X_CRC         ((amhw_lpc_crc_t     *)LPC84X_CRC_BASE    )
                                                        
/** \brief 自唤醒定时器(WKT)寄存器块指针        */                               
#define LPC84X_WKT         ((amhw_lpc_wkt_t     *)LPC84X_WKT_BASE    )
                                                        
/** \brief 电源管理单元(PMU)寄存器块指针        */                               
#define LPC84X_PMU         ((amhw_lpc82x_pmu_t  *)LPC84X_PMU_BASE    )

/** \brief FLASH控制器(FMC)寄存器块指针         */                              
#define LPC84X_FMC         ((amhw_lpc_fmc_t     *)LPC84X_FMC_BASE    )
  
/** \brief 模数转换(ADC)寄存器块指针            */                              
#define LPC84X_ADC0        ((amhw_lpc84x_adc_t  *)LPC84X_ADC0_BASE   )

/** \brief 模拟比较器(ACMP)寄存器块指针         */                     
#define LPC84X_ACMP        ((amhw_lpc84x_acmp_t *)LPC84X_ACMP_BASE   )

/** \brief 窗口看门狗(WWDT)寄存器块指针         */
#define LPC84X_WWDT        ((amhw_lpc_wwdt_t    *)LPC84X_WWDT_BASE   )

/** \brief DAC0寄存器块指针         */
#define LPC84X_DAC0        ((amhw_lpc_dac_t     *)LPC84X_DAC0_BASE   )

/** \brief DAC1寄存器块指针         */
#define LPC84X_DAC1        ((amhw_lpc_dac_t     *)LPC84X_DAC1_BASE   )

/** \brief 电容触摸(CAPT)寄存器块指针         */
#define LPC84X_CAPT        ((amhw_lpc84x_capt_t *)LPC84X_CAPT_BASE   )


/** @} */

/**
 * @} lpc82x_if_periph_map
 */
    
#ifdef __cplusplus
}
#endif

#endif /* LPC84X_REG_BASE_H */

/* end of file */
