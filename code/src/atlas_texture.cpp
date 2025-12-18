//
// Created by donghao on 25-12-6.
//
#include <../include/core/basic_drawing_elements/atlas_texture.hpp>

namespace dao {
    AtlasTexture::AtlasTexture(const uint32 textureId,
                               const float32 left, const float32 up, const float32 right, const float32 down)
        : m_textureId(textureId), m_boundingBox(left, up, right, down) {
    }
}
