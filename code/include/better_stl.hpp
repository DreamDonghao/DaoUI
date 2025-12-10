//
// Created by donghao on 25-12-9.
//
#ifndef BETTER_STL_HPP
#define BETTER_STL_HPP
#include <cstdint>
#include <algorithm>
#include <memory>
#include <unordered_map>

namespace dao {
    using int8 = int8_t;
    using int16 = int16_t;
    using int32 = int32_t;
    using int64 = int64_t;
    using uint8 = uint8_t;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;
    using float32 = float;

    template<typename K, typename V>
    using hash_map = std::unordered_map<K, V>;

    template<typename Container>
    void sort(Container &container) {
        std::sort(container.begin(), container.end());
    }

    template<typename T>
    class SwitchDeleter {
    public:
        enum Mode { Observe, Manage };

        explicit SwitchDeleter(const Mode m = Manage) : mode(m) {
        }

        void operator()(const T *ptr) const noexcept {
            if (mode == Manage) {
                delete ptr;
            }
        }

        void setMode(Mode m) { mode = m; }
        Mode getMode() const { return mode; }

    private:
        Mode mode;
    };

    template<typename T>
    auto makeObserver(T *ptr) {
        return std::unique_ptr<T, SwitchDeleter<T> >(
            ptr, SwitchDeleter<T>(SwitchDeleter<T>::Observe)
        );
    }

    template<typename T>
    auto makeManage(T *ptr) {
        return std::unique_ptr<T, SwitchDeleter<T> >(
            ptr, SwitchDeleter<T>(SwitchDeleter<T>::Manage)
        );
    }
}
#endif //BETTER_STL_HPP
