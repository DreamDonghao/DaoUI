//
// Created by donghao on 25-11-28.
//
#ifndef IMAGE_HPP
#define IMAGE_HPP
#include "atlas_region_data.hpp"
#include "mapped_region.hpp"

namespace dao {
    class TextureData {
    public:
        TextureData() = default;

        TextureData(const TextureEnum textureName, const float left, const float up, const float right, const float down)
            : m_textureName(textureName), m_boundingBox(left, up, right, down) {
        }

        [[nodiscard]] const TextureEnum &getName() const {
            return m_textureName;
        }

        [[nodiscard]] const BoundingBox &getBoundingBox() const {
            return m_boundingBox;
        }

    private:
        TextureEnum m_textureName = TextureEnum::EmptyTexture;
        BoundingBox m_boundingBox; ///< 纹理要显示的位置
    };
}


#endif //IMAGE_HPP
