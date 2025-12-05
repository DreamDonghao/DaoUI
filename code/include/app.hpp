//
// Created by donghao on 25-11-26.
//
#ifndef APP_HPP
#define APP_HPP
#include <window.hpp>

namespace dao {
    /// @brief 管理一个应用程序
    /// @details 用来管理整个应用程序
    ///
    class App final {
    public:
        static App &getApp() {
            static App app{};
            return app;
        }

        Window &createWindow(const uint32_t width, const uint32_t height) {
            auto nowWindow = std::make_unique<Window>(width, height);
            const uint32_t windowId = nowWindow->getId();
            m_windows[windowId] = std::move(nowWindow);
            return *m_windows[windowId];
        }

        void render() {
            for (const auto &window: m_windows | std::views::values) {
                window->render();
            }
        }

        Window &getWindow(const uint32_t windowId) {
            return *m_windows[windowId];
        }

        void run() {
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

    private:
        uint32_t m_runWindowNum = 1;
        std::unordered_map<uint32_t, std::unique_ptr<Window> > m_windows;

        App() = default;

        ~App() = default;
    };
}
#endif //APP_HPP
