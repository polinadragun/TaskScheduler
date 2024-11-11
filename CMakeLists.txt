cmake_minimum_required(VERSION 3.27)
project(TaskScheduler)

set(CMAKE_C_STANDARD 23)

include_directories(.)
include_directories(lib)


add_executable(TaskScheduler
        lib/any.hpp
        lib/func_storage.hpp
        lib/node.hpp
        lib/scheduler.hpp
        main.cpp
        )

enable_testing()
add_subdirectory(tests)
