//
// Created by donghao on 25-12-4.
//
#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <SDL3/SDL.h>
#include <interface/page.hpp>
#include <unordered_map>
#include <memory>

namespace dao {
    /// @brief 窗口
    class Window {
    public:
        Window(int width, int height);

        ~Window();

        /// @brief 添加页面
        /// @param page 要添加页面的unique_ptr指针
        void addPage(std::unique_ptr<Page> page);

        /// @brief 加载纹理图集
        void registerTexture(const uint32_t &textureId);

        /// @brief 获取 id
        [[nodiscard]] uint32_t getId() const { return m_id; }

        /// 更新一帧
        void run(const SDL_Event &event);

        /// 判断是否在运行
        [[nodiscard]] bool isRunning() const { return m_running; }

        /// @brief 渲染
        void render();

    private:
        uint32_t m_id;
        bool m_running = true;
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

        struct TextureDeleter {
            void operator()(SDL_Texture *texture) const {
                if (texture) SDL_DestroyTexture(texture);
            }
        };

        std::unordered_map<uint32_t, SDL_Texture *> m_atlasTextures;
        std::string m_nowPageTitle;
        std::unordered_map<std::string, std::unique_ptr<Page> > m_pages;
    };
}
#endif //WINDOW_HPP
