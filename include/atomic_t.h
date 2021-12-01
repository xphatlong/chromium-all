/* Copyright 2021 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* This file is to provide atomic_t definition */

#ifndef __CROS_EC_ATOMIC_T_H
#define __CROS_EC_ATOMIC_T_H

#ifndef CONFIG_ZEPHYR
typedef int atomic_t;
typedef atomic_t atomic_val_t;
#else
#include <sys/atomic.h>
#endif

#endif  /* __CROS_EC_ATOMIC_T_H */
