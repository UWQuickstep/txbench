add_executable(
        inmemarrays
        inmem_arrays.cpp
        inmem_arrays_TATP_db.cpp
)

target_include_directories(inmemarrays PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(inmemarrays txbench_tatp)
