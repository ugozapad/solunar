set(LAUNCH_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB LAUNCH_SRC
    "${LAUNCH_SRC_DIR}/*.cpp"
    "${LAUNCH_SRC_DIR}/*.h"
)

add_executable(launch ${LAUNCH_SRC})

target_include_directories(launch PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_include_directories(launch PRIVATE "${CMAKE_SOURCE_DIR}/external/stb")

target_link_libraries(launch glfw core render enginecore game)

if (APPLE)
    set_target_properties(launch PROPERTIES XCODE_GENERATE_SCHEME TRUE)
    set_target_properties(launch PROPERTIES XCODE_SCHEME_WORKING_DIRECTORY "${SOLUNAR_ROOT}/")
endif()