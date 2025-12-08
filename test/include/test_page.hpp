//
// Created by donghao on 25-12-8.
//
#ifndef TEST_PAGE_HPP
#define TEST_PAGE_HPP

#include <atlas_vertex_batch_builder.hpp>
#include <string>
#include <texture_id.hpp>
#include "interface/page.hpp"

class TestPage final : public dao::Page {
    dao::AtlasTexture appleImg{texture::food_apple, 0, 0, 100, 100};
    dao::AtlasTexture bananaImg{texture::food_banana, 100, 0, 200, 100};

public:
    explicit TestPage(std::string title): m_title(std::move(title)) {
    }

    [[nodiscard]] std::vector<uint32_t> registerTexture() override;

    void update() override;

    [[nodiscard]] const std::vector<dao::AtlasDrawBatch> &getDrawBatches() override;

    [[nodiscard]] const std::string &getTitle() override { return m_title; }

private:
    std::string m_title;
    dao::AtlasVertexBatchBuilder m_atlasVertexBatchBuilder;
};


#endif //TEST_PAGE_HPP
