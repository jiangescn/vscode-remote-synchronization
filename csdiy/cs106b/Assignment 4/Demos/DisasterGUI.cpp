#include "GUI/MiniGUI.h"
#include "DisasterParser.h"
#include <fstream>
#include <memory>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>
#include "filelib.h"
#include "strlib.h"
#include "gthread.h"
#include "simpio.h"
#include <regex>
using namespace std;
using namespace MiniGUI;

namespace {
    /* 文件常量。 */
    const string kProblemSuffix = ".dst";
    const string kBasePath = "res/disaster-planning/";

    /* 背景色。 */
    const string kBackgroundColor  = "#000000";

    /* 绘制网络时使用的颜色。 */
    struct CityColors {
        string borderColor;
        string fillColor;
        Font   font;
    };

    enum CityState { // “城市所在的州”，而不是“新加坡”。:-)
        UNCOVERED,
        COVERED_INDIRECTLY,
        COVERED_DIRECTLY
    };

    /* 绘制城市时使用的颜色。 */
    const vector<CityColors> kCityColors = {
        { "#101010", "#202020", Font(FontFamily::MONOSPACE, FontStyle::BOLD, 12, "#A0A0A0") },   // 未覆盖
        { "#303060", "#404058", Font(FontFamily::MONOSPACE, FontStyle::BOLD, 12, "#C0C0C0") },   // 间接覆盖
        { "#806030", "#FFDF80", Font(FontFamily::MONOSPACE, FontStyle::BOLD, 12, "#000000") },   // 直接覆盖
    };

    /* 用于绘制道路的颜色。 */
    const string kDarkRoadColor    = "#505050";
    const string kLightRoadColor   = "#FFFFFF";

    /* 线条粗细选项。 */
    const double kRoadWidth = 3;
    const double kCityWidth = 1.5;

    /* 城市标签使用的字体。 */
    const string kLabelFont        = "Monospace-BOLD-12";

    /* 城市半径 */
    const double kCityRadius = 25;

    /* 窗口周围的缓冲空间。 */
    const double kBufferSpace = 60;

    /* 数据范围宽度或高度的下限，用于
     * 共线点。
     */
    const double kLogicalPadding = 1e-5;

    /* 标签中字符串的最大长度。 */
    const string::size_type kMaxLength = 3;

    /* 绘制网络的几何信息。 */
    struct Geometry {
        /* 数据集中 X 和 Y 值的范围，用于
         * 缩放所有内容。
         */
        double minDataX, minDataY, maxDataX, maxDataY;

        /* 绘制所有内容时使用的 X 和 Y 值范围。 */
        double minDrawX, minDrawY, maxDrawX, maxDrawY;
    };

    /* 给定数据集，填入最小和最大 X、Y 值
     * 在该集合中遇到。
     */
    void computeDataBounds(const DisasterTest& network, Geometry& geo) {
        geo.minDataX = geo.minDataY = numeric_limits<double>::infinity();
        geo.maxDataX = geo.maxDataY = -numeric_limits<double>::infinity();

        for (const string& cityName: network.cityLocations) {
            geo.minDataX = min(geo.minDataX, network.cityLocations[cityName].x);
            geo.minDataY = min(geo.minDataY, network.cityLocations[cityName].y);

            geo.maxDataX = max(geo.maxDataX, network.cityLocations[cityName].x);
            geo.maxDataY = max(geo.maxDataY, network.cityLocations[cityName].y);
        }

        /* 扩展边界。这处理一组边界为以下情况的边界问题
         * 退化。
         */
        geo.minDataX -= kLogicalPadding;
        geo.minDataY -= kLogicalPadding;
        geo.maxDataX += kLogicalPadding;
        geo.maxDataY += kLogicalPadding;
    }

    /* 获得数据边界后，可以计算图形边界，
     * 它会尽可能充分利用宽度和高度
     * 我们可使用的内容。
     */
    void computeGraphicsBounds(GWindow& window, Geometry& geo) {
        /* 获取窗口的宽高比。 */
        double winWidth  = window.getCanvasWidth()  - 2 * kBufferSpace;
        double winHeight = window.getCanvasHeight() - 2 * kBufferSpace;
        double winAspect = winWidth / winHeight;

        /* 获取数据集的宽高比。 */
        double dataAspect = (geo.maxDataX - geo.minDataX) / (geo.maxDataY - geo.minDataY);

        double dataWidth, dataHeight;

        /* 如果数据宽高比超过窗口宽高比，
         * 显示中的限制因素将是
         * 宽度。因此，我们将用它来确定有效的
         * 宽度和高度。
         */
        if (dataAspect >= winAspect) {
            dataWidth = winWidth;
            dataHeight = dataWidth / dataAspect;
        } else {
            dataHeight = winHeight;
            dataWidth = dataAspect * dataHeight;
        }

        /* 现在，将其在窗口中居中。 */
        geo.minDrawX = (winWidth  -  dataWidth) / 2.0 + kBufferSpace;
        geo.minDrawY = (winHeight - dataHeight) / 2.0 + kBufferSpace;

        geo.maxDrawX = geo.minDrawX + dataWidth;
        geo.maxDrawY = geo.minDrawY + dataHeight;
    }

    /* 给定道路网络，确定其几何信息。 */
    Geometry geometryFor(GWindow& window, const DisasterTest& network) {
        Geometry result;
        computeDataBounds(network, result);
        computeGraphicsBounds(window, result);
        return result;
    }

    /* 将逻辑空间中的坐标转换为以下空间中的坐标：
     * 物理空间。
     */
    GPoint logicalToPhysical(const GPoint& pt, const Geometry& geo) {
        double x = ((pt.x - geo.minDataX) / (geo.maxDataX - geo.minDataX)) * (geo.maxDrawX - geo.minDrawX) + geo.minDrawX;
        double y = ((pt.y - geo.minDataY) / (geo.maxDataY - geo.minDataY)) * (geo.maxDrawY - geo.minDrawY) + geo.minDrawY;

        return { x, y };
    }

    /* 绘制网络中的所有道路，并高亮以下道路：
     * 与已点亮的城市相邻。
     */
    void drawRoads(GWindow& window,
                   const Geometry& geo,
                   const DisasterTest& network,
                   const Set<string>& selected) {
        /* 为提高效率，只创建一条线。 */
        GLine toDraw;
        toDraw.setLineWidth(kRoadWidth);

        for (const string& source: network.network) {
            for (const string& dest: network.network[source]) {
                /* 选中的道路以亮色绘制；未选中的道路
                 * 道路以深色绘制。
                 */
                toDraw.setColor((selected.contains(source) || selected.contains(dest))? kLightRoadColor : kDarkRoadColor);

                /* 绘制线段，记住坐标位于
                 * 逻辑空间而不是物理空间。
                 */
                auto src = logicalToPhysical(network.cityLocations[source], geo);
                auto dst = logicalToPhysical(network.cityLocations[dest], geo);
                toDraw.setStartPoint(src.x, src.y);
                toDraw.setEndPoint(dst.x, dst.y);

                window.draw(toDraw);
            }
        }
    }

    /* 返回给定城市名称的缩写。我们使用前几个
     * 如果名称是单个单词，则使用其前三个字母；否则使用
     * 其首字母缩写。
     */
    string shorthandFor(const string& name) {
        auto components = stringSplit(name, " ");
        if (components.size() == 0) {
            error("It shouldn't be possible for there to be no components of the city name.");
            return "";
        } else if (components.size() == 1) {
            if (components[0].length() < kMaxLength) return components[0];
            else return components[0].substr(0, 3);
        } else {
            /* 使用姓名首字母。 */
            string result;
            for (size_t i = 0; result.length() < kMaxLength && i < components.size(); i++) {
                /* 跳过空组件；如果以下内容中有连续空格，可能会出现空组件
                 * 名称
                 */
                if (!components[i].empty()) {
                    result += components[i][0];
                }
            }
            return result;
        }
    }

    /* 绘制所有城市，并高亮位于以下集合中的城市：
     * 选中的集合。
     */
    void drawCities(GWindow& window,
                    const Geometry& geo,
                    const DisasterTest& network,
                    const Set<string>& selected) {

        /* 为简单起见，只创建一个椭圆。 */
        GOval oval(0, 0, 2 * kCityRadius, 2 * kCityRadius);
        oval.setLineWidth(kCityWidth);
        oval.setFilled(true);

        for (const string& city: network.network) {
            /* 确定城市在屏幕上的中心。 */
            auto center = logicalToPhysical(network.cityLocations[city], geo);

            /* 查看城市在覆盖方面处于何种状态。 */
            CityState state = UNCOVERED;
            if (selected.contains(city)) state = COVERED_DIRECTLY;
            else if (!(selected * network.network[city]).isEmpty()) state = COVERED_INDIRECTLY;

            /* 无法通过一次调用绘制带边框的实心圆。 */
            oval.setColor(kCityColors[state].borderColor);
            oval.setFillColor(kCityColors[state].fillColor);
            window.draw(oval,
                        center.x - kCityRadius,
                        center.y - kCityRadius);

            /* 设置标签文本和颜色。 */
            auto render = TextRender::construct(shorthandFor(city), {
                                                    center.x - kCityRadius,
                                                    center.y - kCityRadius,
                                                    2 * kCityRadius,
                                                    2 * kCityRadius
                                                }, kCityColors[state].font);
            render->alignCenterHorizontally();
            render->alignCenterVertically();
            render->draw(window);
        }
    }

    void visualizeNetwork(GWindow& window,
                          const DisasterTest& network,
                          const Set<string>& selected) {
        clearDisplay(window, kBackgroundColor);

        /* 边界情况：如果窗口太小，则不绘制。 */
        if (window.getCanvasWidth()  <= 2 * kBufferSpace ||
            window.getCanvasHeight() <= 2 * kBufferSpace) {
            return;
        }

        /* 存在一个奇怪的边界情况：如果没有城市，
         * 无法正确计算窗口几何形状。因此，
         * 如果没有内容可绘制，我们将跳过所有这些逻辑。
         */
        if (!network.network.isEmpty()) {
            Geometry geo = geometryFor(window, network);

            /* 先绘制道路再绘制城市，以避免奇怪的图形
             * 伪影。
             */
            drawRoads(window, geo, network, selected);
            drawCities(window, geo, network, selected);
        }
    }

    vector<string> sampleProblems(const string& basePath) {
        vector<string> result;
        for (const auto& file: listDirectory(basePath)) {
            if (endsWith(file, kProblemSuffix)) {
                result.push_back(file);
            }
        }
        return result;
    }

    /* 使用二分搜索找出灾害
     * 准备度，并用最少城市组填充结果字段
     * 最终需要的内容。
     */
    void solveOptimally(const DisasterTest& test, Set<string>& result) {
        /* 变量 low 是可能可行的最小数值。
         * 变量 high 是我们已知可行的最大数值。
         */
        int low = 0, high = test.network.size();

        /* 从一个使用任意数量城市的可行解开始。 */
        (void) canBeMadeDisasterReady(test.network, high, result);

        while (low < high) {
            /* 这行看起来有些奇怪，但其设计目的是避免整数溢出
             * 在大型输入上。其思想是 (high + low) 可能溢出，但
             * (high - low) / 2 永远不会。
             */
            int mid = low + (high - low) / 2;
            Set<string> thisResult;

            /* 如果此选项可行，则将 high 降到该值，因为我们知道此前一切正常。 */
            if (canBeMadeDisasterReady(test.network, mid, thisResult)) {
                high = mid;
                result = thisResult; // 记住此结果以供后用。
            }
            /* 否则，排除所有小于或等于它的值。 */
            else {
                low = mid + 1;
            }
        }
    }

    class DisasterGUI: public ProblemHandler {
    public:
        DisasterGUI(GWindow& window);

        void actionPerformed(GObservable* source) override;
        void changeOccurredIn(GObservable* source) override;

    protected:
        void repaint() override;

    private:
        /* 用于选择问题的下拉列表。 */
        Temporary<GComboBox> mProblems;

        /* 触发求解器的按钮。 */
        Temporary<GButton> mSolve;

        /* 当前网络和解。 */
        DisasterTest    mNetwork;
        Set<string> mSelected;

        /* 加载具有给定名称的世界。 */
        void loadWorld(const string& filename);

        /* 计算最优解。 */
        void solve();
    };

    DisasterGUI::DisasterGUI(GWindow& window) : ProblemHandler(window) {
        GComboBox* choices = new GComboBox();
        for (const string& file: sampleProblems(kBasePath)) {
            choices->addItem(file);
        }
        choices->setEditable(false);

        mProblems = Temporary<GComboBox>(choices, window, "SOUTH");
        mSolve    = Temporary<GButton>(new GButton("Solve"), window, "SOUTH");

        loadWorld(choices->getSelectedItem());
    }

    void DisasterGUI::changeOccurredIn(GObservable* source) {
        if (source == mProblems) {
            loadWorld(mProblems->getSelectedItem());
        }
    }

    void DisasterGUI::actionPerformed(GObservable* source) {
        if (source == mSolve) {
            solve();
        }
    }

    void DisasterGUI::repaint() {
        visualizeNetwork(window(), mNetwork, mSelected);
    }

    void DisasterGUI::loadWorld(const string& filename) {
        ifstream input(kBasePath + filename);
        if (!input) error("Cannot open file.");

        mNetwork = loadDisaster(input);
        mSelected.clear();
        requestRepaint();
    }

    void DisasterGUI::solve() {
        /* 清除旧解。我们将获得一个新解。 */
        mSelected.clear();

        /* 在操作完成前禁用所有控件。 */
        mSolve->setEnabled(false);
        mProblems->setEnabled(false);

        solveOptimally(mNetwork, mSelected);

        /* 启用控件。 */
        mSolve->setEnabled(true);
        mProblems->setEnabled(true);

        requestRepaint();
    }
}

GRAPHICS_HANDLER("Disaster Planning", GWindow& window) {
    return make_shared<DisasterGUI>(window);
}

namespace {
    /* 显示给定交通网格。 */
    void displayMap(const Map<string, Set<string>>& network) {
        cout << "This transportation grid has " << pluralize(network.size(), "city", "cities") << "." << endl;
        for (string city: network) {
            cout << "  The city " << city << " is adjacent to " << pluralize(network[city].size(), "city", "cities") << "." << endl;
            for (string neighbor: network[city]) {
                cout << "    " << neighbor << endl;
            }
        }
    }

    /* 显示最优解中使用的城市。 */
    void displayBestCities(const Set<string>& cities) {
        cout << "You need to stockpile in " << pluralize(cities.size(), "city", "cities") << " to provide coverage." << endl;
        for (string city: cities) {
            cout << "  " << city << endl;
        }
    }

    void demoDisasterPlanning() {
        cout << "Disaster Planning" << endl;
        do {
            ifstream input(makeFileSelection(".dst"));
            if (!input) error("Internal error - not your fault: Can't open the chosen file.");

            auto scenario = loadDisaster(input);

            displayMap(scenario.network);

            cout << "Running your code to find the fewest number of cities needed... " << flush;
            Set<string> cities;
            solveOptimally(scenario, cities);
            cout << "done!" << endl;

            displayBestCities(cities);
        } while (getYesOrNo("Try another demo file? "));
    }
}

CONSOLE_HANDLER("Disaster Planning") {
    demoDisasterPlanning();
}
