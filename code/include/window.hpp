//
// Created by donghao on 25-12-4.
//
#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <SDL3/SDL.h>
#include <page.hpp>
#include <unordered_map>
#include <memory>

namespace dao {
    class Window {
    public:
        Window(int width, int height);

        ~Window();

        void addPage(std::unique_ptr<Page> page);

        void registerTexture(const TextureEnum &textureName);

        [[nodiscard]] uint32_t getId() const { return m_id; }

        void run(const SDL_Event &event);

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

        std::unordered_map<uint32_t, SDL_Texture *> atlasTextures;
        std::string m_nowPageTitle;
        std::unordered_map<std::string, std::unique_ptr<Page> > m_pages;
    };
}
#endif //WINDOW_HPP
