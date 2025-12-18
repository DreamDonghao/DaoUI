#include <app.hpp>
//
// Created by donghao on 25-11-28.
//
#include <test_page.hpp>

int main(int argc, char *argv[]) {
    if (!TTF_Init()) {
        SDL_Log("1TTF_Init failed: %s", SDL_GetError());
        return -1;
    }

    /// 创建一个应用
    auto &app = dao::App::getApp();
    /// 创建一个窗口并添加一个页面
    app.createWindow(800, 600)
            .addPage(std::make_unique<TestPage>("test1"));
    /// 启动程序
    app.run();
    TTF_Quit();
    return 0;
}
