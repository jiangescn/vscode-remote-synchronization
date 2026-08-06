/*
 * 文件：qtgui.cpp
 * ---------------
 *
 * @author Marty Stepp
 * @version 2018/08/23
 * - 重命名为 qtgui.cpp
 * @version 2018/07/03
 * - 初始版本
 */

#include "qtgui.h"
#include <QEvent>
#include <QtGlobal>
#include <QThread>
#include "consoletext.h"
#include "error.h"
#include "exceptions.h"
#include "gconsolewindow.h"
#include "gthread.h"
#include "strlib.h"
#include "private/static.h"
#include "private/init.h"

// QSPLApplication 成员
QSPLApplication::QSPLApplication(int& argc, char *argv[])
        : QApplication(argc, argv) {
    // 空
}

bool QSPLApplication::notify(QObject* receiver, QEvent* e) {
    // 可以在此处使用 try/catch 处理 GUI 线程上的异常
    // 但这会掩盖来源位置（丢失 backtrace）
    return QApplication::notify(receiver, e);   // 调用父类实现
}


// QtGui 成员
QSPLApplication* QtGui::_app = nullptr;
QtGui* QtGui::_instance = nullptr;

QtGui::QtGui()
        : _initialized(false) {
    connect(GEventQueue::instance(), SIGNAL(eventReady()), this, SLOT(processEventFromQueue()));
}

void QtGui::exitGraphics(int exitCode) {
    if (exitCode == EXITING_DUE_TO_WINDOW_CLOSE) {
        std::cout << std::endl << std::endl << "[Program exiting due to window close event]" << std::endl;
        exitCode = 0;
    }
    if (_app) {
// 需要暂时关闭 C++ 库的 exit 宏，以调用 QApplication 的 exit 方法
// （注意：必须与 init.h 中的 exit 定义保持同步）
#undef exit
        _app->quit();
        _app = nullptr;
        std::exit(exitCode);
#define exit __stanfordcpplib__exitLibrary
    } else {
        std::exit(exitCode);
    }
}

QSPLApplication* QtGui::getApplication() {
    return _app;
}

std::string QtGui::getApplicationDisplayName() const {
    return (_app ? _app->applicationDisplayName().toStdString() : "");
}

int QtGui::getArgc() const {
    return _argc;
}

char** QtGui::getArgv() const {
    return _argv;
}

void QtGui::initializeQt() {
    if (_app) return;

    GThread::runOnQtGuiThread([this]() {
        if (!_app) {
            qSetMessagePattern(
                    "Qt internal warning: %{message}\n"
                    "  - pid: %{pid}\n"
                    "  - thread: %{threadid}\n"

                    // backtrace 在 Windows 和某些其他构建中不可用
#ifndef _WIN32
                    "  - stack:\n"
                    "      %{backtrace depth=20 separator=\"\n      \"}"
#endif // _WIN32
            );
            _app = new QSPLApplication(_argc, _argv);
            _initialized = true;
        }
    });
}

QtGui* QtGui::instance() {
    if (!_instance) {
        _instance = new QtGui();
        GEventQueue::instance();   // 在 Qt GUI 主线程上创建事件队列
    }
    return _instance;
}

void QtGui::processEventFromQueue() {
    if (!GEventQueue::instance()->isEmpty()) {
        GThunk thunk = GEventQueue::instance()->peek();
        thunk();
        GEventQueue::instance()->dequeue();
    }
}

void QtGui::setArgs(int argc, char** argv) {
    _argc = argc;
    _argv = argv;
}

// 应由 Qt 主线程调用此函数
void QtGui::startBackgroundEventLoop(GThunkInt mainFunc, bool exitAfter) {
    GThread::ensureThatThisIsTheQtGuiThread("QtGui::startBackgroundEventLoop");
    native_set_thread_name("Qt GUI Event Loop");
    // 在独立的第二线程中启动学生的 main 函数

    if (!GThread::studentThreadExists()) {
        GThread::startStudentThread([&]() -> int {
            stanfordcpplib::initializeStudentThread();
            int result = mainFunc();
            stanfordcpplib::studentThreadHasExited("Completed");
            return result;
        });

        startEventLoop(exitAfter);   // 在主线程上启动 Qt 事件循环
    }
}

// 应由 Qt 主线程调用此函数
void QtGui::startEventLoop(bool exitAfter) {
    GThread::ensureThatThisIsTheQtGuiThread("QtGui::startEventLoop");
    if (!_app) {
        error("QtGui::startEventLoop: need to initialize Qt first");
    }

    // 在主线程上启动 Qt 事件循环；
    // Qt GUI 主线程在此阻塞，直到 student main()（在其独立线程中）结束
    int exitCode = _app->exec();

    // 如果执行到这里，表示一个“关闭时退出”的窗口刚刚被关闭；
    // 现在该关闭 Qt 系统并退出 C++ 程序了
    if (exitAfter) {
        exitGraphics(exitCode);
    }
}



namespace stanfordcpplib {
void studentThreadHasExited(const std::string& reason) {
    // 短暂等待控制台完成打印任何/全部输出
    GThread::getCurrentThread()->yield();
    GThread::getCurrentThread()->sleep(1);

    // 如果执行到这里，表示学生的 main() 已运行完毕；
    // 通过在图形控制台上显示已完成的标题来表示这一点
    if (getConsoleEnabled()) {
#ifndef SPL_HEADLESS_MODE
        GConsoleWindow* console = getConsoleWindow();
        if (console) {
            console->shutdown(reason);
        }
#endif // SPL_HEADLESS_MODE
    } else {
        // 需要在此处退出，否则程序不会终止
        // BUG 修复：不，这并非必要且有害；它会让窗口过早退出；禁用
        // QtGui::instance()->exitGraphics(result);
    }
}
} // namespace stanfordcpplib


