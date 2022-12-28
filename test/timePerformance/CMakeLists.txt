set(LIBS
        ${LIBS}
        elem_geometricos
        )

set(INCLUDES
        ${INCLUDES}
        ../extern/tinytest
        ../../include/
        )
add_executable(performanceCH testPerformanceCH.cpp)
target_link_libraries(performanceCH PRIVATE ${LIBS})
target_include_directories(performanceCH PUBLIC ${INCLUDES})

add_executable(timeutil timeutil.cpp)
target_link_libraries(timeutil PRIVATE ${LIBS})
target_include_directories(timeutil PUBLIC ${INCLUDES})