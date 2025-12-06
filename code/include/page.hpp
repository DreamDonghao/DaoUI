//
// Created by donghao on 25-11-26.
//
#ifndef PAGE_HPP
#define PAGE_HPP
#include <atlas_vertex_batch_builder.hpp>

namespace dao {
    /// @brief 页面
    /// @details 提供了所有页面的接口，所有页面都应继承这个类
    class Page {
    public:
        [[nodiscard]] virtual eastl::vector<TextureEnum> registerTexture() const = 0;

        /// @brief 更新
        virtual void update() = 0;

        virtual ~Page() = default;

        explicit Page(std::string title): m_title(std::move(title)) {
        }

        [[nodiscard]] auto getDrawBatches() const {
            return m_atlasVertexBatchBuilder.getDrawBatches();
        }

        [[nodiscard]] const std::string &getTitle() const {
            return m_title;
        }

    protected:
        std::string m_title; ///< 标题
        AtlasVertexBatchBuilder<120000> m_atlasVertexBatchBuilder;
    };
}
#endif //PAGE_HPP
