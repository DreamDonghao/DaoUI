//
// Created by donghao on 25-12-6.
//
#include <window.hpp>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "atlas_region.hpp"
#include <print>

namespace dao {
    Window::Window(const int width, const int height) {
        m_window = SDL_CreateWindow("", width, height,SDL_WINDOW_RESIZABLE);
        m_renderer = SDL_CreateRenderer(m_window, "");
        SDL_SetRenderVSync(m_renderer, 0);
        m_id = SDL_GetWindowID(m_window);
        /// 构建纯白纹理
        SDL_Texture *tex = SDL_CreateTexture(
            m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 1, 1
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
        m_atlasTextures[1] = SDL_CreateTextureFromSurface(
            m_renderer, &m_pages[m_nowPageTitle]->getGlyphAtlas().getAtlasSurface());
    }

    void Window::registerTexture(const uint32 &textureId) {
        const AtlasRegion atlasRegion = getAtlasRegion(textureId);
        // 加载新纹理图集
        if (const uint32 atlasId = atlasRegion.atlasId; !m_atlasTextures.contains(atlasId)) {
            const char *texturePath = atlasRegion.atlasPath;
            m_atlasTextures[atlasId] = IMG_LoadTexture(m_renderer, texturePath);
            SDL_SetTextureScaleMode(m_atlasTextures[atlasId], SDL_SCALEMODE_NEAREST);
            detectionError(m_atlasTextures[atlasId], std::string("图集加载失败") + texturePath);
        }
    }

    void Window::update() {
        if (m_pages[m_nowPageTitle]->getGlyphAtlas().isUpdated()) {
            SDL_UpdateTexture(
                m_atlasTextures[1], nullptr,
                m_pages[m_nowPageTitle]->getGlyphAtlas().getAtlasSurface().pixels,
                m_pages[m_nowPageTitle]->getGlyphAtlas().getAtlasSurface().pitch
            );
            SDL_SetTextureScaleMode(m_atlasTextures[1], SDL_SCALEMODE_NEAREST);
            m_pages[m_nowPageTitle]->getGlyphAtlas().clearUpdateFlag();
        }
        m_pages[m_nowPageTitle]->update();
    }

    void Window::handleMessage(const SDL_Event &event) {
        m_pages[m_nowPageTitle]->handleMessage(event);
    }

    void Window::requestClose() {
        m_running = false;
    }

    void Window::render() {
        SDL_RenderClear(m_renderer);
        for (const auto &[atlasId, vertices, indices]:
             m_pages[m_nowPageTitle]->getDrawBatches()) {
            SDL_RenderGeometry(
                m_renderer, m_atlasTextures[atlasId],
                vertices.data(), static_cast<int>(vertices.size()),
                indices->data(), static_cast<int>(vertices.size() / 4 * 6)
            );
        }

        SDL_RenderPresent(m_renderer);
    }
}
