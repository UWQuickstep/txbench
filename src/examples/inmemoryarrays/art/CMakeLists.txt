add_subdirectory(art_lib)

add_executable(
        inmemarrays_art
        inmem_arrays_ART.cpp
        ../inmem_arrays_TATP_db.cpp
        inmem_arrays_TATP_db_ART.cpp
)

target_link_libraries(inmemarrays_art
        txbench_tatp
        art_lib
        )

target_include_directories(inmemarrays_art
        PRIVATE ${CMAKE_SOURCE_DIR}/src)