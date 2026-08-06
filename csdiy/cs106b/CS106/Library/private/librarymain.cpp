/*
 * 文件：librarymain.cpp
 * ---------------------
 * 此文件包含一个 `libraryMain` 函数定义，用于初始化
 * Stanford C++ 库，然后运行学生的 main 函数
 * 在其自己的线程中。这是 Qt 版本库正常运行所必需的
 * 函数正常工作。
 */

#include "private/init.h"
#include "qtgui.h"

// 学生实现看似普通的 main() 函数，但
// 构建期间会重命名为 studentMain()
int studentMain();

// 根据需要初始化 Qt GUI 库子系统和 Qt 图形控制台
// 调用 studentMain 之前

int libraryMain(int argc, char** argv)
{
    stanfordcpplib::initializeLibrary(argc, argv);
#ifdef SPL_HEADLESS_MODE
    studentMain();
#else
    QtGui::instance()->startBackgroundEventLoop(studentMain);
#endif
    stanfordcpplib::shutdownLibrary();
    return 0;
}
