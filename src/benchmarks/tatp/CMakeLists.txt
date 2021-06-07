add_library(
        txbench_tatp
        tatp_benchmark.h tatp_benchmark.cpp
        tatp_connection.h
        tatp_server.h
        tatp_worker.h tatp_worker.cpp
)

target_include_directories(txbench_tatp PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(txbench_tatp txbench_utilities)
