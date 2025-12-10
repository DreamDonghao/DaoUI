//
// Created by donghao on 25-12-6.
//
#include <window.hpp>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "atlas_region.hpp"

namespace dao {
    Window::Window(const int width, const int height) {
        m_window = SDL_CreateWindow("", width, height,SDL_WINDOW_RESIZABLE);
        m_renderer = SDL_CreateRenderer(m_window, "opengl");
        SDL_SetRenderVSync(m_renderer, 0);
        m_id = SDL_GetWindowID(m_window);
        /// 构建纯白纹理
        SDL_Texture *tex = SDL_CreateTexture(
            m_renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_STATIC,
            1, 1
        );
        constexpr Uint32 whitePixel = 0xFFFFFFFF;
        SDL_UpdateTexture(tex, nullptr, &whitePixel, 4);
        m_atlasTextures[0] = tex;
    }

    Window::~Window() {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Window::addPage(std::unique_ptr<Page> page) {
        m_nowPageTitle = page->getTitle();
        for (auto textureId: page->registerTexture()) {
            registerTexture(textureId);
        }
        m_pages[page->getTitle()] = std::move(page);
    }

    void Window::registerTexture(const uint32 &textureId) {
        const AtlasRegion atlasRegion = getAtlasRegion(textureId);
        // 加载新纹理图集
        if (const uint32 atlasId = atlasRegion.atlasId; !m_atlasTextures.contains(atlasId)) {
            const char *texturePath = atlasRegion.atlasPath;
            m_atlasTextures[atlasId] = IMG_LoadTexture(m_renderer, texturePath);
            SDL_SetTextureScaleMode(m_atlasTextures[atlasId], SDL_SCALEMODE_NEAREST);
            if (m_atlasTextures[atlasId] == nullptr) {
                std::cerr << "图集纹理加载失败! 路径: " << texturePath << " 错误: " << SDL_GetError() << std::endl;
                m_atlasTextures.erase(atlasId);
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
                m_atlasTextures[atlasId],
                vertices.data(),
                static_cast<int>(vertices.size()),
                indices->data(),
                static_cast<int>(vertices.size() / 4 * 6)
            );
        }

        SDL_RenderPresent(m_renderer);
    }
}
