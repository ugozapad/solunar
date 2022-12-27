set(GLAD_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(glad STATIC "${GLAD_PATH}/src/glad.c")
target_include_directories(glad PUBLIC "${GLAD_PATH}/include")

target_link_libraries(glad PUBLIC ${CMAKE_DL_LIBS})