if(BOARD STREQUAL "host")
  set(BOARD_SRC host/board_host.cpp host/host_temp_sensor.cpp)
else()
  set(BOARD_SRC target/board_stm32.cpp target/stm32_temp_sensor.cpp)  # arm-none-eabi toolchain
endif()

add_executable(sensor_demo main.cpp app/temp_monitor.cpp ${BOARD_SRC})
target_link_libraries(sensor_demo PRIVATE common)

add_test(NAME sensor_demo COMMAND sensor_demo)
set_tests_properties(sensor_demo PROPERTIES PASS_REGULAR_EXPRESSION "ALARM")
