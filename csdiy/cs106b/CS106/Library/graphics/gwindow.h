/*
 * 文件：gwindow.h
 * ---------------
 *
 * @author Marty Stepp
 * @version 2019/05/05
 * - 添加用于检查深色模式的静态方法
 * - 添加获取系统默认控件背景色/前景色的静态方法
 * @version 2019/04/09
 * - 添加工具栏支持
 * @version 2018/10/20
 * - 添加高密度屏幕功能
 * @version 2018/09/09
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/05
 * - 重构为使用边界布局的 GContainer“内容窗格”存储所有交互控件
 * @version 2018/08/23
 * - 重命名为 gwindow.h，以替代 Java 版本
 * @version 2018/07/29
 * - 菜单栏
 * @version 2018/06/25
 * - 初始版本
 */


#ifndef _gwindow_h
#define _gwindow_h

#include <string>
#include <QCloseEvent>
#include <QEvent>
#include <QLayout>
#include <QMainWindow>
#include <QRect>

#include "gcanvas.h"
#include "gcontainer.h"
#include "gdrawingsurface.h"
#include "geventqueue.h"
#include "ginteractor.h"
#include "grid.h"
#include "gtypes.h"
#include "map.h"
#include "set.h"

class _Internal_QMainWindow;

/**
 * 此类表示支持简单图形操作的图形窗口。
 * GWindow 是 GUI 子系统中的一等对象；所有图形
 * 程序通常会创建至少一个 GWindow，用于容纳其他交互控件和
 * 用于在屏幕上显示的图形对象。
 *
 * GWindow 同时承担两个主要图形用途：
 *
 * 1）交互控件的顶层容器。
 * 可以调用 addToRegion 和 add 方法，将交互控件添加到北部、
 * 窗口的南、西、东和中心区域。
 * 中心区域最多容纳一个在两个维度上扩展的交互控件
 * 填充未被其他四个区域占用的像素。
 * 这类似于 Java AWT/Swing 的 BorderLayout 系统。
 * 窗口使用一个内部 GContainer（称为“内容窗格”）来
 * 安排这些交互控件的位置和大小。
 * 有关布局和容器的更多详细信息，请参阅 gcontainer.h。
 *
 * 2）用于绘制形状、线条和颜色的图形画布。
 * GWindow 包含一个中央图形画布，其实现形式为
 * GCanvas 类型的对象。一旦你执行以下操作，画布就会出现在窗口上
 * 在窗口上调用任意绘图方法。
 *
 * 图形画布由两层组成。
 * 背景层提供用于绘制静态图像的表面，这些图像
 * 不涉及动画，或用于基于二维像素的绘图算法。
 * 有关绘制形状、对象等的更多详细信息，请参阅 gcanvas.h 和 gobjects.h
 * 以及像素。
 *
 * GWindow 类包含若干 drawXxx 和 fillXxx 方法，用于绘制
 * 无需客户端即可在背景层绘制线条、矩形和椭圆
 * 无需直接创建 gobjects.h 层次结构中的对象。
 *
 * 前景层提供用于添加有状态形状和对象的抽象
 * 将图形对象绘制到画布。接受 GObject 的 add() 方法
 * 参数会将这些对象放到前景层。这样做的优点是
 * 前景层的优点是可以随时间操控对象，例如
 * 移动它、更改其颜色、大小或其他属性，并看到这些变化
 * 立即显示在屏幕上。这使前景层最适合
 * 适合动画或移动精灵。
 *
 * 可以在同一个窗口中同时使用两种 GWindow 范式。
 * 例如，可以在北部或南部放置一行按钮，同时
 * 在窗口中心的画布上绘制形状。
 *
 * 如果将 GInteractor add() 到窗口的中心区域，我们会假定
 * 你不希望使用图形画布，并将用所添加的内容替换它
 * 交互控件。
 */
class GWindow : public GObservable, public virtual GForwardDrawingSurface {
public:
    /**
     * 窗口边框布局的五个区域。
     */
    enum Region {
        REGION_CENTER = GContainer::REGION_CENTER,
        REGION_EAST = GContainer::REGION_EAST,
        REGION_NORTH = GContainer::REGION_NORTH,
        REGION_SOUTH = GContainer::REGION_SOUTH,
        REGION_WEST = GContainer::REGION_WEST
    };

    /**
     * 窗口关闭时可能发生的各种操作。
     */
    enum CloseOperation {
        CLOSE_DO_NOTHING,
        CLOSE_HIDE,
        CLOSE_DISPOSE,
        CLOSE_EXIT
    };

    /**
     * 未指定时新创建窗口的默认像素宽度
     * 其宽度未明确指定。
     */
    static const int DEFAULT_WIDTH;

    /**
     * 未指定时新创建窗口的默认像素高度
     * 其高度未明确指定。
     */
    static const int DEFAULT_HEIGHT;

    /**
     * 屏幕被视为
     * 被视为高密度或高 DPI。
     */
    static const int HIGH_DPI_SCREEN_THRESHOLD;

    /**
     * “普通”低 DPI 屏幕的最低每英寸点数。
     * 用于确定在高 DPI 屏幕上应放大多少。
     */
    static const int STANDARD_SCREEN_DPI;

    /**
     * 用于加载 GWindow 初始内容的默认文件名
     * 标题栏图标。
     */
    static const std::string DEFAULT_ICON_FILENAME;

    /**
     * 创建具有默认宽度和高度的新窗口。
     */
    GWindow(bool visible = true);

    /**
     * 创建具有给定宽度和高度的新窗口。
     */
    GWindow(double width, double height, bool visible = true);

    /**
     * 创建具有给定位置和大小的新窗口。
     */
    GWindow(double x, double y, double width, double height, bool visible = true);

    /**
     * 释放窗口内部分配的内存。
     */
    ~GWindow() override;

    /**
     * 将给定交互控件添加到窗口中心区域。
     * 此操作会替换图形画布并将画布隐藏。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void add(GInteractor* interactor);

    /**
     * 将给定交互控件添加到窗口中心区域
     * 并将其移动到给定 x/y 位置。
     * 此操作会替换图形画布并将画布隐藏。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void add(GInteractor* interactor, double x, double y);

    /**
     * 将给定交互控件添加到窗口中心区域。
     * 此操作会替换图形画布并将画布隐藏。
     */
    virtual void add(GInteractor& interactor);

    /**
     * 将给定交互控件添加到窗口中心区域
     * 并将其移动到给定 x/y 位置。
     * 此操作会替换图形画布并将画布隐藏。
     */
    virtual void add(GInteractor& interactor, double x, double y);

    /**
     * 将给定图形对象添加到窗口画布。
     * 若图形画布尚未显示，此操作会使其出现。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void add(GObject* obj);

    /**
     * 将给定图形对象添加到窗口画布
     * 并将其移动到给定 x/y 位置。
     * 若图形画布尚未显示，此操作会使其出现。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void add(GObject* obj, double x, double y);

    /**
     * 将给定图形对象添加到窗口画布。
     * 若图形画布尚未显示，此操作会使其出现。
     */
    virtual void add(GObject& obj);

    /**
     * 将给定图形对象添加到窗口画布
     * 并将其移动到给定 x/y 位置。
     * 若图形画布尚未显示，此操作会使其出现。
     */
    virtual void add(GObject& obj, double x, double y);

    /**
     * 将具有给定文本的菜单添加到窗口顶部菜单栏。
     * 如果给定菜单已存在，则直接返回它而不再次添加。
     */
    virtual QMenu* addMenu(const std::string& text);

    /**
     * 向给定菜单添加新菜单项。
     * 若给定菜单项已存在于此菜单中，则直接返回它，不会
     * 再次添加它。
     * 可以提供一个可选图标，显示在菜单项旁边。
     * 单击菜单项时，会发生 ACTION_MENU 动作事件。
     * @throw 如果给定菜单不存在，则抛出 ErrorException
     */
    virtual QAction* addMenuItem(const std::string& menu, const std::string& item,
                                 const std::string& icon = "");

    /**
     * 向给定菜单添加新菜单项。
     * 若给定菜单项已存在于此菜单中，则直接返回它，不会
     * 再次添加它。
     * 可以提供一个可选图标，显示在菜单项旁边。
     * 单击菜单项时，将调用给定监听器函数。
     * @throw 如果给定菜单不存在，则抛出 ErrorException
     */
    virtual QAction* addMenuItem(const std::string& menu, const std::string& item,
                                 const std::string& icon, GEventListenerVoid func);

    /**
     * 向给定菜单添加新菜单项。
     * 若给定菜单项已存在于此菜单中，则直接返回它，不会
     * 再次添加它。
     * 可以提供一个可选图标，显示在菜单项旁边。
     * 单击菜单项时，将调用给定监听器函数。
     * @throw 如果给定菜单不存在，则抛出 ErrorException
     */
    virtual QAction* addMenuItem(const std::string& menu, const std::string& item,
                                 const QIcon& icon, GEventListenerVoid func);

    /**
     * 向给定菜单添加新菜单项。
     * 若给定菜单项已存在于此菜单中，则直接返回它，不会
     * 再次添加它。
     * 可以提供一个可选图标，显示在菜单项旁边。
     * 单击菜单项时，将调用给定监听器函数。
     * @throw 如果给定菜单不存在，则抛出 ErrorException
     */
    virtual QAction* addMenuItem(const std::string& menu, const std::string& item,
                                 const QPixmap& icon, GEventListenerVoid func);

    /**
     * 向给定菜单添加新的复选菜单项。
     * 若给定菜单项已存在于此菜单中，则直接返回它，不会
     * 再次添加它。
     * 可以提供一个可选图标，显示在菜单项旁边。
     * 单击菜单项时，会发生 ACTION_MENU 动作事件。
     * @throw 如果给定菜单不存在，则抛出 ErrorException
     */
    virtual QAction* addMenuItemCheckBox(const std::string& menu, const std::string& item,
                                         bool checked = false,
                                         const std::string& icon = "");

    /**
     * 向给定菜单添加新的复选菜单项。
     * 若给定菜单项已存在于此菜单中，则直接返回它，不会
     * 再次添加它。
     * 可以提供一个可选图标，显示在菜单项旁边。
     * 单击菜单项时，将调用给定监听器函数。
     * @throw 如果给定菜单不存在，则抛出 ErrorException
     */
    virtual QAction* addMenuItemCheckBox(const std::string& menu, const std::string& item,
                                         bool checked,
                                         const std::string& icon, GEventListenerVoid func);

    /**
     * 在给定菜单末尾添加水平分隔线。
     * @throw 如果给定菜单不存在，则抛出 ErrorException
     */
    virtual QAction* addMenuSeparator(const std::string& menu);

    /**
     * 在现有菜单中添加子菜单。
     * 之后可以使用以下代码向此子菜单添加项：
     *
     * myWindow->addMenuItem(menu + "/" + submenu, item);
     * @throw 如果给定菜单不存在，则抛出 ErrorException
     */
    virtual QMenu* addSubMenu(const std::string& menu, const std::string& submenu);

    /**
     * 将给定交互控件添加到此窗口的给定区域。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void addToRegion(GInteractor* interactor, Region region);

    /**
     * 将给定交互控件添加到此窗口的给定区域。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void addToRegion(GInteractor* interactor, const std::string& region = "Center");

    /**
     * 将给定交互控件添加到此窗口的给定区域。
     */
    virtual void addToRegion(GInteractor& interactor, Region region);

    /**
     * 将给定交互控件添加到此窗口的给定区域。
     */
    virtual void addToRegion(GInteractor& interactor, const std::string& region = "Center");

    /**
     * 向此窗口添加可放置操作按钮的工具栏。
     */
    virtual void addToolbar(const std::string& title = "");

    /**
     * 向窗口工具栏添加新项目。
     * 若窗口没有工具栏，则添加一个。
     * 可以提供一个可选图标，显示在菜单项旁边。
     * 单击菜单项时，会发生 ACTION_MENU 动作事件。
     */
    virtual QAction* addToolbarItem(const std::string& item,
                                    const std::string& icon = "");

    /**
     * 向窗口工具栏添加新项目。
     * 若窗口没有工具栏，则添加一个。
     * 可以提供一个可选图标，显示在菜单项旁边。
     * 单击菜单项时，将调用给定监听器函数。
     */
    virtual QAction* addToolbarItem(const std::string& item,
                                    const std::string& icon,
                                    GEventListenerVoid func);

    /**
     * 向窗口工具栏添加新项目。
     * 若窗口没有工具栏，则添加一个。
     * 可以提供一个可选图标，显示在菜单项旁边。
     * 单击菜单项时，将调用给定监听器函数。
     */
    virtual QAction* addToolbarItem(const std::string& item,
                                    const QIcon& icon,
                                    GEventListenerVoid func);

    /**
     * 向窗口工具栏添加新项目。
     * 若窗口没有工具栏，则添加一个。
     * 可以提供一个可选图标，显示在菜单项旁边。
     * 单击菜单项时，将调用给定监听器函数。
     */
    virtual QAction* addToolbarItem(const std::string& item,
                                    const QPixmap& icon,
                                    GEventListenerVoid func);

    /**
     * 向窗口工具栏添加分隔符。
     * 若窗口没有工具栏，则添加一个。
     */
    virtual QAction* addToolbarSeparator();

    /**
     * 从窗口所有区域删除所有交互控件。
     */
    void clear() override;

    /**
     * 从此窗口的图形画布中删除所有图形对象
     * 并将背景层重置为窗口背景色。
     */
    virtual void clearCanvas();

    /**
     * 从此窗口的图形画布中删除所有图形对象。
     * 这意味着使用 add() 方法添加的任何形状（例如 GRect）
     * GOval 等对象会被移除，而直接绘制到以下对象上的形状
     * 通过调用 drawXxx() 方法绘制到窗口背景像素层的内容将会
     * 保留。若还要清除背景层，请调用 clearCanvasPixels
     * 或改用 clearCanvas。
     */
    virtual void clearCanvasObjects();

    /**
     * 将窗口画布像素的背景层重置为
     * 窗口的背景色。
     * 这意味着使用 add() 方法添加的任何形状（例如 GRect）
     * GOval 等对象会保留，而直接绘制到以下对象上的形状
     * 通过调用 drawXxx() 方法绘制到窗口背景像素层的内容将会
     * 被清除。若还要清除添加到前景层的形状，
     * 改为调用 clearCanvasObjects 或 clearCanvas。
     */
    virtual void clearCanvasPixels();

    /**
     * 从此窗口的给定区域移除所有交互控件。
     */
    virtual void clearRegion(Region region);

    /**
     * 从此窗口的给定区域移除所有交互控件。
     */
    virtual void clearRegion(const std::string& region);

    /**
     * 从窗口工具栏中删除所有项目（如果存在）。
     */
    virtual void clearToolbarItems();

    /**
     * 将窗口精确移动到当前屏幕中心。
     */
    virtual void center();

    /**
     * 根据用户计算机是否处于以下状态，返回应使用的颜色：
     * 处于浅色或深色模式。
     * 若处于浅色模式，返回 lightColor；否则返回 darkColor。
     */
    static std::string chooseLightDarkModeColor(const std::string& lightColor,
                                                const std::string& darkColor);

    /**
     * 根据用户计算机是否处于以下状态，返回应使用的颜色：
     * 处于浅色或深色模式。
     * 若处于浅色模式，返回 lightColor；否则返回 darkColor。
     */
    static int chooseLightDarkModeColorInt(int lightColor, int darkColor);

    /**
     * 关闭窗口。
     * 如果设置了窗口监听器，将依次触发 WINDOW_CLOSING 和
     * 向其发送 WINDOW_CLOSED 事件。
     */
    virtual void close();

    /**
     * 将此窗口的像素与以下图像内容进行比较：
     * 给定文件。
     * 差异显示在“差异图像”窗口中，其中会高亮
     * 任何不同的像素。
     *
     * TODO：实现
     * @private
     */
    virtual void compareToImage(const std::string& filename, bool ignoreWindowSize = true) const;

    /**
     * 如果窗口可以发生事件，则返回 true。
     * 如果窗口已初始化且可见，此值将为 true。
     * @private
     */
    bool eventsEnabled() const override;

    /**
     * 返回指向窗口内部图形画布的直接指针
     * 用于绘制形状和对象。
     * 请谨慎使用！
     */
    virtual GCanvas* getCanvas() const;

    /**
     * 返回窗口中央画布区域的像素高度。
     */
    virtual double getCanvasHeight() const;

    /**
     * 返回窗口中央画布区域的像素宽度和高度。
     */
    virtual GDimension getCanvasSize() const;

    /**
     * 返回窗口中央画布区域的像素宽度。
     */
    virtual double getCanvasWidth() const;

    /**
     * 返回一个常量，表示发生以下情况时将采取的操作
     * 用户关闭窗口。
     */
    virtual CloseOperation getCloseOperation() const;

    /**
     * 以字符串返回交互控件背景的默认颜色。
     * 通常是浅灰色，具体取决于用户的
     * 系统设置。
     * 在某些处于“深色模式”的系统上，它可能是更接近黑色的颜色。
     */
    static std::string getDefaultInteractorBackgroundColor();

    /**
     * 以 RGB 整数形式返回交互控件文本的默认颜色。
     * 通常是浅灰色，具体取决于用户的
     * 系统设置。
     * 在某些处于“深色模式”的系统上，它可能是更接近黑色的颜色。
     */
    static int getDefaultInteractorBackgroundColorInt();

    /**
     * 以字符串返回交互控件文本的默认颜色。
     * 通常是黑色或接近黑色，具体取决于用户的
     * 系统设置。
     * 在某些处于“深色模式”的系统上，它可能是更接近白色的颜色。
     */
    static std::string getDefaultInteractorTextColor();

    /**
     * 以 RGB 整数形式返回交互控件文本的默认颜色。
     * 通常是黑色或接近黑色，具体取决于用户的
     * 系统设置。
     * 在某些处于“深色模式”的系统上，它可能是更接近白色的颜色。
     */
    static int getDefaultInteractorTextColorInt();

    /**
     * 返回窗口中给定从 0 开始索引处的图形对象
     * 图形画布。
     * @throw 如果索引越界，则抛出 ErrorException
     */
    virtual GObject* getGObject(int index) const;

    /**
     * 返回窗口中 z 顺序最上层的图形对象
     * 图形画布中与给定 x/y 像素位置接触的对象。
     * 如果没有对象接触给定位置，则返回 nullptr。
     */
    virtual GObject* getGObjectAt(double x, double y) const;

    /**
     * 返回窗口画布中的图形对象总数。
     */
    virtual int getGObjectCount() const;

    /**
     * 返回指向最近创建的 Qt 窗口对象的指针。
     * 学生不得调用。
     * @private
     */
    static QMainWindow* getLastWindow();

    /**
     * 返回屏幕上窗口内部左上角的 x/y 位置，
     * 不包括屏幕上的窗口标题栏和边框。
     */
    virtual GPoint getLocation() const;

    /**
     * 返回窗口总像素高度，不包括标题
     * 标题栏和边框。
     */
    virtual double getHeight() const;

    /**
     * 返回窗口的首选大小。
     * 窗口倾向于恰好能容纳交互控件的尺寸
     * 以其各自的首选大小放置在其中，而不会拉伸。
     * 调用 pack() 时，窗口将设置为此大小。
     */
    virtual GDimension getPreferredSize() const;

    /**
     * 返回窗口给定区域的像素高度。
     */
    virtual double getRegionHeight(Region region) const;

    /**
     * 返回窗口给定区域的像素高度。
     */
    virtual double getRegionHeight(const std::string& region) const;

    /**
     * 返回窗口给定区域的像素宽度和高度。
     */
    virtual GDimension getRegionSize(Region region) const;

    /**
     * 返回窗口给定区域的像素宽度和高度。
     */
    virtual GDimension getRegionSize(const std::string& region) const;

    /**
     * 返回窗口给定区域的像素宽度。
     */
    virtual double getRegionWidth(Region region) const;

    /**
     * 返回窗口给定区域的像素宽度。
     */
    virtual double getRegionWidth(const std::string& region) const;

    /**
     * 返回屏幕的每英寸点数。
     * 这用于处理高密度屏幕。
     */
    static int getScreenDpi();

    /**
     * 返回此屏幕 DPI 相对于普通低 DPI 屏幕的比率。
     * 这可用于在高密度屏幕上放大图形。
     */
    static double getScreenDpiScaleRatio();

    /**
     * 返回整个屏幕的像素高度。
     */
    static double getScreenHeight();

    /**
     * 返回整个屏幕的像素宽度和高度。
     */
    static GDimension getScreenSize();

    /**
     * 返回整个屏幕的像素宽度。
     */
    static double getScreenWidth();

    /**
     * 返回窗口总像素宽度和高度，不包括
     * 其标题栏和边框。
     */
    virtual GDimension getSize() const;

    /**
     * 返回窗口标题栏文本。
     */
    virtual std::string getTitle() const;

    /* @inherit */
    std::string getType() const override;

    /**
     * 返回表示窗口的内部 Qt 控件。
     * 客户端无需直接使用此方法。
     * @private
     */
    virtual QWidget* getWidget() const;

    /**
     * 返回窗口总像素宽度，不包括标题
     * 标题栏和边框。
     */
    virtual double getWidth() const;

    /**
     * 返回屏幕上窗口内部左边缘的 x 位置，
     * 不包括屏幕上的窗口标题栏和边框。
     */
    virtual double getX() const;

    /**
     * 返回屏幕上窗口内部上边缘的 y 位置，
     * 不包括屏幕上的窗口标题栏和边框。
     */
    virtual double getY() const;

    /**
     * 如果此窗口有工具栏，则返回 true。
     */
    virtual bool hasToolbar() const;

    /**
     * 使窗口在屏幕上不可见。
     * 等价于 setVisible(false)。
     */
    virtual void hide();

    /**
     * 如果给定 x/y 位置位于整个区域边界内，则返回 true
     * 窗口。
     * 请注意，这是基于包含标题栏在内的完整窗口大小
     * 栏、菜单、边框等。
     * 如果你试图测试窗口画布区域中形状的边界，
     * 改用 inCanvasBounds 方法。
     */
    virtual bool inBounds(double x, double y) const;

    /**
     * 如果给定 x/y 位置位于中央区域边界内，则返回 true
     * 窗口的画布区域。
     */
    virtual bool inCanvasBounds(double x, double y) const;

    /**
     * 如果用户计算机处于“深色模式”，则返回 true。
     * 这是一种流行的深色配色方案，主要用于较新的 Mac。
     * 我们的检查并不完善，基本上只是创建一个虚拟控件
     * 并检查其是否具有明亮文本和深色背景。
     */
    static bool isDarkMode();

    /**
     * 返回屏幕每英寸点数是否足够高，以便
     * 将其视为应使用缩放的“高密度”屏幕。
     * 其阈值由常量
     */
    static bool isHighDensityScreen();

    /**
     * 返回在高密度屏幕上运行时是否应缩放某些窗口
     * 屏幕。
     */
    static bool isHighDpiScalingEnabled();

    /**
     * 如果窗口处于占据整个屏幕的最大化状态，则返回 true
     * 屏幕。
     */
    virtual bool isMaximized() const;

    /**
     * 如果窗口处于最小化（图标化）状态，则返回 true
     * 通常表现为窗口被隐藏，只在任务栏中留下图标。
     */
    virtual bool isMinimized() const;

    /**
     * 如果窗口当前打开且在屏幕上可见，则返回 true。
     */
    virtual bool isOpen() const;

    /* @inherit */
    bool isRepaintImmediately() const override;

    /**
     * 如果窗口允许调整大小，则返回 true。
     * 该值初始为 true，但可通过调用 setResizable(false) 更改。
     */
    virtual bool isResizable() const;

    /**
     * 如果窗口在屏幕上可见，则返回 true。
     */
    virtual bool isVisible() const;

    /**
     * 从给定名称的文件读取像素数据并加载到
     * 窗口的画布区域。
     * @throw 如果找不到文件或无法将其作为图像加载，则抛出 ErrorException
     */
    virtual void loadCanvasPixels(const std::string& filename);

    /**
     * 将窗口设为最大化状态，占据整个屏幕。
     */
    virtual void maximize();

    /**
     * 将窗口设为最小化（图标化）状态，
     * 通常表现为窗口被隐藏，只在任务栏中留下图标。
     */
    virtual void minimize();

    /**
     * 将窗口调整为其首选大小。
     * 窗口倾向于恰好能容纳交互控件的尺寸
     * 以其各自的首选大小放置在其中，而不会拉伸。
     * 调用 getPreferredSize 时，窗口会返回此大小。
     */
    virtual void pack();

    /**
     * 使当前线程暂停给定的毫秒数。
     * 等价于 sleep()。
     * @throw 如果 ms 为负，则抛出 ErrorException
     */
    virtual void pause(double ms);

    /**
     * 指示库记住窗口的 x/y 位置，以便如果
     * 将来打开另一个具有相同标题的窗口时，它将
     * 自动返回该位置。
     * @private
     */
    virtual void rememberPosition();

    /**
     * 从窗口中移除给定交互控件。
     * 无论将交互控件添加到哪个区域，此方法都有效。
     * 若在此容器中找不到给定交互控件，则不产生任何效果。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void remove(GInteractor* interactor);

    /**
     * 从窗口中移除给定交互控件。
     * 无论将交互控件添加到哪个区域，此方法都有效。
     * 若在此容器中找不到给定交互控件，则不产生任何效果。
     */
    virtual void remove(GInteractor& interactor);

    /**
     * 从此窗口的画布中移除给定图形对象，
     * 若它原本存在。
     * @throw 如果图形对象为空，则抛出 ErrorException
     */
    virtual void remove(GObject* obj);

    /**
     * 从此窗口的画布中移除给定图形对象，
     * 若它原本存在。
     */
    virtual void remove(GObject& obj);

    /**
     * 从此窗口删除点击监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeClickListener();

    /**
     * 从此窗口内给定区域移除给定交互控件。
     * 若在给定区域中找不到给定交互控件，则不产生任何效果。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void removeFromRegion(GInteractor* interactor, Region region);

    /**
     * 从此窗口内给定区域移除给定交互控件。
     * 若在给定区域中找不到给定交互控件，则不产生任何效果。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void removeFromRegion(GInteractor* interactor, const std::string& region);

    /**
     * 从此窗口内给定区域移除给定交互控件。
     * 若在给定区域中找不到给定交互控件，则不产生任何效果。
     */
    virtual void removeFromRegion(GInteractor& interactor, Region region);

    /**
     * 从此窗口内给定区域移除给定交互控件。
     * 若在给定区域中找不到给定交互控件，则不产生任何效果。
     */
    virtual void removeFromRegion(GInteractor& interactor, const std::string& region);

    /**
     * 从此窗口删除键盘监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeKeyListener();

    /**
     * 从此窗口删除菜单监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeMenuListener();

    /**
     * 从此窗口删除鼠标监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeMouseListener();

    /**
     * 从此窗口删除计时器监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeTimerListener();

    /**
     * 如果窗口有工具栏，则将其删除。
     */
    virtual void removeToolbar();

    /**
     * 从此窗口删除窗口监听器，使其不再
     * 在事件发生时调用它。
     */
    virtual void removeWindowListener();

    /**
     * 请求系统将键盘焦点分配给窗口，这会将
     * 将其置于顶层，并确保键盘事件传递给窗口。
     * 单击窗口会自动请求焦点。
     */
    virtual void requestFocus();

    /**
     * 将窗口设为普通状态，既不最小化也不最大化。
     */
    virtual void restore();

    /**
     * 将窗口图形画布的内容写入给定输出
     * 文件名。这会写入前景层中的所有形状，以及
     * 以及背景层中的所有像素。
     * @throw 如果文件无法保存，则抛出 ErrorException
     */
    virtual void saveCanvasPixels(const std::string& filename);

    /* @inherit */
    void setBackground(int color) override;

    /* @inherit */
    void setBackground(const std::string& color) override;

    /**
     * 调整窗口大小，使中央画布区域恰好占据
     * 给定的像素高度，而不改变其宽度。
     */
    virtual void setCanvasHeight(double height);

    /**
     * 调整窗口大小，使中央画布区域恰好占据
     * 给定像素宽度和高度。
     */
    virtual void setCanvasSize(double width, double height);

    /**
     * 调整窗口大小，使中央画布区域恰好占据
     * 给定像素宽度和高度。
     */
    virtual void setCanvasSize(const GDimension& size);

    /**
     * 调整窗口大小，使中央画布区域恰好占据
     * 给定的像素宽度，而不改变其高度。
     */
    virtual void setCanvasWidth(double width);

    /**
     * 在此窗口上设置鼠标监听器，以便在以下情况发生时调用它
     * 当鼠标在窗口画布上单击时。
     * 任何现有的单击监听器都会被替换。
     * 请注意，此方法并不是监听单个对象点击的方式
     * 窗口中的按钮和其他交互控件；若要这样做，请调用
     * 在这些交互控件上分别调用 setActionListener 和其他类似方法。
     */
    virtual void setClickListener(GEventListener func);

    /**
     * 在此窗口上设置鼠标监听器，以便在以下情况发生时调用它
     * 当鼠标在窗口画布上单击时。
     * 任何现有的单击监听器都会被替换。
     * 请注意，此方法并不是监听单个对象点击的方式
     * 窗口中的按钮和其他交互控件；若要这样做，请调用
     * 在这些交互控件上分别调用 setActionListener 和其他类似方法。
     */
    virtual void setClickListener(GEventListenerVoid func);

    /**
     * 设置窗口关闭时应发生的操作。
     */
    virtual void setCloseOperation(CloseOperation op);

    /**
     * 设置发生以下情况时库的 GUI 系统是否应关闭
     * 窗口已关闭。
     */
    virtual void setExitOnClose(bool exitOnClose);

    /**
     * 设置窗口总像素高度。
     */
    virtual void setHeight(double width);

    /**
     * 在此窗口上设置键盘监听器，以便在以下情况发生时调用它
     * 当用户按下任意键时。
     * 任何现有的按键监听器都会被替换。
     */
    virtual void setKeyListener(GEventListener func);

    /**
     * 在此窗口上设置键盘监听器，以便在以下情况发生时调用它
     * 当用户按下任意键时。
     * 任何现有的按键监听器都会被替换。
     */
    virtual void setKeyListener(GEventListenerVoid func);

    /**
     * 将窗口左上角在屏幕上的 x/y 位置设置为给定坐标。
     */
    virtual void setLocation(double x, double y);

    /**
     * 将窗口左上角在屏幕上的 x/y 位置设置为给定点。
     */
    virtual void setLocation(const GPoint& p);

    /**
     * 设置给定菜单中的给定项目是启用还是禁用。
     * @throw 如果菜单和/或项目不存在，则抛出 ErrorException
     */
    virtual void setMenuItemEnabled(const std::string& menu, const std::string& item, bool enabled);

    /**
     * 为此窗口设置菜单监听器，以便在以下情况下调用：
     * 菜单项被单击时，发送 ACTION_MENU 操作事件。
     * 任何现有的菜单监听器都会被替换。
     */
    virtual void setMenuListener(GEventListener func);

    /**
     * 为此窗口设置菜单监听器，以便在以下情况下调用：
     * 菜单项被单击时。
     * 任何现有的菜单监听器都会被替换。
     */
    virtual void setMenuListener(GEventListenerVoid func);

    /**
     * 在窗口画布上设置鼠标监听器，以便在以下情况发生时调用它
     * 当用户在画布上移动或单击鼠标时。
     * 任何现有的鼠标监听器都会被替换。
     */
    virtual void setMouseListener(GEventListener func);

    /**
     * 在窗口画布上设置鼠标监听器，以便在以下情况发生时调用它
     * 当用户在画布上移动或单击鼠标时。
     * 任何现有的鼠标监听器都会被替换。
     */
    virtual void setMouseListener(GEventListenerVoid func);

    /**
     * 设置给定区域中交互控件的水平对齐方式，该区域属于
     * 窗口。
     */
    virtual void setRegionAlignment(Region region, HorizontalAlignment halign);

    /**
     * 设置给定区域中交互控件的垂直对齐方式，该区域属于
     * 窗口。
     */
    virtual void setRegionAlignment(Region region, VerticalAlignment valign);

    /**
     * 设置给定对象中交互控件的水平和垂直对齐方式
     * 窗口的区域。
     */
    virtual void setRegionAlignment(Region region, HorizontalAlignment halign, VerticalAlignment valign);

    /**
     * 设置给定对象中交互控件的水平和/或垂直对齐方式
     * 窗口的区域。
     */
    virtual void setRegionAlignment(const std::string& region, const std::string& align);

    /**
     * 设置给定对象中交互控件的水平和垂直对齐方式
     * 窗口的区域。
     */
    virtual void setRegionAlignment(const std::string& region, const std::string& halign, const std::string& valign);

    /**
     * 设置给定区域中交互控件的水平对齐方式，该区域属于
     * 窗口。
     */
    virtual void setRegionHorizontalAlignment(Region region, HorizontalAlignment halign);

    /**
     * 设置给定区域中交互控件的水平对齐方式，该区域属于
     * 窗口。
     */
    virtual void setRegionHorizontalAlignment(const std::string& region, const std::string& halign);

    /**
     * 设置给定区域中交互控件的垂直对齐方式，该区域属于
     * 窗口。
     */
    virtual void setRegionVerticalAlignment(const std::string& region, const std::string& valign);

    /**
     * 设置给定区域中交互控件的垂直对齐方式，该区域属于
     * 窗口。
     */
    virtual void setRegionVerticalAlignment(Region region, VerticalAlignment valign);

    /**
     * 设置窗口是否允许调整大小。
     * 初始为 true。
     */
    virtual void setResizable(bool resizable);

    /**
     * 设置窗口总像素宽度和高度。
     * 请注意，此大小包含窗口标题栏、边框等由系统添加的部分
     * 由操作系统决定。
     * 若确实想在给定宽度和高度的像素区域上绘制形状，
     * 你应改用 setCanvasSize 方法。
     */
    virtual void setSize(double width, double height);

    /**
     * 设置窗口的像素宽度和高度。
     * 请注意，此大小包含窗口标题栏、边框等由系统添加的部分
     * 由操作系统决定。
     * 若确实想在给定宽度和高度的像素区域上绘制形状，
     * 你应改用 setCanvasSize 方法。
     */
    virtual void setSize(const GDimension& size);

    /**
     * 为此窗口设置菜单监听器，以便在以下情况下调用：
     * 当计时器延迟到期时，发送计时器事件。
     * 任何现有的计时器监听器都会被替换。
     */
    virtual void setTimerListener(double ms, GEventListener func);

    /**
     * 为此窗口设置菜单监听器，以便在以下情况下调用：
     * 当计时器延迟到期时，发送计时器事件。
     * 任何现有的计时器监听器都会被替换。
     */
    virtual void setTimerListener(double ms, GEventListenerVoid func);

    // TODO：setTimerListenerOnce？

    /**
     * 将窗口标题栏文本设置为给定字符串。
     * 等价于 setWindowTitle。
     */
    virtual void setTitle(const std::string& title);

    /**
     * 设置窗口是否在屏幕上可见。
     * 初始为 true，除非向窗口传入了 visible=false
     * 构造函数。
     */
    virtual void setVisible(bool visible);

    /**
     * 设置窗口总像素宽度。
     */
    virtual void setWidth(double width);

    /**
     * 将窗口设置为使用
     */
    virtual void setWindowIcon(const std::string& iconFile);

    /**
     * 在此窗口上设置窗口监听器，以便在以下情况发生时调用它
     * 当发生窗口事件时，例如调整大小或关闭窗口。
     * 任何现有的动作监听器都会被替换。
     */
    virtual void setWindowListener(GEventListener func);

    /**
     * 在此窗口上设置窗口监听器，以便在以下情况发生时调用它
     * 当发生窗口事件时，例如调整大小或关闭窗口。
     * 任何现有的动作监听器都会被替换。
     */
    virtual void setWindowListener(GEventListenerVoid func);

    /**
     * 将窗口标题栏文本设置为给定字符串。
     * 等价于 setWindowTitle。
     */
    virtual void setWindowTitle(const std::string& title);

    /**
     * 将窗口左侧在屏幕上的 x 位置设置为给定坐标。
     */
    virtual void setX(double x);

    /**
     * 将窗口顶部在屏幕上的 y 位置设置为给定坐标。
     */
    virtual void setY(double y);

    /**
     * 将窗口设置为在屏幕上可见。
     * 等价于 setVisible(true)。
     */
    virtual void show();

    /**
     * 使当前线程暂停给定的毫秒数。
     * 等价于 pause()。
     * @throw 如果 ms 为负，则抛出 ErrorException
     */
    virtual void sleep(double ms);

    /**
     * 在操作系统的 z 顺序中将窗口移到后面，
     * 位于占用相同像素的任何其他窗口之下。
     */
    virtual void toBack();

    /**
     * 在操作系统的 z 顺序中将窗口移到前面，
     * 位于占用相同像素的任何其他窗口之前。
     */
    virtual void toFront();

protected:
    /**
     * @private
     */
    virtual void processKeyPressEventInternal(QKeyEvent* event);

private:
    Q_DISABLE_COPY(GWindow)

    static _Internal_QMainWindow* _lastWindow;

    void ensureForwardTarget() override;
    void _init(double width, double height, bool visible);
    static Region stringToRegion(const std::string& regionStr);

    _Internal_QMainWindow* _iqmainwindow;
    GContainer* _contentPane;
    GCanvas* _canvas;
    bool _resizable;
    CloseOperation _closeOperation;
    Map<std::string, QMenu*> _menuMap;
    Map<std::string, QAction*> _menuActionMap;
    QToolBar* _toolbar;

    friend class GInteractor;
    friend class _Internal_QMainWindow;
};


// 用于兼容性的全局函数

/**
 * 将颜色名称转换为编码该颜色的整数
 * 颜色的红、绿、蓝分量。
 * 有关颜色的更多详细信息，请参阅 gcolor.h。
 */
int convertColorToRGB(const std::string& colorName);

/**
 * 将 <code>rgb</code> 值转换为以下形式的颜色名称：
 * 格式为 <code>"#rrggbb"</code>。其中 <code>rr</code>、
 * <code>gg</code> 和 <code>bb</code> 的值均为两位
 * 表示该颜色分量强度的十六进制数。
 * 有关颜色的更多详细信息，请参阅 gcolor.h。
 */
std::string convertRGBToColor(int rgb);

/**
 * 关闭所有图形窗口并退出应用程序，而不
 * 等待任何进一步的用户交互。
 */
void exitGraphics();

/**
 * 返回整个显示屏的高度。
 */
double getScreenHeight();

/**
 * 返回整个显示屏的宽度/高度。
 */
GDimension getScreenSize();

/**
 * 返回整个显示屏的宽度。
 */
double getScreenWidth();

/**
 * 暂停指定的毫秒数。此函数
 * 适用于运动原本会过快的动画。
 */
void pause(double milliseconds);

/**
 * 发出请求，更新最近创建的图形窗口。
 * 也可以直接调用窗口的 repaint() 方法重绘该窗口。
 */
void repaint();


/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QMainWindow : public QMainWindow {
    Q_OBJECT

public:
    _Internal_QMainWindow(GWindow* gwindow, QWidget* parent = nullptr);

    void changeEvent(QEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void timerEvent(QTimerEvent* event) override;
    virtual bool timerExists(int id = -1);
    virtual int timerStart(double ms);
    virtual void timerStop(int id = -1);

public slots:
    void handleMenuAction(const std::string& menu, const std::string& item);

private:
    GWindow* _gwindow;
    Set<int> _timerIDs;

    void processTimerEvent();

    friend class GWindow;
};

#endif // _gwindow_h
