#include "GUIMain.h"
#include "Core.h"
#include "ProblemHandler.h"
#include "EmptyProblemHandler.h"
#include "gwindow.h"
#include "gevent.h"
#include "gbutton.h"
#include "goptionpane.h"
#include "gthread.h"
#include "map.h"
#include <chrono>
#include <cstdlib>
using namespace std;

namespace {
    /* 窗口图形常量。 */
    const double kWindowWidth  = 1000;
    const double kWindowHeight = 800;

    /* 计时器事件被视为“过期”前的毫秒数。 */
    const long kTimelyCutoff = 100;

    using Constructor = std::function<void()>;

    /* 表示图形功能正常运行所需全部状态的类型。 */
    struct Graphics {
        GWindow window{kWindowWidth, kWindowHeight}; // 窗口
        shared_ptr<ProblemHandler> handler;          // 当前任务处理程序
        Map<GObservable*, Constructor> constructors; // 从按钮到构造函数的映射。
    };

    /* 创建图形窗口及其关联状态。 */
    Graphics* makeGraphics() {
        auto* result = new Graphics();

        /* 基本窗口设置。 */
        result->window.setTitle(MiniGUI::Config::programTitle());
        result->window.setCloseOperation(GWindow::CLOSE_DO_NOTHING);

        /* 基本图形设置。 */
        result->window.setRepaintImmediately(false);
        result->window.setCanvasSize(kWindowWidth, kWindowHeight);

        /* 问题处理程序。 */
        for (const auto& entry: MiniGUI::Config::menuOptions()) {
            auto* button = new GButton(entry.name);
            result->window.addToRegion(button, "NORTH");

            result->constructors[button] = entry.callback;
        }
        return result;
    }

    /* 设置当前活动问题。 */
    void setProblem(Graphics* graphics, GObservable* source) {
        /* 检查是否应中止关闭过程。 */
        if (graphics->handler && !graphics->handler->shuttingDown()) {
            return;
        }

        auto constructor = graphics->constructors.get(source);
        if (!constructor) {
            error("No constructor for that GObservable?");
        }

        /* 释放之前的处理程序，清空显示，然后
         * 设置新处理程序。此操作在 Qt GUI 线程中执行
         * 以避免闪烁。
         */
        GThread::runOnQtGuiThread([&] {
            graphics->handler.reset();
            graphics->window.clearCanvas();
            constructor();
        });
        graphics->handler->settingUp();
    }

    Graphics* theGraphics = nullptr;
    bool theOptionsEnabled = true;
}

/* 启用/禁用所有演示按钮。 */
void setDemoOptionsEnabled(bool isEnabled) {
    for (GObservable* option: theGraphics->constructors) {
        if (auto* button = dynamic_cast<GButton*>(option)) {
            button->setEnabled(isEnabled);
        }
    }
    theOptionsEnabled = isEnabled;
}

namespace MiniGUI {
    namespace Detail {
        GWindow& graphicsWindow() {
            if (!theGraphics) error("Graphics window not available.");
            return theGraphics->window;
        }

        void setActiveDemo(shared_ptr<ProblemHandler> handler) {
            theGraphics->handler = handler;
        }

        void graphicsMain(function<void()> initialDemo) {
            theGraphics = makeGraphics();

            /* 设置初始处理程序。 */
            GThread::runOnQtGuiThread([&] {
                initialDemo();
            });
            theGraphics->handler->settingUp();

            while (true) {
                /* 更新窗口（若无需重绘，则为空操作）。 */
                theGraphics->handler->draw();

                GEvent e = waitForEvent(MOUSE_EVENT | ACTION_EVENT | CHANGE_EVENT | TIMER_EVENT | WINDOW_EVENT | HYPERLINK_EVENT);
                if (e.getEventClass() == ACTION_EVENT) {
                    auto source = GActionEvent(e).getSource();

                    /* 我们负责问题按钮。 */
                    if (theGraphics->constructors.containsKey(source)) {
                        if (theOptionsEnabled) setProblem(theGraphics, source);
                    }
                    /* 其他任何事件都由问题处理程序负责。 */
                    else {
                        theGraphics->handler->actionPerformed(source);
                    }
                } else if (e.getEventClass() == CHANGE_EVENT) {
                    theGraphics->handler->changeOccurredIn(GChangeEvent(e).getSource());
                } else if (e.getEventClass() == TIMER_EVENT) {
                    /* 若某个处理程序响应缓慢，可能造成错误的正反馈
                     * 形成反馈循环，使计时器事件无法及时从队列中取出
                     * 事件生成速度，导致更高优先级事件得不到处理。
                     * 为解决此问题，如果取出一个尚未在合理时间内发生的计时器事件
                     * 足够接近当前时间，则假定处理已经落后，并
                     * 直接吞掉该事件，不进行处理。
                     */
                    long now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
                    if (now - e.getTime() < kTimelyCutoff) {
                        theGraphics->handler->timerFired();
                    }
                } else if (e.getEventClass() == MOUSE_EVENT) {
                    /* 确保事件由画布产生，而不是由某个
                     * 窗口中的某个交互控件。
                     */
                    if (e.getSource() == theGraphics->window.getCanvas()) {
                        if (e.getEventType() == MOUSE_MOVED) {
                            theGraphics->handler->mouseMoved(e.getX(), e.getY());
                        } else if (e.getEventType() == MOUSE_PRESSED) {
                            theGraphics->handler->mousePressed(e.getX(), e.getY());
                        } else if (e.getEventType() == MOUSE_DRAGGED) {
                            theGraphics->handler->mouseDragged(e.getX(), e.getY());
                        } else if (e.getEventType() == MOUSE_RELEASED) {
                            theGraphics->handler->mouseReleased(e.getX(), e.getY());
                        } else if (e.getEventType() == MOUSE_EXITED) {
                            theGraphics->handler->mouseExited();
                        } else if (e.getEventType() == MOUSE_CLICKED) {
                            theGraphics->handler->mouseClicked(e.getX(), e.getY());
                        } else if (e.getEventType() == MOUSE_DOUBLE_CLICKED) {
                            theGraphics->handler->mouseDoubleClicked(e.getX(), e.getY());
                        }
                    }
                } else if (e.getEventClass() == WINDOW_EVENT) {
                    /* 若此事件不属于当前窗口，则忽略它。 */
                    if (e.getSource() == &theGraphics->window) {
                        if (e.getEventType() == WINDOW_MAXIMIZED ||
                            e.getEventType() == WINDOW_RESIZED   ||
                            e.getEventType() == WINDOW_RESTORED) {
                            theGraphics->handler->windowResized();
                        } else if (e.getEventType() == WINDOW_CLOSING && theGraphics->handler->shuttingDown()) {
                            theGraphics->handler.reset();
                            break;
                        }
                    }
                } else if (e.getEventClass() == HYPERLINK_EVENT) {
                    theGraphics->handler->hyperlinkClicked(e.getRequestURL());
                }
            }

            /* TODO：正常窗口关闭流程存在问题，并且
             * 具体含义并不明确。因此改为快速退出，以关闭
             * 在不触发任何对象析构函数的情况下结束程序。所有 GUI 析构函数会
             * 已因 WINDOW_CLOSING 事件触发，因此这里只
             * 不包含线程局部对象和全局析构函数。我所依赖的事实是
             * 不存在我们关心的全局析构函数；即使存在，以下内容
             * 会给它们带来很多问题。
             *
             * htiek@cs.stanford.edu，2021-09-30
             */
            _Exit(0);
        }
    }
}
