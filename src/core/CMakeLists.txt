set(CORE_SRC "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB REFLECTION_SRC
    "${CORE_SRC}/reflection/*.cpp"
    "${CORE_SRC}/reflection/*.h"
)

file(GLOB FILESYSTEM_SRC
    "${CORE_SRC}/filesystem/*.cpp"
    "${CORE_SRC}/filesystem/*.h"
)

source_group(TREE ${CORE_SRC} FILES ${REFLECTION_SRC})
source_group(TREE ${CORE_SRC} FILES ${FILESYSTEM_SRC})

add_library(core STATIC
    ${REFLECTION_SRC}
    ${FILESYSTEM_SRC}
)

target_include_directories(core PRIVATE "${CMAKE_SOURCE_DIR}/src")