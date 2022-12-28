set(LIBS
        ${LIBS}
        elem_geometricos
        )

set(INCLUDES
        ${INCLUDES}
        ../extern/tinytest
        ../include/
        )

include_directories(../src/)

add_executable(testpunto testpunto.cpp)
target_link_libraries(testpunto PRIVATE ${LIBS})
target_include_directories(testpunto PUBLIC ${INCLUDES})

add_executable(testvector testvector.cpp)
target_link_libraries(testvector PRIVATE ${LIBS})
target_include_directories(testvector PUBLIC ${INCLUDES})

add_executable(testpoligono testpoligono.cpp)
target_link_libraries(testpoligono PRIVATE ${LIBS})
target_include_directories(testpoligono PUBLIC ${INCLUDES})

add_executable(testsegmento testsegmento.cpp)
target_link_libraries(testsegmento PRIVATE ${LIBS})
target_include_directories(testsegmento PUBLIC ${INCLUDES})
