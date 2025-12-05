//
// Created by donghao on 25-11-26.
//
#ifndef PAGE_HPP
#define PAGE_HPP
#include <atlas_vertex_batch_builder.hpp>

namespace dao {
    class Page {
    public:
        virtual void update() = 0;

        [[nodiscard]] virtual const std::vector<AtlasDrawBatch> &getDrawBatches() const = 0;

        [[nodiscard]] virtual  std::vector<TextureEnum> registerTexture() const = 0;

        virtual ~Page() = default;

        explicit Page(std::string title): m_title(std::move(title)) {
        }

        [[nodiscard]] const std::string &getTitle() const {
            return m_title;
        }

    protected:
        std::string m_title;
    };
}
#endif //PAGE_HPP
