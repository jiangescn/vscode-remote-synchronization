/*
 * 文件：hashcode.cpp
 * ------------------
 * 此文件实现在 hashcode.h 中声明的接口。
 *
 * @version 2019/04/16
 * - 修复 win64 中 void* 指针 hashCode 的错误
 * @version 2018/08/10
 * - 修复负哈希码和统一字符串哈希相关问题
 * @version 2017/10/21
 * - 为 short、unsigned 整数添加哈希码
 * @version 2015/07/05
 * - 使用全局哈希函数而非全局变量
 */

#include "hashcode.h"
#include <cstddef>       // 用于 size_t
#include <cstdint>       // 用于 uintptr_t
#include <cstring>       // 用于 strlen

static const int HASH_SEED = 5381;               // 第一个周期的起点
static const int HASH_MULTIPLIER = 33;           // 每个周期的乘数
static const int HASH_MASK = unsigned(-1) >> 1;  // 除符号位外全为 1

int hashSeed() {
    return HASH_SEED;
}

int hashMultiplier() {
    return HASH_MULTIPLIER;
}

int hashMask() {
    return HASH_MASK;
}

/* 
 * 实现说明：hashCode(int)
 * -----------------------------------
 * 整数的哈希码会屏蔽符号位，从而保证结果非负。
 */
int hashCode(int key) {
    return key & HASH_MASK;
}

/* 
 * 实现说明：hashCode（其他基本类型）
 * -----------------------------------------------------
 * 所有其他基本类型的哈希码都会转发给整数哈希码。
 * 这确保所有哈希码都得到正确的掩码处理。
 *
 * 感谢 Jeremy Barenholtz 指出这些函数的原始版本
 * 函数只是将参数转换为整数，可能导致负数
 * 结果。
 */
int hashCode(bool key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(char key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(unsigned int key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(long key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(unsigned long key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(short key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(unsigned short key) {
    return hashCode(static_cast<int>(key));
}

#ifdef _WIN64
int hashCode(uintptr_t key) {
    return hashCode(static_cast<unsigned long>(key));
}
#endif // _WIN64

/* 
 * 实现说明：hashCode(void*)
 * -----------------------------------------------------
 * 用于处理未被其他处理程序匹配的指针的兜底处理程序
 * 重载只是将指针值按数值处理。
 */
int hashCode(void* key) {
    return hashCode(reinterpret_cast<uintptr_t>(key));
}

/*
 * 实现说明：hashCode(string)、hashCode(double)
 * --------------------------------------------------------
 * 此函数接收一个字符串键，并用它派生哈希码，
 * 它是通过确定性方式与键关联的非负整数
 * 将键良好分布到整数空间的函数。
 * 这种通用方法称为线性同余法，它也用于
 * 用于随机数生成器。这里使用的具体算法是
 * 以发明者 Daniel J. Bernstein 的姓名首字母命名为 djb2，
 * 伊利诺伊大学芝加哥分校数学教授。
 */
int hashCode(const char* base, size_t numBytes) {
    unsigned hash = HASH_SEED;
    for (size_t i = 0; i < numBytes; i++) {
        hash = HASH_MULTIPLIER * hash + base[i];
    }
    return hashCode(hash);
} 

int hashCode(const char* str) {
    return hashCode(str, strlen(str));
}

int hashCode(const std::string& str) {
    return hashCode(str.data(), str.length());
}

int hashCode(double key) {
    return hashCode(reinterpret_cast<const char *>(&key), sizeof(double));
}

int hashCode(float key) {
    return hashCode(reinterpret_cast<const char *>(&key), sizeof(float));
}

int hashCode(long double key) {
    return hashCode(reinterpret_cast<const char *>(&key), sizeof(long double));
}
