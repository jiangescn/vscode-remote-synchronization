#include "TestingGUI.h"
#include "ProblemHandler.h"
#include "Core.h"
#include "TemporaryComponent.h"
#include "GColorConsole.h"
#include "GUIMain.h"
#include "TextUtils.h"
#include "MemoryDiagnostics.h"
#include "SimpleTest.h"
#include "TestDriver.h"
#include "error.h"
#include "simpio.h"
#include "gthread.h"
using namespace std;

namespace {
    /* 测试类型 --> 字符串 */
    string to_string(SimpleTest::TestType type) {
        switch (type) {
            case SimpleTest::TestType::STUDENT: return "Student Test";
            case SimpleTest::TestType::PROVIDED: return "Provided Test";
            case SimpleTest::TestType::AUTOGRADER: return "Autograder Test";
            case SimpleTest::TestType::MANUAL: return "Manual Test";
            default: error("Unknown test type.");
        }
    }

    /* 测试 --> 显示名称 */
    string displayNameOf(const SimpleTest::Test& test) {
        return to_string(test.type) + ": " + test.name;
    }

    /* 给定文件路径，返回不含路径部分的文件名。 */
    string tailOf(const string& path) {
        /* 查找文件名中最后一个 / 或 \。 */
        size_t index = path.find_last_of("\\/");
        return index == string::npos ? path : path.substr(index + 1);
    }

    /* 允许所有内容。 */
    SimpleTest::TestFilter filter() {
        return [](const string&, const SimpleTest::Test&) {
            return true;
        };
    }

    SimpleTest::TestGroupComparator comparator() {
        /* 按文件索引对文件排序。 */
        auto fileList = MiniGUI::Config::testOrder();

        return [=](const string& lhs, const string& rhs) {
            /* 比较两个字符串的索引。 */
            return find(fileList.begin(), fileList.end(), lhs) <
                   find(fileList.begin(), fileList.end(), rhs);
        };
    }

    /* 获取所有包含测试的文件，即所有测试组 */
    Vector<string> getTestGroups() {
        Vector<string> keys;
        auto& tests = SimpleTest::Internal::rawTests();

        for (const auto& entry: tests) {
            keys += tailOf(entry.first);
        }

        /* 按规范顺序排序。 */
        auto fileList = MiniGUI::Config::testOrder();
        sort(keys.begin(), keys.end(), [&](const string& lhs, const string& rhs) {
            return find(fileList.begin(), fileList.end(), lhs) <
                   find(fileList.begin(), fileList.end(), rhs);
        });

        return keys;
    }

    /* 通过控制台提示用户选择要运行的测试组（或全部运行）。-1 表示全部。 */
    int getTestSelection(const Vector<string>& groups) {
        cout << "Select which test to run!" << endl;

        cout << "0 All Tests" << endl;
        for (int i = 0; i < groups.size(); i++) {
            cout << i + 1 << " " << groups[i] << endl;
        }

        return getInteger("Select which test to run: ") - 1;
    }

    /* 根据测试组 Vector 返回合适的 TestFilter。 */
    SimpleTest::TestFilter filterToSelection(const Vector<string>& groups, int selection) {
        if (selection < 0) {
            return filter();
        }

        string selectedGroup = groups[selection];
        auto defaultFilter = filter();

        return [selectedGroup, defaultFilter](const string& group, const SimpleTest::Test& test) {
            return group == selectedGroup && defaultFilter(group, test);
        };
    }

    /* 显示给定测试组的所有结果。 */
    void displayResults(GColorConsole& console, const Vector<SimpleTest::TestGroup>& testGroups) {
        /* 在主 GUI 线程上执行，以便始终能看到当前进度。 */
        GThread::runOnQtGuiThread([&] {
            console.clearDisplay();

            for (const auto& group: testGroups) {
                /* 绘制标题 */
                console.doWithStyle("#000080", GColorConsole::BOLD, [&] {
                    console << "==== Tests for " << group.name << " ====" << '\n';
                });

                /* 绘制每个测试 */
                for (const auto& test: group.tests) {
                    if (test.result == SimpleTest::TestResult::WAITING) {
                        console.doWithStyle("#A0A0A0", GColorConsole::ITALIC, [&] {
                            console << "         " << displayNameOf(test) << '\n';
                        });
                    } else if (test.result == SimpleTest::TestResult::RUNNING) {
                        console.doWithStyle("#0000FF", GColorConsole::ITALIC, [&] {
                            console << "running: " << displayNameOf(test) << '\n';
                        });
                    } else if (test.result == SimpleTest::TestResult::PASS) {
                        console.doWithStyle("#404040", GColorConsole::ITALIC, [&] {
                            console << "   pass: " << displayNameOf(test) << '\n';
                        });
                    } else if (test.result == SimpleTest::TestResult::FAIL) {
                        console.doWithStyle("#800000", GColorConsole::BOLD, [&] {
                            console << "   FAIL: " << displayNameOf(test) << '\n';
                            console << "    " << test.detailMessage << '\n';
                        });
                    } else if (test.result == SimpleTest::TestResult::EXCEPTION) {
                        console.doWithStyle("#FF0000", GColorConsole::BOLD, [&] {
                            console << "   FAIL: " << displayNameOf(test) << '\n';
                            console << "    " << test.detailMessage << '\n';
                        });
                    } else if (test.result == SimpleTest::TestResult::LEAK) {
                        console.doWithStyle("#FF0000", GColorConsole::BOLD, [&] {
                            console << "   FAIL: " << displayNameOf(test) << '\n';
                            console << "    " << "Test defined on line " << test.lineNumber << "." << '\n';
                            console << "    " << test.detailMessage << '\n';
                        });
                    } else {
                        error("Internal error: Unknown test result. Contact the course staff.");
                    }
                }

                /* 绘制整体结果。 */
                if (group.numPassed == group.numTests && group.numTests > 0) {
                    console.doWithStyle("#0000FF", GColorConsole::ITALIC, [&] {
                        console << "All tests in this section passed!" << '\n';
                        console << '\n';
                        console << '\n';
                    });
                } else {
                    console.doWithStyle("#400000", GColorConsole::BOLD, [&] {
                        console << "Summary: " << group.numPassed << " / " << group.numTests
                             << " test" << (group.numTests == 1? "" : "s") << " passed." << '\n';
                        console << '\n';
                        console << '\n';
                    });
                }
            }

            console.flush();
        });
    }

    class TestingGUI: public ProblemHandler {
    public:
        TestingGUI(GWindow& window);

        void settingUp() override;

    private:
        Temporary<GColorConsole> console;
    };

    /* 初始化界面框架。 */
    TestingGUI::TestingGUI(GWindow& window) : ProblemHandler(window) {
        console = Temporary<GColorConsole>(new GColorConsole(), window, "CENTER");
        setDemoOptionsEnabled(false);
    }

    /* 实际运行所有测试。 */
    void TestingGUI::settingUp() {
        SimpleTest::TestReporter reporter = [this](const Vector<SimpleTest::TestGroup>& groups) {
            displayResults(*console, groups);
        };

        SimpleTest::run(reporter, filter(), comparator());

        setDemoOptionsEnabled(true);
    }
}

GRAPHICS_HANDLER("Run Tests", GWindow& window) {
    return make_shared<TestingGUI>(window);
}

namespace {
    /* 将流从正常目标重定向到其他位置的类型
     * 移动到另一个位置。例如，可以用它来
     * 重定向 stdout 或 stderr。
     */
    class OstreamDiverter {
    public:
        explicit OstreamDiverter(ostream& out) : original(out), diverted(out.rdbuf(replacement.rdbuf())) {

        }

        ~OstreamDiverter() {
            original.rdbuf(diverted.rdbuf());
        }

        /* 用于写入原始源的访问权限。 */
        ostream& out() {
            return diverted;
        }

        /* 已写入的内容。 */
        std::string written() {
            return replacement.str();
        }

    private:
        ostream& original;
        ostringstream replacement;
        ostream  diverted;
    };

    /* 在控制台模式下运行所有测试。 */
    void runConsoleTests(SimpleTest::TestFilter filter, bool divertStreams) {
        Vector<SimpleTest::TestGroup> lastGroups;

        {
            /* 若处于自动评分模式，则重定向该流。 */
            unique_ptr<OstreamDiverter> newCout, newCerr;
            if (divertStreams) {
                newCout.reset(new OstreamDiverter(cout));
                newCerr.reset(new OstreamDiverter(cerr));
            }

            const SimpleTest::Test* running = nullptr;
            SimpleTest::TestReporter reporter = [&](const Vector<SimpleTest::TestGroup>& groups) {
                /* cout 可能已被重定向。若是，请使用“真实”的 cout。 */
                ostream& out = newCout? newCout->out() : cout;

                /* 保存最后一组测试组，以便稍后输出失败信息。 */
                lastGroups = groups;
                for (const auto& group: groups) {
                    for (const auto& test: group.tests) {
                        if (running == &test) {
                            if (test.result == SimpleTest::TestResult::PASS) {
                                out << "    pass" << endl;
                            } else if (test.result == SimpleTest::TestResult::FAIL) {
                                out << "    FAIL: " << test.detailMessage << endl;
                            } else if (test.result == SimpleTest::TestResult::EXCEPTION) {
                                out << "    FAIL: " << test.detailMessage << endl;
                            } else if (test.result == SimpleTest::TestResult::LEAK) {
                                out << "    LEAK: " << test.detailMessage << endl;
                            } else {
                                error("Internal error: Unknown test result?");
                            }
                            running = nullptr;
                        }
                        if (test.result == SimpleTest::TestResult::RUNNING) {
                            running = &test;
                            out << "Running " << displayNameOf(test) << " from " << group.name << "." << endl;
                        }
                    }
                }
            };

            SimpleTest::run(reporter, filter, comparator());
        }

        cout << endl;
        cout << "Test summary: " << endl;

        /* 列出所有错误。 */
        int totalTests = 0, totalPassed = 0;
        for (const auto& group: lastGroups) {
            totalTests  += group.numTests;
            totalPassed += group.numPassed;

            if (group.numPassed != group.numTests) {
                cerr << "Tests failed in " << group.name << ":" << endl;

                for (const auto& test: group.tests) {
                    if (test.result != SimpleTest::TestResult::PASS) {
                        cerr << "FAIL: " << test.name << " (line " << test.lineNumber << ")" << endl;
                        cerr << test.detailMessage << endl;
                    }
                }
            }
        }

        /* 列出错误数量。 */
        for (const auto& group: lastGroups) {
            cout << group.name << ": " << group.numPassed << " of " << pluralize(group.numTests, "test") << " passed." << endl;
        }

        if (lastGroups.size() > 1) {
            cout << "Overall: " << totalPassed << " of " << pluralize(totalTests, "test") << " passed." << endl;
        }

        if (totalTests == totalPassed) {
            cout << "All tests passed!" << endl;
        }
    }
}

namespace MiniGUI {
    namespace Detail {
        void runConsoleModeTests(SimpleTest::TestFilter filter, bool divertStreams) {
            runConsoleTests(filter, divertStreams);
        }
    }
}

CONSOLE_HANDLER("Run Tests") {
    auto groups = getTestGroups();
    int selection = getTestSelection(groups);

    runConsoleTests(filterToSelection(groups, selection), false);
}
