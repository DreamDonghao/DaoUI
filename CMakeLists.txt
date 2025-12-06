cmake_minimum_required(VERSION 3.31)
project(dao)

set(CMAKE_CXX_STANDARD 20)


# 为使用 eastl 添加的配置
project(eastl_support)
add_library(eastl_support STATIC
        code/src/eastl/eastl_support.cpp
)

target_compile_definitions(eastl_support PUBLIC
        EASTL_USER_DEFINED_NEW=1
        EASTL_USER_DEFINED_ASSERTION_FAILURE=1
)

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
        "code/src/app.cpp"
        "code/src/atlas_texture.cpp"
        "code/src/window.cpp"
        "code/src/mapped_region.cpp"
)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(dao PRIVATE SDL3::SDL3)

find_package(SDL3_image CONFIG REQUIRED)
target_link_libraries(dao PRIVATE SDL3_image::SDL3_image)

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(dao PRIVATE EnTT::EnTT)

target_link_libraries(dao PRIVATE eastl_support)

find_package(EASTL CONFIG REQUIRED)
target_link_libraries(dao PRIVATE EASTL)
if (MSVC)
    target_compile_options(dao PRIVATE "/constexpr:steps200000000")
endif ()
add_custom_command(
        TARGET dao POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/tool/example/atlas
        ${CMAKE_CURRENT_BINARY_DIR}/
)
