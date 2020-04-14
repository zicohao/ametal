/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief MicroPort-EEPROM 用户配置文件
 * \sa am_hwconf_microport_eeprom.c
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-28  tee, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_i2c.h"
#include "am_ep24cxx.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_microport_eeprom
 * \copydoc am_hwconf_microport_eeprom.c
 * @{
 */

/*******************************************************************************
  MicroPort-EEPROM 实例初始化（使用芯片功能）
*******************************************************************************/

/** \brief MicroPort-EEPROM 设备信息 */
am_local am_const am_ep24cxx_devinfo_t __g_microport_eeprom_devinfo = {
    0x50,                  /* 设备 7 位从机地址 */
    AM_EP24CXX_FM24C02,    /* 器件型号 */
};

/** \brief MicroPort-EEPROM 设备实例 */
am_local  am_ep24cxx_dev_t __g_microport_eeprom_dev;

/**
 * \brief MicroPort-EEPROM 实例初始化（使用芯片功能）
 */
am_ep24cxx_handle_t am_microport_eeprom_inst_init (void)
{
    am_i2c_handle_t i2c_handle = am_lpc82x_i2c0_inst_init();

    return am_ep24cxx_init(&__g_microport_eeprom_dev,
                           &__g_microport_eeprom_devinfo,
                            i2c_handle);
}

/*******************************************************************************
  MicroPort-EEPROM 实例初始化（将 FM24C02 用作标准的 NVRAM 设备）
*******************************************************************************/

/** \brief MicroPort-EEPROM 设备实例 */
am_local am_nvram_dev_t __g_microport_eeprom_nvram_dev;

/**
 * \brief MicroPort-EEPROM 实例初始化（将 FM24C02 用作标准的 NVRAM 设备）
 */
int am_microport_eeprom_nvram_inst_init (void)
{
    am_ep24cxx_handle_t handle = am_microport_eeprom_inst_init();

    return am_ep24cxx_nvram_init(handle,
                                &__g_microport_eeprom_nvram_dev,
                                 "microport_eeprom");
}

/**
 * @}
 */

/* end of file */
