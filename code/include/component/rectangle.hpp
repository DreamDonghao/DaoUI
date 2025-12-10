//
// Created by donghao on 25-12-8.
//
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <interface/drawable.hpp>

namespace dao {
    class Rectangle : public Drawable {
    public:
        explicit Rectangle(const float x = 0.f, const float y = 0.f, const float width = 0.f, const float height = 0.f,
                  const SDL_FColor leftTopPointColor = {1.0f, 1.0f, 1.0f, 1.0f},
                  const SDL_FColor rightTopColor = {1.0f, 1.0f, 1.0f, 1.0f},
                  const SDL_FColor rightTopPointColor = {1.0f, 1.0f, 1.0f, 1.0f},
                  const SDL_FColor leftBottomPoint = {1.0f, 1.0f, 1.0f, 1.0f})
            : m_vertices{
                {{x, y}, leftTopPointColor, {1.f, 1.f}},
                {{x + width, y}, rightTopColor, {1.f, 1.f}},
                {{x + width, y + height}, rightTopPointColor, {1.f, 1.f}},
                {{x + width, y + height}, rightTopPointColor, {1.f, 1.f}},
                {{x, y + height}, leftBottomPoint, {1.f, 1.f}},
                {{x, y}, leftTopPointColor, {1.f, 1.f}}
            } {
        }

        void setLeftTopPointColor(const SDL_FColor color) {
            m_vertices[0].color = color;
        }

        void setRightTopPointColor(const SDL_FColor color) {
            m_vertices[1].color = color;
        }

        void setRightBottomPointColor(const SDL_FColor color) {
            m_vertices[2].color = color;
        }

        void setLeftBottomPointColor(const SDL_FColor color) {
            m_vertices[3].color = color;
        }

        void writeToBatch(VertexBatchBuilder &builder) const override {
            builder.addToBatch(m_vertices);
        }

    private:
        float m_x{0.f};
        float m_y{0.f};
        float m_width{0.f};
        float m_height{0.f};
        std::vector<SDL_Vertex> m_vertices;
    };
}
#endif //RECTANGLE_HPP
