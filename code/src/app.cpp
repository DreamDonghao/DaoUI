//
// Created by donghao on 25-12-6.
//
#include <app.hpp>
#include <iostream>
#include <ranges>

namespace dao {
    void App::run() {
        while (m_runWindowNum) {
            m_runWindowNum = 0;
            for (const auto &window: m_windows | std::views::values) {
                render();
                m_runWindowNum += window->isRunning();
            }
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                for (const auto &window: m_windows | std::views::values) {
                    window->run(event);
                }
            }
        }
        SDL_Quit();
    }

    Window &App::createWindow(const uint32 width, const uint32 height) {
        auto nowWindow = std::make_unique<Window>(width, height);
        const uint32 windowId = nowWindow->getId();
        m_windows[windowId] = std::move(nowWindow);
        return *m_windows[windowId];
    }

    App::App() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init failed" << SDL_GetError() << std::endl;
        }
    }

    void App::render() {
        for (const auto &window: m_windows | std::views::values) {
            window->render();
        }
    }
}
