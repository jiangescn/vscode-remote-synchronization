#include "GUI/MiniGUI.h"
#include "Demos/GVector.h"
#include "HumanPyramids.h"
#include "simpio.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <limits>
#include <sstream>
#include <iomanip>
using namespace std;
using namespace MiniGUI;

namespace {
    /* 调色板。 */
    const string kBackgroundColor = "#727472"; // Nickel
    const string kLatticeColor    = "#C46210"; // 合金橙

    /* 人物颜色取决于其上方的权重。 */
    struct ColorEntry {
        double minWeight;
        int red, green, blue;
    };

    /* 按权重分配颜色。条目在边界之间插值。 */
    const vector<ColorEntry> kPersonColors = {
        /* 没有权重？使用纯绿色。 */
        {  0.0, 0x00, 0xFF, 0x00 },

        /* 有一定权重？显示为黄色。 */
        {  400, 0xFF, 0xFF, 0x00 },

        /* 权重很大？显示为橙色。 */
        {  600, 0xFF, 0x80, 0x00 },

        /* 权重令人痛苦？显示为黄色。 */
        {  600, 0xFF, 0x00, 0x00 },

        /* 权重很大？颜色会越来越深。 */
        { 1000, 0x80, 0x00, 0x00 },
        { 5000, 0x00, 0x00, 0x00 },

        /* 最后一项必须大于所有可能的权重。 */
        { numeric_limits<double>::infinity(), 0x00, 0x00, 0x00 },
    };

    /* 绘制金字塔中人物边框时颜色回退的量。 */
    const double kBorderDamper = 0.75;

    /* 滑块常量。 */
    const int kMinHeight     = 1;
    const int kMaxHeight     = 31;
    const int kDefaultHeight = 6;
    const int kMajorTickSize = 5;

    /* 单个人的半径。如果并非所有内容都能容纳，可能需要稍微缩小
     * 能够容纳，但这是首选大小。
     */
    const double kPersonRadius = 20;

    /* 所有人排列在等边三角形晶格中。这是首选边长
     * 其中一个三角形的边长；如果并非所有内容都满足条件，我们可能无法做到
     * 适合。
     */
    const double kLatticeSize  = 60;
    const double kLatticeWidth = 5;

    /* 边长为 1 的等边三角形高度。 */
    const double kEquilateralTriangleHeight = sqrt(3.0) / 2.0;

    /* 窗口边框周围的内边距。 */
    const double kPadding = 75;

    /* 用于绘制人物信息的边界框。 */
    const double kPersonInfoX           = 10;
    const double kPersonInfoY           = 10;
    const double kPersonInfoWidth       = 400;
    const double kPersonInfoHeight      = 100;
    const double kPersonInfoPadding     = 10;
    const string kPersonInfoFillColor   = "#F5FFFA"; // 薄荷奶油色
    const string kPersonInfoBorderColor = "#F0EAD6"; // 蛋壳白

    const Font kPersonInfoFont(FontFamily::SANS_SERIF, FontStyle::NORMAL, 24, kBackgroundColor);

    /* 给定金字塔层数信息，返回边界
     * 应绘制该金字塔的方框，以及要使用的缩放系数
     * 绘制时。
     */
    tuple<GRectangle, double> computeGraphicsParameters(const GRectangle& bounds, int height) {
        /* 计算所需总高度。三角晶格高度完全由
         * 与人数无关，人的大小只影响
         * 当查看顶部和底部伸出的部分时。因此，
         * 晶格的高度就是总层数乘以单层高度
         * 这些三角形的高度，加上一个人的高度。
         *
         * 高度中的 -1 项是因为高度计算层数，
         * 这样做存在栅栏柱问题。
         */
        double figureHeight = (height - 1) * kEquilateralTriangleHeight * kLatticeSize + 2 * kPersonRadius;

        /* 宽度的计算方式类似，但稍容易一些，因为
         * 等边三角形更容易确定。
         */
        double figureWidth = (height - 1) * kLatticeSize + 2 * kPersonRadius;

        /* 如果图形高度超过工作高度，则重新缩放所有内容。 */
        double scaleFactor = min(1.0, bounds.height / figureHeight);
        if (scaleFactor < 1) {
            figureHeight *= scaleFactor;
            figureWidth  *= scaleFactor;
        }

        /* 确定如何将所有内容居中。 */
        double x = bounds.x + (bounds.width  - figureWidth)  / 2.0;
        double y = bounds.y + (bounds.height - figureHeight) / 2.0;

        /* 组装结果。 */
        GRectangle result = { x, y, figureWidth, figureHeight };
        return make_tuple(result, scaleFactor);
    }

    /* 绘制人物所处晶格的线条。输入为
     * 给出，使前两个点形成三角形的一条边，第三个点
     * 该点是三角形上的另一个点，使第三个点夹在
     * 位于 p0 和 p1 之间，如下所示：
     *
     *
     *        p2
     *        /\
     *       /  \
     *     p0 -- p1
     */
    void drawLatticeLines(GWindow& window,
                          const GPoint& p0, const GPoint& p1, const GPoint& p2,
                          int height) {
        /* 边界情况！如果高度为 1，则没有内容可绘制。 */
        if (height == 1) return;

        /* 我们将通过连接 p0 和 p1 绘制晶格，然后向上移动
         * 以适当大小的步长朝 p2 移动。为此我们需要获取
         * 使我们朝 p2 移动的向量。
         */
        GVector p02 = (p2 - p0) / (height - 1);
        GVector p12 = (p2 - p1) / (height - 1);

        /* 绘制线条！ */
        GLine line(0, 0, 0, 0);
        line.setColor(kLatticeColor);
        line.setLineWidth(kLatticeWidth);

        for (int i = 0; i < height; i++) {
            auto src = p0 + p02 * i;
            auto dst   = p1 + p12 * i;

            line.setStartPoint(src);
            line.setEndPoint  (dst);

            window.draw(&line);
        }
    }

    /* 给定晶格信息，返回该晶格的控制点
     * （三角晶格的三个边界点）。这些点的排列方式使得
     * 使 p0 位于顶部，底部 p1 在左、p2 在右。
     */
    tuple<GPoint, GPoint, GPoint> controlPointsFor(const GRectangle& bounds,
                                                   int height,
                                                   double latticeSize, double personRadius) {
        /* 确定晶格的角点，并计入需要留出的缓冲区
         * 用于人物。
         */
        double topY    = bounds.y + personRadius;
        double bottomY = bounds.y + bounds.height - personRadius;
        double width   = latticeSize * (height - 1);

        GPoint p0 { bounds.x + bounds.width / 2, topY };
        GPoint p1 { bounds.x + (bounds.width  - width) / 2, bottomY };
        GPoint p2 { bounds.x + (bounds.width + width) / 2, bottomY };

        return make_tuple(p0, p1, p2);
    }

    /* 绘制晶格（所有人的手臂）。 */
    void drawLattice(GWindow& window, int height, const GRectangle& bounds,
                     double latticeSize, double personRadius) {

        GPoint p0, p1, p2;
        tie(p0, p1, p2) = controlPointsFor(bounds, height, latticeSize, personRadius);

        /* 在图形空间中，三角形如下所示：
         *
         *           p0
         *          /  \
         *         /    \
         *        p1 -- p2
         *
         */
        drawLatticeLines(window, p0, p2, p1, height);
        drawLatticeLines(window, p1, p0, p2, height);
    }

    /* 给定某人背上的重量，返回该人员应使用的颜色。
     * 其工作方式是在颜色表的一对端点之间进行线性插值。
     */
    tuple<int, int, int> colorFor(double weight) {
        /* 向前扫描，直到找到超过我们的边界。这里使用线性搜索
         * 因为颜色数量较少。
         */
        size_t index = 1;
        while (kPersonColors[index].minWeight < weight) {
            index++;
        }

        /* 为简单起见。 */
        const auto& lhs = kPersonColors[index - 1];
        const auto& rhs = kPersonColors[index];

        /* 在线性颜色之间插值。 */
        double alpha = (weight - lhs.minWeight) / (rhs.minWeight - lhs.minWeight);

        int red   = lhs.red   + (rhs.red   - lhs.red  ) * alpha;
        int green = lhs.green + (rhs.green - lhs.green) * alpha;
        int blue  = lhs.blue  + (rhs.blue  - lhs.blue ) * alpha;

        return tie(red, green, blue);
    }

    /* 绘制人体金字塔中的一个人。提供图形坐标，以便
     * 我们知道绘制位置，并提供逻辑坐标 (row, col) 以
     * 确定颜色信息。
     */
    void drawPersonAt(GWindow& window, const GPoint& pt, int row, int col, int pyramidHeight, double radius) {
        int red, green, blue;
        tie(red, green, blue) = colorFor(weightOnBackOf(row, col, pyramidHeight));

        /* 背景 */
        window.setColor(GCanvas::createRgbPixel(red, green, blue));
        window.fillOval(pt.x - radius, pt.y - radius, 2 * radius, 2 * radius);

        /* 边框 */
        red   *= kBorderDamper;
        green *= kBorderDamper;
        blue  *= kBorderDamper;
        window.setColor(GCanvas::createRgbPixel(red, green, blue));
        window.drawOval(pt.x - radius, pt.y - radius, 2 * radius, 2 * radius);
    }

    /* 绘制人体金字塔中的人物。 */
    void drawPeople(GWindow& window, int height, const GRectangle& bounds,
                    double latticeSize, double personRadius) {
        GPoint p0, p1, p2;
        tie(p0, p1, p2) = controlPointsFor(bounds, height, latticeSize, personRadius);

        /* 我们始终在位置 p0 绘制一个人。 */
        drawPersonAt(window, p0, 0, 0, height, personRadius);

        /* 边界情况：如果高度恰好为 1，则只绘制这些内容。 */
        if (height == 1) return;

        /* 否则，获取从 p0 到 p1 的向量，我们在向下移动时使用它
         * 晶格，以及从 p1 到 p2 的方向，移动穿过晶格时会使用它。
         * 根据高度缩放它们，使每个向量表示
         * 将一个人向右或向下移动一格。
         */
        auto down = (p1 - p0) / (height - 1);
        auto left = (p2 - p1) / (height - 1);

        /* 绘制一大群人！ */
        for (int row = 1; row < height; row++) {
            for (int col = 0; col <= row; col++) {
                drawPersonAt(window, p0 + down * row + left * col, row, col, height, personRadius);
            }
        }
    }

    /* 在给定矩形内绘制人体金字塔。 */
    void drawPyramid(GWindow& window, int height,
                     const GRectangle& bounds, double scaleFactor) {
        /* 确定要使用的实际人物半径和晶格大小。 */
        double personRadius = kPersonRadius * scaleFactor;
        double latticeSize  = kLatticeSize  * scaleFactor;

        drawLattice(window, height, bounds, latticeSize, personRadius);
        drawPeople (window, height, bounds, latticeSize, personRadius);
    }

    /* 在方框中绘制文本。 */
    GRectangle drawTextBox(const string& text,
                           const GRectangle& bounds,
                           double padding,
                           const string& fillColor,
                           const string& borderColor,
                           const MiniGUI::Font& font,
                           GWindow& window) {
        auto render = TextRender::construct(text, {
                                                bounds.x + padding, bounds.y + padding,
                                                bounds.width - 2 * padding, bounds.height - 2 * padding
                                            }, font);

        /* 绘制方框。 */
        window.setColor(fillColor);
        window.fillRect(bounds);

        window.setColor(borderColor);
        window.drawRect(bounds);

        /* 绘制文本。 */
        render->draw(window);
        return bounds;
    }

    /* 显示各种人体金字塔并报告其所受重量的问题处理程序
     * 每个人。
     */
    class HumanPyramidsGUI: public ProblemHandler {
    public:
        HumanPyramidsGUI(GWindow& window);

        void changeOccurredIn(GObservable* source) override;
        void mouseMoved(double x, double y) override;
        void windowResized() override;

    protected:
        void repaint() override;

    private:
        /* 控制金字塔高度。 */
        Temporary<GSlider> mHeightSlider;
        int mHeight;

        /* 金字塔本身是否为脏状态。当高度
         * 更改。
         */
        bool mPyramidDirty = true;

        /* 选中了哪个人（如果有）。我们使用 -1 作为
         * 未选中任何人时的哨兵值。
         */
        int mSelectedRow = -1, mSelectedCol = -1;

        /* 所选人员是否为脏状态。当鼠标在
         * 以会改变内容的方式。
         */
        bool mPersonDirty = false;

        /* 所选人员最后一次的边界矩形。 */
        GRectangle mPersonInfo;

        /* 用于放置所有内容的边界矩形。 */
        GRectangle mBounds;

        /* 设置选中的人员。 */
        void select(int row, int col);
        void clearSelection();

        /* 重绘选中的图形项目。 */
        void redrawPyramid(GWindow& window);
        void redrawPersonInfo(GWindow& window);

        void calculateGeometry();
    };


    HumanPyramidsGUI::HumanPyramidsGUI(GWindow& window) : ProblemHandler(window) {
        mHeightSlider = Temporary<GSlider>(new GSlider(kMinHeight, kMaxHeight, kDefaultHeight),
                                           window,
                                           "SOUTH");
        mHeightSlider->setPaintLabels(true);
        mHeightSlider->setPaintTicks(true);
        mHeightSlider->setSnapToTicks(true);
        mHeightSlider->setMajorTickSpacing(kMajorTickSize);
        mHeightSlider->setMinorTickSpacing(1);
        mHeightSlider->setBounds(0, 0, window.getCanvasWidth(), mHeightSlider->getHeight());

        mHeight = kDefaultHeight;

        calculateGeometry();
    }

    void HumanPyramidsGUI::changeOccurredIn(GObservable* source) {
        if (source == mHeightSlider) {
            /* 检查值是否发生变化。如果是，则重绘。 */
            int height = mHeightSlider->getValue();
            if (height != mHeight) {
                mHeight = height;
                mPyramidDirty = true;
                requestRepaint();
            }
        }
    }
    void HumanPyramidsGUI::repaint() {
        if (mPersonDirty) {
            redrawPersonInfo(window());
        }
        if (mPyramidDirty) {
            redrawPyramid(window());

            /* 假装该人员也变脏——需要重绘内容。 */
            mPersonDirty = true;
        }
    }

    void HumanPyramidsGUI::redrawPyramid(GWindow& window) {
        clearDisplay(window, kBackgroundColor);

        GRectangle bounds;
        double scaleFactor;
        tie(bounds, scaleFactor) = computeGraphicsParameters(mBounds, mHeight);

        drawPyramid(window, mHeight, bounds, scaleFactor);

        mPyramidDirty = false;
    }

    void HumanPyramidsGUI::redrawPersonInfo(GWindow& window) {
        /* 清除绘制此信息的区域。 */
        window.setColor(kBackgroundColor);
        window.fillRect(mPersonInfo);

        /* 如果选中了某人，则显示其信息。 */
        if (mSelectedRow != -1 && mSelectedCol != -1) {
            ostringstream builder;
            builder << "Person (" << mSelectedRow << ", " << mSelectedCol << ")" << endl;
            builder << "  Weight on back: "
                    << fixed << setprecision(2) << weightOnBackOf(mSelectedRow, mSelectedCol, mHeight) << endl;

            mPersonInfo = drawTextBox(builder.str(),
                                      {
                                          kPersonInfoX, kPersonInfoY,
                                          kPersonInfoWidth,
                                          kPersonInfoHeight,
                                      },
                                      kPersonInfoPadding,
                                      kPersonInfoFillColor,
                                      kPersonInfoBorderColor,
                                      kPersonInfoFont,
                                      window);
        }

        mPersonDirty = false;
    }

    void HumanPyramidsGUI::mouseMoved(double x, double y) {
        /* 获取图形信息，我们需要用它反转所有内容。 */

        GRectangle bounds;
        double scaleFactor;
        tie(bounds, scaleFactor) = computeGraphicsParameters(mBounds, mHeight);

        /* 为了反转内容，需要知道窗口中各对象的大小。 */
        double latticeSize  = kLatticeSize  * scaleFactor;
        double personRadius = kPersonRadius * scaleFactor;

        /* 获取控制点，用于确定当前位置。 */
        GPoint p0, p1, p2;
        tie(p0, p1, p2) = controlPointsFor(bounds, mHeight, latticeSize, personRadius);

        /* 边界情况！如果高度恰好为 1，则会与一个人重叠
         * 当且仅当位于其半径范围内时。
         */
        GPoint mouse { x, y };
        if (mHeight == 1) {
            if (magnitudeOf(p0 - mouse) <= personRadius) {
                select(0, 0);
            } else {
                clearSelection();
            }
            return;
        }

        /* 获取从 p0 到 p1（向下）和从 p1 到 p2（向左）的向量。缩放应
         * 应选择为：在晶格中向下或横向移动一个单位对应于以下空间中的一个单位：
         * 新的空间。
         */
        auto down = (p1 - p0) / (mHeight - 1);
        auto left = (p2 - p1) / (mHeight - 1);

        /* 向下和向左向量构成晶格空间的一组基。我们希望
         * 从标准空间转换为向下/向左空间，这意味着要计算
         *
         *  | d    l | -1                             -1
         *  | o    e |     | x - p0 |     | d.x  l.x |    |x - p0|
         *  | w    f |     | y - p0 |  =  | d.y  l.y |    |y - p0|
         *  | n    t |
         *
         * 这意味着需要进行以下矩阵计算：
         *
         *           1           |  l.y    -l.x | |x - p0|
         * --------------------  | -d.y     d.x | |y - p0|
         * d.x * ly - l.x * d.y
         *
         *         （det）              （A）            （v）
         */
        double det = down.x * left.y - left.x * down.y;

        auto v = mouse - p0;
        GPoint latticePoint = {
             (left.y * v.x - left.x * v.y) / det,
            (-down.y * v.x + down.x * v.y) / det
        };

        /* 该晶格点几乎肯定是实数值。将坐标舍入到
         * 最近的整数。这绝不会带来问题，因为最近的点
         * 对我们而言，永远不会涉及向相反方向舍入。
         *
         * 由于矩阵列的选择方式，X 坐标对应于
         * 行号对应 Y 坐标，列号对应
         */
        int row = round(latticePoint.x);
        int col = round(latticePoint.y);

        /* 如果该点不是真实人物，则处理结束。 */
        if (row < 0 || row >= mHeight || col < 0 || col > row) {
            clearSelection();
        } else {
            /* 现在，查看鼠标与该位置圆之间的距离。 */
            if (magnitudeOf(mouse - (p0 + down * row + left * col)) <= personRadius) {
                select(row, col);
            } else {
                clearSelection();
            }
        }
    }

    void HumanPyramidsGUI::select(int row, int col) {
        /* 如果它与现有内容相同，则无需执行任何操作。 */
        if (row == mSelectedRow && col == mSelectedCol) return;

        /* 否则，需要重绘内容。 */
        mSelectedRow = row;
        mSelectedCol = col;
        mPersonDirty = true;
        requestRepaint();
    }

    void HumanPyramidsGUI::clearSelection() {
        select(-1, -1);
    }

    void HumanPyramidsGUI::windowResized() {
        calculateGeometry();
        ProblemHandler::windowResized();
    }

    void HumanPyramidsGUI::calculateGeometry() {
        double width  = max(window().getCanvasWidth()  - 2 * kPadding, 2 * kPadding);
        double height = max(window().getCanvasHeight() - 2 * kPadding, 2 * kPadding);

        /* 可使用的空间是整个画布减去各边的内边距。 */
        mBounds = {
            (window().getCanvasWidth() - width) / 2.0, (window().getCanvasHeight() - height) / 2.0,
            width,
            height
        };

        /* 强制重绘所有内容。 */
        mPyramidDirty = mPersonDirty = true;
    }
}

GRAPHICS_HANDLER("Human Pyramids", GWindow& window) {
    return make_shared<HumanPyramidsGUI>(window);
}

CONSOLE_HANDLER("Human Pyramids") {
    do {
        int row    = getInteger("Enter row of person to look up: ");
        int col    = getInteger("Enter column of person to look up: ");
        int height = getInteger("Enter number of rows in the pyramid: ");

        try {
            double result = weightOnBackOf(row, col, height);
            cout << "Weight on that person's back is " << result << endl;
        } catch (const ErrorException& e) {
            cout << "An error occurred. The error message is " << e.what() << endl;
        }

    } while (getYesOrNo("Want to look up another person? "));
}
