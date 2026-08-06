#include "GUI/MiniGUI.h"
#include "GVector.h"
#include "Sierpinski.h"
using namespace std;
using namespace MiniGUI;

namespace {
    const string kBackgroundColor = "#FFFFFF";

    /* 滑块选项。 */
    const int kLowOrder     = 0;
    const int kHighOrder    = 8;
    const int kDefaultOrder = 0;

    /* 头部信息。 */
    const string kHeader =
        "Use the slider to change the order of the "
        "triangle. Drag the red ovals to reposition the corners.";

    const Font kHeaderFont(FontFamily::SERIF, FontStyle::ITALIC, 15, "#36454F"); // 炭灰色
    const double kHeaderHeight = 100;
    const double kHeaderPadding   = 10;

    /* 控制点。 */
    const string kControlPointFillColor    = "#C41E3A"; // 基本方向
    const string kControlPointBorderColor  = "#620F1C"; // 半基数方向
    const double kControlPointRadius  = 10;
    const double kControlPointPadding = 25;

    /* 返回 GOval 的中心点。 */
    GPoint centerOf(const GOval* oval) {
        return {
            oval->getX() + oval->getWidth()  / 2.0,
            oval->getY() + oval->getHeight() / 2.0
        };
    }

    GRectangle expand(const GRectangle& rect, double delta) {
        return {
            rect.x - delta, rect.y - delta,
            rect.width + 2 * delta, rect.height + 2 * delta
        };
    }
    GRectangle expand(double x, double y, double width, double height, double delta) {
        return expand({ x, y, width, height }, delta);
    }

    /* 用于可视化不同阶数 Sierpinski 三角形的问题处理程序。 */
    class SierpinskiGUI: public ProblemHandler {
    public:
        SierpinskiGUI(GWindow& window);

        void changeOccurredIn(GObservable* source) override;
        void mousePressed(double x, double y) override;
        void mouseDragged(double x, double y) override;
        void windowResized() override;

        static std::string name();

    protected:
        void repaint() override;

    private:
        Temporary<GSlider> mOrderSlider;
        int  mOrder;

        /* 当前顶点。 */
        GOval* mCornerPoints[3];

        /* 上次鼠标按下的位置。 */
        GPoint mLastMouse;

        /* 上次选中的椭圆。 */
        GOval* mSelected = nullptr;

        /* 可显示三角形的工作区。 */
        GRectangle mWorkspace;

        /* 给定 {x, y} 点，将其限制到工作区内。 */
        GPoint clampToWorkspace(double x, double y) const;

        void calculateGeometry();
    };

    SierpinskiGUI::SierpinskiGUI(GWindow& window) : ProblemHandler(window) {
        mOrderSlider = Temporary<GSlider>(new GSlider(kLowOrder, kHighOrder, kDefaultOrder),
                                          window,
                                          "SOUTH");
        mOrderSlider->setPaintLabels(true);
        mOrderSlider->setPaintTicks(true);
        mOrderSlider->setSnapToTicks(true);
        mOrderSlider->setMajorTickSpacing(1);
        mOrderSlider->setBounds(0, 0, window.getCanvasWidth(), mOrderSlider->getHeight());

        mOrder = kDefaultOrder;

        calculateGeometry();

        /* 将控制点设置到窗口各角。 */
        GPoint corners[3];
        corners[0] = { mWorkspace.x,                        mWorkspace.y + mWorkspace.height };
        corners[1] = { mWorkspace.x + mWorkspace.width,     mWorkspace.y + mWorkspace.height };
        corners[2] = { mWorkspace.x + mWorkspace.width / 2, mWorkspace.y                     };

        for (size_t i = 0; i < 3; i++) {
            mCornerPoints[i] = new GOval(corners[i].x - kControlPointRadius,
                                         corners[i].y - kControlPointRadius,
                                         2 * kControlPointRadius,
                                         2 * kControlPointRadius);
            mCornerPoints[i]->setFilled(true);
            mCornerPoints[i]->setColor(kControlPointBorderColor);
            mCornerPoints[i]->setFillColor(kControlPointFillColor);
            window.add(mCornerPoints[i]);
        }
    }

    void SierpinskiGUI::changeOccurredIn(GObservable* source) {
        if (source == mOrderSlider) {
            /* 检查值是否发生变化。如果是，则重绘。 */
            int order = mOrderSlider->getValue();
            if (order != mOrder) {
                mOrder = order;
                requestRepaint();
            }
        }
    }

    void SierpinskiGUI::repaint() {
        /* 标题文本只需绘制一次。 */
        clearDisplay(window(), kBackgroundColor);

        auto header = TextRender::construct(kHeader, {
                                                kHeaderPadding, kHeaderPadding,
                                                window().getCanvasWidth()  - 2 * kHeaderPadding,
                                                window().getCanvasHeight() - 2 * kHeaderPadding
                                            }, kHeaderFont);
        header->alignCenterHorizontally();
        header->draw(window());

        /* 重绘三角形。 */
        auto p0 = centerOf(mCornerPoints[0]);
        auto p1 = centerOf(mCornerPoints[1]);
        auto p2 = centerOf(mCornerPoints[2]);
        drawSierpinskiTriangle(window(),
                               p0.x, p0.y,
                               p1.x, p1.y,
                               p2.x, p2.y,
                               mOrder);
    }

    void SierpinskiGUI::mousePressed(double x, double y) {
        /* 查看是否点击了任何内容。 */
        GPoint mouse = {x, y};
        for (auto* oval: mCornerPoints) {
            if (magnitudeOf(centerOf(oval) - mouse) <= kControlPointRadius) {
                mSelected = oval;
                mLastMouse = clampToWorkspace(mouse.x, mouse.y);
                return;
            }
        }

        /* 糟糕——什么都没点中。 */
        mSelected = nullptr;
    }

    void SierpinskiGUI::mouseDragged(double x, double y) {
        /* 如果没有选中任何内容，就无需执行操作。 */
        if (mSelected == nullptr) return;

        /* 根据当前点和上一个点之间的增量移动选中的椭圆
         * 点。
         */
        GPoint mouse = clampToWorkspace(x, y);
        auto delta = mouse - mLastMouse;

        mSelected->move(delta.x, delta.y);
        requestRepaint();

        mLastMouse = mouse;
    }

    GPoint SierpinskiGUI::clampToWorkspace(double x, double y) const {
        x = max(min(x, mWorkspace.x + mWorkspace.width),  mWorkspace.x);
        y = max(min(y, mWorkspace.y + mWorkspace.height), mWorkspace.y);

        return { x, y };
    }

    void SierpinskiGUI::calculateGeometry() {
        /* 设置控制点。首先查看绘制标头需要多少空间。 */
        auto headerArea = TextRender::construct(kHeader, {
                                                    kHeaderPadding, kHeaderPadding,
                                                    window().getCanvasWidth()  - 2 * kHeaderPadding,
                                                    kHeaderHeight,
                                                }, kHeaderFont)->computedBounds();

        mWorkspace = expand(0, headerArea.y + headerArea.height,
                            window().getCanvasWidth(),
                            window().getCanvasHeight() - headerArea.y - headerArea.height,
                            -kControlPointPadding);

        /* 如果空间已用尽，则使用头部下方的内容。 */
        if (mWorkspace.height < 0) mWorkspace.height = 0;
    }

    void SierpinskiGUI::windowResized() {
        calculateGeometry();

        /* 移动角点使其位于窗口内，以防窗口缩小。 */
        for (int i = 0; i < 3; i++) {
            double dx = (mCornerPoints[i]->getX() + mCornerPoints[i]->getWidth())  - (mWorkspace.x + mWorkspace.width);
            double dy = (mCornerPoints[i]->getY() + mCornerPoints[i]->getHeight()) - (mWorkspace.y + mWorkspace.height);

            if (dx < 0) dx = 0;
            if (dy < 0) dy = 0;

            mCornerPoints[i]->move(-dx, -dy);
        }

        ProblemHandler::windowResized();
    }
}

GRAPHICS_HANDLER("Interactive Sierpinski", GWindow& window) {
    return make_shared<SierpinskiGUI>(window);
}
