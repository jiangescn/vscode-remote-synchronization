#ifndef DisasterPlanning_Included
#define DisasterPlanning_Included

#include <string>
#include "set.h"
#include "map.h"

/**
 * 给定某国家或地区的交通网格，以及可用于防灾物资的城市数量
 * 物资可以囤积，返回是否能在最多以下数量内囤积灾难物资
 * 指定数量的城市，使每个城市要么拥有补给，要么与一个拥有补给的城市相邻
 * 执行。
 * <p>
 * 此函数可以假定每个城市都是交通映射中的键，并且道路
 * 双向：如果存在从城市 A 到城市 B 的道路，则也存在从城市 B 返回
 * 城市 A 也是如此。
 * <p>
 * 城市数量可以为零，但绝不能为负数。如果为负数，你
 * 应通过调用 error() 函数报告错误。
 *
 * @param roadNetwork 底层交通网络。
 * @param numCities 能够负担用于存放补给品的城市数量。
 * @param supplyLocations 输出参数；如果存在解，则填入应选择的城市。
 * @return 是否存在解。
 */
bool canBeMadeDisasterReady(const Map<std::string, Set<std::string>>& roadNetwork,
                            int numCities,
                            Set<std::string>& supplyLocations);

#endif
