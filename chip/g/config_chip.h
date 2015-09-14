/* Copyright (c) 2014 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef __CROS_EC_CONFIG_CHIP_H
#define __CROS_EC_CONFIG_CHIP_H

#include "core/cortex-m/config_core.h"

/* Number of IRQ vectors on the NVIC */
/* TODO_FPGA this should come from the generated .h file */
#define CONFIG_IRQ_COUNT 188

/* Describe the RAM layout */
#define CONFIG_RAM_BASE         0x10000
#define CONFIG_RAM_SIZE         0x10000

/* Flash chip specifics */
#define CONFIG_FLASH_BANK_SIZE         0x800	/* protect bank size */
#define CONFIG_FLASH_ERASE_SIZE        0x800	/* erase bank size */
/* This flash can only be written as 4-byte words (aligned properly, too). */
#define CONFIG_FLASH_WRITE_SIZE        4	/* min write size (bytes) */
/* But we have a 32-word buffer for writing multiple adjacent cells */
#define CONFIG_FLASH_WRITE_IDEAL_SIZE  128	/* best write size (bytes) */

/* Describe the flash layout */
#define CONFIG_PROGRAM_MEMORY_BASE     0x40000
#define CONFIG_FLASH_SIZE              (512 * 1024)
#define CONFIG_RO_HEAD_ROOM	       1024	/* Room for ROM signature. */

/* Compute the rest of the flash params from these */
#include "config_std_internal_flash.h"

/* Interval between HOOK_TICK notifications */
#define HOOK_TICK_INTERVAL_MS 500
#define HOOK_TICK_INTERVAL    (HOOK_TICK_INTERVAL_MS * MSEC)

/* System stack size */
#define CONFIG_STACK_SIZE 1024

/* Idle task stack size */
#define IDLE_TASK_STACK_SIZE 256

/* Default task stack size */
#define TASK_STACK_SIZE 488

/* Larger task stack size, for hook task */
#define LARGER_TASK_STACK_SIZE 640

/* Maximum number of deferrable functions */
#define DEFERRABLE_MAX_COUNT 8

#define GPIO_PIN(port, index) GPIO_##port, (1 << index)
#define GPIO_PIN_MASK(port, mask) GPIO_##port, (mask)

/* TODO_FPGA this should come from the generated .h file */
#define PCLK_FREQ  (24 * 1000 * 1000)

#endif /* __CROS_EC_CONFIG_CHIP_H */
