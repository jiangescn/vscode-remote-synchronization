/*
 * 文件：qtgui.h
 * -------------
 *
 * @author Marty Stepp
 * @version 2018/09/09
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 qtgui.h
 * @version 2018/07/03
 * - 初始版本
 */


#ifndef _qtgui_h
#define _qtgui_h

#include <string>
#include <QApplication>
#include <QObject>

#include "gthread.h"
#include "gtypes.h"

#define EXITING_DUE_TO_WINDOW_CLOSE 106

class GWindow;

class QSPLApplication : public QApplication {
public:
    QSPLApplication(int& argc, char *argv[]);
    bool notify(QObject* receiver, QEvent* e) override;
};


/**
 * 此类包含用于初始化和管理整体
 * 库中基于 Qt 的 GUI 系统。
 * 学生和客户端通常无需直接与此类交互
 * 直接。
 * @private
 */
class QtGui : public QObject {
    Q_OBJECT

public:
    /**
     * 关闭 Qt 图形系统。
     */
    void exitGraphics(int exitCode = 0);


    /**
     * 返回应用程序的显示名称（用作
     * 窗口和菜单的标题）。如果名称（尚）不可用，
     * 返回空字符串。
     */
    std::string getApplicationDisplayName() const;

    /**
     * 返回传给 main() 函数的参数数量。
     * 字符串参数本身可以使用 getArgv 查看。
     */
    int getArgc() const;

    /**
     * 返回传给 main() 函数的字符串参数。
     * 参数数量通过 getArgc 获取。
     */
    char** getArgv() const;

    /**
     * 如果 Qt 图形子系统尚未初始化，则进行初始化。
     * 客户端无需直接调用此函数，因为它会被
     * 在 main() 运行之前由库自动执行。
     */
    void initializeQt();

    /**
     * 返回指向图形库 QtGui 对象的指针。
     */
    static QtGui* instance();

    /**
     * 在运行 main 之前设置 argc 和 argv 值。
     */
    void setArgs(int argc, char** argv);

    /**
     * 运行事件循环，调用返回 int 的给定函数。
     * 事件循环将阻塞，直到图形程序运行完毕。
     * 如果 exitAfter 参数为 true，则在事件后调用 exitGraphics
     * 循环结束。
     */
    void startBackgroundEventLoop(GThunkInt mainFunc, bool exitAfter = true);

    void startEventLoop(bool exitAfter = true);


public slots:
    /**
     * Qt 事件队列使用的槽函数。
     */
    void processEventFromQueue();

private:
    Q_DISABLE_COPY(QtGui)

    QtGui();   // 禁止构造

    /**
     * 返回指向整个 Qt 应用程序的指针。
     * 如果应用程序尚未初始化，此值将为 null。
     */
    QSPLApplication* getApplication();

    bool _initialized;
    int _argc;
    char** _argv;

    static QSPLApplication* _app;
    static QThread* _qtGuiThread;
    static GThread* _studentThread;
    static QtGui* _instance;

    friend class GEventQueue;
    friend class GThread;
    friend class GWindow;
};

namespace stanfordcpplib {
/*
 * 学生线程关闭时运行的代码。
 * @private
 */
void studentThreadHasExited(const std::string& reason);
} // namespace stanfordcpplib

#endif // _qtgui_h
