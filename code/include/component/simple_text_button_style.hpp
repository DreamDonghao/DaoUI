//
// Created by donghao on 25-12-18.
//
#ifndef SIMPLE_TEXT_BUTTON_STYLE_HPP
#define SIMPLE_TEXT_BUTTON_STYLE_HPP
#include "interface/button_style.hpp"

namespace dao {
    class SimpleTextButtonStyle : public ButtonStyle {
    public:
        SimpleTextButtonStyle(const float32 x, const float32 y, const float32 w, const float32 h,
                              const std::u32string &text, const float32 textSize, const ColorRGBA textColor,Button *button)
            : m_text(x, y, text, textSize, textColor), m_button(button) {
        }

        void writeToBatch(VertexBatchBuilder &builder) const override {
            if (m_button->getStatus() != ButtonStatus::Pressed) {
                builder.addToBatch(m_text);
            }
        }

        void bindButton(Button *button) override {
            m_button = button;
        }

    private:
        Text m_text;
        Button *m_button;
    };
}
#endif //SIMPLE_TEXT_BUTTON_STYLE_HPP
