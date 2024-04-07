cmake_minimum_required(VERSION 3.5)

project(s_terra_test_task LANGUAGES C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SRC_C "src/*.c" SRC_H "src/*.h")
add_executable(s_terra_test_task ${SRC_C} ${SRC_H})

install(TARGETS s_terra_test_task
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
