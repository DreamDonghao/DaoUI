//
// Created by donghao on 25-12-8.
//
#include "../include/test_page.hpp"
#include <component/rectangle.hpp>

std::vector<uint32_t> TestPage::registerTexture() const {
    std::vector registerTexture{
        texture::food_apple,
        texture::food_banana,
    };
    return registerTexture;
}

dao::Text text(300, 200, U"ab你好bc", 100, {0.5,0.3,0,1});

void TestPage::update() {
    m_atlasVertexBatchBuilder.clearDrawBatches();

    m_atlasVertexBatchBuilder.addToBatch(appleImg);

    m_atlasVertexBatchBuilder.addToBatch(bananaImg);

    rectangle2.writeToBatch(m_atlasVertexBatchBuilder);

    rectangle3.writeToBatch(m_atlasVertexBatchBuilder);
    buttonStyle.writeToBatch(m_atlasVertexBatchBuilder);
     m_atlasVertexBatchBuilder.addToBatch(text);
}

void TestPage::handleMessage(const SDL_Event &event) {
    button.update(event);
}

const std::vector<dao::AtlasDrawBatch> &TestPage::getDrawBatches() const {
    return m_atlasVertexBatchBuilder.getDrawBatches();
}

