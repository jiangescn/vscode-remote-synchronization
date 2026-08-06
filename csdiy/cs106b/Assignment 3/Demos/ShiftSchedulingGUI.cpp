#include "GUI/MiniGUI.h"
#include "ShiftScheduling.h"
#include "random.h"
#include "simpio.h"
#include <string>
using namespace std;
using namespace MiniGUI;

namespace {
    /* 通用图形常量。 */
    const string kBackgroundColor = "#FFFFFF";
    const double kWindowPadding = 10;

    /* 线条颜色。 */
    const string kLineColor = "#989898"; // 西班牙灰

    /* Grid 属性。 */
    const Font   kHeaderFont(FontFamily::SANS_SERIF, FontStyle::NORMAL, 14, "#989898");
    const double kHeaderHeight    = 50;

    const Font   kHourFont(FontFamily::SANS_SERIF, FontStyle::NORMAL, 8, "#989898");
    const double kHourWidth       = 30;

    /* 允许该人员工作的小时数。 */
    const int kStandardHours = 30;

    /* 班次属性。 */
    const string kShiftBackgroundColor = "#0093AF"; // 孟塞尔蓝
    const string kShiftBorderColor     = "#004957"; // Munsell Blue 的分量，减半
    const Font kShiftFont(FontFamily::SANS_SERIF, FontStyle::NORMAL, 14, "#FFFFFF");

    const string kUnchosenShiftBackgroundColor = "#E3DAC9"; // 骨白色
    const string kUnchosenShiftBorderColor     = "#716D64"; // Bone 的分量，减半
    const Font kUnchosenShiftFont(FontFamily::SANS_SERIF, FontStyle::NORMAL, 14, "#383632"); // Bone 的分量，缩小为四分之一
    const double kShiftPadding         = 5;

    /* 班次值的范围。 */
    const int kLowWeight  = 0;
    const int kHighWeight = 99 / 8; // 最长班次的长度

    /* 可用班次。 */
    const Set<Shift> kStandardShifts = {
        { Day::SUNDAY,  8, 14, 0 },
        { Day::SUNDAY, 12, 18, 0 },

        { Day::MONDAY,  8, 12, 0 },
        { Day::MONDAY, 12, 16, 0 },
        { Day::MONDAY, 16, 20, 0 },
        { Day::MONDAY,  8, 16, 0 },
        { Day::MONDAY, 12, 20, 0 },

        { Day::TUESDAY,  8, 12, 0 },
        { Day::TUESDAY, 12, 16, 0 },
        { Day::TUESDAY, 16, 20, 0 },
        { Day::TUESDAY,  8, 16, 0 },
        { Day::TUESDAY, 12, 20, 0 },

        { Day::WEDNESDAY,  8, 12, 0 },
        { Day::WEDNESDAY, 12, 16, 0 },
        { Day::WEDNESDAY, 16, 20, 0 },
        { Day::WEDNESDAY,  8, 16, 0 },
        { Day::WEDNESDAY, 12, 20, 0 },

        { Day::THURSDAY,  8, 12, 0 },
        { Day::THURSDAY, 12, 16, 0 },
        { Day::THURSDAY, 16, 20, 0 },
        { Day::THURSDAY,  8, 16, 0 },
        { Day::THURSDAY, 12, 20, 0 },

        { Day::FRIDAY,  8, 12, 0 },
        { Day::FRIDAY, 12, 16, 0 },
        { Day::FRIDAY, 16, 20, 0 },
        { Day::FRIDAY,  8, 16, 0 },
        { Day::FRIDAY, 12, 20, 0 },

        { Day::SATURDAY,  8, 14, 0 },
        { Day::SATURDAY, 12, 18, 0 },
    };


    /* 按顺序返回一周所有日期的列表。 */
    const Vector<Day> kAllDays = {
        Day::SUNDAY,
        Day::MONDAY,
        Day::TUESDAY,
        Day::WEDNESDAY,
        Day::THURSDAY,
        Day::FRIDAY,
        Day::SATURDAY
    };

    /* 将一种类型的集合转换为另一种类型。 */
    template <typename Result, typename T>
    Result setCast(const T& input) {
        Result result;
        for (const auto& elem: input) {
            result += elem;
        }
        return result;
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

    /* 给定窗口，返回该窗口内的绘图区域。 */
    GRectangle boundsFor(GWindow& window) {
        return expand(0.0, 0.0, window.getCanvasWidth(), window.getCanvasHeight(), -kWindowPadding);
    }

    /* 将星期转换为字符串。 */
    string dayToString(Day day) {
        ostringstream result;
        result << day;
        return result.str();
    }

    /* 在给定边界内居中绘制单个文本字符串。 */
    void drawCenteredText(const string& text,
                          const GRectangle& bounds,
                          const Font& font,
                          GWindow& window) {
        auto render = TextRender::construct(text, bounds, font);
        render->alignCenterHorizontally();
        render->alignCenterVertically();
        render->draw(window);
    }

    /* 给定列的客户端区域，返回 GRectangle 列表，每个矩形
     * 它对应小时数的边界框。第一个条目
     * 对应时间 kLowHour，下一个对应 kLowHour + 1，依此类推。
     *
     * 尽管每个小时都有边界框，但通常不会绘制该框。
     */
    Vector<GRectangle> cellBoundingBoxes(const GRectangle& bounds, int lowHour, int highHour) {
        Vector<GRectangle> result;

        double cellHeight = bounds.height / (highHour - lowHour + 1);
        for (int hour = lowHour; hour <= highHour; hour++) {
            result.add({
                bounds.x, bounds.y + cellHeight * (hour - lowHour),
                bounds.width, cellHeight
            });
        }

        return result;
    }

    /* 绘制日历视图的一列。bounds 参数表示
     * 此列应占用的空间。
     */
    void drawColumnFor(Day day, GWindow& window, const GRectangle& headerSpace,
                       const GRectangle& columnSpace,
                       int lowHour, int highHour) {
        /* 绘制标题。 */
        window.setColor(kLineColor);
        window.drawRect(headerSpace);
        drawCenteredText(dayToString(day), headerSpace, kHeaderFont, window);

        /* 绘制列轮廓。 */
        window.setColor(kLineColor);
        window.drawRect(columnSpace);

        /* 绘制列内的内部线条。 */
        for (auto box: cellBoundingBoxes(columnSpace, lowHour, highHour)) {
            window.drawLine(box.x, box.y + box.height / 2,
                            box.x + box.width, box.y + box.height / 2);
        }
    }

    /* 给定小时，返回该小时的人类可读表示。 */
    string hourToString(int hour) {
        hour %= 24;

        if (hour ==  0) return "12AM";
        if (hour < 12)  return to_string(hour) + "AM";
        if (hour == 12) return "12PM";
        return to_string(hour - 12) + "PM";
    }

    /* 在每行前绘制标题。 */
    void drawRowHeaders(GWindow& window, const GRectangle& bounds, int lowHour, int highHour) {
        auto boxes = cellBoundingBoxes(bounds, lowHour, highHour);

        for (int i = 0; i < boxes.size(); i++) {
            int hour = lowHour + i;
            drawCenteredText(hourToString(hour), boxes[i], kHourFont, window);
        }
    }

    /* 在指定空间中绘制日历网格。 */
    void drawGrid(GWindow& window,
                  const GRectangle& rowSpace,
                  const GRectangle& columnHeaderSpace,
                  const GRectangle& columnSpace,
                  double columnWidth,
                  int lowHour, int highHour) {
        /* 绘制所有列。 */
        for (auto day: kAllDays) {
            double x = columnSpace.x + static_cast<double>(day) * columnWidth;
            drawColumnFor(day, window, {
                              x, columnHeaderSpace.y,
                              columnWidth,
                              columnHeaderSpace.height
                          }, {
                              x, columnSpace.y,
                              columnWidth, columnSpace.height
                          }, lowHour, highHour);
        }

        /* 绘制行标题。 */
        drawRowHeaders(window, rowSpace, lowHour, highHour);
    }

    /* 渲染所选班次集合，假定它们都在同一
     * 某一天，位于分配给该天的边界框内。
     */
    void drawShiftsForDay(GWindow& window, const GRectangle& bounds,
                          const Set<Shift>& shifts,
                          const Set<Shift>& chosen,
                          int lowHour, int highHour) {
        /* 边界情况：如果没有班次，则没有内容可绘制！ */
        if (shifts.isEmpty()) return;

        /* 现在的问题是，如何以最少方式细分此列。事实证明
         * 可视为一类称为区间图的图的着色问题
         * （节点对应区间，边对应重叠的
         * 区间）！一般而言，图着色是难解问题，但幸运的是
         * 区间图的图着色问题已知可以在
         * 通过贪心算法在多项式时间内完成（按开始时间排序区间，并
         * 将每个区间放入第一个能容纳它的槽位）。这源自
         * 区间图是完美图这一事实。
         *
         * 我们将用它为每个区间分配一个虚拟子列。幸运的是，
         * 用于班次的比较函数会隐式按开始时间排序，
         * 这样就能遍历班次并找到第一个满足条件的子列
         * 不会与它们冲突！
         *
         * 可以使用更巧妙的数据结构加速，但由于我们
         * 处理少量区间时无需在此处执行此操作。
         */
        Map<Shift, int> subcolumns;       // 键是班次，索引是其子列。
        Map<int,   int> subcolumnBottoms; // 键是子列，索引是下一个空闲位置
                                          // 该子列中的位置。

        for (const auto& shift: shifts) {
            /* 依次尝试所有子列，直到找到可容纳它的位置。 */
            for (int i = 0; ; i++) {
                /* autoinsert 默认为 0，对我们而言总是可行。 */
                if (subcolumnBottoms[i] <= shift.startHour) {
                    subcolumns[shift] = i;
                    subcolumnBottoms[i] = shift.endHour;
                    break;
                }
            }
        }

        /* 所需子列数等于 subcolumnBottoms 映射的大小，因为
         * 只有在需要探测某个特定子列时才会访问它。
         */
        double width = bounds.width / subcolumnBottoms.size();
        auto boxes = cellBoundingBoxes(bounds, lowHour, highHour);

        /* 在各自子列中绘制每个班次。 */
        for (const auto& shift: shifts) {

            /* 将逻辑小时转换为从 0 开始的小时。 */
            int startIndex = shift.startHour - lowHour;
            int endIndex   = shift.endHour   - lowHour;

            double x = bounds.x + width * subcolumns[shift];
            double y = boxes[startIndex].y + boxes[startIndex].height / 2.0;

            /* 所有框的高度相同，因此只需查看它们之间的距离。 */
            double height = boxes[endIndex].y - boxes[startIndex].y;

            auto box = expand(x, y, width, height, -kShiftPadding);

            /* 绘制方框。 */
            window.setColor(chosen.contains(shift)? kShiftBackgroundColor : kUnchosenShiftBackgroundColor);
            window.fillRect(box);
            window.setColor(chosen.contains(shift)? kShiftBorderColor : kUnchosenShiftBorderColor);
            window.drawRect(box);

            /* 绘制值。 */
            drawCenteredText(to_string(valueOf(shift)), box, chosen.contains(shift)? kShiftFont : kUnchosenShiftFont, window);
        }
    }

    /* 将指定班次集合绘制到日历网格中。 */
    void drawShifts(GWindow& window, const GRectangle& columnSpace, double columnWidth,
                    const Set<Shift>& shifts, const Set<Shift>& chosen,
                    int lowHour, int highHour) {
        /* 按天划分班次以便渲染。 */
        Map<Day, Set<Shift>> byDay;
        for (const auto& shift: shifts) {
            byDay[shift.day] += shift;
        }

        /* 分别渲染每一天。 */
        for (Day day: byDay) {
            double x = columnSpace.x + columnWidth * static_cast<double>(day);
            drawShiftsForDay(window, {
                                 x, columnSpace.y, columnWidth, columnSpace.height
                             }, byDay[day], chosen, lowHour, highHour);
        }
    }

    /* 给定班次集合，返回这些班次的总价值。 */
    int valueOf(const Set<Shift>& shifts) {
        int result = 0;
        for (const auto& shift: shifts) {
            result += valueOf(shift);
        }
        return result;
    }

    /* 给定班次集合，返回这些班次的总时长。 */
    int lengthOf(const Set<Shift>& shifts) {
        int result = 0;
        for (const auto& shift: shifts) {
            result += lengthOf(shift);
        }
        return result;
    }

    /* 用于可视化以下过程会生成的班次类型的问题处理程序
     * 最优调度器。
    */
    class ShiftSchedulingGUI: public ProblemHandler {
    public:
        ShiftSchedulingGUI(GWindow& window);

        void actionPerformed(GObservable* source) override;

    protected:
        void repaint() override;

    private:
        Set<Shift> mShifts; // 要显示的班次
        Set<Shift> mChosen; // 哪些已由用户选取。

        /* 图形控件。 */
        Temporary<GButton> mSolve;
        Temporary<GButton> mRandomize;
        Temporary<GLabel>  mStatus;

        /* 随机化系统中的权重。 */
        void randomizeWeights();

        /* 返回描述所生成解的字符串。 */
        string solutionDescription() const;
    };


    ShiftSchedulingGUI::ShiftSchedulingGUI(GWindow& window) : ProblemHandler(window) {
        mSolve     = Temporary<GButton>(new GButton("Optimize"), window, "EAST");
        mRandomize = Temporary<GButton>(new GButton("Randomize Values"), window, "EAST");
        mStatus    = Temporary<GLabel> (new GLabel(" "), window, "SOUTH");

        randomizeWeights();
    }

    void ShiftSchedulingGUI::actionPerformed(GObservable* source) {
        if (source == mSolve) {
            mSolve->setEnabled(false);
            mRandomize->setEnabled(false);
            mStatus->setText("Optimizing...");
            mChosen = highestValueScheduleFor(mShifts, kStandardHours);
            requestRepaint();
            mStatus->setText(solutionDescription());
            mRandomize->setEnabled(true);
            mSolve->setEnabled(true);
        } else if (source == mRandomize) {
            randomizeWeights();
            mChosen.clear();
            requestRepaint();
        }
    }

    void ShiftSchedulingGUI::repaint() {
        clearDisplay(window(), kBackgroundColor);

        /* 确定行和列的位置。 */
        auto bounds = boundsFor(window());

        /* 列标题相对于行起点有偏移。 */
        GRectangle columnHeaderSpace = {
            bounds.x + kHourWidth, bounds.y,
            bounds.width - kHourWidth, kHeaderHeight
        };

        /* 行空间会按列标题的高度向下偏移，但
         * 否则会紧贴边框。
         */
        GRectangle rowSpace = {
            bounds.x, columnHeaderSpace.y + columnHeaderSpace.height,
            kHourWidth, bounds.height - columnHeaderSpace.y - columnHeaderSpace.height
        };

        /* 两侧夹着标题的列空间。 */
        GRectangle columnSpace = {
            rowSpace.x + rowSpace.width, rowSpace.y,
            bounds.width - rowSpace.width, rowSpace.height
        };

        /* 确定每列的宽度。 */
        double columnWidth = columnSpace.width / kAllDays.size();

        /* 找出这些班次覆盖的小时范围。如果没有班次，则默认使用
         * 0（午夜）和 24（午夜）。
         */
        int lowHour = 0;
        int highHour = 24;

        if (!mShifts.isEmpty()) {
            lowHour = min_element(mShifts.begin(), mShifts.end(), [](const Shift& lhs, const Shift& rhs) {
                return lhs.startHour < rhs.startHour;
            })->startHour;
            highHour = max_element(mShifts.begin(), mShifts.end(), [](const Shift& lhs, const Shift& rhs) {
                return lhs.endHour < rhs.endHour;
            })->endHour;
        }

        drawGrid(window(), rowSpace, columnHeaderSpace, columnSpace, columnWidth, lowHour, highHour);
        drawShifts(window(), columnSpace, columnWidth, mShifts, mChosen, lowHour, highHour);
    }

    string ShiftSchedulingGUI::solutionDescription() const {
        ostringstream builder;
        builder << "Best solution produces " << valueOf(mChosen)
                << " value, using " << lengthOf(mChosen)
                << " of " << kStandardHours << " available hours.";
        return builder.str();
    }

    void ShiftSchedulingGUI::randomizeWeights() {
        /* 按每小时随机分配权重。即生成每小时值，
         * 然后用该每小时数值对偏移量加权。
         */
        mShifts.clear();
        for (Shift shift: kStandardShifts) {
            shift.value = randomInteger(kLowWeight, kHighWeight) * (shift.endHour - shift.startHour);
            mShifts += shift;
        }
    }
}

GRAPHICS_HANDLER("Shift Scheduling", GWindow& window) {
    return make_shared<ShiftSchedulingGUI>(window);
}

CONSOLE_HANDLER("Shift Scheduling") {
    cout << "We will generate random values for a set of seven shifts" << endl;
    cout << "and an employee who has twelve free hours, then report which" << endl;
    cout << "shifts were selected." << endl;
    cout << endl;

    do {
        Set<Shift> shifts;
        for (Shift shift: kStandardShifts) {
            shift.value = randomInteger(0, 100);
            shifts += shift;
        }

        cout << "The shifts are: " << endl;
        for (Shift shift: shifts) {
            cout << "  " << shift << endl;
        }

        auto result = highestValueScheduleFor(shifts, 12);
        cout << "Your code reports that the employee should pick these shifts: " << endl;

        shifts.clear();
        int value = 0;
        for (Shift shift: result) {
            shifts += shift;
            value += valueOf(shift);
        }

        for (Shift shift: shifts) {
            cout << "  " << shift << endl;
        }
        cout << "This produces $" << value << " of value." << endl;

    } while (getYesOrNo("Want to see another set of shifts? "));
}
