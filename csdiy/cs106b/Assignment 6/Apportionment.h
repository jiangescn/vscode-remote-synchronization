#pragma once

#include "map.h"
#include <string>

/* 使用以下方法将 numSeats 个众议院席位分配给给定州集合：
 * Huntington-Hill 方法。假定席位数至少足够
 * 让每个州获得一个席位；如果情况不是这样，此函数
 * 报告 error()。随后函数返回一个 Map，其键为各州
 * 其值是分配给该州的席位数量。
 */
Map<std::string, int> apportion(const Map<std::string, int>& populations, int numSeats);
