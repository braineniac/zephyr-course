#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);


int main(void)
{
    bool led_state = true;

    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    const struct device* dev = DEVICE_DT_GET(DT_NODELABEL(my_led_dev0));
    if (!device_is_ready(dev)) {
        return -ENODEV;
    }
    
    struct sensor_value val;


    while (1) {
        //if (gpio_pin_toggle_dt(&led) < 0) return 0;
        sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
        
        //led_state = !led_state;
        //LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);

        sensor_sample_fetch_chan(dev, SENSOR_CHAN_AMBIENT_TEMP);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
