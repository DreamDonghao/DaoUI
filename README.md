[中文](./docs/README.ch-ZN.md)

# Dao

This is a cross platform C++GUI program development framework that can be used to develop GUI programs and applications such as games.

## Use

Due to the project being in its early stages, the library files and framework system are being refined

### Environmental requirements

The following is a tested and constructible version, other versions can be tried on their own

- C++ 23
- Cmake 3.31
- Vcpkg: [sdl3 3.2.26] [sdl3-image 3.2.4 (png)] For specific content of third-party libraries, please refer to the vcpkg.json file

### Get started quickly

You can directly edit the contents of **main.cpp** and **test\u page.hpp** in the project to quickly familiarize yourself with how to use

```C++
/// code/main.cpp
#include <app.hpp>
#include <test_page.hpp>

int main(int argc, char *argv[]) {
    ///Create an app
    auto &app = dao::App::getApp();
    ///Create a window and add a page
    app.createWindow(800, 600)
            .addPage(std::make_unique<dao::TestPage>("test1"));
    ///Start up procedure
    app.run();
    return 0;
}

```

```c++
/// code/test/test_page.hpp
#ifndef TESTPAGE_HPP
#define TESTPAGE_HPP
#include "page.hpp"

namespace dao {
    class TestPage final : public Page {
        ///Texture atlas batch vertex array builder
        AtlasVertexBatchBuilder m_atlasVertexBatchBuilder;
        ///An apple picture
        TextureData appleImg{TextureEnum::food_apple, 0, 0, 100, 100};
        ///A banana picture
        TextureData bananaImg{TextureEnum::food_banana, 100, 0, 200, 100};

    public:
        explicit TestPage(std::string title): Page(std::move(title)) {
        }

        ///Submit the picture and load it into the video memory when creating the window
        [[nodiscard]] std::vector<TextureEnum> registerTexture() const override {
            std::vector registerTexture{
                TextureEnum::food_apple,
                TextureEnum::food_banana,
            };
            return registerTexture;
        }

        ///Update logic per frame of window
        void update() override {
            m_atlasVertexBatchBuilder.clearDrawBatches();
            for (int i = 0; i < 30; ++i) {
                for (int j = 0; j < 200; ++j) {
                    m_atlasVertexBatchBuilder.addToBatch(appleImg);
                }
                for (int j = 0; j < 200; ++j) {
                    m_atlasVertexBatchBuilder.addToBatch(bananaImg);
                }
            }
        }

        ///Submit vertex array drawing
        [[nodiscard]] const std::vector<AtlasDrawBatch> &getDrawBatches() const override {
            return m_atlasVertexBatchBuilder.getDrawBatches();
        }
    };
}

#endif //TESTPAGE_HPP

```