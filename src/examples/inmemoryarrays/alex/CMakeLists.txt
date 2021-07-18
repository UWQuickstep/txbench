add_subdirectory(alex_lib)

add_executable(
        inmemarrays_alex
        inmem_arrays_ALEX.cpp
        ../inmem_arrays_TATP_db.cpp
        inmem_arrays_TATP_db_ALEX.cpp
)

target_link_libraries(inmemarrays_alex
PRIVATE Threads::Threads
        txbench_tatp
        alex_lib)

target_include_directories(inmemarrays_alex
        PRIVATE ${CMAKE_SOURCE_DIR}/src
        PRIVATE Threads::Threads)

target_include_directories(inmemarrays_alex
        PRIVATE ${CMAKE_SOURCE_DIR}/src
        PRIVATE Threads::Threads
        )


