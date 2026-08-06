#ifndef MemoryDiagnostics_Included
#define MemoryDiagnostics_Included

/* 一组实用函数，用于跟踪以下对象的分配和释放：
 * 各种节点类型。在实际 C++ 代码中通常不会这样做，而会
 * 而应依赖优秀的外部工具，例如 Valgrind；如果继续学习，你会见到它
 * 继续学习 CS107！
 */

#include <string>

/* 宏：TRACK_ALLOCATIONS_OF(type)
 * ------------------------------------------------------------------------------
 * 将指定节点类型接入内存诊断系统。使用方法是：
 * 在正在定义的 struct 或 class 内部，插入如下所示的一行：
 *
 *     struct MyType {
 *         ...
 *         TRACK_ALLOCATIONS_OF(MyType);
 *     };
 */
#define TRACK_ALLOCATIONS_OF(type) /* 无需关注的内容 */











/* * * * * 此处以下为实现部分 * * * * */










#include <typeinfo>
#include <cstddef>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <map>
#include <vector>

/* 内存诊断辅助函数。通常不需要使用其中任何函数
 * 代码中的函数。
 */
namespace MemoryDiagnostics {
    void recordNew(const std::type_info& type);
    void recordDelete(const std::type_info& type);

    template <typename T> struct MemorySentinel {
        static int initializer;
    };

    /* 将指定类型安装到主类型表中。返回一个整数值
     * 完全无关紧要。
     */
    int registerSentinel(const std::type_info& type);

    /* 用于分配和释放内存的挂钩。可用它自定义内存系统如何
     * 分配和释放该类型的对象。
     */
    template <typename T> struct Allocator {
        static void* scalarAlloc(std::size_t bytes) {
            return ::operator new(bytes);
        }

        static void* vectorAlloc(std::size_t bytes) {
            return ::operator new[](bytes);
        }

        static void scalarFree(void* memory) {
            ::operator delete(memory);
        }

        static void vectorFree(void* memory) {
            ::operator delete[](memory);
        }
    };

    /* 清除所有分配记录，相当于重置内存泄漏计数。 */
    void clear();

    /* 返回包含内存泄漏/错误的所有类型的映射。键是类型
     * 键为名称，值为分配记录。
     */
    std::map<std::string, int> typesWithErrors();
}

template <typename T>
int MemoryDiagnostics::MemorySentinel<T>::initializer = registerSentinel(typeid(T));

/* TRACK_ALLOCATIONS 的实现会引入 operator new/delete 挂钩，并调用
 * 接入内存诊断系统。
 *
 * 若按 F2 或 fn+F2 后被重定向到这里，则你已被送到
 * TRACK_ALLOCATIONS_OF 的实现而非定义。向上滚动查看
 * 向上查看本文件中的更多信息。
 */
#undef TRACK_ALLOCATIONS_OF
#define TRACK_ALLOCATIONS_OF(Type)                                           \
    void* operator new(std::size_t bytes) {                                  \
        (void) ::MemoryDiagnostics::MemorySentinel<Type>::initializer;       \
        ::MemoryDiagnostics::recordNew(typeid(Type));                        \
        return MemoryDiagnostics::Allocator<Type>::scalarAlloc(bytes);       \
    }                                                                        \
    void* operator new[](std::size_t bytes) {                                \
        ::MemoryDiagnostics::recordNew(typeid(Type));                        \
        return MemoryDiagnostics::Allocator<Type>::vectorAlloc(bytes);       \
    }                                                                        \
    void operator delete(void* ptr) {                                        \
        ::MemoryDiagnostics::recordDelete(typeid(Type));                     \
        return MemoryDiagnostics::Allocator<Type>::scalarFree(ptr);          \
    }                                                                        \
    void operator delete(void* ptr, std::size_t) {                           \
        ::MemoryDiagnostics::recordDelete(typeid(Type));                     \
        return MemoryDiagnostics::Allocator<Type>::scalarFree(ptr);          \
    }                                                                        \
    void operator delete[](void* ptr) {                                      \
        ::MemoryDiagnostics::recordDelete(typeid(Type));                     \
        return MemoryDiagnostics::Allocator<Type>::vectorFree(ptr);          \
    }                                                                        \
    void operator delete[](void* ptr, std::size_t) {                         \
        ::MemoryDiagnostics::recordDelete(typeid(Type));                     \
        return MemoryDiagnostics::Allocator<Type>::vectorFree(ptr);          \
    }                                                                        \
    static_assert(true, "Just so we need a semicolon.")

#endif
