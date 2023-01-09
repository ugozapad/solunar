set(CORE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB REFLECTION_SRC
    "${CORE_SRC_DIR}/reflection/*.cpp"
    "${CORE_SRC_DIR}/reflection/*.h"
)

file(GLOB FILESYSTEM_SRC
    "${CORE_SRC_DIR}/filesystem/*.cpp"
    "${CORE_SRC_DIR}/filesystem/*.h"
)

source_group(TREE ${CORE_SRC_DIR} FILES ${REFLECTION_SRC})
source_group(TREE ${CORE_SRC_DIR} FILES ${FILESYSTEM_SRC})

add_library(core STATIC
    ${REFLECTION_SRC}
    ${FILESYSTEM_SRC}
)

target_include_directories(core PRIVATE "${CMAKE_SOURCE_DIR}/src")

# GLM Linkage
target_include_directories(core PUBLIC "${CMAKE_SOURCE_DIR}/external/glm")
