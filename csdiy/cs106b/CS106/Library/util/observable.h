/*
 * 文件：observable.h
 * ------------------
 * 此文件定义名为 <code>Observable</code> 的抽象超类，该类
 * 允许对象存储观察者列表；观察者是其他对象，它们
 * 当可观察对象状态的某部分发生变化时收到通知。
 * 这是经典观察者/可观察对象设计模式的一个示例。
 *
 * @author Marty Stepp
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 * @version 2017/10/25
 * - 添加接受引用参数的 addObserver/removeObserver 重载
 * @version 2016/11/20
 * - 重构以使用事件类型模板
 * @version 2014/10/08
 * - 移除“using namespace”语句
 * - 修复 removeObserver 的错误字符串（原先写成“addObserver”）
 * @version 2014/03/09
 * - 初始版本
 */


#ifndef _observable_h
#define _observable_h

#include <set>

#include "error.h"

// 前向声明
template <class T>
class Observer;

/**
 * 此抽象超类允许对象存储观察者列表，
 * 即希望在对象的某部分
 * 可观察对象的状态发生变化。
 *
 * 预期用法是，在你希望
 * 希望被观察，然后在其代码中的适当位置调用 notifyObservers
 * 位置。然后创建另一个继承 Observer 并定义以下内容的对象
 * update 方法，并将其附加到 Observable，以便接收通知。
 */
template <typename T>
class Observable {
public:
    /**
     * 将给定观察者对象添加到此可观察对象的内部列表
     * 观察者的数量。调用以下内容时会调用观察者的 update 方法：
     * 随后会调用 notifyObservers 方法。
     * 前置条件：obs != nullptr
     */
    void addObserver(Observer<T>* obs);

    /**
     * 将给定观察者对象添加到此可观察对象的内部列表
     * 观察者的数量。调用以下内容时会调用观察者的 update 方法：
     * 随后会调用 notifyObservers 方法。
     */
    void addObserver(Observer<T>& obs);

    /**
     * 调用之前添加的所有观察者的 update 方法
     * 添加到此可观察对象。
     * 可以传入给定参数，以便向
     * 必要时通知观察者。如果未传入参数，则使用 nullptr。
     */
    void notifyObservers(T arg = T());

    /**
     * 从此可观察对象的内部列表中移除给定观察者对象
     * 观察者列表。该观察者将不再收到通知。
     */
    void removeObserver(Observer<T>* obs);

    /**
     * 从此可观察对象的内部列表中移除给定观察者对象
     * 观察者列表。该观察者将不再收到通知。
     */
    void removeObserver(Observer<T>& obs);

private:
    // 调用 notifyObservers 时要通知的观察者列表
    std::set<Observer<T>*> m_observers;
};

/**
 * 希望在可观察对象状态变化时收到通知的对象
 * 更改。
 */
template <typename T>
class Observer {
public:
    /**
     * 由 Observable 调用，以通知此观察者其状态已变化。
     * 'obs' 参数是指向可观察对象本身的指针
     * 状态变化发生的位置。'arg' 参数将
     * Observable 调用以下方法时传递的额外信息
     * notifyObservers（如果有）。
     */
    virtual void update(Observable<T>* obs, const T& arg = T()) = 0;
};

template <typename T>
void Observable<T>::addObserver(Observer<T>* obs) {
    if (!obs) {
        error("Observable::addObserver: null observer passed");
    }
    m_observers.insert(obs);
}

template <typename T>
void Observable<T>::addObserver(Observer<T>& obs) {
    addObserver(&obs);
}

template <typename T>
void Observable<T>::notifyObservers(T arg) {
    for (Observer<T>* obs : m_observers) {
        obs->update(this, arg);
    }
}

template <typename T>
void Observable<T>::removeObserver(Observer<T>* obs) {
    if (!obs) {
        error("Observable::removeObserver: null observer passed");
    }
    m_observers.erase(obs);
}

template <typename T>
void Observable<T>::removeObserver(Observer<T>& obs) {
    removeObserver(&obs);
}

#endif // _observable_h
