#ifndef DisasterParser_Included
#define DisasterParser_Included

#include "DisasterPlanning.h"
#include "map.h"
#include "hashset.h"
#include "gtypes.h"
#include <string>
#include <istream>

/**
 * 表示灾害准备问题测试用例的类型。
 */
struct DisasterTest {
    Map<std::string, Set<std::string>> network; // 道路网络
    Map<std::string, GPoint> cityLocations;     // 每个城市应绘制的位置
};

/**
 * 给定指向 Disaster Preparation 测试用例的流，
 * 从该测试用例中提取数据。
 *
 * @param source 包含测试用例的流。
 * @return 从文件读取的测试用例。
 * @throws 如果发生错误或文件无效，则抛出 ErrorException。
 */
DisasterTest loadDisaster(std::istream& source);

#endif
