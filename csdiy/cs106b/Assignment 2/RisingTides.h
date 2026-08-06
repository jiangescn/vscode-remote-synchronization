#ifndef RisingTides_Included
#define RisingTides_Included

#include "grid.h"
#include "vector.h"

/**
 * 给定地形和海拔，返回 Grid<bool>，表示每个单元格是否
 * 位于水下。水下单元格标记为 true，水上单元格标记为 false。
 * 如果水能从某个水源沿一条路径到达某单元格，该单元格最终会被淹没，该路径
 * 绝不会流到水位以上。特别是，与水位高度相同的点
 * 与水源之间没有更高海拔单元格阻隔的单元格将位于水下。
 *
 * 请记住，水只能沿基数方向流动（上、下、左、右），
 * 不能沿对角线。
 *
 * 可以假定地形中的所有水源都位于边界内
 * 地形。水源数量可以任意，包括零个。
 *
 * 你的解法需要适用于任意大小的地形，包括
 * 包含数百万个单元格。
 *
 * @param terrain 地形高度图。
 * @param sources 所有水源的位置，可以假定它们都在边界内。
 * @param height 水面高度，单位为米。
 * @return 表示哪些单元格被淹没的 Grid，其中 true 表示“已淹没”，并且
 *         false 表示“水面之上”。
 */
Grid<bool> floodedRegionsIn(const Grid<double>& terrain,
                            const Vector<GridLocation>& sources,
                            double height);

#endif
