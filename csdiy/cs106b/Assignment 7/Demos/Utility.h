#ifndef Utility_Included
#define Utility_Included

#include "HashFunction.h"
#include <ostream>

/**
 * 宏：DISALLOW_COPYING_OF(Type)
 *
 * 禁止指定类型的复制/赋值。
 */
#define DISALLOW_COPYING_OF(Type)                                           \
    Type(const Type &) = delete;                                            \
    Type(Type &&) = delete;                                                 \
    void operator= (Type) = delete

/**
 * 宏：MAKE_PRINTERS_FOR(Type)
 *
 * 导出使给定函数可打印到 cout 的函数。
 *
 * 若正在定义自己的自定义类型，并在尝试以下操作时收到错误：
 * 使用 MAKE_PRINTERS_FOR，无需担心！打开文件 Demos/Printers.cpp。在那里，
 * 你会找到输出 Slot、SlotType 等的函数。复制/粘贴代码
 * 并进行适当编辑，以支持你自己的自定义类型。
 */
#define MAKE_PRINTERS_FOR(Type) \
    friend std::ostream& operator<< (std::ostream&, Type)

/**
 * 宏：MAKE_COMPARATORS_FOR(Type)
 *
 * 导出使给定类型可用 == 和 != 比较的函数。
 *
 * 若正在定义自己的自定义类型，并在尝试以下操作时收到错误：
 * 使用 MAKE_COMPARATORS_FOR，无需担心！打开文件 Demos/Printers.cpp。在那里，
 * 你会找到比较 Slot 等的函数。复制/粘贴代码
 * 并进行适当编辑，以支持你自己的自定义类型。
 */
#define MAKE_COMPARATORS_FOR(Type) \
    friend bool operator== (const Type& lhs, const Type& rhs); \
    friend bool operator!= (const Type& lhs, const Type& rhs) { return !(lhs == rhs); } \
    static_assert(true, "Just so we need a semicolon.")

/* 哈希函数工具。 */
namespace Hash {
    HashFunction<std::string> random(int numSlots);
    HashFunction<std::string> consistentRandom(int numSlots);    // 随机选择，但在不同运行间保持一致
    HashFunction<std::string> zero(int numSlots);                // 始终为零
    HashFunction<std::string> constant(int numSlots, int value); // 始终为常量

    /* 假定键为整数。如果不是，返回的哈希值将保持一致但为任意值。 */
    HashFunction<std::string> identity(int numSlots);
}

#endif
