if (CONFIG_MY_LED_DRIVER)
    target_sources(app PRIVATE my_led_driver.c)
    target_include_directories(app PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endif()