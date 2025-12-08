//
// Created by donghao on 25-12-1.
//
#ifndef TEXTURE_BATCH_BUILDER_HPP
#define TEXTURE_BATCH_BUILDER_HPP
#include <SDL3/SDL_render.h>
#include "atlas_texture.hpp"
#include <vector>

namespace dao {
    /// @brief 纹理图集绘制批
    /// @details 一次纹理图集绘制用到的数据
    struct AtlasDrawBatch {
        uint32_t atlasId;                 ///< 绘制的纹理图集 ID
        std::vector<SDL_Vertex> vertices; ///< 绘制纹理图集的顶点数组
        const int *indices = nullptr;
    };

    /// @brief 纹理批处理构建器
    /// @details 用来将纹理构建为纹理图集处理数据
    class AtlasVertexBatchBuilder {
    public:
        explicit AtlasVertexBatchBuilder(const size_t qudaCount = 1024) { expandQudaIndicesTo(qudaCount); }

        /// @brief 扩容共用矩形索引缓冲
        /// @details 若当前容量不足以容纳指定数量的矩形（每矩形 6 个索引），
        /// 则将索引数组扩展到能容纳 qudaCount 个矩形的大小。
        /// 仅在需要时增长容量，不会缩小原有大小。
        /// @param qudaCount 需要的矩形数量
        static void expandQudaIndicesTo(size_t qudaCount);


        /// @brief 重新设置共用矩形索引缓冲的大小
        /// @details 将索引数组调整为可容纳 qudaCount 个矩形的精确大小（每矩形 6 个索引）。
        /// 若当前容量不足则扩容；若容量过大则收缩至精确大小。
        /// @param qudaCount 目标矩形数量
        static void resetQudaIndices(size_t qudaCount);

        /// @brief 禁用复制构造函数
        AtlasVertexBatchBuilder(const AtlasVertexBatchBuilder &) = delete;

        /// @brief 添加绘制元素到批处理
        void addToBatch(const AtlasTexture &texture);

        /// @brief 添加绘制元素到批处理
        void addToBatch(const std::vector<SDL_Vertex>& v);

        /// @brief 清理要绘制的纹理图集
        /// @details 一般要每帧调用，否则会堆积上一帧的内容
        void clearDrawBatches() { m_drawBatches.clear(); }

        /// @brief 获取将要绘制的所有内容的数据
        [[nodiscard]] const std::vector<AtlasDrawBatch> &getDrawBatches() const { return m_drawBatches; }

    private:
        std::vector<AtlasDrawBatch> m_drawBatches; ///< 一组纹理图集绘制的数据
        static std::vector<int> s_qudaIndices;     ///< 共用矩形顶点数组索引

        /// @brief  添加纹理的数据到顶点数组
        static void appendQuadVertices(std::vector<SDL_Vertex> &vertices, BoundingBox pos, uint32_t textureId);
    };
} // name_

#endif //TEXTURE_BATCH_BUILDER_HPP
