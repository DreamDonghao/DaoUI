//
// Created by donghao on 25-12-6.
//
#ifndef RECT_VERTEX_INDEX_HPP
#define RECT_VERTEX_INDEX_HPP
#include <array>

namespace dao {
    template<std::size_t QuadCount>
    constexpr auto make_indices() {
        std::array<int, QuadCount * 6> arr{};

        for (std::size_t i = 0; i < QuadCount; ++i) {
            const unsigned base = i * 4;
            arr[i * 6 + 0] = base + 0;
            arr[i * 6 + 1] = base + 1;
            arr[i * 6 + 2] = base + 2;
            arr[i * 6 + 3] = base + 2;
            arr[i * 6 + 4] = base + 3;
            arr[i * 6 + 5] = base + 0;
        }
        return arr;
    }
}
#endif //RECT_VERTEX_INDEX_HPP
