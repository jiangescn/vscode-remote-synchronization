#include "../PlayingFair.h"
#include "../GUI/MiniGUI.h"
#include "ginteractors.h"
#include "simpio.h"
using namespace std;
using namespace MiniGUI;

namespace {
    /* 为避免退化情况而微调世界坐标边界的量。 */
    const double kEpsilon = 0.01;

    /* 线条粗细。 */
    const double kLineWidth = 2;

    /* 从窗口边框到实际晶体的边距。 */
    const double kWindowPadding = 20;

    /* 文本允许达到的最大高度。 */
    const double kFontHeight = 24;

    /* 滑块控件。 */
    const int kMinOrder = 0;
    const int kMaxOrder = 13;
    const int kDefaultOrder = 0;

    /* 前景色和背景色。 */
    const Vector<string> kColors = {
        "#000000",
        "#FFFF00"
    };

    const Font kLabelFont(FontFamily::SERIF, FontStyle::NORMAL, 16, "#00FFFF");

    /* 类型：Geometry
     *
     * 关于每个单元格应有多大以及如何在其中正确显示内容的信息
     * 窗口。
     */
    struct Geometry {
        double minX, minY;   // 任意点的最小 X 和 Y 坐标
        double baseX, baseY; // 从屏幕左上角到内容区域的偏移量
        double scale;        // 从全局坐标转换到窗口坐标的缩放系数
    };

    /* 给定晶体，计算用于绘制它的几何信息。 */
    Geometry geometryFor(const Vector<GPoint>& points, GWindow& window) {
        /* 计算边界框。 */
        double minX =  numeric_limits<double>::infinity();
        double minY =  numeric_limits<double>::infinity();

        double maxX = -numeric_limits<double>::infinity();
        double maxY = -numeric_limits<double>::infinity();

        /* 扩展包围分形所用位置的方框。 */
        for (const auto& loc: points) {
            minX = min(minX, loc.x);
            minY = min(minY, loc.y);

            maxX = max(maxX, loc.x);
            maxY = max(maxY, loc.y);
        }

        /* 将所有内容轻微移动，以避免退化情况。 */
        minX -= kEpsilon;
        minY -= kEpsilon;

        maxX += kEpsilon;
        maxY += kEpsilon;

        /* 获取世界的宽度和高度。 */
        double width  = maxX - minX;
        double height = maxY - minY;

        /* 计算缩放到窗口宽度和高度所需的缩放因子。 */
        double scaleX = (window.getWidth()  - 2 * kWindowPadding) / width;
        double scaleY = (window.getHeight() - 2 * kWindowPadding) / height;
        double scale = min(scaleX, scaleY);

        /* 根据缩放比例计算基础 x 和 y。 */
        double baseX = kWindowPadding + (window.getWidth()  - 2 * kWindowPadding - width  * scale) / 2.0;
        double baseY = kWindowPadding + (window.getHeight() - 2 * kWindowPadding - height * scale) / 2.0;

        return {
            minX, minY,
            baseX, baseY,
            scale
        };
    }

    Vector<GPoint> fractalOfOrder(int n) {
        Vector<GPoint> result;

        GPoint loc(0, 0);

        /* 如果阶数为奇数，默认情况下所有内容都会旋转 180 度，因此需要修正
         * 此项。如果阶数为偶数，它会逆时针旋转 30 度。
         */
        double theta;
        if (n == 0) theta = 0;
        else if (n % 2 == 0) theta = 11 * M_PI / 6;
        else theta = M_PI;

        result += loc;

        for (char ch: aSequenceOfOrder(n)) {
            if (ch == 'A') {
                loc = {
                    loc.x + cos(theta),
                    loc.y + sin(theta)
                };

                result += loc;
                theta += M_PI / 3.0;
            } else if (ch == 'B') {
                theta += M_PI;
            } else {
                error("Unknown character in A-sequence: '" + to_string(ch) + "'.");
            }
        }

        return result;
    }

    void drawFractal(int order, GWindow& window) {
        auto points = fractalOfOrder(order);

        window.setColor(kColors[0]);
        window.fillRect(0, 0, window.getCanvasWidth(), window.getCanvasHeight());

        auto g = geometryFor(points, window);

        /* 为提高效率，只创建一个 GLine。 */
        GLine line;
        line.setColor(kColors[1]);
        line.setLineWidth(kLineWidth);

        for (int i = 0; i + 1 < points.size(); i++) {
            double x0 = g.baseX + (points[i].x - g.minX) * g.scale;
            double y0 = g.baseY + (points[i].y - g.minY) * g.scale;

            double x1 = g.baseX + (points[i+1].x - g.minX) * g.scale;
            double y1 = g.baseY + (points[i+1].y - g.minY) * g.scale;

            line.setStartPoint(x0, y0);
            line.setEndPoint(x1, y1);
            window.draw(line);
        }

        /* 为简单起见，显示阶数。 */
        auto render = TextRender::construct("Derived from order-" + to_string(order) + " A-sequence.",
                                            { kWindowPadding, window.getCanvasHeight() - kWindowPadding - kFontHeight, window.getCanvasWidth() - 2 * kWindowPadding, kFontHeight},
                                            kLabelFont, LineBreak::NO_BREAK_SPACES);
        render->alignCenterVertically();
        render->draw(window);
    }

    class PlayingFairGUI: public ProblemHandler {
    public:
        PlayingFairGUI(GWindow& window);
        void changeOccurredIn(GObservable* source) override;

    protected:
        void repaint() override;

    private:
        Temporary<GSlider> order;
        int lastOrder = kDefaultOrder;
    };

    PlayingFairGUI::PlayingFairGUI(GWindow& window) : ProblemHandler(window) {
        auto* slider = new GSlider(kMinOrder, kMaxOrder, kDefaultOrder);
        slider->setPaintLabels(true);
        slider->setPaintTicks(true);
        slider->setSnapToTicks(true);
        slider->setMajorTickSpacing(1);
        slider->setBounds(0, 0, window.getCanvasWidth(), slider->getHeight());

        order = Temporary<GSlider>(slider, window, "SOUTH");
    }

    void PlayingFairGUI::changeOccurredIn(GObservable* source) {
        if (source == order) {
            int currOrder = order->getValue();
            if (currOrder != lastOrder) {
                lastOrder = currOrder;
                requestRepaint();
            }
        }
    }

    void PlayingFairGUI::repaint() {
        drawFractal(lastOrder, window());
    }
}

GRAPHICS_HANDLER("Playing Fair", GWindow& window) {
    return make_shared<PlayingFairGUI>(window);
}

CONSOLE_HANDLER("Playing Fair") {
    do {
        int n = getInteger("Enter value of n: ");

        try {
            string aSequence = aSequenceOfOrder(n);
            cout << "A-sequence of order " << n << ": " << aSequence << endl;
        } catch (const ErrorException& e) {
            cerr << "An error occurred: " << e.what() << endl;
        }

        try {
            string bSequence = bSequenceOfOrder(n);
            cout << "B-sequence of order " << n << ": " << bSequence << endl;
        } catch (const ErrorException& e) {
            cerr << "An error occurred: " << e.what() << endl;
        }
    } while (getYesOrNo("Choose another order? "));
}
