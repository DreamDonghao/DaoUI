//
// Created by donghao on 25-12-4.
//
#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <SDL3/SDL.h>
#include <interface/page.hpp>
#include <memory>

namespace dao {
    /// @brief 窗口
    class Window {
        struct TextureDeleter {
            void operator()(SDL_Texture *texture) const {
                if (texture) SDL_DestroyTexture(texture);
            }
        };

    public:
        Window(int width, int height);

        ~Window();

        /// @brief 添加页面
        /// @param page 要添加页面的unique_ptr指针
        void addPage(std::unique_ptr<Page> page);

        /// @brief 加载纹理图集
        void registerTexture(const uint32 &textureId);

        /// @brief 获取 id
        [[nodiscard]] uint32 getId() const { return m_id; }

        /// @brief 更新一帧
        void update();

        /// @brief 处理消息
        void handleMessage(const SDL_Event &event);

        /// @brief 窗口关闭请求
        void requestClose();

        /// @brief 判断是否在运行
        [[nodiscard]] bool isRunning() const { return m_running; }

        /// @brief 渲染
        void render();

    private:
        uint32 m_id;           ///< ID
        bool m_running = true; ///< 是否正在运行
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        hash_map<uint32, SDL_Texture *> m_atlasTextures;
        std::string m_nowPageTitle;
        hash_map<std::string, std::unique_ptr<Page> > m_pages;
    };
}
#endif //WINDOW_HPP
