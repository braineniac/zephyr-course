#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell_string_conv.h>

#include "my_led_driver.h"

static int fetch_handler(const struct shell *sh, size_t argc, char **argv) {
    const struct device* dev = DEVICE_DT_GET(DT_NODELABEL(my_led_dev0));
    sensor_sample_fetch_chan(dev, SENSOR_CHAN_AMBIENT_TEMP);
    shell_print(sh, "Fetched sample");
    return 0;
}

static int read_handler(const struct shell *sh, size_t argc, char **argv) {
    const struct device* dev = DEVICE_DT_GET(DT_NODELABEL(my_led_dev0));
    struct sensor_value val;
    int ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
    shell_print(sh, "Sensor channel: %d", ret);
    return 0;
}

static int info_handler(const struct shell *sh, size_t argc, char **argv) {
    const struct device* dev = DEVICE_DT_GET(DT_NODELABEL(my_led_dev0));
    shell_print(sh, "Device %s is %s", dev->name, device_is_ready(dev) ? "ready": "not ready");
    return 0;
}

static int set_handler(const struct shell *sh, size_t argc, char **argv) {

    int conv_err_ptr = 0;
    int wait = shell_strtoul(argv[1], 10, &conv_err_ptr);

    if ((argc != 2) || (conv_err_ptr != 0) || (wait > 1000)) {
        shell_error(sh, "Argument missing or out of range!");
        return -1;
    }

    const struct device* dev = DEVICE_DT_GET(DT_NODELABEL(my_led_dev0));
    my_led_driver_set_wait(dev, wait);
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
    SHELL_CMD(fetch, NULL, "Calls sensor_sample_fetch()", fetch_handler),
    SHELL_CMD(read, NULL, "Calls sensor_channel_get() and prints the result", read_handler),
    SHELL_CMD(info, NULL, "Prints device name and ready state", info_handler),
    SHELL_CMD_ARG(set, NULL, "Sets wait time in ms(0-1000)", set_handler, 2, 0),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_sensor, "Sensor commands", NULL);
