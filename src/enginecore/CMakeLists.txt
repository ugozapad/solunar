set(ENGINECORE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB ENGINECORE_ENTITY_SRC
    "${ENGINECORE_SRC_DIR}/entity/*.cpp"
    "${ENGINECORE_SRC_DIR}/entity/*.h"
)

source_group(TREE ${ENGINECORE_SRC_DIR} FILES ${ENGINECORE_ENTITY_SRC})

add_library(enginecore STATIC
    ${ENGINECORE_ENTITY_SRC}
)

target_include_directories(enginecore PRIVATE "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(enginecore core)