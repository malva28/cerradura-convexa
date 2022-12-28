set(HEADER_FILE "${PROJECT_SOURCE_DIR}/include/elem_geometricos.h")

set(LIBRARY_NAME elem_geometricos)

add_library(${LIBRARY_NAME} Punto.h Vector.h Poligono.h Segmento.h FloatComparison.h ${HEADER_FILE})

set_target_properties(elem_geometricos PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${LIBRARY_NAME} INTERFACE ../include)