/*
 * 文件：hashcode.h
 * ----------------
 * 此文件声明各种常用数据类型的全局哈希函数。
 * 这些函数由 HashMap 和 HashSet 集合以及
 * 由希望作为 HashMap/Set 元素使用的其他集合调用。
 */

#ifndef _hashcode_h
#define _hashcode_h

#include <string>
#include <utility>

/*
 * 函数：hashCode
 * 用法：int hash = hashCode(key);
 * --------------------------------
 * 返回指定键的哈希码，它始终是一个
 * 非负整数。此函数已重载以支持
 * 所有基本类型以及 C++ <code>string</code> 类型。
 */
int hashCode(bool key);
int hashCode(char key);
int hashCode(double key);
int hashCode(float key);
int hashCode(long double key);
int hashCode(int key);
int hashCode(unsigned int key);
int hashCode(long key);
int hashCode(unsigned long key);
int hashCode(short key);
int hashCode(unsigned short key);
int hashCode(const char* str);
int hashCode(const std::string& str);
int hashCode(void* key);

/*
 * 用于帮助实现这些函数的常量
 * （用法示例请参阅 hashcode.h）
 */
int hashSeed();         // 第一个周期的起点
int hashMultiplier();   // 每个周期的乘数
int hashMask();         // 除符号位外全为 1

/*
 * 根据多个值的列表计算组合哈希码。
 * 各分量会按比例放大，以扩展值的范围
 * 并减少冲突。
 * 传入的每种值类型都必须具有合适的 hashCode() 函数。
 */
template <typename T1, typename T2, typename... Others>
int hashCode(T1&& first, T2&& second, Others&&... remaining) {
    int result = hashSeed();

    /* 计算最后 n - 1 个参数的哈希码。 */
    result += hashCode(std::forward<T2>(second), std::forward<Others>(remaining)...);

    /* 更新哈希值，将第一个元素的哈希计入其中。 */
    result *= hashMultiplier();
    result += hashCode(std::forward<T1>(first));

    /* 对得到的整数进行哈希，以屏蔽任何不需要的位。 */
    return hashCode(result);
}

#endif // _hashcode_h
