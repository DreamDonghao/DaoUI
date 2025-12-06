//
// Created by donghao on 25-12-1.
//
#ifndef TEXTURE_BATCH_BUILDER_HPP
#define TEXTURE_BATCH_BUILDER_HPP
#include <SDL3/SDL_render.h>
#include "atlas_texture.hpp"
#include "atlas_region_data.hpp"
#include "EASTL/vector.h"
#include <quad_index.hpp>

namespace dao {
    /// @brief 纹理图集绘制批
    /// @details 一次纹理图集绘制用到的数据
    struct AtlasDrawBatch {
        uint32_t atlasId;                   ///< 绘制的纹理图集 ID
        eastl::vector<SDL_Vertex> vertices; ///< 绘制纹理图集的顶点数组
        const int *indices = nullptr;
    };

    /// @brief 纹理批处理构建器
    /// @details 用来将纹理构建为纹理图集处理数据
    template<std::size_t QuadCount>
    class AtlasVertexBatchBuilder {
    public:
        AtlasVertexBatchBuilder() = default;

        /// @brief 禁用复制构造函数
        AtlasVertexBatchBuilder(const AtlasVertexBatchBuilder &) = delete;

        /// @brief 添加绘制元素到批处理
        void addToBatch(const AtlasTexture &texture);

        /// @brief 添加绘制元素到批处理
        void addToBatch(eastl::vector<SDL_Vertex> v);

        /// @brief 清理要绘制的纹理图集
        /// @details 一般要每帧调用，否则会堆积上一帧的内容
        void clearDrawBatches() { m_drawBatches.clear(); }

        /// @brief 获取将要绘制的所有内容的数据
        [[nodiscard]] const eastl::vector<AtlasDrawBatch> &getDrawBatches() const { return m_drawBatches; }

    private:
        eastl::vector<AtlasDrawBatch> m_drawBatches; ///< 一组纹理图集绘制的数据
        static constexpr auto m_qudaIndices = make_indices<QuadCount>();

        /// @brief  添加纹理的数据到顶点数组
        static void appendQuadVertices(eastl::vector<SDL_Vertex> &vertices,
                                       const BoundingBox pos, const TextureEnum textureName) {
            const float winL = pos.getLeft();
            const float winT = pos.getTop();
            const float winR = pos.getRight();
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

    template<std::size_t QuadCount>
    void AtlasVertexBatchBuilder<QuadCount>::addToBatch(const AtlasTexture &texture) {
        const AtlasRegion atlasRegion = getAtlasRegion(texture.getName());
        if (const uint32_t atlasId = atlasRegion.atlasId;
            m_drawBatches.empty() || atlasId != m_drawBatches.back().atlasId) {
            m_drawBatches.emplace_back(atlasId, eastl::vector<SDL_Vertex>());
            m_drawBatches.back().indices = m_qudaIndices.data();
        }
        appendQuadVertices(
            m_drawBatches.back().vertices,
            texture.getBoundingBox(), texture.getName()
        );
    }


    template<std::size_t QuadCount>
    void AtlasVertexBatchBuilder<QuadCount>::addToBatch(eastl::vector<SDL_Vertex> v) {
        if (m_drawBatches.empty() || m_drawBatches.back().atlasId != 0) {
            m_drawBatches.emplace_back(0, eastl::vector<SDL_Vertex>());
        }
        m_drawBatches.back().vertices.insert(m_drawBatches.back().vertices.end(), v.begin(), v.end());
    }
} // name_

#endif //TEXTURE_BATCH_BUILDER_HPP
