set(RENDER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB RENDER_SRC
    "${RENDER_SRC_DIR}/*.cpp"
    "${RENDER_SRC_DIR}/*.h"
)

file(GLOB RENDER_CORE_SRC
    "${RENDER_SRC_DIR}/core/*.cpp"
    "${RENDER_SRC_DIR}/core/*.h"
)

file(GLOB RENDER_CORE_GL_SRC
    "${RENDER_SRC_DIR}/core/gl/*.cpp"
    "${RENDER_SRC_DIR}/core/gl/*.h"
)

file(GLOB RENDER_CORE_DX11_SRC
    "${RENDER_SRC_DIR}/core/dx11/*.cpp"
    "${RENDER_SRC_DIR}/core/dx11/*.h"
)

source_group(TREE ${RENDER_SRC_DIR} FILES ${RENDER_SRC})
source_group(TREE ${RENDER_SRC_DIR} FILES ${RENDER_CORE_SRC})
source_group(TREE ${RENDER_SRC_DIR} FILES ${RENDER_CORE_GL_SRC})
source_group(TREE ${RENDER_SRC_DIR} FILES ${RENDER_CORE_DX11_SRC})

add_library(render STATIC
    ${RENDER_SRC}
    ${RENDER_CORE_SRC}
    ${RENDER_CORE_GL_SRC}
)

if (MSVC)
	target_sources(render PRIVATE ${RENDER_CORE_DX11_SRC})
endif()

target_include_directories(render PRIVATE "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(render core glfw glad)
