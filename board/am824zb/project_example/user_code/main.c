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
 * \brief AM824ZB 模板工程
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-07  nwt, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_led.h"
#include "demo_am824zb_entries.h"
#include "demo_am824_core_entries.h"
/**
 * \brief AMetal 应用程序入口
 */
void am_main (void)
{
    AM_DBG_INFO("Start up successful!\r\n");
    /*
     * am824zb与am824_core的外设几乎相同，仅仅多了Zigbee模块，
     * 但是am824zb板的I2C0的PIO10_10和PIO0_11与miniport的引脚可能会造成冲突，
     * 导致一些demo只能在am824_core上运行而无法在am824zb上正常运行，因冲突而不能运行的demo:
     *
     * demo_am824_core_miniport_hc595_digitron_temp_entry();
     *
     * 此外，用户若设计出某些需要使用到PIO10_10、PIO10_11引脚的miniport与lm75同时使用的代码也无法正常运行。
     *
     * 以下为所有可正常运行demo的入口函数，需要运行哪个 demo，就取消对应函数调用行的注释，默认运行的是LED闪烁 demo。
     * 注意：同一时刻只能运行一个 demo，即只能使某一行处于取消注释状态。
     */

    demo_am824_core_std_led_entry();
    //demo_am824_core_std_wwdt_entry();
    //demo_am824_core_hw_wwdt_entry();
    //demo_am824_core_hw_acmp_int_entry();
    //demo_am824_core_hw_acmp_lad_entry();
    //demo_am824_core_hw_acmp_poll_entry();
    //demo_am824_core_std_buzzer_entry();
    //demo_am824_core_hw_crc_entry();
    //demo_am824_core_std_crc_entry();
    //demo_am824_core_drv_dma_hwtrigger_burst_entry();
    //demo_am824_core_drv_dma_m2m_entry();
    //demo_am824_core_drv_dma_ping_pong_entry();
    //demo_am824_core_hw_flash_ctrl_entry();
    //demo_am824_core_hw_gpio_entry();
    //demo_am824_core_hw_gpio_int_entry();
    //demo_am824_core_hw_gpio_pmatch_entry();
    //demo_am824_core_std_gpio_entry();
    //demo_am824_core_std_gpio_int_entry();
    //demo_am824_core_std_gpio_key_entry();
    //demo_am824_core_hw_i2c_master_dma_entry();
    //demo_am824_core_hw_i2c_master_poll_entry();
    //demo_am824_core_hw_i2c_slave_dma_entry();
    //demo_am824_core_hw_i2c_slave_int_entry();
    //demo_am824_core_hw_i2c_slave_poll_entry();
    //demo_am824_core_std_i2c_lm75_entry();
    //demo_am824_core_std_i2c_master_sync_entry();
    //demo_am824_core_std_i2c_master_async_entry();
    //demo_am824_core_hw_iap_entry();
    //demo_am824_core_std_key_input_event_entry();
    //demo_am824_core_miniport_digitron_entry();
    //demo_am824_core_miniport_hc595_digitron_key_entry();
    //demo_am824_core_miniport_hc595_digitron_entry();
    //demo_am824_core_miniport_hc595_led_entry();
    //demo_am824_core_miniport_key_digitron_entry();
    //demo_am824_core_miniport_key_entry();
    //demo_am824_core_miniport_led_entry();
    //demo_am824_core_miniport_zlg72128_entry();
    //demo_am824_core_hw_mrt_entry();
    //demo_am824_core_std_mrt_timer_entry();
    //demo_am824_core_hw_pll_entry();
    //demo_am824_core_hw_pmu_deeppowerdown_entry();
    //demo_am824_core_hw_pmu_deepsleep_entry();
    //demo_am824_core_hw_pmu_powerdown_entry();
    //demo_am824_core_hw_pmu_sleep_entry();
    //demo_am824_core_drv_sct_timing_pwm_entry();
    //demo_am824_core_hw_sct_1_32bit_pwm_entry();
    //demo_am824_core_hw_sct_1_32bit_timing_entry();
    //demo_am824_core_hw_sct_2_16bit_pwm_entry();
    //demo_am824_core_hw_sct_2_16bit_timing_entry();
    //demo_am824_core_hw_sct_cap_entry();
    //demo_am824_core_hw_sct_multi_states_entry();
    //demo_am824_core_std_sct_cap_entry();
    //demo_am824_core_std_sct_pwm_entry();
    //demo_am824_core_std_sct_timer_entry();
    //demo_am824_core_hw_spi_master_entry();
    //demo_am824_core_hw_spi_slave_entry();
    //demo_am824_core_hw_spi_slave_dma_entry();
    //demo_am824_core_std_spi_master_dma_entry();
    //demo_am824_core_std_spi_master_int_entry();
    //demo_am824_core_hw_bod_entry();
    //demo_am824_core_hw_clkout_entry();
    //demo_am824_core_std_delay_entry();
    //demo_am824_core_std_systick_timer_entry();
    //demo_am824_core_hw_usart_autobaud_entry();
    //demo_am824_core_hw_usart_poll_entry();
    //demo_am824_core_hw_usart_rx_dma_entry();
    //demo_am824_core_hw_usart_tx_dma_entry();
    //demo_am824_core_std_usart_flowctrl_entry();
    //demo_am824_core_std_usart_poll_entry();
    //demo_am824_core_std_usart_rngbuf_entry();
    //demo_am824_core_hw_wkt_deeppowerdown_wakeup_entry();
    //demo_am824_core_hw_wkt_timer_entry();
    //demo_am824_core_std_wkt_timer_entry();

    /*
     * 以下demo为am824zb板特有demo
     */
    //demo_am824zb_hw_adc_dma_entry();
    //demo_am824zb_hw_adc_thcmp_entry();
    //demo_am824zb_std_adc_dma_int_entry();
    //demo_am824zb_std_adc_dma_poll_entry();
    //demo_am824zb_std_adc_int_entry();
    //demo_am824zb_std_adc_ntc_entry();
    //demo_am824zb_std_adc_poll_entry();
    //demo_am824zb_std_zm516x_baudrate_entry();
    //demo_am824zb_std_zm516x_gpio_entry();
    //demo_am824zb_std_zm516x_key_led_entry();
    //demo_am824zb_std_zm516x_network_entry();
    //demo_am824zb_std_zm516x_search_entry();
    //demo_am824zb_std_zm516x_entry();

    while(1) {
        ;
    }
}

/* end of file */
