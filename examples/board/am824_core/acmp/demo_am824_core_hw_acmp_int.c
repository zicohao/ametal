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
 * \brief 模拟比较器例程（中断模式），通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. PIO0_1 连接模拟输入 2；
 *   2. PIO0_14 连接模拟输入 3。
 *
 * - 实验现象：
 *   1. 当输入 2 与输入 3 比较结果发生变化的时候会输出提示字符；
 *   2. 输入 2 大于输入 3 时，串口会输出比较结果 "result: PIO0_1_ACMP_I2 > PIO0_14_ACMP_I3"；
 *   3. 输入 2 小于输入 3 时，串口会输出比较结果 "result: PIO0_1_ACMP_I2 < PIO0_14_ACMP_I3"。
 *
 * \note
 *    如需观察串口打印的调试信息，需要将 PIO0_0 引脚连接 PC 串口的 TXD，
 *    PIO0_4 引脚连接 PC 串口的 RXD。
 *
 * \par 源代码
 * \snippet demo_am845_core_hw_acmp_int.c src_am845_core_hw_acmp_int
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-05  hgo, modified
 * - 1.00 15-07-21  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_acmp_int
 * \copydoc demo_am845_core_hw_acmp_int.c
 */

/**
 * \addtogroup demo_if_am824_hw_acmp_int
 * \copydoc demo_am824_hw_acmp_int.c
 */

/** [src_am824_hw_acmp_int] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "demo_nxp_entries.h"

/**
 * \brief ACMP 例程入口
 */
am_local void __plfm_acmp_init()
{
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_ACMP);
    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_ACMP);

    /* 使能管脚  PIO0_1 为比较器输入 2 功能（比较器输入 2 管脚固定为 PIO0_1） */
    am_gpio_pin_cfg (PIO0_1, PIO0_1_ACMP_I2);

    /* 使能管脚  PIO0_14 为比较器输入 3 功能（比较器输入 3 管脚固定为 PIO0_14） */
    am_gpio_pin_cfg (PIO0_14, PIO0_14_ACMP_I3);

    /* 使能管脚 PIO0_18 为比较器输出功能 */
    am_gpio_pin_cfg (PIO0_18, PIO_FUNC_ACMP_O);
}


/**
 * \brief 例程入口
 */
void demo_am824_core_hw_acmp_int_entry (void)
{
    uint32_t flags = 0;

    am_kprintf("demo am824_core hw acmp int!\r\n");
    /* 平台初始化 */
    __plfm_acmp_init();

    flags = AMHW_LPC82X_ACMP_CTRL_VP_CMP2      |  /* 输入 2 为同相端输入 */
            AMHW_LPC82X_ACMP_CTRL_VM_CMP3      |  /* 输入 3 为反相端输入 */
            AMHW_LPC82X_ACMP_CTRL_EDGESEL_BOTH |  /* 配置双边沿触发中断 */
            AMHW_LPC82X_ACMP_CTRL_HYS_20MV;       /* 迟滞电压为 20mV */


    demo_lpc824_hw_acmp_int_entry(LPC82X_ACMP, flags, INUM_ACMP, PIO0_18);
}
/** [src_am824_hw_acmp_int] */

/* end of file */
