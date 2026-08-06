/* 共享配置信息。供以下对象使用：
 * 程序驱动代码，不供客户端使用。
 */

#pragma once

/* 宏：GRAPHICS_HANDLER("演示名称", GWindow& window) {
 *    ...
 * }
 *
 * 定义一个在图形模式菜单中显示的图形处理程序。
 * 此函数应返回 std::shared_ptr<T> 类型，其中 T 是某种
 * ProblemHandler 的派生类。
 */
#define GRAPHICS_HANDLER(name, argument) /* ……某些内部内容…… */

/* 宏：CONSOLE_HANDLER("演示名称") {
 *    ...
 * }
 *
 * 定义一个在控制台模式菜单中显示的演示。此函数
 * 应按需与 stdin/stdout 交互。
 */
#define CONSOLE_HANDLER(name) /* ……某些内部内容…… */







/***** 此处以下为实现部分 *****/

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include "ProblemHandler.h"

namespace MiniGUI {
    /* 具名菜单回调函数。 */
    struct MenuOption {
        std::string name;
        std::function<void()> callback;
    };

    namespace Config {
        /* 程序标题。 */
        std::string programTitle();

        /* 菜单选项列表。 */
        std::vector<MenuOption> menuOptions();

        /* 测试用例所使用的文件顺序。 */
        std::vector<std::string> testOrder();

        /* 当前是否处于控制台模式。 */
        bool isConsoleMode();

        /* 当前是否处于自动评分模式。 */
        bool isAutograderMode();
    }

    namespace Detail {
        struct FileKey {
            const char* filename;
            std::size_t line;
        };

        struct GraphicsInstaller {
            GraphicsInstaller(FileKey key,
                              const char* name,
                              std::function<std::shared_ptr<ProblemHandler>(GWindow&)>);
        };
        struct ConsoleInstaller {
            ConsoleInstaller(FileKey key,
                             const char* name,
                             std::function<void()>);
        };
    }
}

#undef GRAPHICS_HANDLER

#define GRAPHICS_HANDLER(title, arg) MAKE_GRAPHICS_HANDLER(__FILE__, __LINE__, title, arg)
#define MAKE_GRAPHICS_HANDLER(file, line, title, arg) DO_MAKE_GRAPHICS_HANDLER(file, line, title, arg)
#define DO_MAKE_GRAPHICS_HANDLER(file, line, title, arg)                  \
    static std::shared_ptr<ProblemHandler> _graphicsHandler##line(arg);   \
    static ::MiniGUI::Detail::GraphicsInstaller _installer##line(         \
        { file, line }, title, _graphicsHandler##line                     \
    );                                                                    \
    static std::shared_ptr<ProblemHandler> _graphicsHandler##line(arg)

#undef CONSOLE_HANDLER

#define CONSOLE_HANDLER(title) MAKE_CONSOLE_HANDLER(__FILE__, __LINE__, title)
#define MAKE_CONSOLE_HANDLER(file, line, title) DO_MAKE_CONSOLE_HANDLER(file, line, title)
#define DO_MAKE_CONSOLE_HANDLER(file, line, title)                        \
    static void _consoleHandler##line();                                  \
    static ::MiniGUI::Detail::ConsoleInstaller _installer##line(          \
        { file, line }, title, _consoleHandler##line                      \
    );                                                                    \
    static void _consoleHandler##line()
