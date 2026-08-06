/*
 * 文件：hashset.h
 * ---------------
 * 此文件导出 <code>HashSet</code> 类，该类
 * 实现用于存储值集合的高效抽象。
 */

#ifndef _hashset_h
#define _hashset_h

#include <initializer_list>
#include <iostream>

#include "collections.h"
#include "hashmap.h"

/* HashSet 的特征类型，它包装了底层 HashMap。 */
namespace stanfordcpplib {
    namespace collections {
        template <typename T> struct HashSetTraits {
            using ValueType = T;
            using MapType   = HashMap<T, bool>;
            static std::string name() {
                return "HashSet";
            }
            /* 可以默认构造 HashSet。 */
            static MapType construct() {
                return {};
            }

            /* 但不能传入任何其他参数。 */
            template <typename... Args>
            static void construct(Args&&...) {
                static_assert(Fail<Args...>::value, "Oops! Seems like you tried to initialize a HashSet incorrectly. Click here for details.");

                /*
                 * 同学你好！如果你看到此消息，说明你尝试了
                 * 错误地初始化 HashSet。例如，你可能尝试过
                 * 写入类似以下内容：
                 *
                 *     HashSet<int> mySet = 137; // 错误！
                 *
                 * 这里，例如，你试图把一个 int 赋给 HashSet<int>。
                 *
                 * 或者你可能有一个类似如下的函数：
                 *
                 *     void myFunction(HashSet<int>& mySet);
                 *
                 * 而你的调用方式是
                 *
                 *     myFunction(someSet + someOtherSet); // 错误用法！
                 *     myFunction({ });                    // 错误用法！
                 *
                 * 在这些情况下，你试图向一个接受以下参数的函数传入值：
                 * 通过（非 const）引用接收参数。C++ 不允许这样做。
                 *
                 * 要查看实际错误来源，请查看错误消息列表
                 * 在 Qt Creator 中。你应当看到一行写着“required from here”，它
                 * 指向代码中的某处。那才是导致问题的实际代码行
                 * 问题所在，因此双击该错误消息，查看它将你带到哪里
                 * 你。现在知道该去哪里查看了！
                 *
                 * 希望这能有所帮助！
                 */
                error("static_assert succeeded?");
            }
        };
    }
}

/*
 * 以任意顺序存储的一组元素。只有满足以下条件的元素才能存储在此处：
 * 如果它们支持某个函数
 *
 *     int hashCode(ValueType);
 *
 * 返回非负整数，并使用 == 进行相等比较。
 */
template <typename ValueType>
    using HashSet = stanfordcpplib::collections::GenericSet<stanfordcpplib::collections::HashSetTraits<ValueType>>;

#endif // _hashset_h
