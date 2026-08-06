#include "GUI/MiniGUI.h"
#include "Combine.h"
#include "BigOFunctions.h"
#include "Matching/Matchmaker.h"
#include "ginteractors.h"
#include "gtimer.h"
#include "simpio.h"
#include <functional>
#include <chrono>
#include <cstdint>
#include <string>
#include <limits>
#include <cmath>
#include <iomanip>
using namespace std;
using namespace MiniGUI;

namespace {
    const string kNotSelected = "-";

    /* 图形常量。 */
    const double kEventTimerSpeed = 1; // 足够快，可以流畅运行，但又不会淹没事件队列
    const string kBackgroundColor = "White";
    const double kPadding = 20;

    /* 控制台高度，以画布大小的比例表示。 */
    const double kConsoleScaleFactor = 0.9;

    /* 坐标轴常量。 */
    const char kAxisColor[] = "#555555"; // 戴维灰
    const Font kAxisFont(FontFamily::SERIF, FontStyle::NORMAL, 8, kAxisColor);
    const size_t kMaxAxisLabels = 10;    // X 轴主刻度线的最大数量

    /* 内容区域。 */
    const double kHeaderHeight    = 50;
    const Font kHeaderFont(FontFamily::SERIF, FontStyle::BOLD_ITALIC, 24, kAxisColor);

    /* 图例区域，以相对于图表区域起点的偏移量表示。 */
    const double kLegendXOffset   = 100;
    const double kLegendYOffset   =   0;
    const double kLegendWidth     = 150;
    const double kLegendHeight    = 200;
    const Font kLegendFont(FontFamily::SANS_SERIF, FontStyle::NORMAL, 12, kAxisColor);


    /**
     * 表示秒表的类型，用于测量各种操作的耗时
     * 操作。
     */
    class Timer {
    public:
      void start() {
        current = chrono::high_resolution_clock::now();
      }

      void stop() {
        total += chrono::high_resolution_clock::now() - current;
      }

      double elapsed() const {
        return chrono::duration_cast<chrono::nanoseconds>(total).count();
      }

    private:
      chrono::high_resolution_clock::duration total =
        chrono::high_resolution_clock::duration::zero();
      chrono::high_resolution_clock::time_point current;
    };

    /* 运行计时测试所需的全部信息。 */
    struct TimeTest {
        function<void (size_t n, size_t k, Timer& timer)> callback; // 给定 n、k 和计时器，执行工作。
        vector<size_t> ns, ks;                                      // n 和 k 的值
        string name;                                                // 我们正在测试的内容
    };

    /* 按线性和指数序列生成数字 */
    vector<size_t> linRange(size_t low, size_t high, size_t step) {
        vector<size_t> result;
        for (; low <= high; low += step) {
            result.push_back(low);
        }
        return result;
    }

    vector<size_t> expRange(size_t low, size_t high, double step) {
        vector<size_t> result;
        for (; low <= high; low *= step) {
            result.push_back(low);
        }
        return result;
    }

    /* 将 cout 输出重定向到其他位置。 */
    struct StreamDiverter {
        ostringstream buffer;
        streambuf* oldBuf;
        StreamDiverter() {
            oldBuf = cout.rdbuf(buffer.rdbuf());
        }

        ~StreamDiverter() {
            cout.rdbuf(oldBuf);
        }
    };

    /* 为确保编译器不会优化掉其中一些调用，
     * 我们用这些调用的结果增加累加器。
     */
    volatile unsigned int accumulator = 0;

    /* 所有可运行测试的列表。 */
    const vector<TimeTest> kAllTests = {
        /* printH */
        {
            [](int n, int, Timer& timer) {
                StreamDiverter diverter;

                timer.start();
                printH(n);
                timer.stop();
            },
            linRange(1000, 10000, 1000),
            { 1 },
            "printH"
        },

        /* printC */
        {
            [](int n, int, Timer& timer) {
                StreamDiverter diverter;

                timer.start();
                printC(n);
                timer.stop();
            },
            linRange(100000, 1000000, 50000),
            { 1 },
            "printC"
        },

        /* printI */
        {
            [](int n, int, Timer& timer) {
                StreamDiverter diverter;

                timer.start();
                printI(n);
                timer.stop();
            },
            linRange(1000, 10000, 1000),
            { 1 },
            "printI"
        },

        /* printP */
        {
            [](int n, int, Timer& timer) {
                StreamDiverter diverter;

                timer.start();
                printP(n);
                timer.stop();
            },
            linRange(1000, 10000, 1000),
            { 1 },
            "printP"
        },

        /* printChip */
        {
            [](int n, int, Timer& timer) {
                StreamDiverter diverter;

                timer.start();
                printChip(n);
                timer.stop();
            },
            linRange(1000, 10000, 1000),
            { 1 },
            "printChip"
        },

        /* countTriples */
        {
            [](int n, int, Timer& timer) {
                Vector<int> values;
                for (int i = 0; i < n; i++) {
                    values += randomInteger(-1000, +1000);
                }

                timer.start();
                accumulator += countTriples(values, 137);
                timer.stop();
            },
            linRange(100, 1000, 100),
            { 1 },
            "countTriples"
        },

        /* printCycle_v1 */
        {
            [](int n, int, Timer& timer) {
                StreamDiverter diverter;

                Vector<int> values;
                for (int i = 0; i < n; i++) {
                    values += randomInteger(-1000, +1000);
                }

                timer.start();
                printCycle_v1(values);
                timer.stop();
            },
            linRange(10000, 50000, 5000),
            { 1 },
            "printCycle_v1"
        },

        /* printCycle_v2 */
        {
            [](int n, int, Timer& timer) {
                StreamDiverter diverter;

                Vector<int> values;
                for (int i = 0; i < n; i++) {
                    values += randomInteger(-1000, +1000);
                }

                timer.start();
                printCycle_v2(values);
                timer.stop();
            },
            linRange(1000, 5000, 500),
            { 1 },
            "printCycle_v2"
        },

        /* printCycle_v3 */
        {
            [](int n, int, Timer& timer) {
                StreamDiverter diverter;

                Queue<int> values;
                for (int i = 0; i < n; i++) {
                    values.enqueue(randomInteger(-1000, +1000));
                }

                timer.start();
                printCycle_v3(values);
                timer.stop();
            },
            linRange(1000000, 5000000, 500000),
            { 1 },
            "printCycle_v3"
        },

        /* recursivePuzzle */
        {
            [](int n, int, Timer& timer) {
                timer.start();
                for (int i = 0; i < 10000; i++) {
                    recursivePuzzle(n);
                }
                timer.stop();
            },
            linRange(1000, 5000, 500),
            { 1 },
            "recursivePuzzle"
        },

        /* recursiveEnigma */
        {
            [](int n, int, Timer& timer) {
                timer.start();
                for (int i = 0; i < 1000000; i++) {
                    recursiveEnigma(n);
                }
                timer.stop();
            },
            linRange(0, 100000000, 1000000),
            { 1 },
            "recursiveEnigma"
        },

        /* maximumSingleSellProfit_v1 */
        {
            [](int n, int, Timer& timer) {
                Vector<int> values;
                for (int i = 0; i < n; i++) {
                    values += randomInteger(-1000, +1000);
                }

                timer.start();
                accumulator += maximumSingleSellProfit_v1(values);
                timer.stop();
            },
            linRange(1000, 10000, 1000),
            { 1 },
            "maximumSingleSellProfit_v1"
        },

        /* maximumSingleSellProfit_v2 */
        {
            [](int n, int, Timer& timer) {
                Vector<int> values;
                for (int i = 0; i < n; i++) {
                    values += randomInteger(-1000, +1000);
                }

                timer.start();
                accumulator += maximumSingleSellProfit_v2(values);
                timer.stop();
            },
            linRange(10000, 100000, 10000),
            { 1 },
            "maximumSingleSellProfit_v2"
        },

        /* Matchmaker */
        {
            [](int n, int, Timer& timer) {
                Map<string, Map<string, int>> possibilities;
                for (int i = 0; i < n; i++) {
                    for (int j = i+1; j < n; j++) {
                        possibilities[to_string(i)][to_string(j)] =
                        possibilities[to_string(j)][to_string(i)] = randomInteger(0, 1000);
                    }
                }

                timer.start();
                accumulator += fastMaxWeightMatching(possibilities).size();
                timer.stop();
            },
            linRange(50, 500, 50),
            { 1 },
            "fastMaxWeightMatching"
        },

        /* 合并 */
        {
            [](int n, int k, Timer& timer) {
                /* 创建一组要合并的向量。 */
                Vector<Vector<DataPoint>> toMerge(k);

                /* 按照近似几何分布添加元素。 */
                for (int i = 0; i < n; i++) {
                    int index = 0;
                    while (index < k - 1 && randomBool()) index++;

                    toMerge[index] += { to_string(i), double(i) };
                }

                /* 运行多路合并。 */
                timer.start();
                (void) combine(toMerge);
                timer.stop();
            },
            linRange(10000, 100000, 5000),
            expRange(1, 1 << 12, 4),
            "combine"
        }
    };

    /* 测试驱动程序，与任何特定测试结果显示方式分离。 */
    class TestDriver {
    public:
        TestDriver(const TimeTest& test,
                   function<void(int k)> onNewK,
                   function<void(int n, double value)> onNewN,
                   function<void()> onStop) : test(test),
                                              onNewK(onNewK),
                                              onNewN(onNewN),
                                              onStop(onStop) {

        }

        /* 运行测试的下一步。这样做是为了让 GUI 能够使用
         * 计时器回调；测试驱动代码只需逐步执行直到完成。
         */
        void step();

    private:
        TimeTest test;
        size_t nextN = 0, nextK = 0; // 接下来要使用的 n 和 k 值。

        function<void(int k)> onNewK;
        function<void(int n, double value)> onNewN;
        function<void()> onStop;
    };

    void TestDriver::step() {
        /* 当前是否位于最开始？ */
        if (nextN == 0 && nextK == 0) {
            onNewK(test.ks[nextK]);
        }

        /* 否则，运行下一个测试。 */
        Timer timer;
        test.callback(test.ns[nextN], test.ks[nextK], timer);

        /* 保存结果。 */
        onNewN(test.ns[nextN], timer.elapsed());

        /* 向前一步。 */
        nextN++;

        /* 所有 n 都完成了吗？进入下一个 k。 */
        if (nextN == test.ns.size()) {
            nextN = 0;
            nextK++;

            /* 所有 k 都完成了吗？处理结束！ */
            if (nextK == test.ks.size()) {
                onStop();
                return;
            } else {
                onNewK(test.ks[nextK]);
            }
        }
    }

    /* 用于不同 k 值的颜色。 */
    const vector<string> kLineColors = {
        "#CC0000", // 赛车红
        "#EE7F2D", // 普林斯顿橙
        "#FFC40C", // 御竹黄
        "#008000", // 办公室绿
        "#007BA7", // Cerulean
        "#B53389", // Fandango
        "#343434", // Jet
    };

    /* 报告不同类型计时信息的问题处理程序。 */
    class PerformanceGUI: public ProblemHandler {
    public:
        PerformanceGUI(GWindow& window);

        void timerFired() override;
        void actionPerformed(GObservable* source) override;

    protected:
        void repaint() override;

    private:
        /* 每次计时器触发都会进入下一个测试用例。 */
        GTimer timer{kEventTimerSpeed};

        /* 我们正在执行哪个测试（如果有）。 */
        bool isActive = false;
        TimeTest currTest;

        vector<string> axisLabels{2};   // x 轴标签。默认为两个空字符串
        size_t axisTicks = 0;           // X 轴上使用的次刻度线

        /* 截至目前的测试用例结果。 */
        unique_ptr<TestDriver> driver;
        Vector<Vector<double>> results;

        /* 装饰布局：
         *
         * +------------------------------+
         * | 函数：[ 下拉框 ] [运行！] |
         * +------------------------------+
         */
        Temporary<GLabel> functionLabel;
        Temporary<GComboBox> functionSelector;
        Temporary<GButton> go;

        Map<string, const TimeTest*> tests;

        /* 侧边控制台。 */
        Temporary<GColorConsole> console;

        void startTests(const TimeTest& test);

        void drawChart (GWindow& window, const GRectangle& bounds);
        void drawHeader(GWindow& window, const GRectangle& bounds);
        void drawLegend(GWindow& window, const GRectangle& bounds);
    };

    PerformanceGUI::PerformanceGUI(GWindow& window) : ProblemHandler(window) {
        console = make_temporary<GColorConsole>(window, "WEST");
        console->setHeight(window.getCanvasHeight() * kConsoleScaleFactor);

        functionLabel = make_temporary<GLabel>(window, "SOUTH", "Function: ");
        functionSelector = make_temporary<GComboBox>(window, "SOUTH");
        functionSelector->addItem(kNotSelected);

        for (const auto& test: kAllTests) {
            tests[test.name] = &test;
            functionSelector->addItem(test.name);
        }

        go = make_temporary<GButton>(window, "SOUTH", "Time");
    }

    void PerformanceGUI::timerFired() {
        /* 若没有活动测试，则无需执行任何操作。 */
        if (!isActive) {
            timer.stop();
            return;
        }

        driver->step();

        /* 需要重绘！ */
        requestRepaint();
    }

    /* 开始新的测试会话。 */
    void PerformanceGUI::startTests(const TimeTest& test) {
        /* 清除所有旧测试信息。 */
        currTest = test;

        /* 从 k 值到文本颜色的映射。如果存在以下情况，则会忽略此项：
         * 只有一个 k 值。
         */
        map<size_t, string> colors;
        for (size_t k: test.ks) {
            colors.insert(make_pair(k, kLineColors[colors.size()]));
        }

        /* 重置状态。 */
        auto onNewK = [test, colors, this](int k) {
            /* 为结果添加新的存放位置。 */
            results.add({});

            /* 若有多个 k 值需要依次显示，则显示当前 k 的选择。 */
            if (test.ks.size() != 1) {
                console->doWithStyle(colors.at(k), GColorConsole::BOLD, [&]{
                    *console << "k = " << k << endl;
                });
            }
        };

        auto onNewN = [this](int n, double elapsed) {
            /* 保存结果。 */
            results[results.size() - 1] += elapsed;

            *console << "  n = " << left << setw(10) << (to_string(n) + ": ") << elapsed / 1e6 << "ms" << endl;
        };

        auto onStop = [this] {
            timer.stop();
            isActive = false;
        };

        driver.reset(new TestDriver(test, onNewK, onNewN, onStop));
        results.clear();
        console->clearDisplay();

        /* 设置 x 轴标签。 */
        axisLabels.clear();

        /* X 轴上的标签永远不会超过 kMaxAxisLabels 个。如果我们
         * 否则会开始引入次级刻度。
         *
         * 我们将按如下方式执行。我们会计算
         * ceil（标签数量 / kAxisLabels），得到需要跳过的刻度数
         * 要使用的值。例如，如果希望有 11 个标签且最大值为 10，我们会计算
         * ceil(11 / 10) - 1 = 2，并在每组之间放置一个次级刻度
         * 主刻度的数量。
         *
         * 我们实际上使用以下技巧计算：公式 (a + b - 1) / b 可计算
         * ceil(a / b)。
         */
        axisTicks = ((test.ns.size() + kMaxAxisLabels - 1) / kMaxAxisLabels);
        size_t numMajor = (test.ns.size() + axisTicks - 1) / axisTicks;

        for (size_t i = 0; i < numMajor; i++) {
            size_t effectiveIndex = i * axisTicks; // 毕竟，我们正在跳过内容！

            string label;
            if (effectiveIndex == 0) {
                label = "n=" + to_string(test.ns[effectiveIndex]);
            } else if (effectiveIndex < test.ns.size()) {
                label = to_string(test.ns[effectiveIndex]);
            } else {
                label = ""; // 不是必需的，但有助于明确意图。
            }

            axisLabels.push_back(label);
        }

        /* axisTicks 参数实际上直接控制要绘制多少个次刻度
         * 实际绘制的刻度，而不是主刻度之间的跳步大小。因此需要减去
         * 这里多画一个，以确保绘制正确数量的次刻度线。
         */
        axisTicks--;

        isActive = true;
        timer.start();

        console->doWithStyle(FontSize(16), [&] {
            *console << test.name << endl;
        });
    }


    void PerformanceGUI::actionPerformed(GObservable* source) {
        if (source == go) {
            string choice = functionSelector->getSelectedItem();
            if (choice != kNotSelected && tests.containsKey(choice)) {
                startTests(*tests[choice]);
            }
        }
    }

    void PerformanceGUI::repaint() {
        clearDisplay(window(), kBackgroundColor);

        /* 为标题预留空间。 */
        GRectangle header = {
            kPadding, kPadding,
            window().getCanvasWidth() - 2 * kPadding,
            kHeaderHeight
        };

        double chartTop = header.y + header.height;

        /* 设置图表。 */
        GRectangle chart = {
            kPadding, chartTop,
            window().getCanvasWidth()  - 2 * kPadding,
            window().getCanvasHeight() - chartTop - kPadding
        };

        /* 以及图例。 */
        GRectangle legend = {
            chart.x + kLegendXOffset, chart.y + kLegendYOffset,
            kLegendWidth, kLegendHeight
        };

        drawHeader(window(), header);
        drawChart (window(), chart);
        drawLegend(window(), legend);
    }

    void PerformanceGUI::drawHeader(GWindow& window, const GRectangle& bounds) {
        auto render = TextRender::construct(currTest.name, bounds, kHeaderFont, LineBreak::NO_BREAK_SPACES);
        render->alignCenterHorizontally();
        render->alignCenterVertically();
        render->draw(window);
    }

    void PerformanceGUI::drawChart(GWindow& window, const GRectangle& bounds) {
        /* Y 轴标签将为空。但至少需要两个，因此我们会创建它们。 */
        vector<string> yLabels(2);

        /* 将结果转换为线段。 */

        /* 找出所有内容中的最大值。 */
        double maxValue = 0;
        double minValue = numeric_limits<double>::infinity();
        for (const auto& result: results) {
            for (double val: result) {
                maxValue = max(val, maxValue);
                minValue = min(val, minValue);
            }
        }

        /* 将最大值稍微上调，以避免除以零。 */
        maxValue = nextafter(maxValue, numeric_limits<double>::infinity());

        /* 按该数值将所有内容归一化。 */
        vector<vector<GPoint>> lines;
        for (const auto& result: results) {
            vector<GPoint> line;
            for (int i = 0; i < result.size(); i++) {
                line.push_back({ i * 1.0 / (currTest.ns.size() - 1), (result[i] - minValue) / (maxValue - minValue) });
            }
            lines.push_back(line);
        }

        /* 绘制它！ */
        LineGraphRender::construct(lines,
                                   axisLabels,
                                   yLabels,
                                   axisTicks,
                                   0,
                                   bounds,
                                   kAxisFont,
                                   kAxisFont,
                                   kLineColors,
                                   kAxisColor)->draw(window);
    }

    void PerformanceGUI::drawLegend(GWindow& window, const GRectangle& bounds) {
        /* 若只有一个 k 值，则不绘制任何内容。 */
        if (currTest.ks.size() <= 1) return;

        /* 否则，存在多个 k 值。根据行数组织标签
         * 目前已绘制的内容。
         */
        vector<string> labels;
        for (size_t i = 0; i < currTest.ks.size() && i < size_t(results.size()); i++) {
            labels.push_back("k = " + to_string(currTest.ks[i]));
        }

        /* 设置图例。先不要绘制；我们需要清除其后面的区域。 */
        auto legend = LegendRender::construct(labels, kLineColors, bounds, kLegendFont, kLegendFont.color());
        window.setColor(kBackgroundColor);
        window.fillRect(legend->computedBounds());

        /* 现在绘制它。 */
        legend->draw(window);
    }
}

GRAPHICS_HANDLER("Time Tests", GWindow& window) {
    return make_shared<PerformanceGUI>(window);
}

CONSOLE_HANDLER("Time Tests") {
    Vector<string> options;

    for (const auto& entry: kAllTests) {
        options += entry.name;
    }

    do {
        int choice = makeSelectionFrom("Choose a function to time-test:", options);
        auto test = kAllTests[choice];

        auto onNextK = [&](int k) {
            if (test.ks.size() != 1) {
                cout << "k = " << k << endl;
            }
        };

        auto onNextN = [&](int n, double result) {
            cout << "  n = " << left << setw(10) << (to_string(n) + ": ") << result / 1e6 << "ms" << endl;
        };

        bool done = false;
        auto onDone = [&] {
            done = true;
        };

        cout << "Timing " << test.name << endl;
        TestDriver driver(test, onNextK, onNextN, onDone);
        while (!done) {
            driver.step();
        }
    } while (getYesOrNo("Run tests on another function? "));
}
