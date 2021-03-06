/* Copyright 2020 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef __CROS_EC_CONFIG_CHIP_H
#define __CROS_EC_CONFIG_CHIP_H

#include <devicetree.h>

/*
 * This file translates Kconfig options to platform/ec options.
 *
 * Options which are from Zephyr platform/ec module (Kconfig) start
 * with CONFIG_PLATFORM_EC_, and can be found in the Kconfig file.
 *
 * Options which are for the platform/ec configuration can be found in
 * common/config.h.
 */

#define CONFIG_ZEPHYR
#define CHROMIUM_EC

/* Chipset and power configuration */
#ifdef CONFIG_AP_X86_INTEL_TGL
#define CONFIG_CHIPSET_TIGERLAKE
#endif

/* Battery configuration */
#undef CONFIG_BATTERY
#undef CONFIG_BATTERY_FUEL_GAUGE
#ifdef CONFIG_PLATFORM_EC_BATTERY
#define CONFIG_BATTERY
#define CONFIG_BATTERY_FUEL_GAUGE
#endif

#undef CONFIG_CHARGER_ISL9241
#ifdef CONFIG_PLATFORM_EC_CHARGER_ISL9241
#define CONFIG_CHARGER_ISL9241
/* Hardware based charge ramp is broken in the ISL9241 (b/169350714) */
#define CONFIG_CHARGE_RAMP_SW
#endif

#undef CONFIG_BATTERY_SMART
#ifdef CONFIG_PLATFORM_EC_BATTERY_SMART
#define CONFIG_BATTERY_SMART
#endif

/* eSPI configuration */
#ifdef CONFIG_PLATFORM_EC_ESPI

#ifdef CONFIG_PLATFORM_EC_HOSTCMD
#define CONFIG_HOSTCMD_ESPI
#endif

/* eSPI signals */
#ifdef CONFIG_PLATFORM_EC_ESPI_VW_SLP_S3
#define CONFIG_HOSTCMD_ESPI_VW_SLP_S3
#endif

#ifdef CONFIG_PLATFORM_EC_ESPI_VW_SLP_S4
#define CONFIG_HOSTCMD_ESPI_VW_SLP_S4
#endif

#endif /* CONFIG_PLATFORM_EC_ESPI */

#ifdef CONFIG_PLATFORM_EC_I2C
/* Also see shim/include/i2c/i2c.h which defines the ports enum */
#define CONFIG_I2C
#endif

#undef CONFIG_KEYBOARD_PROTOCOL_8042
#ifdef CONFIG_PLATFORM_EC_KEYBOARD_PROTOCOL_8042
#define CONFIG_KEYBOARD_PROTOCOL_8042
#endif /* CONFIG_PLATFORM_EC_KEYBOARD_PROTOCOL_8042 */

#undef CONFIG_CMD_KEYBOARD
#ifdef CONFIG_PLATFORM_EC_CONSOLE_CMD_KEYBOARD_8042
#define CONFIG_CMD_KEYBOARD
#endif

#undef CONFIG_KEYBOARD_COL2_INVERTED
#ifdef CONFIG_PLATFORM_EC_KEYBOARD_COL2_INVERTED
#define CONFIG_KEYBOARD_COL2_INVERTED
#endif  /* CONFIG_PLATFORM_EC_KEYBOARD_COL2_INVERTED */

#ifdef CONFIG_PLATFORM_EC_POWERSEQ_CPU_PROCHOT_ACTIVE_LOW
#define CONFIG_CHIPSET_CPU_PROCHOT_ACTIVE_LOW
#endif

#ifdef CONFIG_PLATFORM_EC_POWERSEQ_RSMRST_DELAY
#define CONFIG_CHIPSET_X86_RSMRST_DELAY
#endif

#ifdef CONFIG_PLATFORM_EC_POWERSEQ_SLP_S3_L_OVERRIDE
#define CONFIG_CHIPSET_SLP_S3_L_OVERRIDE
#endif

#ifdef CONFIG_PLATFORM_EC_POWERSEQ_PP3300_RAIL_FIRST
#define CONFIG_CHIPSET_PP3300_RAIL_FIRST
#endif

#ifdef CONFIG_PLATFORM_EC_POWERSEQ_RTC_RESET
#define CONFIG_BOARD_HAS_RTC_RESET
#endif

#ifdef CONFIG_PLATFORM_EC_POWERSEQ_PP5000_CONTROL
#define CONFIG_POWER_PP5000_CONTROL
#endif

#ifdef CONFIG_PLATFORM_EC_TIMER
#define CONFIG_HWTIMER_64BIT
#define CONFIG_HW_SPECIFIC_UDELAY
#undef CONFIG_WATCHDOG

#undef CONFIG_CMD_GETTIME
#ifdef CONFIG_PLATFORM_EC_TIMER_CMD_GETTIME
#define CONFIG_CMD_GETTIME
#endif  /* CONFIG_PLATFORM_EC_TIMER_CMD_GETTIME */

#undef CONFIG_CMD_TIMERINFO
#ifdef CONFIG_PLATFORM_EC_TIMER_CMD_TIMERINFO
#define CONFIG_CMD_TIMERINFO
#endif  /* CONFIG_PLATFORM_EC_TIMER_CMD_TIMERINFO */

#undef CONFIG_CMD_WAITMS
#ifdef CONFIG_PLATFORM_EC_TIMER_CMD_WAITMS
#define CONFIG_CMD_WAITMS
#endif  /* CONFIG_PLATFORM_EC_TIMER_CMD_TIMERINFO */

#endif  /* CONFIG_PLATFORM_EC_TIMER */

#endif  /* __CROS_EC_CONFIG_CHIP_H */
