#ifndef ATLAS_REGION_DATA_HPP
#define ATLAS_REGION_DATA_HPP
#include "atlas_region_data.hpp"
#include <iterator>

namespace dao {
    /// @brief 图集区域数据
    struct AtlasRegion {
        const char *const atlasPath; ///< 图集区域对应的纹理图集文件路径
        const uint32_t atlasId;      ///< 图集区域对应的纹理图集编号
        const float normalizedLeft, normalizedTop,
                normalizedRight, normalizedBottom; ///< 归一化的图集区域的左上右下坐标
    };

    enum class TextureEnum:int32_t {
        /// python 脚本生成
        #include <textures.inc>
        EmptyTexture
    };

    inline constexpr AtlasRegion regions[] = {
        /// python 脚本生成
        #include <texture_datas.inc>
    };

    static_assert(static_cast<uint32_t>(TextureEnum::EmptyTexture) == std::size(regions), "纹理图集数据错误");

    /// @brief 通过纹理名称获取图集区域数据
    inline const AtlasRegion &getAtlasRegion(const TextureEnum textureName) {
        return regions[static_cast<uint32_t>(textureName)];
    }
}

#endif //ATLAS_REGION_DATA_HPP
