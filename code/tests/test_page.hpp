//
// Created by donghao on 25-11-28.
//
#ifndef TESTPAGE_HPP
#define TESTPAGE_HPP
#include "page.hpp"

namespace dao {
    class TestPage final : public Page {

        AtlasTexture appleImg{TextureEnum::food_apple, 0, 0, 100, 100};
        AtlasTexture bananaImg{TextureEnum::food_banana, 100, 0, 200, 100};

    public:
        explicit TestPage(std::string title): Page(std::move(title)) {
        }

        [[nodiscard]] eastl::vector<TextureEnum> registerTexture() const override {
            eastl::vector registerTexture{
                TextureEnum::food_apple,
                TextureEnum::food_banana,
            };
            return registerTexture;
        }

        void update() override {
            m_atlasVertexBatchBuilder.clearDrawBatches();
            for (int i = 0; i < 300; ++i) {
                for (int j = 0; j < 200; ++j) {
                    m_atlasVertexBatchBuilder.addToBatch(appleImg);
                }
                for (int j = 0; j < 200; ++j) {
                    m_atlasVertexBatchBuilder.addToBatch(bananaImg);
                }
            }
        }



    private:
    };
}

#endif //TESTPAGE_HPP
