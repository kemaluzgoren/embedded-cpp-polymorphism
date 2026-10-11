cmake_minimum_required(VERSION 3.16)
project(embedded_demos CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOARD host CACHE STRING "host | stm32")
if(NOT BOARD STREQUAL "host" AND NOT BOARD STREQUAL "stm32")
  message(FATAL_ERROR "Unknown BOARD: ${BOARD}")
endif()

# Shared HAL: demos include it as "common/hal.hpp".
add_library(common INTERFACE)
target_include_directories(common INTERFACE ${CMAKE_SOURCE_DIR})

enable_testing()  # each demo is also a smoke test (ctest)

add_subdirectory(led_demo)
add_subdirectory(sensor_demo)
add_subdirectory(door_demo)
