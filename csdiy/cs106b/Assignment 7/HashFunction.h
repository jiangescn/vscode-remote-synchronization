#ifndef Hashes_Included
#define Hashes_Included

#include <functional>
#include "hashcode.h"
#include "error.h"
#include "collections.h"

template <typename T> class HashFunction {
public:
    /**
     * 为给定槽位数构造新的 HashFunction。每个哈希
     * 以此方式构造的函数将随机初始化。
     *
     * 第二个参数是随机种子。设置此值
     * 如果希望哈希函数始终表现一致，则很有用
     * 在程序的不同运行之间。
     */
    explicit HashFunction(int numSlots, int randomSeed = 0);

    /**
     * 构造新的 HashFunction。此 HashFunction 无法使用，因为
     * 它不会使用桶数量初始化，而尝试
     * 使用它会导致运行时错误。
     *
     * 不应直接使用此构造函数；它仅用于
     * 可以声明 HashFunction 类型的变量并对其初始化
     * 稍后。
     */
    HashFunction();

    /**
     * 构造专门使用底层原始数据的哈希函数
     * 使用其哈希码作为哈希函数。如果你想确保
     * 测试时为哈希函数提供可预测的值。
     */
    static HashFunction wrap(int numSlots,
                             std::function<int (const T &)> hashFn);

    /**
     * 返回此哈希函数设计用于操作的槽位数量
     * 结束。
     */
    int numSlots() const;

    /**
     * 将哈希函数应用于指定参数。其语法为
     * 使用此函数是
     *
     *     hashFn(argument)
     *
     * 也就是说，可将 HashFunction 类型的变量当作它是
     * 一个真正的函数，而不是某种类型的变量。
     */
    int operator() (const T& argument) const;

private:
    std::function<int(const T&)> callback;
    int mNumSlots;

    static_assert(stanfordcpplib::collections::IsHashable<T>::value,
                  "Oops! You've tried to make a HashFunction for a type that isn't hashable. "
                  "Double-click this error message for more details.");

    /*
     * CS106 的同学你好！如果编译错误将你指向此行代码，
     * 这可能意味着你尝试使用自定义结构体或类创建 HashFunction<T>
     * 类类型。
     *
     * 要为类型 T 提供 HashFunction<T>，类型 T 需要有 hashCode
     * 已定义函数，并且能够使用 == 运算符比较。如果你被
     * 如果被引导到这里，说明这两个条件之一未满足。
     *
     * 有两种修复方式。第一种是直接不使用自定义
     * 将该类型与 HashFunction<T> 配合使用。这可能是最简单的选择。
     *
     * 第二种修复方式是显式定义 hashCode() 和 operator== 函数
     * 为你的类型定义。首先按如下方式定义 hashCode：
     *
     *     int hashCode(const YourCustomType& obj) {
     *         return stanfordcpplib::collections::hashCode(obj.data1, obj.data2, ..., obj.dataN);
     *     }
     *
     * 其中 data1、data2、...、dataN 是该类型的数据成员。例如，如果你有
     * 自定义类型
     *
     *     struct MyType {
     *         int myInt;
     *         string myString;
     *     };
     *
     * 你需要定义函数
     *
     *     int hashCode(const MyType& obj) {
     *         return stanfordcpplib::collections::hashCode(obj.myInt, obj.myString);
     *     }
     *
     * 其次，按如下方式定义 operator==：
     *
     *     bool operator== (const YourCustomType& lhs, const YourCustomType& rhs) {
     *         return lhs.data1 == rhs.data1 &&
     *                lhs.data2 == rhs.data2 &&
     *                         ...
     *                lhs.dataN == rhs.dataN;
     *     }
     *
     * 使用上面的 MyType 示例，我们会编写
     *
     *     bool operator== (const MyType& lhs, const MyType& rhs) {
     *         return lhs.myInt == rhs.myInt && lhs.myString == rhs.myString;
     *     }
     *
     * 希望这能有所帮助！
     */
};

namespace hashfunction_detail {
    std::function<int(int)> tabulationHashFunction(int seed);
}

/* * * * * 此处以下为实现部分 * * * * */
template <typename T>
HashFunction<T>::HashFunction(int numSlots, int seed) {
    if (numSlots <= 0) {
        error("HashFunction<T>::wrap(): numSlots must be positive.");
    }

    auto scrambler = hashfunction_detail::tabulationHashFunction(seed);
    mNumSlots = numSlots;
    callback = [scrambler, numSlots](const T& key) {
        return (scrambler(hashCode(key)) & 0x7FFFFFF) % numSlots;
    };
}

template <typename T>
HashFunction<T> HashFunction<T>::wrap(int numSlots,
                                      std::function<int (const T&)> hashFn) {
    if (numSlots <= 0) {
        error("HashFunction<T>::wrap(): numSlots must be positive.");
    }

    HashFunction result;
    result.callback = [hashFn, numSlots] (const T& key) {
        return (0x7FFFFFFF & hashFn(key)) % numSlots;
    };
    result.mNumSlots = numSlots;

    return result;
}

template <typename T> int HashFunction<T>::numSlots() const {
    return mNumSlots;
}

/* 默认构造函数设置一个始终报告错误的哈希函数。 */
template <typename T> HashFunction<T>::HashFunction() {
    callback = [](const T&) -> int {
        error("Attempted to use an uninitialized HashFunction object.");
    };
    mNumSlots = 0;
}

/* 调用运算符会转发给回调。 */
template <typename T> int HashFunction<T>::operator()(const T& arg) const {
    return callback(arg);
}

#endif
