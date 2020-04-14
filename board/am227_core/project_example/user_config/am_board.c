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
 * \brief am217_core
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"
#include "am_event_input_key.h"
#include "am_event_category_input.h"
#include "am_bsp_isr_defer_pendsv.h"
#include "am_zlg217.h"
#include "am_zlg217_inst_init.h"
#include "am_bsp_system_heap.h"
#include "am_bsp_delay_timer.h"
#include "am_service_inst_init.h"

#ifdef __CC_ARM
#ifdef __MICROLIB
#include "am_bsp_microlib.h"
#else
#include "am_bsp_armlib.h"
#endif /* __MICROLIB */
#elif defined(__GNUC__)
#include "am_bsp_newlib.h"
#endif

/** \brief SRAM 信息,使用 ARMCC 时需要提供 SRAM 结束地址 */
#ifdef __CC_ARM
#define SRAM_SIZE   20
#define SRAM_START  0x20000000
#define SRAM_END    (SRAM_START + SRAM_SIZE * 1024)

#endif /* __CC_ARM */

/*******************************************************************************
  全局变量
*******************************************************************************/

/**
 * \brief 蜂鸣器使用的定时器的 handle
 *
 * 当使用蜂鸣器时，默认将使用 TIM3 的 OUT1 输出 PWM 波形，因此已经将 TIM3 初始化为
 * PWM 功能
 */
am_pwm_handle_t   g_buzzer_pwm_handle;

/**
 * \brief 系统滴答使用的定时器的 handle
 *
 * 当使用系统滴答时，默认使用 TIM4 的通道 0 作为基础定时单元，因此已经将 TIM4 初始化
 * 为定时器功能
 */
am_timer_handle_t g_system_tick_timer_handle;

/*******************************************************************************
  公共函数
*******************************************************************************/

/**
 * \brief 板级初始化
 */
void am_board_init (void)
{
    am_uart_handle_t dbg_handle = NULL;

#ifdef  __GNUC__
    extern char __heap_start__;            /* Defined by the linker */
    extern char __heap_end__;              /* Defined by the linker */

    static char *heap_start = &__heap_start__;
    static char *heap_end   = &__heap_end__;

#elif defined(__CC_ARM)

    extern int Image$$RW_IRAM1$$ZI$$Limit; /* Defined by the linker */
	
    int *heap_start = (int *)&Image$$RW_IRAM1$$ZI$$Limit;
    int *heap_end   = (int *)SRAM_END;
#endif

    /* 系统堆栈初始化 */
    am_bsp_system_heap_init((void *)heap_start, (void *)heap_end);

#if (AM_CFG_DELAY_ENABLE == 1)
    am_bsp_delay_timer_init(am_zlg217_systick_inst_init(), 0);
#endif /* (AM_CFG_DELAY_ENABLE == 1) */

#if (AM_CFG_LED_ENABLE == 1)
    am_led_gpio_inst_init();
#endif /* (AM_CFG_LED_ENABLE == 1) */

#ifdef AM_VDEBUG

#if (AM_CFG_DEBUG_ENABLE == 1)
    dbg_handle = am_debug_uart_inst_init();
#endif /* (AM_CFG_DEBUG_ENABLE == 1) */

#endif /* AM_VDEBUG */

#if (AM_CFG_STDLIB_ENABLE == 1)
    #ifdef __CC_ARM
        #ifdef __MICROLIB

            /* 初始化Micro LIB */
            am_bsp_microlib_init(dbg_handle);
        #else

            /* 初始化ARM LIB */
            am_bsp_armlib_init(dbg_handle);
        #endif /* __MICROLIB */

    #elif defined(__GNUC__)

        /* 初始化 NEW LIB 库 */
        am_bsp_newlib_init(dbg_handle);
    #endif
#endif /* (AM_CFG_STDLIB_ENABLE == 1) */

#if ((AM_CFG_SOFTIMER_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1))
    g_system_tick_timer_handle = am_system_tick_softimer_inst_init();
#elif (AM_CFG_SYSTEM_TICK_ENABLE == 1)
    g_system_tick_timer_handle = am_system_tick_inst_init();
#endif /* ((AM_CFG_SOFTIMER_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1)) */

#if (AM_CFG_BUZZER_ENABLE == 1)
    g_buzzer_pwm_handle = am_buzzer_pwm_inst_init();
#endif /* (AM_CFG_BUZZER_ENABLE == 1) */

#if (AM_CFG_KEY_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1)
    am_event_input_inst_init();                   /* 事件输入管理器服务初始化 */
#endif /* (AM_CFG_KEY_ENABLE == 1) || (AM_CFG_KEY_GPIO_ENABLE == 1) */

#if (AM_CFG_KEY_GPIO_ENABLE == 1)
    am_key_gpio_inst_init();
#endif /* (AM_CFG_KEY_GPIO_ENABLE == 1) */

#if (AM_CFG_ISR_DEFER_ENABLE == 1)
    am_bsp_isr_defer_pendsv_init();
#endif /* (AM_CFG_ISR_DEFER_ENABLE == 1) */

    /* 其它内容待添加 */
}

/* end of file */
