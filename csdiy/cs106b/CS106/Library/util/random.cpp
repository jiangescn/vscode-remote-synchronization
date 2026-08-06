/*
 * 文件：random.cpp
 * ----------------
 * 此文件实现 random.h 接口。
 *
 * @version 2019/05/16
 * - 添加接受最小/最大 RGB 的 randomColor
 * @version 2017/10/05
 * - 添加 randomFeedClear
 * @version 2017/09/28
 * - 将随机“feed”函数移到 autograder 命名空间
 * - 确保随机提供的整数位于指定范围内
 * @version 2016/10/04
 * - 移除所有静态变量（改用 STATIC_VARIABLE 宏）
 * @version 2016/08/02
 * - 添加 randomColor、randomColorString
 * @version 2014/10/19
 * - 按字母顺序排列函数
 * @version 2014/10/08
 * - 移除“using namespace”语句
 */

#include "random.h"
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <queue>
#include <sstream>
#include "error.h"
#include "private/static.h"

/* 私有函数原型 */

static void initRandomSeed();

bool randomBool() {
    return randomChance(0.5);
}

/*
 * 实现说明：randomChance
 * ----------------------------------
 * randomChance 的代码调用 randomReal(0, 1)，然后检查
 * 结果是否小于所请求的概率。
 */
bool randomChance(double p) {
    initRandomSeed();
    return randomReal(0, 1) < p;
}

int randomColor() {
    initRandomSeed();
    return rand() & 0x00ffffff;
}

int randomColor(int minRGB, int maxRGB) {
    if (minRGB < 0 || minRGB > 255 || maxRGB < 0 || maxRGB > 255
            || minRGB > maxRGB) {
        error("randomColor: min/max values out of range");
    }
    int r = randomInteger(minRGB, maxRGB);
    int g = randomInteger(minRGB, maxRGB);
    int b = randomInteger(minRGB, maxRGB);
    return r << 16 | g << 8 | b;
}

// 参见 gcolor.h 中的 convertRGBToColor（此处重复以避免依赖 Qt）
std::string randomColorString() {
    int rgb = randomColor();
    std::ostringstream os;
    os << std::hex << std::uppercase << "#";
    os << std::setw(2) << std::setfill('0') << (rgb >> 16 & 0xFF);
    os << std::setw(2) << std::setfill('0') << (rgb >> 8 & 0xFF);
    os << std::setw(2) << std::setfill('0') << (rgb & 0xFF);
    return os.str();
}

std::string randomColorString(int minRGB, int maxRGB) {
    int rgb = randomColor(minRGB, maxRGB);
    std::ostringstream os;
    os << std::hex << std::uppercase << "#";
    os << std::setw(2) << std::setfill('0') << (rgb >> 16 & 0xFF);
    os << std::setw(2) << std::setfill('0') << (rgb >> 8 & 0xFF);
    os << std::setw(2) << std::setfill('0') << (rgb & 0xFF);
    return os.str();
}

/*
 * 实现说明：randomInteger
 * -----------------------------------
 * randomInteger 的代码分四步生成数字：
 *
 * 1. 在范围 [0 .. 1) 中生成一个随机实数 d。
 * 2. 将数字缩放到范围 [0 .. N)，其中 N 是值的数量。
 * 3. 平移数字，使范围从适当值开始。
 * 4. 将结果转换为下一个较小整数。
 *
 * 由于表达式和
 *
 *     RAND_MAX + 1
 *
 * 以及值数量的表达式
 *
 *     high - low + 1
 *
 * 可能溢出整数范围。因此这些计算必须
 * 使用 double 而不是 int 执行。
 */
int randomInteger(int low, int high) {
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (double(high) - low + 1);
    return int(floor(low + s));
}

/*
 * 实现说明：randomReal
 * --------------------------------
 * randomReal 的代码与 randomInteger 类似，
 * 不执行最后的转换步骤。
 */
double randomReal(double low, double high) {
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (high - low);
    return low + s;
}

/*
 * 实现说明：setRandomSeed
 * -----------------------------------
 * setRandomSeed 函数只是将其参数转发给 srand。
 * 必须调用 initRandomSeed 来设置 initialized 标志。
 */
void setRandomSeed(int seed) {
    initRandomSeed();
    srand(seed);
}

/*
 * 实现说明：initRandomSeed
 * ------------------------------------
 * initRandomSeed 函数声明了一个静态变量，用来记录
 * 种子是否已初始化。首次调用 initRandomSeed 时
 * 调用时 initialized 为 false，因此种子被设置为当前时间。
 */
static void initRandomSeed() {
    static bool _initialized = false;
    if (!_initialized) {
        srand(int(time(nullptr)));
        rand();   // BUG 修复：通过一次无用调用启动随机数生成
        _initialized = true;
    }
}
