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
    SimpleTest::TestFilter getTestFilter(const Vector<string>& groups, int selection) {
        if (selection < 0) {
            return [](const string&, const SimpleTest::Test&) { return true; };
        }

        string selectedGroup = groups[selection];

        return [selectedGroup](const string& group, const SimpleTest::Test&) {
            return group == selectedGroup;
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

    SimpleTest::TestGroupComparator comparator() {
        /* 按文件索引对文件排序。 */
        auto fileList = MiniGUI::Config::testOrder();

        return [=](const string& lhs, const string& rhs) {
            /* 比较两个字符串的索引。 */
            return find(fileList.begin(), fileList.end(), lhs) <
                   find(fileList.begin(), fileList.end(), rhs);
        };
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

        SimpleTest::run(reporter, comparator());

        setDemoOptionsEnabled(true);
    }
}

GRAPHICS_HANDLER("Run Tests", GWindow& window) {
    return make_shared<TestingGUI>(window);
}

CONSOLE_HANDLER("Run Tests") {
    auto groups = getTestGroups();
    int selection = getTestSelection(groups);

    Vector<SimpleTest::TestGroup> lastGroups;
    const SimpleTest::Test* running = nullptr;
    SimpleTest::TestReporter reporter = [&](const Vector<SimpleTest::TestGroup>& groups) {
        /* 保存最后一组测试组，以便稍后输出失败信息。 */
        lastGroups = groups;
        for (const auto& group: groups) {
            for (const auto& test: group.tests) {
                if (running == &test) {
                    if (test.result == SimpleTest::TestResult::PASS) {
                        cout << "    pass" << endl;
                    } else if (test.result == SimpleTest::TestResult::FAIL) {
                        cout << "    FAIL: " << test.detailMessage << endl;
                    } else if (test.result == SimpleTest::TestResult::EXCEPTION) {
                        cout << "    FAIL: " << test.detailMessage << endl;
                    } else if (test.result == SimpleTest::TestResult::LEAK) {
                        cout << "    LEAK: " << test.detailMessage << endl;
                    } else {
                        error("Internal error: Unknown test result?");
                    }
                    running = nullptr;
                }
                if (test.result == SimpleTest::TestResult::RUNNING) {
                    running = &test;
                    cout << "Running " << displayNameOf(test) << " from " << group.name << "." << endl;
                }
            }
        }
    };

    SimpleTest::run(reporter, getTestFilter(groups, selection), comparator());

    cout << endl;
    cout << "Test summary: " << endl;

    /* 列出所有错误。 */
    int totalTests = 0, totalPassed = 0;
    for (const auto& group: lastGroups) {
        if (selection < 0 || groups[selection] == group.name) {
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
    }

    /* 列出错误数量。 */
    for (const auto& group: lastGroups) {
        if (selection < 0 || groups[selection] == group.name) {
            cout << group.name << ": " << group.numPassed << " of " << pluralize(group.numTests, "test") << " passed." << endl;
        }
    }

    if (selection < 0) {
        cout << "Overall: " << totalPassed << " of " << pluralize(totalTests, "test") << " passed." << endl;
    }

    if (totalTests == totalPassed) {
        cout << "All tests passed!" << endl;
    }
}
