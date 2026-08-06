/*
 * 文件：gevent.h
 * --------------
 *
 * @author Marty Stepp
 * @version 2018/09/20
 * - 暂时移除 waitForEvent/Click 全局函数的弃用警告
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gevent.h，以替代 Java 版本
 * @version 2018/07/06
 * - 初始版本
 */


#ifndef _gevent_h
#define _gevent_h

#include <functional>
#include <iostream>
#include <string>

#include "gtypes.h"

class QEvent;
class GEvent;
class GInteractor;
class GObservable;
class _Internal_QCanvas;
class _Internal_QCheckBox;
class _Internal_QPushButton;
class _Internal_QWidget;

/** 传递给各种交互控件的事件监听器函数类型。 */
typedef std::function<void(GEvent)> GEventListener;

/** 传递给各种交互控件的事件监听器函数类型。 */
typedef std::function<void()>       GEventListenerVoid;

/**
 * 表示所有主要事件类别。
 */
enum EventClass {
    NULL_EVENT      = 0x0000,
    ACTION_EVENT    = 0x0010,
    KEY_EVENT       = 0x0020,
    TIMER_EVENT     = 0x0040,
    WINDOW_EVENT    = 0x0080,
    MOUSE_EVENT     = 0x0100,
    CLICK_EVENT     = 0x0200,
    TABLE_EVENT     = 0x0400,
    SERVER_EVENT    = 0x0800,
    CHANGE_EVENT    = 0x1000,
    HYPERLINK_EVENT = 0x2000,
    SCROLL_EVENT    = 0x4000,
    ANY_EVENT       = ACTION_EVENT | KEY_EVENT | TIMER_EVENT | WINDOW_EVENT
                    | MOUSE_EVENT | CLICK_EVENT | TABLE_EVENT | SERVER_EVENT
                    | CHANGE_EVENT | HYPERLINK_EVENT | SCROLL_EVENT
};
// 注意：如果添加任何新的事件类，还必须向以下位置添加逻辑：
// gevent.cpp 中的 GEvent::classToString 函数。


/**
 * 定义所有事件的事件子类型。
 * 事件类型是事件类中的一个子类别。
 */
enum EventType {
    NULL_TYPE            = 0,

    WINDOW_CLOSED        = WINDOW_EVENT + 1,
    WINDOW_RESIZED       = WINDOW_EVENT + 2,
    CONSOLE_CLOSED       = WINDOW_EVENT + 3,
    WINDOW_CLOSING       = WINDOW_EVENT + 4,
    WINDOW_MINIMIZED     = WINDOW_EVENT + 5,
    WINDOW_RESTORED      = WINDOW_EVENT + 6,
    WINDOW_MAXIMIZED     = WINDOW_EVENT + 7,

    ACTION_PERFORMED     = ACTION_EVENT + 1,
    ACTION_MENU          = ACTION_EVENT + 2,

    MOUSE_CLICKED        = MOUSE_EVENT + 1,
    MOUSE_PRESSED        = MOUSE_EVENT + 2,
    MOUSE_RELEASED       = MOUSE_EVENT + 3,
    MOUSE_MOVED          = MOUSE_EVENT + 4,
    MOUSE_DRAGGED        = MOUSE_EVENT + 5,
    MOUSE_ENTERED        = MOUSE_EVENT + 6,
    MOUSE_EXITED         = MOUSE_EVENT + 7,
    MOUSE_WHEEL_DOWN     = MOUSE_EVENT + 8,
    MOUSE_WHEEL_UP       = MOUSE_EVENT + 9,
    MOUSE_DOUBLE_CLICKED = MOUSE_EVENT + 10,

    KEY_PRESSED          = KEY_EVENT + 1,
    KEY_RELEASED         = KEY_EVENT + 2,
    KEY_TYPED            = KEY_EVENT + 3,

    TIMER_TICKED         = TIMER_EVENT + 1,

    TABLE_UPDATED        = TABLE_EVENT + 1,   // 当单元格的值被设置时
    TABLE_SELECTED       = TABLE_EVENT + 2,   // 光标移动到某个单元格上
    TABLE_EDIT_BEGIN     = TABLE_EVENT + 3,   // 用户按 F2 或双击开始编辑单元格
    TABLE_REPLACE_BEGIN  = TABLE_EVENT + 4,   // 用户开始在单元格中输入；类似 TABLE_EDIT_BEGIN，但会清除原值
    TABLE_EDIT_CANCEL    = TABLE_EVENT + 5,   // 用户按 Esc 或以其他方式停止编辑单元格
    TABLE_CUT            = TABLE_EVENT + 6,   // 用户将单元格值剪切到剪贴板
    TABLE_COPY           = TABLE_EVENT + 7,   // 用户将单元格值复制到剪贴板
    TABLE_PASTE          = TABLE_EVENT + 8,   // 用户从剪贴板粘贴单元格值

    SERVER_REQUEST       = SERVER_EVENT + 1,

    STATE_CHANGED        = CHANGE_EVENT + 1,

    HYPERLINK_CLICKED    = HYPERLINK_EVENT + 1,

    SCROLL_SCROLLED      = SCROLL_EVENT + 1
};
// 注意：如果添加任何新的事件类，还必须向以下位置添加逻辑：
// gevent.cpp 中的 GEvent::typeToString 函数。

/**
 * 一组常量，用于检查各种事件修饰键是否生效。
 * 这些常量可以使用位运算符合并到一个修饰符 int 中。
 */
enum Modifier {
    SHIFT_DOWN     = 1 << 0,
    CTRL_DOWN      = 1 << 1,
    META_DOWN      = 1 << 2,
    ALT_DOWN       = 1 << 3,
    ALT_GRAPH_DOWN = 1 << 4,
    BUTTON1_DOWN   = 1 << 5,
    BUTTON2_DOWN   = 1 << 6,
    BUTTON3_DOWN   = 1 << 7
};

/**
 * GEvent 表示在图形交互控件上发生的用户操作。
 *
 * 此库的旧版本使用事件轮询模型，客户端会
 * 建议编写 while (true) 循环并调用 waitForEvent(...) 来
 * 获取每个事件并处理它。
 * 当前设计更倾向于附加事件监听器函数
 * 在事件发生时调用。
 * 这些监听器函数可以接受一个可选的 GEvent 参数。
 * GEvent 对象将包含有关已发生事件的信息。
 *
 * 此库的旧版本针对各种类型使用继承层次结构
 * 事件类型，例如 GMouseEvent、GKeyEvent 等。
 * 当前设计使用单一 GEvent 类型，它是所有数据的联合
 * 任何类型的事件都需要。
 * 此前的子类名称（如 GMouseEvent）为保持向后
 * 用于兼容性，但它们现在只是 GEvent 类型的别名。
 */
class GEvent {
public:
    /**
     * 一个什么也不做、可传入的空事件处理程序。
     */
    static GEventListener EMPTY_EVENT_LISTENER;

    /**
     * 仅打印所发生事件的事件监听器。
     * 此监听器有助于调试。
     */
    static GEventListener LOG_EVENT;

    /*
     * 类型：KeyCode
     * -------------
     * 此类型定义按键事件中返回的键码名称。
     */
    enum KeyCode {
        BACKSPACE_KEY = 8,
        TAB_KEY = 9,
        ENTER_KEY = 10,
        CLEAR_KEY = 12,
        RETURN_KEY = 13,
        SHIFT_KEY = Qt::Key_Shift,
        CTRL_KEY = Qt::Key_Control,
        ALT_KEY = Qt::Key_Alt,
        PAUSE_KEY = 19,
        CAPS_LOCK_KEY = 20,
        ESCAPE_KEY = 27,
        PAGE_UP_KEY = Qt::Key_PageUp,
        PAGE_DOWN_KEY = Qt::Key_PageDown,
        END_KEY = Qt::Key_End,
        HOME_KEY = Qt::Key_Home,
        LEFT_ARROW_KEY = Qt::Key_Left,
        UP_ARROW_KEY = Qt::Key_Up,
        RIGHT_ARROW_KEY = Qt::Key_Right,
        DOWN_ARROW_KEY = Qt::Key_Down,
        F1_KEY = Qt::Key_F1,
        F2_KEY = Qt::Key_F2,
        F3_KEY = Qt::Key_F3,
        F4_KEY = Qt::Key_F4,
        F5_KEY = Qt::Key_F5,
        F6_KEY = Qt::Key_F6,
        F7_KEY = Qt::Key_F7,
        F8_KEY = Qt::Key_F8,
        F9_KEY = Qt::Key_F9,
        F10_KEY = Qt::Key_F10,
        F11_KEY = Qt::Key_F11,
        F12_KEY = Qt::Key_F12,
        DELETE_KEY = 127,
        NUM_LOCK_KEY = Qt::Key_NumLock,
        SCROLL_LOCK_KEY = Qt::Key_ScrollLock,
        PRINT_SCREEN_KEY = Qt::Key_Print,
        INSERT_KEY = Qt::Key_Insert,
        HELP_KEY = Qt::Key_Help,
        META_KEY = Qt::Key_Meta,
        WINDOWS_KEY = Qt::Key_Super_L,
        MENU_KEY = Qt::Key_Menu
    };

    /**
     * 创建给定类型的新事件。
     */
    GEvent(EventClass eventClass = NULL_EVENT,
            EventType eventType = NULL_TYPE,
            const std::string& eventName = "",
            GObservable* source = nullptr);

    /**
     * 释放事件内部分配的内存。
     */
    virtual ~GEvent();

    /**
     * 将 ACTION_PERFORMED 等事件类转换为
     * 转换为类似 "ACTION_PERFORMED" 的字符串。
     * @private
     */
    static std::string classToString(EventClass eventClass);

    /**
     * 返回与事件关联的动作命令。
     * 对于按钮等某些交互控件，这将是以下对象的文本：
     * 交互控件。
     */
    virtual std::string getActionCommand() const;

    /**
     * 如果这是鼠标事件，则返回点击的鼠标按钮。
     * 若这不是鼠标事件，则返回 0。
     */
    virtual int getButton() const;

    /**
     * 返回此事件的类（例如 MOUSE_EVENT 这样的主要类型）。
     * 等价于 getEventClass。
     */
    virtual EventClass getClass() const;

    /**
     * 如果这是表格事件，则返回发生交互的列。
     * 若这不是表格事件，则返回 0。
     */
    virtual int getColumn() const;

    /**
     * 返回从以下时刻起经过的毫秒数所表示的当前时间
     * 1970/01/01 12:00am 纪元。
     * 用于为各个事件提供时间戳。
     * @private
     */
    static long getCurrentTimeMS();

    /**
     * 返回此事件的类（例如 MOUSE_EVENT 这样的主要类型）。
     * 等价于 getClass。
     */
    virtual EventClass getEventClass() const;

    /**
     * 返回事件类型（次要类型，例如 MOUSE_PRESSED）。
     * 等价于 getType。
     */
    virtual EventType getEventType() const;

    /**
     * 返回生成此事件的源交互控件。
     */
    virtual GInteractor* getInteractor() const;

    /**
     * 返回此事件所包装的 Qt 事件（如果有）。
     * 如果此事件未包装 Qt 事件，则返回 nullptr。
     */
    virtual QEvent* getInternalEvent() const;

    /**
     * 如果这是键盘事件，则返回输入的键盘字符。
     * 如果这不是键盘事件，则返回 '\0'。
     */
    virtual char getKeyChar() const;

    /**
     * 如果这是键盘事件，则返回输入的整数键码。
     * 用于比较键值的有用常量见 KeyCode 枚举。
     * 如果这不是键盘事件，则返回 0。
     */
    virtual int getKeyCode() const;

    /**
     * 返回表示交互控件内鼠标位置的 (x, y) 点
     * 此事件发生的时间。
     * 如果这不是鼠标事件，则返回 (0, 0)。
     */
    virtual GPoint getLocation() const;

    /**
     * 返回此事件期间激活的修饰键。
     * 更多信息见 Modifiers 枚举。
     */
    virtual int getModifiers() const;

    /**
     * 返回此事件的名称，例如 "click"、"keydown" 或 "actionperformed"。
     */
    virtual std::string getName() const;

    /**
     * 如果这是服务器 URL 事件，则返回此事件的请求 URL。
     * 如果这不是服务器 URL 事件，则返回空字符串。
     */
    virtual std::string getRequestURL() const;

    /**
     * 如果这是表格事件，则返回发生交互的行。
     * 若这不是表格事件，则返回 0。
     */
    virtual int getRow() const;

    /**
     * 返回生成此事件的源对象。
     */
    virtual GObservable* getSource() const;

    /**
     * 返回此事件的时间戳，以从以下时刻起经过的毫秒数表示
     * 自 1970/01/01 12:00am 纪元以来。
     */
    virtual long getTime() const;

    /**
     * 返回事件类型（主要类型，例如 MOUSE_EVENT）。
     * 等价于 getEventType。
     */
    virtual EventType getType() const;

    /**
     * 返回交互控件内鼠标位置的 x 坐标
     * 此事件发生的时间。
     * 若这不是鼠标事件，则返回 0。
     */
    virtual double getX() const;

    /**
     * 返回交互控件内鼠标位置的 y 坐标
     * 此事件发生的时间。
     * 若这不是鼠标事件，则返回 0。
     */
    virtual double getY() const;

    /**
     * 指示 GUI 系统忽略或取消此事件。
     * 例如，如果监听窗口关闭事件并忽略它们，
     * 窗口将保持打开状态。
     */
    virtual void ignore();

    /**
     * 如果此事件发生时按住 Alt 键，则返回 <code>true</code>。
     * 若这不是鼠标事件或按键事件，则返回 false。
     */
    virtual bool isAltKeyDown() const;

    /**
     * 如果此事件发生时按住 Ctrl 键，则返回 <code>true</code>。
     * 若这不是鼠标事件或按键事件，则返回 false。
     */
    virtual bool isCtrlKeyDown() const;

    /**
     * 如果按住 Ctrl 键或 Command 键（Mac），则返回 <code>true</code>
     * 在此事件期间被按住。
     * 若这不是鼠标事件或按键事件，则返回 false。
     */
    virtual bool isCtrlOrCommandKeyDown() const;

    /**
     * 如果用户多次按下鼠标按钮，则返回 true。
     * 若这不是鼠标事件，则返回 false。
     */
    virtual bool isDoubleClick() const;

    /**
     * 如果用户按下鼠标左键，则返回 true。
     * 若这不是鼠标事件，则返回 false。
     */
    virtual bool isLeftClick() const;

    /**
     * 如果用户按下鼠标中键，则返回 true。
     * （请注意，并非每个鼠标都能简单划分为“左键、右键、
     * 以及“中键”按钮；这是在标准三键鼠标上实现的
     * 使用滚轮。）
     * 若这不是鼠标事件，则返回 false。
     */
    virtual bool isMiddleClick() const;

    /**
     * 如果用户按下鼠标右键，则返回 true。
     * 若这不是鼠标事件，则返回 false。
     */
    virtual bool isRightClick() const;

    /**
     * 如果此事件发生时按住 Meta/Command 键，则返回 <code>true</code>。
     * 若这不是鼠标事件或按键事件，则返回 false。
     */
    virtual bool isMetaKeyDown() const;

    /**
     * 如果此事件发生时按住 Shift 键，则返回 <code>true</code>。
     * 若这不是鼠标事件或按键事件，则返回 false。
     */
    virtual bool isShiftKeyDown() const;

    /**
     * 将 67 这样的键码转换为“A”这样的字符串。
     * 适用于“Enter”和“Tab”等特殊键。
     */
    static std::string keyCodeToString(int keyCode);

    /**
     * @private
     */
    virtual void setActionCommand(const std::string& actionCommand);

    /**
     * @private
     */
    virtual void setButton(int button);

    /**
     * @private
     */
    virtual void setInternalEvent(QEvent* event);

    /**
     * @private
     */
    virtual void setKeyChar(char keyChar);

    /**
     * @private
     */
    virtual void setKeyChar(const std::string& keyCharString);

    /**
     * @private
     */
    virtual void setKeyCode(int keyCode);

    /**
     * @private
     */
    virtual void setModifiers(Qt::KeyboardModifiers modifiers);

    /**
     * @private
     */
    virtual void setRequestURL(const std::string& requestUrl);

    /**
     * @private
     */
    virtual void setRowAndColumn(int row, int col);

    /**
     * @private
     */
    virtual void setSource(GObservable* source);

    /**
     * @private
     */
    virtual void setX(double x);

    /**
     * @private
     */
    virtual void setY(double y);

    /**
     * 返回用于调试的事件文本表示。
     */
    virtual std::string toString() const;

    /**
     * 将 MOUSE_EVENT 等事件类型转换为以下字符串：
     * “MOUSE_EVENT”。
     */
    static std::string typeToString(EventType eventType);

private:
    /*
     * 表示两种事件监听器。
     */
    enum EventListenerType {
        HANDLER_EVENT,
        HANDLER_VOID
    };

    /*
     * 可保存两种事件监听器类型之一的包装器。
     */
    struct EventListenerWrapper {
        GEventListener handler;
        GEventListenerVoid handlerVoid;
        EventListenerType type;

        void fireEvent(const GEvent& event) {
            if (type == HANDLER_EVENT) {
                handler(event);
            } else {
                handlerVoid();
            }
        }
    };

    // 成员变量
    std::string _actionCommand;
    int _button;
    EventClass _class;
    char _keyChar;
    int _keyCode;
    int _modifiers;
    std::string _name;
    std::string _requestUrl;
    GObservable* _source;
    long _time;
    EventType _type;
    double _x;
    double _y;
    int _row;
    int _col;
    QEvent* _internalQtEvent;

    friend class GInteractor;
    friend class GObservable;
    friend class _Internal_QWidget;
};

/**
 * 将给定事件写入给定输出流。
 */
std::ostream& operator <<(std::ostream& out, const GEvent& event);

// 将 GEvent 作为所有事件类型的别名
typedef GEvent GActionEvent;
typedef GEvent GChangeEvent;
typedef GEvent GHyperlinkEvent;
typedef GEvent GKeyEvent;
typedef GEvent GMouseEvent;
typedef GEvent GScrollEvent;
typedef GEvent GServerEvent;
typedef GEvent GTableEvent;
typedef GEvent GTimerEvent;
typedef GEvent GWindowEvent;

// 用于向后兼容的全局函数
// 实现见 geventqueue.cpp

/**
 * 检查队列中是否存在所需类型的事件
 * 事件队列。如果存在，此函数会以完全相同的形式返回事件
 * 方式与 <code>waitForEvent</code> 相同；如果没有，<code>getNextEvent</code>
 * 返回无效事件。<code>mask</code> 参数是可选的。
 * 如果缺少它，<code>getNextEvent</code> 将接受任何事件。
 *
 * @deprecated 已弃用
 * 此函数已弃用，不建议使用。
 * 不要在事件循环中调用 waitForClick，而应连接一个
 * 使用所选控件对象的方法，将事件监听函数连接到该控件
 * 例如 setActionListener 或 setMouseListener。
 */
GEvent getNextEvent(int mask = ANY_EVENT) /*Q_DECL_DEPRECATED*/;

/**
 * 等待任意窗口中任意位置发生鼠标单击，
 * 返回发生的事件。
 *
 * @deprecated 已弃用
 * 此函数已弃用，不建议使用。
 * 不要在事件循环中调用 waitForClick，而应连接一个
 * 使用所选控件对象的方法，将事件监听函数连接到该控件
 * 例如 setActionListener 或 setMouseListener。
 */
GMouseEvent waitForClick() /*Q_DECL_DEPRECATED*/;

/**
 * 让进程等待，直到发生类型被以下对象覆盖的事件：
 * 事件掩码。mask 参数是以下事件的组合
 * 感兴趣的事件。例如，要等待鼠标事件或动作事件，
 * 客户端可以使用以下调用：
 *
 *<pre>
 *    e = waitForEvent(MOUSE_EVENT + ACTION_EVENT);
 *</pre>
 *
 * <code>mask</code> 参数是可选的。如果省略，
 * <code>waitForEvent</code> 接受任何事件。
 *
 * <p>作为更复杂的示例，以下代码是标准的
 * 需要响应鼠标的动画应用程序事件循环，
 * 键盘事件和计时器事件：
 *
 *<pre>
 *    GTimer timer(ANIMATION_DELAY_IN_MILLISECONDS);
 *    timer.start();
 *    while (true) {
 *       GEvent e = waitForEvent(TIMER_EVENT + MOUSE_EVENT + KEY_EVENT);
 *       switch (e.getEventClass()) {
 *        case TIMER_EVENT:
 *          takeAnimationStep();
 *          break;
 *        case MOUSE_EVENT:
 *          handleMouseEvent(GMouseEvent(e));
 *          break;
 *        case KEY_EVENT:
 *          handleKeyEvent(GKeyEvent(e));
 *          break;
 *       }
 *    }
 *</pre>
 *
 * @deprecated 已弃用
 * 此函数已弃用，不建议使用。
 * 不要在事件循环中调用 waitForClick，而应连接一个
 * 使用所选控件对象的方法，将事件监听函数连接到该控件
 * 例如 setActionListener 或 setMouseListener。
 */
GEvent waitForEvent(int mask = ANY_EVENT) /*Q_DECL_DEPRECATED*/;

#endif // _gevent_h
