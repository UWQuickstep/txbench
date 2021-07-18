
add_executable(
        inmemarrays_btree
        inmem_arrays_BTREE.cpp
        threadskv10h.c
        ../inmem_arrays_TATP_db.cpp
        inmem_arrays_TATP_db_BTREE.cpp
)

target_link_libraries(inmemarrays_btree
        txbench_tatp)

target_include_directories(inmemarrays_btree
        PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(inmemarrays_btree
        txbench_tatp
        )