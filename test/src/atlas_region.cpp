//
// Created by donghao on 25-12-8.
//
#include "atlas_region.hpp"

namespace dao {
    const AtlasRegion regions[] = {
        {"", 0, 1, 1, 1, 1},
        {"", 0},
        #include <texture_datas.inc>
    };
}
