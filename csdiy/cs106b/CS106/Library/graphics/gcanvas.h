/*
 * 文件：gcanvas.h
 * ---------------
 *
 * @author Marty Stepp
 * @version 2019/05/01
 * - 添加 createArgbPixel
 * - 修复与保存及带 alpha 透明度的 setPixels 相关的问题
 * @version 2019/03/07
 * - 添加直接从 istream 加载画布的支持（htiek）
 * @version 2018/09/10
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/04
 * - 添加双击事件支持
 * @version 2018/08/23
 * - 重命名为 gcanvas.h，以替代 Java 版本
 * @version 2018/06/30
 * - 初始版本
 */


#ifndef _gcanvas_h
#define _gcanvas_h

#include <string>
#include <QtEvents>
#include <QPainter>

#include "gdrawingsurface.h"
#include "gevent.h"
#include "ginteractor.h"
#include "gobjects.h"

// 用于高亮两幅图像间不匹配像素的默认颜色
#define GCANVAS_DEFAULT_DIFF_PIXEL_COLOR 0xdd00dd

class _Internal_QCanvas;

/**
 * GCanvas 是可在其上绘制形状、线条和颜色的图形绘图表面，
 * 和颜色，以及设置单个像素的 RGB 颜色值。
 *
 * 图形画布由两层组成：
 *
 * 1）背景层提供用于绘制静态图像的表面，这些图像
 * 不涉及动画，或用于基于二维像素的绘图算法。
 * 该类包含多个 drawXxx 和 fillXxx 方法，用于绘制
 * 背景层上的线条、矩形和椭圆。
 *
 * setPixel 和 setPixels 方法操纵
 * 背景层。可以使用 getPixels 以 Grid 形式获取所有像素，
 * 修改网格，然后使用 setPixels 将其传回，以执行二维
 * 对画布进行基于像素的操作。
 *
 * 2）前景层提供用于添加有状态形状和对象的抽象
 * 将图形对象绘制到画布。接受 GObject 的 add() 方法
 * 参数会将这些对象放到前景层。这样做的优点是
 * 前景层的优点是可以随时间操控对象，例如
 * 移动它、更改其颜色、大小或其他属性，并看到这些变化
 * 立即显示在屏幕上。这使前景层最适合
 * 适合动画或移动精灵。
 *
 * 当客户端执行以下操作时，GCanvas 会隐式添加到每个 GWindow 的中心
 * 调用窗口的 add()、drawXxx/fillXxx 或其他方法。在大多数情况下
 * 窗口只是将这些方法调用转发给其内部 GCanvas，后者
 * 执行大部分工作。
 *
 * 有关绘制形状和对象的更多详细信息，请参阅 gobjects.h。
 */
class GCanvas : public virtual GInteractor, public virtual GDrawingSurface {
public:
    /**
     * 图像宽度和/或高度允许的最大值。
     * 如果尝试创建/调整超过此大小的图像，将抛出错误。
     */
    static const int WIDTH_HEIGHT_MAX;

    /**
     * 根据给定的 0-255 A-R-G-B 分量创建单个 ARGB 整数。
     * @throw 如果 alpha、red、green 或 blue 不在 0-255（含）范围内，则抛出 ErrorException
     */
    static int createArgbPixel(int alpha, int red, int green, int blue);

    /**
     * 根据给定的 0-255 R-G-B 分量创建单个 RGB 整数。
     * @throw 如果 red、green 或 blue 不在 0-255（含）范围内，则抛出 ErrorException
     */
    static int createRgbPixel(int red, int green, int blue);

    /**
     * 从给定 ARGB 整数中提取 0-255 的 alpha 分量。
     * alpha 分量来自整数的第 24-31 位（最高有效位）。
     */
    static int getAlpha(int argb);

    /**
     * 从给定 RGB 整数中提取 0-255 的蓝色分量。
     * 蓝色分量来自整数的第 0-7 位（最低有效位）。
     */
    static int getBlue(int rgb);

    /**
     * 从给定 RGB 整数中提取 0-255 的绿色分量。
     * 绿色分量来自整数的第 8–15 位。
     */
    static int getGreen(int rgb);

    /**
     * 从给定 RGB 整数中提取 0-255 的红色分量。
     * 红色分量来自整数的第 16–23 位。
     */
    static int getRed(int rgb);

    /**
     * 提取 0-255 的红、绿、蓝分量
     * 给定 RGB 整数的值，通过引用填充。
     */
    static void getRedGreenBlue(int rgb, int& red, int& green, int& blue);

    /**
     * 创建默认大小为 0x0 像素的空画布
     * 默认背景色和前景色均为黑色。
     */
    GCanvas(QWidget* parent = nullptr);

    /**
     * 创建画布，并从以下来源加载其背景层像素数据：
     * 给定的图像文件名。
     * @throw 如果给定文件不存在或无法读取，则抛出 ErrorException
     *        作为有效图像文件
     */
    GCanvas(const std::string& filename, QWidget* parent = nullptr);

    /**
     * 创建画布，并从以下来源加载其背景层像素数据：
     * 给定的输入流
     * @throw 如果给定流无法作为有效图像文件读取，则抛出 ErrorException
     */
    GCanvas(std::istream& filename, QWidget* parent = nullptr);

    /**
     * 创建具有指定大小和可选背景色的空画布。
     * 若未传入背景色，则使用默认透明背景。
     * @throw 如果给定宽度/高度范围为负，则抛出 ErrorException
     * @throw 如果给定 rgb 值无效或超出范围，则抛出 ErrorException
     */
    GCanvas(double width, double height, int rgbBackground, QWidget* parent = nullptr);

    /**
     * 创建具有指定大小和背景色的空画布。
     * 若未传入背景色，则使用默认透明背景。
     * @throw 如果给定宽度/高度范围为负，则抛出 ErrorException
     * @throw 如果给定 rgb 值无效或超出范围，则抛出 ErrorException
     */
    GCanvas(double width, double height, const std::string& rgbBackground = "#00000000", QWidget* parent = nullptr);

    /**
     * 释放画布内部分配的内存。
     */
    ~GCanvas() override;

    /**
     * 将给定交互控件添加到画布。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void add(GObject* gobj);

    /**
     * 将给定交互控件添加到画布
     * 并将其移动到给定 x/y 位置。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    virtual void add(GObject* gobj, double x, double y);

    /**
     * 将给定交互控件添加到画布。
     */
    virtual void add(GObject& gobj);

    /**
     * 将给定交互控件添加到画布
     * 并将其移动到给定 x/y 位置。
     */
    virtual void add(GObject& gobj, double x, double y);

    /**
     * 从画布前景层删除所有图形对象
     * 并清空背景层以显示当前背景色。
     */
    void clear() override;

    /**
     * 移除画布前景层中的所有图形对象。
     * 这意味着使用 add() 方法添加的任何形状（例如 GRect）
     * GOval 等对象会被移除，而直接绘制到以下对象上的形状
     * 通过调用 drawXxx() 方法绘制到画布背景像素层的内容会
     * 保留。若还要清除背景层，请调用 clearPixels
     * 或改用 clear。
     */
    virtual void clearObjects();

    /**
     * 将画布像素的背景层重置为当前
     * 背景色。
     * 这意味着使用 add() 方法添加的任何形状（例如 GRect）
     * GOval 等对象会保留，而直接绘制到以下对象上的形状
     * 通过调用 drawXxx() 方法绘制到画布背景像素层的内容会
     * 被清除。若还要清除添加到前景层的形状，
     * 改为调用 clearObjects 或 clear。
     */
    virtual void clearPixels();

    /**
     * 如果以下对象前景层中的任一图形对象满足条件，则返回 true
     * 画布与给定 x/y 像素接触。
     */
    virtual bool contains(double x, double y) const;

    /**
     * 返回颜色与目标颜色不同的像素总数
     * 此图像与给定另一图像之间。
     * 若图像大小不同，则位于其中一个图像范围内、
     * 但超出另一图像边界的像素也视为不同。
     * 此版本的方法比较完整图像。
     */
    virtual int countDiffPixels(const GCanvas& image) const;

    /**
     * 返回颜色与目标颜色不同的像素总数
     * 此图像与给定另一图像之间。
     * 若图像大小不同，则位于其中一个图像范围内、
     * 但超出另一图像边界的像素也视为不同。
     * 此版本的方法传入要比较的像素 (x,y) 范围。
     */
    virtual int countDiffPixels(const GCanvas& image, int xmin, int ymin, int xmax, int ymax) const;

    /**
     * 返回颜色与目标颜色不同的像素总数
     * 此图像与给定另一图像之间。
     * 若图像大小不同，则位于其中一个图像范围内、
     * 但超出另一图像边界的像素也视为不同。
     * 此版本的方法比较完整图像。
     * @throw 如果传入的图像为空，则抛出 ErrorException
     */
    virtual int countDiffPixels(const GCanvas* image) const;

    /**
     * 返回颜色与目标颜色不同的像素总数
     * 此图像与给定另一图像之间。
     * 若图像大小不同，则位于其中一个图像范围内、
     * 但超出另一图像边界的像素也视为不同。
     * 此版本的方法传入要比较的像素 (x,y) 范围。
     * @throw 如果传入的图像为空，则抛出 ErrorException
     */
    virtual int countDiffPixels(const GCanvas* image, int xmin, int ymin, int xmax, int ymax) const;

    /**
     * 生成新画布，其内容与此画布相同，但
     * 将与参数 image 中对应像素不匹配的像素标成给定
     * 使用给定颜色（默认紫色）突出显示两者之间的差异。
     */
    virtual GCanvas* diff(const GCanvas& image, int diffPixelColor = GCANVAS_DEFAULT_DIFF_PIXEL_COLOR) const;

    /**
     * 生成新画布，其内容与此画布相同，但
     * 将与参数 image 中对应像素不匹配的像素标成给定
     * 使用给定颜色（默认紫色）突出显示两者之间的差异。
     * @throw 如果传入的图像为空，则抛出 ErrorException
     */
    virtual GCanvas* diff(const GCanvas* image, int diffPixelColor = GCANVAS_DEFAULT_DIFF_PIXEL_COLOR) const;

    /**
     * 将给定图形对象绘制到画布背景层。
     * 请注意，由于它绘制在背景层，未来对以下对象的更改
     * 图形对象，例如设置其位置、颜色、大小等，
     * 不会立即反映到此画布上。
     * 如果确实希望反映这些更改，请改为将形状添加到
     * 使用 add() 添加到前景层。
     * @throw 如果传入对象为 null，则抛出 ErrorException
     */
    void draw(GObject* gobj) override;

    /**
     * @inherit
     * @private
     */
    void draw(QPainter* painter) override;

    /**
     * 如果给定两个画布包含完全相同的像素数据，则返回 true。
     */
    virtual bool equals(const GCanvas& other) const;

    /**
     * 将画布中每个像素的颜色设置为给定颜色值。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     * @throw 如果给定 rgb 值不是有效颜色，则抛出 ErrorException
     */
    virtual void fill(int rgb);

    /**
     * 将画布中每个像素的颜色设置为给定颜色值。
     * 有关颜色的更多详细信息，请参阅 gcolor.h。
     */
    virtual void fill(const std::string& rgb);

    /**
     * 设置画布给定矩形范围内每个像素的颜色
     * 将像素数据设置为给定颜色值。
     * 具体来说，是矩形范围从 (x, y) 到
     * (x + width - 1, y + height - 1) 区域会填充为给定颜色。
     * @throw 如果给定 x/y/width/height 范围超出边界，则抛出 ErrorException
     *        图像边界，
     *        或给定 rgb 值不是有效颜色时
     */
    virtual void fillRegion(double x, double y, double width, double height, int rgb);

    /**
     * 设置画布给定矩形范围内每个像素的颜色
     * 将像素数据设置为给定颜色值。
     * 具体来说，是矩形范围从 (x, y) 到
     * (x + width - 1, y + height - 1) 区域会填充为给定颜色。
     * @throw 如果给定 x/y/width/height 范围超出边界，则抛出 ErrorException
     *        图像边界
     */
    virtual void fillRegion(double x, double y, double width, double height,
                            const std::string& rgb);

    /**
     * 将所有图形对象从前景层移动到背景层
     * 图层。这意味着未来对这些对象的更改不会
     * 在画布上看到。
     */
    virtual void flatten();

    /**
     * 用以下内容替换画布背景层的全部内容
     * 给定 RGB 像素值网格的内容。
     * 如果此图像与网格尺寸不同，则调整图像大小。
     * 任何之前的背景层内容都会丢失。
     * 等价于 getPixels。
     */
    virtual void fromGrid(const Grid<int>& grid);

    /* @inherit */
    std::string getBackground() const override;

    /* @inherit */
    int getBackgroundInt() const override;

    /**
     * 返回指向以下对象前景层中图形对象的指针
     * 画布中指定索引处的对象，在以下维度中从后向前编号
     * <i>z</i> 维度。
     * @throw 如果索引超出范围，则抛出 ErrorException
     */
    virtual GObject* getElement(int index) const;

    /**
     * 返回指向以下对象前景层中第一个图形对象的指针
     * 画布中包含给定 (x, y) 点的对象；如果没有则返回空指针
     * 此画布中的对象与它接触。
     */
    virtual GObject* getElementAt(double x, double y) const;

    /**
     * 返回以下对象前景层中存储的图形对象数量
     * 画布。
     */
    virtual int getElementCount() const;

    /**
     * 返回加载此画布所用的图像文件名称，或
     * 指向最近一次保存它的位置。
     * 如果此画布未与任何文件关联，则返回 ""。
     */
    virtual std::string getFilename() const;

    /* @inherit */
    std::string getFont() const override;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回给定 x/y 坐标处像素的颜色，该像素属于
     * 画布背景层的颜色，以 0xff00cc 这样的整数表示。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     *
     * @throw 如果给定 x/y 值越界，则抛出 ErrorException。
     */
    int getPixel(double x, double y) const override;

    /**
     * 返回给定 x/y 坐标处像素的颜色，该像素属于
     * 画布背景层的颜色，以 0xffff00cc 这样的整数表示。
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
    int getPixelARGB(double x, double y) const override;

    /**
     * 以 Grid 形式返回画布背景层的所有像素，
     * 其中行表示 y 值，列表示 x 值。
     * 例如，grid[y][x] 返回该像素的 RGB 整数值。
     * 等价于 toGrid。
     */
    Grid<int> getPixels() const override;

    /**
     * 以 Grid 形式返回画布背景层的所有像素，
     * 其中行表示 y 值，列表示 x 值。
     * 它与 getPixels 的不同之处在于会显式保留并返回
     * 每个像素的 alpha 通道位于高 8 位，从而允许
     * 透明效果。
     */
    Grid<int> getPixelsARGB() const override;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /* @inherit */
    bool isAutoRepaint() const override;

    /**
     * 从给定图像文件读取画布像素内容。
     * @throw 如果给定文件不存在或无法读取，则抛出 ErrorException
     *        作为有效图像文件
     */
    virtual void load(const std::string& filename);

    /**
     * 从给定输入流读取画布像素内容。
     * @throw 如果给定文件不存在或无法读取，则抛出 ErrorException
     *        作为有效图像文件
     */

    /**
     * 从画布的前景层中移除给定图形对象，
     * 若它原本存在。
     * @throw 如果图形对象为空，则抛出 ErrorException
     */
    virtual void remove(GObject* gobj);

    /**
     * 从画布的前景层中移除给定图形对象，
     * 若它原本存在。
     */
    virtual void remove(GObject& gobj);

    /**
     * 移除画布前景层中的所有图形对象。
     */
    virtual void removeAll();

    /**
     * 指示画布重绘其各层。
     * 默认情况下，只要进行以下操作，画布就会自动重绘自身：
     * 背景层或前景层发生变化。
     * 但若调用 setAutoRepaint(false)，则必须手动重绘画布
     * 才能看到更改。如果计划进行大批量修改，这会很有用
     * 一系列更改，并希望仅在全部完成后重绘。
     */
    void repaint() override;

    /**
     * 指示画布重绘前景层和背景层中给定的像素区域
     * 其各图层。
     */
    void repaintRegion(int x, int y, int width, int height) override;

    /**
     * 将此图像的边界更改为给定大小。
     * 这不会缩放图像，而只是更改可用的最大 x/y
     * 可以绘制到此图像上。
     * 如果未传入 'retain' 参数或将其设为 true，
     * 调整大小时将保留任何现有像素值。
     * 如果 'retain' 为 false，内容将被清除并设为默认值。
     * 丢弃任何现有像素内容并恢复默认值。
     * @throw 如果给定宽度/高度范围为负，则抛出 ErrorException
     */
    void resize(double width, double height, bool retain = true);

    /**
     * 将画布内容保存到给定图像文件。
     * @throw 如果给定文件不可写，则抛出 ErrorException。
     */
    virtual void save(const std::string& filename);

    /**
     * 设置每次进行以下更改时画布是否自动重绘自身
     * 背景层或前景层发生变化。
     * 默认为 true。
     * 但若调用 setAutoRepaint(false)，则必须手动重绘画布
     * 才能看到更改。如果计划进行大批量修改，这会很有用
     * 一系列更改，并希望仅在全部完成后重绘。
     */
    void setAutoRepaint(bool autoRepaint) override;

    /* @inherit */
    void setBackground(int color) override;

    /* @inherit */
    void setBackground(const std::string& color) override;

    /* @inherit */
    void setColor(int color) override;

    /* @inherit */
    void setColor(const std::string& color) override;

    /* @inherit */
    void setFont(const QFont& font) override;

    /* @inherit */
    void setFont(const std::string& font) override;

    /* @inherit */
    void setForeground(int rgb) override;

    /* @inherit */
    void setForeground(const std::string& color) override;

    /**
     * 在此画布上设置键盘监听器，以便在以下情况发生时调用它
     * 当画布上按下或释放任意按键时。
     * 任何现有的按键监听器都会被替换。
     */
    void setKeyListener(GEventListener func) override;

    /**
     * 在此画布上设置键盘监听器，以便在以下情况发生时调用它
     * 当画布上按下或释放任意按键时。
     * 任何现有的按键监听器都会被替换。
     */
    void setKeyListener(GEventListenerVoid func) override;

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将画布设置为给定 RGB 值。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     *
     * @throw 如果 x/y 超出范围，或 rgb 不是有效颜色，则抛出 ErrorException
     */
    void setPixel(double x, double y, int rgb) override;

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将画布设置为给定 RGB 值。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixels 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixels 提交所有更改。
     *
     * @throw 如果 x/y 超出范围，或 r、g、b 不在 0-255 之间，则抛出 ErrorException
     */
    void setPixel(double x, double y, int r, int g, int b) override;

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将画布设置为给定 ARGB 值。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixelsARGB 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixelsARGB 提交所有更改。
     *
     * @throw 如果 x/y 超出范围，或 argb 不是有效颜色，则抛出 ErrorException
     */
    void setPixelARGB(double x, double y, int argb) override;

    /**
     * 设置背景层中给定 x/y 像素的颜色，该背景层属于
     * 将画布设置为给定 ARGB 值。
     *
     * 请注意，如果你打算在背景中设置许多像素，并且
     * 若要获得最高性能，应改为调用 getPixelsARGB 提取
     * 将所有像素读入一个 Grid，然后在该 Grid 中操作所有需要修改的像素，
     * 然后调用 setPixelsARGB 提交所有更改。
     *
     * @throw 如果 x/y 超出范围，或 a、r、g、b 不在 0-255 之间，则抛出 ErrorException
     */
    void setPixelARGB(double x, double y, int a, int r, int g, int b) override;

    /**
     * 设置以下对象背景层中所有像素的颜色：
     * 将画布设置为给定 RGB 值，以行为 y 值、列为
     * x 值。任何现有背景层像素都会被替换。
     * 若给定网格大小与此画布不同，则画布会
     * 调整大小以匹配网格。
     * 等价于 fromGrid。
     */
    void setPixels(const Grid<int>& pixels) override;

    /**
     * 设置以下对象背景层中所有像素的颜色：
     * 将画布设置为给定 ARGB 值，以行为 y 值、列为
     * x 值。任何现有背景层像素都会被替换。
     * 若给定网格大小与此画布不同，则画布会
     * 调整大小以匹配网格。
     */
    void setPixelsARGB(const Grid<int>& pixelsARGB) override;

    /**
     * 将画布像素转换为 GImage 对象。
     */
    virtual GImage* toGImage() const;

    /**
     * 将此画布像素数据转换为 RGB 像素网格。
     * 网格的第一个索引是行或 y 索引，第二个索引是
     * 是列或 x 索引。
     * 例如，grid[y][x] 返回该像素的 RGB 整数值。
     * 在此版本的方法中，返回网格。
     * 等价于 getPixels。
     */
    virtual Grid<int> toGrid() const;

    /**
     * 将此画布像素数据转换为 RGB 像素网格。
     * 网格的第一个索引是行或 y 索引，第二个索引是
     * 是列或 x 索引。
     * 例如，grid[y][x] 返回该像素的 RGB 整数值。
     * 在此版本的方法中，通过引用填充网格。
     * 等价于 getPixels。
     */
    virtual void toGrid(Grid<int>& grid) const;

private:
    Q_DISABLE_COPY(GCanvas)

    _Internal_QCanvas* _iqcanvas;
    GCompound _gcompound;
    QImage* _backgroundImage;
    std::string _filename;   // 加载画布的文件；如果不是从文件加载，则为“”

    friend class _Internal_QCanvas;

    void ensureBackgroundImage();

    void ensureBackgroundImageConstHack() const;

    void init(double width, double height, int rgbBackground, QWidget* parent);

    /**
     * 从给定流读取画布像素内容。
     * @return 加载成功时为 true，加载失败时为 false
     */
    virtual bool loadFromStream(std::istream& input);

    void notifyOfResize(double width, double height);
};

// 参数在 Qt 6 中具有新类型
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    typedef QEvent ParameterToEnterEvent;
#else
    typedef QEnterEvent ParameterToEnterEvent;
#endif

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QCanvas : public QWidget, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QCanvas(GCanvas* gcanvas, QWidget* parent = nullptr);
    void detach() override;
    void enterEvent(ParameterToEnterEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    virtual void setCanvasSize(double width, double height);
    QSize sizeHint() const override;
    void wheelEvent(QWheelEvent* event) override;

signals:
    void doubleClicked();

protected:
    void mouseDoubleClickEvent(QMouseEvent* e) override;

private:
    GCanvas* _gcanvas;

    friend class GCanvas;
};

#endif // _gcanvas_h
