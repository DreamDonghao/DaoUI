//
// Created by donghao on 25-12-9.
//
#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <ostream>
#include <SDL3/SDL_render.h>
#include <interface/drawable.hpp>
namespace dao {

    struct Vertex{
        float32 x;
        float32 y;
    };

    class Polygon : public Drawable {
    public:
        Polygon(const std::initializer_list<SDL_Vertex> list)
            : m_vertices(list) {
        }

        ~Polygon() override = default;

        void addVertex(const SDL_Vertex &vertex, const uint32 index = UINT32_MAX) {
            if (index == UINT32_MAX) {
                m_vertices.push_back(vertex);
            }
            m_vertices.insert(m_vertices.begin() + index, vertex);
        }

        SDL_Vertex &getVertex(const int index) {
            return m_vertices[index];
        }

        void writeToBatch(VertexBatchBuilder &builder) const override {
            builder.addToBatch(m_vertices);
        }

    private:
        std::vector<SDL_Vertex> m_vertices;
    };
} // dao

#endif //POLYGON_HPP
