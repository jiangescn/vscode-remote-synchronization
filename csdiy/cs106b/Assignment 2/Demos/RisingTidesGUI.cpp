#include "RisingTides.h"
#include "GUI/MiniGUI.h"
#include "DownloadCache.h"
#include "gwindow.h"
#include "ginteractors.h"
#include "gobjects.h"
#include "gcontainer.h"
#include "filelib.h"
#include "gthread.h"
#include <istream>
#include <fstream>
#include <vector>
#include <unordered_set>
using namespace std;

namespace {

    using GBufferedImage = GCanvas;

    const string kOutputFile = "res/terrains/result.png";
    const string kBackgroundColor = "#802040";

    const string kLoadButtonText     = "Load";
    const string kWaterHeightText    = "Water Height: ";
    const string kFloodButtonText    = "Go!";

    const string kRenderingText      = "Rendering the result...";
    const string kDownloadingMessage = "Downloading the terrain from Stanford's servers...";
    const string kBadNumberText      = "Please enter a real number.";
    const string kRunningCodeText    = " (running your code...)";

    const string kLoadingText        = "Loading the landscape...";

    /* 读取地形失败时显示的错误消息。 */
    const string kMalformedDataFileMessage = "Oops! Something went wrong reading that data file. If this is a terrain file you designed, double-check the syntax of the file. Otherwise, this isn't your fault.";

    /* 查找文件的位置。 */
    const string kBasePath = "res/terrains/";
    const string kFileSuffix = ".terrain";

    /* 表示“未选中任何内容”的哨兵值。 */
    const string kNotSelected = "-";

    /* 错误消息。 */
    const string kRemoteDownloadErrorString = "Oops! We weren't able to download that terrain file. This isn't your fault. (Please contact the course staff.)";
    const string kVisualizationErrorString  = "Oops! We weren't able to download that terrain file. (Check your network connection?)";

    const size_t kTextInputSize = 15;

    /* 用于水的颜色。 */
    const int kUnderwaterColor = GBufferedImage::createRgbPixel(0, 49, 83); // 普鲁士蓝

    /* 地图的其余部分按以下方案着色。高度被映射
     * 转换为 0 到 1 之间的实数。然后使用这些实数在
     * 由在不同间隔处标记的一系列固定颜色点组成。
     *
     * RGBPoint 类型表示一个特定 RGB 颜色，并附带一个阈值
     * 介于 0 和 1 之间，表示该颜色所在位置。
     */
    struct RGBPoint {
        int red, green, blue;
        double threshold;
    };

    /* 绘制地图实际使用的颜色，并附有对应阈值。 */
    const vector<RGBPoint> kColors = {
        {   0, 102,   0, 0.0  },   // 巴基斯坦绿
        { 154, 205,  50, 0.1  },   // 黄绿色
        { 251, 236,  93, 0.25 },   // Maize
        { 212, 175,  55, 0.4  },   // 金属金色
        { 166,  60,  20, 1.01 }    // 赭色。这里的 1.01 用于确保覆盖舍入误差。
    };

    /* 在两个量之间进行线性插值。progress 变量范围为 0 到 1。 */
    int interpolate(int from, int to, double progress) {
        return from + (to - from) * progress;
    }

    /* 给定绝对高度和与某范围关联的高度范围，返回
     * 与该高度关联的颜色。
     */
    int colorFor(double height, bool underwater, double lowest, double highest) {
        /* 如果点位于水下，则始终使用水色。 */
        if (underwater) return kUnderwaterColor;

        /* 将高度映射到 [0, 1]。 */
        double alpha = (height - lowest) / nextafter(highest - lowest, numeric_limits<double>::infinity());

        /* 确定我们位于哪些点之间。 */
        for (size_t i = 1; i < kColors.size(); i++) {
            if (alpha <= kColors[i].threshold) {
                /* 进度以两点之间的距离比例衡量。0.0 表示
                 * “完全位于左端。1.0 表示完全位于右端。”
                 */
                double progress = (alpha - kColors[i - 1].threshold) /
                                  (kColors[i].threshold - kColors[i - 1].threshold);

                /* 在这些颜色点之间插值以获得整体颜色。 */
                int red   = interpolate(kColors[i - 1].red,   kColors[i].red,   progress);
                int green = interpolate(kColors[i - 1].green, kColors[i].green, progress);
                int blue  = interpolate(kColors[i - 1].blue,  kColors[i].blue,  progress);

                return GBufferedImage::createRgbPixel(red, green, blue);
            }
        }

        /* 此代码不可到达。 */
        error("Impossible alpha: " + to_string(alpha));
        return 0;
    }

    /* 将给定图像写入输出文件。这样做是因为 GBufferedImage 是高效的
     * 将图像推送到后端的方法，但不支持调整大小（TODO：验证此项）。
     * 因此我们将其转储到文件，之后再作为支持调整大小的 GImage 重新加载。
     */
    void renderToFile(const Grid<double>& heights, const Grid<bool>& underwater) {
        double lowest  = *min_element(heights.begin(), heights.end());
        double highest = *max_element(heights.begin(), heights.end());

        Grid<int> pixels(heights.numRows(), heights.numCols());
        for (int row = 0; row < heights.numRows(); row++) {
            for (int col = 0; col < heights.numCols(); col++) {
                pixels[row][col] = colorFor(heights[row][col], underwater[row][col], lowest, highest);
            }
        }

        GThread::runOnQtGuiThread([&] {
            GBufferedImage image;
            image.fromGrid(pixels);
            image.save(kOutputFile);
        });
    }

    /* 生成一条略带幽默的消息，在所有内容计算时消磨时间。 */
    string floodMessage() {
        switch (rand() % 4) {
            case 0:  return "Forecasting the flood";
            case 1:  return "Watering the world";
            case 2:  return "Deploying the deluge";
            default: return "Simulating the surge";
        }
    }

    /* 类型：Terrain
     * ----------------------------------------------------------------------------------
     * 表示地形的类型，即细分为各个单元格的 Grid<double>，
     * 每个位置都有相关高度，以及水可以从中流出的水源列表
     * 向外淹没。
     *
     * GridLocation 类型是一个简单结构体，只包含行和列。
     * 它用于将 Grid 中的位置作为单个对象进行跟踪。
     */
    struct Terrain {
        Grid<double> heights;              // 地图上每个点的高度，单位为米。
        Vector<GridLocation> waterSources; // 哪些位置是水源（如果有）。
    };

    /* 从数据文件加载地形。 */
    Terrain loadTerrain(istream& input, GLabel* statusLine) {
        /* 输入的第一行要么是要下载的 URL，要么是字符串 "local"。
         * 如果是远程下载，需要先获取文件。
         */
        string url;
        if (!getline(input, url)) {
            error(kMalformedDataFileMessage);
        }

        if (url != "local") {
            auto data = webContentsOf(url, ".terrain", [&] (DownloadStatus status) {
                if (status == DownloadStatus::DOWNLOADING) {
                    statusLine->setText(kDownloadingMessage);
                } else if (status == DownloadStatus::FINISHED) {
                    statusLine->setText(" ");
                }
            });

            /* 改为下载该数据。 */
            return loadTerrain(*data, statusLine);
        }

        statusLine->setText(kLoadingText);

        int numRows, numCols;
        if (input >> numRows >> numCols, !input) {
            error(kMalformedDataFileMessage);
        }

        int numSources;
        if (input >> numSources, !input) {
            error(kMalformedDataFileMessage);
        }

        /* 读取洪水源。 */
        Terrain result;
        for (int i = 0; i < numSources; i++) {
            int row, col;
            if (input >> row >> col, !input) {
                error(kMalformedDataFileMessage);
            }

            result.waterSources.add({ row, col });
        }

        /* 读取高度数据。 */
        result.heights.resize(numRows, numCols);
        for (int row = 0; row < result.heights.numRows(); row++) {
            for (int col = 0; col < result.heights.numCols(); col++) {
                if (input >> result.heights[row][col], !input) {
                    error(kMalformedDataFileMessage);
                }
            }
        }

        char leftover;
        if (input >> leftover) {
            error(kMalformedDataFileMessage);
        }

        return result;
    }

    /* 返回示例目录中找到的所有样例问题。 */
    vector<string> sampleProblems() {
        vector<string> result;
        for (const auto& file: listDirectory(kBasePath)) {
            if (endsWith(file, kFileSuffix)) {
                result.push_back(file);
            }
        }
        return result;
    }

    /* 与水位问题对应的 Problem 类。 */
    class FindWaterLevel: public ProblemHandler {
    public:
        /* 构造处理程序，假定输入流包含要读取的数据。 */
        FindWaterLevel(GWindow& window);

        /* TODO：交互控件的内存发生泄漏。请修复！ */

        /* 文件扩展名。 */
        static std::string fileExtension();

        /* 响应动作事件。 */
        void actionPerformed(GObservable* source) override;

    protected:
        /* 绘制当前状态。 */
        void repaint() override;

    private:
        /* 两行项目网格。布局如下
         *
         *    下拉框   加载     水位：    输入字段     开始！
         *    ------------------- 状态行 ------------------------
         */
        Temporary<GContainer> container;

        /* 加载文件。 */
        GComboBox*  terrainChooser;
        GButton*    loadButton;

        /* 输入字段。 */
        GLabel*     heightDesc;
        GTextField* heightField;
        GButton*    solveButton;

        /* 状态报告。 */
        GLabel*     statusLine;

        /* 洪泛平原及当前位于水下的部分。 */
        Terrain plain;
        Grid<bool> underwater;

        /* 当前地形的名称。 */
        string currTerrain = kNotSelected;

        /* 运行洪水模拟。 */
        void runFlood(double height);

        /* 设置当前活动的地形。 */
        void setActiveTerrain(const string& terrainFile, bool clearHeight);
    };

    FindWaterLevel::FindWaterLevel(GWindow& window) : ProblemHandler(window) {
        auto* rawContainer = new GContainer(GContainer::LAYOUT_GRID);

        terrainChooser = new GComboBox();
        terrainChooser->addItem(kNotSelected); // 初始时不显示任何内容
        for (const string& file: sampleProblems()) {
            terrainChooser->addItem(file);
        }
        terrainChooser->setEditable(false);

        loadButton  = new GButton(kLoadButtonText);
        heightDesc  = new GLabel(kWaterHeightText);
        heightField = new GTextField(kTextInputSize);
        solveButton = new GButton(kFloodButtonText);
        statusLine  = new GLabel("");

        rawContainer->addToGrid(terrainChooser, 0, 0);
        rawContainer->addToGrid(loadButton,     0, 1);
        rawContainer->addToGrid(heightDesc,     0, 2);
        rawContainer->addToGrid(heightField,    0, 3);
        rawContainer->addToGrid(solveButton,    0, 4);
        rawContainer->addToGrid(statusLine,     1, 0, 1, 5);

        heightField->setText("0.0");

        container= Temporary<GContainer>(rawContainer, window, "SOUTH");

        setActiveTerrain(kNotSelected, true);
    }

    /* 从给定高度开始运行洪水模拟。 */
    void FindWaterLevel::runFlood(double height) {
        statusLine->setText(floodMessage() + kRunningCodeText);
        underwater = floodedRegionsIn(plain.heights, plain.waterSources, height);

        /* 将渲染后的图像暂存到磁盘。 */
        statusLine->setText(kRenderingText);
        renderToFile(plain.heights, underwater);
        statusLine->setText(" ");

        requestRepaint();
    }

    /* 渲染洪水结果。 */
    void FindWaterLevel::repaint() {
        /* 清空显示内容。 */
        clearDisplay(window(), kBackgroundColor);

        /* 如果世界为空，则不绘制任何内容。 */
        if (plain.heights.isEmpty()) return;

        GImage image(kOutputFile);

        /* 重新缩放图像以适应窗口。 */
        double aspectRatio = image.getWidth() / image.getHeight();
        double scale;
        if (aspectRatio > window().getCanvasWidth() / window().getCanvasHeight()) {
            scale = window().getCanvasWidth() / image.getWidth();
        } else {
            scale = window().getCanvasHeight() / image.getHeight();
        }
        image.scale(scale);

        /* 绘制图像。 */

        /* TODO：截至目前（2019-02-27），缩放 GBufferedImage 时存在一个错误，会导致
         * 除宽度和高度外，还要应用于其 x 和 y 坐标的变换。因此我们
         * 必须在此处反转变换。
         *
         * 修复此错误后，删除缩放 x 和 y 坐标的逻辑。
         */
        window().draw(&image, (window().getCanvasWidth()  - image.getWidth() * scale)  / (2 * scale),
                              (window().getCanvasHeight() - image.getHeight() * scale) / (2 * scale));
    }

    void FindWaterLevel::actionPerformed(GObservable* source) {
        if (source == heightField || source == solveButton) {
            double height;
            bool heightValid = true;

            try {
                height = stringToReal(heightField->getText());
            } catch (const exception& e) {
                statusLine->setText(kBadNumberText);
                heightValid = false;
            }

            if (heightValid) {
                container->setEnabled(false);
                if (currTerrain != terrainChooser->getSelectedItem()) {
                    setActiveTerrain(terrainChooser->getSelectedItem(), false);
                } else if (terrainChooser->getSelectedItem() != kNotSelected) {
                    runFlood(height);
                }
                container->setEnabled(true);
            }
        } else if (source == loadButton) {
            setActiveTerrain(terrainChooser->getSelectedItem(), true);
        }
    }

    void FindWaterLevel::setActiveTerrain(const string& terrainFile, bool clearHeight) {
        if (terrainFile == kNotSelected) {
            plain.heights.clear();
            plain.waterSources.clear();
            currTerrain = kNotSelected;
        } else {
            setDemoOptionsEnabled(false);
            container->setEnabled(false);
            try {
                ifstream input(kBasePath + terrainFile);
                if (!input) error("Cannot open file " + kBasePath + terrainFile);
                plain = loadTerrain(input, statusLine);
                if (clearHeight) heightField->setText("0.0");
                currTerrain = terrainFile;

                double height = 0.0;
                try {
                    height = stringToReal(heightField->getText());
                } catch (const exception &) {

                }
                runFlood(height);
            } catch (const DownloadError& e) {
                if (e.errorCode() < 0) {
                    statusLine->setText(kVisualizationErrorString);
                } else {
                    statusLine->setText(kRemoteDownloadErrorString);
                }
            }
            container->setEnabled(true);
            setDemoOptionsEnabled(true);
        }
    }
}

GRAPHICS_HANDLER("Rising Tides", GWindow& window) {
    return make_shared<FindWaterLevel>(window);
}
