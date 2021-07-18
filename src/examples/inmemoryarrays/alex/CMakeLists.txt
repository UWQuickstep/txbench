add_subdirectory(alex_lib)

add_executable(
        inmemarrays_alex
        inmem_arrays_ALEX.cpp
        ../inmem_arrays_TATP_db.cpp
        inmem_arrays_TATP_db_ALEX.cpp
)

target_link_libraries(inmemarrays_alex
        txbench_tatp
        alex_lib)

target_include_directories(inmemarrays_alex
        PRIVATE ${CMAKE_SOURCE_DIR}/src
        PRIVATE Threads::Threads)

target_include_directories(inmemarrays_alex
        PRIVATE ${CMAKE_SOURCE_DIR}/src
        PRIVATE Threads::Threads
        PRIVATE ${BOOST_INCLUDE_DIRS}
        PRIVATE ${GLOG_INCLUDE_DIRS}
        PRIVATE ${GFLAG_INCLUDE_DIRS}
        PRIVATE ${JEMALLOC_INCLUDE_DIRS}
        )


target_link_libraries(inmemarrays_alex
        txbench_tatp
        glog
        /usr/local/Cellar/boost/1.72.0_1/lib/libboost_atomic-mt.a
        /usr/local/Cellar/boost/1.72.0_1/lib/libboost_chrono.a
        /usr/local/Cellar/boost/1.72.0_1/lib/libboost_thread-mt.a
        )