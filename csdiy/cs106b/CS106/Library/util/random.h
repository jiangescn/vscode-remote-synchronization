/*
 * 文件：random.h
 * --------------
 * 此文件导出用于生成伪随机数的函数。
 *
 * @version 2019/05/16
 * - 添加接受最小/最大 RGB 的 randomColor
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 * @version 2017/10/05
 * - 添加 randomFeedClear
 * @version 2017/09/28
 * - 将随机“feed”函数移到 autograder 命名空间
 * @version 2016/08/02
 * - 添加 randomColor、randomColorString
 * @version 2014/10/19
 * - 按字母顺序排列函数
 */


#ifndef _random_h
#define _random_h

#include <string>

/**
 * 以 50% 的概率返回 <code>true</code>。
 */
bool randomBool();

/**
 * 以 <code>p</code> 指定的概率返回 <code>true</code>。
 * 参数 <code>p</code> 必须是介于以下范围的浮点数
 * 0（从不）和 1（总是）。例如，调用
 * <code>randomChance(.30)</code> 有 30% 的概率返回 <code>true</code>
 * 时间。
 */
bool randomChance(double p);

/**
 * 以整数返回随机 RGB 颜色。
 * 另请参阅：gwindow.h convertRGBToColor()
 */
int randomColor();

/**
 * 以整数返回随机 RGB 颜色，其中 RGB 分量的值
 * 限制在给定最小值和最大值之间。
 * @throw 如果 min 或 max 不在 [0..255] 内，或 min > max，则抛出 ErrorException
 * 另请参阅：gwindow.h convertRGBToColor()
 */
int randomColor(int minRGB, int maxRGB);

/**
 * 以十六进制字符串返回随机 RGB 颜色，例如品红色为 "#ff00ff"。
 * 另请参阅：gwindow.h convertColorToRGB()
 */
std::string randomColorString();

/**
 * 以十六进制字符串返回随机 RGB 颜色，例如品红色为 "#ff00ff"，
 * RGB 分量值限制在给定最小值和最大值之间。
 * @throw 如果 min 或 max 不在 [0..255] 内，或 min > max，则抛出 ErrorException
 * 另请参阅：gwindow.h convertColorToRGB()
 */
std::string randomColorString(int minRGB, int maxRGB);

/**
 * 返回范围从 <code>low</code> 到以下值的随机整数
 * <code>high</code>，包含该值。
 */
int randomInteger(int low, int high);

/**
 * 返回半开区间内的随机实数
 * [<code>low</code>&nbsp;..&nbsp;<code>high</code>)。半开区间
 * 区间包含第一个端点，但不包含第二个端点，这
 * 表示结果始终大于或等于
 * 不小于 <code>low</code>，但严格小于 <code>high</code>。
 */
double randomReal(double low, double high);

/**
 * 将内部随机数种子设置为指定值。你
 * 可以使用此函数为以下对象设置特定起点：
 * 伪随机序列，或确保程序行为
 * 在调试阶段可重复。
 */
void setRandomSeed(int seed);

#endif // _random_h
