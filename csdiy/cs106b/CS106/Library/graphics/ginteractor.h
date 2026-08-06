/*
 * 文件：ginteractor.h
 * -------------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 添加 set/removeActionListener
 * - 添加 set/removeClickListener
 * - 添加 set/removeDoubleClickListener
 * - 添加 set/removeKeyListener
 * - 添加 set/removeMouseListener
 * @version 2019/04/22
 * - 添加接受 QIcon 和 QPixmap 的 setIcon
 * @version 2018/09/20
 * - 添加读写锁以避免竞态条件
 * @version 2018/09/05
 * - 添加 getContainer 和 is/setVisible 逻辑
 * @version 2018/08/23
 * - 重命名为 ginteractor.h，以替代 Java 版本
 * @version 2018/06/25
 * - 初始版本
 */


#ifndef _ginteractor_h
#define _ginteractor_h

#include <string>
#include <QReadWriteLock>
#include <QWidget>

#include "gevent.h"
#include "gobservable.h"

class QPixmap;
class QIcon;

class GContainer;
class GDiffGui;
class GWindow;
class _Internal_QWidget;

/**
 * 此抽象类是所有图形交互控件的超类。
 * 在大多数应用中，交互控件会添加到沿着窗口的控制条中
 * GWindow 的一个区域。
 */
class GInteractor : public GObservable {
public:
    /**
     * 交互控件可将其文本相对于图标放置的位置。
     */
    enum TextPosition {
        TEXT_BESIDE_ICON,
        TEXT_UNDER_ICON,
        TEXT_ONLY
    };

    /**
     * 初始化新创建的交互控件。
     * 如果 Qt 图形子系统尚未初始化，构造
     * 交互控件会对其进行初始化。
     */
    GInteractor();

    /**
     * 释放交互控件内部分配的内存。
     */
    virtual ~GInteractor();

    /**
     * 如果此交互控件当前接受事件，则返回 true。
     * 初始为 true。
     * 交互控件必须可见并添加到屏幕窗口中，才能接收事件。
     */
    bool eventsEnabled() const override;

    /**
     * 返回表示此交互控件快捷键的字符串，
     * 如果未设置快捷键，则返回空字符串。
     * @return 快捷键，例如“Ctrl-S”
     */
    virtual std::string getAccelerator() const;

    /**
     * 返回此交互控件的动作命令，
     * 它是一个半唯一字符串，可在事件发生时用来标识该对象。
     * 例如，对于按钮，默认动作命令是按钮文本。
     */
    virtual std::string getActionCommand() const;

    /**
     * 以字符串返回交互控件的背景色。
     * @return 颜色字符串，例如 "blue" 或 "#7700ff"
     */
    virtual std::string getBackground() const;

    /**
     * 以 RGB 整数返回交互控件的背景色。
     * @return 整数，例如 0x7700ff
     */
    virtual int getBackgroundInt() const;

    /**
     * 返回表示此交互控件 x/y 位置和大小的矩形。
     */
    virtual GRectangle getBounds() const;

    /**
     * 以字符串形式返回交互控件的前景色/文本颜色。
     * 等价于 getForeground。
     * @return 颜色字符串，例如 "blue" 或 "#7700ff"
     */
    virtual std::string getColor() const;

    /**
     * 以 RGB 整数形式返回交互控件的前景色/文本颜色。
     * 等价于 getForegroundInt。
     * @return 整数，例如 0x7700ff
     */
    virtual int getColorInt() const;

    /**
     * 返回指向容纳此交互控件的屏幕容器的指针。
     * 创建交互控件时，其容器初始为 null。
     * 如果将交互控件添加到
     * 窗口或其他布局容器。
     * 交互控件必须添加到容器或窗口中才能接收事件
     * 或使其在屏幕上可见。
     * @return 容器；如果交互控件尚未被放入容器，则为 nullptr
     *         添加到任何容器
     */
    virtual GContainer* getContainer() const;

    /**
     * 以类似以下内容的字体字符串返回此交互控件文本的字体
     * "Helvetica-12-Bold"。
     * @return 字体字符串，例如“Helvetica-12-Bold”
     */
    virtual std::string getFont() const;

    /**
     * 以字符串形式返回交互控件的前景色/文本颜色。
     * 等价于 getColor。
     * @return 颜色字符串，例如 "blue" 或 "#7700ff"
     */
    virtual std::string getForeground() const;

    /**
     * 以 RGB 整数形式返回交互控件的前景色/文本颜色。
     * 等价于 getColorInt。
     * @return 整数，例如 0x7700ff
     */
    virtual int getForegroundInt() const;

    /**
     * 返回此交互控件当前屏幕高度（像素）。
     */
    virtual double getHeight() const;

    /**
     * 返回此交互控件的全局唯一标识符，
     * 该值在构造交互控件时设置。
     * 这些 ID 有助于调试，以唯一标识交互控件。
     */
    virtual int getID() const;

    /**
     * 返回与此交互控件关联的图标文件名，
     * 如果未设置图标，则返回空字符串。
     * 并非所有交互控件类型都支持图标。
     */
    virtual std::string getIcon() const;

    /**
     * 返回指向此对象所包装内部 Qt 控件的直接指针
     * 交互控件。所有交互控件子类都必须重写此方法。
     * 学生/客户端通常不需要调用此函数。
     * @private
     */
    virtual _Internal_QWidget* getInternalWidget() const = 0;

    /**
     * 返回表示屏幕左上角位置的 (x, y) 点
     * 此交互控件在其所在窗口中的角。
     */
    virtual GPoint getLocation() const;

    /**
     * 返回此交互控件允许的最小像素高度
     * 将自身调整到的大小。
     */
    virtual double getMinimumHeight() const;

    /**
     * 返回表示最小像素尺寸的 GDimension 结构
     * 此交互控件允许自身调整到的大小。
     */
    virtual GDimension getMinimumSize() const;

    /**
     * 返回此交互控件允许的最小像素宽度
     * 将自身调整到的大小。
     */
    virtual double getMinimumWidth() const;

    /**
     * 返回表示此交互控件唯一名称的字符串。
     * 默认名称字符串使用交互控件的类型及其 ID 来生成
     * 类似 "GButton_14" 的字符串，但可调用 setName 覆盖。
     * @return 字符串，例如“GButton_14”
     */
    virtual std::string getName() const;

    /**
     * 返回此交互控件首选的像素高度，
     * 恰好容纳其内容，不进行拉伸，也不显示滚动条。
     */
    virtual double getPreferredHeight() const;

    /**
     * 返回存储像素宽度和高度的 GDimension 结构
     * 此交互控件的首选大小，
     * 恰好容纳其内容，不进行拉伸，也不显示滚动条。
     */
    virtual GDimension getPreferredSize() const;

    /**
     * 返回此交互控件首选的像素高度，
     * 恰好容纳其内容，不进行拉伸，也不显示滚动条。
     */
    virtual double getPreferredWidth() const;

    /**
     * 返回存储当前屏幕宽度和高度的 GDimension 结构
     * 此交互控件的像素大小。
     */
    virtual GDimension getSize() const;

    /**
     * 返回表示此交互控件类名的字符串，
     * 例如 "GButton" 或 "GCheckBox"。
     * GInteractor 的所有子类都必须实现此方法。
     * @return 字符串，例如“GCheckBox”
     */
    std::string getType() const override = 0;

    /**
     * 返回指向此对象所包装内部 Qt 控件的直接指针
     * 交互控件。所有交互控件子类都必须重写此方法。
     * 学生/客户端通常不需要调用此函数。
     * @private
     */
    virtual QWidget* getWidget() const = 0;

    /**
     * 返回此交互控件当前屏幕宽度（像素）。
     */
    virtual double getWidth() const;

    /**
     * 返回此交互控件左上像素的 x 坐标
     * 在其屏幕窗口内。
     */
    virtual double getX() const;

    /**
     * 返回此交互控件左上像素的 y 坐标
     * 在其屏幕窗口内。
     */
    virtual double getY() const;

    /**
     * 如果给定的 x/y 像素位于此交互控件的边界内，则返回 true。
     */
    virtual bool inBounds(double x, double y) const;

    /**
     * 如果给定的 x/y 像素位于此交互控件的边界内，则返回 true。
     */
    virtual bool inBounds(int x, int y) const;

    /**
     * 如果此交互控件当前已启用，则返回 true。
     * 大多数交互控件初始时处于启用状态，但可以禁用以阻止它们
     * 能够被单击或以其他方式发出事件。
     */
    virtual bool isEnabled() const;

    /**
     * 如果交互控件在屏幕上可见，则返回 true。
     * 交互控件在添加到屏幕上的以下对象之前不可见：
     * 窗口或容器。
     */
    virtual bool isVisible() const;

    /**
     * 从此交互控件删除动作监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeActionListener();

    /**
     * 从此交互控件删除点击监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeClickListener();

    /**
     * 从此交互控件删除双击监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeDoubleClickListener();

    /**
     * 从此交互控件删除键盘监听器，使其不再
     * 在发生键盘事件时调用它。
     */
    virtual void removeKeyListener();

    /**
     * 从此交互控件删除鼠标监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeMouseListener();

    /**
     * 将键盘焦点转移到此交互控件。
     */
    virtual void requestFocus();

    /**
     * 为此交互控件设置快捷键，例如 "Ctrl-S"。
     * 并非所有交互控件类型都支持快捷键。
     * @param accelerator 快捷键，例如“Ctrl-S”
     */
    virtual void setAccelerator(const std::string& accelerator);

    /**
     * 设置此交互控件的动作命令。
     * 动作命令应是一个半唯一字符串，可用于
     * 在事件发生时标识交互控件。
     * 例如，对于按钮，默认动作命令是按钮文本，
     * 但如果愿意，可以将它改为其他字符串。
     * 此功能的主要用途是，当你希望将同一个函数用作
     * 如果要为许多交互控件设置事件监听器，可以使用动作命令
     * 帮助区分每个事件由哪个交互控件生成。
     */
    virtual void setActionCommand(const std::string& actionCommand);

    /**
     * 在此交互控件上设置动作监听器，以便在以下情况发生时调用它
     * 当以其主要方式与它交互时。
     * 例如，若此交互控件是按钮，单击时会触发。
     * 任何现有的动作监听器都会被替换。
     */
    virtual void setActionListener(GEventListener func);

    /**
     * 在此交互控件上设置动作监听器，以便在以下情况发生时调用它
     * 当以其主要方式与它交互时。
     * 例如，若此交互控件是按钮，单击时会触发。
     * 任何现有的动作监听器都会被替换。
     */
    virtual void setActionListener(GEventListenerVoid func);

    /**
     * 将交互控件的背景色设置为由以下内容表示的颜色：
     * 给定 RGB 整数。
     * @param rgb RGB 整数，例如 0x7700ff
     */
    virtual void setBackground(int rgb);

    /**
     * 将交互控件的背景色设置为由以下内容表示的颜色：
     * 给定字符串。
     * @param color 颜色字符串，例如 "blue" 或 "#7700ff"
     */
    virtual void setBackground(const std::string& color);

    /**
     * 设置控件的大小和位置。
     * 通常应避免显式设置控件大小和位置
     * 不要采用这种方式；应使用容器和区域帮助布局
     * 以适当大小放置控件。
     */
    virtual void setBounds(double x, double y, double width, double height);

    /**
     * 设置控件的大小和位置。
     * 通常应避免显式设置控件大小和位置
     * 不要采用这种方式；应使用容器和区域帮助布局
     * 以适当大小放置控件。
     */
    virtual void setBounds(const GRectangle& size);

    /**
     * 为此交互控件设置鼠标监听器，以便在以下情况下调用：
     * 当鼠标在其上单击时。
     * 任何现有的单击监听器都会被替换。
     */
    virtual void setClickListener(GEventListener func);

    /**
     * 为此交互控件设置鼠标监听器，以便在以下情况下调用：
     * 当鼠标在其上单击时。
     * 任何现有的单击监听器都会被替换。
     */
    virtual void setClickListener(GEventListenerVoid func);

    /**
     * 将交互控件的前景/文本颜色设为以下内容表示的颜色：
     * 给定 RGB 整数。
     * 等价于 setForeground。
     * @param rgb RGB 整数，例如 0x7700ff
     */
    virtual void setColor(int rgb);

    /**
     * 将交互控件的前景/文本颜色设为以下内容表示的颜色：
     * 给定字符串。
     * 等价于 setForeground。
     * @param color 颜色字符串，例如 "blue" 或 "#7700ff"
     */
    virtual void setColor(const std::string& color);

    /**
     * 为此交互控件设置鼠标监听器，以便在以下情况下调用：
     * 当鼠标在其上双击时。
     * 任何现有的双击监听器都会被替换。
     */
    virtual void setDoubleClickListener(GEventListener func);

    /**
     * 为此交互控件设置鼠标监听器，以便在以下情况下调用：
     * 当鼠标在其上双击时。
     * 任何现有的双击监听器都会被替换。
     */
    virtual void setDoubleClickListener(GEventListenerVoid func);

    /**
     * 设置此交互控件当前是否启用。
     * 大多数交互控件初始时处于启用状态，但可以禁用以阻止它们
     * 能够被单击或以其他方式发出事件。
     */
    virtual void setEnabled(bool value);

    /**
     * 将此控件使用的字体设为给定 Qt 字体。
     * 客户端通常应使用此方法的字符串版本。
     */
    virtual void setFont(const QFont& font);

    /**
     * 将此控件使用的字体设为以下字符串所表示的字体
     * 给定字体字符串，例如“Helvetica-16-Bold”。
     * @param font 字体字符串，例如“Helvetica-16-Bold”
     */
    virtual void setFont(const std::string& font);

    /**
     * 将交互控件的前景/文本颜色设为以下内容表示的颜色：
     * 给定 RGB 整数。
     * 等价于 setColor。
     * @param rgb RGB 整数，例如 0x7700ff
     */
    virtual void setForeground(int rgb);

    /**
     * 将交互控件的前景/文本颜色设为以下内容表示的颜色：
     * 给定字符串。
     * 等价于 setColor。
     * @param color 颜色字符串，例如 "blue" 或 "#7700ff"
     */
    virtual void setForeground(const std::string& color);

    /**
     * 设置交互控件在屏幕上的像素高度。
     * @throw 如果 height 为负数，则抛出 ErrorException
     */
    virtual void setHeight(double height);

    /**
     * 设置与此交互控件关联的图标。
     * 并非所有交互控件类型都支持图标。
     * @param icon 要使用的图标
     */
    virtual void setIcon(const QIcon& icon);

    /**
     * 设置与此交互控件关联的图标。
     * 并非所有交互控件类型都支持图标。
     * @param icon 要使用的图标
     */
    virtual void setIcon(const QPixmap& icon);

    /**
     * 设置与此交互控件关联的图标文件名，
     * 如果未设置图标，则返回空字符串。
     * 并非所有交互控件类型都支持图标。
     * @param filename 要使用的图标文件路径
     * @param retainIconSize 如果图标应保持现有像素大小，则为 true（默认），
     *                       如果应调整大小以适应交互控件，则为 false
     */
    virtual void setIcon(const std::string& filename, bool retainIconSize = true);

    /**
     * 在此交互控件上设置键盘监听器，以便在以下情况发生时调用它
     * 当用户按下任意键时。
     * 任何现有的按键监听器都会被替换。
     */
    virtual void setKeyListener(GEventListener func);

    /**
     * 在此交互控件上设置键盘监听器，以便在以下情况发生时调用它
     * 当用户按下任意键时。
     * 任何现有的按键监听器都会被替换。
     */
    virtual void setKeyListener(GEventListenerVoid func);

    /**
     * 设置交互控件左上角在屏幕上的 x/y 坐标
     * 相对于其窗口。
     * 通常客户端不应调用此函数，而应改用容器
     * 以及用于定位交互控件的布局区域。
     */
    virtual void setLocation(double x, double y);

    /**
     * 设置此交互控件允许自身缩小到的最小像素尺寸
     * 要调整到的大小。
     * @throw 如果 width 或 height 为负，则抛出 ErrorException
     */
    virtual void setMinimumSize(double width, double height);

    /**
     * 设置此交互控件允许自身缩小到的最小像素尺寸
     * 要调整到的大小。
     * @throw 如果 width 或 height 为负，则抛出 ErrorException
     */
    virtual void setMinimumSize(const GDimension& size);

    /**
     * 为此交互控件设置鼠标监听器，以便在以下情况下调用：
     * 当鼠标在其上移动或单击时。
     * 任何现有的鼠标监听器都会被替换。
     */
    virtual void setMouseListener(GEventListener func);

    /**
     * 为此交互控件设置鼠标监听器，以便在以下情况下调用：
     * 当鼠标在其上移动或单击时。
     * 任何现有的鼠标监听器都会被替换。
     */
    virtual void setMouseListener(GEventListenerVoid func);

    /**
     * 设置表示此交互控件唯一名称的字符串。
     * 默认名称字符串使用交互控件的类型及其 ID 来生成
     * 类似 "GButton_14" 的字符串，但可调用 setName 覆盖。
     * @param name 字符串，例如“GButton_14”
     */
    virtual void setName(const std::string& name);

    /**
     * 设置此交互控件的首选像素高度。
     * 通常客户端无需调用此方法；交互控件可以
     * 自行确定首选大小。
     * 但调用它可以在以下情况下向容器/布局系统提供提示：
     * 你希望给定交互控件“倾向于”使自身变大或变小
     * 针对具体程序的需要。
     */
    virtual void setPreferredHeight(double height);

    /**
     * 设置此交互控件的首选像素宽度和高度。
     * 通常客户端无需调用此方法；交互控件可以
     * 自行确定首选大小。
     * 但调用它可以在以下情况下向容器/布局系统提供提示：
     * 你希望给定交互控件“倾向于”使自身变大或变小
     * 针对具体程序的需要。
     */
    virtual void setPreferredSize(double width, double height);


    /**
     * 设置此交互控件的首选像素尺寸。
     * 通常客户端无需调用此方法；交互控件可以
     * 自行确定首选大小。
     */
    virtual void setPreferredSize(const GDimension& size);


    /**
     * 设置此交互控件的首选像素宽度。
     * 通常客户端无需调用此方法；交互控件可以
     * 自行确定首选大小。
     */
    virtual void setPreferredWidth(double width);

    /**
     * 设置交互控件在屏幕上的像素宽度和高度。
     * @throw 如果 width 或 height 为负，则抛出 ErrorException
     */
    virtual void setSize(double width, double height);

    /**
     * 设置交互控件在屏幕上的像素宽度和高度。
     * @throw 如果 width 或 height 为负，则抛出 ErrorException
     */
    virtual void setSize(const GDimension& size);

    /**
     * 设置一个“工具提示”，当用户将鼠标悬停于以下位置时显示
     * 覆盖在交互控件上。
     * 设置空字符串以清除工具提示。
     */
    virtual void setTooltip(const std::string& tooltipText);

    /**
     * 如果交互控件在屏幕上可见，则返回 true。
     * 交互控件在添加到屏幕上的以下对象之前不可见：
     * 窗口或容器。
     * 如果对不在任何屏幕窗口中的交互控件调用 setVisible
     * 容器中，它不会产生任何效果。
     */
    virtual void setVisible(bool visible);

    /**
     * 设置交互控件在屏幕上的像素宽度。
     * @throw 如果 width 为负数，则抛出 ErrorException
     */
    virtual void setWidth(double width);

    /**
     * 设置交互控件左上角在屏幕上的 x 坐标
     * 相对于其窗口。
     * 通常客户端不应调用此函数，而应改用容器
     * 以及用于定位交互控件的布局区域。
     */
    virtual void setX(double x);

    /**
     * 设置交互控件左上角在屏幕上的 y 坐标
     * 相对于其窗口。
     * 通常客户端不应调用此函数，而应改用容器
     * 以及用于定位交互控件的布局区域。
     */
    virtual void setY(double y);

protected:
    /**
     * @private
     */
    std::string _actionCommand;

    /**
     * @private
     */
    std::string _actionEventType;

    /**
     * @private
     */
    std::string _icon;

    /**
     * @private
     */
    std::string _name;

    /**
     * @private
     */
    int _id;

    /**
     * @private
     */
    GContainer* _container;

    /**
     * @private
     */
    QReadWriteLock _lock;    // 避免线程竞态条件

    /**
     * @private
     */
    static QWidget* getInternalParent(QWidget* parent);

    /**
     * @private
     */
    virtual std::string getActionEventType() const;

    /**
     * @private
     */
    virtual std::string getDefaultInteractorName() const;

    /**
     * @private
     */
    virtual void lockForRead();

    /**
     * @private
     */
    virtual void lockForReadConst() const;

    /**
     * @private
     */
    virtual void lockForWrite();

    /**
     * @private
     */
    virtual void lockForWriteConst() const;

    /**
     * @private
     */
    static std::string normalizeAccelerator(const std::string& accelerator);

    /**
     * @private
     */
    virtual void setContainer(GContainer* container);

    /**
     * @private
     */
    virtual void unlock();

    /**
     * @private
     */
    virtual void unlockConst() const;

    friend class GContainer;
    friend class GDiffGui;
    friend class GWindow;
    friend class _Internal_QWidget;

private:
    static int _interactorCount;
};


/**
 * 表示包装在以下对象内部的内部 Qt 控件的类：
 * GInteractor 对象。
 * 每个 GInteractor 子类都必须定义一个以下对象的子类：
 * 要由该交互控件包装的 _Internal_QWidget。
 * @private
 */
class _Internal_QWidget {
public:
    _Internal_QWidget();
    virtual ~_Internal_QWidget();
    virtual void detach();
    virtual QSize getMinimumSize() const;
    virtual bool hasMinimumSize() const;
    virtual QSize getPreferredSize() const;
    virtual bool hasPreferredSize() const;
    virtual void setMinimumSize(double width, double height);
    virtual void setMinimumSize(const QSize& size);
    virtual void setPreferredSize(double width, double height);
    virtual void setPreferredSize(const QSize& size);

private:
    GDimension _minimumSize;
    GDimension _preferredSize;

    friend class GInteractor;
};

/**
 * 一个通用的简单 GInteractor，可包装传入的任意 Qt QWidget。
 * 这样设计是为了使库可扩展，并允许你包装其他
 * 原始库中未内置的 Qt 控件。
 * @private
 */
template <typename T>
class GGenericInteractor : public GInteractor {
public:
    GGenericInteractor(T* widget)
            : _widget(widget) {
        _iqwidget = new _Internal_QWidget();   // 占位项
    }

    _Internal_QWidget* getInternalWidget() const override {
        return _iqwidget;
    }

    std::string getType() const override {
        std::string typeName = typeid(T).name();
        return std::string("GGenericInteractor<") + typeName + ">";
    }

    QWidget* getWidget() const override {
        return _widget;
    }

private:
    _Internal_QWidget* _iqwidget;
    T* _widget;
};

#endif // _ginteractor_h
