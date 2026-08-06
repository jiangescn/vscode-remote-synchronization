#ifndef WhatAreYouDoing_Included
#define WhatAreYouDoing_Included

#include "vector.h"
#include "set.h"
#include <string>

/* 此函数已提供给你，无需实现。它接收
 * 一个字符串，然后返回表示该字符串不同部分的 Vector<string>
 * 按照它们出现的顺序。
 */
Vector<std::string> tokenize(const std::string& sentence);

/* 你需要实现此函数。详情请参阅作业讲义。 */
Set<std::string> allEmphasesOf(const std::string& sentence);

#endif
