//
// Created by donghao on 25-12-8.
//
#ifndef TEST_PAGE_HPP
#define TEST_PAGE_HPP
#include <vertex_batch_builder.hpp>
#include <string>
#include <texture_id.hpp>
#include <component/simple_button_style.hpp>
#include "component/simple_button.hpp"
#include "component/rectangle.hpp"
#include "interface/page.hpp"

class TestPage final : public dao::Page {
    dao::AtlasTexture appleImg{texture::food_apple, 0, 0, 100, 100};
    dao::AtlasTexture bananaImg{texture::food_banana, 100, 0, 200, 100};
    dao::Rectangle rectangle{200, 0, 100, 100, dao::hexToRGBA("#25B1F3")};
    dao::Rectangle rectangle2{0, 100, 200, 100, {0, 255, 0, 1.0f}};
    dao::Rectangle rectangle3{0, 200, 200, 100, {0, 0, 255, 1.0f}};
    dao::SimpleButton button{
        200, 200, 100, 100, dao::ButtonStatus::Normal,
        []() {
            static int i = 0;
            std::cout << "button pressed   " << i++ << std::endl;
        }
    };
    dao::SimpleButtonStyle buttonStyle{
        200, 200, 100, 100, texture::food_apple, texture::food_apple, texture::food_banana, &button
    };

public:
    explicit TestPage(std::string title): m_title(std::move(title)) {
    }

    [[nodiscard]] std::vector<dao::uint32> registerTexture() const override;

    void update() override;

    void handleMessage(const SDL_Event &event) override;

    [[nodiscard]] const std::vector<dao::AtlasDrawBatch> &getDrawBatches() const override;

    dao::GlyphAtlas &getGlyphAtlas() override {
        return m_atlasVertexBatchBuilder.getGlyphAtlas();
    }

    [[nodiscard]] const std::string &getTitle() const override { return m_title; }

private:
    std::string m_title;
    dao::VertexBatchBuilder m_atlasVertexBatchBuilder{"zh-cn.ttf", 64, 1024};
};


#endif //TEST_PAGE_HPP
