/*
 * 文件：gcontainer.h
 * ------------------
 *
 * @author Marty Stepp
 * @version 2018/09/25
 * - 添加 getLayout 方法
 * @version 2018/09/19
 * - 添加 contains、regionContains 方法
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/29
 * - 初始版本
 */


#ifndef _gcontainer_h
#define _gcontainer_h

#include <QBoxLayout>
#include <QLayout>

#include "ginteractor.h"
#include "vector.h"

class _Internal_QContainer;   // 前向声明

/**
 * GContainer 是交互控件的逻辑分组。
 * 容器管理其中交互控件的位置和大小。
 * 此类与 Java 中容器的概念非常相似，表示为
 * 在 Swing 中由 JPanel 类实现。
 *
 * 容器具有用于指导如何放置交互控件的布局。
 * 支持的布局包括边框布局（将交互控件放在 N/S/W/E/Center），
 * 网格（按行和列排列交互控件）和流式布局（交互控件按
 * 单条水平线或垂直线）。
 *
 * 容器还使用类似 CSS 盒模型的“盒模型”，包含边距
 * 以及每个交互控件周围的内边距和相邻控件之间的间距：
 *
 * <pre>
    容器
 * +-------------------+
 * |       外边距       |
 * |  +---边框------+  |
 * |  |    内边距    |  |
 * |  |    内容     |  |
 * |  |    内边距    |  |
 * |  +-------------+  |
 * |       外边距       |
 * |                   |
 * |        间距        |
 * |                   |
 * |       外边距       |
 * |  +---边框------+  |
 * |  |    内边距    |  |
 * |  |    内容     |  |
 * |  |    内边距    |  |
 * |  +-------------+  |
 * |       外边距       |
 * |       ...         |
 * +-------------------+
 * </pre>
 */
class GContainer : public GInteractor {
public:
    /**
     * 每个交互控件周围的默认边距。
     */
    static const int MARGIN_DEFAULT;

    /**
     * 相邻交互控件之间的默认间距。
     */
    static const int SPACING_DEFAULT;

    /**
     * 容器可以使用的各种布局管理样式。
     */
    enum Layout {
        LAYOUT_NONE,
        LAYOUT_FLOW_HORIZONTAL,
        LAYOUT_FLOW_VERTICAL,
        LAYOUT_BORDER,
        LAYOUT_GRID
    };

    /**
     * 边框布局的五个区域。
     * 其他布局样式不使用。
     */
    enum Region {
        REGION_CENTER,
        REGION_EAST,
        REGION_NORTH,
        REGION_SOUTH,
        REGION_WEST
    };

    /**
     * 使用给定布局创建新容器。
     */
    GContainer(Layout layout = LAYOUT_FLOW_HORIZONTAL, QWidget* parent = nullptr);

    /**
     * 使用给定行数和列数创建新容器。
     * 用于网格布局。
     */
    GContainer(Layout layout, int rows, int cols, QWidget* parent = nullptr);

    /**
     * 释放容器内部分配的内存。
     */
    ~GContainer() override;

    /**
     * 将给定交互控件添加到此容器交互控件列表末尾。
     * 若容器使用网格布局，则将交互控件添加到下一个可用
     * 行/列。如果使用边框布局，则添加到中心区域。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void add(GInteractor* interactor);

    /**
     * 将给定交互控件添加到此容器交互控件列表末尾。
     * 若容器使用网格布局，则将交互控件添加到下一个可用
     * 行/列。如果使用边框布局，则添加到中心区域。
     */
    virtual void add(GInteractor& interactor);

    /**
     * 将给定交互控件添加到此容器的指定行和列，
     * 假定其使用网格布局。
     * 若传入 rowspan 和/或 colspan 参数，该项目会占据
     * 占据多行或多列的空间。
     * 若容器不使用网格布局，则等价于 add()。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void addToGrid(GInteractor* interactor, int row, int col, int rowspan = 1, int colspan = 1);

    /**
     * 将给定交互控件添加到此容器的指定行和列，
     * 假定其使用网格布局。
     * 若传入 rowspan 和/或 colspan 参数，该项目会占据
     * 占据多行或多列的空间。
     * 若容器不使用网格布局，则等价于 add()。
     */
    virtual void addToGrid(GInteractor& interactor, int row, int col, int rowspan = 1, int colspan = 1);

    /**
     * 将给定交互控件添加到此容器的给定区域，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则等价于 add()。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void addToRegion(GInteractor* interactor, Region region);

    /**
     * 将给定交互控件添加到此容器的给定区域，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则等价于 add()。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void addToRegion(GInteractor* interactor, const std::string& region = "Center");

    /**
     * 将给定交互控件添加到此容器的给定区域，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则等价于 add()。
     */
    virtual void addToRegion(GInteractor& interactor, Region region);

    /**
     * 将给定交互控件添加到此容器的给定区域，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则等价于 add()。
     */
    virtual void addToRegion(GInteractor& interactor, const std::string& region = "Center");

    /**
     * 从此容器删除所有交互控件。
     */
    virtual void clear();

    /**
     * 从此容器的给定区域移除所有交互控件，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则不产生任何效果。
     */
    virtual void clearRegion(Region region);

    /**
     * 从此容器的给定区域移除所有交互控件，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则不产生任何效果。
     */
    virtual void clearRegion(const std::string& region);

    /**
     * 如果在此容器中找到给定交互控件，则返回 true。
     * 如果交互控件为 null，则返回 false
     */
    virtual bool contains(GInteractor* interactor) const;

    /**
     * 如果在此容器中找到给定交互控件，则返回 true。
     */
    virtual bool contains(GInteractor& interactor) const;

    /**
     * 返回此容器内部所有子级或后代交互控件
     * 容器。它与 getInteractors 的区别在于，不仅返回
     * 不仅包括直接子项，还包括所有子容器中的孙项等。
     * 如果传入 type 参数，则只返回该类型的交互控件
     * （例如“GCheckBox”）。否则将返回所有交互控件。
     */
    virtual Vector<GInteractor*> getDescendents(const std::string& type = "") const;

    /**
     * 返回此容器中给定从 0 开始索引处的子交互控件。
     * @throw 如果索引越界，则抛出 ErrorException
     */
    virtual GInteractor* getInteractor(int i) const;

    /**
     * 返回此容器中所有子交互控件的向量。
     */
    virtual const Vector<GInteractor*>& getInteractors() const;

    /**
     * 返回此容器中的子交互控件数量。
     */
    virtual int getInteractorCount() const;

    /**
     * 返回给定对象中从 0 开始的指定索引处的子交互控件
     * 此容器中的区域，假定该容器使用边框布局。
     * 若容器不使用边界布局，则返回 nullptr。
     * @throw 如果索引越界，则抛出 ErrorException
     */
    virtual GInteractor* getInteractorByRegion(int i, Region region) const;

    /**
     * 返回给定对象中从 0 开始的指定索引处的子交互控件
     * 此容器中的区域，假定该容器使用边框布局。
     * 若容器不使用边界布局，则返回 nullptr。
     * @throw 如果索引越界，则抛出 ErrorException
     */
    virtual GInteractor* getInteractorByRegion(int i, const std::string& region = "Center") const;

    /**
     * 返回给定区域内子交互控件的数量
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则返回 0。
     */
    virtual int getInteractorCountByRegion(Region region) const;

    /**
     * 返回给定区域内子交互控件的数量
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则返回 0。
     */
    virtual int getInteractorCountByRegion(const std::string& region = "Center") const;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回此容器使用的布局类型。
     */
    virtual Layout getLayout() const;

    /**
     * 返回此容器中每个控件周围的像素边距。
     */
    virtual double getMargin() const;

    /**
     * 返回此容器内部的像素内边距。
     */
    virtual double getPadding() const;

    /**
     * 返回此容器底部的像素内边距。
     */
    virtual double getPaddingBottom() const;

    /**
     * 返回此容器左侧的像素内边距。
     */
    virtual double getPaddingLeft() const;

    /**
     * 返回此容器右侧的像素内边距。
     */
    virtual double getPaddingRight() const;

    /**
     * 返回此容器顶部的像素内边距。
     */
    virtual double getPaddingTop() const;

    /* @inherit */
    GDimension getPreferredSize() const override;

    /**
     * 返回此容器给定区域的像素高度，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则返回 0。
     */
    virtual double getRegionHeight(Region region) const;

    /**
     * 返回此容器给定区域的像素高度，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则返回 0。
     */
    virtual double getRegionHeight(const std::string& region) const;

    /**
     * 返回此容器给定区域的像素宽度和高度，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则返回 0。
     */
    virtual GDimension getRegionSize(Region region) const;

    /**
     * 返回此容器给定区域的像素宽度和高度，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则返回 0。
     */
    virtual GDimension getRegionSize(const std::string& region) const;

    /**
     * 返回此容器给定区域的像素宽度，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则返回 0。
     */
    virtual double getRegionWidth(Region region) const;

    /**
     * 返回此容器给定区域的像素宽度，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则返回 0。
     */
    virtual double getRegionWidth(const std::string& region) const;

    /**
     * 返回此容器中控件之间的像素间距。
     */
    virtual double getSpacing() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 将给定交互控件添加到此容器中给定索引之前。
     * @throw 如果索引越界或交互控件为空，则抛出 ErrorException
     */
    virtual void insert(int index, GInteractor* interactor);

    /**
     * 将给定交互控件添加到此容器中给定索引之前。
     * @throw 如果索引越界，则抛出 ErrorException
     */
    virtual void insert(int index, GInteractor& interactor);

    /**
     * 将给定交互控件添加到此容器内的给定布局区域
     * 紧邻给定索引之前。假定容器使用边界
     * 布局；若不是，则等价于 insert()。
     * @throw 如果索引越界或交互控件为空，则抛出 ErrorException
     */
    virtual void insertToRegion(int index, GInteractor* interactor, Region region);

    /**
     * 将给定交互控件添加到此容器内的给定布局区域
     * 紧邻给定索引之前。假定容器使用边界
     * 布局；若不是，则等价于 insert()。
     * @throw 如果索引越界或交互控件为空，则抛出 ErrorException
     */
    virtual void insertToRegion(int index, GInteractor* interactor, const std::string& region = "Center");

    /**
     * 将给定交互控件添加到此容器内的给定布局区域
     * 紧邻给定索引之前。假定容器使用边界
     * 布局；若不是，则等价于 insert()。
     * @throw 如果索引越界，则抛出 ErrorException
     */
    virtual void insertToRegion(int index, GInteractor& interactor, Region region);

    /**
     * 将给定交互控件添加到此容器内的给定布局区域
     * 紧邻给定索引之前。假定容器使用边界
     * 布局；若不是，则等价于 insert()。
     * @throw 如果索引越界，则抛出 ErrorException
     */
    virtual void insertToRegion(int index, GInteractor& interactor, const std::string& region = "Center");

    /**
     * 如果容器不包含任何交互控件，则返回 true。
     */
    virtual bool isEmpty() const;

    /**
     * 若在以下对象的给定区域中找到给定交互控件，则返回 true：
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则等价于 contains()。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual bool regionContains(GInteractor* interactor, Region region) const;

    /**
     * 若在以下对象的给定区域中找到给定交互控件，则返回 true：
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则等价于 contains()。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual bool regionContains(GInteractor* interactor, const std::string& region) const;

    /**
     * 若在以下对象的给定区域中找到给定交互控件，则返回 true：
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则等价于 contains()。
     */
    virtual bool regionContains(GInteractor& interactor, Region region) const;

    /**
     * 若在以下对象的给定区域中找到给定交互控件，则返回 true：
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则等价于 contains()。
     */
    virtual bool regionContains(GInteractor& interactor, const std::string& region) const;

    /**
     * 从此容器中移除给定交互控件。
     * 适用于任意布局。
     * 若在此容器中找不到给定交互控件，则不产生任何效果。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void remove(GInteractor* interactor);

    /**
     * 从此容器中移除给定交互控件。
     * 适用于任意布局。
     * 若在此容器中找不到给定交互控件，则不产生任何效果。
     */
    virtual void remove(GInteractor& interactor);

    /**
     * 从此容器删除给定从 0 开始索引处的子交互控件。
     * 适用于任意布局。
     * @throw 如果索引越界，则抛出 ErrorException
     */
    virtual void remove(int index);

    /**
     * 从此容器内给定区域移除给定交互控件，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则等价于 remove()。
     * 若在给定区域中找不到给定交互控件，则不产生任何效果。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void removeFromRegion(GInteractor* interactor, Region region);

    /**
     * 从此容器内给定区域移除给定交互控件，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则等价于 remove()。
     * 若在给定区域中找不到给定交互控件，则不产生任何效果。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void removeFromRegion(GInteractor* interactor, const std::string& region);

    /**
     * 从此容器内给定区域移除给定交互控件，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则等价于 remove()。
     * 若在给定区域中找不到给定交互控件，则不产生任何效果。
     */
    virtual void removeFromRegion(GInteractor& interactor, Region region);

    /**
     * 从此容器内给定区域移除给定交互控件，
     * 假定其使用边界布局。
     * 若容器不使用边界布局，则等价于 remove()。
     * 若在给定区域中找不到给定交互控件，则不产生任何效果。
     */
    virtual void removeFromRegion(GInteractor& interactor, const std::string& region);

    /**
     * 从给定对象中移除从 0 开始的指定索引处的子交互控件
     * 此容器中的区域，假定该容器使用边框布局。
     * 若容器不使用边界布局，则不产生任何效果。
     * 若在给定区域中找不到给定交互控件，则不产生任何效果。
     * @throw 如果索引越界，则抛出 ErrorException
     */
    virtual void removeFromRegion(int index, Region region);

    /**
     * 从给定对象中移除从 0 开始的指定索引处的子交互控件
     * 此容器中的区域，假定该容器使用边框布局。
     * 若容器不使用边界布局，则不产生任何效果。
     * 若在给定区域中找不到给定交互控件，则不产生任何效果。
     * @throw 如果索引越界，则抛出 ErrorException
     */
    virtual void removeFromRegion(int index, const std::string& region);

    /**
     * 设置此容器中交互控件的水平和垂直对齐方式。
     */
    virtual void setAlignment(HorizontalAlignment halign, VerticalAlignment valign);

    /**
     * 设置此容器中交互控件的水平对齐方式。
     */
    virtual void setHorizontalAlignment(HorizontalAlignment halign);

    /**
     * 设置此容器中交互控件周围的像素边距。
     */
    virtual void setMargin(double px);

    /**
     * 设置此容器中控件四周的内边距。
     */
    virtual void setPadding(double px);

    /**
     * 设置此容器中控件四周的内边距，
     * 垂直边与水平边使用不同的内边距。
     */
    virtual void setPadding(double topBottom, double leftRight);

    /**
     * 设置此容器中控件四周的内边距，
     * 四条边分别使用不同的内边距。
     */
    virtual void setPadding(double top, double right, double bottom, double left);

    /**
     * 设置此容器中交互控件的垂直对齐方式。
     */
    virtual void setVerticalAlignment(VerticalAlignment valign);

    /**
     * 设置给定区域中交互控件的水平对齐方式，该区域属于
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则设置以下对象的对齐方式：
     * 改用整个容器。
     */
    virtual void setRegionAlignment(Region region, HorizontalAlignment halign);

    /**
     * 设置给定区域中交互控件的垂直对齐方式，该区域属于
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则设置以下对象的对齐方式：
     * 改用整个容器。
     */
    virtual void setRegionAlignment(Region region, VerticalAlignment valign);

    /**
     * 设置给定区域中交互控件的水平和垂直对齐方式
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则设置以下对象的对齐方式：
     * 改用整个容器。
     */
    virtual void setRegionAlignment(Region region, HorizontalAlignment halign, VerticalAlignment valign);

    /**
     * 设置窗口给定区域中交互控件的水平和/或垂直对齐方式
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则设置以下对象的对齐方式：
     * 改用整个容器。
     */
    virtual void setRegionAlignment(const std::string& region, const std::string& align);

    /**
     * 设置给定区域中交互控件的水平和垂直对齐方式
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则设置以下对象的对齐方式：
     * 改用整个容器。
     */
    virtual void setRegionAlignment(const std::string& region, const std::string& halign, const std::string& valign);

    /**
     * 设置给定区域中交互控件的水平对齐方式，该区域属于
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则设置以下对象的对齐方式：
     * 改用整个容器。
     */
    virtual void setRegionHorizontalAlignment(Region region, HorizontalAlignment halign);

    /**
     * 设置给定区域中交互控件的水平对齐方式，该区域属于
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则设置以下对象的对齐方式：
     * 改用整个容器。
     */
    virtual void setRegionHorizontalAlignment(const std::string& region, const std::string& halign);

    /**
     * 设置给定区域中交互控件的垂直对齐方式，该区域属于
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则设置以下对象的对齐方式：
     * 改用整个容器。
     */
    virtual void setRegionVerticalAlignment(const std::string& region, const std::string& valign);

    /**
     * 设置给定区域中交互控件的垂直对齐方式，该区域属于
     * 此容器假定使用边界布局。
     * 若容器不使用边界布局，则设置以下对象的对齐方式：
     * 改用整个容器。
     */
    virtual void setRegionVerticalAlignment(Region region, VerticalAlignment valign);

    /**
     * 设置此容器中交互控件之间的间距。
     */
    virtual void setSpacing(double px);

private:
    Q_DISABLE_COPY(GContainer)

    _Internal_QContainer* _iqcontainer;
    Vector<GInteractor*> _interactors;
    Map<Region, Vector<GInteractor*>> _interactorsByRegion;
    Layout _layout;

    friend class _Internal_QContainer;
    friend class GWindow;

    static Region stringToRegion(const std::string& regionStr);
};


/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QContainer : public QWidget, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QContainer(GContainer* gcontainer, GContainer::Layout layoutType, QWidget* parent = nullptr);
    _Internal_QContainer(GContainer* gcontainer, int rows, int cols, QWidget* parent = nullptr);
    QSize sizeHint() const override;

private:
    GContainer* _gcontainer;
    GContainer::Layout _layoutType;
    HorizontalAlignment _halign;
    VerticalAlignment _valign;
    int _margin;
    int _spacing;
    // int _rows;
    int _cols;
    int _currentIndex;

    // N/S/W/E/C 的边框布局区域：
    // +------------------------+
    // |          北部           |
    // |------------------------|
    // |          中央           |
    // |+----------------------+|
    // || west | center | east ||
    // |+----------------------+|
    // |------------------------|
    // |          南部           |
    // +------------------------+
    // 尺寸/拉伸规则：
    // - N/S 水平扩展
    // - W/E 垂直扩展
    // - C 占据所有剩余空间
    // - 除 Center 控件外，每个控件均以其首选（“建议”）大小显示
    QVBoxLayout* _overallLayout;
    QHBoxLayout* _northLayout;
    QHBoxLayout* _southLayout;
    QVBoxLayout* _westLayout;
    QVBoxLayout* _eastLayout;
    QHBoxLayout* _centerLayout;
    QHBoxLayout* _middleLayout;
    Map<GContainer::Region, HorizontalAlignment> _halignMap;
    Map<GContainer::Region, VerticalAlignment> _valignMap;
    Map<GContainer::Region, bool> _regionStretchMap;

    virtual void add(QWidget* widget);
    virtual void addToGrid(QWidget* widget, int row, int col, int rowspan = 1, int colspan = 1);
    virtual void addToRegion(QWidget* widget, GContainer::Region region);
    virtual void clear();
    virtual void clearRegion(GContainer::Region region);
    virtual bool contains(QWidget* widget) const;
    void detach() override;
    virtual void fixAlignment(QWidget* widget, GContainer::Region region = GContainer::REGION_CENTER);
    virtual void fixMargin(QLayout* layout, bool hasStretch = false);
    virtual HorizontalAlignment getHorizontalAlignment() const;
    virtual VerticalAlignment getVerticalAlignment() const;
    virtual GContainer::Layout getLayoutType() const;
    virtual int getMargin() const;
    QSize getPreferredSize() const override;
    virtual QLayout* getQLayout() const;
    virtual int getSpacing() const;
    virtual void insert(int i, QWidget* widget);
    virtual void insertToRegion(int i, QWidget* widget, GContainer::Region region);
    virtual bool isRegionStretch(GContainer::Region region) const;
    virtual QLayout* layoutForRegion(GContainer::Region region) const;
    virtual bool regionContains(QWidget* widget, GContainer::Region region) const;
    virtual void remove(QWidget* widget);
    virtual void removeFromRegion(QWidget* widget, GContainer::Region region);
    virtual void remove(int i);
    virtual void removeFromRegion(int i, GContainer::Region region);
    virtual void setHorizontalAlignment(HorizontalAlignment halign);
    virtual void setLayoutType(GContainer::Layout layout);
    virtual void setMargin(int margin);
    virtual void setPadding(int padding);
    virtual void setPadding(int left, int top, int right, int bottom);
    virtual void setRegionAlignment(GContainer::Region region,
                                    HorizontalAlignment halign,
                                    VerticalAlignment valign);
    virtual void setRegionHorizontalAlignment(GContainer::Region region,
                                              HorizontalAlignment halign);
    virtual void setRegionStretch(GContainer::Region region, bool stretch = true);
    virtual void setRegionVerticalAlignment(GContainer::Region region,
                                            VerticalAlignment valign);
    virtual void setSpacing(int spacing);
    virtual void setVerticalAlignment(VerticalAlignment valign);

    friend class GContainer;
};

#endif // _gcontainer_h
