/*
 * 文件：geventqueue.h
 * -------------------
 *
 * @author Marty Stepp
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 geventqueue.h
 * @version 2018/07/03
 * - 初始版本
 */


#ifndef _geventqueue_h
#define _geventqueue_h

#include <string>
#include <QObject>
#include <QReadWriteLock>

#include "gevent.h"
#include "gtypes.h"
#include "queue.h"

class GObservable;
class GThread;
class QtGui;

/**
 * GEventQueue 是一个先进先出（FIFO）的事件队列，其中存放发生的事件
 * 在图形交互控件上。
 *
 * 我们的交互控件类（GButton、GCheckBox 等）使用此队列
 * 在内部。当这些控件上发生事件时，我们会将其放入 GEventQueue
 * 以便将它们发送给客户端代码中的各个事件监听器。
 *
 * 大多数客户端无需直接使用 GEventQueue。
 *
 * @private
 */
class GEventQueue : public QObject {
    Q_OBJECT

public:
    /**
     * 返回事件队列的唯一实例。
     * 如果尚不存在实例，则创建一个。
     * @return 返回值
     */
    static GEventQueue* instance();

    /**
     * 返回半弃用全局函数当前使用的事件掩码
     * waitForEvent 等事件处理函数。
     */
    int getEventMask() const;

    /**
     * 返回下一个与给定掩码匹配的事件
     * 事件类型。
     */
    GEvent getNextEvent(int mask = ANY_EVENT);

    /**
     * 如果给定事件会被当前设置接受，则返回 true
     * 事件掩码，参见 setEventMask。
     */
    bool isAcceptingEvent(const GEvent& event) const;
    bool isAcceptingEvent(int type) const;

    /**
     * 设置要监听的事件类型位标志掩码
     * 用于 waitForEvent 等半弃用的全局事件处理函数。
     * 如果尚未调用 setEventMask，则接受所有事件。
     */
    void setEventMask(int mask);

    /**
     * 暂停当前线程，直到发生匹配给定条件的事件
     * 带位标志的掩码。随后返回该事件。
     * 当前事件掩码也设置为给定掩码，就像
     * 已调用 setEventMask。
     */
    GEvent waitForEvent(int mask = ANY_EVENT);

signals:
    /**
     * 当队列中存在可处理事件时触发。
     */
    void eventReady();

private:
    Q_DISABLE_COPY(GEventQueue)

    /*
     * 禁止构造。请改用 instance()。
     */
    GEventQueue();

    GThunk dequeue();
    void enqueueEvent(const GEvent& event);
    bool isEmpty() const;
    GThunk peek();
    void runOnQtGuiThreadAsync(GThunk thunk);
    void runOnQtGuiThreadSync(GThunk thunk);

    static GEventQueue* _instance;
    Queue<GThunk> _functionQueue;
    Queue<GEvent> _eventQueue;
    QReadWriteLock _eventQueueMutex;
    QReadWriteLock _functionQueueMutex;
    int _eventMask;

    friend class GObservable;
    friend class GThread;
    friend class QtGui;
};

#endif // _geventqueue_h
