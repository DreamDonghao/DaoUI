//
// Created by donghao on 25-12-1.
//
#ifndef TEXTURE_BATCH_BUILDER_HPP
#define TEXTURE_BATCH_BUILDER_HPP
#include <SDL3/SDL_render.h>
#include "texture_data.hpp"
#include <vector>
namespace dao {
    /// @brief 纹理图集绘制批
    /// @details 一次纹理图集绘制用到的数据
    struct AtlasDrawBatch {
        uint32_t atlasId;                 ///< 绘制的纹理图集 ID
        std::vector<SDL_Vertex> vertices; ///< 绘制纹理图集的顶点数组
        std::vector<int> indices;
    };

    /// @brief 纹理批处理构建器
    /// @details 用来将纹理构建为纹理图集处理数据
    class AtlasVertexBatchBuilder {
    public:
        AtlasVertexBatchBuilder() = default;

        /// @brief 禁用复制构造函数
        AtlasVertexBatchBuilder(const AtlasVertexBatchBuilder &) = delete;

        /// @brief 将一个纹理加入批处理
        void addToBatch(const TextureData &texture) {
            const AtlasRegion atlasRegion = getAtlasRegion(texture.getName());

            if (const uint32_t atlasId = atlasRegion.atlasId;
                m_drawBatches.empty() || atlasId != m_drawBatches.back().atlasId) {
                m_drawBatches.emplace_back(atlasId, std::vector<SDL_Vertex>());
            }
            appendQuadVertices(
                m_drawBatches.back().vertices, m_drawBatches.back().indices,
                texture.getBoundingBox(), texture.getName()
            );
        }

        /// @brief 清理要绘制的纹理图集
        /// @details 一般要每帧调用，否则会堆积上一帧的内容
        void clearDrawBatches() {
            m_drawBatches.clear();
        }

        /// @brief 获取将要绘制的所有内容的数据
        [[nodiscard]] const std::vector<AtlasDrawBatch> &getDrawBatches() const {
            return m_drawBatches;
        }

    private:
        std::vector<AtlasDrawBatch> m_drawBatches; ///< 一组纹理图集绘制的数据


        static inline void appendQuadVertices(
            std::vector<SDL_Vertex> &vertices,
            std::vector<int> &indices,
            const BoundingBox pos,
            const TextureEnum textureName
        ) {
            const int base = static_cast<int>(vertices.size());

            //indices.reserve(indices.size() + 6);
            indices.push_back(base + 0);
            indices.push_back(base + 1);
            indices.push_back(base + 2);
            indices.push_back(base + 2);
            indices.push_back(base + 3);
            indices.push_back(base + 0);

            const float winL = pos.getLeft();
            const float winR = pos.getRight();
            const float winT = pos.getTop();
            const float winB = pos.getBottom();

            const AtlasRegion atlasRegion = getAtlasRegion(textureName);

            const float normalized_texL = atlasRegion.normalizedLeft;
            const float normalized_texT = atlasRegion.normalizedTop;
            const float normalized_texR = atlasRegion.normalizedRight;
            const float normalized_texB = atlasRegion.normalizedBottom;

            vertices.push_back({{winL, winT}, {1, 1, 1, 1}, {normalized_texL, normalized_texT}});
            vertices.push_back({{winR, winT}, {1, 1, 1, 1}, {normalized_texR, normalized_texT}});
            vertices.push_back({{winR, winB}, {1, 1, 1, 1}, {normalized_texR, normalized_texB}});
            vertices.push_back({{winL, winB}, {1, 1, 1, 1}, {normalized_texL, normalized_texB}});
        }
    };
} // name_

#endif //TEXTURE_BATCH_BUILDER_HPP
