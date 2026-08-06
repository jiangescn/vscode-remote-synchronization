#pragma once

#include <string>
#include <sstream>
#include <utility>
#include <cstdlib>
#include "strlib.h"

/**
 * 给定数字，返回用逗号分隔各位数字的版本。
 *
 * @param val 目标数字
 * @return 添加逗号后的数字。
 */
template <typename IntegerType> std::string addCommasTo(IntegerType val) {
    std::string asStr = std::to_string(val);
    const size_t length = asStr.length();

    std::string result;
    for (size_t i = 0; i < length; i++) {
        /* 从源字符串末尾向前遍历，以确定逗号应放在何处
         * 会简单得多。
         */
        result = asStr[length - 1 - i] + result;

        /* 若已添加三个字符但尚未
         * 即将用完所有数字。
         */
        if (i % 3 == 2 && i < length - 1) {
            result = ',' + result;
        }
    }
    return result;
}

/* 给定数量，返回该数量加上正确复数形式的字符串
 * 其实际内容的可读版本。
 */
template <typename ValueType>
std::string pluralize(const ValueType& value, const std::string& singular, const std::string& plural) {
    return addCommasTo(value) + " " + (value == 1? singular : plural);
}

/* 除非另有指定，否则假定通过添加 s 构成复数。 */
template <typename ValueType>
std::string pluralize(const ValueType& value, const std::string& singular) {
    return pluralize(value, singular, singular + "s");
}

/**
 * 给定字符串或字符，以类似 C++14 std::quoted 的方式为其加引号。
 *
 * @param input 要转义的文本。
 * @return 该字符串加引号后的版本。
 */
std::string quotedVersionOf(const std::string& input);
std::string quotedVersionOf(char input);

/**
 * 通用 printf 替换函数。给定一个包含如下形式替换位置的字符串
 * %s 和若干参数，将每个 %s 占位位置替换为相应的
 * 参数。
 *
 * 若参数数量错误，此函数会报告错误。
 *
 * @param text 含占位符的文本。
 * @param args 用于替换这些占位符的内容。
 */
std::string format(const std::string& pattern);

template <typename First, typename... Args>
std::string format(const std::string& pattern, First&& first, Args&&... args) {
    std::size_t toReplace = pattern.find("%s");
    if (toReplace == std::string::npos) {
        error("No pattern to replace?");
    }

    return    pattern.substr(0, toReplace)
            + std::to_string(std::forward<First>(first))
            + format(pattern.substr(toReplace + 2), args...);
}

template <typename... Args>
std::string format(const std::string& pattern, const std::string& first, Args&&... args) {
    std::size_t toReplace = pattern.find("%s");
    if (toReplace == std::string::npos) {
        error("No pattern to replace?");
    }

    return    pattern.substr(0, toReplace)
            + first
            + format(pattern.substr(toReplace + 2), args...);
}

template <typename... Args>
std::string format(const std::string& pattern, char first, Args&&... args) {
    std::size_t toReplace = pattern.find("%s");
    if (toReplace == std::string::npos) {
        error("No pattern to replace?");
    }

    return    pattern.substr(0, toReplace)
            + first
            + format(pattern.substr(toReplace + 2), args...);
}

/**
 * 使用指定连词连接一组字符串。例如：
 * 我们可能得到
 *
 *    A
 *    A 和 B
 *    A、B 和 C
 *
 * @param strings 要连接的字符串
 * @param conjunction 用于连接这些项目的连词
 * @return 使用指定连词连接各项所得的字符串
 */
template <typename Container>
std::string conjunctionJoin(const Container& container, const std::string& conjunction) {
    if (container.size() == 1) return *container.begin();
    if (container.size() == 2) return *container.begin() + " " + conjunction + " " + *next(container.begin());

    /* 构造字符串 x1、x2、x3、...、conjunction xn。 */
    std::string result;
    for (auto itr = container.begin(); itr != container.end();  ++itr) {
        if (itr != container.begin()) result += ", ";
        if (next(itr) == container.end()) result += conjunction + " ";
        result += *itr;
    }

    return result;
}
