#include "GUIUtils.h"
#include "strlib.h"
#include "filelib.h"
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

namespace {
    /* 自然换行之间使用的行高倍数。 */
    const double kLineSpacing = 1.1;

    /* 段落分隔之间使用的行高倍数。 */
    const double kParagraphSpacing = kLineSpacing + 0.35;

    /* 将字符串词元化为可独立渲染的单元。 */
    vector<string> tokenize(const string& text) {
        istringstream input(text);

        string current;
        vector<string> result;

        while (true) {
            int next = input.get();

            /* 若遇到 EOF，则刷新当前词元并停止。 */
            if (next == EOF) {
                if (!current.empty()) result.push_back(current);
                return result;
            }

            /* 若遇到空格，则刷新当前词元并开始新词元。 */
            if (isspace(char(next))) {
                if (!current.empty()) result.push_back(current);
                current = string(1, char(next));
            }
            /* 否则，这是非空格字符。扩展当前词元，并在需要时刷新
             * 如果它是空白词元。
             */
            else {
                if (!current.empty() && isspace(current[0])) {
                    result.push_back(current);
                    current.clear();
                }

                current += char(next);
            }
        }
    }

    /* 给定字体字符串，将该字体大小减小一个单位。 */
    bool reduceFont(MiniGUI::Font& font) {
        /* 字号不能减小到 1 以下。 */
        if (font.size() <= 1) {
            return false;
        }
        font = font.size(font.size() - 1);
        return true;
    }
}

/***************************/
/******* TextRender ********/
/***************************/

shared_ptr<TextRender> TextRender::construct(const string& text,
                                             const GRectangle& bounds,
                                             const MiniGUI::Font& font,
                                             LineBreak breakMode) {
    /* 将文本拆分为独立词元。 */
    auto tokens = tokenize(text);

    /* 不断尝试使内容适配，并逐步缩小字号，直至成功。
     *
     * TODO：这是一个效率不高的 O(n) 算法。是否改用二分查找？
     */
    shared_ptr<TextRender> result(new TextRender());
    result->mBounds         = bounds;
    result->mFont           = font;
    result->mComputedFont   = font;
    while (true) {
        /* 检查此方法是否可行。 */
        if (result->fitText(tokens, breakMode)) break;

        /* 尝试缩小字号。若无法缩小，则没有可渲染的内容，并且
         * 这没有问题！
         */
        if (!reduceFont(result->mComputedFont)) {
            result->mComputedBounds = {
                result->mBounds.x, result->mBounds.y, 0, 0
            };
            break;
        }
    }

    return result;
}

/* 尝试对文本换行，使其适合边界矩形。成功时返回 true，并
 * 将渲染信息写入输出参数。否则返回 false，并保持
 * 保持不变。
 */
bool TextRender::fitText(const vector<string>& tokens, LineBreak breakMode) {
    /* 设置渲染标签。 */
    GText label("");
    label.setFont(mComputedFont.stanfordCPPLibFontString());

    /* 根据字体度量计算行高。 */
    double lineHeight = label.getFontAscent() + label.getFontDescent();

    /* 记录原始起始坐标。稍后计算时会用到
     * 边界框。
     */
    double renderedWidth = 0;
    double renderedHeight = 0;

    /* 初始位置位于左上角，并向下偏移字体上升部的距离
     * （因为我们沿基线绘制。）
     */
    double x = mBounds.x;
    double y = mBounds.y + label.getFontAscent();

    vector<TextLine> computedLines;
    TextLine currLine;
    currLine.baseline = { x, y };
    currLine.width    = 0;

    /* 开始布局词元。 */
    for (const auto& token: tokens) {
        /* 若这是换行符，则插入硬换行。 */
        if (breakMode == LineBreak::BREAK_SPACES && token == "\n") {
            /* 缓存目前生成的行。 */
            computedLines.push_back(currLine);

            /* 下移到下一行。 */
            x = mBounds.x;
            y += lineHeight * kParagraphSpacing;

            currLine.text = "";
            currLine.width = 0;
            currLine.baseline = { x, y };
        }
        /* 否则，若这是另一种空白词元，则按需向前移动，
         * 但不要调整边界矩形。
         */
        else if (breakMode == LineBreak::BREAK_SPACES && isspace(token[0])) {
            /* 若位于行首，则不执行任何操作。 */
            if (int(x - mBounds.x) != 0) {
                label.setText(token);
                currLine.text += token;
                currLine.width += label.getWidth();
                x += label.getWidth();
            }
        }
        /* 否则，绘制此词元并更新全局边界矩形。 */
        else {
            label.setText(token);

            /* 若放不下，则前进到下一行。 */
            if (breakMode == LineBreak::BREAK_SPACES && x + label.getWidth() > mBounds.x + mBounds.width) {
                /* 写出目前为止的这一行。 */
                computedLines.push_back(currLine);

                x = mBounds.x;
                y += lineHeight * kLineSpacing;

                currLine.text = "";
                currLine.width = 0;
                currLine.baseline = { x, y };
            }

            currLine.text += token;

            /* 向右移动刚添加内容的宽度。 */
            x += label.getWidth();
            currLine.width += label.getWidth();

            /* 更新边界矩形。 */
            renderedWidth  = max(renderedWidth, x - mBounds.x);
            renderedHeight = max(y + label.getFontDescent() - mBounds.y, renderedHeight);

            /* 若越界，则报告错误。 */
            if (renderedWidth > mBounds.width || renderedHeight > mBounds.height) return false;
        }
    }

    /* 处理所有剩余词元。 */
    if (!currLine.text.empty()) {
        computedLines.push_back(currLine);
    }

    mLines = computedLines;
    mComputedBounds = { mBounds.x, mBounds.y, renderedWidth, renderedHeight };
    return true;
}

void TextRender::draw(GWindow& window) {
    draw(window.getCanvas());
}

void TextRender::draw(GCanvas* canvas) {
    GText label;
    label.setFont(mComputedFont.stanfordCPPLibFontString());
    label.setColor(mComputedFont.color());

    for (const auto& line: mLines) {
        label.setLocation(line.baseline);
        label.setText(line.text);
        canvas->draw(&label);
    }
}

GRectangle TextRender::bounds() const {
    return mBounds;
}

GRectangle TextRender::computedBounds() const {
    return mComputedBounds;
}

MiniGUI::Font TextRender::font() const {
    return mFont;
}

MiniGUI::Font TextRender::computedFont() const {
    return mComputedFont;
}

void TextRender::alignLeft() {
    /* 对每一行进行平移，使其贴到初始边界。 */
    for (auto& line: mLines) {
        line.baseline = {
            mBounds.x,
            line.baseline.y
        };
    }
}

void TextRender::alignCenterHorizontally() {
    /* 对每一行进行平移，使其在初始边界内居中。 */
    for (auto& line: mLines) {
        line.baseline = {
            mBounds.x + (mBounds.width - line.width) / 2.0,
            line.baseline.y
        };
    }
}

void TextRender::alignTop() {
    /* 调整每一行，使其到完整边界顶部的相对距离
     * 与它到计算边界顶部的距离一致。
     */
    for (auto& line: mLines) {
        line.baseline = {
            line.baseline.x,
            mBounds.y + (line.baseline.y - mComputedBounds.y)
        };
    }

    /* 同时调整计算得到的边界。 */
    mComputedBounds = {
        mComputedBounds.x,
        mBounds.y,
        mComputedBounds.width,
        mComputedBounds.height
    };
}

void TextRender::alignCenterVertically() {
    /* 确定新计算边界的起始位置。 */
    double newY = mBounds.y + (mBounds.height - mComputedBounds.height) / 2.0;

    /* 调整每一行的 Y 坐标，使它到新 Y 坐标的距离与
     * 它到计算边界的距离。
     */
    for (auto& line: mLines) {
        line.baseline = {
            line.baseline.x,
            newY + (line.baseline.y - mComputedBounds.y)
        };
    }

    /* 同时调整计算得到的边界。 */
    mComputedBounds = {
        mComputedBounds.x,
        newY,
        mComputedBounds.width,
        mComputedBounds.height
    };
}

/***************************/
/****** LegendRender *****/
/***************************/

namespace {
    const double kBulletSize    = 10;
    const double kBulletPadding = 10;
    const double kItemPadding   = 5;
}

shared_ptr<LegendRender> LegendRender::construct(const vector<string>& strings,
                                                 const vector<string>& colors,
                                                 const GRectangle& bounds,
                                                 const vector<string>& textColors,
                                                 const MiniGUI::Font& font,
                                                 const string& borderColor,
                                                 LineBreak breakMode) {
    /* 验证输入。 */
    if (strings.size() > colors.size()) error("Not enough colors to draw legend.");

    /* 设置初始字段。 */
    shared_ptr<LegendRender> result(new LegendRender());
    result->mBounds = bounds;
    result->mBorderColor = borderColor;
    result->mBulletColors = colors;

    /* 尝试使用当前字体大小让所有内容正常显示。若可行则完成；否则减小字号
     * 调整字号并重试。
     *
     * TODO：这里使用了效率不高的 O(n) 算法。是否切换为二分查找？
     */
    MiniGUI::Font currFont = font;
    while (true) {
        /* 当前 x、y 坐标，用于布局文本。 */
        double x = bounds.x;
        double y = bounds.y + kItemPadding;

        vector<shared_ptr<TextRender>> entries;

        /* TODO：若提前失败，是否应短路？ */
        const double bulletSpacing = kBulletSize + 2 * kBulletPadding;
        double width = 0;
        for (size_t i = 0; i < strings.size(); i++) {
            /* 为此项目构造文本渲染对象，并记录它最终所在的位置。 */


            /* 提供不受限的垂直空间。稍后再调整高度。 */
            auto render = TextRender::construct(strings[i], {
                                                    x + bulletSpacing, y,
                                                    bounds.width - bulletSpacing - kItemPadding,
                                                    numeric_limits<double>::max()
                                                }, currFont.color(textColors[i]), breakMode);

            y = render->computedBounds().y + render->computedBounds().height + kItemPadding;
            entries.push_back(render);

            width = max(width, render->computedBounds().width);
        }

        /* 获取净边界框。我们会强制其宽度与给定空间一致
         * 以保持一致性。
         */
        GRectangle computedBounds = {
            bounds.x, bounds.y, bounds.width, y - bounds.y
        };

        /* 是否放得下？ */
        if (computedBounds.height <= bounds.height && computedBounds.width <= bounds.width) {
            result->mComputedBounds = computedBounds;
            result->mLines = entries;
            return result;
        }

        /* 糟糕，放不下。缩小字号后重试。 */
        if (!reduceFont(currFont)) {
            result->mComputedBounds = {
                result->mBounds.x, result->mBounds.y, 0, 0
            };
            return result;
        }
    }
}

shared_ptr<LegendRender> LegendRender::construct(const vector<string>& strings,
                                                 const vector<string>& colors,
                                                 const GRectangle& bounds,
                                                 const MiniGUI::Font& font,
                                                 const string& borderColor,
                                                 LineBreak breakMode) {
    return construct(strings, colors, bounds, vector<string>(strings.size(), font.color()), font, borderColor, breakMode);
}

void LegendRender::draw(GWindow& window) {
    /* 先绘制所有文本项及其对应的项目符号。 */
    for (size_t i = 0; i < mLines.size(); i++) {
        mLines[i]->draw(window);

        /* 绘制项目符号，并在垂直方向居中。 */
        window.setColor(mBulletColors[i]);
        GRectangle bullet = {
            mComputedBounds.x + kBulletPadding,
            mLines[i]->computedBounds().y + mLines[i]->computedBounds().height / 2.0 - kBulletSize / 2.0,
            kBulletSize,
            kBulletSize,
        };
        window.fillRect(bullet);
    }

    /* 绘制整体边界框。 */
    window.setColor(mBorderColor);
    window.drawRect(mComputedBounds);
}

GRectangle LegendRender::bounds() const {
    return mBounds;
}

GRectangle LegendRender::computedBounds() const {
    return mComputedBounds;
}

/***************************/
/***** LineGraphRender *****/
/***************************/

namespace {
    /* 坐标轴线常量。 */
    const double kAxisLineWidth = 2;
    const double kSmallTickSize = 8;
    const double kLargeTickSize = 16;

    /* 刻度线与标签之间的内边距。 */
    const double kTickPadding = 2;

    /* 绘制线条所用常量。 */
    const double kPlottedLineWidth = 5;

    /* 给定标签列表和标签字体，返回一个足够大的边界矩形
     * 足以容纳任意这些标签。
     */
    GDimension labelDimensionsFor(const vector<string>& labels,
                                  const MiniGUI::Font& font) {
        GText measurer;
        measurer.setFont(font.stanfordCPPLibFontString());

        /* 找出所有标签的最大范围。 */
        double maxWidth = 0;
        double maxHeight = 0;

        for (const auto& label: labels) {
            measurer.setLabel(label);

            /* 计算高度时必须考虑上升部和下降部。 */
            maxHeight = max(maxHeight, measurer.getFontAscent() + measurer.getFontDescent());
            maxWidth = max(maxWidth, measurer.getWidth());
        }

        return { maxWidth, maxHeight };
    }

    /* 给定所有 X、Y 轴标签及其字体，返回三个控制点
     * （原点、x 轴终点、y 轴终点），用于定义坐标轴
     */
    tuple<GPoint, GPoint, GPoint>
    axesFor(const GRectangle& bounds,
            const vector<string>& xLabels,
            const vector<string>& yLabels,
            const MiniGUI::Font& xLabelFont,
            const MiniGUI::Font& yLabelFont) {

        double originX = bounds.x;
        double originY = bounds.y + bounds.height;

        double xEnd    = bounds.x + bounds.width;
        double yEnd    = bounds.y;

        /* 标签在所有水平和垂直刻度线上居中绘制。
         * 这意味着标签的一半会分别沿 X、Y 方向伸出
         * 坐标轴的每个端点，这意味着需要预留完整宽度的
         * x 轴上一个完整的 x 轴标签，以及 y 轴上一个完整的 y 轴标签。
         */
        auto xSize = labelDimensionsFor(xLabels, xLabelFont);
        auto ySize = labelDimensionsFor(yLabels, yLabelFont);
        xEnd    -= xSize.width  / 2;
        yEnd    += ySize.height / 2;

        /* 此外，还需要考虑 y 轴标签的宽度以及
         * x 轴标签的高度，因为它们绘制在左侧和下方
         * 分别对应 y 轴。
         *
         * 还需要考虑可能有很大的半个标签伸出
         * 从 X 轴或 Y 轴原点偏移。
         */
        originX += max(ySize.width,  xSize.width  / 2.0);
        originY -= max(xSize.height, ySize.height / 2.0);

        /* 别忘了刻度线的内边距！ */
        originX += kTickPadding;
        originY -= kTickPadding;

        /* 最后，需要在每个方向预留半个刻度线，因为这些刻度
         * 刻度覆盖线条。
         */
        originX += kLargeTickSize / 2.0;
        originY -= kLargeTickSize / 2.0;

        return make_tuple(GPoint(originX, originY), GPoint(xEnd, originY), GPoint(originX, yEnd));
    }
}

shared_ptr<LineGraphRender>
LineGraphRender::construct(const vector<vector<GPoint>>& lines,
                           const vector<string>& xLabels,
                           const vector<string>& yLabels,
                           size_t xMinorTicks,
                           size_t yMinorTicks,
                           const GRectangle& bounds,
                           const MiniGUI::Font& xLabelFont,
                           const MiniGUI::Font& yLabelFont,
                           const vector<string>& lineColors,
                           const string& axisColor) {
    /* 边界情况：若没有至少两个刻度，就无法绘制折线图
     * 分别沿 X 和 Y 方向。
     */
    if (xLabels.size() < 2 || yLabels.size() < 2) error("Insufficiently many ticks.");

    /* 边界情况：每条线都需要一种颜色。 */
    if (lineColors.size() < lines.size()) error("Too few line colors (have " + to_string(lineColors.size()) + ", need " + to_string(lines.size()) + ").");

    shared_ptr<LineGraphRender> result(new LineGraphRender());

    /* 复制基本信息。 */
    result->mXLabelFont  = xLabelFont;
    result->mYLabelFont  = yLabelFont;
    result->mXLabels     = xLabels;
    result->mYLabels     = yLabels;
    result->mAxisColor   = axisColor;
    result->mLineColors  = lineColors;
    result->mXMinorTicks = xMinorTicks;
    result->mYMinorTicks = yMinorTicks;
    result->mBounds      = bounds;

    /* 首要任务：确定标签需要多少空间
     * 在坐标轴上。必须这样做，才能确定
     * 坐标轴所在位置。
     */
    tie(result->mOrigin, result->mXEnd, result->mYEnd) =
            axesFor(bounds, xLabels, yLabels, xLabelFont, yLabelFont);

    /* 现在已有这些坐标点，可以重新映射各条线，使其使用
     * 使用折线图坐标空间，而不是虚拟 [0, 1] 坐标空间。
     */
    double baseX  = result->mOrigin.x;
    double baseY  = result->mOrigin.y;
    double width  = result->mXEnd.x   - result->mOrigin.x;
    double height = result->mOrigin.y - result->mYEnd.y;
    for (const auto& line: lines) {
        vector<GPoint> physical;
        for (const auto& pt: line) {
            physical.push_back({ baseX + width * pt.x, baseY - height * pt.y });
        }
        result->mLines.push_back(physical);
    }

    return result;
}

void LineGraphRender::drawYAxis(GWindow& window) const {
    /* 绘制坐标轴线。 */
    GLine axisLine(mOrigin, mYEnd);
    axisLine.setColor(mAxisColor);
    axisLine.setLineWidth(kAxisLineWidth);
    window.draw(&axisLine);

    /* 绘制刻度线。 */
    GText tickLabel("");
    tickLabel.setColor(mAxisColor);
    tickLabel.setFont(mYLabelFont.stanfordCPPLibFontString());

    /* 实用常量。 */
    const double height  = mOrigin.y - mYEnd.y;
    const double spacing = height / (mYLabels.size() - 1);

    for (size_t i = 0; i < mYLabels.size(); i++) {
        /* 主刻度线。 */
        double y = mOrigin.y - i * spacing;
        double x = mOrigin.x;
        window.setColor(mAxisColor);
        window.drawLine(x - kLargeTickSize / 2.0, y, x + kLargeTickSize / 2.0, y);

        /* 刻度标签。 */
        tickLabel.setLabel(mYLabels[i]);
        window.draw(&tickLabel, x - kLargeTickSize / 2.0 - kTickPadding - tickLabel.getWidth(), y + tickLabel.getFontDescent());

        /* 次级刻度线。 */
        if (i + 1 != mYLabels.size()) {
            for (size_t tick = 0; tick < mYMinorTicks; tick++) {
                /* 想知道这个结果从何而来？这里假设我们正在绘制次级
                 * 将次级刻度线绘制在主刻度线之上，以获得正确间距。
                 */
                double minorY = y - (tick + 1) * (spacing / (mYMinorTicks + 1));
                window.drawLine(x - kSmallTickSize / 2.0, minorY, x + kSmallTickSize / 2.0, minorY);
            }
        }
    }
}

void LineGraphRender::drawXAxis(GWindow& window) const {
    /* 绘制坐标轴线。 */
    GLine axisLine(mOrigin, mXEnd);
    axisLine.setColor(mAxisColor);
    axisLine.setLineWidth(kAxisLineWidth);
    window.draw(&axisLine);

    /* 绘制刻度线。 */
    GText tickLabel("");
    tickLabel.setColor(mAxisColor);
    tickLabel.setFont(mXLabelFont.stanfordCPPLibFontString());

    /* 实用常量。 */
    const double width  = mXEnd.x - mOrigin.x;
    const double spacing = width / (mXLabels.size() - 1);

    for (size_t i = 0; i < mXLabels.size(); i++) {
        double x = mOrigin.x + i * spacing;
        double y = mOrigin.y;

        window.setColor(mAxisColor);
        window.drawLine(x, y - kLargeTickSize / 2.0, x, y + kLargeTickSize / 2.0);

        /* 刻度标签。 */
        tickLabel.setLabel(mXLabels[i]);
        window.draw(&tickLabel, x - tickLabel.getWidth() / 2.0, y + kLargeTickSize / 2.0 + kTickPadding + tickLabel.getFontAscent());

        /* 次级刻度线。 */
        if (i + 1 != mXLabels.size()) {
            for (size_t tick = 0; tick < mXMinorTicks; tick++) {
                /* 想知道这个结果从何而来？这里假设我们正在绘制次级
                 * 将次级刻度线绘制在主刻度线之上，以获得正确间距。
                 */
                double minorX = x + (tick + 1) * (spacing / (mXMinorTicks + 1));
                window.drawLine(minorX, y - kSmallTickSize / 2.0, minorX, y + kSmallTickSize / 2.0);
            }
        }
    }
}

void LineGraphRender::drawLines(GWindow& window) const {
    /* 从后向前绘制各条线。 */
    for (size_t j = mLines.size(); j > 0; --j) {
        GLine line(0, 0, 0, 0);
        line.setLineWidth(kPlottedLineWidth);
        line.setColor(mLineColors[j - 1]);

        for (size_t i = 0; i + 1 < mLines[j - 1].size(); i++) {
            auto src = mLines[j - 1][i];
            auto dst = mLines[j - 1][i + 1];
            line.setStartPoint(src.x, src.y);
            line.setEndPoint(dst.x, dst.y);
            window.draw(&line);
        }
    }
}

GRectangle LineGraphRender::bounds() const {
    return mBounds;
}

void LineGraphRender::draw(GWindow& window) {
    drawXAxis(window);
    drawYAxis(window);
    drawLines(window);
}




/***************************/
/******* 辅助函数 ********/
/***************************/

void clearDisplay(GWindow& window, const std::string& backgroundColor) {
    clearDisplay(window.getCanvas(), backgroundColor);
}
void clearDisplay(GCanvas* canvas, const std::string& backgroundColor) {
    canvas->setColor(backgroundColor);
    canvas->fillRect({ 0, 0, canvas->getWidth(), canvas->getHeight() });
}

/* 此函数背后的数学公式毫不掩饰地（并怀着敬意）取自 Wikipedia：
 *
 *   https://en.wikipedia.org/wiki/Mollweide_projection#Mathematical_formulation
 *
 * 逆向公式比正向公式简单得多。:-)
 *
 * 此函数输出一对实数，范围为 [-2, +2] × [-1, 1]，
 * 随后需要根据窗口大小进行缩放和平移。
 */
tuple<double, double> mollweideProjectionOf(double latitude, double longitude,
                                            double longitudeOffset, double latitudeOffset) {
    /* 调整经度以适配地图。 */
    longitude -= longitudeOffset;
    if (longitude < -180) longitude += 360;
    if (longitude > 180)  longitude -= 360;

    latitude -= latitudeOffset;
    if (latitude < -90)   latitude += 180;
    if (latitude >  90)   latitude  -= 180;

    /* 将角度（从 USGS 获得的单位）转换为弧度。 */
    longitude *= M_PI / 180;
    latitude  *= M_PI / 180;

    /* 没有可直接求解坐标的闭式公式，因此我们会
     * 使用牛顿法尝试逼近解。感谢微积分！
     */
    static const size_t kNumIterations = 100;
    double theta = latitude;
    for (size_t i = 0; i < kNumIterations; i++) {
        theta = theta - (2 * theta + sin(2 * theta) - M_PI * sin(latitude)) / (2 + 2 * cos(2 * theta));
    }

    /* 有了 theta，就可以计算 x 和 y 坐标。 */
    double x = 2 * cos(theta) * longitude / M_PI;
    double y = sin(theta);

    return make_tuple(x, y);
}

Temporary<GSlider> makeYearSlider(GWindow& window, int startYear, int endYear) {
    Temporary<GSlider> result(new GSlider(startYear, endYear, startYear),
                              window,
                              "SOUTH");
    result->setPaintLabels(true);
    result->setPaintTicks(true);
    result->setSnapToTicks(true);
    result->setMajorTickSpacing(10);
    result->setMinorTickSpacing(1);
    result->setBounds(0, 0, window.getCanvasWidth(), result->getHeight());
    return result;
}

namespace {
    /* 给定文件名，返回不含后缀的文件名。 */
    string trimExtensionFrom(const string& filename) {
        auto index = filename.rfind('.');
        return index == string::npos? filename : filename.substr(0, index);
    }
}

/* 用于创建文件选择组合框的实用工具。 */
GComboBox* makeFileSelector(const string& baseDir, const string& defaultOption,
                            function<bool(const string&)> predicate) {
    /* 在此保存文件。 */
    Vector<string> files;

    GComboBox* result = new GComboBox();
    result->addItem(defaultOption);
    for (const string& file: listDirectory(baseDir)) {
        if (predicate(file)) {
            files += file;
        }
    }

    /* 对文件排序。此比较器在比较时会忽略后缀，因此
     * 稳定排序（所有内容已按名称排序）。
     */
    stable_sort(files.begin(), files.end(), [](const string& lhs, const string& rhs) {
        return trimExtensionFrom(lhs) < trimExtensionFrom(rhs);
    });

    /* 对所有内容排序。 */
    for (string file: files) {
        result->addItem(file);
    }

    result->setEditable(false);
    return result;
}

/* 使边界适配宽高比。 */
GRectangle fitToBounds(const GRectangle& bounds, double aspectRatio) {
    double width, height;

    /* 太窄了吗？ */
    if (bounds.width / bounds.height <= aspectRatio) {
        width = bounds.width;
        height = width / aspectRatio;
    } else {
        height = bounds.height;
        width = height * aspectRatio;
    }

    double baseX = bounds.x + (bounds.width  - width)  / 2.0;
    double baseY = bounds.y + (bounds.height - height) / 2.0;

    return { baseX, baseY, width, height };
}
