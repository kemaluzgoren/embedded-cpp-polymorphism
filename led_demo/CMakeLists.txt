if(BOARD STREQUAL "host")
  set(BOARD_SRC host/board_host.cpp)
else()
  set(BOARD_SRC target/board_stm32.cpp)  # use with an arm-none-eabi toolchain file
endif()

add_executable(led_demo main.cpp ${BOARD_SRC})
target_link_libraries(led_demo PRIVATE common)

add_executable(vtable_demo vtable_demo.cpp)
target_link_libraries(vtable_demo PRIVATE common)

add_test(NAME led_demo COMMAND led_demo)
set_tests_properties(led_demo PROPERTIES PASS_REGULAR_EXPRESSION "button pressed")
add_test(NAME vtable_demo COMMAND vtable_demo)
