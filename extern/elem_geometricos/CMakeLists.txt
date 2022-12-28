cmake_minimum_required(VERSION 3.19)

project(elem_geometricos)


set(CMAKE_CXX_STANDARD 17)


# subdirectories must have a CMakeList file or else these commands won't work
# that's why I'm not including tinytest here
add_subdirectory(src)
add_subdirectory(test)

add_executable(main main.cpp)

#target_include_directories(main PUBLIC elem_geometricos_lib include/)
#target_link_directories(main PUBLIC elem_geometricos_lib)
target_link_libraries(main elem_geometricos)

# there's an error raised occasionally that says:
# CMake can not determine linker language for target
# see: https://stackoverflow.com/questions/11801186/cmake-unable-to-determine-linker-language-with-c
# uncomment the line bellow if the error raises, it should be fixed importing punto.h library as
# interface in the src CMakeList.txt file though

# set_target_properties(elem_geometricos PROPERTIES LINKER_LANGUAGE CXX)
