#include "GUI/MiniGUI.h"
#include "Sierpinski.h"
#include "GVector.h"
#include "gtimer.h"
#include <algorithm>
using namespace std;

namespace {
    const string kBackgroundColor = "#FFFFFF";
    const string kBorderColor     = "#4C516D"; // Independence

    /* 计时参数。 */
    const int    kFramesPerSecond = 100;
    const double kPauseTime = 1000.0 / kFramesPerSecond;
    const int    kFramesPerAnimation = 100;

    /* 三角形参数。 */
    const int kOrder = 8;

    /* 边长为 1 的等边三角形高度。 */
    const double kEquilateralHeight = sqrt(3.0) / 2.0;

    /* 计算三个点的重心。 */
    GPoint centroidOf(const GPoint& p0, const GPoint& p1, const GPoint& p2) {
        return {
            (p0.x + p1.x + p2.x) / 3.0,
            (p0.y + p1.y + p2.y) / 3.0
        };
    }


    /* 用于深入探索 Sierpinski 三角形的问题处理程序。 */
    class SierpinskiBungeeJumpGUI: public ProblemHandler {
    public:
        SierpinskiBungeeJumpGUI(GWindow& window);
        ~SierpinskiBungeeJumpGUI();

        void timerFired() override;
        void windowResized() override;

    protected:
        void repaint() override;

    private:
        GTimer* mTimer;
        int    mFrame = 0; // 当前处于哪个动画帧

        GPoint mPoints[3];       // 三角形的控制点
        GPoint mCentroid;        // 旋转中心

        void calculateGeometry();
    };

    SierpinskiBungeeJumpGUI::SierpinskiBungeeJumpGUI(GWindow& window) : ProblemHandler(window), mTimer(new GTimer(kPauseTime)) {
        mTimer->start();
        calculateGeometry();
    }

    SierpinskiBungeeJumpGUI::~SierpinskiBungeeJumpGUI() {
        /* TODO：GTimer 中似乎存在一个错误，如果我们使用
         * 此处实际使用 GTimer 对象，而不是指向它的指针。请修复泄漏并
         * 删除此析构函数。
         */
        mTimer->stop();
    }

    void SierpinskiBungeeJumpGUI::timerFired() {
        if (mTimer->isStarted()) {
            mFrame++;
            if (mFrame == kFramesPerAnimation) mFrame = 0;

            requestRepaint();
        }
    }

    void SierpinskiBungeeJumpGUI::repaint() {
        clearDisplay(window(), kBackgroundColor);

        /* 查看当前动画进度。 */
        double alpha = mFrame / double(kFramesPerAnimation);

        /* 假设我们有这个初始三角形
         *
         *            p2
         *            /\
         *           /--\
         *          /\  /\
         *         /--\/--\
         *        /\      /\
         *       /--\   C/--\
         *      /\  /\  /\  /\
         *     /--\/--\/--\/--\
         *    p0      A^^^^B  p1
         *
         * 我们希望最终满足
         *
         *     点 A 最终位于 p2 原来的位置，
         *     点 B 最终位于 p0 原来的位置，并且
         *     点 C 最终位于 p1 原来的位置。
         *
         * 这对应于
         *
         *     1. 将整个图形绕三角形 ABC 的重心旋转 120 度，然后
         *     2. 将整个图形的大小加倍，并以 ABC 的重心为中心。
         *
         * 我们将根据目前完成的进度计算旋转和缩放。
         *
         * 还需要考虑最后一个影响。如果我们单纯地放大到此处的中心
         * 三角形时，我们最终会查看纯空白区域。还需要稍微平移
         * 将所有内容稍微平移；具体来说，使顶部的三角形成为新的
         * 中心点。
         *
         * 为此，我们将计算该新三角形的质心，并随
         * 移入位置。
         */

        GPoint sticky = mPoints[0];
        auto anchor = centroidOf(mPoints[0] + (sticky - mPoints[0]) / 2,
                                 mPoints[1] + (sticky - mPoints[1]) / 2,
                                 mPoints[2] + (sticky - mPoints[2]) / 2);


        /* 围绕该点旋转所有内容。 */
        double theta = alpha * 2 * M_PI / 3;
        GPoint p0 = mCentroid + (rotate(mPoints[0] - mCentroid, theta));
        GPoint p1 = mCentroid + (rotate(mPoints[1] - mCentroid, theta));
        GPoint p2 = mCentroid + (rotate(mPoints[2] - mCentroid, theta));
        anchor    = mCentroid + (rotate(anchor     - mCentroid, theta));

        /* 围绕该点缩放所有内容。 */
        p0     += alpha * (p0     - mCentroid);
        p1     += alpha * (p1     - mCentroid);
        p2     += alpha * (p2     - mCentroid);
        anchor += alpha * (anchor - mCentroid);

        /* 根据锚点确定所有内容需要偏移多少。 */
        auto shift = (mCentroid - anchor) * alpha;

        p0 += shift;
        p1 += shift;
        p2 += shift;

        /* 绘制我们的三角形！ */
        drawSierpinskiTriangle(window(),
                               p0.x, p0.y,
                               p1.x, p1.y,
                               p2.x, p2.y,
                               kOrder);

        /* 绘制边框，以避免暴露旋转完成时的细节，即
         * 三角形实际上并不像原始结构那样与同一区域中的相邻三角形相邻
         * 那个是什么。:-)
         */
        window().setColor(kBorderColor);

        /* 各边 */
        window().fillRect(0, 0, mPoints[0].x, window().getCanvasHeight());
        window().fillRect(mPoints[1].x, 0, window().getCanvasWidth() - mPoints[1].x, window().getCanvasHeight());

        /* 顶部和底部 */
        window().fillRect(0, 0, window().getCanvasWidth(), mPoints[2].y);
        window().fillRect(0, mPoints[0].y, window().getCanvasWidth(), window().getCanvasHeight() - mPoints[0].y);
    }

    void SierpinskiBungeeJumpGUI::calculateGeometry() {
        /* 我们希望三角形是尽可能大的等边三角形
         * 同时仍能放入窗口。假定我们
         * 具有单位三角形。
         */
        double scale  = min(window().getCanvasWidth(), window().getCanvasHeight() / kEquilateralHeight);
        double width  = 1.0 * scale;
        double height = kEquilateralHeight * scale;

        /* 使用它计算原点。 */
        double baseX = (window().getCanvasWidth()  - width)  / 2.0;
        double baseY = (window().getCanvasHeight() - height) / 2.0;

        /* 计算三角形各顶点的位置。 */
        mPoints[0] = { baseX,             baseY + height };
        mPoints[1] = { baseX + width,     baseY + height };
        mPoints[2] = { baseX + width / 2, baseY          };

        mCentroid = centroidOf(mPoints[0], mPoints[1], mPoints[2]);
    }

    void SierpinskiBungeeJumpGUI::windowResized() {
        calculateGeometry();
        ProblemHandler::windowResized();
    }
}

GRAPHICS_HANDLER("Sierpinski Bungee Jump", GWindow& window) {
    return make_shared<SierpinskiBungeeJumpGUI>(window);
}
