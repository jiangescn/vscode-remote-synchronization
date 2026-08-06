#ifndef ProblemHandler_Included
#define ProblemHandler_Included

#include "gwindow.h"
#include "gobjects.h"
#include <memory>
#include <string>
#include <utility>

/* 表示能够显示问题的类型的接口
 * 以图形方式显示并响应事件。
 *
 * 设计意图是按需创建和销毁每个问题处理程序
 * 取决于用户的选择，因此不要假定一定会有
 * 在实现这些类型时访问长期运行状态。
 *
 * 每个 ProblemHandler 还必须导出以下函数：
 *
 *      Constructor(GWindow&)：在关联窗口中构造新的处理程序。
 */
class ProblemHandler {
public:
    /* 多态类需要虚析构函数。 */
    virtual ~ProblemHandler() = default;

    /* 响应组件事件。 */
    virtual void actionPerformed(GObservable* source);
    virtual void changeOccurredIn(GObservable* source);

    /* 响应鼠标移动。 */
    virtual void mouseMoved(double x, double y);
    virtual void mousePressed(double x, double y);
    virtual void mouseDragged(double x, double y);
    virtual void mouseReleased(double x, double y);
    virtual void mouseExited();
    virtual void mouseClicked(double x, double y);
    virtual void mouseDoubleClicked(double x, double y);

    /* 响应计时器事件。 */
    virtual void timerFired();

    /* 响应窗口变化。 */
    virtual void windowResized();

    /* 响应链接事件。 */
    virtual void hyperlinkClicked(const std::string& url);

    /* 响应构造过程。可以运行启用 UI 的
     * 在此处编写代码。
     */
    virtual void settingUp();

    /* 响应关闭请求。返回 true 继续关闭，返回
     * 设为 false 可停止它。
     */
    virtual bool shuttingDown();

    /* 重绘窗口。 */
    void draw();

protected:
    /* 构造函数保存窗口。
     *
     * 每个 ProblemHandler 的构造函数都在 Qt GUI 线程内运行。请使用
     * 由构造函数处理初始界面框架设置，但不要执行任何会
     * 需要刷新 UI。
     */
    ProblemHandler(GWindow& window);

    /* 绘制当前状态。 */
    virtual void repaint();

    /* 将区域标记为脏。 */
    void requestRepaint();

    /* 当前操作的窗口。 */
    GWindow& window() const;

private:
    /* 脏标记。初始为脏，因为尚未绘制任何内容。 */
    bool isDirty = true;

    /* 指向主窗口的指针。 */
    GWindow* mainWindow;
};

#endif
