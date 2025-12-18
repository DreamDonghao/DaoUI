//
// Created by donghao on 25-12-8.
//
#include "../../code/include/core/basic_drawing_elements/atlas_region.hpp"

namespace dao {
    const AtlasRegion regions[] = {
        {"", 0, 1, 1, 1, 1},
        {"", 0},
        #include <texture_datas.inc>
    };
}
