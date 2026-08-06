#include "Core.h"
#include "BarrierGUI.h"
#include "GUIMain.h"
#include "ConsoleMain.h"
#include "AutograderMain.h"
#include "EmptyProblemHandler.h"
#include "filelib.h"
#include <algorithm>
#include <map>
#include <set>
using namespace std;

/* 从配置文件中读取所有 #define。 */
#define RUN_TESTS_MENU_OPTION()
#define MENU_ORDER(...)
#define WINDOW_TITLE(title)
#define TEST_ORDER(...)
#define TEST_BARRIER(demo, ...)
#define INITIAL_HANDLER(demo)
#include "../Demos/GUIConfig.h"

/* 捕获所有 #define。 */
#ifdef MG_CONSOLE_MODE
    #define MG_INTERNAL_CONSOLE_MODE
    #undef MG_CONSOLE_MODE

    /* 在控制台模式下启用控制台。 */
    #include "console.h"

    namespace MiniGUI::Config {
        bool isConsoleMode() {
            return true;
        }
    }
#else
    namespace MiniGUI::Config {
        bool isConsoleMode() {
            return false;
        }
    }
#endif

#ifdef MG_AUTOGRADER_MODE
    namespace MiniGUI::Config {
        bool isAutograderMode() {
            return true;
        }
    }
#else
    namespace MiniGUI::Config {
        bool isAutograderMode() {
            return false;
        }
    }
#endif

/* 取消定义所有 #define，以便未来可以再次导入。 */
#undef WINDOW_TITLE
#undef TEST_BARRIER
#undef MENU_ORDER
#undef TEST_ORDER
#undef INITIAL_HANDLER
#undef RUN_TESTS_MENU_OPTION

/* 使用 X 宏技巧获取所有文件名的列表。 */
namespace {
    const vector<string>& demoFileOrder() {
        static const vector<string> kAllFiles = {
            #define RUN_TESTS_MENU_OPTION() "TestingGUI.cpp",
            #define MENU_ORDER(...) __VA_ARGS__,
            #define TEST_ORDER(...)
            #define TEST_BARRIER(demo, ...)
            #define WINDOW_TITLE(title)
            #define INITIAL_HANDLER(demo)

            #include "../Demos/GUIConfig.h"

            #ifdef MG_CONSOLE_MODE
            #undef MG_CONSOLE_MODE
            #endif

            #undef INITIAL_HANDLER
            #undef TEST_ORDER
            #undef TEST_BARRIER
            #undef WINDOW_TITLE
            #undef MENU_ORDER
            #undef RUN_TESTS_MENU_OPTION
        };
        return kAllFiles;
    }

    const vector<string>& testFileOrder() {
        static const vector<string> kAllFiles = {
            #define RUN_TESTS_MENU_OPTION()
            #define MENU_ORDER(...)
            #define TEST_ORDER(...) __VA_ARGS__
            #define TEST_BARRIER(demo, ...)
            #define WINDOW_TITLE(title)
            #define INITIAL_HANDLER(demo)

            #include "../Demos/GUIConfig.h"

            #ifdef MG_CONSOLE_MODE
            #undef MG_CONSOLE_MODE
            #endif

            #undef INITIAL_HANDLER
            #undef TEST_BARRIER
            #undef TEST_ORDER
            #undef WINDOW_TITLE
            #undef MENU_ORDER
            #undef RUN_TESTS_MENU_OPTION
        };
        return kAllFiles;
    }

    /* 返回文件在文件名列表中的索引；若不存在，则返回一个较大值。 */
    size_t fileIndex(const string& filename) {
        return find(demoFileOrder().begin(), demoFileOrder().end(), filename) - demoFileOrder().begin();
    }

    /* 比较两个文件名，并按它们在演示文件列表中的出现顺序排序。 */
    int demoFileCompare(const string& lhs, const string& rhs) {
        /* 比较文件名顺序。 */
        size_t leftIndex  = fileIndex(lhs);
        size_t rightIndex = fileIndex(rhs);
        if (leftIndex < rightIndex) return -1;
        if (leftIndex > rightIndex) return +1;

        /* 若文件名具有相同索引，但文件名本身
         * 若二者不同，则以此打破平局。
         */
        if (lhs < rhs) return -1;
        if (lhs > rhs) return +1;
        return 0;
    }
}

/* 图形处理程序。 */
namespace {
    struct GraphicsHandler {
        string filename;
        size_t line;
        string name;
        function<shared_ptr<ProblemHandler>(GWindow&)> callback;

        /* 是否应将其包含在可见处理程序列表中？ */
        bool isPublic;
    };

    /* 所有图形处理程序的主列表；由静态初始化器填充。 */
    vector<GraphicsHandler>& graphicsHandlers() {
        static vector<GraphicsHandler> theRawHandlers;
        return theRawHandlers;
    };

    #ifndef MG_INTERNAL_CONSOLE_MODE
        /* 先按文件名、再按行号对处理程序排序。 */
        void sortGraphicsHandlers() {
            static bool sorted = false;
            if (!sorted) {
                sort(graphicsHandlers().begin(), graphicsHandlers().end(),
                     [](const GraphicsHandler& lhs, const GraphicsHandler& rhs) {
                        int fileComp = demoFileCompare(lhs.filename, rhs.filename);
                        if (fileComp != 0) {
                            return fileComp < 0;
                        }

                        /* 文件顺序相同，文件也相同。现在按行号打破平局。 */
                        return lhs.line < rhs.line;
                });

                sorted = true;
            }
        }
    #endif
}

/* 控制台处理程序。 */
namespace {
    struct ConsoleHandler {
        string filename;
        size_t line;
        string name;
        function<void()> callback;

        /* 是否应将其包含在可见处理程序列表中？ */
        bool isPublic;
    };

    /* 所有图形处理程序的主列表；由静态初始化器填充。 */
    vector<ConsoleHandler>& consoleHandlers() {
        static vector<ConsoleHandler> theRawHandlers;
        return theRawHandlers;
    };

    #ifdef MG_INTERNAL_CONSOLE_MODE
        /* 先按文件名、再按行号对处理程序排序。 */
        void sortConsoleHandlers() {
            static bool sorted = false;
            if (!sorted) {
                sort(consoleHandlers().begin(), consoleHandlers().end(),
                     [](const ConsoleHandler& lhs, const ConsoleHandler& rhs) {
                        int fileComp = demoFileCompare(lhs.filename, rhs.filename);
                        if (fileComp != 0) {
                            return fileComp < 0;
                        }

                        /* 文件顺序相同，文件也相同。现在按行号打破平局。 */
                        return lhs.line < rhs.line;
                });

                sorted = true;
            }
        }
    #endif
}

/* 再次使用 X 宏技巧定义窗口标题。 */
static string kWindowTitle =
    #define MENU_ORDER(...)
    #define RUN_TESTS_MENU_OPTION()
    #define WINDOW_TITLE(title) title
    #define TEST_ORDER(...)
    #define CONSOLE_MODE()
    #define TEST_BARRIER(demo, ...)
    #define INITIAL_HANDLER(demo)

    #include "../Demos/GUIConfig.h"

    #ifdef MG_CONSOLE_MODE
    #undef MG_CONSOLE_MODE
    #endif

    #undef INITIAL_HANDLER
    #undef CONSOLE_MODE
    #undef TEST_BARRIER
    #undef WINDOW_TITLE
    #undef GUI_HANDLER
    #undef MENU_ORDER
    #undef TEST_ORDER
;

/* 安装器。 */
namespace MiniGUI {
    namespace Detail {
        GraphicsInstaller::GraphicsInstaller(FileKey key, const char* name,
                                             function<shared_ptr<ProblemHandler>(GWindow&)> callback) {
            /* 确认目标文件存在于文件列表中；如果不存在，则不要将其包含在内
             * 列入选项列表，因为它可能是私有的或已被禁用。
             */
            bool isPublic = find(demoFileOrder().begin(), demoFileOrder().end(), getTail(key.filename)) != demoFileOrder().end();
            graphicsHandlers().push_back({
                getTail(key.filename),
                key.line,
                name,
                callback,
                isPublic
            });
        }

        ConsoleInstaller::ConsoleInstaller(FileKey key, const char* name,
                                           function<void()> callback) {
            /* 确认目标文件存在于文件列表中；如果不存在，则不要将其包含在内
             * 列入选项列表，因为它可能是私有的或已被禁用。
             */
            bool isPublic = find(demoFileOrder().begin(), demoFileOrder().end(), getTail(key.filename)) != demoFileOrder().end();
            consoleHandlers().push_back({
                getTail(key.filename),
                key.line,
                name,
                callback,
                isPublic
            });
        }
    }
}

/* 测试屏障。 */
namespace {
    const map<string, set<string>> kTestBarriers = {
        #define MENU_ORDER(...)
        #define RUN_TESTS_MENU_OPTION()
        #define WINDOW_TITLE(title)
        #define TEST_ORDER(...)
        #define CONSOLE_MODE()
        #define TEST_BARRIER(demo, ...) { demo, {__VA_ARGS__} },
        #define INITIAL_HANDLER(demo)

        #include "../Demos/GUIConfig.h"

        #ifdef MG_CONSOLE_MODE
        #undef MG_CONSOLE_MODE
        #endif

        #undef INITIAL_HANDLER
        #undef CONSOLE_MODE
        #undef TEST_BARRIER
        #undef WINDOW_TITLE
        #undef GUI_HANDLER
        #undef MENU_ORDER
        #undef TEST_ORDER
    };
}

/* 初始处理程序。 */
namespace {
    const char kInitialDemoFile[] = ""
        #define MENU_ORDER(...)
        #define RUN_TESTS_MENU_OPTION()
        #define WINDOW_TITLE(title)
        #define TEST_ORDER(...)
        #define CONSOLE_MODE()
        #define TEST_BARRIER(demo, ...)
        #define INITIAL_HANDLER(demo) demo

        #include "../Demos/GUIConfig.h"

        #ifdef MG_CONSOLE_MODE
        #undef MG_CONSOLE_MODE
        #endif

        #undef INITIAL_HANDLER
        #undef CONSOLE_MODE
        #undef TEST_BARRIER
        #undef WINDOW_TITLE
        #undef GUI_HANDLER
        #undef MENU_ORDER
        #undef TEST_ORDER
    ;
}

namespace MiniGUI {
    namespace Config {
        /* 程序标题。 */
        std::string programTitle() {
            return kWindowTitle;
        }

        /* 菜单选项列表。 */
        vector<MenuOption> menuOptions() {
            vector<MenuOption> result;
            #ifdef MG_INTERNAL_CONSOLE_MODE
                sortConsoleHandlers();
                for (const auto& entry: consoleHandlers()) {
                    if (entry.isPublic) {
                        auto itr = kTestBarriers.find(entry.filename);
                        if (itr != kTestBarriers.end()) {
                            result.push_back({ entry.name, ifPassedThen(itr->second, entry.callback)});
                        } else {
                            result.push_back({ entry.name, entry.callback });
                        }
                    }
                }
            #else
                sortGraphicsHandlers();
                for (const auto& entry: graphicsHandlers()) {
                    if (entry.isPublic) {
                        auto constructor = entry.callback;

                        /* 若存在测试屏障，则在调用构造函数前将其启用。 */
                        auto itr = kTestBarriers.find(entry.filename);
                        if (itr != kTestBarriers.end()) {
                            constructor = ifPassedThen(itr->second, entry.callback);
                        }

                        /* 将回调包装为可安装到图形窗口中的对象。 */
                        result.push_back({ entry.name, [=]() {
                            MiniGUI::Detail::setActiveDemo(constructor(MiniGUI::Detail::graphicsWindow()));
                        }});
                    }
                }
            #endif

            return result;
        }

        /* 无回调函数的文件列表，以备需要。 */
        vector<string> testOrder() {
            return testFileOrder();
        }
    }
}

/* 自动评分模式下没有演示。 */
#ifndef MG_AUTOGRADER_MODE
namespace {
    /* 要运行的初始演示。控制台模式下默认为欢迎页面。
     * 对于控制台，此项默认为空函数。
     */
    function<void()> initialDemo() {
        #ifdef MG_INTERNAL_CONSOLE_MODE
            /* 查找名称与演示文件匹配的第一个图形处理程序。 */
            sortConsoleHandlers();
            auto itr = find_if(consoleHandlers().begin(), consoleHandlers().end(),[](const ConsoleHandler& handler) {
                return handler.filename == kInitialDemoFile;
            });

            if (itr == consoleHandlers().end()) {
                return nullptr;
            } else {
                return itr->callback;
            }
        #else
            /* 查找名称与演示文件匹配的第一个图形处理程序。 */
            sortGraphicsHandlers();
            auto itr = find_if(graphicsHandlers().begin(), graphicsHandlers().end(),[](const GraphicsHandler& handler) {
                return handler.filename == kInitialDemoFile;
            });

            if (itr == graphicsHandlers().end()) {
                return [] {
                    MiniGUI::Detail::setActiveDemo(make_shared<EmptyProblemHandler>(MiniGUI::Detail::graphicsWindow()));
                };
            } else {
                return [itr] {
                    MiniGUI::Detail::setActiveDemo(itr->callback(MiniGUI::Detail::graphicsWindow()));
                };
            }

        #endif

    }
}
#endif

int main() {
    #if defined(MG_AUTOGRADER_MODE)
        MiniGUI::Detail::autograderMain();
    #elif defined(MG_INTERNAL_CONSOLE_MODE)
        MiniGUI::Detail::consoleMain(initialDemo());
    #else
        MiniGUI::Detail::graphicsMain(initialDemo());
    #endif

    return 0;
}
