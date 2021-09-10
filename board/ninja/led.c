/* Copyright (c) 2015 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * Power LED control for Ninja
 */

#include "charge_state.h"
#include "chipset.h"
#include "gpio.h"
#include "hooks.h"
#include "led_common.h"
#include "pwm.h"
#include "util.h"

const enum ec_led_id supported_led_ids[] = {EC_LED_ID_POWER_LED};
const int supported_led_ids_count = ARRAY_SIZE(supported_led_ids);

enum led_color {
	LED_OFF = 0,
	LED_BLUE,

	/* Number of colors, not a color itself */
	LED_COLOR_COUNT
};

/* Brightness vs. color, for Power LED */
static const uint8_t color_brightness[LED_COLOR_COUNT] = {
	0,
	100,
};

/**
 * Set LED color
 *
 * @param color		Enumerated color value
 */
static void set_color(enum led_color color)
{
	pwm_set_duty(PWM_CH_LED_BLUE_POWER_LED, color_brightness[color]);
}

void led_get_brightness_range(enum ec_led_id led_id, uint8_t *brightness_range)
{
	brightness_range[EC_LED_COLOR_BLUE] = 100;
}

int led_set_brightness(enum ec_led_id led_id, const uint8_t *brightness)
{
	pwm_set_duty(PWM_CH_LED_BLUE_POWER_LED, brightness[EC_LED_COLOR_BLUE]);
	return EC_SUCCESS;
}

static void led_init(void)
{
	/* Configure GPIOs */
	gpio_config_module(MODULE_PWM_LED, 1);

	/*
	 * Enable PWMs and set to 0% duty cycle.  If they're disabled, the LM4
	 * seems to ground the pins instead of letting them float.
	 */
	pwm_enable(PWM_CH_LED_BLUE_POWER_LED, 1);
	set_color(LED_OFF);
}
DECLARE_HOOK(HOOK_INIT, led_init, HOOK_PRIO_DEFAULT);

/**
 * Called by hook task every 250 ms
 */
static void led_tick(void)
{
	static unsigned power_ticks;
	static int previous_state_suspend;

	power_ticks++;

	/* If we don't control the LED, nothing to do */
	if (!led_auto_control_is_enabled(EC_LED_ID_POWER_LED))
		return;

	if (chipset_in_state(CHIPSET_STATE_ON)) {
		set_color(LED_BLUE);
	} else if (chipset_in_state(CHIPSET_STATE_SUSPEND)) {
		if (!previous_state_suspend) {
			previous_state_suspend = 1;
			power_ticks = 0;
		}
		/* Flashing 1 sec on, 1 sec off */
		set_color((power_ticks % 8) < 4 ? LED_BLUE : LED_OFF);
		return;
	} else {
		set_color(LED_OFF);
	}

	previous_state_suspend = 0;

}
DECLARE_HOOK(HOOK_TICK, led_tick, HOOK_PRIO_DEFAULT);