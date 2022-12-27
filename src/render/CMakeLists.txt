set(RENDER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB RENDER_SRC
    "${RENDER_SRC_DIR}/*.cpp"
    "${RENDER_SRC_DIR}/*.h"
)

file(GLOB RENDER_GL_SRC
    "${RENDER_SRC_DIR}/gl/*.cpp"
    "${RENDER_SRC_DIR}/gl/*.h"
)

source_group(TREE ${RENDER_SRC_DIR} FILES ${RENDER_SRC})
source_group(TREE ${RENDER_SRC_DIR} FILES ${RENDER_GL_SRC})

add_library(render STATIC
    ${RENDER_SRC}
    ${RENDER_GL_SRC}
)

target_include_directories(render PRIVATE "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(render glfw glad)
