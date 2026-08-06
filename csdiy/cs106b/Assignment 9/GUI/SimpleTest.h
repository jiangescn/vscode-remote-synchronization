#pragma once

/* 检查给定条件是否为 true。若是，则不执行任何操作；若条件
 * 为 false，则测试失败。例如：
 *
 *     EXPECT(vec.isEmpty());
 *     EXPECT(history.next() == "Dik-dik");
 */
#define EXPECT(condition) /* 某些无需关注的内部内容。 */

/* 检查给定表达式是否调用 error() 处理程序。若是，则不执行任何操作。
 * 否则测试失败。可用它确认某个表达式
 * 预期会触发异常的表达式确实触发异常。例如：
 *
 *     Vector<int> myVec;
 *     EXPECT_ERROR(myVec.get(0));    // 不执行任何操作，因为 myVec.get(0) 的确会触发 error()。
 *     EXPECT_ERROR(myVec.isEmpty()); // 测试失败，因为这里不会产生错误。
 */
#define EXPECT_ERROR(expression) /* 某些无需关注的内部内容。 */

/* 检查给定表达式是否不调用 error() 处理程序。若未调用 error()，
 * 被调用时不执行任何操作。若调用 error()，测试失败。
 *
 *     Vector<int> myVec;
 *     EXPECT_NO_ERROR(myVec.isEmpty()); // 不执行任何操作；没有产生错误。
 *     EXPECT_NO_ERROR(myVec.get(0));    // 测试失败；此操作会触发错误。
 */
#define EXPECT_NO_ERROR(expression) /* 某些无需关注的内部内容。 */

/* 检查两个对象是否相等。若相等，则不执行任何操作；否则测试失败
 * 并报告这两个值分别是什么。预期第一个值应当是
 * 学生的值，第二个值应当是正确答案。例如：
 *
 *     EXPECT_EQUAL(studentValue, referenceValue)
 */
#define EXPECT_EQUAL(student, reference) /* 某些无需关注的内部内容。 */

/* 检查两个对象是否不相等。若不相等，则不执行任何操作；否则测试失败
 * 并报告这两个值分别是什么。预期第一个值应当是
 * 学生的值，第二个值应当是正确答案。例如：
 *
 *     EXPECT_EQUAL(studentValue, referenceValue)
 */
#define EXPECT_NOT_EQUAL(student, reference) /* 某些无需关注的内部内容。 */

/* 检查两个对象是否满足给定关系。若满足，则不执行任何操作；否则
 * 测试失败并报告这两个值。预期第一个值
 * 第一个应当是学生的值，第二个应当是正确答案。
 */
#define EXPECT_LESS_THAN(student, reference)                /* 某些无需关注的内部内容。 */
#define EXPECT_GREATER_THAN(student, reference)             /* 某些无需关注的内部内容。 */
#define EXPECT_LESS_THAN_OR_EQUAL_TO(student, reference)    /* 某些无需关注的内部内容。 */
#define EXPECT_GREATER_THAN_OR_EQUAL_TO(student, reference) /* 某些无需关注的内部内容。 */

/* 使给定测试失败，并输出指定错误消息。例如：
 *
 *     SHOW_ERROR("出现了错误。");
 */
#define SHOW_ERROR(message);

/* 定义一个新测试用例。可以在测试用例内部编写任意需要的代码，
 * 不过在测试用例中通常会使用 EXPECT 和 EXPECT_ERROR，因为它们
 * 真正执行测试的内容。
 *
 * 定义新测试用例的语法为
 *
 *    STUDENT_TEST("测试用例说明") {
 *       ……任意编写你需要的代码……
 *    }
 */
#define STUDENT_TEST(name) /* 某些无需关注的内部内容。 */

/* 允许 SimpleTest 测试用例访问给定类的私有字段。这是
 * 使用 SimpleTest 检查类内部状态时很有用。
 *
 * 使用方法为
 *
 *     class MyClass {
 *     public:
 *        // ... //
 *
 *     private（私有）：
 *        ALLOW_TEST_ACCESS();
 *     }
 */
#define ALLOW_TEST_ACCESS() /* 某些无需关注的内部内容。 */











/******************************************************************************
 * 此处以下完全是实现细节。你不应当                         *
 * 无需引用或使用此处以下的任何内容。                         *
 ******************************************************************************/









#include "TextUtils.h"
#include "TestDriver.h"
#include "error.h"
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <cfloat>
#include <algorithm>

namespace SIMPLE_TEST_CASE {
    /* 模板函数，其各个特化就是实际测试用例。所有测试用例都
     * 作为此单一函数的特化，使 ALLOW_TEST_ACCESS 宏能够令
     * 使此模板的所有特化成为给定类型的友元，这是相应机制
     * 从而允许这些函数在类内部访问。
     *
     * 将其置于独立命名空间中，以防测试用例内部的名称查找
     * 意外引用 SimpleTest 的内部函数。（有一个学期确实发生过这种情况，而且它
     * 调试起来一团糟！）
     */
    template <const char* file, int line> void testCase();
}

namespace SimpleTest {
    namespace Internal {
        /* 表示顶层测试映射中键的类型。它是
         * 声明该测试的文件名。
         */
        using TestKey = std::string;

        /* 表示测试用例的类型。 */
        struct TestCase {
            std::string name;
            TestType type;
            int lineNumber;
            std::function<void()> callback;
        };

        /* 顶层测试映射。此对象定义为函数而非静态变量
         * 确保它能与静态初始化器正确配合。
         */
        std::map<TestKey, std::multimap<int, TestCase>>& rawTests();

        /* 表示测试用例失败的异常类型。 */
        class TestFailedException: public std::logic_error {
        public:
            TestFailedException(const std::string& message, std::size_t line);
        };

        /* 唯一用途是将测试用例放入测试组的对象。 */
        class TestCaseAdder {
        public:
            TestCaseAdder(const TestKey& key, int lineNumber, const std::string& name, TestType type, std::function<void()> test);
        };

        /**** 定义用于添加新测试用例的宏。 ****/

        #define JOIN(x, y) x ## y

        /* 通用测试添加器，由 STUDENT_TEST、PROVIDED_TEST 等接入。
         * 由于预处理器的工作方式，这里需要多层间接展开。
         * 第一层展开为所需结构的骨架。
         */
        #define ADD_TEST(name, type) DO_ADD_TEST(_testCase, _adder, name, type, __FILE__, __LINE__)

        /* 设置此层间接访问，是为了让 line 展开为 __LINE__，并让
         * 从那里映射到真实行号。这里仍不能进行词元拼接，因为
         * 更进一步的一层间接访问。
         *
         * 这里的基本思路如下：需要创建 TestCaseAdder 来安装
         * 静态初始化器运行时的测试函数。该初始化器会安装一个
         * testCase() 模板的特化。该模板以一个
         * 使用 const char*（当前文件）和 int（行号）保证唯一性
         * 跨翻译单元使用。但是，要将 const char* 作为模板参数传递，
         * 需要让它引用具有链接属性的对象，因此创建一个包含以下内容的静态数组
         * 先比较文件名。
         */
        #define DO_ADD_TEST(fn, adder, name, type, file, line)\
            static constexpr char JOIN(_testName, line)[] = file; \
            template <> void SIMPLE_TEST_CASE::testCase<JOIN(_testName, line), line>();\
            static SimpleTest::Internal::TestCaseAdder JOIN(adder, line)(file, line, name, type, SIMPLE_TEST_CASE::testCase<JOIN(_testName, line), line>);\
            template <> void SIMPLE_TEST_CASE::testCase<JOIN(_testName, line), line>()

        /***** 添加特定测试用例。 *****/
        #undef STUDENT_TEST
        #define STUDENT_TEST(name) ADD_TEST(name, SimpleTest::TestType::STUDENT)
        #define PROVIDED_TEST(name) ADD_TEST(name, SimpleTest::TestType::PROVIDED)
        #define AUTOGRADER_TEST(name) ADD_TEST(name, SimpleTest::TestType::AUTOGRADER)
        #define MANUAL_TEST(name) ADD_TEST(name, SimpleTest::TestType::MANUAL)

        /***** 用于实现测试原语的宏。 *****/
        [[ noreturn ]] void doFail(const std::string &message, std::size_t line);

        #undef EXPECT
        #define EXPECT(condition) SimpleTest::Internal::doExpect(condition, "EXPECT failed: " #condition " is not true.", __LINE__)
        void doExpect(bool condition, const std::string& expression, std::size_t line);

        #undef EXPECT_ERROR
        #define EXPECT_ERROR(condition) do {\
            try {\
                (void)(condition); \
                SimpleTest::Internal::doFail("EXPECT_ERROR: " #condition " did not call error().", __LINE__); \
            } catch (const ErrorException& ) { \
                /* 不执行任何操作。 */ \
            }\
        } while(0)

        #undef EXPECT_NO_ERROR
        #define EXPECT_NO_ERROR(condition) do {\
            try {\
                (void)(condition); \
            } catch (const ErrorException& e) {\
                SimpleTest::Internal::doFail("EXPECT_NO_ERROR: " #condition " called error(" + quotedVersionOf(e.what()) + ").", __LINE__); \
            }\
        } while(0)

        /* * * * EXPECT_EQUAL 的美化输出器 * * * */
        inline std::string debugFriendlyString(char c) {
            return quotedVersionOf(c);
        }

        /* 用引号包围字符串后输出。 */
        inline std::string debugFriendlyString(const std::string& s) {
            return quotedVersionOf(s);
        }
        inline std::string debugFriendlyString(const char* s) {
            return debugFriendlyString(std::string(s));
        }
        template <size_t N> std::string debugFriendlyString(char (&s)[N]) {
            return debugFriendlyString((const char *)s);
        }

        /* 将 bool 值按字符串输出。 */
        inline std::string debugFriendlyString(bool value) {
            return value? "true" : "false";
        }

        /* 以最高精度输出 float/double。 */
        inline std::string debugFriendlyString(float value) {
            std::ostringstream result;
            result << std::setprecision(FLT_DIG+1) << value << "f";
            return result.str();
        }

        inline std::string debugFriendlyString(double value) {
            std::ostringstream result;
            result << std::setprecision(DBL_DIG+1) << value << "d";
            return result.str();
        }

        /* 将 nullptr 按其本义输出。 */
        inline std::string debugFriendlyString(std::nullptr_t) {
            return "nullptr";
        }

        template <typename T>
        inline std::string debugFriendlyString(T* ptr) {
            /* 将空指针按其本义输出。 */
            if (ptr == nullptr) return "nullptr";

            std::ostringstream converter;
            converter << "Memory address " << std::hex << ptr;
            return converter.str();
        }

        /* 其他所有内容使用流插入运算符输出。 */
        template <typename T> std::string debugFriendlyString(const T& value) {
            std::ostringstream result;
            result << value;
            return result.str();
        }

        /* * * * 相等性比较 * * * */

        /* 实数的相等性比较采用模糊比较。 */
        inline bool areEqual(double lhs, double rhs) {
            double tolerance = std::max(std::abs(lhs), std::abs(rhs)) * DBL_EPSILON;
            return std::abs(lhs - rhs) <= tolerance;
        }

        template <typename T1, typename T2> bool areEqual(const T1& lhs, const T2& rhs) {
            return lhs == rhs;
        }

        template <typename T1, typename T2> bool areNotEqual(T1&& lhs, T2&& rhs) {
            return !areEqual(std::forward<T1>(lhs), std::forward<T2>(rhs));
        }

        template <typename T1, typename T2> bool isLessThan(T1&& lhs, T2&& rhs) {
            return lhs < rhs;
        }

        template <typename T1, typename T2> bool isGreaterThan(T1&& lhs, T2&& rhs) {
            return lhs > rhs;
        }

        template <typename T1, typename T2> bool isLessThanOrEqualTo(T1&& lhs, T2&& rhs) {
            return lhs <= rhs;
        }

        template <typename T1, typename T2> bool isGreaterThanOrEqualTo(T1&& lhs, T2&& rhs) {
            return lhs >= rhs;
        }

        /* 截断过长字符串 */
        inline std::string abbreviate(const std::string& s, size_t maxLen = 300) {
            return s.length() < maxLen ? s : s.substr(0, maxLen) + " ...";
        }

        #undef EXPECT_EQUAL
        #define EXPECT_EQUAL(student, ...) DO_COMPOUND_EXPECT("EXPECT_EQUAL", "!=", SimpleTest::Internal::areEqual, student, __VA_ARGS__)

        #undef EXPECT_NOT_EQUAL
        #define EXPECT_NOT_EQUAL(student, ...) DO_COMPOUND_EXPECT("EXPECT_NOT_EQUAL", "==", SimpleTest::Internal::areNotEqual, student, __VA_ARGS__)

        #undef EXPECT_LESS_THAN
        #define EXPECT_LESS_THAN(student, ...) DO_COMPOUND_EXPECT("EXPECT_LESS_THAN", ">=", SimpleTest::Internal::isLessThan, student, __VA_ARGS__)

        #undef EXPECT_LESS_THAN_OR_EQUAL_TO
        #define EXPECT_LESS_THAN_OR_EQUAL_TO(student, ...) DO_COMPOUND_EXPECT("EXPECT_LESS_THAN_OR_EQUAL_TO", ">", SimpleTest::Internal::isLessThanOrEqualTo, student, __VA_ARGS__)

        #undef EXPECT_GREATER_THAN
        #define EXPECT_GREATER_THAN(student, ...) DO_COMPOUND_EXPECT("EXPECT_GREATER_THAN", "<=", SimpleTest::Internal::isGreaterThan, student, __VA_ARGS__)

        #undef EXPECT_GREATER_THAN_OR_EQUAL_TO
        #define EXPECT_GREATER_THAN_OR_EQUAL_TO(student, ...) DO_COMPOUND_EXPECT("EXPECT_GREATER_THAN_OR_EQUAL_TO", "<", SimpleTest::Internal::isGreaterThanOrEqualTo, student, __VA_ARGS__)

        #define DO_COMPOUND_EXPECT(name, failSymbol, comparator, student, ...)                      \
            do {                                                                                    \
               auto _studentAnswer = (student);                                                     \
               decltype(_studentAnswer) _referenceAnswer = __VA_ARGS__;                             \
                                                                                                    \
               if (!comparator(_studentAnswer, _referenceAnswer)) {                                 \
                   std::stringstream _expression;                                                   \
                   _expression << std::boolalpha << name " failed: "                                \
                               << #student << " " failSymbol " " << #__VA_ARGS__ "\n"               \
                               << "                " #student   " = "                               \
                               << SimpleTest::Internal::abbreviate(SimpleTest::Internal::debugFriendlyString(_studentAnswer)) << '\n'\
                               << "                " #__VA_ARGS__ " = "                             \
                               << SimpleTest::Internal::abbreviate(SimpleTest::Internal::debugFriendlyString(_referenceAnswer));\
                   SHOW_ERROR(_expression.str()); \
               } \
            } while (0)

        #undef SHOW_ERROR
        #define SHOW_ERROR(message) SimpleTest::Internal::showError(message, __LINE__)
        [[ noreturn ]] void showError(const std::string& message, std::size_t line);

        #undef ALLOW_TEST_ACCESS
        #define ALLOW_TEST_ACCESS() template <const char*, int> friend void SIMPLE_TEST_CASE::testCase()
    }
}
