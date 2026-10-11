if(BOARD STREQUAL "host")
  set(BOARD_SRC host/board_host.cpp host/host_keypad.cpp host/host_lock.cpp)
else()
  message(FATAL_ERROR "door_demo has no target board file yet, use BOARD=host")
endif()

add_executable(door_demo main.cpp app/pin_code.cpp app/door_controller.cpp ${BOARD_SRC})
target_link_libraries(door_demo PRIVATE common)

add_test(NAME door_demo COMMAND door_demo)
set_tests_properties(door_demo PROPERTIES PASS_REGULAR_EXPRESSION "too many attempts, locked out")
