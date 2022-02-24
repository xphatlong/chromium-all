/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#define DT_DRV_COMPAT cros_ec_usba_port_enable_pins

#include <devicetree.h>
#include "hooks.h"

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

BUILD_ASSERT(DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) > 0,
		"No compatible USBA Port Enable instance found");

const int usb_port_enable[] = {
	DT_FOREACH_CHILD(DT_PATH(usba_port_enable_list), GPIO_SIGNAL_WITH_COMMA)
};

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */