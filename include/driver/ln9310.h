/* Copyright 2020 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * LION Semiconductor LN-9310 switched capacitor converter.
 */

#ifndef __CROS_EC_LN9310_H
#define __CROS_EC_LN9310_H

#include "gpio.h"

/* I2C address */
#define LN9310_I2C_ADDR_0_FLAGS		0x72
#define LN9310_I2C_ADDR_1_FLAGS		0x73
#define LN9310_I2C_ADDR_2_FLAGS		0x53
#define LN9310_I2C_ADDR_3_FLAGS		0x54

/* Registers */
#define LN9310_REG_CHIP_ID		0x00
#define LN9310_CHIP_ID			0x44
#define LN9310_REG_INT1			0x01
#define LN9310_REG_INT1_MSK		0x02
#define LN9310_INT1_TIMER		BIT(0)
#define LN9310_INT1_INFET		BIT(1)
#define LN9310_INT1_TEMP		BIT(2)
#define LN9310_INT1_REV_CURR		BIT(3)
#define LN9310_INT1_MODE		BIT(4)
#define LN9310_INT1_ALARM		BIT(5)
#define LN9310_INT1_OK			BIT(6)
#define LN9310_INT1_FAULT		BIT(7)

#define LN9310_REG_SYSGPIO_MSK		0x03

#define LN9310_REG_SYS_STS		0x04
#define LN9310_SYS_STANDBY		BIT(0)
#define LN9310_SYS_SWITCHING21_ACTIVE	BIT(1)
#define LN9310_SYS_SWITCHING31_ACTIVE	BIT(2)
#define LN9310_SYS_BYPASS_ACTIVE	BIT(3)
#define LN9310_SYS_INFET_OK		BIT(4)
#define LN9310_SYS_SC_OUT_SWITCH_OK	BIT(5)
#define LN9310_SYS_INFET_OUT_SWITCH_OK	BIT(6)

#define LN9310_REG_SAFETY_STS		0x05
#define LN9310_REG_FAULT1_STS		0x06
#define LN9310_REG_FAULT2_STS		0x07

#define LN9310_REG_PWR_CTRL		0x1d
#define LN9310_PWR_OP_MODE0		BIT(0)
#define LN9310_PWR_OP_MODE1		BIT(1)
#define LN9310_PWR_INFET_EN		BIT(2)
#define LN9310_PWR_INFET_AUTO_MODE	BIT(3)
#define LN9310_PWR_REVERSE_MODE		BIT(4)
#define LN9310_PWR_VIN_OV_IGNORE	BIT(5)
#define LN9310_PWR_OP_MANUAL_UPDATE	BIT(6)
#define LN9310_PWR_FORCE_INSNS_EN	BIT(7)
#define LN9310_PWR_OP_MODE_MASK		0x03
#define LN9310_PWR_OP_MODE_DISABLED	0x00
#define LN9310_PWR_OP_MODE_BYPASS	0x01
#define LN9310_PWR_OP_MODE_SWITCH21	0x02
#define LN9310_PWR_OP_MODE_SWITCH31	0x03
#define LN9310_PWR_OP_MODE_MANUAL_UPDATE_MASK	0x40
#define LN9310_PWR_OP_MODE_MANUAL_UPDATE_OFF	0x00
#define LN9310_PWR_INFET_AUTO_MODE_MASK		0x08
#define LN9310_PWR_INFET_AUTO_MODE_ON		0x08
#define LN9310_PWR_INFET_AUTO_MODE_OFF		0x00

#define LN9310_REG_SYS_CTRL		0x1e

#define LN9310_REG_STARTUP_CTRL			0x1f
#define LN9310_STARTUP_STANDBY_EN				BIT(0)
#define LN9310_STARTUP_SELECT_EXT_5V_FOR_VDR	BIT(3)

#define LN9310_REG_IIN_CTRL		0x20
#define LN9310_REG_VIN_CTRL		0x21

#define LN9310_REG_TRACK_CTRL		0x22
#define LN9310_TRACK_INFET_OUT_SWITCH_OK_EN			BIT(7)
#define LN9310_TRACK_INFET_OUT_SWITCH_OK_CFG2		BIT(6)
#define LN9310_TRACK_INFET_OUT_SWITCH_OK_CFG1		BIT(5)
#define LN9310_TRACK_INFET_OUT_SWITCH_OK_CFG0		BIT(4)
#define LN9310_TRACK_INFET_OUT_SWITCH_OK_EN_MASK	0x80
#define LN9310_TRACK_INFET_OUT_SWITCH_OK_EN_ON		0x80
#define LN9310_TRACK_INFET_OUT_SWITCH_OK_EN_OFF		0x00
#define LN9310_TRACK_INFET_OUT_SWITCH_OK_CFG_MASK	0x70
#define LN9310_TRACK_INFET_OUT_SWITCH_OK_CFG_10V	0x10

#define LN9310_REG_OCP_CTRL		0x23

#define LN9310_REG_TIMER_CTRL		0x24
#define LN9310_TIMER_OP_SELF_SYNC_EN		BIT(3)
#define LN9310_TIMER_OP_SELF_SYNC_EN_MASK	0x08
#define LN9310_TIMER_OP_SELF_SYNC_EN_ON		0x08

#define LN9310_REG_RECOVERY_CTRL	0x25

#define LN9310_REG_LB_CTRL		0x26
#define LN9310_LB_MIN_FREQ_EN	BIT(2)
#define LN9310_LB_DELTA_MASK	0x38
#define LN9310_LB_DELTA_2S		0x20
#define LN9310_LB_DELTA_3S		0x20

#define LN9310_REG_SC_OUT_OV_CTRL	0x29
#define LN9310_REG_STS_CTRL		0x2d

#define LN9310_REG_MODE_CHANGE_CFG	0x2e
#define LN9310_MODE_TM_VIN_OV_CFG0		BIT(0)
#define LN9310_MODE_TM_VIN_OV_CFG1		BIT(1)
#define LN9310_MODE_TM_VIN_OV_CFG2		BIT(2)
#define LN9310_MODE_TM_SC_OUT_PRECHG_CFG0	BIT(3)
#define LN9310_MODE_TM_SC_OUT_PRECHG_CFG1	BIT(4)
#define LN9310_MODE_TM_TRACK_CFG0		BIT(5)
#define LN9310_MODE_TM_TRACK_CFG1		BIT(6)
#define LN9310_MODE_FORCE_MODE_CFG		BIT(7)
#define LN9310_MODE_TM_TRACK_MASK		0x60
#define LN9310_MODE_TM_TRACK_BYPASS		0x00
#define LN9310_MODE_TM_TRACK_SWITCH21		0x20
#define LN9310_MODE_TM_TRACK_SWITCH31		0x60
#define LN9310_MODE_TM_SC_OUT_PRECHG_MASK	0x18
#define LN9310_MODE_TM_SC_OUT_PRECHG_BYPASS	0x0
#define LN9310_MODE_TM_SC_OUT_PRECHG_SWITCH21	0x08
#define LN9310_MODE_TM_SC_OUT_PRECHG_SWITCH31	0x18
#define LN9310_MODE_TM_VIN_OV_CFG_MASK		0x07
#define LN9310_MODE_TM_VIN_OV_CFG_2S		0x0  /* 14V */
#define LN9310_MODE_TM_VIN_OV_CFG_3S		0x2  /* 20V */

#define LN9310_REG_SPARE_0	0x2A
#define LN9310_SPARE_0_SW4_BEFORE_BSTH_BSTL_EN_CFG_MASK	0x40
#define LN9310_SPARE_0_SW4_BEFORE_BSTH_BSTL_EN_CFG_ON	0x40
#define LN9310_SPARE_0_LB_MIN_FREQ_SEL_MASK	0x10
#define LN9310_SPARE_0_LB_MIN_FREQ_SEL_ON	0x10

#define LN9310_REG_SC_DITHER_CTRL	0x2f

#define LN9310_REG_LION_CTRL				0x30
#define LN9310_LION_CTRL_MASK				0xFF
#define LN9310_LION_CTRL_UNLOCK_AND_EN_TM	0xAA
#define LN9310_LION_CTRL_UNLOCK				0x5B
/*
 * value changed to 0x22 to distinguish from reset value of 0x00
 * 0x22 and 0x00 are functionally equivalent within LN9310
 */
#define LN9310_LION_CTRL_LOCK				0x22

#define LN9310_REG_CFG_0	0x3C
#define LN9310_CFG_0_LS_HELPER_IDLE_MSK_MASK	0x20
#define LN9310_CFG_0_LS_HELPER_IDLE_MSK_ON		0x20

#define LN9310_REG_CFG_4	0x40
#define LN9310_CFG_4_SC_OUT_PRECHARGE_EN_TIME_CFG		BIT(2)
#define LN9310_CFG_4_SW1_VGS_SHORT_EN_MSK				BIT(3)
#define LN9310_CFG_4_SC_OUT_PRECHARGE_EN_TIME_CFG_MASK 	0x04
#define LN9310_CFG_4_SW1_VGS_SHORT_EN_MSK_MASK			0x08
#define LN9310_CFG_4_BSTH_BSTL_HIGH_ROUT_CFG_MASK		0xC0
#define LN9310_CFG_4_SC_OUT_PRECHARGE_EN_TIME_CFG_ON 	0x04
#define LN9310_CFG_4_SW1_VGS_SHORT_EN_MSK_OFF			0x00
#define LN9310_CFG_4_BSTH_BSTL_HIGH_ROUT_CFG_LOWEST		0x00

#define LN9310_REG_CFG_5	0x41
#define LN9310_CFG_5_INGATE_PD_EN_MASK		0xC0
#define LN9310_CFG_5_INGATE_PD_EN_OFF		0x00
#define LN9310_CFG_5_INFET_CP_PD_BIAS_CFG_MASK		0x30
#define LN9310_CFG_5_INFET_CP_PD_BIAS_CFG_LOWEST	0x00

#define LN9310_REG_TEST_MODE_CTRL	0x46
#define LN9310_TEST_MODE_CTRL_FORCE_SC_OUT_PRECHARGE_MASK		0x40
#define LN9310_TEST_MODE_CTRL_FORCE_SC_OUT_PRECHARGE_ON			0x40
#define LN9310_TEST_MODE_CTRL_FORCE_SC_OUT_PRECHARGE_OFF		0x00
#define LN9310_TEST_MODE_CTRL_FORCE_SC_OUT_PREDISCHARGE_MASK	0x20
#define LN9310_TEST_MODE_CTRL_FORCE_SC_OUT_PREDISCHARGE_ON		0x20
#define LN9310_TEST_MODE_CTRL_FORCE_SC_OUT_PREDISCHARGE_OFF		0x00

#define LN9310_REG_FORCE_SC21_CTRL_1	0x49
#define LN9310_FORCE_SC21_CTRL_1_TM_SC_OUT_CFLY_PRECHARGE_MASK	0xFF
#define LN9310_FORCE_SC21_CTRL_1_TM_SC_OUT_CFLY_PRECHARGE_ON	0x59
#define LN9310_FORCE_SC21_CTRL_1_TM_SC_OUT_CFLY_PRECHARGE_OFF	0x40

#define LN9310_REG_FORCE_SC21_CTRL_2	0x4A
#define LN9310_FORCE_SC21_CTRL_2_FORCE_SW_CTRL_REQ_MASK		0x80
#define LN9310_FORCE_SC21_CTRL_2_FORCE_SW_CTRL_REQ_ON		0x80
#define LN9310_FORCE_SC21_CTRL_2_FORCE_SW_CTRL_REQ_OFF		0x00

#define LN9310_REG_SWAP_CTRL_0	0x58
#define LN9310_REG_SWAP_CTRL_1	0x59
#define LN9310_REG_SWAP_CTRL_2	0x5A
#define LN9310_REG_SWAP_CTRL_3	0x5B

#define LN9310_REG_BC_STS_B		0x51
#define LN9310_BC_STS_B_INFET_OUT_SWITCH_OK		BIT(5)
#define LN9310_BC_STS_B_INFET_OUT_SWITCH_OK_MASK	0x20

#define LN9310_REG_BC_STS_C				0x52
#define LN9310_BC_STS_C_CHIP_REV_MASK	0xF0
#define LN9310_BC_STS_C_CHIP_REV_FIXED	0x40

/* LN9310 Timing definition */
#define LN9310_CDC_DELAY 				120	/* 120us */
#define LN9310_CFLY_PRECHARGE_DELAY 	(12*MSEC)
#define LN9310_CFLY_PRECHARGE_TIMEOUT	(100*MSEC)

/* LN9310 Driver Configuration */
#define LN9310_INIT_RETRY_COUNT 3

/* Define configuration of LN9310 part */
struct ln9310_config_t {
	const int i2c_port;
	const int i2c_addr_flags;
};

/* Configuration struct defined at board level */
extern const struct ln9310_config_t ln9310_config;

/* Init the driver */
void ln9310_init(void);

/* Enable/disable the ln9310 output */
void ln9310_software_enable(int enable);

/* Interrupt handler */
void ln9310_interrupt(enum gpio_signal signal);

/* Return the POWER_GOOD status */
int ln9310_power_good(void);

/* Battery cell type */
enum battery_cell_type {
	BATTERY_CELL_TYPE_UNKNOWN = 0,
	BATTERY_CELL_TYPE_2S = 2,
	BATTERY_CELL_TYPE_3S = 3
};

enum battery_cell_type board_get_battery_cell_type(void);

#endif /* __CROS_EC_LN9310_H */
