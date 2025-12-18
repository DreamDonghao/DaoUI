//
// Created by donghao on 25-12-6.
//
#include <app.hpp>
#include <iostream>
#include <ranges>
#include <SDL3_ttf/SDL_ttf.h>

namespace dao {
    void App::run() {
        while (m_runWindowNum) {
            m_runWindowNum = 0;
            for (const auto &window: m_windows | std::views::values) {
                render();
                window->update();
                m_runWindowNum += window->isRunning();

            }
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                    uint32 wid = event.window.windowID;

                    if (auto it = m_windows.find(wid); it != m_windows.end()) {
                        it->second->requestClose();  // 让窗口自己决定怎么关
                    }
                }
                SDL_Window *focus = SDL_GetMouseFocus(); // 更常用
                if (!focus) {
                    continue;
                }

                auto wid = SDL_GetWindowID(focus);
                m_windows[wid]->handleMessage(event);
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
