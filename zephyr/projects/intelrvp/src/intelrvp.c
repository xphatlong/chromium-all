/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "gpio.h"
#include "hooks.h"

static void board_init(void)
{
	/* Enable SOC SPI */
	gpio_set_level(GPIO_EC_SPI_OE_MECC, 1);
}
DECLARE_HOOK(HOOK_INIT, board_init, HOOK_PRIO_LAST);