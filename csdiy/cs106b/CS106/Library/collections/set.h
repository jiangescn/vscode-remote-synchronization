/*
 * 文件：set.h
 * -----------
 * 此文件导出 <code>Set</code> 类，该类实现
 * 用于存储一组不同元素的集合。
 */

#ifndef _set_h
#define _set_h

#include <initializer_list>
#include <iostream>
#include <set>
#include <functional>
#include <type_traits>

#include "collections.h"
#include "map.h"

/* Set 的特征类型，它包装了底层 Map。 */
namespace stanfordcpplib {
    namespace collections {
        template <typename T> struct SetTraits {
            using ValueType = T;
            using MapType   = Map<T, bool>;
            static std::string name() {
                return "Set";
            }

            /* Set 类型确实允许你通过传入
             * 以及一个 std::function。
             */
            template <typename Function>
            static MapType construct(Function comparator) {
                static_assert(std::is_assignable<std::function<bool(const ValueType&, const ValueType&)>, Function>::value,
                              "Oops! Seems like you tried to initialize a Set incorrectly. Click here for details.");
                /*
                 * 同学你好！如果你看到此消息，说明你尝试了
                 * 错误地初始化 Set。例如，可能尝试编写
                 * 类似这样：
                 *
                 *     Set<int> mySet = 137; // 错误！
                 *
                 * 例如，这里试图将 int 赋值给 Set<int>。
                 *
                 * 或者你可能有一个类似如下的函数：
                 *
                 *     void myFunction(Set<int>& mySet);
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
                return MapType(comparator);
            }

            /* 也可以默认构造它。 */
            static MapType construct() {
                return {};
            }

            /* 但不能传入任何其他参数。 */
            template <typename... Args>
            static void construct(MapType &, Args&&...) {
                static_assert(Fail<Args...>::value, "Oops! Seems like you tried to initialize a Set incorrectly. Click here for details.");

                /*
                 * 同学你好！如果你看到此消息，说明你尝试了
                 * 错误地初始化 Set。例如，可能尝试编写
                 * 类似这样：
                 *
                 *     Set<int> mySet = 137; // 错误！
                 *
                 * 例如，这里试图将 int 赋值给 Set<int>。
                 *
                 * 或者你可能有一个类似如下的函数：
                 *
                 *     void myFunction(Set<int>& mySet);
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
                error("static_assert failed?");
            }
        };
    }
}

/*
 * 按排序顺序存储的一组元素。元素必须可比较
 * 使用 < 运算符，以便存储在此处。
 */
template <typename ValueType>
    using Set = stanfordcpplib::collections::GenericSet<stanfordcpplib::collections::SetTraits<ValueType>>;

#endif // _set_h
