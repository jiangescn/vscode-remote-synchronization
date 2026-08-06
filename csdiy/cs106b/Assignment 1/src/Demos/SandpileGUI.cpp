#include "../GUI/MiniGUI.h"
#include "../Sandpiles.h"
#include "grid.h"
#include "gwindow.h"
#include "hashmap.h"
#include "ginteractors.h"
#include "gtimer.h"
#include <iostream>
#include <cctype>
#include <vector>
using namespace std;
using namespace MiniGUI;

namespace {
    const vector<int> kAdvanceRates = {
        1,
        2,
        4,
        8,
        16,
        32,
        64,
        128,
        256,
        512,
        1024,
        2048,
    };

    const Font kLegendFont(FontFamily::MONOSPACE, FontStyle::BOLD, 14, "#343434"); // Jet
    const double kFontHeight = 24;


    /* 帧之间的暂停时间。 */
    const double kPauseTime = 100;

    /* 世界内边距。 */
    const double kPadding = 30;

    /* 最大单元格尺寸。 */
    const double kMaxCellSize = 10;

    /* 世界尺寸。 */
    const vector<string> kSizeClasses = {
        "Tiny",
        "Small",
        "Medium",
        "Large",
        "Huge"
    };

    /* 尺寸类别。 */
    const HashMap<string, pair<int, int>> kSizes = {
        { "Tiny",   {  15,  15 } },
        { "Small",  {  31,  31 } },
        { "Medium", {  63,  63 } },
        { "Large",  { 127, 127 } },
        { "Huge",   { 255, 255 } },
    };

    /* 背景色和单元格颜色。 */
    const string kBackgroundColor = "#727472"; // Nickel
    const Vector<string> kColors = {
        "#000000",
        "#303080",
        "#8080A0",
        "#CFCFFF"
    };

    struct Geometry {
        double baseX, baseY;
        double cellSize;
    };

    Geometry geometryFor(const Grid<int>& world, GWindow& window) {
        /* 计算缩放到窗口宽度和高度所需的缩放因子。 */
        double width  = window.getCanvasWidth()  - 2 * kPadding;
        double height = window.getCanvasHeight() - 2 * kPadding;

        double scaleX = width  / world.numCols();
        double scaleY = height / world.numRows();
        double scale = min({ scaleX, scaleY, kMaxCellSize });

        /* 根据缩放比例计算基础 x 和 y。 */
        double baseX = kPadding + (width  - world.numCols() * scale) / 2.0;
        double baseY = kPadding + (height - world.numRows() * scale) / 2.0;

        return {
            baseX, baseY,
            scale
        };
    }

    void drawWorld(const Grid<int>& world, GWindow& window) {
        /* 清空整个显示区域。 */
        window.setColor(kBackgroundColor);
        window.fillRect(0, 0, window.getCanvasWidth(), window.getCanvasHeight());

        auto g = geometryFor(world, window);

        /* 优化：不绘制空单元格。 */
        window.setColor(kColors[0]);
        window.fillRect(g.baseX, g.baseY, world.numCols() * g.cellSize, world.numRows() * g.cellSize);

        GRect toDraw(0, 0, g.cellSize, g.cellSize);
        toDraw.setFilled(true);

        for (int row = 0; row < world.numRows(); row++) {
            for (int col = 0; col < world.numCols(); col++) {
                /* 优化：不绘制空单元格。 */
                if (world[row][col] == 0) continue;

                double x = col * g.cellSize + g.baseX;
                double y = row * g.cellSize + g.baseY;

                toDraw.setLocation(x, y);
                toDraw.setFillColor(kColors[world[row][col]]);
                toDraw.setColor(kColors[world[row][col]]);
                window.draw(toDraw);
            }
        }
    }

    /* 在数字字符串中插入逗号。 */
    string addCommasTo(int val) {
        string asStr = to_string(val);
        const int length = int(asStr.length());

        string result;
        for (int i = 0; i < length; i++) {
            /* 从源字符串末尾向前遍历，以确定逗号应放在何处
             * 会简单得多。
             */
            result = asStr[length - 1 - i] + result;

            /* 若已添加三个字符但尚未
             * 即将用完所有数字。
             */
            if (i % 3 == 2 && i < length - 1) {
                result = ',' + result;
            }
        }
        return result;
    }

    /* 渲染说明已投放沙粒数量的图例。 */
    void drawLegend(int grainsDropped, GWindow& window) {
        GRectangle bounds {
            0, window.getCanvasHeight() - kFontHeight,
            window.getCanvasWidth(),
            kFontHeight
        };

        string text = addCommasTo(grainsDropped) + (grainsDropped == 1? " sand grain dropped." : " sand grains dropped.");

        auto render = TextRender::construct(text, bounds, kLegendFont, LineBreak::NO_BREAK_SPACES);
        render->alignCenterVertically();
        render->draw(window);
    }

    /* 用于可视化不断增长沙堆的问题处理程序。 */
    class SandpileGUI: public ProblemHandler {
    public:
        SandpileGUI(GWindow& window);
        void actionPerformed(GObservable* source) override;
        void timerFired() override;

    protected:
        void repaint() override;

    private:
        /* 世界的当前状态。 */
        Grid<int> world;

        /* 用于驱动操作的计时器。 */
        unique_ptr<GTimer> timer;

        /* 用于控制世界大小的按钮。 */
        Temporary<GLabel> sizeLabel;
        vector<Temporary<GButton>> sizeButtons;

        /* 用于控制速度的滑块。 */
        Temporary<GLabel> speedLabel;
        Temporary<GSlider> speedControl;

        /* 我们已经投放的沙粒数量。 */
        int grainsDropped = 0;
    };

    SandpileGUI::SandpileGUI(GWindow& window) : ProblemHandler(window) {
        world.resize(kSizes["Medium"].first, kSizes["Medium"].second);

        /* 尺寸按钮。 */
        sizeLabel = Temporary<GLabel>(new GLabel("World Size: "), window, "SOUTH");
        for (const auto& size: kSizeClasses) {
            sizeButtons.emplace_back(new GButton(size), window, "SOUTH");
        }

        /* 速度控制。 */
        speedLabel = Temporary<GLabel>(new GLabel("Drop rate: "), window, "SOUTH");
        GSlider* slider = new GSlider(0, kAdvanceRates.size() - 1, 0);
        slider->setPaintTicks(true);
        speedControl = Temporary<GSlider>(slider, window, "SOUTH");

        timer.reset(new GTimer(kPauseTime));
        timer->start();
    }

    void SandpileGUI::repaint() {
        drawWorld(world, window());
        drawLegend(grainsDropped, window());
    }

    void SandpileGUI::actionPerformed(GObservable* source) {
        /* 如果来源是我们的某个按钮，则更改世界大小。 */
        auto itr = find(sizeButtons.begin(), sizeButtons.end(), source);
        if (itr != sizeButtons.end()) {
            auto size = kSizes[(*itr)->getText()];
            world.resize(size.first, size.second);
            world.fill(0);
            grainsDropped = 0;
            requestRepaint();
        }
    }

    void SandpileGUI::timerFired() {
        int numSteps = kAdvanceRates[speedControl->getValue()];
        for (int i = 0; i < numSteps; i++) {
            dropSandOn(world, world.numRows() / 2, world.numCols() / 2);
            ++grainsDropped;
        }
        requestRepaint();
    }
}

GRAPHICS_HANDLER("Sandpiles", GWindow& window) {
    return make_shared<SandpileGUI>(window);
}

namespace {
    void drawWorld(const Grid<int>& world) {
        cout << "Current configuration:" << endl;
        for (int row = 0; row < world.numRows(); row++) {
            for (int col = 0; col < world.numCols(); col++) {
                cout << world[row][col] << " ";
            }
            cout << endl;
        }
    }
}

CONSOLE_HANDLER("Sandpiles") {
    Grid<int> world(5, 5);
    drawWorld(world);
    while (getYesOrNo("Drop a grain of sand in the middle? ")) {
        dropSandOn(world, world.numRows() / 2, world.numCols() / 2);
        drawWorld(world);
    }
}
