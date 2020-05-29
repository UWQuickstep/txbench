cmake_minimum_required(VERSION 3.15)
project(txbench)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

add_subdirectory(benchmarks)

add_library(
        txbench
        benchmark.h benchmark.cpp
        loader.h
        worker.h
        random_generator.h random_generator.cpp
)

target_include_directories(
        txbench
        PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
        txbench
        Threads::Threads
)
