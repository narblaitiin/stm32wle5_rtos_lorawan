/*
 * Copyright (c) 2024
 * Regis Rousseau
 * Univ Lyon, INSA Lyon, Inria, CITI, EA3720
 * SPDX-License-Identifier: Apache-2.0
 */

#include "app_lorawan.h"
#include "app_flash.h"


//  ======== globals ============================================
static const struct gpio_dt_spec led_tx = GPIO_DT_SPEC_GET(LED_TX, gpios);
static const struct gpio_dt_spec led_rx = GPIO_DT_SPEC_GET(LED_RX, gpios);

//  ======== main ===============================================
int8_t main(void)
{
	struct nvs_fs fs;
	const struct device *dev;
	uint16_t min = 0;			// min value of ADC
	uint16_t max = 3300;		// max value of ADC (12-bit - 4095)
	int8_t count = 10;

	// initialization of all devices
	app_flash_init(&fs);
	// initialization of LoRaWAN
	app_lorawan_init(dev);

	printk("Geophone Measurement Simulation and Process Information\nBoard: %s\n", CONFIG_BOARD);

	// beginning forever loop (polling mode)
	while (1) {
//		app_lorawan_handler(grn_min, grn_max, grn_cnt);
		    uint16_t data_tx[count];
    int8_t ret;

	for (int8_t itr = 0; itr < count; itr++) {
        data_tx[itr] = sys_rand16_get() % (max - min + 1) + min;
		printk("random value: %d mV\n", data_tx[itr]);
    }

    // transmission of packets on lorawan protocole
	printk("sending data...\n");

	ret = lorawan_send(2, data_tx, sizeof(data_tx), LORAWAN_MSG_CONFIRMED);
	if (ret == -EAGAIN) {
			printk("lorawan_send failed: %d. continuing...\n", ret);
			k_sleep(DELAY);
			continue;
	} else if (ret < 0) {
		printk("lorawan_send failed: %d.\n", ret);
		k_sleep(DELAY);
		//return 0;
		continue;
	}
    // flashing of the LED when a packet is transmitted
	ret = gpio_pin_toggle_dt(&led_tx);
	if (ret < 0) {
		return 0;
	}
	printk("data sent!\n"); 
		k_sleep(DELAY);
	}

	return 0;
}