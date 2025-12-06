//
// Created by donghao on 25-12-6.
//
#include <window.hpp>
#include <SDL3_image/SDL_image.h>
#include <iostream>

namespace dao {
    Window::Window(const int width, const int height) {
        if (SDL_Init(SDL_INIT_VIDEO) == 0) {
            std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        }
        m_window = SDL_CreateWindow("", width, height,SDL_WINDOW_RESIZABLE);
        m_renderer = SDL_CreateRenderer(m_window, "opengl");
        SDL_SetRenderVSync(m_renderer, 0);
        m_id = SDL_GetWindowID(m_window);
    }

    Window::~Window() {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Window::addPage(std::unique_ptr<Page> page) {
        m_nowPageTitle = page->getTitle();
        for (auto textureName: page->registerTexture()) {
            registerTexture(textureName);
        }
        m_pages[page->getTitle()] = std::move(page);
    }

    void Window::registerTexture(const TextureEnum &textureName) {
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

    void Window::run(const SDL_Event &event) {
        m_pages[m_nowPageTitle]->update();
        if (event.type == SDL_EVENT_QUIT) {
            m_running = false;
        }
    }

    void Window::render() {
        for (const auto &[atlasId, vertices, indices]:
             m_pages[m_nowPageTitle]->getDrawBatches()) {
            //std::cout << vertices.size()/4<< std::endl;
            SDL_RenderGeometry(
                m_renderer,
                atlasTextures[atlasId],
                vertices.data(),
                static_cast<int>(vertices.size()),
                indices,
                static_cast<int>(vertices.size() / 4 * 6)
            );
        }

        SDL_RenderPresent(m_renderer);
    }
}
