#ifndef MY_LED_DRIVER_H_
#define MY_LED_DRIVER_H_

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int my_led_driver_set_wait(const struct device *dev, int time);

#ifdef __cplusplus
}
#endif

#endif // MY_LED_DRIVER_H_