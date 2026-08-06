/*
 * 文件：init.cpp
 * --------------
 *
 * TODO（待办）
 *
 * @author Marty Stepp
 * @version 2018/11/22
 * - 添加无界面模式支持
 * @version 2018/08/28
 * - 重构以使用 stanfordcpplib 命名空间
 * @version 2018/08/27
 * - 初始版本
 */

#include "private/init.h"
#include "consoletext.h"
#include "exceptions.h"
#include "qtgui.h"
#include "strlib.h"
#include "private/static.h"
#include <QStandardPaths>
#include "private/version.h"


#ifdef _WIN32
#  include <direct.h>   // 用于 chdir
#else // _WIN32
#  include <unistd.h>   // 用于 chdir
#endif // _WIN32

inline void initResourcesOutsideNamespace() { Q_INIT_RESOURCE(images); }


namespace stanfordcpplib {

namespace qtgui {
extern void initializeQtGraphicalConsole();
extern void shutdownConsole();
}

static void parseArgsQt(int argc, char** argv);

STATIC_VARIABLE_DECLARE(bool, isExitEnabled, true)

bool exitEnabled() {
    return STATIC_VARIABLE(isExitEnabled);
}

// 由真正的 main() 函数自动调用；
// 在 Qt GUI 主线程中运行
void initializeLibrary(int argc, char** argv) {
    // 确保库只初始化一次
    static bool _initialized = false;
    if (_initialized) {
        return;
    }
    _initialized = true;

#ifndef SPL_HEADLESS_MODE
    GThread::setGuiThread();
#endif // SPL_HEADLESS_MODE

    parseArgsQt(argc, argv);

#ifndef SPL_HEADLESS_MODE
    // 初始化主 Qt 图形子系统
    QtGui::instance()->setArgs(argc, argv);
    QtGui::instance()->initializeQt();
    initResourcesOutsideNamespace();

    // 初始化 Qt 图形控制台（如果学生 #include 了它）
    initializeQtGraphicalConsole();
#endif // SPL_HEADLESS_MODE
}

void initializeStudentThread() {
    exceptions::setTopLevelExceptionHandlerEnabled(true);
}

// 此处代码应与 platform.cpp 的 parseArgs 函数大致相同
static void parseArgsQt(int argc, char** argv) {
    if (argc <= 0) {
        return;
    }
    std::string arg0 = argv[0];
    exceptions::setProgramName(argv[0]);
    // programName() = getRoot(getTail(arg0));

#ifndef _WIN32
    // 仅在 Mac 上，由于应用嵌套目录结构，可能需要更改 wd
    size_t ax = arg0.find(".app/Contents/");
    if (ax != std::string::npos) {
        while (ax > 0 && arg0[ax] != '/') {
            ax--;
        }
        if (ax > 0) {
            std::string cwd = arg0.substr(0, ax);
            chdir(cwd.c_str()); // wd 是包含 .app 的文件夹
        }
    }
#endif // _WIN32

    char* noConsoleFlag = getenv("NOCONSOLE");
    if (noConsoleFlag && startsWith(std::string(noConsoleFlag), "t")) {
        return;
    }
}

void setExitEnabled(bool enabled) {
    STATIC_VARIABLE(isExitEnabled) = enabled;
    // TODO：通知 GConsoleWindow？
}

// 关闭 Qt 图形控制台窗口；
// 在 Qt 主线程中运行
void shutdownLibrary() {
#ifdef SPL_HEADLESS_MODE
    // 空
#else
    shutdownConsole();
#endif // SPL_HEADLESS_MODE
}

} // namespace stanfordcpplib

namespace std {
void __stanfordcpplib__exitLibrary(int status) {
    if (stanfordcpplib::exitEnabled()) {
        // 调用 std::exit（已重命名）

#ifdef exit
#undef exit
        std::exit(status);
#define exit __stanfordcpplib__exitLibrary
#endif // 退出

    } else {
        // 不允许调用 exit()；生成错误消息
        std::ostringstream out;
        out << "Program tried to call exit(" << status << ") to quit. " << std::endl;
        out << "*** This function has been disabled; main should end through " << std::endl;
        out << "*** normal program control flow." << std::endl;
        error(out.str());
    }
}

} // namespace std
