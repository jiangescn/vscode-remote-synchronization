/*
 * 文件：gdrawingsurface.h
 * -----------------------
 *
 * @author Marty Stepp
 * @version 2018/09/10
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gdrawingsurface.h，以替代 Java 版本
 * @version 2018/07/11
 * - 初始版本
 */


#ifndef _gdrawingsurface_h
#define _gdrawingsurface_h

#include <string>
#include <QFont>
#include <QWidget>

#include "grid.h"
#include "gobjects.h"
#include "gtypes.h"

/**
 * GDrawingSurface 是允许绘制形状的类型的抽象超类
 * 并将像素绘制到自身，作为像素背景层。
 * 其中包括图形画布对象（GCanvas）以及窗口（GWindow）。
 */
class GDrawingSurface {
public:
    /**
     * 擦除绘图表面的所有像素数据。
     */
    virtual void clear() = 0;

    /**
     * 仅当交互控件内容发生变化时才重绘。
     */
    virtual void conditionalRepaint();

    /**
     * 仅当交互控件内容发生变化时，才重绘给定区域。
     */
    virtual void conditionalRepaintRegion(int x, int y, int width, int height);

    /**
     * 仅当交互控件内容发生变化时，才重绘给定区域。
     */
    virtual void conditionalRepaintRegion(const GRectangle& bounds);

    /**
     * 将给定图形对象绘制到此对象的背景像素层
     * 交互控件。
     * @throw 如果对象为空，则抛出 ErrorException
     */
    virtual void draw(GObject* gobj) = 0;

    /**
     * 将给定图形对象绘制到此对象的背景像素层
     * 先将交互控件移动到给定 x/y 位置。
     * @throw 如果对象为空，则抛出 ErrorException
     */
    virtual void draw(GObject* gobj, double x, double y);

    /**
     * 将给定图形对象绘制到此对象的背景像素层
     * 交互控件。
     */
    virtual void draw(GObject& gobj);

    /**
     * 将给定图形对象绘制到此对象的背景像素层
     * 先将交互控件移动到给定 x/y 位置。
     */
    virtual void draw(GObject& gobj, double x, double y);

    /**
     * 使用给定 Qt 画笔对象绘制此交互控件。
     * @private
     */
    virtual void draw(QPainter* painter) = 0;

    /**
     * 在背景像素层上绘制具有给定属性的未填充弧
     * 此交互控件在当前颜色下的图层。
     * 有关 GArc 参数的说明，请参阅 gobjects.h。
     */
    virtual void drawArc(double x, double y, double width, double height, double start, double sweep);

    /**
     * 将从给定文件名加载的图像绘制到背景像素层
     * 此交互控件在给定 x/y 位置的图层。
     * 有关 GImage 参数的说明，请参阅 gobjects.h。
     * @throw 如果找不到或无法加载给定文件，则抛出 ErrorException
     *        作为有效图像文件
     */
    virtual void drawImage(const std::string& filename, double x = 0, double y = 0);

    /**
     * 在给定两点之间绘制线段到背景像素层
     * 在当前颜色下，设置此交互控件给定 x/y 位置的图层。
     * 有关 GLine 参数的说明，请参阅 gobjects.h。
     */
    virtual void drawLine(const GPoint& p0, const GPoint& p1);

    /**
     * 在给定两点之间绘制线段到背景像素层
     * 在当前颜色下，设置此交互控件给定 x/y 位置的图层。
     * 有关 GLine 参数的说明，请参阅 gobjects.h。
     */
    virtual void drawLine(double x0, double y0, double x1, double y1);

    /**
     * 将具有给定边界框的空心椭圆绘制到背景像素层
     * 在当前颜色下，设置此交互控件给定 x/y 位置的图层。
     * 有关 GOval 参数的说明，请参阅 gobjects.h。
     */
    virtual void drawOval(const GRectangle& bounds);

    /**
     * 将具有给定边界框的空心椭圆绘制到背景像素层
     * 在当前颜色下，设置此交互控件给定 x/y 位置的图层。
     * 有关 GOval 参数的说明，请参阅 gobjects.h。
     */
    virtual void drawOval(double x, double y, double width, double height);

    /**
     * 使用极坐标绘制线段到背景像素层
     * 此交互控件在当前颜色下的图层。
     * 线段从给定 x/y 点开始，并从该点按以下增量延伸：
     * 给定角度和半径。
     * 返回与 p0 相对、线条结束处的端点。
     * 有关 GLine 参数的说明，请参阅 gobjects.h。
     */
    virtual GPoint drawPolarLine(const GPoint& p0, double r, double theta);

    /**
     * 使用极坐标绘制线段到背景像素层
     * 此交互控件在当前颜色下的图层。
     * 线段从给定 x/y 点开始，并从该点按以下增量延伸：
     * 给定角度和半径。
     * 返回线条结束处的端点。
     * 有关 GLine 参数的说明，请参阅 gobjects.h。
     */
    virtual GPoint drawPolarLine(double x0, double y0, double r, double theta);

    /**
     * 设置此交互控件背景层中给定 x/y 像素的颜色
     * 使用交互控件当前的颜色。
     */
    virtual void drawPixel(double x, double y);

    /**
     * 设置此交互控件背景层中给定 x/y 像素的颜色
     * 使用给定颜色。
     */
    virtual void drawPixel(double x, double y, int color);

    /**
     * 设置此交互控件背景层中给定 x/y 像素的颜色
     * 使用给定颜色。
     */
    virtual void drawPixel(double x, double y, const std::string& color);

    /**
     * 将包含给定点的空心多边形绘制到背景像素层
     * 在当前颜色下设置此交互控件的像素层。
     * 有关 GPolygon 参数的说明，请参阅 gobjects.h。
     */
    virtual void drawPolygon(std::initializer_list<double> coords);

    /**
     * 将包含给定点的空心多边形绘制到背景像素层
     * 在当前颜色下设置此交互控件的像素层。
     * 有关 GPolygon 参数的说明，请参阅 gobjects.h。
     */
    virtual void drawPolygon(std::initializer_list<GPoint> points);

    /**
     * 将给定尺寸的空心矩形绘制到背景像素层
     * 在当前颜色下设置此交互控件的像素层。
     * 有关 GRect 参数的说明，请参阅 gobjects.h。
     */
    virtual void drawRect(const GRectangle& bounds);

    /**
     * 将给定尺寸的空心矩形绘制到背景像素层
     * 在当前颜色下设置此交互控件的像素层。
     * 有关 GRect 参数的说明，请参阅 gobjects.h。
     */
    virtual void drawRect(double x, double y, double width, double height);

    /**
     * 在此交互控件的背景像素层上绘制文本字符串
     * 在当前字体和颜色下绘制于给定 x/y 位置。
     * 有关 GText 参数的说明，请参阅 gobjects.h。
     */
    virtual void drawString(const std::string& text, double x, double y);

    /**
     * 在背景像素层上绘制具有给定属性的填充弧
     * 使用当前颜色和填充色绘制此交互控件的图层。
     * 有关 GArc 参数的说明，请参阅 gobjects.h。
     */
    virtual void fillArc(double x, double y, double width, double height, double start, double sweep);

    /**
     * 将具有给定边界框的填充椭圆绘制到背景像素层
     * 在当前颜色下设置此交互控件给定 x/y 位置的图层
     * 以及填充颜色。
     * 有关 GOval 参数的说明，请参阅 gobjects.h。
     */
    virtual void fillOval(const GRectangle& bounds);

    /**
     * 将具有给定边界框的填充椭圆绘制到背景像素层
     * 在当前颜色下设置此交互控件给定 x/y 位置的图层
     * 以及填充颜色。
     * 有关 GOval 参数的说明，请参阅 gobjects.h。
     */
    virtual void fillOval(double x, double y, double width, double height);

    /**
     * 将包含给定点的填充多边形绘制到背景像素层
     * 在当前颜色和填充颜色下设置此交互控件的像素层。
     * 有关 GPolygon 参数的说明，请参阅 gobjects.h。
     */
    virtual void fillPolygon(std::initializer_list<double> coords);

    /**
     * 将包含给定点的填充多边形绘制到背景像素层
     * 在当前颜色和填充颜色下设置此交互控件的像素层。
     * 有关 GPolygon 参数的说明，请参阅 gobjects.h。
     */
    virtual void fillPolygon(std::initializer_list<GPoint> coords);

    /**
     * 将给定尺寸的填充矩形绘制到背景像素层
     * 在当前颜色和填充颜色下设置此交互控件的像素层。
     * 有关 GRect 参数的说明，请参阅 gobjects.h。
     */
    virtual void fillRect(const GRectangle& bounds);

    /**
     * 将给定尺寸的填充矩形绘制到背景像素层
     * 在当前颜色和填充颜色下设置此交互控件的像素层。
     * 有关 GRect 参数的说明，请参阅 gobjects.h。
     */
    virtual void fillRect(double x, double y, double width, double height);

    /**
     * 返回给定 x/y 位置处的像素颜色数据，
     * 在高 8 位中保留 alpha 通道透明度。
     */
    virtual int getARGB(double x, double y) const;

    /**
     * 以字符串返回交互控件当前背景色。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     */
    virtual std::string getBackground() const;

    /**
     * 以 RGB 整数返回交互控件当前背景色。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     */
    virtual int getBackgroundInt() const;

    /**
     * 以字符串形式返回交互控件当前的前景轮廓颜色。
     * 使用该颜色绘制通过以下方法所绘形状的轮廓：
     * 使用 drawXxx 和 fillXxx 方法绘制时，也作为默认颜色
     * 调用 setPixel 或 setRGB。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     * 等价于 getForeground。
     */
    virtual std::string getColor() const;

    /**
     * 以 RGB 整数形式返回交互控件当前的前景轮廓颜色。
     * 使用该颜色绘制通过以下方法所绘形状的轮廓：
     * 使用 drawXxx 和 fillXxx 方法绘制时，也作为默认颜色
     * 调用 setPixel 或 setRGB。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * 等价于 getForegroundInt。
     */
    virtual int getColorInt() const;

    /**
     * 以字符串形式返回交互控件当前的填充颜色。
     * 使用 fillXxx 方法绘制的形状会显示此颜色。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     */
    virtual std::string getFillColor() const;

    /**
     * 以 RGB 整数返回交互控件当前填充色。
     * 使用 fillXxx 方法绘制的形状会显示此颜色。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     */
    virtual int getFillColorInt() const;

    /**
     * 以字体字符串返回交互控件当前文本字体。
     * 使用 drawString 绘制文本字符串时采用此字体。
     * 有关字体字符串的更多信息，请参阅 gfont.h。
     */
    virtual std::string getFont() const;

    /**
     * 以字符串形式返回交互控件当前的前景轮廓颜色。
     * 使用该颜色绘制通过以下方法所绘形状的轮廓：
     * 使用 drawXxx 和 fillXxx 方法绘制时，也作为默认颜色
     * 调用 setPixel 或 setRGB。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     * 等价于 getColor。
     */
    virtual std::string getForeground() const;

    /**
     * 以 RGB 整数形式返回交互控件当前的前景轮廓颜色。
     * 使用该颜色绘制通过以下方法所绘形状的轮廓：
     * 使用 drawXxx 和 fillXxx 方法绘制时，也作为默认颜色
     * 调用 setPixel 或 setRGB。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * 等价于 getColor。
     */
    virtual int getForegroundInt() const;

    /**
     * 返回绘制以下对象轮廓时使用的当前线型
     * 形状和线条。
     * 默认线型为实线（GObject::LINE_SOLID）。
     */
    virtual GObject::LineStyle getLineStyle() const;

    /**
     * 返回绘制形状和线条轮廓时使用的粗细。
     * 默认粗细为 1。
     */
    virtual double getLineWidth() const;

    /**
     * 返回给定 x/y 坐标处像素的颜色，该像素属于
     * 交互控件背景层的颜色，以类似 0xff00cc 的整数表示。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     *
     * 等价于 getRGB。
     *
     * @throw 如果给定 x/y 值越界，则抛出 ErrorException。
     */
    virtual int getPixel(double x, double y) const = 0;

    /**
     * 返回给定 x/y 坐标处像素的颜色，该像素属于
     * 交互控件背景层的颜色，以 0xffff00cc 这样的整数表示。
     * 它与 getPixel 的不同之处在于会显式保留并返回
     * 该像素的 alpha 通道位于高 8 位，从而允许
     * 透明效果。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     *
     * @throw 如果给定 x/y 值越界，则抛出 ErrorException。
     */
    virtual int getPixelARGB(double x, double y) const = 0;

    /**
     * 以 Grid 形式返回表面的所有像素，
     * 其中行表示 y 值，列表示 x 值。
     */
    virtual Grid<int> getPixels() const = 0;

    /**
     * 以 Grid 形式返回表面背景层的所有像素，
     * 其中行表示 y 值，列表示 x 值。
     * 它与 getPixels 的不同之处在于会显式保留并返回
     * 每个像素的 alpha 通道位于高 8 位，从而允许
     * 透明效果。
     */
    virtual Grid<int> getPixelsARGB() const = 0;

    /**
     * 返回图像给定 x/y 坐标处像素的颜色
     * 以类似“#ff00cc”的字符串形式。
     * 返回的字符串来自 <code>GWindow</code> 函数
     * <code>convertRGBToColor</code>；请参阅该函数的文档。
     * 如果给定 x/y 值越界，则抛出错误。
     */
    virtual std::string getPixelString(double x, double y) const;

    /**
     * 返回给定 x/y 坐标处像素的颜色，该像素属于
     * 交互控件背景层的颜色，以类似 0xff00cc 的整数表示。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     *
     * 等价于 getPixel。
     *
     * @throw 如果给定 x/y 值越界，则抛出 ErrorException。
     */
    virtual int getRGB(double x, double y) const;

    /**
     * 返回给定 x/y 坐标处像素的颜色，该像素属于
     * 交互控件背景层的颜色，以“#ff00cc”这样的颜色字符串表示。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     *
     * @throw 如果给定 x/y 值越界，则抛出 ErrorException。
     */
    virtual std::string getRGBString(double x, double y) const;

    /**
     * 如果交互控件应在每次以下情况发生时自动重绘自身，则返回 true
     * 其图形数据发生任何变化时。
     * 但若调用 setAutoRepaint(false)，则必须手动重绘交互控件
     * 才能看到更改。如果计划进行大批量修改，这会很有用
     * 一系列更改，并希望仅在全部完成后重绘。
     * 等价于 isRepaintImmediately。
     */
    virtual bool isAutoRepaint() const;

    /**
     * 如果交互控件应在每次以下情况发生时自动重绘自身，则返回 true
     * 其图形数据发生任何变化时。
     * 但若调用 setAutoRepaint(false)，则必须手动重绘交互控件
     * 才能看到更改。如果计划进行大批量修改，这会很有用
     * 一系列更改，并希望仅在全部完成后重绘。
     * 等价于 isAutoRepaint。
     */
    virtual bool isRepaintImmediately() const;

    /**
     * 指示交互控件在屏幕上重绘自身。
     * 默认情况下，只要进行以下操作，交互控件就会自动重绘自身：
     * 更改其图形数据。
     * 但若调用 setAutoRepaint(false)，则必须手动重绘交互控件
     * 才能看到更改。如果计划进行大批量修改，这会很有用
     * 一系列更改，并希望仅在全部完成后重绘。
     */
    virtual void repaint() = 0;

    /**
     * 指示交互控件重绘给定像素数据区域。
     * 如果你有以下情况，出于性能考虑，这可能比 repaint() 更合适
     * 进行了一项仅影响给定矩形区域的小改动，该区域位于
     * 该交互控件。
     */
    virtual void repaintRegion(int x, int y, int width, int height) = 0;

    /**
     * 指示交互控件重绘给定像素数据区域。
     * 如果你有以下情况，出于性能考虑，这可能比 repaint() 更合适
     * 进行了一项仅影响给定矩形区域的小改动，该区域位于
     * 该交互控件。
     */
    virtual void repaintRegion(const GRectangle& bounds);

    /**
     * 设置交互控件是否应在每次以下情况发生时自动重绘自身
     * 其图形数据发生任何变化时。
     * 默认为 true。
     * 但若调用 setAutoRepaint(false)，则必须手动重绘交互控件
     * 才能看到更改。如果计划进行大批量修改，这会很有用
     * 一系列更改，并希望仅在全部完成后重绘。
     * 等价于 setRepaintImmediately。
     */
    virtual void setAutoRepaint(bool autoRepaint);

    /**
     * 以 RGB 整数设置交互控件当前背景色。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     */
    virtual void setBackground(int color);

    /**
     * 以字符串设置交互控件当前背景色。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     */
    virtual void setBackground(const std::string& color);

    /**
     * 以 RGB 整数设置交互控件当前前景轮廓色。
     * 使用该颜色绘制通过以下方法所绘形状的轮廓：
     * 使用 drawXxx 和 fillXxx 方法绘制时，也作为默认颜色
     * 调用 setPixel 或 setRGB。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     * 等价于 setForeground。
     */
    virtual void setColor(int color);

    /**
     * 以字符串形式设置交互控件当前的前景轮廓颜色。
     * 使用该颜色绘制通过以下方法所绘形状的轮廓：
     * 使用 drawXxx 和 fillXxx 方法绘制时，也作为默认颜色
     * 调用 setPixel 或 setRGB。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     * 等价于 setForeground。
     */
    virtual void setColor(const std::string& color);

    /**
     * 以 RGB 整数设置交互控件当前填充色。
     * 使用 fillXxx 方法绘制的形状会显示此颜色。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     */
    virtual void setFillColor(int color);

    /**
     * 以字符串形式返回交互控件当前的填充颜色。
     * 使用 fillXxx 方法绘制的形状会显示此颜色。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     */
    virtual void setFillColor(const std::string& color);

    /**
     * 使用 Qt 字体对象返回交互控件当前文本字体。
     * 使用 drawString 绘制文本字符串时采用此字体。
     * @private
     */
    virtual void setFont(const QFont& font);

    /**
     * 以字体字符串设置交互控件当前文本字体。
     * 使用 drawString 绘制文本字符串时采用此字体。
     * 有关字体字符串的更多信息，请参阅 gfont.h。
     */
    virtual void setFont(const std::string& font);

    /**
     * 以 RGB 整数设置交互控件当前前景轮廓色。
     * 使用该颜色绘制通过以下方法所绘形状的轮廓：
     * 使用 drawXxx 和 fillXxx 方法绘制时，也作为默认颜色
     * 调用 setPixel 或 setRGB。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     * 等价于 setColor。
     */
    virtual void setForeground(int color);

    /**
     * 以字符串形式设置交互控件当前的前景轮廓颜色。
     * 使用该颜色绘制通过以下方法所绘形状的轮廓：
     * 使用 drawXxx 和 fillXxx 方法绘制时，也作为默认颜色
     * 调用 setPixel 或 setRGB。
     * 有关颜色字符串的更多详细信息，请参阅 gcolor.h。
     * 等价于 setColor。
     */
    virtual void setForeground(const std::string& color);

    /**
     * 设置绘制形状和线条轮廓时使用的粗细。
     * 默认粗细为 1。
     */
    virtual void setLineWidth(double lineWidth);

    /**
     * 设置绘制以下对象轮廓时使用的当前线型
     * 形状和线条。
     * 默认线型为实线（GObject::LINE_SOLID）。
     */
    virtual void setLineStyle(GObject::LineStyle lineStyle);

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将交互控件设置为给定 RGB 值。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     * 等价于 setRGB。
     *
     * @throw 如果 x/y 超出范围，或 rgb 不是有效颜色，则抛出 ErrorException
     */
    virtual void setPixel(double x, double y, int rgb) = 0;

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将交互控件设置为给定 RGB 值。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     * 等价于 setRGB。
     *
     * @throw 如果 x/y 超出范围，或 r、g、b 不在 0-255 之间，则抛出 ErrorException
     */
    virtual void setPixel(double x, double y, int r, int g, int b);

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将交互控件设为给定颜色。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     * 等价于 setRGB。
     *
     * @throw 如果 x/y 超出范围，则抛出 ErrorException
     */
    virtual void setPixel(double x, double y, const std::string& color);

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将交互控件设为给定 ARGB 值。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixelsARGB 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixelsARGB 提交所有更改。
     *
     * @throw 如果 x/y 超出范围，或 argb 不是有效颜色，则抛出 ErrorException
     */
    virtual void setPixelARGB(double x, double y, int argb) = 0;

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将交互控件设为给定 ARGB 值。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixelsARGB 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixelsARGB 提交所有更改。
     *
     * @throw 如果 x/y 超出范围，或 a、r、g、b 不在 0-255 之间，则抛出 ErrorException
     */
    virtual void setPixelARGB(double x, double y, int a, int r, int g, int b);

    /**
     * 设置以下对象背景层中所有像素的颜色：
     * 将交互控件设为给定 RGB 值，其中行作为 y 值，列作为
     * x 值。任何现有背景层像素都会被替换。
     * 若给定网格大小与此交互控件不同，则交互控件
     * 将调整大小以匹配网格。
     */
    virtual void setPixels(const Grid<int>& pixels) = 0;

    /**
     * 设置以下对象背景层中所有像素的颜色：
     * 将交互控件设为给定 ARGB 值，其中行作为 y 值，列作为
     * x 值。任何现有背景层像素都会被替换。
     * 若给定网格大小与此交互控件不同，则交互控件
     * 将调整大小以匹配网格。
     */
    virtual void setPixelsARGB(const Grid<int>& pixelsARGB) = 0;

    /**
     * 设置交互控件是否应在每次以下情况发生时自动重绘自身
     * 其图形数据发生任何变化时。
     * 默认为 true。
     * 但若调用 setAutoRepaint(false)，则必须手动重绘交互控件
     * 才能看到更改。如果计划进行大批量修改，这会很有用
     * 一系列更改，并希望仅在全部完成后重绘。
     * 等价于 setAutoRepaint。
     */
    virtual void setRepaintImmediately(bool autoRepaint);

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将交互控件设置为给定 RGB 值。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     * 等价于 setPixel。
     *
     * @throw 如果 x/y 超出范围，或 rgb 不是有效颜色，则抛出 ErrorException
     */
    virtual void setRGB(double x, double y, int rgb);

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将交互控件设置为给定 RGB 值。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     * 等价于 setPixel。
     *
     * @throw 如果 x/y 超出范围，或 r、g、b 不在 0-255 之间，则抛出 ErrorException
     */
    virtual void setRGB(double x, double y, int r, int g, int b);

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将交互控件设为给定颜色。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     * 等价于 setPixel。
     *
     * @throw 如果 x/y 超出范围，则抛出 ErrorException
     */
    virtual void setRGB(double x, double y, const std::string& color);

protected:
    GDrawingSurface();
    virtual ~GDrawingSurface();

    GDrawingSurface* _forwardTarget;
    std::string _backgroundColor;
    std::string _color;
    std::string _fillColor;
    std::string _font;
    int _backgroundColorInt;
    int _colorInt;
    int _fillColorInt;
    GObject::LineStyle _lineStyle;
    double _lineWidth;
    bool _autoRepaint;

    /**
     * 如果给定 x/y 值越界，则抛出错误。
     */
    void checkBounds(const std::string& member, double x, double y, double width, double height) const;

    /**
     * 如果给定 rgb 值不是有效颜色，则抛出错误。
     */
    void checkColor(const std::string& member, int rgb) const;

    /**
     * 如果给定的宽度/高度值越界，则抛出错误。
     */
    void checkSize(const std::string& member, double width, double height) const;

    /**
     * 初始化要绘制的新图形对象。
     * 作为便捷方法，用于设置颜色、填充颜色、轮廓样式，
     * 根据以下对象的设置调整图形对象的字体及其他设置：
     * 绘图表面。
     */
    virtual void initializeGObject(GObject& obj, bool filled = false);

    /**
     * 初始化要绘制的新图形对象。
     * 作为便捷方法，用于设置颜色、填充颜色、轮廓样式，
     * 根据以下对象的设置调整图形对象的字体及其他设置：
     * 绘图表面。
     */
    virtual void initializeGObject(GObject* obj, bool filled = false);

    /**
     * 设置绘图调用应发送到的转发目标。
     * 供 GForwardDrawingSurface 使用。
     * @private
     */
    virtual void setDrawingForwardTarget(GDrawingSurface* forwardTarget);
};

/**
 * 一个绘图表面，它会将收到的所有调用转发给另一个
 * 绘图表面。
 * 在我们的库中，此类主要用于让 GWindow 转发
 * 将 drawRect 和 fillOval 等绘图调用转发到其内部 GCanvas 实例。
 * @private
 */
class GForwardDrawingSurface : public virtual GDrawingSurface {
public:
    void clear() override;
    void draw(GObject* gobj) override;
    void draw(GObject* gobj, double x, double y) override;
    void draw(GObject& gobj) override;
    void draw(GObject& gobj, double x, double y) override;
    void draw(QPainter* painter) override;
    int getPixel(double x, double y) const override;
    int getPixelARGB(double x, double y) const override;
    Grid<int> getPixels() const override;
    Grid<int> getPixelsARGB() const override;
    bool isAutoRepaint() const override;
    void repaint() override;
    void repaintRegion(int x, int y, int width, int height) override;
    void setAutoRepaint(bool autoRepaint) override;
    void setBackground(int color) override;
    void setBackground(const std::string& color) override;
    void setColor(int color) override;
    void setColor(const std::string& color) override;
    void setFillColor(int color) override;
    void setFillColor(const std::string& color) override;
    void setFont(const QFont& font) override;
    void setFont(const std::string& font) override;
    void setLineWidth(double lineWidth) override;
    void setPixel(double x, double y, int rgb) override;
    void setPixel(double x, double y, int r, int g, int b) override;
    void setPixelARGB(double x, double y, int argb) override;
    void setPixelARGB(double x, double y, int a, int r, int g, int b) override;
    void setPixels(const Grid<int>& pixels) override;
    void setPixelsARGB(const Grid<int>& pixelsARGB) override;
    void setRepaintImmediately(bool repaintImmediately) override;

protected:
    virtual void ensureForwardTarget() = 0;
    virtual void ensureForwardTargetConstHack() const;
};

#endif // _gcanvas_h
