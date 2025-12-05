#include <app.hpp>
#include <test_page.hpp>

int main(int argc, char *argv[]) {
    /// 创建一个应用
    auto &app = dao::App::getApp();
    /// 创建一个窗口并添加一个页面
    app.createWindow(800, 600)
            .addPage(std::make_unique<dao::TestPage>("test1"));
    /// 启动程序
    app.run();
    return 0;
}