/*
 * 文件：console.h
 * ---------------
 * 此文件包含与库的图形控制台窗口相关的函数，
 * 使用原生 C++ 的 Qt 图形库实现，而不是 Java。
 * 通常，如果 #include 此文件，将隐式启用图形
 * 控制台。如果不希望这样做，应 #define 一个名为
 * 在包含此头文件之前定义 __DONT_ENABLE_QT_GRAPHICAL_CONSOLE。
 * 启用图形控制台后，很难再将其关闭
 * 再次用于该程序。
 *
 * @author Marty Stepp
 * @version 2018/11/22
 * - 添加无界面模式支持
 * @version 2018/10/18
 * - 修复 include，避免意外启用 GUI
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/27
 * - 清理注释
 * @version 2018/08/23
 * - 重命名为 console.h，以替代 Java 版本
 * - 将 gconsolewindow.h/cpp 独立拆分
 * @version 2018/07/29
 * - 菜单、图标、快捷键
 * @version 2018/07/26
 * - 重构 GConsoleWindow 类
 * @version 2018/07/15
 * - 初始版本，基于 io/console.h
 */


#ifndef _console_h
#define _console_h

#include <string>

#ifndef SPL_HEADLESS_MODE
class GConsoleWindow;
struct GDimension;
struct GPoint;
#endif // SPL_HEADLESS_MODE

/**
 * 擦除控制台窗口内容。
 */
void clearConsole();

/**
 * 返回是否应启用控制台的“clear”函数。
 * 默认为 true。若为 false，clear() 只会输出一条消息
 * 而不是真正清空控制台。
 * @private
 */
bool getConsoleClearEnabled();

/**
 * 返回用户点击控制台“关闭”按钮时控制台将执行的操作。
 * 默认值为 CONSOLE_HIDE_ON_CLOSE，除非另有设置。
 */
/* GWindow::CloseOperation */ int getConsoleCloseOperation();

/**
 * 返回 Stanford 图形控制台的输入/输出是否
 * 控制台窗口内容正在镜像到操作系统标准终端
 * 窗口。初始值为 false，除非之前调用以下方法将其设为 true：
 * setConsoleEcho(true)。
 */
bool getConsoleEcho();

/**
 * 返回图形控制台窗口是否已启用。
 * 如果程序中包含了 "qconsole.h"，则此值为 true。
 */
bool getConsoleEnabled();

/**
 * 返回控制台满足以下条件时整个 C++ 程序是否会终止
 * 窗口关闭。默认情况下初始值为 false。
 */
bool getConsoleExitProgramOnClose();

/**
 * 返回控制台当前使用的字体。字体
 * 通常是形如 <code>family-style-size</code> 的字符串。
 * 在此字符串中，<code>family</code> 是字体族名称；
 * <code>style</code> 可以省略（表示普通字体），也可以是
 * 字符串 <code>Bold</code>、<code>Italic</code> 或
 * <code>BoldItalic</code>；<code>size</code> 是整数
 * 表示字号。
 * 有关字体字符串的更多信息，请参阅 gfont.h。
 */
std::string getConsoleFont();

/**
 * 返回控制台窗口的像素高度。
 */
double getConsoleHeight();

/**
 * 返回控制台窗口左上角的 x/y 位置。
 */
#ifndef SPL_HEADLESS_MODE
GPoint getConsoleLocation();
#endif // SPL_HEADLESS_MODE

/**
 * 返回控制台窗口的位置是否应被记住并
 * 在程序的多次运行之间恢复。初始为 false。
 */
bool getConsoleLocationSaved();

/**
 * 返回是否启用了会导致异常被以下方式处理的功能
 * 抛出时回显到 Stanford 图形控制台窗口。
 * 默认禁用（false）。
 */
bool getConsolePrintExceptions();

/**
 * 返回 setConsoleFont 或 setConsoleSize 等函数是否
 * 当前会被忽略。请参阅 setConsoleSettingsLocked。
 * 客户端通常不应调用此方法。
 * @private
 */
bool getConsoleSettingsLocked();

/**
 * 返回控制台窗口的像素尺寸。
 */
#ifndef SPL_HEADLESS_MODE
GDimension getConsoleSize();
#endif // SPL_HEADLESS_MODE

/**
 * 返回控制台窗口的像素宽度。
 */
double getConsoleWidth();

/**
 * 返回指向图形控制台窗口的指针，
 * 它是 GWindow 的子类，因此可像操作
 * 任何其他窗口。
 *
 * @private
 */
#ifndef SPL_HEADLESS_MODE
GConsoleWindow* getConsoleWindow();
#endif // SPL_HEADLESS_MODE

/**
 * 返回控制台窗口标题栏文本。
 */
std::string getConsoleWindowTitle();

/**
 * 如果 Qt 图形控制台的状态尚未初始化，则进行初始化
 * 已初始化。
 * 客户端通常不应调用此方法。
 * @private
 */
void initializeQtGraphicalConsole();

// 定义于 gwindow.h/cpp
extern void pause(double milliseconds);

/**
 * 返回是否应启用控制台的“clear”函数。
 * 默认为 true。若为 false，clear() 只会输出一条消息
 * 而不是真正清空控制台。
 * 这有时用于帮助创建自动评分脚本。
 * @private
 */
void setConsoleClearEnabled(bool value);

/**
 * 设置用户点击控制台“关闭”按钮时控制台应执行的操作。
 */
void setConsoleCloseOperation(/*GWindow::CloseOperation*/ int op);

/**
 * 启用或禁用回显 Stanford 图形控制台的输入/输出
 * 将控制台窗口内容镜像到操作系统标准终端窗口。
 * 通常不需要这种回显，但如果你希望能够复制
 * 并将控制台交互粘贴到另一个窗口时，此功能很有用。
 */
void setConsoleEcho(bool echo);

/**
 * 设置用于在控制台窗口中显示文本的颜色。
 * 传入的颜色字符串应采用十六进制格式，例如“#ffa32f”；
 * 有关颜色和颜色字符串的更多详细信息，请参阅 gcolor.h。
 */
void setConsoleErrorColor(const std::string& color);

/**
 * 设置控制台满足以下条件时整个 C++ 程序是否应终止
 * 窗口关闭。默认情况下初始值为 false。
 */
void setConsoleExitProgramOnClose(bool exitOnClose);

/**
 * 更改控制台使用的字体。<code>font</code> 参数
 * 通常是形如 <code>family-style-size</code> 的字符串。
 * 在此字符串中，<code>family</code> 是字体族名称；
 * <code>style</code> 可以省略（表示普通字体），也可以是
 * 字符串 <code>Bold</code>、<code>Italic</code> 或
 * <code>BoldItalic</code>；<code>size</code> 是整数
 * 表示字号。如果其中任何组件
 * 指定为星号时，保留现有值。
 * <code>font</code> 参数也可以是一系列
 * 多个这样的规范以分号分隔，在这种情况下
 * 使用系统上第一个可用字体。
 * 有关字体字符串的更多信息，请参阅 gfont.h。
 */
void setConsoleFont(const std::string& font);

/**
 * 将控制台左上角的 (x, y) 像素位置更改为
 * 指定坐标，相对于屏幕左上角。
 */
void setConsoleLocation(double x, double y);

/**
 * 设置控制台窗口的位置是否应被记住并
 * 在程序的多次运行之间恢复。默认为 false。
 */
void setConsoleLocationSaved(bool value);

/**
 * 设置用于在控制台窗口中显示文本的颜色。
 * 传入的颜色字符串应采用十六进制格式，例如“#ffa32f”；
 * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
 */
void setConsoleOutputColor(const std::string& color);

/**
 * 如果设为 true，将禁用 setConsoleFont 或 setConsoleSize 等函数，
 * 通过否定其中的此类调用来帮助构建自动评分器
 * 学生的主程序。初始为 false。
 * 客户端通常不应调用此方法。
 * @private
 */
void setConsoleSettingsLocked(bool value);

/**
 * 将控制台大小更改为指定像素尺寸。
 */
void setConsoleSize(double width, double height);

/**
 * 将控制台窗口标题栏文本更改为指定文本。
 */
void setConsoleWindowTitle(const std::string& title);

/**
 * 关闭图形控制台窗口并将其停用。
 */
void shutdownConsole();

#endif // _console_h


/*
 * console.h 的特殊之处在于学生程序必须能够 #include 它
 * 然后神奇地获得图形控制台而不是标准控制台；
 * 但我们希望其他库文件能够包含 console.h，以获得
 * 函数原型，而不真正启用图形控制台。
 * 为实现这一点，我们提供了 __DONT_ENABLE_QT_GRAPHICAL_CONSOLE 标志，库
 * 文件可以在 #include console.h 之前定义。如果这样做，将会
 * 声明原型，但不初始化图形控制台。
 */
#ifndef __DONT_ENABLE_QT_GRAPHICAL_CONSOLE

extern void setConsoleEnabled(bool);

namespace stanfordcpplib {
namespace qtgui {

#ifndef QtConsoleInitializer_created
#define QtConsoleInitializer_created
/**
 * @private
 */
class QtConsoleInitializer_private {
public:
    /*
     * 初始化库的代码。
     * 以类构造函数的形式实现，以便它会在
     * 静态初始化阶段，它发生在学生代码之前
     * main 函数。
     */
    QtConsoleInitializer_private() {
        setConsoleEnabled(true);
    }
};

/**
 * @private
 */
static QtConsoleInitializer_private __qt_console_init;
#endif // QtConsoleInitializer_created

} // namespace qtgui
} // namespace stanfordcpplib

#endif // __DONT_ENABLE_QT_GRAPHICAL_CONSOLE

