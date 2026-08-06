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

    /* 绘图器文件的文件后缀。 */
    const string kFileSuffix = ".plot";

    /* “未选择”选项。 */
    const string kNotSelected = "-";

    /* 加载按钮的文本。 */
    const string kLoadButtonText = "Plot!";

    /* 窗口背景色——用于画布以外的所有区域。 */
    const string kWindowColor = "#A4DDED"; // 非摄影蓝：颜色足够深，可以清晰地
                                           // 边框颜色不能太暗，以免边框上的线
                                           // 将不可见

    /* 画布颜色。 */
    const string kCanvasColor = "#FFFFFF"; // 为简单起见，使用纯白色

    class PlotterGUI: public ProblemHandler {
    public:
        PlotterGUI(GWindow& window);
        ~PlotterGUI();

        void addLine(double x0, double y0, double x1, double y1, PenStyle style);
        void actionPerformed(GObservable* obj) override;
        void windowResized() override;

    protected:
        void repaint() override;

    private:
        /* 几何。 */
        double baseX, baseY, scale;

        /* 要绘制的线条。 */
        struct Line {
            double x0, y0, x1, y1;
            PenStyle style;
        };

        /* 抽象空间中的原始线条。 */
        vector<Line> rawLines;

        /* 要在屏幕上绘制的线条。此列表可能比 rawLines 短
         * 如果有一条已添加但尚未绘制的线，
         * 或窗口调整大小时。务必同步 rawLines 的大小
         * 以及绘制前 displayLines 的大小！
         */
        vector<unique_ptr<GLine>> displayLines;

        /* 两行项目网格。布局如下
         *
         *                     下拉框   加载
         *    ------------------- 状态行 ------------------------
         */
        Temporary<GContainer> container;

        /* 加载文件。 */
        GComboBox*  fileChooser;
        GButton*    loadButton;

        /* 状态报告。 */
        GLabel*     statusLine;

        /* 初始化辅助函数。 */
        void calculateGeometry();
        void setUpChrome();

        /* 重置图形状态。 */
        void clearGraphics();

        /* 使 displayLines 列表与 rawLines 同步。 */
        void createGraphicsLines();
    };

    /* 返回示例目录中找到的所有 plotter 文件。 */
    vector<string> allPlotFiles() {
        vector<string> result;
        for (const auto& file: listDirectory("res/")) {
            if (endsWith(file, kFileSuffix)) {
                result.push_back(file);
            }
        }
        return result;
    }

    /* 噫——全局变量！ */
    PlotterGUI* theGUI = nullptr;

    /* 构造函数设置图形并将我们注册为唯一 GUI。 */
    PlotterGUI::PlotterGUI(GWindow& window) : ProblemHandler(window) {
        if (theGUI) error("Why are there two copies of us?");
        theGUI = this;

        setUpChrome();
        calculateGeometry();
    }

    PlotterGUI::~PlotterGUI() {
        theGUI = nullptr;
    }

    /* 从全局图形系统连接到绘制线条的挂钩。 */
    void PlotterGUI::addLine(double x0, double y0, double x1, double y1, PenStyle style) {
        rawLines.push_back({x0, y0, x1, y1, style});
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
        auto* rawContainer = new GContainer(GContainer::LAYOUT_GRID);

        fileChooser = new GComboBox();
        fileChooser->addItem(kNotSelected); // 初始时不显示任何内容
        for (const string& file: allPlotFiles()) {
            fileChooser->addItem(file);
        }
        fileChooser->setEditable(false);

        loadButton  = new GButton(kLoadButtonText);
        statusLine  = new GLabel("");

        rawContainer->addToGrid(fileChooser, 0, 0);
        rawContainer->addToGrid(loadButton,  0, 1);
        rawContainer->addToGrid(statusLine,  1, 0, 1, 2);

        container = Temporary<GContainer>(rawContainer, window(), "SOUTH");
    }

    void PlotterGUI::repaint() {
        /* 必须在线条上方绘制边框，以防绘图器
         * 越界！
         */
        clearDisplay(window(), kCanvasColor);
        createGraphicsLines();

        for (const auto& line: displayLines) {
            window().draw(*line);
        }

        /* 在画布上方、左侧、右侧和下方绘制。 */
        window().setColor(kWindowColor);
        window().fillRect(0, 0, baseX - scale, window().getHeight()); // 左侧
        window().fillRect(baseX + scale, 0, window().getWidth() - baseX - scale, window().getHeight()); // 右侧
        window().fillRect(0, 0, window().getWidth(), baseY - scale);
        window().fillRect(0, baseY + scale, window().getWidth(), window().getHeight() - baseY - scale);
    }

    void PlotterGUI::createGraphicsLines() {
        /* 将新行添加到列表末尾。 */
        for (size_t i = displayLines.size(); i < rawLines.size(); i++) {
            Line curr = rawLines[i];

            /* TODO：当 C++14 得到全面支持后，使用 make_unique。 */
            unique_ptr<GLine> line(new GLine(curr.x0 * scale + baseX, -curr.y0 * scale + baseY,
                                             curr.x1 * scale + baseX, -curr.y1 * scale + baseY));
            line->setColor(curr.style.color);
            line->setLineWidth(curr.style.width);
            displayLines.push_back(move(line));
        }
    }

    void PlotterGUI::actionPerformed(GObservable* obj) {
        /* 是加载按钮吗？如果是，则加载内容。 */
        if (obj == loadButton) {
            string toLoad = fileChooser->getSelectedItem();
            if (toLoad != kNotSelected) {
                clearGraphics();

                ifstream input("res/" + toLoad);
                runPlotterScript(input);
            }
        }
    }

    void PlotterGUI::clearGraphics() {
        displayLines.clear();
        rawLines.clear();
        requestRepaint();
    }

    void PlotterGUI::windowResized() {
        /* 清除此前显示的所有线条；它们的位置不正确。 */
        displayLines.clear();

        calculateGeometry();
        requestRepaint();
    }
}

/* 学生调用 drawLine 的入口点。 */
void drawLine(double x0, double y0, double x1, double y1, PenStyle style) {
    if (MiniGUI::Config::isConsoleMode()) {
        cout << "Line drawn from (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << "), width " << style.width << ", color " << style.color << endl;
    } else {
        if (theGUI) {
            theGUI->addLine(x0, y0, x1, y1, style);
        }
    }
}

GRAPHICS_HANDLER("Plotter", GWindow& window) {
    return make_shared<PlotterGUI>(window);
}

CONSOLE_HANDLER("Plotter") {
    cout << "The console version of Plotter will display the "
            "coordinates and styles of all lines drawn with the drawLine command." << endl;
    do {
        auto options = allPlotFiles();
        int choice = makeSelectionFrom("Choose a file to plot: ", options);

        ifstream input("res/" + options[choice], ios::binary);
        if (!input) {
            cerr << "Error: Can't open file " << choice << endl;
        } else {
            cout << "Running your script..." << endl;
            runPlotterScript(input);
            cout << "Done." << endl;
        }
    } while (getYesOrNo("Draw another plot? "));
}
