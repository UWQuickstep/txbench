add_library(
        txbench_utilities
        benchmark.h benchmark.cpp
        options.h options.cpp
        random_generator.h random_generator.cpp
        worker.h worker.cpp
)

target_link_libraries(txbench_utilities cxxopts)
