//
// Created by donghao on 25-12-12.
//
#ifndef BUTTON_STYLE_HPP
#define BUTTON_STYLE_HPP
#include "button.hpp"
#include "drawable.hpp"

namespace dao {
    /// @brief 按钮样式接口
    class ButtonStyle : Drawable {
    public:
        ~ButtonStyle() override = default;

        /// @brief 加入绘制批处理
        void writeToBatch(VertexBatchBuilder &builder) const override = 0;

        /// @brief 绑定按钮
        virtual void bindButton(Button *button) = 0;
    };
}
#endif //BUTTON_STYLE_HPP
