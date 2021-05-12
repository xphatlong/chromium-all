/* Copyright 2021 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef __CROS_EC_POWER_QCOM_H_
#define __CROS_EC_POWER_QCOM_H_

enum power_signal {
	SC7X80_AP_RST_ASSERTED = 0,
	SC7X80_PS_HOLD,
	SC7X80_POWER_GOOD,
	SC7X80_WARM_RESET,
	SC7X80_AP_SUSPEND,
	SC7X80_DEPRECATED_AP_RST_REQ,
	POWER_SIGNAL_COUNT,
};

/* Swithcap functions */
void board_set_switchcap_power(int enable);
int board_is_switchcap_enabled(void);
int board_is_switchcap_power_good(void);

#endif /* __CROS_EC_POWER_QCOM_H_ */
