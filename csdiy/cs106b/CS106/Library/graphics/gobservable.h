/*
 * 文件：gobservable.h
 * --------------------
 *
 * @author Marty Stepp
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gobservable.h，以替代 Java 版本
 * @version 2018/07/11
 * - 初始版本
 */


#ifndef _gobservable_h
#define _gobservable_h

#include <functional>
#include <string>
#include <QtEvents>

#include "gevent.h"
#include "map.h"

class GInteractor;
class _Internal_QWidget;

/**
 * GObservable 对象能够发送事件。
 * 监听器可以注册，以便在事件发生时收到通知。
 * 它作为各种 GInteractor 子类以及
 * 与 GWindow 类类似，以便客户端可以向其附加监听器。
 */
class GObservable {
public:
    /**
     * 初始化新创建的可观察对象。
     */
    GObservable();

    /**
     * 释放可观察对象内部使用的任何内存。
     */
    virtual ~GObservable();

    /**
     * 如果对象当前允许自身触发事件，则返回 true。
     * 初始为 true，除非客户端已调用
     * 调用 <code>setEventsEnabled(false)</code>，或对象不可见。
     */
    virtual bool eventsEnabled() const;

    /**
     * 以字符串返回对象的具体类型，例如
     * <code>"GButton"</code> 或 <code>"GWindow"</code>。
     * 每个 GObservable 子类型都必须重写此方法。
     */
    virtual std::string getType() const = 0;

    /**
     * 设置对象当前是否允许自身触发事件。
     * 初始为 true。
     */
    virtual void setEventsEnabled(bool eventsEnabled);

    /**
     * 返回此可观察对象状态的字符串表示。
     * 主要用于调试。
     */
    virtual std::string toString() const;

protected:
    /**
     * 从此对象中删除所有事件监听器。
     */
    virtual void clearEventListeners();

    /**
     * 确保当前位于 Qt GUI 线程。
     */
    virtual void ensureThreadSafety(const std::string& memberName = "");

    /**
     * 将给定事件发送给所有附加的监听器。
     */
    virtual void fireEvent(GEvent& event);

    /**
     * 创建给定类型的事件，然后将其发送给所有
     * 已连接的监听器。
     */
    virtual void fireGEvent(QEvent* event, EventType eventType, const std::string& eventName);

    /**
     * 创建给定类型的事件，然后将其发送给所有
     * 已连接的监听器。
     */
    virtual void fireGEvent(QCloseEvent* event, EventType eventType, const std::string& eventName);

    /**
     * 创建给定类型的事件，然后将其发送给所有
     * 已连接的监听器。
     */
    virtual void fireGEvent(QKeyEvent* event, EventType eventType, const std::string& eventName);

    /**
     * 创建给定类型的事件，然后将其发送给所有
     * 已连接的监听器。
     */
    virtual void fireGEvent(QMouseEvent* event, EventType eventType, const std::string& eventName, const std::string& actionCommand = "");

    /**
     * 创建给定类型的事件，然后将其发送给所有
     * 已连接的监听器。
     */
    virtual void fireGEvent(QResizeEvent* event, EventType eventType, const std::string& eventName);

    /**
     * 创建给定类型的事件，然后将其发送给所有
     * 已连接的监听器。
     */
    virtual void fireGEvent(QTimerEvent* event, EventType eventType, const std::string& eventName);

    /**
     * 创建给定类型的事件，然后将其发送给所有
     * 已连接的监听器。
     */
    virtual void fireGEvent(QWheelEvent* event, EventType eventType, const std::string& eventName);

    /**
     * 创建给定类型的事件，然后将其发送给所有
     * 已连接的监听器。
     */
    virtual void fireGEvent(QWindowStateChangeEvent* event, EventType eventType, const std::string& eventName);

    /**
     * 若可观察对象具有给定事件类型的监听器，则返回 true
     * 事件的
     */
    virtual bool hasEventListener(const std::string& eventName) const;

    /**
     * 若可观察对象具有给定事件类型的监听器，则返回 true
     * 事件的
     * 有关事件类型和掩码，请参阅 gevent.h。
     */
    virtual bool isAcceptingEvent(int eventMask) const;

    /**
     * 若可观察对象具有给定事件类型的监听器，则返回 true
     * 事件的
     */
    virtual bool isAcceptingEvent(const GEvent& event) const;

    /**
     * 若可观察对象具有给定事件类型的监听器，则返回 true
     * 事件的
     */
    virtual bool isAcceptingEvent(const std::string& eventType) const;

    /**
     * 从此可观察对象中移除所有会响应的事件监听器
     * 响应给定类型的事件，例如“click”或“keydown”。
     */
    virtual void removeEventListener(const std::string& eventName);

    /**
     * 从此可观察对象中移除所有会响应的事件监听器
     * 响应给定的多种事件类型，例如“click”或“keydown”。
     */
    virtual void removeEventListeners(std::initializer_list<std::string> eventNames);

    /**
     * 为此可观察对象添加事件监听器，以响应
     * 响应给定类型的事件，例如“click”或“keydown”。
     * 此前该事件类型的监听器会被替换。
     */
    virtual void setEventListener(const std::string& eventName, GEventListener func);

    /**
     * 为此可观察对象添加事件监听器，以响应
     * 响应给定类型的事件，例如“click”或“keydown”。
     * 此前该事件类型的监听器会被替换。
     */
    virtual void setEventListener(const std::string& eventName, GEventListenerVoid func);

    /**
     * 为此可观察对象添加事件监听器，以响应
     * 响应给定的多种事件类型，例如“click”或“keydown”。
     * 此前这些事件类型的监听器会被替换。
     */
    virtual void setEventListeners(std::initializer_list<std::string> eventNames, GEventListener func);

    /**
     * 为此可观察对象添加事件监听器，以响应
     * 响应给定的多种事件类型，例如“click”或“keydown”。
     * 此前这些事件类型的监听器会被替换。
     */
    virtual void setEventListeners(std::initializer_list<std::string> eventNames, GEventListenerVoid func);

private:
    Map<std::string, GEvent::EventListenerWrapper> _eventMap;
    bool _eventsEnabled;

    // 允许所有交互控件及其内部 QWidget 调用可观察对象方法
    friend class GInteractor;
    friend class _Internal_QWidget;
};

#endif // _gobservable_h
