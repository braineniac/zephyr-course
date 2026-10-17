if (CONFIG_MY_LED_DRIVER)
    target_sources(app PRIVATE my_led_driver.c)
endif()