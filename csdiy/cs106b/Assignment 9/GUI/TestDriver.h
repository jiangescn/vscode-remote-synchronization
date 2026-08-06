#pragma once

#include "vector.h"
#include <string>
#include <cstdint>
#include <functional>

namespace SimpleTest {
    /* 描述测试类别的类型。 */
    enum class TestType {
        STUDENT,
        PROVIDED,
        AUTOGRADER,
        MANUAL
    };

    /* 表示测试结果状态的类型。 */
    enum class TestResult {
        WAITING,   // 测试尚未运行
        RUNNING,   // 测试当前正在运行
        PASS,      // 测试通过
        FAIL,      // 测试因 EXPECT、EXPECT_ERROR 等断言失败
        LEAK,      // 测试通过，但存在内存泄漏
        EXCEPTION  // 测试因异常而失败
    };

    /* 表示单个测试的类型。 */
    struct Test {
        /* 基本信息。 */
        std::string name;
        TestType type;
        int lineNumber;

        /* 测试结果。 */
        TestResult result;
        std::string detailMessage;

        /* 仅供内部使用。 */
        std::function<void()> callback;
    };


    /* 表示一组测试的类型。 */
    struct TestGroup {
        std::string name;

        Vector<Test> tests;
        size_t numTests;
        size_t numPassed;
    };

    /* 表示可接收和报告内容的显示接口类型
     * 有关测试的信息。
     */
    using TestReporter = std::function<void(const Vector<TestGroup> &)>;

    /* 表示决定运行哪些测试的过滤器类型。输入为
     * 输入为测试的组名和测试本身；若该测试
     * 应当运行时为 true，否则为 false。
     */
    using TestFilter = std::function<bool(const std::string&, const Test&)>;

    /* 表示用于确定各组顺序的比较器类型
     * 应当显示。
     */
    using TestGroupComparator = std::function<bool(const std::string&, const std::string&)>;

    /* 运行所有符合给定过滤器的测试，并按以下给定顺序报告各组：
     * 比较器。
     *
     * 若未指定过滤器，则运行所有测试。
     *
     * 若未指定比较器，则按字母顺序排列测试组。
     */
    void run(TestReporter, TestFilter, TestGroupComparator);
    void run(TestReporter, TestFilter);
    void run(TestReporter, TestGroupComparator);
    void run(TestReporter);
}
