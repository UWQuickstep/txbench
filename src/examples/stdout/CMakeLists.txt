add_executable(
        stdout_tatp stdout_tatp.cpp
)

target_include_directories(stdout_tatp
        PRIVATE ${CMAKE_SOURCE_DIR}/src
        PRIVATE Threads::Threads)

target_link_libraries(stdout_tatp txbench_tatp)
