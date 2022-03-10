/* Copyright 2022 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <sys/atomic.h>
#include <logging/log.h>
#include <drivers/gpio.h>

#include <ap_power/ap_power.h>
#include <ap_power/ap_power_events.h>
#include <ap_power/ap_power_interface.h>
#include <power_signals.h>
#include <x86_power_signals.h>

#include "chipset.h"
#include "hooks.h"
#include "gpio/gpio.h"

LOG_MODULE_DECLARE(ap_pwrseq, LOG_LEVEL_INF);

#define  X86_NON_DSX_ADLP_NONPWRSEQ_FORCE_SHUTDOWN_TO_MS	5

static void generate_ec_soc_dsw_pwrok_handler(int delay)
{
	int in_sig_val = power_signal_get(PWR_DSW_PWROK);

	if (in_sig_val != power_signal_get(PWR_EC_SOC_DSW_PWROK)) {
		if (in_sig_val)
			k_msleep(delay);
		power_signal_set(PWR_EC_SOC_DSW_PWROK, 1);
	}
}

/* Override */
void ap_power_force_shutdown(enum ap_power_shutdown_reason reason)
{
	int timeout_ms = X86_NON_DSX_ADLP_NONPWRSEQ_FORCE_SHUTDOWN_TO_MS;

	power_signal_set(PWR_EC_PCH_RSMRST, 1);
	power_signal_set(PWR_EC_SOC_DSW_PWROK, 0);

	while (power_signal_get(PWR_RSMRST) == 0 &&
	      power_signal_get(PWR_SLP_SUS) == 0 && timeout_ms > 0) {
		k_msleep(1);
		timeout_ms--;
	}
	if (power_signal_get(PWR_SLP_SUS) == 0) {
		LOG_WRN("SLP_SUS is not deasserted! Assuming G3");
	}

	if (power_signal_get(PWR_RSMRST) == 1) {
		LOG_WRN("RSMRST is not deasserted! Assuming G3");
	}

	power_signal_set(PWR_EN_PP3300_A, 0);

	power_signal_set(PWR_EN_PP5000_A, 0);

	timeout_ms = X86_NON_DSX_ADLP_NONPWRSEQ_FORCE_SHUTDOWN_TO_MS;
	while (power_signal_get(PWR_DSW_PWROK) && timeout_ms > 0) {
		k_msleep(1);
		timeout_ms--;
	};

	if (power_signal_get(PWR_DSW_PWROK))
		LOG_WRN("DSW_PWROK didn't go low!  Assuming G3.");
	ap_power_ev_send_callbacks(AP_POWER_SHUTDOWN);
}

/* Override */
void g3s5_action_handler(int delay, int signal_timeout)
{
	LOG_DBG("Turning on PWR_EN_PP5000_A and PWR_EN_PP3300_A");
	power_signal_set(PWR_EN_PP5000_A, 1);
	power_signal_set(PWR_EN_PP3300_A, 1);

	power_wait_signals_timeout(IN_PGOOD_ALL_CORE, signal_timeout);

	generate_ec_soc_dsw_pwrok_handler(delay);
}

/* Override */
int generate_pch_pwrok_handler(int delay)
{
	/* Pass though PCH_PWROK */
	if (power_signal_get(PWR_PCH_PWROK) == 0) {
		k_msleep(delay);
		power_signal_set(PWR_PCH_PWROK, 1);
	}

	return 0;
}

int board_power_signal_get(enum power_signal signal)
{
	switch (signal) {
	default:
		LOG_ERR("Unknown signal for board get: %d", signal);
		return -EINVAL;

	case PWR_ALL_SYS_PWRGD:
		/*
		 * All system power is good.
		 * Checks that PWR_SLP_S3 is off, and
		 * the GPIO signal for all power good is set,
		 * and that the 1.05 volt line is ready.
		 */
		if (power_signal_get(PWR_SLP_S3)) {
			return 0;
		}
		if (!gpio_pin_get_dt(
		     GPIO_DT_FROM_NODELABEL(gpio_all_sys_pwrgd))) {
			return 0;
		}
		if (!power_signal_get(PWR_PG_PP1P05)) {
			return 0;
		}
		return 1;
	/*
	 * TODO: When upstreamed changes ready, remove.
	 * Temporary workaround for ADC signal.
	 * Assume always on.
	 */
	case PWR_DSW_PWROK:
		return 1;

	case PWR_PG_PP1P05:
		return 1;
	}
}

int board_power_signal_set(enum power_signal signal, int value)
{
	return -EINVAL;
}