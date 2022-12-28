set(LIBS
        ${LIBS}
        elem_geometricos
        cerradura_convexa
        )

set(INCLUDES
        ${INCLUDES}
        ../include/
        )

include_directories(../src/)
add_subdirectory(timePerformance)

add_executable(testconvex testConvexHull.cpp)
target_link_libraries(testconvex PRIVATE gtest_main ${LIBS})
target_include_directories(testconvex PUBLIC ${INCLUDES})

add_executable(testregpoly testRegPolyFixture.cpp)
target_link_libraries(testregpoly PRIVATE gtest_main ${LIBS})
target_include_directories(testregpoly PUBLIC ${INCLUDES})

include(GoogleTest)
gtest_discover_tests(testconvex)
gtest_discover_tests(testregpoly)