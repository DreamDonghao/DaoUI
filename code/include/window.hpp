//
// Created by donghao on 25-12-4.
//
#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <entt/entt.hpp>
#include <page.hpp>

namespace dao {
    class Window {
    public:
        Window(const int width, const int height) {
            if (SDL_Init(SDL_INIT_VIDEO) == 0) {
                std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
            }
            m_window = SDL_CreateWindow("", width, height,SDL_WINDOW_RESIZABLE);
            m_renderer = SDL_CreateRenderer(m_window, "opengl");
            SDL_SetRenderVSync(m_renderer, 0);
            m_id = SDL_GetWindowID(m_window);
        }

        ~Window() {
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
        }

        void addPage(std::unique_ptr<Page> page) {
            m_nowPageTitle = page->getTitle();
            for (auto textureName: page->registerTexture()) {
                registerTexture(textureName);
            }
            m_pages[page->getTitle()] = std::move(page);
        }

        void registerTexture(const TextureEnum &textureName) {
            const AtlasRegion atlasRegion = getAtlasRegion(textureName);
            // 加载新纹理图集
            if (const uint32_t atlasId = atlasRegion.atlasId; !atlasTextures.contains(atlasId)) {
                const char *texturePath = atlasRegion.atlasPath;
                atlasTextures[atlasId] = IMG_LoadTexture(m_renderer, texturePath);
                SDL_SetTextureScaleMode(atlasTextures[atlasId], SDL_SCALEMODE_NEAREST);
                if (atlasTextures[atlasId] == nullptr) {
                    std::cerr << "图集纹理加载失败! 路径: " << texturePath << " 错误: " << SDL_GetError() << std::endl;
                    atlasTextures.erase(atlasId);
                }
            }
        }

        [[nodiscard]] uint32_t getId() const { return m_id; }

        void run(const SDL_Event &event) {
            m_pages[m_nowPageTitle]->update();
            if (event.type == SDL_EVENT_QUIT) {
                m_running = false;
            }
        }

        [[nodiscard]] bool isRunning() const {
            return m_running;
        }

        void render() {
            for (const auto &[atlasId, vertices, indices]:
                 m_pages[m_nowPageTitle]->getDrawBatches()) {
                SDL_RenderGeometry(
                    m_renderer,
                    atlasTextures[atlasId],
                    vertices.data(),
                    static_cast<int>(vertices.size()),
                    indices.data(),
                    static_cast<int>(indices.size()) // ← 正确的是它！
                );
            }

            SDL_RenderPresent(m_renderer);
        }

    private:
        uint32_t m_id;
        bool m_running = true;
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

        struct TextureDeleter {
            void operator()(SDL_Texture *t) const {
                if (t) SDL_DestroyTexture(t);
            }
        };

        std::unordered_map<uint32_t, SDL_Texture *> atlasTextures;
        AtlasVertexBatchBuilder m_atlasVertexBatchBuilder;
        std::string m_nowPageTitle;
        std::unordered_map<std::string, std::unique_ptr<Page> > m_pages;
    };
}
#endif //WINDOW_HPP
