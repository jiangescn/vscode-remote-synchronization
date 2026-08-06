#ifndef DataPoint_Included
#define DataPoint_Included

#include <string>
#include <ostream>
#include <istream>
#include "Demos/DataPointAlloc.h"

/* 表示数据点的类型。本作业全程都会使用此类型
 * 表示某段信息（此处为字符串）及其关联的
 * 权重（此处为 double）。原则上可以设想包含更多
 * 由某个键（一般信息）及其关联内容组成的复杂结构
 * 关联权重，其中键按权重排序。
 */
struct DataPoint {
    std::string name;
    double weight;

    TRACK_ALLOCATIONS_OF(DataPoint);
    ADD_SAFETY_CHECKS_TO(DataPoint);
};





/* 以下所有内容都是我们提供的额外功能，用于让以下操作更容易：
 * 处理 DataPoint。这涉及我们尚未讲到的内容
 * 本季度的 CS106B；如对此工作方式有疑问，请联系我们！
 */

/* 一些用于处理 DataPoint 的实用运算符。 */
bool operator== (const DataPoint& lhs, const DataPoint& rhs);
bool operator!= (const DataPoint& lhs, const DataPoint& rhs);

/* 将 DataPoint 写入流。 */
std::ostream& operator<< (std::ostream& out, const DataPoint& pt);

/* 从流中读取一个 DataPoint。 */
std::istream& operator>> (std::istream& in, DataPoint& result);

/* 不应使用关系运算符直接相互比较 DataPoint
 * 运算符。如果你在这里附近遇到编译器错误，很可能是
 *
 *   1. 你正在相互比较 DataPoint 对象，例如
 *
 *         if (dp1 < dp2) { ... 错误！ ... }
 *
 *      若是这种情况，需要明确指定希望比较的内容
 *      相互比较。你的本意是否是比较它们的
 *      权重？
 *
 *         if (dp1.weight < dp2.weight) { ... 正确！ ... }
 *
 *   2. 你正在构造 Set<DataPoint> 或 Map<DataPoint, Something>。
 *      就本作业而言，不需要执行这两种操作中的任何一种
 *      操作。看看是否有其他方式可以实现你的具体目标。
 */
bool operator<  (const DataPoint& lhs, const DataPoint& rhs) = delete;
bool operator<= (const DataPoint& lhs, const DataPoint& rhs) = delete;
bool operator>= (const DataPoint& lhs, const DataPoint& rhs) = delete;
bool operator>  (const DataPoint& lhs, const DataPoint& rhs) = delete;

#endif
