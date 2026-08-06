/*
 * 文件：console.cpp
 * -----------------
 * 此文件实现 console .h 接口。
 *
 * @author Marty Stepp
 * @version 2019/04/12
 * - 在无界面模式中添加 pause() 实现（空实现）
 * @version 2018/11/22
 * - 添加无界面模式支持
 * @version 2018/10/01
 * - 修复即使未包含图形控制台也会弹出的错误
 * @version 2018/08/23
 * - 重命名为 console .cpp/h，以替代 Java 版本
 * - 将 gconsolewindow.h/cpp 独立拆分
 * @version 2018/07/15
 * - 初始版本，基于 io/console .cpp
 */

#include "consoletext.h"
#include <cstdio>
#include "error.h"
#include "exceptions.h"
#include "filelib.h"
#include "gconsolewindow.h"
#include "gthread.h"
#include "private/static.h"

// 可以通过显式调用 setConsoleBlah 覆盖默认值
static const int DEFAULT_X = -1, DEFAULT_Y = -1; // 将居中
static const int DEFAULT_WIDTH = 900, DEFAULT_HEIGHT = 500;
static const bool DEFAULT_ECHO = true, DEFAULT_EXIT_ON_CLOSE = true;

#ifdef SPL_HEADLESS_MODE

void clearConsole() {
    // 空
}

bool getConsoleClearEnabled() {
    return true;
}

/* GWindow::CloseOperation */ int getConsoleCloseOperation() {
    return 0;
}

bool getConsoleEcho() {
    return true;
}

bool getConsoleEnabled() {
    return true;
}

bool getConsoleExitProgramOnClose() {
    return true;
}

std::string getConsoleFont() {
    return "";
}

double getConsoleHeight() {
    return 0;
}

bool getConsoleLocationSaved() {
    return false;
}

bool getConsolePrintExceptions() {
    return exceptions::getTopLevelExceptionHandlerEnabled();
}

bool getConsoleSettingsLocked() {
    return false;
}

double getConsoleWidth() {
    return 0;
}

std::string getConsoleWindowTitle() {
    return "";
}

void pause(double /*毫秒*/) {
    // 空
}

void setConsoleClearEnabled(bool /*值*/) {
    // 空
}

void setConsoleCloseOperation(int /*op*/) {
    // 空
}

void setConsoleEcho(bool /*回显*/) {
    // 空
}

void setConsoleEnabled(bool /*已启用*/) {
    // 空
}

void setConsoleErrorColor(const std::string& /*颜色*/) {
    // 空
}

void setConsoleExitProgramOnClose(bool /*exitOnClose*/) {
    // 空
}

void setConsoleFont(const std::string& /*字体*/) {
    // 空
}

void setConsoleLocation(double /*x*/, double /*y*/) {
    // 空
}

void setConsoleLocationSaved(bool /*值*/) {
    // 空
}

void setConsoleOutputColor(const std::string& /*颜色*/) {
    // 空
}

void setConsoleSettingsLocked(bool /*值*/) {
    // 空
}

void setConsoleSize(double /*宽度*/, double /*高度*/) {
    // 空
}

void setConsoleWindowTitle(const std::string& /*标题*/) {
    // 空
}

void shutdownConsole() {
    // 空
}

#else // SPL_HEADLESS_MODE

void clearConsole() {
    GConsoleWindow::instance()->clearConsole();
}

bool getConsoleClearEnabled() {
    return GConsoleWindow::instance()->isClearEnabled();
}

/* GWindow::CloseOperation */ int getConsoleCloseOperation() {
    return GConsoleWindow::instance()->getCloseOperation();
}

bool getConsoleEcho() {
    return GConsoleWindow::instance()->isEcho();
}

bool getConsoleEnabled() {
#ifdef __DONT_ENABLE_QT_GRAPHICAL_CONSOLE
    return false;
#else
    return GConsoleWindow::consoleEnabled();
#endif
}

bool getConsoleExitProgramOnClose() {
    return GConsoleWindow::instance()->getCloseOperation() == GWindow::CLOSE_EXIT;
}

std::string getConsoleFont() {
#ifdef __DONT_ENABLE_QT_GRAPHICAL_CONSOLE
    return GConsoleWindow::getDefaultFont();
#else
    return GConsoleWindow::instance()->getFont();
#endif
}

double getConsoleHeight() {
    return GConsoleWindow::instance()->getHeight();
}

GPoint getConsoleLocation() {
    return GConsoleWindow::instance()->getLocation();
}

bool getConsoleLocationSaved() {
    return GConsoleWindow::instance()->isLocationSaved();
}

bool getConsolePrintExceptions() {
    return exceptions::getTopLevelExceptionHandlerEnabled();
}

bool getConsoleSettingsLocked() {
    return GConsoleWindow::isInitialized()
            && GConsoleWindow::instance()->isLocked();
}

GDimension getConsoleSize() {
    return GConsoleWindow::instance()->getSize();
}

double getConsoleWidth() {
    return GConsoleWindow::instance()->getWidth();
}

GConsoleWindow* getConsoleWindow() {
    return GConsoleWindow::instance();
}

std::string getConsoleWindowTitle() {
    return GConsoleWindow::instance()->getTitle();
}

void setConsoleClearEnabled(bool value) {
    if (getConsoleSettingsLocked()) { return; }
    GConsoleWindow::instance()->setClearEnabled(value);
}

void setConsoleCloseOperation(/*GWindow::CloseOperation*/ int op) {
    GWindow::CloseOperation gwcop = static_cast<GWindow::CloseOperation>(op);
    if (getConsoleSettingsLocked()) { return; }
    GConsoleWindow::instance()->setCloseOperation(gwcop);
}

void setConsoleEcho(bool echo) {
    if (getConsoleSettingsLocked()) { return; }
    GConsoleWindow::instance()->setEcho(echo);
}

void setConsoleEnabled(bool enabled) {
    GConsoleWindow::setConsoleEnabled(enabled);
}

void setConsoleErrorColor(const std::string& color) {
    if (getConsoleSettingsLocked()) { return; }
    GConsoleWindow::instance()->setErrorColor(color);
}

void setConsoleExitProgramOnClose(bool exitOnClose) {
    if (getConsoleSettingsLocked()) { return; }
    GConsoleWindow::instance()->setExitOnClose(exitOnClose);
}

void setConsoleFont(const std::string& font) {
    if (getConsoleSettingsLocked()) { return; }
    GConsoleWindow::instance()->setFont(font);
}

void setConsoleLocation(double x, double y) {
    if (getConsoleSettingsLocked()) { return; }
    if (floatingPointEqual(x, -1) && floatingPointEqual(y, -1)) {
        GConsoleWindow::instance()->center();
    } else {
        GConsoleWindow::instance()->setLocation(x, y);
    }
}

void setConsoleLocationSaved(bool value) {
    GConsoleWindow::instance()->setLocationSaved(value);
}

void setConsoleOutputColor(const std::string& color) {
    GConsoleWindow::instance()->setOutputColor(color);
}

void setConsoleSettingsLocked(bool value) {
    GConsoleWindow::instance()->setLocked(value);
}

void setConsoleSize(double width, double height) {
    if (getConsoleSettingsLocked()) { return; }
    GConsoleWindow::instance()->setConsoleSize(width, height);
}

void setConsoleWindowTitle(const std::string& title) {
    if (getConsoleSettingsLocked()) { return; }
    GConsoleWindow::instance()->setTitle(title);
}

void shutdownConsole() {
    if (getConsoleEnabled() && !GConsoleWindow::instance()->isLocked()) {
        GConsoleWindow::instance()->shutdown("Shutdown");
    }
}

#endif // SPL_HEADLESS_MODE

/*
 * 设置控制台选项，例如窗口大小、位置、关闭时退出等。
 * 恢复为默认值
 */
void setConsolePropertiesQt() {

    setConsoleSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setConsoleLocation(DEFAULT_X, DEFAULT_Y);
    setConsoleEcho(DEFAULT_ECHO);
    setConsoleExitProgramOnClose(DEFAULT_EXIT_ON_CLOSE);
}

void initializeQtGraphicalConsole() {
#ifndef __DONT_ENABLE_QT_GRAPHICAL_CONSOLE
    // 确保控制台只初始化一次
    static bool _initialized = false;
    if (_initialized) {
        return;
    }
    _initialized = true;

    // 声明此对象可确保 std::cin、cout、cerr 已初始化
    // 在库尝试处理/重定向之前正确初始化它们
    static std::ios_base::Init ios_base_init;

#ifndef SPL_HEADLESS_MODE
    if (GConsoleWindow::consoleEnabled()) {
        GConsoleWindow::instance();   // 确保控制台窗口已就绪
        setConsolePropertiesQt();
    }
#endif // SPL_HEADLESS_MODE

#endif // __DONT_ENABLE_QT_GRAPHICAL_CONSOLE
}
