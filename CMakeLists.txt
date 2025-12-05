cmake_minimum_required(VERSION 3.31)
project(dao)

set(CMAKE_CXX_STANDARD 23)

include_directories(
        code/include
        code/tests
)

include_directories(
        tool/example/inc
)

add_executable(
        dao
        "code/main.cpp"
)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(dao PRIVATE SDL3::SDL3)

find_package(SDL3_image CONFIG REQUIRED)
target_link_libraries(dao PRIVATE SDL3_image::SDL3_image)

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(dao PRIVATE EnTT::EnTT)

add_custom_command(
        TARGET dao POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/tool/example/atlas
        ${CMAKE_CURRENT_BINARY_DIR}/
)
