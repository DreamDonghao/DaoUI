include_directories(
        include
)

include_directories(
        ../tool/example/inc
)

add_library(dao
        src/app.cpp
        src/atlas_texture.cpp
        src/window.cpp
        src/mapped_region.cpp
        src/bounding_box.cpp
        src/vertex_batch_builder.cpp
        include/component/rectangle.hpp
        include/better_stl.hpp
)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

target_link_libraries(dao PRIVATE SDL3::SDL3 PRIVATE SDL3_image::SDL3_image)


if (MSVC)
    target_compile_options(dao PRIVATE "/constexpr:steps200000000")
endif ()

