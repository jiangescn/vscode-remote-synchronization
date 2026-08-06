/*
 * 文件：gtypes.h
 * --------------
 * 此文件定义用于表示点、尺寸和
 * 矩形。
 *
 * @version 2018/09/09
 * - 添加用于生成新文档的文档注释
 * @version 2018/07/14
 * - 初始版本，基于 gtypes.h
 */


#ifndef _gtypes_h
#define _gtypes_h

#include <functional>
#include <iostream>
#include <Qt>
#include <string>

/**
 * 无参数 void 函数的函数包装器别名
 * 且无返回值。
 */
typedef std::function<void()> GThunk;

/**
 * 无参数且有返回值函数的函数包装器别名
 * 并返回 int（例如 main()）。
 */
typedef std::function<int()> GThunkInt;


/**
 * 此结构体包含实数类型的 width 和 height 字段。
 * 用于表示图形对象的大小。
 */
struct GDimension {
public:
    /**
     * 使用指定参数创建 <code>GDimension</code> 对象
     * <code>width</code> 和 <code>height</code> 坐标。
     */
    GDimension(double width, double height);

    /*
     * 构造默认维度 0, 0。
     */
    GDimension();


    /**
     * 将 <code>GDimension</code> 转换为以下形式的字符串：
     * <code>"(</code><i>宽度</i><code>,</code>&nbsp;<i>高度</i><code>)"</code>。
     */
    std::string toString() const;

    /* 宽度和高度——可直接访问或修改 */
    double width;
    double height;

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：此类中此处以下的所有内容在逻辑上都属于  */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/
private:
    /* 实例变量 */

    /* 友元声明 */
    friend std::ostream& operator <<(std::ostream& os, const GDimension& dim);
    friend bool operator ==(const GDimension& d1, const GDimension& d2);
    friend bool operator !=(const GDimension& d1, const GDimension& d2);
    friend bool operator <(const GDimension& d1, const GDimension& d2);
    friend bool operator <=(const GDimension& d1, const GDimension& d2);
    friend bool operator >(const GDimension& d1, const GDimension& d2);
    friend bool operator >=(const GDimension& d1, const GDimension& d2);
    friend GDimension operator *(const GDimension& d, double scale);
    friend int hashCode(const GDimension& dim);
};

/**
 * 将 GDimension 写入给定输出流。
 */
std::ostream& operator <<(std::ostream& os, const GDimension& dim);

/**
 * 比较两个 GDimension 对象是否相等。
 */
bool operator ==(const GDimension& d1, const GDimension& d2);

/**
 * 比较两个 GDimension 对象是否不相等。
 */
bool operator !=(const GDimension& d1, const GDimension& d2);

/**
 * 先按宽度、再按以下属性比较两个 GDimension 对象的关系运算符：
 * 然后按高度。
 */
bool operator <(const GDimension& d1, const GDimension& d2);

/**
 * 先按宽度、再按以下属性比较两个 GDimension 对象的关系运算符：
 * 然后按高度。
 */
bool operator <=(const GDimension& d1, const GDimension& d2);

/**
 * 先按宽度、再按以下属性比较两个 GDimension 对象的关系运算符：
 * 然后按高度。
 */
bool operator >(const GDimension& d1, const GDimension& d2);

/**
 * 先按宽度、再按以下属性比较两个 GDimension 对象的关系运算符：
 * 然后按高度。
 */
bool operator >=(const GDimension& d1, const GDimension& d2);

/**
 * 将给定 GDimension 对象的宽度和高度乘以给定的
 * 缩放系数，并返回缩放后的尺寸对象。
 */
GDimension operator *(const GDimension& d, double scale);

/**
 * GDimension 对象的哈希函数。
 */
int hashCode(const GDimension& dim);

/**
 * 控件或组件支持的水平对齐方式。
 * 屏幕上的对象。
 */
enum HorizontalAlignment {
    ALIGN_CENTER,
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_HORIZONTAL_STRETCH
};

/**
 * 控件或组件支持的垂直对齐方式。
 * 屏幕上的对象。
 */
enum VerticalAlignment {
    ALIGN_MIDDLE,
    ALIGN_TOP,
    ALIGN_BOTTOM,
    ALIGN_VERTICAL_STRETCH
};

/**
 * 对齐方式和图标位置的常量。
 * 为向后兼容而保留；新代码不应使用此枚举。
 *
 */
enum SwingConstants {
    SWING_CENTER,
    SWING_TOP,
    SWING_LEFT,
    SWING_BOTTOM,
    SWING_RIGHT
};
// 注意：必须与 GInteractor::TextPosition 保持同步。

/**
 * 将对齐值转换为“Center”或“Left”这样的字符串。
 */
std::string toString(HorizontalAlignment alignment);

/**
 * 将对齐值转换为“Middle”或“Top”这样的字符串。
 */
std::string toString(VerticalAlignment alignment);

/**
 * 将“Center”或“Left”这样的字符串转换为对齐值。
 */
HorizontalAlignment toHorizontalAlignment(const std::string& alignmentStr);

/**
 * 将对齐值转换为 Qt 对齐常量。
 */
Qt::Alignment toQtAlignment(HorizontalAlignment alignment);

/**
 * 将对齐值转换为 Qt 对齐常量。
 */
Qt::Alignment toQtAlignment(VerticalAlignment alignment);

/**
 * 将“Middle”或“Top”这样的字符串转换为对齐值。
 */
VerticalAlignment toVerticalAlignment(const std::string& alignmentStr);

/**
 * 此结构体包含实数类型的 x 和 y 字段。
 * 用于表示图形平面上的位置。
 */
struct GPoint {
public:
    /**
     * 使用指定 <code>x</code> 创建 <code>GPoint</code> 对象
     * 以及 <code>y</code> 坐标。
     */
    GPoint(double x, double y);

    /*
     * 构造默认 GPoint 0, 0。
     */
    GPoint();

    /**
     * 将 <code>GPoint</code> 转换为以下形式的字符串：
     * <code>"(</code><i>x</i><code>,</code>&nbsp;<i>y</i><code>)"</code>。
     */
    std::string toString() const;

    /* x 和 y 坐标——可直接访问或修改 */
    double x;
    double y;

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：此类中此处以下的所有内容在逻辑上都属于  */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/
private:

    /* 友元声明 */
    friend std::ostream& operator <<(std::ostream& out, const GPoint& p);
    friend bool operator ==(const GPoint& p1, const GPoint& p2);
    friend bool operator !=(const GPoint& p1, const GPoint& p2);
    friend bool operator <(const GPoint& p1, const GPoint& p2);
    friend bool operator <=(const GPoint& p1, const GPoint& p2);
    friend bool operator >(const GPoint& p1, const GPoint& p2);
    friend bool operator >=(const GPoint& p1, const GPoint& p2);
    friend GPoint operator *(const GPoint& p, double scale);
    friend int hashCode(const GPoint& pt);
};

/**
 * 将给定点写入给定输出流。
 */
std::ostream& operator <<(std::ostream& os, const GPoint& pt);

/**
 * 比较两个 GPoint 对象是否相等。
 */
bool operator ==(const GPoint& p1, const GPoint& p2);

/**
 * 比较两个 GPoint 对象是否不相等。
 */
bool operator !=(const GPoint& p1, const GPoint& p2);

/**
 * 先按 x 坐标、然后按以下属性比较点的关系运算符：
 * 按 y 坐标。
 */
bool operator <(const GPoint& p1, const GPoint& p2);

/**
 * 先按 x 坐标、然后按以下属性比较点的关系运算符：
 * 按 y 坐标。
 */
bool operator <=(const GPoint& p1, const GPoint& p2);

/**
 * 先按 x 坐标、然后按以下属性比较点的关系运算符：
 * 按 y 坐标。
 */
bool operator >(const GPoint& p1, const GPoint& p2);

/**
 * 先按 x 坐标、然后按以下属性比较点的关系运算符：
 * 按 y 坐标。
 */
bool operator >=(const GPoint& p1, const GPoint& p2);

/**
 * 将给定点的 x 和 y 坐标乘以给定缩放系数
 * 系数并返回缩放后的点。
 */
GPoint operator *(const GPoint& p, double scale);

/**
 * GPoint 对象的哈希函数。
 */
int hashCode(const GPoint& pt);

/**
 * 此结构体包含实数类型的 x、y、width 和 height 字段。
 * 用于表示图形对象的边界框。
 */
struct GRectangle {
public:
    /**
     * 创建具有指定位置的 <code>GRectangle</code> 对象
     * 以及大小。若未提供这些参数，构造函数会将
     * 将这些字段设为 0。
     */
    GRectangle(double x = 0, double y = 0, double width = 0, double height = 0);

    /**
     * 创建具有指定位置的 <code>GRectangle</code> 对象
     * 以及大小。若未提供这些参数，构造函数会将
     * 将这些字段设为 0。
     */
    GRectangle(double x, double y, const GDimension& size);

    /**
     * 创建具有指定位置的 <code>GRectangle</code> 对象
     * 以及大小。若未提供这些参数，构造函数会将
     * 将这些字段设为 0。
     */
    GRectangle(const GPoint& p, double width = 0, double height = 0);

    /**
     * 创建具有指定位置的 <code>GRectangle</code> 对象
     * 以及大小。若未提供这些参数，构造函数会将
     * 将这些字段设为 0。
     */
    GRectangle(const GPoint& p, const GDimension& size);

    /**
     * 如果矩形包含给定点，则返回 <code>true</code>。
     */
    bool contains(double x, double y) const;

    /**
     * 如果矩形包含给定点，则返回 <code>true</code>。
     */
    bool contains(const GPoint& pt) const;

    /**
     * 如果此矩形包含给定矩形，则返回 <code>true</code>
     * 完全。
     */
    bool contains(const GRectangle& rect) const;

    /**
     * 返回一个边界向外移动给定距离的新矩形
     * 四个边上相同的量。
     * 例如，位于 (55, 42) 的 10x10 矩形扩大 1 后将变为
     *      位于 (54, 41) 的 12x12 矩形。
     */
    GRectangle enlargedBy(double amount);

    /**
     * 如果此矩形与给定另一矩形重叠，则返回 true。
     */
    bool intersects(const GRectangle& other) const;

    /**
     * 如果矩形为空（即它满足以下条件），则返回 <code>true</code>
     * 宽度和高度都为 0 或负数。
     */
    bool isEmpty() const;

    /**
     * 将 <code>GRectangle</code> 转换为以下形式的字符串：
     * <code>"(</code><i>x</i><code>,</code>&nbsp;<i>y</i><code>,</code>
     * <i>宽度</i><code>,</code>&nbsp;<i>高度</i><code>)"</code>。
     */
    std::string toString() const;

    /* 坐标和尺寸——可直接访问或修改 */
    double x;        /* 矩形的 x 坐标 */
    double y;        /* 矩形的 y 坐标 */
    double width;    /* 矩形的宽度        */
    double height;   /* 矩形的高度       */

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：此类中此处以下的所有内容在逻辑上都属于  */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/
private:
    /* 实例变量 */


    /* 友元声明 */
    friend std::ostream& operator <<(std::ostream& os, const GRectangle& rect);
    friend bool operator ==(const GRectangle& r1, const GRectangle& r2);
    friend bool operator !=(const GRectangle& r1, const GRectangle& r2);
    friend bool operator <(const GRectangle& r1, const GRectangle& r2);
    friend bool operator <=(const GRectangle& r1, const GRectangle& r2);
    friend bool operator >(const GRectangle& r1, const GRectangle& r2);
    friend bool operator >=(const GRectangle& r1, const GRectangle& r2);
    friend int hashCode(const GRectangle& r);
};

/**
 * 将给定矩形写入给定输出流。
 */
std::ostream& operator <<(std::ostream& os, const GRectangle& rect);

/**
 * 比较两个矩形是否相等。
 */
bool operator ==(const GRectangle& r1, const GRectangle& r2);

/**
 * 比较两个矩形是否不相等。
 */
bool operator !=(const GRectangle& r1, const GRectangle& r2);

/**
 * 依次按 x、y、宽度、高度比较矩形的关系运算符。
 */
bool operator <(const GRectangle& r1, const GRectangle& r2);

/**
 * 依次按 x、y、宽度、高度比较矩形的关系运算符。
 */
bool operator <=(const GRectangle& r1, const GRectangle& r2);

/**
 * 依次按 x、y、宽度、高度比较矩形的关系运算符。
 */
bool operator >(const GRectangle& r1, const GRectangle& r2);

/**
 * 依次按 x、y、宽度、高度比较矩形的关系运算符。
 */
bool operator >=(const GRectangle& r1, const GRectangle& r2);

/**
 * GRectangle 对象的哈希函数。
 */
int hashCode(const GRectangle& r);

#endif // _gtypes_h
