#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define DT_DRV_COMPAT my_led_driver

#define LED_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(my_led_driver, LOG_LEVEL_INF);

static int my_led_driver_channel_get(const struct device *dev,
                                     enum sensor_channel chan,
                                     struct sensor_value *val)
{
    if (gpio_pin_set(led.port, led.pin, 0) == 0)
    {
        LOG_INF("Turning LED off.");
    }
    return 0;
}

static int my_led_driver_channel_fetch(const struct device *dev,
                                       enum sensor_channel chan)
{
    if (gpio_pin_set(led.port, led.pin, 1) == 0)
    {
        LOG_INF("Turning LED on.");
    }
    return 0;
}

static DEVICE_API(sensor, my_led_driver_api) = {
    .channel_get = my_led_driver_channel_get,
    .sample_fetch = my_led_driver_channel_fetch,
};

static int my_led_driver_init(const struct device *dev)
{
    LOG_INF("Device Initialized!");
    return 0;
}

#define DEV_INST(inst) DEVICE_DT_INST_DEFINE(inst, my_led_driver_init, NULL, NULL, NULL, POST_KERNEL, 80, &my_led_driver_api);

DT_INST_FOREACH_STATUS_OKAY(DEV_INST);
