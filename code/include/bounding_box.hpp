//
// Created by donghao on 25-11-27.
//
#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP
#include <algorithm>

namespace dao {
    ///@brief 边界框
    ///@details 用来表示一个矩形范围区域左上右下边界的坐标
    class BoundingBox {
    public:
        BoundingBox() = default;

        /// @brief 构造函数
        /// @param left 左边界坐标
        /// @param left 上边界坐标
        /// @param left 右边界坐标
        /// @param left 下边界坐标
        BoundingBox(const float left, const float up, const float right, const float down)
            : m_left(left), m_up(up), m_right(right), m_down(down) {
        }

        ~BoundingBox() = default;

        /// @brief 设置数据
        /// @param left 左边界坐标
        /// @param left 上边界坐标
        /// @param left 右边界坐标
        /// @param left 下边界坐标
        void set(const float left, const float up, const float right, const float down) {
            m_left = left;
            m_up = up;
            m_right = right;
            m_down = down;
        }

        /// @brief 设置左边界坐标
        /// @param left 左边界坐标
        void setLeft(const float left) { m_left = left; }

        /// @brief 设置上边界坐标
        /// @param up 上边界坐标
        void setUp(const float up) { m_up = up; }

        /// @brief 设置右边界坐标
        /// @param right 右边界坐标
        void setRight(const float right) { m_right = right; }

        /// @brief 设置下边界坐标
        /// @param down 下边界坐标
        void setDown(const float down) { m_down = down; }

        /// @brief 水平移动
        /// @details 正右负左
        void moveHorizontal(const float distance) {
            m_left += distance;
            m_right += distance;
        }

        /// @brief 竖直移动
        /// @details 正上负下
        void moveVertical(const float distance) {
            m_up += distance;
            m_down += distance;
        }

        /// @brief 正常化
        /// @details 使颠倒的数据正常，若正常则无效果
        void normalize() {
            if (m_left > m_right) std::swap(m_left, m_right);
            if (m_up > m_down) std::swap(m_up, m_down);
        }

        /// @brief 检查是否有效
        /// @returns 判断有效的布尔值
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


        /// @brief 获取左边界坐标
        /// @return 左边界坐标
        [[nodiscard]] float getLeft() const { return m_left; }

        /// @brief 获取上边界坐标
        /// @return 上边界坐标
        [[nodiscard]] float getTop() const { return m_up; }

        /// @brief 获取右边界坐标
        /// @return 右边界x坐标值
        [[nodiscard]] float getRight() const { return m_right; }

        /// @brief 获取下边界坐标
        /// @return 下边界坐标值
        [[nodiscard]] float getBottom() const { return m_down; }


        [[nodiscard]] float getWidth() const { return m_right - m_left; }


        [[nodiscard]] float getHeight() const { return m_down - m_up; }

    private:
        float m_left = 0.f;
        float m_up = 0.f;
        float m_right = 0.f;
        float m_down = 0.f;
    };
}
#endif //BOUNDING_BOX_HPP
