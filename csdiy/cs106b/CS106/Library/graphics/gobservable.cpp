/*
 * 文件：gobservable.cpp
 * ---------------------
 *
 * @author Marty Stepp
 * @version 2018/08/23
 * - 重命名为 gobservable.cpp，以替代 Java 版本
 * @version 2018/07/11
 * - 初始版本
 */

#include "gobservable.h"
#include <iostream>
#include <sstream>
#include "geventqueue.h"
#include "gthread.h"
#include "require.h"
#include "strlib.h"

GObservable::GObservable()
        : _eventsEnabled(true) {
    // 空
}

GObservable::~GObservable() {
    // 空
}

void GObservable::clearEventListeners() {
    _eventMap.clear();
}

void GObservable::ensureThreadSafety(const std::string& memberName) {
    GThread::ensureThatThisIsTheQtGuiThread(memberName);
}

bool GObservable::eventsEnabled() const {
    return _eventsEnabled;
}

void GObservable::fireEvent(GEvent& event) {
    if (eventsEnabled()) {
        event.setSource(this);
        if (hasEventListener(event.getName())) {
            _eventMap[event.getName()].fireEvent(event);
        } else {
            // 放入全局队列供 waitForEvent 调用使用
            GEventQueue::instance()->enqueueEvent(event);
        }
    }
}

void GObservable::fireGEvent(QEvent* event,
                             EventType eventType,
                             const std::string& eventName) {
    require::nonNull(event, "GObservable::fireGEvent", "event");
    GEvent generalEvent(
                /* 类  */ MOUSE_EVENT,
                /* 类型   */ eventType,
                /* 名称   */ eventName,
                /* 来源 */ this);
    generalEvent.setInternalEvent(event);
    fireEvent(generalEvent);
}

void GObservable::fireGEvent(QCloseEvent* event,
                             EventType eventType,
                             const std::string& eventName) {
    require::nonNull(event, "GObservable::fireGEvent", "event");
    GEvent windowEvent(
                /* 类  */ WINDOW_EVENT,
                /* 类型   */ eventType,
                /* 名称   */ eventName,
                /* 来源 */ this);
    windowEvent.setInternalEvent(event);
    fireEvent(windowEvent);
}

void GObservable::fireGEvent(QKeyEvent* event,
                             EventType eventType,
                             const std::string& eventName) {
    require::nonNull(event, "GObservable::fireGEvent", "event");
    GEvent keyEvent(
                /* 类  */ KEY_EVENT,
                /* 类型   */ eventType,
                /* 名称   */ eventName,
                /* 来源 */ this);
    keyEvent.setKeyCode(event->key());
    std::string text = event->text().toStdString();
    if (!text.empty()) {
        keyEvent.setKeyChar(text);
    } else {
        // int keyChar = event->key() & 0x0000ffff & ~Qt::KeyboardModifierMask;
        // keyEvent.setKeyChar((char) keyChar);
    }
    keyEvent.setModifiers(event->modifiers());
    keyEvent.setInternalEvent(event);
    fireEvent(keyEvent);
}

void GObservable::fireGEvent(QMouseEvent* event,
                             EventType eventType,
                             const std::string& eventName,
                             const std::string& actionCommand) {
    require::nonNull(event, "GObservable::fireGEvent", "event");
    GEvent mouseEvent(
                /* 类  */ MOUSE_EVENT,
                /* 类型   */ eventType,
                /* 名称   */ eventName,
                /* 来源 */ this);
    mouseEvent.setButton((int) event->button());
    mouseEvent.setX(event->pos().x());
    mouseEvent.setY(event->pos().y());
    mouseEvent.setModifiers(event->modifiers());
    mouseEvent.setActionCommand(actionCommand);
    mouseEvent.setInternalEvent(event);
    fireEvent(mouseEvent);
}

void GObservable::fireGEvent(QResizeEvent* event,
                             EventType /* eventType */,
                             const std::string& eventName) {
    require::nonNull(event, "GObservable::fireGEvent", "event");
    GEvent windowEvent(
                /* 类  */ WINDOW_EVENT,
                /* 类型   */ WINDOW_RESIZED,
                /* 名称   */ eventName,
                /* 来源 */ this);
    windowEvent.setInternalEvent(event);
    fireEvent(windowEvent);
}

void GObservable::fireGEvent(QTimerEvent* event,
                             EventType /* eventType */,
                             const std::string& /* eventName */) {
    require::nonNull(event, "GObservable::fireGEvent", "event");
    GEvent timerEvent(
                /* 类  */ TIMER_EVENT,
                /* 类型   */ TIMER_TICKED,
                /* 名称   */ "timer",
                /* 来源 */ this);
    timerEvent.setInternalEvent(event);
    fireEvent(timerEvent);
}

void GObservable::fireGEvent(QWheelEvent* event,
                             EventType eventType,
                             const std::string& eventName) {
    require::nonNull(event, "GObservable::fireGEvent", "event");
    GEvent wheelEvent(
                /* 类  */ MOUSE_EVENT,
                /* 类型   */ eventType,
                /* 名称   */ eventName,
                /* 来源 */ this);
    wheelEvent.setButton((int) event->buttons());
    wheelEvent.setX(event->position().x());
    wheelEvent.setY(event->position().y());
    wheelEvent.setModifiers(event->modifiers());
    wheelEvent.setInternalEvent(event);
    fireEvent(wheelEvent);
}

void GObservable::fireGEvent(QWindowStateChangeEvent* event,
                             EventType eventType,
                             const std::string& eventName) {
    require::nonNull(event, "GObservable::fireGEvent", "event");
    GEvent windowEvent(
                /* 类  */ WINDOW_EVENT,
                /* 类型   */ eventType,
                /* 名称   */ eventName,
                /* 来源 */ this);
    windowEvent.setInternalEvent(event);
    fireEvent(windowEvent);
}

bool GObservable::isAcceptingEvent(const std::string& eventType) const {
    if (hasEventListener(eventType)) {
        return true;
    }
    int eventMask = ANY_EVENT;
    if (startsWith(eventType, "action")) {
        eventMask = ACTION_EVENT;
    } else if (startsWith(eventType, "change")) {
        eventMask = CHANGE_EVENT;
    } else if (startsWith(eventType, "key")) {
        eventMask = KEY_EVENT;
    } else if (startsWith(eventType, "mouse")) {
        eventMask = MOUSE_EVENT;
    } else if (startsWith(eventType, "server")) {
        eventMask = SERVER_EVENT;
    } else if (startsWith(eventType, "table")) {
        eventMask = TABLE_EVENT;
    } else if (startsWith(eventType, "timer")) {
        eventMask = TIMER_EVENT;
    } else if (startsWith(eventType, "window")) {
        eventMask = WINDOW_EVENT;
    }
    return isAcceptingEvent(eventMask);
}

bool GObservable::isAcceptingEvent(const GEvent& event) const {
    return isAcceptingEvent(event.getName());
}

bool GObservable::hasEventListener(const std::string& eventName) const {
    return _eventMap.containsKey(eventName);
}

bool GObservable::isAcceptingEvent(int eventMask) const {
    return GEventQueue::instance()->isAcceptingEvent(eventMask);
}

void GObservable::removeEventListener(const std::string& eventName) {
    _eventMap.remove(eventName);
}

void GObservable::removeEventListeners(std::initializer_list<std::string> eventNames) {
    for (std::string eventName : eventNames) {
        removeEventListener(eventName);
    }
}

void GObservable::setEventListener(const std::string& eventName, GEventListener func) {
    GEvent::EventListenerWrapper wrapper;
    wrapper.type = GEvent::HANDLER_EVENT;
    wrapper.handler = func;
    _eventMap[eventName] = wrapper;
}

void GObservable::setEventListener(const std::string& eventName, GEventListenerVoid func) {
    GEvent::EventListenerWrapper wrapper;
    wrapper.type = GEvent::HANDLER_VOID;
    wrapper.handlerVoid = func;
    _eventMap[eventName] = wrapper;
}

void GObservable::setEventListeners(std::initializer_list<std::string> eventNames, GEventListener func) {
    for (std::string eventName : eventNames) {
        setEventListener(eventName, func);
    }
}

void GObservable::setEventListeners(std::initializer_list<std::string> eventNames, GEventListenerVoid func) {
    for (std::string eventName : eventNames) {
        setEventListener(eventName, func);
    }
}

void GObservable::setEventsEnabled(bool eventsEnabled) {
    _eventsEnabled = eventsEnabled;
}

std::string GObservable::toString() const {
    std::ostringstream out;
    out << getType() << "@" << this;
    return out.str();
}
