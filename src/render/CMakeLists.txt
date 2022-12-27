set(RENDER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB RENDER_SRC
    "${RENDER_SRC_DIR}/*.cpp"
    "${RENDER_SRC_DIR}/*.h"
)

source_group(TREE ${RENDER_SRC_DIR} FILES ${RENDER_SRC})

add_library(render STATIC
    ${RENDER_SRC}
)

target_include_directories(render PRIVATE "${CMAKE_SOURCE_DIR}/src")