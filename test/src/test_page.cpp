//
// Created by donghao on 25-12-8.
//
#include "../include/test_page.hpp"

std::vector<uint32_t> TestPage::registerTexture() {
    std::vector registerTexture{
        texture::food_apple,
        texture::food_banana,
    };
    return registerTexture;
}

void TestPage::update() {
    m_atlasVertexBatchBuilder.clearDrawBatches();

    m_atlasVertexBatchBuilder.addToBatch(appleImg);

    m_atlasVertexBatchBuilder.addToBatch(bananaImg);


    std::vector<SDL_Vertex> vertices(3);

    vertices[0] = {
        {0.0f, 0.0f},
        {0.5f, 0.5f, 0.5f, 1},
        {0.0f, 0.0f}
    };

    vertices[1] = {
        {0.0f, 100.0f},
        {0.5f, 0.5f, 0.5f, 1},
        {0.0f, 1.0f}
    };

    vertices[2] = {
        {100.0f, 100.0f},
        {0.5f, 0.5f, 0.5f, 1},
        {1.0f, 1.0f}
    };

    m_atlasVertexBatchBuilder.addToBatch(vertices);
}

const std::vector<dao::AtlasDrawBatch> & TestPage::getDrawBatches() {
    return m_atlasVertexBatchBuilder.getDrawBatches();
}
