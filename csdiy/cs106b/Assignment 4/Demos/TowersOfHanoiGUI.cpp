#include "TowersOfHanoi.h"
#include "GUI/MiniGUI.h"
#include "gthread.h"
#include "error.h"
#include "gobjects.h"
#include "gwindow.h"
#include "ginteractors.h"
#include "stack.h"
#include "simpio.h"
#include <iostream>
#include <string>
#include <memory> // 用于 unique_ptr
#include <mutex>
using namespace std;
using namespace MiniGUI;

namespace {
    /******** 常量 ********/

    /* 允许的最大圆盘数。 */
    const int kMaxDisks = 8;

    /* 纺锤数量。 */
    const int kNumSpindles = 3;

    /* 一次打印到控制台的最大圆盘移动数（若要始终一次性打印所有行而不暂停询问输入，请改为 -1！ */
    const int kMaxLines = 25;

    /* 一个纺锤的宽度。 */
    const int kSpindleWidth = 20;

    /* 纺锤工作区之间的像素间距。 */
    const double kSpindleMarginSize = 10;

    /* 窗口边界与内容区域之间的像素间距。 */
    const double kPadding = 30;

    /* 窗口的宽高比。 */
    const double kMinAspectRatio = 5.0 / 3.0;

    /* 显示窗口的最小尺寸。 */
    const double kMinHeight = 20;
    const double kMinWidth  = kMinHeight * kMinAspectRatio;

    /* 允许的最小圆盘宽度。 */
    const double kMinDiskWidth = 3 * kSpindleWidth;

    /* 纺锤颜色：赤褐色！ */
    const string kSpindleColor = "#80461B";

    /* 每个圆盘的颜色。 */
    const string kDiskColors[] = {
       "#000000",
       "#0000ff",
       "#ff00ff",
       "#ff0000",
       "#ff8000",
       "#ffff00",
       "#00ff00",
       "#00ffff"
    };
    /* 每个圆盘的边框颜色。这些只是圆盘颜色的较深版本
     * 如上所述。
     */
    const string kDiskBorderColors[] = {
        "#000000",
        "#000080",
        "#800080",
        "#800000",
        "#804000",
        "#808000",
        "#008000",
        "#008080"
    };

    /* 提醒先调整窗口大小的消息。 */
    const string kResizeMessage =
            "Don't forget to resize this window so that you can see both the graphics display "
            "and the Qt Creator debugger before hitting the \"Go!\" button. Once the debugger "
            "engages, you may not be able to resize or move this window.";

    /* 该消息的字体信息。 */
    const Font kResizeMessageFont(FontFamily::SERIF, FontStyle::ITALIC, 16, "#400080");

    /* 动画步数。 */
    const int kNumAnimationSteps = 50;

    /* 表示单个圆盘的类型。 */
    struct Disk {
        int size;    // 零表示最小圆盘，尺寸由此递增。
        GRect* rect; // 图形矩形。
    };

    struct Spindle {
        /* 当前有哪些 GRect。 */
        Stack<Disk> disksHere;

        /* 此纺锤的矩形。 */
        GRect* rect;

        /* 所分配区域的起始和结束 x 坐标
         * 添加到此纺锤。这是可放置圆盘的空间
         * 已移动。
         */
        double startX, endX;

        /* 纺锤的中心线。 */
        double centerX;
    };

    class TowersOfHanoiGUI: public ProblemHandler {
    public:
        TowersOfHanoiGUI(GWindow& window);
        ~TowersOfHanoiGUI();
        void actionPerformed(GObservable* source) override;

        void initHanoiDisplay(int mNumDisks, AnimationSpeed speed);
        void moveSingleDisk(char from, char to);

        bool shuttingDown() override;

    protected:
        void repaint() override;

    private:
        GRectangle mBounds;

        Temporary<GButton> mGoButton;

        Vector<Spindle> mSpindles;

        bool mHasStarted = false;

        int mNumDisks;
        double mDiskHeight;

        double mPauseTime;

        void   setupSpindles();
        void   setupDisks();
        double diskYPosition(int spindle);
        void   computeBounds();
        void   animateDiskPath(GRect* disk, double endX, double endY, double totalTime);

        void clearGraphics();
    };

    /* 噫，全局变量！我们经过仔细权衡后决定这样做
     * 选项。另一方面，你不应这样做。:-)
     *
     * 这些必须是原始指针，而不能是实际对象，以免它们被析构
     * 在静态对象销毁期间仍处于使用状态。
     */
    auto* theGUI        = new shared_ptr<TowersOfHanoiGUI>;
    auto* theGUILock    = new mutex();
    bool  isConsoleMode = false;

    /******** 实现 ********/

    /* 略带技巧的代码：更新图形显示时，希望强制重绘
     * 这样即使启用了调试器，我们仍能看到变化。
     */
    void add(GWindow& window, GObject* toAdd) {
        GThread::runOnQtGuiThread([&] {
            window.add(toAdd);
            window.repaint();
        });
    }
    void setLocation(GWindow& window, GObject* object, double x, double y) {
        GThread::runOnQtGuiThread([&] {
            object->setLocation(x, y);
            window.repaint();
        });
    }

    /* 设置纺锤。 */
    void TowersOfHanoiGUI::setupSpindles() {
        /* 计算可分配给一个轴的总水平区域。 */
        double workspaceWidth = mBounds.width / kNumSpindles;

        for (int i = 0; i < kNumSpindles; i++) {
            Spindle spindle;

            /* 适当设置工作区域。 */
            spindle.startX = mBounds.x + workspaceWidth * i       + kSpindleMarginSize;
            spindle.endX   = mBounds.x + workspaceWidth * (i + 1) - kSpindleMarginSize;

            /* 为此轴创建矩形。轴将居中位于
             * 工作区域，其高度等于圆盘数量加上
             * 一个（这样纺锤仍然可见）。它还会底部对齐。
             */
            double height = (mNumDisks + 1) * mDiskHeight;
            double y = mBounds.y + mBounds.height - height;

            /* 确定中心线位置，然后让矩形围绕它居中。 */
            spindle.centerX = (spindle.startX + spindle.endX) / 2.0;
            spindle.rect = new GRect(spindle.centerX - kSpindleWidth / 2.0, y, kSpindleWidth, height);
            spindle.rect->setFilled(true);
            spindle.rect->setColor(kSpindleColor);

            /* 将其添加到显示内容中。 */
            add(window(), spindle.rect);

            /* 将此轴添加到列表中。 */
            mSpindles += spindle;
        }
    }

    /* 创建并设置模拟中使用的所有圆盘。 */
    void TowersOfHanoiGUI::setupDisks() {
        for (int i = 0; i < mNumDisks; i++) {
            /* 需要确定圆盘的位置、颜色和大小。
             *
             * 为确定圆盘大小，我们将在工作区之间进行线性插值
             * 区域（最大可能宽度）和最小可能圆盘宽度
             * （指定为常量）。特别是，我们希望底部圆盘
             * 尺寸恰好填满纺锤工作区，而我们希望
             * 最上方圆盘的大小等于 kMinDiskWidth。我们使用的公式
             * 我们将使用以下公式：
             *
             * 圆盘 0 的宽度 = 工作区宽度。
             * 圆盘 i - 1 的宽度 = kMinDiskWidth。
             *
             * 因此：
             *
             * width = ((kMinDiskWidth - workspaceWidth) / (numDisks - 1)) * i + workspaceWidth
             *
             * 当 numDisks = 1 时存在一个边界情况，因此我们将单独处理它。
             */
            double workspaceWidth = mSpindles[0].endX - mSpindles[0].startX;

            double width;
            if (mNumDisks == 1) {
                width = workspaceWidth;
            } else {
                width = max(kMinDiskWidth, ((kMinDiskWidth - workspaceWidth) / (mNumDisks - 1)) * i + workspaceWidth);
            }

            /* 给定宽度，可通过取以下对象的中心线来找到 x 坐标：
             * 纺锤，并回退其宽度的一半。
             */
            double x = mSpindles[0].centerX - width / 2.0;

            /* 可以使用已有函数确定圆盘的 y 坐标
             * 用于确定下一个圆盘应放在轴上的何处。
             */
            double y = diskYPosition(0);

            /* 创建矩形。 */
            GRect* rect = new GRect(x, y, width, mDiskHeight);
            rect->setColor(kDiskBorderColors[kMaxDisks - 1 - i]);
            rect->setFilled(true);
            rect->setFillColor(kDiskColors[kMaxDisks - 1 - i]);

            /* 绘制圆盘。 */
            add(window(), rect);

            /* 将圆盘添加到轴上。 */
            Disk disk;
            disk.rect = rect;
            disk.size = mNumDisks - i; // 顺序反转，因为我们先创建最大的圆盘。

            mSpindles[0].disksHere.push(disk);
        }
    }

    /* 给定轴编号，返回下一个圆盘所在位置的 y 坐标
     * 将放置在该纺锤顶部。
     */
    double TowersOfHanoiGUI::diskYPosition(int spindle) {
        if (spindle < 0 || spindle >= mSpindles.size()) {
            error("Invalid spindle number.");
        }

        /* 位置按如下方式确定：
         *
         * 1. 从窗口底部开始。
         * 2. 按堆栈中的圆盘数量向后退。
         * 3. 再向后退一次，因为我们需要给出上方 y 坐标。
         *
         * 计算结果为 windowHeight - (disksInStack + 1) * diskHeight。
         */
        return mBounds.y + mBounds.height - (mSpindles[spindle].disksHere.size() + 1) * mDiskHeight;
    }

    /* 给定一个字符，将该字符映射到轴编号。 */
    int charToSpindle(char ch) {
        switch (ch) {
            case 'A': case 'a': return 0;
            case 'B': case 'b': return 1;
            case 'C': case 'c': return 2;
            default: error("Unknown spindle."); return -1;
        }
    }

    /* 给定动画中的时间，用 0（起点）到以下值之间的数字表示：
     * 和 1（终点）之间，插值计算圆盘在该时刻沿轨迹所在的位置
     * 使用三次 Hermite 样条随时间变化。这会使动画看起来明显
     * 比以前更平滑。
     *
     * http://en.wikipedia.org/wiki/Cubic_Hermite_spline
     */
    double interpolate(double t) {
        return -2 * t * t * t + 3 * t * t;
    }

    /* 让圆盘从当前位置移动到目标位置的动画。 */
    void TowersOfHanoiGUI::animateDiskPath(GRect* disk, double endX, double endY, double totalTime) {
        const double startX = disk->getX(), startY = disk->getY();

        /* 为移动添加动画！ */
        for (int i = 0; i < kNumAnimationSteps; i++) {
            /* 在起始位置和结束位置之间插值。为了确定
             * 对于插值量，我们使用三次 Hermite 样条来映射
             * 从已完成动画比例转换为更平滑的
             * 动画点。
             */
            double x = startX + (endX - startX) * interpolate(double(i) / (kNumAnimationSteps - 1));
            double y = startY + (endY - startY) * interpolate(double(i) / (kNumAnimationSteps - 1));
            setLocation(window(), disk, x, y);

            /* 暂停以让动画继续。实际上不会精确暂停
             * 恰好持续正确时长，因为其中存在一定延迟
             * 在图形调用中，但已经“足够接近”。
             */
            pause(totalTime / kNumAnimationSteps);
        }
    }

    void TowersOfHanoiGUI::computeBounds() {
        /* 计算显示区域可能的最大宽度和高度。 */
        double maxWidth  = max(kMinWidth,  window().getCanvasWidth()  - 2 * kPadding);
        double maxHeight = max(kMinHeight, window().getCanvasHeight() - 2 * kPadding);

        /* 确定当前宽高比。 */
        double empiricalAspectRatio = maxWidth / maxHeight;

        /* 绝不低于要求的宽高比。 */
        double width, height;
        if (empiricalAspectRatio < kMinAspectRatio) {
            width  = maxWidth;
            height = width / kMinAspectRatio;
        } else {
            width  = maxWidth;
            height = maxHeight;
        }

        /* 计算所需内边距。 */
        double xPadding = (window().getCanvasWidth()  - width)  / 2.0;
        double yPadding = (window().getCanvasHeight() - height) / 2.0;

        mBounds = {
            xPadding,
            yPadding,
            width,
            height
        };

        /* 确定单个圆盘的高度。我们希望圆盘大小满足
         * 每个轴都可以在顶部放置所有圆盘，然后留出一些垂直空间以
         * 显示每个纺锤顶部，然后在其上方显示两个空格。这样可以
         * 最终需要的“虚拟圆盘”数量等于圆盘总数
         * 实际使用的数量，再加四个额外项。
         */
        int numVirtualDisks = mNumDisks + 4;
        mDiskHeight = mBounds.height / numVirtualDisks;
    }

    /* 返回与给定常量关联的动画速度。 */
    double pauseTimeFor(AnimationSpeed speed) {
        switch (speed) {
        case AnimationSpeed::MOLASSES:
            return 1000;
        case AnimationSpeed::CHEETAH:
            return 500;
        case AnimationSpeed::PEREGRINE_FALCON:
            return 100;
        default:
            error("Unknown speed?");
            return -1;
        }
    }

    TowersOfHanoiGUI::TowersOfHanoiGUI(GWindow& window) : ProblemHandler(window) {
        mGoButton = Temporary<GButton>(new GButton("Go!"), window, "SOUTH");
    }
}

/* 恭喜！你已找到触发以下调用的函数：
 * solveTowersOfHanoi！
 */
void makeTheMagicHappen() {
    solveTowersOfHanoi(5, 'A', 'C', 'B');
}

namespace {
    void TowersOfHanoiGUI::actionPerformed(GObservable* source) {
        if (source == mGoButton) {
            /* 是的，演示已经开始！ */
            mHasStarted = true;

            setDemoOptionsEnabled(false);
            mGoButton->setEnabled(false);

            makeTheMagicHappen();

            mGoButton->setEnabled(true);
            setDemoOptionsEnabled(true);
        }
    }

    void TowersOfHanoiGUI::moveSingleDisk(char startCh, char finishCh) {
        /* 将起始轴和结束轴转换为索引。 */
        int start = charToSpindle(startCh), end = charToSpindle(finishCh);

        /* 确认起始轴不为空。 */
        if (mSpindles[start].disksHere.isEmpty()) {
            error("No disks at the start spindle.");
        }

        /* 获取要移动的圆盘。 */
        Disk disk = mSpindles[start].disksHere.pop();

        /* 确保可以合法地将圆盘从起始纺锤移动到
         * 结束轴。
         */
        if (!mSpindles[end].disksHere.isEmpty() &&
            mSpindles[end].disksHere.peek().size <= disk.size) {
            error("Cannot move a larger disk atop a smaller one.");
        }

        /* 确定动画三个部分中每部分必须持续多长时间
         * 动画。
         */
        double eachAnimationTime = mPauseTime / 3;

        /* 向上移动圆盘。 */
        animateDiskPath(disk.rect, disk.rect->getX(), mBounds.y, eachAnimationTime);

        /* 横向移动圆盘。需要通过居中计算新的 x 坐标
         * 将圆盘移过新的中线。
         */
        double newX = mSpindles[end].centerX - disk.rect->getWidth() / 2.0;
        animateDiskPath(disk.rect, newX, mBounds.y, eachAnimationTime);

        /* 向下移动圆盘。 */
        animateDiskPath(disk.rect, disk.rect->getX(), diskYPosition(end), eachAnimationTime);

        /* 更新内部状态：确保圆盘现在位于目标
         * 纺锤。
         */
        mSpindles[end].disksHere.push(disk);
    }



    /* 初始化显示。 */
    void TowersOfHanoiGUI::initHanoiDisplay(int numDisks, AnimationSpeed speed) {
        /* 验证输入。 */
        if (numDisks > kMaxDisks) {
            error("Sorry, but we can't support that many disks.");
        }

        if (numDisks <= 0) {
            error("Sorry, but we need a positive number of disks.");
        }

        clearGraphics();
        mNumDisks = numDisks;
        computeBounds();

        /* 初始化纺锤和圆盘。 */
        setupSpindles();
        setupDisks();

        mPauseTime = pauseTimeFor(speed);
    }

    void TowersOfHanoiGUI::clearGraphics() {
        window().clearCanvas();
        for (auto& spindle: mSpindles) {
            window().remove(spindle.rect);
            delete spindle.rect;

            while (!spindle.disksHere.isEmpty()) {
                auto disk = spindle.disksHere.pop();
                window().remove(disk.rect);
                delete disk.rect;
            }
        }
        mSpindles.clear();
    }

    TowersOfHanoiGUI::~TowersOfHanoiGUI() {
        clearGraphics();
    }

    void TowersOfHanoiGUI::repaint() {
        /* 如果已经完成演示，则不要显示调整大小的消息。 */
        if (!mHasStarted) {
            window().clearCanvasPixels();

            double width  = window().getCanvasWidth()  - 2 * kPadding;
            double height = window().getCanvasHeight() - 2 * kPadding;
            GRectangle bounds = {
                kPadding, kPadding, width, height
            };
            try {
                auto text = TextRender::construct(kResizeMessage, bounds, kResizeMessageFont);
                text->alignCenterHorizontally();
                text->alignCenterVertically();
                text->draw(window());
            } catch (const ErrorException &) {
                // 糟糕，文本无法放入框中。不要尝试。
            }
        }
    }

    bool TowersOfHanoiGUI::shuttingDown() {
        unique_lock<mutex> lock(*theGUILock);

        /* 释放此处存储的共享指针，以触发析构函数
         * GUI 使用完我们之后。
         */
        theGUI->reset();

        return true;
    }



    /******** 控制台实现 ********/
    class TowersOfHanoiConsole {
    public:
        bool condensedOutput = false;
        void initHanoiDisplay(int mNumDisks, AnimationSpeed speed);
        void moveSingleDisk(char from, char to);

    private:
        int mNumDisks;
        int mNumCalls = 0;
        Map<char, Vector<int>> mSpindles;

        double mPauseTime;

        void setup();
        void listDisks(char spindle);
        void listSpires();

    };

    TowersOfHanoiConsole console; // 全局实例

    /* 将 int 转换为用于轴标签的字母字符 */
    char convert(int i) {
        return (i % 26) + 'A';
    }

    /* 初始化 mSpindles，使所有 mNumDisks 个圆盘都位于最左侧纺锤，其余纺锤为空 */
    void TowersOfHanoiConsole::setup() {
        // 按字母表初始化纺锤（左侧为 'A'）
        for (int i = 0; i < kNumSpindles; i++){
            mSpindles[convert(i)] = { };
        }

        // 将圆盘添加到最左侧轴，使其从上到下按 1 到 mNumDisks 排列
        for (int i = 0; i < mNumDisks; i++) {
            mSpindles['A'].add(mNumDisks - i);
        }

    }

    /* 从顶部（vector 末尾）到底部（vector 开头）打印纺锤上的圆盘列表 */
    void TowersOfHanoiConsole::listDisks(char spindle) {
        for (int i = mSpindles[spindle].size() - 1; i >= 0; i--){
            cout << mSpindles[spindle][i];
            if (i > 0) {
                cout << " ";
            }
        }
    }

    /* 列出所有塔柱及其圆盘 */
    void TowersOfHanoiConsole::listSpires() {
        for (int i = 0; i < kNumSpindles; i++){
            cout << " " << convert(i) << " [";
            listDisks(convert(i));
            cout << "]";
            if (i < kNumSpindles - 1){
                cout << ",";
            }
        }
        cout << endl;
    }

    /* 等待用户输入空行。 */
    void pressEnterToContinue(const string& message) {
        string line;
        do {
            line = getLine(message);
        } while (!line.empty());
    }

    /**
     * 初始化控制台“显示”：在最左侧纺锤（纺锤 'A'）上设置 numDisks 个圆盘，并打印基于文本的设置说明
     *
     * @param numDisks 问题中使用的圆盘数量；所有圆盘最初都在最左侧轴上
     * @param speed 动画速度决定各打印语句之间的暂停长度
     */
    void TowersOfHanoiConsole::initHanoiDisplay(int numDisks, AnimationSpeed speed){
        if (numDisks > kMaxDisks) {
            error("Sorry, but we can't support that many disks.");
        }

        if (numDisks <= 0) {
            error("Sorry, but we need a positive number of disks.");
        }
        mNumDisks = numDisks;

        setup(); // 初始化纺锤和圆盘

        mPauseTime = pauseTimeFor(speed);

        // 设置说明
        cout << "The movement of the disks will be abbreviated, and at each move the state of all the spires will be printed. ";
        cout << "'1 from A to C:  A [2 3 4 5], B [], C [1]' translates to 'Disk 1 moves from A to C, and as a result the spires look like the following: 2, 3, 4, and 5 are on spire A, no disks are on spire B, and disk 1 is on spire C.'" << endl;

        pressEnterToContinue("Press enter when you're ready to begin.");

        cout << "Initial state: ";
        listSpires();

    }

    /* 打印移动说明，并更新内部状态以反映圆盘变化 */
    void TowersOfHanoiConsole::moveSingleDisk(char from, char to){
        // 检查是否已经打印 kMaxLines 行；如果是，则在继续打印前提示用户
        if (kMaxLines >= 0 && mNumCalls >= kMaxLines) {
            pressEnterToContinue("Press enter to continue printing lines.");
            mNumCalls = 0;
        }

        if (mSpindles[from].isEmpty()) {
            error("No disks at the start spire.");
        }

        // 执行移动——更新 mSpindles
        int currDisk = mSpindles[from][mSpindles[from].size() - 1];
        mSpindles[from].remove(mSpindles[from].size() - 1);

        if (!mSpindles[to].isEmpty() &&
            mSpindles[to][mSpindles[to].size() - 1] <= currDisk) {
            error("Cannot move a larger disk atop a smaller one.");
        }

        mSpindles[to].add(currDisk);

        cout << currDisk << " from " << from << " to " << to << ": ";
        listSpires();

        mNumCalls++;
    }
}

GRAPHICS_HANDLER("Towers of Hanoi", GWindow& window) {
    isConsoleMode = false;

    unique_lock<mutex> lock(*theGUILock);
    if (!*theGUI) {
        theGUI->reset(new TowersOfHanoiGUI(window));
    }
    return *theGUI;
}

void initHanoiDisplay(int n, AnimationSpeed speed) {
    if (!isConsoleMode) {
        unique_lock<mutex> lock(*theGUILock);
        if (!*theGUI) {
            error("No display was detected. This can happen if you tried calling one of the "
                  "Towers of Hanoi graphics functions from a test case, which isn't permitted.");
        }

        (*theGUI)->initHanoiDisplay(n, speed);
    } else {
        /* 已完成：设置汉诺塔图形。 */
        console.initHanoiDisplay(n, speed);
    }
}

void moveSingleDisk(char start, char finish) {
    if (!isConsoleMode) {
        unique_lock<mutex> lock(*theGUILock);
        if (!*theGUI) {
            error("No display was detected. This can happen if you tried calling one of the "
                  "Towers of Hanoi graphics functions from a test case, which isn't permitted.");
        }

        (*theGUI)->moveSingleDisk(start, finish);
    } else {
        console.moveSingleDisk(start, finish);
    }
}

CONSOLE_HANDLER("Towers of Hanoi") {
    /* 将全局模式设为 console，使处理程序知道当前处于控制台模式。 */
    isConsoleMode = true;

    makeTheMagicHappen();
}
