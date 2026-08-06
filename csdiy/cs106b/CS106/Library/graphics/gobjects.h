/*
 * 文件：gobjects.h
 * ----------------
 * 此文件导出一个基于
 * 为 ACM Java Graphics 开发的模型。
 * <include src="pictures/ClassHierarchies/GObjectHierarchy-h.html">
 *
 * @author Marty Stepp
 * @version 2019/05/05
 * - 添加可预测的 GLine 点顺序
 * @version 2019/04/23
 * - 修复 Windows 上因 istream 更改导致的从文件加载 GImage 问题
 * @version 2019/03/07
 * - 添加直接从 istream 加载 GImage 的支持（htiek）
 * @version 2018/09/14
 * - 添加不透明度支持
 * - 添加 GCanvas 到 GImage 的转换支持
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gobjects.h，以替代 Java 版本
 * @version 2018/06/30
 * - 初始版本
 */


#ifndef _gobjects_h
#define _gobjects_h

#include <initializer_list>
#include <iostream>
#include <QFont>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QWidget>

#include "gtypes.h"
#include "vector.h"

class GCanvas;
class GCompound;
class GDiffImage;

/**
 * 此类是所有可
 * 显示在图形窗口上。类 <code>GObject</code>
 * 其本身是一个<b><i>抽象类</i></b>，这意味着你不能
 * 不允许直接构造 <code>GObject</code>，而必须
 * 构造其中一个具体子类。
 * <include src="pictures/ClassHierarchies/GObjectHierarchy.html">
 *
 * 大多数图形方法接受指向 <code>GObject</code> 的指针
 * 而不是 <code>GObject</code> 本身。使用以下功能的应用程序
 * 因此，<code>GObject</code> 指针使用箭头运算符
 * 使用 (<code>-&gt;</code>) 将方法应用到对象指针。
 * 有关 <code>GObject</code> 类用法示例，请参阅
 * 各个子类的说明。
 */
class GObject {
public:
    /**
     * 可用于各种形状周围轮廓的样式。
     * 对 GObject 调用 setLineStyle，并传入这些值之一。
     */
    enum LineStyle {
        LINE_NONE,
        LINE_SOLID,
        LINE_DASH,
        LINE_DOT,
        LINE_DASH_DOT,
        LINE_DASH_DOT_DOT
    };

    /**
     * 释放对象的存储空间。
     */
    virtual ~GObject();

    /**
     * 若指定点位于对象内部，则返回 <code>true</code>。
     */
    virtual bool contains(double x, double y) const;

    /**
     * 若指定点位于对象内部，则返回 <code>true</code>。
     */
    virtual bool contains(const GPoint& pt) const;

    /**
     * 将此对象绘制到给定表面。
     * 每个 GObject 子类都必须重写此方法。
     * @private
     */
    virtual void draw(QPainter* painter) = 0;

    /**
     * 返回对象右下角的 x/y 坐标。
     */
    virtual GPoint getBottomRightLocation() const;

    /**
     * 返回对象底部的 <i>y</i> 坐标。
     * 等价于顶部 y 坐标加对象高度。
     */
    virtual double getBottomY() const;

    /**
     * 返回此对象的边界框，其定义为
     * 覆盖图形所绘制全部内容的最小矩形。
     * 此矩形的坐标不一定与以下对象的位置匹配：
     * 由 <code>getLocation</code> 返回。给定一个 <code>GText</code>
     * 对象，例如 <code>getLocation</code> 返回坐标
     * 字符串开始处的基线点；
     * 相比之下，<code>getBounds</code> 方法返回一个矩形，该矩形
     * 覆盖字符串占据的整个窗口区域。
     */
    virtual GRectangle getBounds() const;

    /**
     * 返回对象中心的 x/y 坐标。
     * 等价于左上角加对象尺寸的一半。
     */
    virtual GPoint getCenterLocation() const;

    /**
     * 返回对象中心的 <i>x</i> 坐标。
     * 等价于左上角加对象宽度的一半。
     */
    virtual double getCenterX() const;

    /**
     * 返回对象中心的 <i>y</i> 坐标。
     * 等价于左上角加对象高度的一半。
     */
    virtual double getCenterY() const;

    /**
     * 返回用于显示此对象的颜色。此颜色
     * 始终以 <code>"#rrggbb"</code> 形式的字符串返回，
     * 其中 <code>rr</code>、<code>gg</code> 和 <code>bb</code> 是
     * 颜色的红、绿、蓝分量，表示为
     * 两位十六进制值。
     */
    virtual std::string getColor() const;

    /**
     * 返回用于显示此对象填充区域的颜色。
     * 如果尚未设置，则返回空字符串。
     */
    virtual std::string getFillColor() const;

    /**
     * 返回此对象的高度，它与以下高度相同
     * 其边界框。
     */
    virtual double getHeight() const;

    /**
     * 返回对象的线型，例如实线或虚线。
     */
    virtual LineStyle getLineStyle() const;

    /**
     * 返回绘制此对象所用线条的宽度。
     * @return 默认值为 1
     */
    virtual double getLineWidth() const;

    /**
     * 返回对象左上角的位置。
     */
    virtual GPoint getLocation() const;

    /**
     * 返回此对象显示时的不透明度（非透明度），范围从 0.0
     * （完全透明）到 1.0（完全不透明，默认）。
     */
    virtual double getOpacity() const;

    /**
     * 返回指向包含此对象的 <code>GCompound</code> 的指针
     * 对象。每个 <code>GWindow</code> 初始化时都包含一个
     * 与窗口对齐的 <code>GCompound</code>。添加
     * 向窗口添加对象会将它们添加到该 <code>GCompound</code>，
     * 这意味着添加到窗口的每个对象都有父对象。
     * 对顶层 <code>GCompound</code> 调用 <code>getParent</code>
     * 返回 <code>nullptr</code>。
     */
    virtual GCompound* getParent() const;

    /**
     * 返回对象右侧的 <i>x</i> 坐标。
     * 等价于左侧 x 坐标加对象宽度。
     */
    virtual double getRightX() const;

    /**
     * 以 <code>GDimension</code> 返回对象大小。
     */
    virtual GDimension getSize() const;

    /**
     * 以字符串返回对象类型，例如
     * <code>"GOval"</code> 或 <code>"GRect"</code>。
     * 每个 GObject 子类型都必须重写此方法。
     */
    virtual std::string getType() const = 0;

    /**
     * 返回此对象的宽度，它等于以下对象的宽度
     * 边界框。
     */
    virtual double getWidth() const;

    /**
     * 返回对象最左侧的 <i>x</i> 坐标。
     */
    virtual double getX() const;

    /**
     * 返回对象最上方的 <i>y</i> 坐标。
     */
    virtual double getY() const;

    /**
     * 返回是否应全局对图形对象使用抗锯齿。
     * 默认开启。
     */
    static bool isAntiAliasing();

    /**
     * 如果对象已填充颜色，则返回 <code>true</code>。
     */
    virtual bool isFilled() const;

    /**
     * 如果此对象已被变换，则返回 <code>true</code>
     * 通过调用 rotate() 或 scale() 等方法。
     * 某些操作（例如 setSize）在以下情况后无法执行：
     * 图形对象已被变换。
     */
    virtual bool isTransformed() const;

    /**
     * 如果此对象在屏幕上可见，则返回 <code>true</code>。
     */
    virtual bool isVisible() const;

    /**
     * 使用位移量在屏幕上移动对象
     * <code>dx</code> 和 <code>dy</code>。
     */
    virtual void move(double dx, double dy);

    /**
     * 指示对象在屏幕上重绘自身。
     */
    virtual void repaint();

    /**
     * 撤销此前对该对象进行的所有缩放/旋转变换。
     */
    virtual void resetTransform();

    /**
     * 将对象旋转 <code>theta</code> 度来变换它
     * 绕其原点逆时针方向。
     * 对图形对象调用此方法后，<code>isTransformed</code>
     * 会为该对象返回 <code>true</code>，除非随后调用
     * 对其调用 <code>resetTransform</code>。
     */
    virtual void rotate(double theta);

    /**
     * 按指定缩放系数缩放对象。此形式
     * 在两个维度上按 <code>sf</code> 缩放对象，使得
     * 调用 <code>gobj->scale(2);</code> 会将对象大小加倍。
     * 对图形对象调用此方法后，<code>isTransformed</code>
     * 会为该对象返回 <code>true</code>，除非随后调用
     * 对其调用 <code>resetTransform</code>。
     */
    virtual void scale(double sf);

    /**
     * 按指定缩放系数缩放对象。例如，
     * <code>gobj->scale(2, 2);</code> 将对象大小加倍。
     * 此形式分别对 <i>x</i> 和 <i>y</i> 应用独立缩放因子
     * 尺寸。
     * 对图形对象调用此方法后，<code>isTransformed</code>
     * 会为该对象返回 <code>true</code>，除非随后调用
     * 对其调用 <code>resetTransform</code>。
     */
    virtual void scale(double sx, double sy);

    /**
     * 在 <i>z</i> 维度中将此对象向后移动一步。
     * 如果它已位于栈的末尾，则不执行任何操作。
     */
    void sendBackward();

    /**
     * 在 <i>z</i> 维度中将此对象向前移动一步。
     * 如果它已位于栈的开头，则不执行任何操作。
     */
    void sendForward();

    /**
     * 在 <i>z</i> 维度中将此对象移到显示区域最后面。
     * 将其移到后面后，该对象会看起来位于其他对象之后
     * 显示区域中的图形对象，并且可能被其他对象遮挡
     * 在前面。
     */
    void sendToBack();

    /**
     * 在 <i>z</i> 维度中将此对象移到显示区域最前面。
     * 将其移到前面后，该对象会看起来位于其他对象之上
     * 显示区域中的其他图形对象，并可能遮住任何
     * 位于更后方。
     */
    void sendToFront();

    /**
     * 全局开启/关闭抗锯齿功能，用于平滑
     * 屏幕形状的边缘。默认开启。
     * 调用时不会重绘任何屏幕对象；你必须自行重绘。
     */
    static void setAntiAliasing(bool value);

    /**
     * 将此对象的边界更改为指定值。
     */
    virtual void setBounds(double x, double y, double width, double height);

    /**
     * 将此对象的边界更改为指定矩形。
     */
    virtual void setBounds(const GRectangle& size);

    /**
     * 设置此对象底部 y 坐标的位置。
     */
    virtual void setBottomY(double y);

    /**
     * 设置此对象最右侧 x 坐标的位置。
     */
    virtual void setRightX(double x);

    /**
     * 设置此对象右下角的位置。
     */
    virtual void setBottomRightLocation(double x, double y);

    /**
     * 设置此对象右下角的位置。
     */
    virtual void setBottomRightLocation(const GPoint& pt);

    /**
     * 设置此对象中心的 x 坐标。
     */
    virtual void setCenterX(double x);

    /**
     * 设置此对象中心的 y 坐标。
     */
    virtual void setCenterY(double y);

    /**
     * 设置此对象中心的位置。
     */
    virtual void setCenterLocation(double x, double y);

    /**
     * 设置此对象中心的位置。
     */
    virtual void setCenterLocation(const GPoint& pt);

    /**
     * 设置显示此对象所用的颜色。
     * 有关指定颜色的方法，请参阅 gcolor.h。
     *
     * 等价于 setForeground。
     *
     * @param r 0-255 范围内的红色分量
     * @param g 0-255 范围内的绿色分量
     * @param b 0-255 范围内的蓝色分量
     */
    virtual void setColor(int r, int g, int b);

    /**
     * 设置显示此对象所用的颜色。
     * 有关指定颜色的方法，请参阅 gcolor.h。
     *
     * 等价于 setForeground。
     *
     * @param rgb RGB 整数值，例如 0x7700ff
     */
    virtual void setColor(int rgb);

    /**
     * 设置显示此对象所用的颜色。
     * 有关指定颜色的方法，请参阅 gcolor.h。
     *
     * 等价于 setForeground。
     *
     * @param color 颜色字符串，例如 "#7700ff" 或 "purple"
     */
    virtual void setColor(const std::string& color);

    /**
     * 设置此对象填充区域的显示颜色（若存在）。
     * 作为副作用，将此对象设为填充状态（setFilled(true)）。
     * 有关指定颜色的方法，请参阅 gcolor.h。
     * 若传入空字符串，则将 filled 设为 false。
     *
     * @param r 0-255 范围内的红色分量
     * @param g 0-255 范围内的绿色分量
     * @param b 0-255 范围内的蓝色分量
     */
    virtual void setFillColor(int r, int g, int b);

    /**
     * 设置此对象填充区域的显示颜色（若存在）。
     * 作为副作用，将此对象设为填充状态（setFilled(true)）。
     * 有关指定颜色的方法，请参阅 gcolor.h。
     *
     * @param rgb RGB 整数值，例如 0x7700ff
     */
    virtual void setFillColor(int rgb);

    /**
     * 设置此对象填充区域的显示颜色（若存在）。
     * 作为副作用，将此对象设为填充状态（setFilled(true)）。
     * 有关指定颜色的方法，请参阅 gcolor.h。
     * 若传入空字符串，则将 filled 设为 false。
     *
     * @param color 颜色字符串，例如 "#7700ff" 或 "purple"
     */
    virtual void setFillColor(const std::string& color);

    /**
     * 设置对象的填充状态，其中 <code>false</code> 表示
     * false 表示仅描边，<code>true</code> 表示填充。
     */
    virtual void setFilled(bool flag);

    /**
     * 按以下内容更改显示对象所用的字体：
     * 给定的 Qt 字体。
     * 有关如何指定字体的更多详细信息，请参阅 gfont.h。
     */
    virtual void setFont(const QFont& font);

    /**
     * 按以下内容更改显示对象所用的字体：
     * 字符串 <code>font</code>，其格式如下：
     *
     * <pre>
     * "字体族-样式-大小"
     * </pre>
     *
     * 其中 <code>style</code> 和 <code>size</code> 都是可选的。
     * 若缺少任一元素，或以星号指定，
     * 保留现有值。
     * 有关如何指定字体的更多详细信息，请参阅 gfont.h。
     */
    virtual void setFont(const std::string& font);

    /**
     * 设置显示此对象所用的颜色。
     * 有关指定颜色的方法，请参阅 gcolor.h。
     *
     * 等价于 setColor。
     *
     * @param r 0-255 范围内的红色分量
     * @param g 0-255 范围内的绿色分量
     * @param b 0-255 范围内的蓝色分量
     */
    virtual void setForeground(int r, int g, int b);

    /**
     * 设置显示此对象所用的颜色。
     * 有关指定颜色的方法，请参阅 gcolor.h。
     *
     * 等价于 setColor。
     *
     * @param rgb RGB 整数值，例如 0x7700ff
     */
    virtual void setForeground(int rgb);

    /**
     * 设置显示此对象所用的颜色。
     * 有关指定颜色的方法，请参阅 gcolor.h。
     *
     * 等价于 setColor。
     *
     * @param color 颜色字符串，例如 "#7700ff" 或 "purple"
     */
    virtual void setForeground(const std::string& color);

    /**
     * 将此对象的高度更改为指定高度
     * 而不改变其宽度。
     */
    virtual void setHeight(double height);

    /**
     * 设置对象的线型，例如实线（GObject::LINE_SOLID）或虚线
     * （GObject::LINE_DASH）。
     */
    virtual void setLineStyle(LineStyle lineStyle);

    /**
     * 设置绘制此对象所用线条的宽度。
     * 默认线宽为 1。
     */
    virtual void setLineWidth(double lineWidth);

    /**
     * 将此对象左上角的位置设置为
     * 指定坐标。
     */
    virtual void setLocation(double x, double y);

    /**
     * 将此对象左上角的位置设置为
     * 指定点。
     */
    virtual void setLocation(const GPoint& pt);

    /**
     * 设置此对象显示时的不透明度（非透明度），范围从 0.0
     * （完全透明）到 1.0（完全不透明，默认）。
     * @throw 如果 opacity 超出 [0.0, 1.0] 范围，则抛出 ErrorException
     */
    virtual void setOpacity(double opacity);

    /**
     * 将此对象大小更改为指定宽度和高度。
     */
    virtual void setSize(double width, double height);

    /**
     * 将此对象大小更改为指定宽度和高度。
     */
    virtual void setSize(const GDimension& size);

    /**
     * 设置此对象是否可见。
     * 图形对象创建时默认可见。
     */
    virtual void setVisible(bool flag);

    /**
     * 将此对象的宽度更改为指定宽度
     * 而不改变其高度。
     */
    virtual void setWidth(double width);

    /**
     * 设置此对象左侧的 x 位置。
     */
    virtual void setX(double x);

    /**
     * 设置此对象顶部的 y 位置。
     */
    virtual void setY(double y);

    /**
     * 返回对象的可打印表示形式。
     */
    virtual std::string toString() const;

// 私有部分
private:
    // 禁止对象之间赋值
    const GObject& operator =(const GObject&) {
        return *this;
    }

    // 禁止复制构造
    GObject(const GObject&) {
        // 空
    }

    // 是否对图形对象启用抗锯齿；默认为 true
    static bool _sAntiAliasing;

    /* 实例变量 */
protected:
    double _x;                       // 原点的 x 坐标
    double _y;                       // 原点的 y 坐标
    double _width;                   // 边界矩形的宽度
    double _height;                  // 边界矩形的高度
    double _lineWidth;               // 线条的像素宽度
    double _opacity;                 // 0.0（透明）- 1.0（不透明，默认）
    LineStyle _lineStyle;            // 线型，例如实线或虚线
    std::string _color;              // 对象的颜色
    int _colorInt;
    std::string _fillColor;          // 用于填充对象的颜色
    int _fillColorInt;
    std::string _font;               // 标签的字体字符串
    bool _fillFlag;                  // 表示对象是否已填充
    bool _visible;                   // 表示对象是否可见
    bool _transformed;               // 表示对象是否已变换
    GCompound* _parent;             // 指向父节点的指针
    QPen _pen;                       // 用于轮廓
    QBrush _brush;                   // 用于填充
    QTransform _transform;           // 用于变换（旋转、缩放）

protected:
    /**
     * 在给定位置构造图形对象。
     * @private
     */
    GObject(double x = 0, double y = 0, double width = 0, double height = 0);

    /**
     * 初始化 Qt 画刷和画笔，以使用以下设置绘制此对象
     * 给定的绘制器。
     * @private
     */
    virtual void initializeBrushAndPen(QPainter* painter = nullptr);

    /**
     * 将我们的线型枚举转换为用于绘制的 Qt 画笔样式。
     * @private
     */
    static Qt::PenStyle toQtPenStyle(LineStyle lineStyle);

    /**
     * 返回包含有关此对象的任何额外唯一信息的字符串
     * 图形对象的类型。
     */
    virtual std::string toStringExtra() const;

    friend class GArc;
    friend class GCompound;
    friend class GImage;
    friend class GInteractor;
    friend class GLine;
    friend class GOval;
    friend class GPolygon;
    friend class GRect;
    friend class GRoundRect;
    friend class GText;
};

/**
 * 此图形对象子类表示一段椭圆弧。
 * 弧由以下参数指定：
 *
 * <p><ul>
 *   <li>边界矩形的坐标（<code>x</code>，
 *       <code>y</code>、<code>width</code>、<code>height</code>）
 *   <li>弧开始的角度（<code>start</code>）
 *   <li>弧覆盖的角度数（<code>sweep</code>）
 * </ul>
 *
 * <p><code>GArc</code> 描述中的所有角度均以以下方式测量：
 * 从 +<i>x</i> 轴逆时针移动的角度。负数
 * <code>start</code> 或 <code>sweep</code> 的值表示
 * 顺时针方向的运动。
 * <include src="pictures/GObjectDiagrams/GArcGeometry.html">
 */
class GArc : public GObject {
public:
    /**
     * 创建由椭圆弧组成的新 <code>GArc</code> 对象。
     * 此形式创建一个原点为 (0, 0) 的 <code>GArc</code>。
     */
    GArc(double width = 0, double height = 0, double start = 0, double sweep = 0);

    /**
     * 创建由椭圆弧组成的新 <code>GArc</code> 对象。
     * 此形式创建一个 <code>GArc</code>，其原点为
     * （<code>x</code>，<code>y</code>）。
     */
    GArc(double x, double y, double width, double height, double start, double sweep);

    /* @inherit */
    bool contains(double x, double y) const override;

    /**
     * 使用给定 Qt 画笔在屏幕上绘制此弧。
     * @private
     */
    void draw(QPainter* painter) override;

    /* @inherit */
    GRectangle getBounds() const override;

    /**
     * 返回弧结束处的点。
     */
    virtual GPoint getEndPoint() const;

    /**
     * 返回用于框定弧的矩形边界。
     */
    virtual GRectangle getFrameRectangle() const;

    /**
     * 返回此弧的起始角度（度）。
     */
    virtual double getStartAngle() const;

    /**
     * 返回弧开始处的点。
     */
    virtual GPoint getStartPoint() const;

    /**
     * 返回此弧的扫过角度（度）。
     */
    virtual double getSweepAngle() const;

    /* @inherit */
    std::string getType() const override;

    /**
     * 更改用于框定弧的矩形边界。
     */
    virtual void setFrameRectangle(const GRectangle& rect);

    /**
     * 更改用于框定弧的矩形边界。
     */
    virtual void setFrameRectangle(double x, double y, double width, double height);

    /**
     * 设置此弧的起始角度（度）。
     */
    virtual void setStartAngle(double start);

    /**
     * 设置此弧的扫过角度（度）。
     */
    virtual void setSweepAngle(double start);

    /* @inherit */
    std::string toStringExtra() const override;

private:
    virtual bool containsAngle(double theta) const;
    virtual GPoint getArcPoint(double theta) const;

    /* 实例变量 */
    double _start;                   /* 弧的起始角度       */
    double _sweep;                   /* 弧跨越的角度数   */
};

/**
 * 此图形对象子类由一组其他
 * 图形对象。组装完成后，可以操作内部对象
 * 作为一个整体。复合对象记录自身位置，所有项目
 * 其中的内容相对于该位置绘制。
 */
class GCompound : public GObject {
public:
    /**
     * 创建不含内部组件的复合对象。
     */
    GCompound();

    /**
     * 若该图形对象尚未存在于复合对象中，则将其添加到复合对象
     * 已存在于复合对象中。
     * 若对象已存储在此复合对象中，则不产生任何效果。
     * @throw 如果对象为空，则抛出 ErrorException
     */
    virtual void add(GObject* gobj);

    /**
     * 若该图形对象尚未存在于复合对象中，则将其添加到复合对象
     * 已存在于复合对象中。
     * 此形式会先将对象移动到点 (<code>x</code>, <code>y</code>)。
     * 若对象已存储在此复合对象中，则不产生任何效果。
     * @throw 如果对象为空，则抛出 ErrorException
     */
    virtual void add(GObject* gobj, double x, double y);

    /**
     * 向复合对象添加新的图形对象。
     */
    virtual void add(GObject& gobj);

    /**
     * 若该图形对象尚未存在于复合对象中，则将其添加到复合对象
     * 已存在于复合对象中。
     * 此形式会先将对象移动到点 (<code>x</code>, <code>y</code>)。
     * 若对象已存储在此复合对象中，则不产生任何效果。
     */
    virtual void add(GObject& gobj, double x, double y);

    /**
     * 移除复合对象中的所有图形对象。
     * 等价于 removeAll。
     */
    virtual void clear();

    /**
     * 仅在 compound 需要重绘时才重绘
     * （如果其任何内容已发生变化）。
     */
    virtual void conditionalRepaint();

    /**
     * 仅当复合对象需要重绘时，才重绘给定矩形区域
     * 需要重绘（如果其任何内容已发生变化）。
     */
    virtual void conditionalRepaintRegion(int x, int y, int width, int height);

    /**
     * 仅当复合对象需要重绘时，才重绘给定矩形区域
     * 需要重绘（如果其任何内容已发生变化）。
     */
    virtual void conditionalRepaintRegion(const GRectangle& bounds);

    /* @inherit */
   bool contains(double x, double y) const override;

    /**
     * 使用给定画笔绘制此复合对象中存储的所有对象。
     * @private
     */
    void draw(QPainter* painter) override;

    /* @inherit */
    GRectangle getBounds() const override;

    /**
     * 返回指向指定索引处图形对象的指针，
     * 在 <i>z</i> 维度中从后向前编号。
     * @throw 如果索引超出范围，则抛出 ErrorException
     */
    virtual GObject* getElement(int index) const;

    /**
     * 返回指向包含给定位置的第一个图形对象的指针
     * (x, y) 点；如果此复合对象中没有对象接触该点，则返回空指针。
     */
    virtual GObject* getElementAt(double x, double y) const;

    /**
     * 返回 compound 中存储的图形对象数量。
     */
    virtual int getElementCount() const;

    /* @inherit */
    std::string getType() const override;

    /**
     * 返回与此 compound 关联的 Qt 控件；若没有则返回空指针
     * 若此复合对象未与任何控件关联。
     * 最初，compound 不与任何控件关联，直到
     * 调用 setWidget 方法。
     * 客户端通常无需使用此方法。
     * @private
     */
    virtual QWidget* getWidget() const;

    /**
     * 返回 compound 在其内容变化时是否自动重绘自身
     * 内容发生变化。
     */
    virtual bool isAutoRepaint() const;

    /**
     * 如果 compound 不包含任何图形对象，则返回 true。
     */
    virtual bool isEmpty() const;

    /**
     * 从复合对象中移除指定对象。
     * @throw 如果对象为空，则抛出 ErrorException
     */
    virtual void remove(GObject* gobj);

    /**
     * 从复合对象中移除指定对象。
     */
    virtual void remove(GObject& gobj);

    /**
     * 移除复合对象中的所有图形对象。
     * 等价于 clear。
     */
    virtual void removeAll();

    /**
     * 指示 compound 重绘其所有图形对象。
     */
    void repaint() override;

    /**
     * 指示复合对象重绘其内部给定矩形区域，
     * 包括接触该区域的任何图形对象。
     */
    virtual void repaintRegion(int x, int y, int width, int height);

    /**
     * 指示复合对象重绘其内部给定矩形区域，
     * 包括接触该区域的任何图形对象。
     */
    virtual void repaintRegion(const GRectangle& bounds);

    /**
     * 设置 compound 在其内容变化时是否自动重绘自身
     * 内容发生变化。
     */
    virtual void setAutoRepaint(bool autoRepaint);

    /**
     * 设置与此 compound 关联的 Qt 控件，或设置为空指针
     * 若此复合对象未与任何控件关联。
     * 最初，compound 不与任何控件关联，直到此
     * 调用 Widget 方法。
     * 客户端通常无需使用此方法。
     * @private
     */
    virtual void setWidget(QWidget* widget);

    /* @inherit */
    std::string toString() const override;

private:
    // 用于在 z 顺序中移动对象的方法
    void sendBackward(GObject* gobj);
    void sendForward(GObject* gobj);
    void sendToBack(GObject* gobj);
    void sendToFront(GObject* gobj);
    virtual int findGObject(GObject* gobj) const;
    virtual void removeAt(int index);

    // 实例变量
    Vector<GObject*> _contents;
    QWidget* _widget = nullptr;    // 包含此复合对象的控件
    bool _autoRepaint;   // 任何更改时自动重绘；默认为 true

    friend class GObject;
};

/**
 * 此图形对象子类表示来自文件的图像。
 */
class GImage : public GObject {
public:
    /**
     * 通过从指定文件加载图像构造新图像。
     * 默认情况下，图像左上角位于原点，
     * 但可以传入坐标，将其移动到该点
     * （<code>x</code>，<code>y</code>）。
     * @throw 如果找不到或无法加载给定文件，则抛出 ErrorException
     *        作为有效图像文件
     */
    GImage(const std::string& filename = "", double x = 0, double y = 0);

    /**
     * 通过从指定输入流加载图像构造新图像。
     * 默认情况下，图像左上角位于原点，
     * 但可以传入坐标，将其移动到该点
     * （<code>x</code>，<code>y</code>）。
     * @throw 如果找不到或无法加载给定文件，则抛出 ErrorException
     *        作为有效图像文件
     */
    GImage(std::istream& source, double x = 0, double y = 0);

    /**
     * 创建给定宽度和高度的空白 GImage。
     * GCanvas 转换为图像时调用。
     */
    GImage(double width, double height);

    /**
     * 释放图像内部分配的内存。
     */
    virtual ~GImage();



    /**
     * 使用给定 Qt 画笔在屏幕上绘制此图像。
     * @private
     */
    void draw(QPainter* painter) override;

    /**
     * 返回用于加载图像的文件名，
     * 与传递给构造函数的内容相同。
     */
    virtual std::string getFileName() const;

    /**
     * 以 RGB 整数返回给定 x/y 位置处像素的颜色。
     * @throw 如果 x/y 超出范围，则抛出 ErrorException
     */
    virtual int getPixel(int x, int y) const;

    /* @inherit */
    std::string getType() const override;

    /**
     * 将给定 x/y 位置的像素设置为给定颜色，
     * 表示为 RGB 整数。
     * @throw 如果 x/y 超出范围，则抛出 ErrorException
     */
    virtual void setPixel(int x, int y, int rgb);

    /* @inherit */
    std::string toStringExtra() const override;

protected:
    /**
     * 创建包装给定 Qt 图像的 GImage。
     * GCanvas 转换画布为图像时调用。
     */
    GImage(QImage* qimage);

    /**
     * 返回所包装的内部 Qt QImage 对象。
     */
    QImage* getQImage() const;

private:
    /**
     * 从给定文件读取图像像素内容。
     * @return 加载成功时为 true，加载失败时为 false
     */
    bool load(const std::string& filename);

    /**
     * 从给定流读取图像像素内容。
     * @return 加载成功时为 true，加载失败时为 false
     */
    bool loadFromStream(std::istream& input);

    std::string _filename;
    QImage* _qimage;

    friend class GCanvas;
    friend class GDiffImage;
};

/**
 * 此图形对象子类表示一条线段。
 */
class GLine : public GObject {
public:
    /**
     * 根据端点构造线段。
     * 点 (<code>x0</code>,&nbsp;<code>y0</code>) 定义
     * 该直线与点 (<code>x1</code>,&nbsp;<code>y1</code>) 定义
     * 末尾。
     */
    GLine(double x0 = 0, double y0 = 0, double x1 = 0, double y1 = 0, LineStyle lineStyle = LINE_SOLID);

    /**
     * 根据端点构造线段。
     * 点 <code>p0</code> 定义直线的起点，而
     * 点 <code>p1</code> 定义终点。
     */
    GLine(const GPoint& p0, const GPoint& p1);

    /* @inherit */
    bool contains(double x, double y) const override;

    /**
     * 使用给定 Qt 画笔在屏幕上绘制此线段。
     * @private
     */
    void draw(QPainter* painter) override;

    /* @inherit */
    GRectangle getBounds() const override;

    /**
     * 返回线条结束处的点。
     */
    virtual GPoint getEndPoint() const;

    /**
     * 返回线条终点的 x 坐标。
     */
    virtual double getEndX() const;

    /**
     * 返回线条终点的 y 坐标。
     */
    virtual double getEndY() const;

    /* @inherit */
    double getHeight() const override;

    /**
     * 返回线条开始处的点。
     * 等价于 getLocation。
     */
    virtual GPoint getStartPoint() const;

    /**
     * 返回线条起点的 x 坐标。
     * 等价于 getX。
     */
    virtual double getStartX() const;

    /**
     * 返回线条起点的 y 坐标。
     * 等价于 getY。
     */
    virtual double getStartY() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    double getWidth() const override;

    /**
     * 将线的终点设置为 (<code>x1</code>,&nbsp;<code>y1</code>)，
     * 并保持起点不变。因此此方法不同于
     * <code>setLocation</code>，它会移动线段的两个端点。
     */
    virtual void setEndPoint(double x1, double y1);

    /**
     * 将线的终点设置为 p，
     * 并保持起点不变。因此此方法不同于
     * <code>setLocation</code>，它会移动线段的两个端点。
     */
    virtual void setEndPoint(const GPoint& p);

    /**
     * 将此线条的两个端点设置为 (x0, y0) 和 (x1, y1)。
     * 这些点会重新排列为 x 优先、y 次优先顺序；也就是说，如果
     * 如果 x1 < x0，或（x1 == x0 且 y1 < y0），则交换两个点。
     * 这样做是为了提高绘制线条时的一致性。
     */
    virtual void setPoints(double x0, double y0, double x1, double y1);

    /**
     * 将此线条的两个端点设置为 p0 和 p1。
     * 这些点会重新排列为 x 优先、y 次优先顺序；也就是说，如果
     * 如果 x1 < x0，或（x1 == x0 且 y1 < y0），则交换两个点。
     * 这样做是为了提高绘制线条时的一致性。
     */
    virtual void setPoints(const GPoint& p0, const GPoint& p1);

    /**
     * 将线的起点设置为 (<code>x0</code>,&nbsp;<code>y0</code>)，
     * 并保持终点不变。因此此方法不同于
     * <code>setLocation</code>，它会移动线段的两个端点。
     */
    virtual void setStartPoint(double x0, double y0);

    /**
     * 将线的起点设置为 p，
     * 并保持终点不变。因此此方法不同于
     * <code>setLocation</code>，它会移动线段的两个端点。
     */
    virtual void setStartPoint(const GPoint& p);

    /* @inherit */
    std::string toStringExtra() const override;

protected:
    /* 实例变量 */
    double _dx;   // 直线的 x 方向位移
    double _dy;   // 直线的 y 方向位移
};

/**
 * 此图形对象子类表示内接于
 * 矩形框。
 */
class GOval : public GObject {
public:
    /**
     * 构造内接于指定矩形的新椭圆。
     * 默认情况下，椭圆位于原点，但可以传入
     * 坐标 <code>x</code> 和 <code>y</code>。
     */
    GOval(double x = 0, double y = 0, double width = 0, double height = 0);

    /* @inherit */
   bool contains(double x, double y) const override;

    /**
     * 使用给定 Qt 画笔在屏幕上绘制此椭圆。
     * @private
     */
    void draw(QPainter* painter) override;

    /* @inherit */
    std::string getType() const override;
};

/**
 * 此图形对象子类表示由
 * 线段。<code>GPolygon</code> 构造函数创建一个
 * 空多边形。要完成图形，需要添加顶点
 * 使用 <code>addVertex</code> 等方法添加到多边形中，
 * <code>addEdge</code> 和 <code>addPolarEdge</code>。
 */
class GPolygon : public GObject {
public:
    /**
     * 在原点构造新的空多边形。
     */
    GPolygon();

    /**
     * 使用给定顶点坐标构造新多边形。
     */
    GPolygon(std::initializer_list<double> coords);
    GPolygon(std::initializer_list<GPoint> points);

    /**
     * 向多边形添加一条边，其分量由以下位移给出：
     * 从最后一个顶点起的 <code>dx</code> 和 <code>dy</code>。
     */
    virtual void addEdge(double dx, double dy);

    /**
     * 向多边形添加一条边，其相对于最后一个顶点的位移
     * 被指定为给定点的 x/y 值。
     */
    virtual void addEdge(const GPoint& pt);

    /**
     * 向多边形添加多条边，其各分量由以下内容给出：
     * 相对于上一个顶点的位移 <code>dx</code> 和 <code>dy</code>。
     */
    virtual void addEdges(std::initializer_list<double> coords);

    /**
     * 向多边形添加多条边，其各分量由以下内容给出：
     * 相对于上一个顶点的位移 <code>dx</code> 和 <code>dy</code>。
     */
    virtual void addEdges(std::initializer_list<GPoint> points);

    /**
     * 以极坐标指定方式向多边形添加边。
     * 边的长度由 <code>r</code> 给出，并且该边延伸
     * 沿 <code>theta</code> 方向，以逆时针角度计量
     * 从 +x 轴。
     */
    virtual void addPolarEdge(double r, double theta);

    /**
     * 在相对于多边形的 (<code>x</code>, <code>y</code>) 处添加顶点
     * 原点。
     */
    virtual void addVertex(double x, double y);

    /**
     * 在给定的 (<code>x</code>, <code>y</code>) 点添加顶点
     * 相对于多边形原点。
     */
    virtual void addVertex(const GPoint& pt);

    /**
     * 向多边形添加多条边，其各分量由以下内容给出：
     * 相对于多边形的坐标 <code>dx</code> 和 <code>dy</code>
     * 原点。
     */
    virtual void addVertexes(std::initializer_list<double> coords);

    /**
     * 向多边形添加多条边，其各分量由以下内容给出：
     * 相对于多边形的坐标 <code>dx</code> 和 <code>dy</code>
     * 原点。
     */
    virtual void addVertexes(std::initializer_list<GPoint> points);

    /**
     * 从多边形中删除所有顶点。
     */
    virtual void clear();

    /* @inherit */
    bool contains(double x, double y) const override;

    /**
     * 使用给定 Qt 画笔在屏幕上绘制此多边形。
     * @private
     */
    void draw(QPainter* painter) override;

    /* @inherit */
    GRectangle getBounds() const override;

    /* @inherit */
    double getHeight() const override;

    /* @inherit */
    std::string getType() const override;

    /**
     * 返回此多边形中给定从 0 开始索引处的顶点。
     * @throw 如果索引越界，则抛出 ErrorException。
     */
    virtual GPoint getVertex(int i) const;

    /**
     * 返回此多边形中的顶点数量。
     */
    virtual int getVertexCount() const;

    /**
     * 返回多边形中所有点的向量。
     */
    virtual Vector<GPoint> getVertices() const;

    /* @inherit */
    double getWidth() const override;

    /**
     * 将此多边形中给定从 0 开始索引处的顶点设置为
     * 给定坐标。
     * @throw 如果索引越界，则抛出 ErrorException。
     */
    virtual void setVertex(int i, GPoint point);

    /* @inherit */
    std::string toStringExtra() const override;

private:
    /* 实例变量 */
    QVector<QPointF> _vertices;   // 多边形的各个顶点
    double _cx;                   // 最近一次的 x 坐标
    double _cy;                   // 最近一次的 y 坐标
};

/**
 * GRect 是外观由以下内容组成的图形对象：
 * 矩形框。
 */
class GRect : public GObject {
public:
    /**
     * 构造具有指定宽度和高度的矩形。第一个
     * 一种形式位于原点；第二种位于坐标
     * 由 <code>x</code> 和 <code>y</code> 给出。
     */
    GRect(double x = 0, double y = 0, double width = 0, double height = 0);

    /**
     * 使用给定 Qt painter 在屏幕上绘制此矩形。
     * @private
     */
    void draw(QPainter* painter) override;

    /* @inherit */
    std::string getType() const override;
};

/**
 * GRoundRect 表示外观由以下内容组成的图形对象
 * 带圆角的矩形框。
 */
class GRoundRect : public GRect {
public:
    /**
     * 未指定时圆角矩形拐角的默认直径
     * 提供给构造函数。
     */
    static const double DEFAULT_CORNER;

    /**
     * 构造具有指定宽度和高度的新矩形，
     * 位于 (0, 0)。<code>corner</code> 参数指定
     * 形成圆角的弧的直径。
     */
    GRoundRect(double width = 0, double height = 0, double corner = DEFAULT_CORNER);

    /**
     * 构造具有指定宽度和高度的新矩形，
     * 其左上角位于 (x, y)。<code>corner</code> 参数
     * 指定构成拐角的弧直径。
     */
    GRoundRect(double x, double y, double width, double height, double corner = DEFAULT_CORNER);

    /**
     * 若指定点位于对象内部，则返回 <code>true</code>。
     */
    bool contains(double x, double y) const override;

    /**
     * 使用给定 Qt painter 在屏幕上绘制此矩形。
     * @private
     */
    void draw(QPainter* painter) override;

    /**
     * 返回构成此圆角对象拐角的弧直径
     * 矩形。
     */
    virtual double getCorner() const;

    /* @inherit */
    std::string getType() const override;

    /**
     * 设置构成此圆角对象拐角的弧直径
     * 矩形。
     */
    virtual void setCorner(double corner);

    /* @inherit */
    std::string toStringExtra() const override;

protected:
    double _corner;
};

/**
 * 此图形对象子类表示一个文本字符串。
 *
 * 控制 <code>GText</code> 的外观和位置
 * 取决于对以下术语的理解：
 *
 * <ul>
 *   <li><b><i>基线</i></b>是以下内容所在的水平线：
 *       字符保持不变。
 *   <li><b><i>原点</i></b>是基线上以下对象所在的点：
 *       标签开始的位置。
 *   <li><b><i>高度</i></b>是分隔两个对象的距离
 *       连续各行。
 *   <li><b><i>上升部</i></b>是字符可达到的最大距离
 *       此字体中伸到基线以上的部分。
 *   <li><b><i>下降部</i></b>是字符可达到的最大距离
 *       此字体中伸到基线以下的部分。
 * </ul>
 */
class GText : public GObject {
public:

    /**
     * 创建包含指定字符串的 <code>GText</code> 对象。
     * 默认情况下，第一个字符的基线位于原点；
     * 第二种形式会自动重置
     * 将 <code>GText</code> 移动到点 (<code>x</code>, <code>y</code>)。
     */
    GText(const std::string& str = "", double x = 0, double y = 0);

    /**
     * 使用给定 Qt 画笔在屏幕上绘制此文本标签。
     * @private
     */
    void draw(QPainter* painter) override;

    /* @inherit */
    GRectangle getBounds() const override;

    /**
     * 返回标签的当前字体。
     */
    virtual std::string getFont() const;

    /**
     * 返回此字体中字符串向基线上方延伸的最大距离
     * 基线。
     */
    virtual double getFontAscent() const;

    /**
     * 返回此字体中字符串向基线下方延伸的最大距离
     * 基线。
     */
    virtual double getFontDescent() const;

    /**
     * 返回此对象显示的字符串。
     * 等价于 getLabel。
     */
    virtual std::string getLabel() const;

    /**
     * 返回此对象显示的字符串。
     * 等价于 getLabel。
     */
    virtual std::string getText() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    void setFont(const QFont& font) override;

    /* @inherit */
    void setFont(const std::string& font) override;

    /**
     * 更改文本标签中保存的字符串，使
     * 显示区域出现新的文本字符串。
     * 等价于 setText。
     */
    virtual void setLabel(const std::string& str);

    /**
     * 更改文本标签中保存的字符串，使
     * 显示区域出现新的文本字符串。
     * 等价于 setText。
     */
    virtual void setText(const std::string& str);

    /* @inherit */
    std::string toStringExtra() const override;

private:
    /* 实例变量 */
    std::string _text;   // 标签显示的字符串
    QFont _qfont;

    // 字体或文本变化时更新宽度和高度
    void updateSize();
};

/**
 * 将给定图形对象打印到输出流。
 */
std::ostream& operator <<(std::ostream& out, const GObject& obj);

#endif // _gobjects_h
