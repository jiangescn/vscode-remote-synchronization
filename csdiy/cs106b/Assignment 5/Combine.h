#ifndef Combine_Included
#define Combine_Included

#include "Demos/DataPoint.h"
#include "vector.h"

/**
 * 给定多个不同的有序序列列表，将所有这些有序序列合并
 * 合并为一个整体的大型有序序列。
 *
 * 每个序列表示为 Vector<DataPoint>，其中 DataPoint 按以下顺序排序
 * 按权重排序。各序列不一定具有相同长度，事实上
 * 序列可能完全为空。
 *
 * 此函数应在 O(n log k) 时间内运行，其中 n 是元素总数
 * 跨越所有这些序列，而 k 是序列数量。
 *
 * 这些序列中可能有许多数据点具有相同权重。如果是这样，请
 * 可以按任意方式打破平局。
 *
 * @param toMerge 要合并的有序序列列表。每个序列均按权重排序，
 *                按升序。
 * @return 这些序列中所有元素按排序顺序组成的列表。
 */
Vector<DataPoint> combine(const Vector<Vector<DataPoint>>& toMerge);

#endif
