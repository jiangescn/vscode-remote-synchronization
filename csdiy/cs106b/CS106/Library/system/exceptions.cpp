/*
 * 文件：exceptions.cpp
 * --------------------
 * 此文件包含顶层异常处理程序，用于打印抛出的异常
 * 由学生代码输出到控制台。
 *
 * @author Julie Zelenski
 * @version 2020/08/28
 * - 移除堆栈跟踪收集，统一致命错误处理
 * @author Marty Stepp
 * @version 2019/05/16
 * - 添加更多从堆栈跟踪中过滤的函数名
 * @version 2019/04/16
 * - 从堆栈跟踪中过滤 Qt/std 线程方法
 * @version 2019/04/02
 * - 小幅修复 string 异常中 -Wreturn-std-move 的警告
 * @version 2018/10/18
 * - 添加 set_unexpected 处理程序（自动评分器在抛出错误时使用）
 * - 添加一些新的函数名以从堆栈跟踪中过滤
 * @version 2018/09/27
 * - 修复在线程环境下打印更好堆栈跟踪的问题
 * @version 2018/09/25
 * - 修改 setTopLevelExceptionHandlerEnabled，使其更适合线程环境
 * @version 2016/12/23
 * - 添加更多用于堆栈跟踪过滤的函数名（主要是线程相关）
 * @version 2016/12/09
 * - 添加 insertStarsBeforeEachLine
 * @version 2016/11/07
 * - 添加 cleanupFunctionNameForStackTrace
 * - 小幅重构 shouldFilterOutFromStackTrace
 * @version 2016/10/30
 * - 将递归函数移到 recursion.h/cpp
 * @version 2016/10/04
 * - 移除所有静态变量（改用 STATIC_VARIABLE 宏）
 * @version 2016/08/02
 * - 向堆栈跟踪添加一些新的 C++11 过滤器
 * - 修复异常处理程序 *** 消息的间距
 * @version 2015/10/13
 * - 修复 terminate 处理程序，使其在结束时关闭信号处理程序
 * @version 2015/05/28
 * - 修复 Windows 上异常堆栈跟踪打印格式的小错误
 * @version 2014/11/19
 * - 禁用 SetThreadErrorMode，以避免 Windows 系统上的编译错误
 * @version 2014/11/18
 * - 修复从堆栈跟踪中过滤嵌套 <> 模板参数的小错误
 * @version 2014/11/14
 * - 修复自动评分器模式下 SIGABRT 处理的错误（原先会掩盖单元测试失败）
 * @version 2014/11/12
 * - 公开提供 printStackTrace 函数
 * - 添加顶层信号处理程序（用于空指针解引用等）
 * @since 2014/11/05
 */

#include "exceptions.h"
#include <csignal>
#include <string>
#include "error.h"
#include "strlib.h"
#include "private/static.h"
#include "qtgui.h"
#include <QCoreApplication> // 用于应用程序名称
#ifdef _WIN32
#include <windows.h>
#include <Debugapi.h>
#endif
#ifdef __GNUG__ // GNU C++ 编译器
#include <cxxabi.h>
#endif


namespace exceptions {
// 只是一个不等于任何现有信号的值
#define SIGSTACK (static_cast<int>(0xdeadbeef))
#define SIGUNKNOWN (static_cast<int>(0xcafebabe))

// 静态“变量”（使用函数形式以避免初始化顺序错误）
STATIC_VARIABLE_DECLARE(std::string, gProgramName, "")
STATIC_CONST_VARIABLE_DECLARE_COLLECTION(Vector<int>, SIGNALS_HANDLED, SIGSEGV, SIGILL, SIGFPE, SIGABRT)

static void signalHandlerDisable();
static void signalHandlerEnable();
static void stanfordCppLibSignalHandler(int sig);
[[noreturn]] static void stanfordCppLibTerminateHandler();

#ifdef __GNUG__ // GNU C++ 编译器

static std::string demangle(const char* mangled_name)
{
    int status = -99;
    // name 由 malloc 分配并会泄漏，但我们只在 terminate 时反修饰……
    char *name = __cxxabiv1::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
    return (status == 0 && name) ? name : mangled_name;
}

#else

static std::string demangle(const char* mangled_name) { return mangled_name; }

#endif // _GNUG_

#if _WIN32

void interruptIfDebug()
{
    if (IsDebuggerPresent())
        DebugBreak();
}

#else

enum status_t { DBG_UNKNOWN = -1, DBG_NO, DBG_YES };
static status_t gStatus = DBG_UNKNOWN;

static void local_handler(int)
{
    gStatus = DBG_NO;
    signal(SIGTRAP, SIG_DFL); // 重置为默认处理程序
}

void interruptIfDebug()
{
    if (gStatus == DBG_UNKNOWN) { // 第一次执行时
        gStatus = DBG_YES;  // 除非获知其他情况，否则假定存在调试器
        signal(SIGTRAP, local_handler); // 安装我们的信号处理程序
        raise(SIGTRAP); // raise；如果处理程序接收到信号，则没有 IsDebuggerPresent
                        // 如果在调试器中运行，则调试器会接收到它
    } else if (gStatus == DBG_YES) {
        raise(SIGTRAP);
    }
}

#endif

bool getTopLevelExceptionHandlerEnabled() {
    return std::get_terminate() == stanfordCppLibTerminateHandler;
}

std::string& getProgramName() {
    return STATIC_VARIABLE(gProgramName);
}

void setProgramName(char* programName) {
    STATIC_VARIABLE(gProgramName) = programName;
}

#ifdef _WIN32

LONG WINAPI UnhandledException(LPEXCEPTION_POINTERS exceptionInfo) {
    DWORD code = exceptionInfo->ExceptionRecord->ExceptionCode;
    if (code == EXCEPTION_STACK_OVERFLOW || code == EXCEPTION_FLT_STACK_CHECK) {
        stanfordCppLibSignalHandler(SIGSTACK);
    } else if (code == EXCEPTION_IN_PAGE_ERROR || code == EXCEPTION_ACCESS_VIOLATION) {
        stanfordCppLibSignalHandler(SIGSEGV);
    } else if (code == EXCEPTION_FLT_DENORMAL_OPERAND || code == EXCEPTION_FLT_DIVIDE_BY_ZERO
               || code == EXCEPTION_FLT_INEXACT_RESULT || code == EXCEPTION_FLT_INVALID_OPERATION
               || code == EXCEPTION_FLT_OVERFLOW || code == EXCEPTION_FLT_UNDERFLOW
               || code == EXCEPTION_INT_DIVIDE_BY_ZERO || code == EXCEPTION_INT_OVERFLOW) {
        stanfordCppLibSignalHandler(SIGFPE);
    } else if (code == EXCEPTION_ILLEGAL_INSTRUCTION || code == EXCEPTION_PRIV_INSTRUCTION) {
        stanfordCppLibSignalHandler(SIGILL);
    } else {
        stanfordCppLibSignalHandler(SIGUNKNOWN);
    }
    return EXCEPTION_EXECUTE_HANDLER;
}
#endif // _WIN32

void setTopLevelExceptionHandlerEnabled(bool enabled) {
    static void (* old_terminate)() = nullptr;

    if (enabled) {
        void (* previous)() = std::set_terminate(stanfordCppLibTerminateHandler);
        if (previous != stanfordCppLibTerminateHandler) {
            old_terminate = previous;
        }
#ifdef _WIN32
        SetErrorMode(SEM_FAILCRITICALERRORS);
        SetUnhandledExceptionFilter(UnhandledException);
#endif // _WIN32
        signalHandlerEnable(); // 捕获段错误 / abort / fpe
    } else {
        std::set_terminate(old_terminate);
        signalHandlerDisable();
    }
}

static void signalHandlerDisable() {
    for (int sig : STATIC_VARIABLE(SIGNALS_HANDLED)) {
        signal(sig, SIG_DFL);
    }
}

static void signalHandlerEnable() {
#if _WIN32
    for (int sig : STATIC_VARIABLE(SIGNALS_HANDLED)) {
        signal(sig, stanfordCppLibSignalHandler); // 仅 Windows 信号，不是 sigaction，唉
    }
#else
    struct sigaction action;
    action.sa_handler = stanfordCppLibSignalHandler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    // 处理程序运行期间屏蔽其他信号
    for (int sig : STATIC_VARIABLE(SIGNALS_HANDLED)) {
        sigaddset(&action.sa_mask, sig);
    }
    // 对所有处理的信号使用同一操作
    for (int sig : STATIC_VARIABLE(SIGNALS_HANDLED)) {
        sigaction(sig, &action, 0);
    }
#endif
}

static void reportFatalEvent(std::string event, std::string details)
{
    std::string indent = "    "; // 用于让详细信息从样板代码中突出显示

    std::cerr << std::endl;
    std::cerr <<"*** STANFORD C++ LIBRARY" << std::endl;
    std::cerr << "*** The " << QCoreApplication::applicationName().toStdString() << " program has terminated unexpectedly (crashed)" << std::endl;
    std::cerr << "*** " << event << std::endl;
    stringReplaceInPlace(details ,"\n", "\n" + indent);
    std::cerr << std::endl << indent << details << std::endl << std::endl;
    std::cerr << "*** To get more information about a program crash," << std::endl;
    std::cerr << "*** run your program again under the debugger." << std::endl;
    std::cerr << std::endl;
    std::cerr.flush();
}

/*
 * 进程信号的通用处理程序。
 * 打印信号详细信息。
 */
static void stanfordCppLibSignalHandler(int sig) {
    signalHandlerDisable();

   // 根据发生的信号类型定制错误消息
    std::string event = "A fatal error (signal " + std::to_string(sig) + ") was received";
    std::string details = "No details were provided about the error";


    if (sig == SIGSEGV) {
        event = "A segmentation fault (SIGSEGV) occurred";
        details = "This error indicates your program attempted to dereference a pointer\nto an invalid memory address (possibly out of bounds, deallocated, nullptr, ...)";
    } else if (sig == SIGABRT) {
        event = "An abort error (SIGABRT) was raised";
        details = "This error is raised by system functions that detect corrupt state";
    } else if (sig == SIGFPE) {
        event = "An arithmetic error (SIGFPE) occurred";
        details = "This error happens when dividing by zero or producing numeric overflow";
    } else if (sig == SIGSTACK) {
        event = "A stack overflow occurred";
        details = "This can happen when your program has infinite recursion";
    } else if (sig == SIGUSR1) {
        event = "Custom signal 1 was raised";
        details = "This can happen when your program produces infinite output";
    }
    event += " during program execution";

    reportFatalEvent(event, details);

    if (GThread::iAmRunningOnTheQtGuiThread()) {
        // 如果崩溃的是 GUI 线程，则无法恢复
        raise(sig); // 我们的信号处理已禁用，默认处理程序将中止
    } else {
        interruptIfDebug();
        stanfordcpplib::studentThreadHasExited("Terminated");
        native_thread_exit(); // 退出此线程（不返回），GUI 循环可继续运行
    }
}

/*
 * 任何未捕获异常的通用处理程序。
 * 打印异常详细信息。
 */
[[noreturn]] static void stanfordCppLibTerminateHandler() {
    signalHandlerDisable();

    std::string event  ="An exception was thrown during program execution";
    std::string details = "(details of exception unknown)";

    try {
        throw;   // 重新抛出已经发生的异常
    } catch (const ErrorException& ex) {
        event = "A fatal error was reported:";
        details = ex.what();
    } catch (const std::exception& ex) {
        event = "A C++ standard exception was thrown during program execution";
        details = demangle(typeid(ex).name()) + " " + ex.what();
    } catch (const std::string& str) {
        details = str;
    } catch (char const* str) {
        details = str;
    } catch (int n) {   // 抛出基本类型帮助不大，但我想有些人可能会这样做
        details = "int exception " + std::to_string(n);
    } catch (double d) {
        details = "double exception " + realToString(d);
    } catch (...) {
        event = "An unexpected exception was thrown during program execution";
        // 使用默认详细信息
    }

    reportFatalEvent(event, details);

    if (GThread::iAmRunningOnTheQtGuiThread()) {
        // 如果崩溃的是 GUI 线程，则无法恢复
        abort();
    } else {
        interruptIfDebug();
        stanfordcpplib::studentThreadHasExited("Terminated");
        native_thread_exit(); // 退出此线程（不返回），GUI 循环可继续运行
    }
}


} // namespace exceptions
