#include "../Plotter.h"
#include "../GUI/MiniGUI.h"
#include "gobjects.h"
#include "error.h"
#include "filelib.h"
#include "ginteractors.h"
#include <memory>
#include <vector>
using namespace std;

namespace {
    /* 从窗口边框到内容区域的内边距。 */
    const double kPadding = 20;

    /* 窗口背景色——用于画布以外的所有区域。 */
    const string kWindowColor = "#A4DDED"; // 非摄影蓝：颜色足够深，可以清晰地
                                           // 边框颜色不能太暗，以免边框上的线
                                           // 将不可见

    /* 画布颜色。 */
    const string kCanvasColor = "#FFFFFF"; // 为简单起见，使用纯白色

    class PlotterGUI: public ProblemHandler {
    public:
        PlotterGUI(GWindow& window);

        void actionPerformed(GObservable* obj) override;
        void mousePressed(double x, double y) override;
        void mouseDragged(double x, double y) override;

    protected:
        void repaint() override;

    private:
        void addLine(double x, double y, double width, double height, PenStyle style);

        /* 几何。 */
        double baseX, baseY, scale;

        double lastX, lastY; // 在真实坐标中

        double mouseToX(double mouseX) const;
        double mouseToY(double mouseY) const;

        /* 要绘制的线条。 */
        vector<unique_ptr<GLine>> lines;
        ostringstream commands;

        Temporary<GTextField> mFilename;
        Temporary<GButton> mSave;
        Temporary<GTextField> mColor;
        Temporary<GTextField> mWidth;

        /* 初始化辅助函数。 */
        void calculateGeometry();
        void setUpChrome();
    };

    /* 构造函数设置图形并将我们注册为唯一 GUI。 */
    PlotterGUI::PlotterGUI(GWindow& window) : ProblemHandler(window) {
        setUpChrome();
        calculateGeometry();
    }

    /* 从全局图形系统连接到绘制线条的挂钩。 */
    void PlotterGUI::addLine(double x0, double y0, double x1, double y1, PenStyle style) {
        /* TODO：当 C++14 得到全面支持后，使用 make_unique。 */
        unique_ptr<GLine> line(new GLine(x0 * scale + baseX, -y0 * scale + baseY,
                                         x1 * scale + baseX, -y1 * scale + baseY));
        line->setColor(style.color);
        line->setLineWidth(style.width);
        lines.push_back(move(line));

        requestRepaint();
    }

    /* 计算窗口几何信息——缩放比例、基础 X、基础 Y 等。 */
    void PlotterGUI::calculateGeometry() {
        /* 计算缩放到窗口宽度和高度所需的缩放因子。 */
        double width  = window().getCanvasWidth()  - 2 * kPadding;
        double height = window().getCanvasHeight() - 2 * kPadding;

        scale = min(width, height) / 2.0;

        /* 根据缩放比例计算基础 x 和 y。 */
        baseX = kPadding + width / 2.0;
        baseY = kPadding + height / 2.0;
    }

    /* 设置窗口控件（“装饰”）。 */
    void PlotterGUI::setUpChrome() {
        mFilename = Temporary<GTextField>(new GTextField("(filename)"), window(), "SOUTH");
        mSave     = Temporary<GButton>(new GButton("Save"), window(), "SOUTH");
        mColor    = Temporary<GTextField>(new GTextField("black"), window(), "SOUTH");
        mWidth    = Temporary<GTextField>(new GTextField("1"), window(), "SOUTH");
    }

    void PlotterGUI::repaint() {
        /* 必须在线条上方绘制边框，以防绘图器
         * 越界！
         */
        clearDisplay(window(), kCanvasColor);

        for (const auto& line: lines) {
            window().draw(*line);
        }

        /* 在画布上方、左侧、右侧和下方绘制。 */
        window().setColor(kWindowColor);
        window().fillRect(0, 0, baseX - scale, window().getHeight()); // 左侧
        window().fillRect(baseX + scale, 0, window().getWidth() - baseX - scale, window().getHeight()); // 右侧
        window().fillRect(0, 0, window().getWidth(), baseY - scale);
        window().fillRect(0, baseY + scale, window().getWidth(), window().getHeight() - baseY - scale);
    }

    void PlotterGUI::actionPerformed(GObservable* obj) {
        if (obj == mSave) {
            ofstream output(mFilename->getText());
            output << commands.str();
        }
    }

    void PlotterGUI::mousePressed(double mouseX, double mouseY) {
        commands << "PenUp" << endl;
        commands << "MoveAbs " << mouseToX(mouseX) << " " << mouseToY(mouseY) << endl;
        commands << "PenColor " << mColor->getText() << endl;
        commands << "PenWidth " << mWidth->getText() << endl;
        commands << "PenDown" << endl;

        lastX = mouseToX(mouseX);
        lastY = mouseToY(mouseY);
    }

    void PlotterGUI::mouseDragged(double mouseX, double mouseY) {
        double x = mouseToX(mouseX);
        double y = mouseToY(mouseY);

        commands << "MoveRel " << (x - lastX) << " " << (y - lastY) << endl;

        PenStyle style;
        style.color = mColor->getText();
        style.width = stringToReal(mWidth->getText());
        addLine(lastX, lastY, x, y, style);


        lastX = x;
        lastY = y;

        requestRepaint();
    }

    double PlotterGUI::mouseToX(double x) const {
        return (x - baseX) / scale;
    }
    double PlotterGUI::mouseToY(double y) const {
        return -(y - baseY) / scale;
    }
}

GRAPHICS_HANDLER("Drawing Canvas", GWindow& window) {
    return make_shared<PlotterGUI>(window);
}
