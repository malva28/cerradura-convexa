cmake_minimum_required(VERSION 3.20)


set(CONVEX_PROJECT_NAME
        cerradura_convexa
        )
set(CONVEX_SOURCE_DIR
        src
        )
#set(CONVEX_SOURCE
#        ${FOO_SOURCE_DIR}/main.cpp
#        )
set(CONVEX_LIBRARIES_DIR
        extern
        )
set(CONVEX_LIBRARIES
        elem_geometricos
        )

project(${CONVEX_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(test)

add_executable(convex_main main.cpp)


#quitar para evitar test
enable_testing()


target_link_libraries(convex_main PRIVATE ${CONVEX_LIBRARIES})


