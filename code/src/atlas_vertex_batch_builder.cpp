//
// Created by donghao on 25-12-8.
//
#include <atlas_vertex_batch_builder.hpp>
#include "atlas_region.hpp"

namespace dao {
    std::vector<int> dao::AtlasVertexBatchBuilder::s_qudaIndices = {};

    void AtlasVertexBatchBuilder::expandQudaIndicesTo(const size_t qudaCount) {
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

    void AtlasVertexBatchBuilder::resetQudaIndices(size_t qudaCount) {
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

    void AtlasVertexBatchBuilder::addToBatch(const AtlasTexture &texture) {
        const AtlasRegion atlasRegion = getAtlasRegion(texture.getName());
        if (const uint32_t atlasId = atlasRegion.atlasId;
            m_drawBatches.empty() || atlasId != m_drawBatches.back().atlasId) {
            m_drawBatches.emplace_back(atlasId, std::vector<SDL_Vertex>());
            m_drawBatches.back().indices = s_qudaIndices.data();
        }
        appendQuadVertices(
            m_drawBatches.back().vertices,
            texture.getBoundingBox(), texture.getName()
        );
    }

    void AtlasVertexBatchBuilder::addToBatch(const std::vector<SDL_Vertex>& v) {
        if (m_drawBatches.empty() || m_drawBatches.back().atlasId != 0) {
            m_drawBatches.emplace_back(0, std::vector<SDL_Vertex>());
        }
        m_drawBatches.back().vertices.insert(m_drawBatches.back().vertices.end(), v.begin(), v.end());
    }

    void AtlasVertexBatchBuilder::appendQuadVertices(std::vector<SDL_Vertex> &vertices, const BoundingBox pos,
        const uint32_t textureId) {
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
