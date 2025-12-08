//
// Created by donghao on 25-12-6.
//
#include <atlas_texture.hpp>

namespace dao {
    AtlasTexture::AtlasTexture(const uint32_t textureId,
                               const float left, const float up, const float right, const float down)
        : m_textureId(textureId), m_boundingBox(left, up, right, down) {
    }
}
