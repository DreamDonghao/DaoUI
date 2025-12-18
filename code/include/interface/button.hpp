//
// Created by donghao on 25-12-12.
//
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SDL3/SDL_events.h>

namespace dao {
    /// @brief 按钮状态
    enum class ButtonStatus {
        Disabled, ///< 禁用
        Normal,   ///< 自然
        Hover,    ///< 悬停
        Pressed,  ///< 按下
    };

    /// @brief  按钮接口
    class Button {
    public:
        virtual ~Button() = default ;

        /// @brief 处理消息，更新状态
        virtual void update(const SDL_Event &event) = 0;

        /// @brief 获取当前状态
        [[nodiscard]] virtual ButtonStatus getStatus() const = 0;
    };
}
#endif //BUTTON_HPP
