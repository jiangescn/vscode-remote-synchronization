#ifndef GUIUtils_Included
#define GUIUtils_Included

#include "TemporaryComponent.h"
#include "Font.h"
#include "gobjects.h"
#include "ginteractors.h"
#include "gwindow.h"
#include <string>
#include <vector>
#include <tuple>
#include <memory>
#include <functional>

/* 断行模式。可选择在空格处断行，或
 * 原样保留所有词元。
 */
enum class LineBreak {
    BREAK_SPACES,
    NO_BREAK_SPACES
};

/* 类型：TextRender
 *
 * 能够在屏幕上渲染格式美观的文本的对象。
 */
class TextRender {
public:
    /* 文本渲染的边界矩形。第一个选项给出所提供的边界
     * 在构造时提供；如果想充分利用全部空间，这很有用
     * 可用区域。第二个是文本实际所在位置的边界矩形
     * 绘制；如果想只在某一部分后方绘制背景，这会很有用
     * 已使用。
     */
    GRectangle bounds() const;
    GRectangle computedBounds() const;

    /* 预期字体和实际字体。 */
    MiniGUI::Font font() const;
    MiniGUI::Font computedFont() const;

    /* 在指定窗口中绘制此文本渲染对象。 */
    void draw(GWindow& window);
    void draw(GCanvas* canvas);

    /* 更改文本的水平对齐方式。 */
    void alignLeft();
    void alignCenterHorizontally();

    /* 更改文本的垂直对齐方式。 */
    void alignTop();
    void alignCenterVertically();

    /* 布局字符串，使其适合指定矩形。文本可能不会填满
     * 若长度不足，则覆盖该矩形的全部范围。
     *
     * 此函数会尽量遵循字体字符串中指定的字号，但可能
     * 必须缩小字号，才能让内容放得下。
     */
    static std::shared_ptr<TextRender> construct(const std::string& text,
                                                 const GRectangle& bounds,
                                                 const MiniGUI::Font& font,
                                                 LineBreak breakMode = LineBreak::BREAK_SPACES);

private:
    TextRender() = default;
    GRectangle    mBounds;         // 用户指定的边界
    GRectangle    mComputedBounds; // 实际占用的边界。
    MiniGUI::Font mFont;          // 用户指定的字体
    MiniGUI::Font mComputedFont;  // 实际使用的字体

    /* 表示单行文本的类型。 */
    struct TextLine {
        std::string text;
        GPoint      baseline; // 基线所在位置
        double      width;
    };

    std::vector<TextLine> mLines;

    /* 将文本拆分成多行，并不断缩小字体，直至适合给定矩形。
     * 成功时返回 true。
     */
    bool fitText(const std::vector<std::string>& tokens, LineBreak breakMode);
};

/* 类型：LegendRender
 *
 * 能够在屏幕上渲染格式美观的图表图例的对象。
 */
class LegendRender {
public:
    /* 与之前一样，这里有两组边界。第一组是给定边界，其中
     * 图例应当构造的区域。第二个是实际占用的区域。
     */
    GRectangle bounds() const;
    GRectangle computedBounds() const;

    void draw(GWindow& window);

    /* 构造图例渲染对象，其中每个文本字符串使用相同颜色。
     *
     * 输入字符串列表可以短于输入颜色列表，但必须
     * 不能更长。
     */
    static std::shared_ptr<LegendRender> construct(const std::vector<std::string>& strings,
                                                   const std::vector<std::string>& colors,
                                                   const GRectangle& bounds,
                                                   const MiniGUI::Font& font,
                                                   const std::string& borderColor,
                                                   LineBreak breakMode = LineBreak::BREAK_SPACES);

    /* 构造图例渲染对象，其中每个文本字符串都有指定颜色
     *
     * 输入字符串列表可以短于输入颜色列表，但必须
     * 不能更长。
     *
     * 指定字体除颜色外的所有属性都会保留；颜色将
     * 会因项目而异。
     */
    static std::shared_ptr<LegendRender> construct(const std::vector<std::string>& strings,
                                                   const std::vector<std::string>& bulletColors,
                                                   const GRectangle& bounds,
                                                   const std::vector<std::string>& textColors,
                                                   const MiniGUI::Font& font,
                                                   const std::string& borderColor,
                                                   LineBreak breakMode = LineBreak::BREAK_SPACES);

private:
    LegendRender() = default;
    GRectangle mBounds;
    GRectangle mComputedBounds;
    std::vector<std::shared_ptr<TextRender>> mLines;
    std::vector<std::string> mBulletColors;
    std::string mBorderColor;
};

/* 类型：LineGraphRender
 *
 * 能够在屏幕上渲染格式美观的折线图的对象。
 */
class LineGraphRender {
public:
    GRectangle bounds() const;

    void draw(GWindow& window);

    /* 组装折线图渲染器。
     *
     * X、Y 轴会为主刻度分配标签。可以将这些标签留
     * 如果愿意可以留空，但标签数量将根据以下各项的长度推断：
     * 标签列表。
     *
     * 若需要，可将主刻度大小设置为大于零，从而在每条坐标轴上显示次级刻度
     * 将主刻度大小设为大于零的数值。
     *
     * 提供的数据点应归一化到虚拟空间，其中 (0, 0) 是
     * 原点，而 (1, 1) 是折线图的右上角。这些线没有
     * 具有相同数量的数据点，也不必恰好穿过 X 轴刻度线
     * 坐标轴。
     */
    static std::shared_ptr<LineGraphRender> construct(const std::vector<std::vector<GPoint>>& lines,
                                                      const std::vector<std::string>& xLabels,
                                                      const std::vector<std::string>& yLabels,
                                                      std::size_t xMinorTicks,
                                                      std::size_t yMinorTicks,
                                                      const GRectangle& bounds,
                                                      const MiniGUI::Font& xLabelFont,
                                                      const MiniGUI::Font& yLabelFont,
                                                      const std::vector<std::string>& lineColors,
                                                      const std::string& axisColors);

private:
    LineGraphRender() = default;

    /* 坐标轴起点和终点。 */
    GPoint mOrigin, mXEnd, mYEnd;

    /* 行标签和字体。 */
    std::vector<std::string> mXLabels, mYLabels;
    MiniGUI::Font mXLabelFont, mYLabelFont;

    /* 坐标轴参数。 */
    std::string mAxisColor;
    std::size_t mXMinorTicks, mYMinorTicks;

    /* 实际空间（而非虚拟空间）中的线条。 */
    std::vector<std::vector<GPoint>> mLines;
    std::vector<std::string> mLineColors;

    GRectangle mBounds;

    /* 绘制每个组件。 */
    void drawXAxis(GWindow& window) const;
    void drawYAxis(GWindow& window) const;
    void drawLines(GWindow& window) const;
};

/* 清空显示内容，并将其重置为指定颜色。 */
void clearDisplay(GWindow& window, const std::string& backgroundColor);
void clearDisplay(GCanvas* canvas, const std::string& backgroundColor);

/* 给定地球表面坐标和中心坐标，返回
 * 在 Mollweide 投影中显示该坐标所用的 (x, y) 坐标。
 * 返回坐标位于逻辑空间（[-2, +2] × [-1, +1]），需要
 * 在显示之前转换到屏幕坐标空间。
 *
 * 输入的经纬度应使用角度而非弧度。
 */
std::tuple<double, double> mollweideProjectionOf(double latitude, double longitude,
                                                 double centerLongitude = 0.0,
                                                 double centerLatitude  = 0.0);

/* 在 SOUTH 控制台中创建滑块，可在给定年份范围内滑动。 */
Temporary<GSlider> makeYearSlider(GWindow& window, int startYear, int endYear);

/* 创建但不安装一个组合框，其中包含目录内的所有文件
 * 通过给定过滤器，并使用指定默认值。
 */
GComboBox* makeFileSelector(const std::string& baseDir,
                            const std::string& defaultOption,
                            std::function<bool(const std::string&)> filter);

/* 给定边界框和宽高比，返回最大的 GRectangle
 * 既 (1) 适合边界框，又 (2) 具有该宽高比。
 */
GRectangle fitToBounds(const GRectangle& bounds, double aspectRatio);

#endif
