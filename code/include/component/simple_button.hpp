//
// Created by donghao on 25-12-11.
//
#pragma once
#include <functional>
#include <SDL3/SDL_events.h>
#include <component/rectangle.hpp>
#include "../core/tool/better_stl.hpp"
#include "../core/tool/bounding_box.hpp"
#include <interface/button.hpp>

namespace dao {
    class SimpleButton : public Button {
    public:
        ~SimpleButton() override = default;

        SimpleButton(const float32 x, const float32 y, const float32 width, const float32 height,
                     const ButtonStatus buttonStatus,
                     std::move_only_function<void()> onClick)
            : m_boundingBox(x, y, x + width, y + height),
              m_status(buttonStatus), m_onClick(std::move(onClick)) {
        }

        void update(const SDL_Event &event) override {
            if (m_status == ButtonStatus::Disabled) {
                return;
            }
            float x = 0, y = 0;
            if (event.type == SDL_EVENT_MOUSE_MOTION) {
                x = event.motion.x;
                y = event.motion.y;
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
                       event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                x = event.button.x;
                y = event.button.y;
            } else {
                return;
            }
            if (!m_boundingBox.isInBoundingBox(x, y)) {
                m_status = ButtonStatus::Normal;
                return;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
                event.button.button == SDL_BUTTON_LEFT) {
                m_status = ButtonStatus::Pressed;
                return;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP &&
                event.button.button == SDL_BUTTON_LEFT &&
                m_status == ButtonStatus::Pressed) {
                m_status = ButtonStatus::Hover;
                m_onClick();
                return;
            }
            m_status = ButtonStatus::Hover;
        }


        [[nodiscard]] ButtonStatus getStatus() const override {
            return m_status;
        }

    private:
        BoundingBox m_boundingBox{};
        ButtonStatus m_status{ButtonStatus::Disabled};
        std::move_only_function<void()> m_onClick;
    };


}
