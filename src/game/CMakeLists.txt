set(GAME_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB GAME_RENDER_SRC
    "${GAME_SRC_DIR}/render/*.cpp"
    "${GAME_SRC_DIR}/render/*.h"
)

source_group(TREE ${GAME_SRC_DIR} FILES ${GAME_RENDER_SRC})

add_library(game STATIC
    ${GAME_RENDER_SRC}
)

target_include_directories(game PRIVATE "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(game enginecore render core)