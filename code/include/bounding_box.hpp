//
// Created by donghao on 25-11-27.
//
#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

namespace dao {
    ///@brief 边界框
    ///@details 用来表示一个矩形范围区域左上右下边界的坐标
    class BoundingBox {
    public:
        BoundingBox() = default;

        BoundingBox(const float left, const float up, const float right, const float down)
            : m_left(left), m_up(up), m_right(right), m_down(down) {
        }

        ~BoundingBox() = default;

        void set(const float left, const float up, const float right, const float down) {
            m_left = left;
            m_up = up;
            m_right = right;
            m_down = down;
        }

        void setLeft(const float left) { m_left = left; }

        void setUp(const float up) { m_up = up; }

        void setRight(const float right) { m_right = right; }

        void setDown(const float down) { m_down = down; }

        void moveHorizontal(const float distance) {
            m_left += distance;
            m_right += distance;
        }

        void moveVertical(const float distance) {
            m_up += distance;
            m_down += distance;
        }

        void normalize() {
            if (m_left > m_right) std::swap(m_left, m_right);
            if (m_up > m_down) std::swap(m_up, m_down);
        }


        [[nodiscard]] bool isValid() const {
            return m_left <= m_right && m_up <= m_down;
        }

        [[nodiscard]] bool isInBoundingBox(const float x, const float y) const {
            return (x >= m_left && x <= m_right) && (y >= m_up && y <= m_down);
        }

        [[nodiscard]] bool isIntersects(const BoundingBox &other) const {
            return std::max(m_left, other.m_left) <= std::min(m_right, other.m_right) &&
                   std::max(m_up, other.m_up) <= std::min(m_down, other.m_down);
        }

        [[nodiscard]] float getLeft() const { return m_left; }

        [[nodiscard]] float getTop() const { return m_up; }

        [[nodiscard]] float getRight() const { return m_right; }

        [[nodiscard]] float getBottom() const { return m_down; }

        [[nodiscard]] float     getWidth() const { return m_right - m_left; }

        [[nodiscard]] float getHeight() const { return m_down - m_up; }

    private:
        float m_left = 0.f;
        float m_up = 0.f;
        float m_right = 0.f;
        float m_down = 0.f;
    };
}
#endif //BOUNDING_BOX_HPP
