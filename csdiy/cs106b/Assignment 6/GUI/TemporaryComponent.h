#ifndef TemporaryComponent_Included
#define TemporaryComponent_Included

#include "gwindow.h"
#include "gobjects.h"
#include <string>

/* 表示生命周期很短的图形对象的类型。该对象
 * 在创建 Temporary 时创建并安装，并且它会
 * 在销毁 Temporary 时移除并释放。
 */
template <typename Component> class Temporary {
public:
    /* 构造函数安装新组件。 */
    Temporary(Component* component, GWindow& window, const std::string& location);

    /* 默认构造函数不执行任何操作。 */
    Temporary() = default;

    /* 析构函数将其移除。 */
    ~Temporary();

    /* 访问底层组件。 */
    Component* get() const;
    Component& operator*  () const;
    Component* operator-> () const;

    /* 释放底层组件。 */
    void release();

    /* 不允许复制。 */
    Temporary(const Temporary &) = delete;

    /* 允许移动。 */
    Temporary(Temporary &&);
    Temporary& operator= (Temporary);

private:
    /* 底层组件、窗口和位置。 */
    Component* component   = nullptr;
    GWindow*   window      = nullptr;
    std::string location;
};

/* 用于创建新 Temporary 的实用函数。 */
template <typename Component, typename... Args>
Temporary<Component> make_temporary(GWindow& window, const std::string& region, Args&&... args) {
    return Temporary<Component>(new Component(std::forward<Args>(args)...), window, region);
}

template <typename Component, typename Pointer>
bool operator== (const Temporary<Component>& lhs, const Pointer* rhs) {
    return lhs.get() == rhs;
}

template <typename Component, typename Pointer>
bool operator!= (const Temporary<Component>& lhs, const Pointer* rhs) {
    return !(lhs == rhs);
}

template <typename Component, typename Pointer>
bool operator== (const Pointer* lhs, const Temporary<Component>& rhs) {
    return rhs == lhs;
}

template <typename Component, typename Pointer>
bool operator!= (const Pointer* lhs, const Temporary<Component>& rhs) {
    return rhs != lhs;
}

/* * * * * 此处以下为实现部分 * * * * */
template <typename Component>
Temporary<Component>::Temporary(Component* component,
                                GWindow& window,
                                const std::string& location)
    : component(component), window(&window), location(location) {
    window.addToRegion(component, location);
}

/* 析构函数移除并释放组件（前提是组件原本存在）。 */
template <typename Component>
Temporary<Component>::~Temporary() {
    release();
}

/* release 将组件从其所属窗口中移除。 */
template <typename Component>
void Temporary<Component>::release() {
    if (component != nullptr) {
        window->removeFromRegion(component, location);
        delete component;

        /* 中心区域比较特殊，因为画布应当放在那里。
         * 若从中间移除了某项，则需要恢复画布。
         */
        if (location == "CENTER") {
            window->addToRegion(window->getCanvas(), "CENTER");
        }
    }
}

/* 访问器直接返回底层组件。 */
template <typename Component>
Component* Temporary<Component>::get() const {
    return component;
}

/* 星号和箭头运算符。 */
template <typename Component>
Component& Temporary<Component>::operator *() const {
    return *component;
}
template <typename Component>
Component* Temporary<Component>::operator->() const {
    return &**this;
}

/* 移动支持。 */
template <typename Component>
Temporary<Component>::Temporary(Temporary&& rhs) {
    /* 交换全部内容。 */
    std::swap(component, rhs.component);
    std::swap(window,    rhs.window);
    std::swap(location,  rhs.location);
}

template <typename Component>
Temporary<Component>& Temporary<Component>::operator= (Temporary rhs) {
    std::swap(component, rhs.component);
    std::swap(window,    rhs.window);
    std::swap(location,  rhs.location);
    return *this;
}

#endif
