#include "TestDriver.h"
#include "SimpleTest.h"
#include "MemoryDiagnostics.h"
using namespace std;

namespace {
    /* 给定文件路径，返回不含路径部分的文件名。 */
    string tailOf(const string& path) {
        /* 查找文件名中最后一个 / 或 \。 */
        size_t index = path.find_last_of("\\/");
        return index == string::npos? path : path.substr(index + 1);
    }

    /* 运行单个测试。 */
    void runSingleTest(SimpleTest::Test& test, SimpleTest::TestGroup& group) {
        try {
            /* 重置内存计数器，避免测试之间遗留状态。 */
            MemoryDiagnostics::clear();

            /* 运行测试。 */
            test.callback();

            /* 检查是否存在内存泄漏。 */
            auto errors = MemoryDiagnostics::typesWithErrors();
            if (errors.empty()) {
                test.result = SimpleTest::TestResult::PASS;
                group.numPassed++;
            } else {
                /* 存在内存泄漏。 */
                test.result = SimpleTest::TestResult::LEAK;

                ostringstream out;
                out << "    Test failed due to memory errors with these types:" << endl;
                for (const auto& entry: errors) {
                    string type = entry.first;
                    int    delta = entry.second;

                    if (delta > 0) {
                        out << "            " << type << ": Leaked " << pluralize(delta, "object") << "." << endl;
                    } else {
                        out << "            " << type << ": Deallocated " << pluralize(-delta, "more object") << " than allocated." << endl;
                    }
                }

                test.detailMessage = out.str();
            }
        } catch (const SimpleTest::Internal::TestFailedException& e) {
            test.result = SimpleTest::TestResult::FAIL;
            ostringstream out;
            out << "    " << e.what() << endl;
            test.detailMessage = out.str();
        } catch (const ErrorException& e) {
            test.result = SimpleTest::TestResult::EXCEPTION;
            ostringstream out;
            out << "    Test failed due to the program triggering an ErrorException." << endl;
            out << endl;
            out << "    This means that the test did not fail because of a call" << endl;
            out << "    to EXPECT() or EXPECT_ERROR() failing, but rather because" << endl;
            out << "    some code explicitly called the error() function." << endl;
            out << endl;
            out << "    Error: " << e.getMessage() << endl;
            test.detailMessage = out.str();
        } catch (const exception& e) {
            test.result = SimpleTest::TestResult::EXCEPTION;
            ostringstream out;
            out << "    Test failed due to the program triggering an exception." << endl;
            out << endl;
            out << "    This means that the test did not fail because of a call" << endl;
            out << "    to EXPECT() or an EXPECT_ERROR() failing, but rather because" << endl;
            out << "    some code - probably an internal C++ library - triggered" << endl;
            out << "    an error." << endl;
            out << endl;
            out << "    Error: " << e.what() << endl;
            test.detailMessage = out.str();
        } catch (...) {
            test.result = SimpleTest::TestResult::EXCEPTION;
            ostringstream out;
            out << "    Test failed due to the program triggering an unknown type" << endl;
            out << "    of exception. " << endl;
            out << endl;
            out << "    This means that the test did not fail because of a call" << endl;
            out << "    to EXPECT() or an EXPECT_ERROR() failing, but rather because" << endl;
            out << "    some code triggered an error whose format we couldn't" << endl;
            out << "    recognize." << endl;
            out << endl;
            test.detailMessage = out.str();
        }
    }

    /* 根据测试系统的原始数据生成可视化 TestGroup。 */
    SimpleTest::TestGroup testsToGroup(const pair<const SimpleTest::Internal::TestKey, multimap<int, SimpleTest::Internal::TestCase>>& entry,
                                       SimpleTest::TestFilter filter) {
        /* 将原始测试组转换为规范的 TestGroup 对象。 */
        SimpleTest::TestGroup result;

        /* 测试组名称是文件完整路径。这里只需要末尾文件名。 */
        result.name = tailOf(entry.first);
        result.numPassed = 0;
        result.numTests = entry.second.size();

        for (const auto& rawTest: entry.second) {
            SimpleTest::Test test;
            test.name = rawTest.second.name;
            test.type = rawTest.second.type;
            test.lineNumber = rawTest.second.lineNumber;
            test.result = SimpleTest::TestResult::WAITING; // 它尚未运行
            test.callback = rawTest.second.callback;

            /* 若不应运行该测试，则将其排除。 */
            if (filter(result.name, test)) {
                result.tests += test;
            }
        }

        return result;
    }

    /* 默认过滤器和比较器。 */
    SimpleTest::TestFilter defaultFilter() {
        return [](const string&, const SimpleTest::Test&) {
            return true;
        };
    }
    SimpleTest::TestGroupComparator defaultComparator() {
        return std::less<std::string>();
    }
}

namespace SimpleTest{
    /* 运行指定测试，并随执行进度更新显示。 */
    void run(TestReporter reporter, TestFilter filter, TestGroupComparator comparator) {
        /* 将原始测试转换为规范的测试组列表。 */
        Vector<TestGroup> displayedTests;
        for (const auto& entry: Internal::rawTests()) {
            auto tests = testsToGroup(entry, filter);

            /* 边界情况：文件中没有测试？不要显示它。 */
            if (!tests.tests.isEmpty()) {
                displayedTests += tests;
            }
        }

        /* 对各组排序。 */
        sort(displayedTests.begin(), displayedTests.end(), [&](const TestGroup& lhs, const TestGroup& rhs) {
            return comparator(lhs.name, rhs.name);
        });

        /* 显示所有内容，以便提供一些基本数据。 */
        reporter(displayedTests);

        /* 现在运行测试。 */
        for (auto& group: displayedTests) {
            for (auto& test: group.tests) {
                /* 明确显示当前正在运行测试。 */
                test.result = TestResult::RUNNING;
                reporter(displayedTests);

                runSingleTest(test, group);
                reporter(displayedTests);
            }
        }
    }

    void run(TestReporter reporter, TestFilter filter) {
        run(reporter, filter, defaultComparator());
    }
    void run(TestReporter reporter, TestGroupComparator comparator) {
        run(reporter, defaultFilter(), comparator);
    }
    void run(TestReporter reporter) {
        run(reporter, defaultFilter(), defaultComparator());
    }
}
