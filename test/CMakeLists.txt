include_directories(
        ../code/include
        ../tool/example/inc
        include
)

add_executable(dao_test
        src/main.cpp
        src/atlas_region.cpp
        src/test_page.cpp
)

target_link_libraries(dao_test PRIVATE dao)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(dao_test PRIVATE SDL3::SDL3)

if (MSVC)
    target_compile_options(dao_test PRIVATE "/constexpr:steps200000000")
endif ()

# 资源复制
add_custom_command(
        TARGET dao_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/tool/example/atlas
        ${CMAKE_CURRENT_BINARY_DIR}/
)
