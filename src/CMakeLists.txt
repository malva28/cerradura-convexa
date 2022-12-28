set(HEADER_FILE "${PROJECT_SOURCE_DIR}/include/convex_hull.h")

set(LIBRARY_NAME cerradura_convexa)

add_library(${LIBRARY_NAME} convexHullJarvis.h convexHullGraham.h ${HEADER_FILE})

set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${LIBRARY_NAME} INTERFACE ../include)