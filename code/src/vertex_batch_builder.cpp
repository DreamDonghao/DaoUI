//
// Created by donghao on 25-12-8.
//
#include <span>
#include <vertex_batch_builder.hpp>
#include "atlas_region.hpp"
#include <print>

namespace dao {
    std::vector<int> VertexBatchBuilder::s_qudaIndices = {};

    VertexBatchBuilder::VertexBatchBuilder(
        const std::string_view fontPath, const float32 glyphSize,
        const int32 atlasSize, const size_t qudaCount)
        : m_glyphAtlas(fontPath, glyphSize, atlasSize) {
        expandQudaIndicesTo(qudaCount);
    }

    void VertexBatchBuilder::expandQudaIndicesTo(const size_t qudaCount) {
        if (qudaCount * 6 > s_qudaIndices.size()) {
            const size_t oldSize = s_qudaIndices.size();
            s_qudaIndices.resize(qudaCount * 6);
            for (std::size_t i = oldSize; i < qudaCount; ++i) {
                const int base = static_cast<int>(i) * 4;
                s_qudaIndices[i * 6 + 0] = base + 0;
                s_qudaIndices[i * 6 + 1] = base + 1;
                s_qudaIndices[i * 6 + 2] = base + 2;
                s_qudaIndices[i * 6 + 3] = base + 2;
                s_qudaIndices[i * 6 + 4] = base + 3;
                s_qudaIndices[i * 6 + 5] = base + 0;
            }
        }
    }

    void VertexBatchBuilder::resetQudaIndices(const size_t qudaCount) {
        if (qudaCount * 6 > s_qudaIndices.size()) {
            const size_t oldSize = s_qudaIndices.size();
            s_qudaIndices.resize(qudaCount * 6);
            for (std::size_t i = oldSize; i < qudaCount; ++i) {
                const int base = static_cast<int>(i) * 4;
                s_qudaIndices[i * 6 + 0] = base + 0;
                s_qudaIndices[i * 6 + 1] = base + 1;
                s_qudaIndices[i * 6 + 2] = base + 2;
                s_qudaIndices[i * 6 + 3] = base + 2;
                s_qudaIndices[i * 6 + 4] = base + 3;
                s_qudaIndices[i * 6 + 5] = base + 0;
            }
        } else {
            s_qudaIndices.resize(qudaCount * 6);
            s_qudaIndices.shrink_to_fit();
        }
    }

    void VertexBatchBuilder::addToBatch(const AtlasTexture &texture) {
        const AtlasRegion atlasRegion = getAtlasRegion(texture.getName());
        if (const uint32 atlasId = atlasRegion.atlasId;
                m_drawBatches.empty() || atlasId != m_drawBatches.back().atlasId
            ) {
            m_drawBatches.emplace_back(atlasId, std::vector<SDL_Vertex>(), makeObserver(&s_qudaIndices));
        }
        appendQuadVertices(
            m_drawBatches.back().vertices,
            texture.getBoundingBox(), texture.getName()
        );
    }

    void VertexBatchBuilder::addToBatch(const std::span<const SDL_Vertex> v, const std::span<const int32> indices) {
        if (m_drawBatches.empty() || m_drawBatches.back().atlasId != 0) {
            m_drawBatches.emplace_back(0, std::vector<SDL_Vertex>(), makeManage(new std::vector<int32>()));
        }
        const auto offset = static_cast<int32>(m_drawBatches.back().vertices.size());
        m_drawBatches.back().vertices.insert(m_drawBatches.back().vertices.end(), v.begin(), v.end());
        auto &current_indices = *m_drawBatches.back().indices;
        for (const int32 index: indices) {
            current_indices.push_back(index + offset);
        }
    }

    void VertexBatchBuilder::addToBatch(const Text &text) {
        if (m_drawBatches.empty() || m_drawBatches.back().atlasId != 1) {
            m_drawBatches.emplace_back(1, std::vector<SDL_Vertex>(), makeObserver(&s_qudaIndices));
        }
        auto &vertices = m_drawBatches.back().vertices;
        float x = text.getX();
        const float y = text.getY();
        for (const auto &ch: text.getContent()) {
            m_glyphAtlas.registerGlyph(ch);
            auto b = m_glyphAtlas.getGlyphAtlasRegion(ch);
            vertices.push_back({
                {x, y},
                text.getColor(),
                {b.getLeft(), b.getTop()}
            });
            vertices.push_back(
                {
                    {x + 50, y},
                    text.getColor(),
                    {b.getRight(), b.getTop()}
                });
            vertices.push_back({
                {x + 50, y + 50},
                text.getColor(),
                {b.getRight(), b.getBottom()}
            });
            vertices.push_back({
                {x, y + 50},
                text.getColor(),
                {b.getLeft(), b.getBottom()}
            });
            x += 50;
        }
    }

    void VertexBatchBuilder::appendQuadVertices(std::vector<SDL_Vertex> &vertices, const BoundingBox pos,
                                                const uint32 textureId) {
        const float winL = pos.getLeft();
        const float winT = pos.getTop();
        const float winR = pos.getRight();
        const float winB = pos.getBottom();
        const AtlasRegion atlasRegion = getAtlasRegion(textureId);
        const float normalized_texL = atlasRegion.normalizedLeft;
        const float normalized_texT = atlasRegion.normalizedTop;
        const float normalized_texR = atlasRegion.normalizedRight;
        const float normalized_texB = atlasRegion.normalizedBottom;
        vertices.push_back({{winL, winT}, {1, 1, 1, 1}, {normalized_texL, normalized_texT}});
        vertices.push_back({{winR, winT}, {1, 1, 1, 1}, {normalized_texR, normalized_texT}});
        vertices.push_back({{winR, winB}, {1, 1, 1, 1}, {normalized_texR, normalized_texB}});
        vertices.push_back({{winL, winB}, {1, 1, 1, 1}, {normalized_texL, normalized_texB}});
    }
}
