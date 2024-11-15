/*
 * Copyright (c) 2024
 * Regis Rousseau
 * Univ Lyon, INSA Lyon, Inria, CITI, EA3720
 * SPDX-License-Identifier: Apache-2.0
 */

#include "app_lorawan.h"
#include "app_flash.h"

//  ======== interrupt sub-routine ===============================
void test_work_handler(struct k_work *work_rtc)
{
	int8_t grn_min = 0;
	int8_t grn_max = 3;
	int8_t grn_cnt = 10;
	const struct device *dev;

	printk("lorawan handler called\n");
	app_lorawan_handler(dev, grn_min, grn_max, count);
}
K_WORK_DEFINE(test_work, test_work_handler);

void test_timer_handler(struct k_timer *rtc_dum)
{
	k_work_submit(&test_work);
}
K_TIMER_DEFINE(test_timer, test_timer_handler, NULL);

//  ======== main ===============================================
int8_t main(void)
{
	struct nvs_fs fs;
	const struct device *dev;

	// initialization of all devices
	app_flash_init(&fs);
	// initialization of LoRaWAN
	app_lorawan_init(dev);

	printk("Geophone Measurement Simulation and Process Information\nBoard: %s\n", CONFIG_BOARD);

	// beginning of interrupt subroutine timer
	k_timer_start(&test_timer, K_NO_WAIT, K_MINUTES(30));		// for test
	return 0;
}