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
 * \brief ZLG217 kboot KinetisFlashTool 用户配置文件
 *
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-13  yrh, first implementation
 * \endinternal
 */

/**
 * \addtogroup am_if_src_bootconf_zlg217_kft
 * \copydoc am_bootconf_zlg217_kft.c
 * @{
 */

#include "am_zlg217.h"
#include "am_zlg217_inst_init.h"
#include "am_zlg_boot_flash.h"
#include "am_arm_boot.h"
#include "am_boot_flash.h"
#include "am_boot_mem_flash.h"
#include "am_zlg_flash.h"
#include "zlg217_regbase.h"
#include "am_boot_firmware_flash.h"
#include "am_int.h"
#include "am_zlg217_clk.h"
#include "am_arm_nvic.h"
#include "am_bootconf_zlg217.h"


/*******************************************************************************
 * flash配置
 ******************************************************************************/
/**
 * < \brief bootloader flash 设备信息
 */
static am_zlg_boot_flash_devinfo_t __g_flash_devinfo = {

    {
        /** \brief flash的起始地址 */
        0x08000000,
        /** \brief flash的总的大小 */
        128 * 1024,
        /** \brief flash扇区大小 */
        1024,
        /** \brief flash页大小 */
        0,
    },

    /** \brief flash寄存器的基地址 */
    ZLG217_FLASH_BASE,
    /** \brief 平台初始化函数 */
    NULL,
    /** \brief 平台初解始化函数 */
    NULL,
};

/**
 * < \brief bootloader flash 设备实例
 */
static am_zlg_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flash实例初始化，获得其标准服务句柄
 *
 * \param 无
 *
 * \return bootloader flash标准服务句柄，若为 NULL，表明初始化失败
 */
static am_boot_flash_handle_t am_zlg217_boot_single_flash_inst_init(void)
{
    return am_zlg_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}

/*******************************************************************************
 * 固件以flash的方式存储配置
 ******************************************************************************/
static am_boot_firmware_flash_devinfo_t __g_firmware_flash_devinfo = {
    /** \brief 固件在内存中存放的起始地址 */
    0x08007000,
    /**< \brief 应用代码区的总大小 */
    80 * 1024,
    /** \brief 驱动存放固件缓冲区大小 ,值为内存写入最小大小的整数倍 */
    4,
    /** \brief 平台初始化函数 */
    NULL,
    /** \brief 平台解初始化函数 */
    NULL,
};

static am_boot_firmware_flash_dev_t __g_firmware_flash_dev;

am_boot_firmware_handle_t am_zlg217_boot_single_firmware_flash_inst_init(void)
{
    am_boot_flash_handle_t   flash_handle;
    flash_handle = am_zlg217_boot_single_flash_inst_init();
    return am_boot_firmware_flash_init (&__g_firmware_flash_dev,
                                        &__g_firmware_flash_devinfo,
                                         flash_handle);
}

/*******************************************************************************
 * 标准bootloader接口配置
 ******************************************************************************/

/* 在整个bootloader中用到的资源都要接初始化并释放，常见的如定时器，串口等 */
static void __zlg217_boot_single_plfm_deinit()
{
    volatile uint32_t i = 1000000;
    /* 串口解初始化 ，解初始化前需要小段的延时，保证寄存器任务已经完成*/
    while(i--){
    }
    am_clk_disable(CLK_UART1);
    am_gpio_pin_cfg(PIOA_9, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_10,AM_GPIO_INPUT);

    amhw_zlg_uart_disable((amhw_zlg_uart_t *)ZLG217_UART1_BASE);
    am_int_disable(INUM_UART1);

    /* 定时器解初始化  */
    amhw_zlg_tim_int_disable(ZLG217_TIM4, AMHW_ZLG_TIM_UIE);
    amhw_zlg_tim_disable(ZLG217_TIM4);
    am_int_disable(INUM_TIM4);
    am_zlg217_clk_reset(CLK_TIM4);
    am_clk_disable(CLK_TIM4);

    am_arm_nvic_deinit();
    __disable_irq();
}
/**
 * < \brief bootloader标准设备信息
 */
static am_arm_boot_devinfo_t __g_zlg217_boot_single_devinfo = {
    /**< \brief 应用代码区起始地址*/
    0x08007000,
    /** \brief ram起始地址 */
    0x20000000,
    /** \brief ram大小 */
    20 * 1024,
    /** \brief 平台初始化函数 */
    NULL,
    /** \brief 平台解初始化函数 */
    __zlg217_boot_single_plfm_deinit,
};

int am_zlg217_boot_single_inst_init()
{
    return am_arm_boot_init(&__g_zlg217_boot_single_devinfo);
}


/** @} */

/* end of file */
