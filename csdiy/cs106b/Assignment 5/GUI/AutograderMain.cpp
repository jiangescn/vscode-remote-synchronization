#include "Core.h"
#include "SimpleTest.h"
#include "TestingGUI.h"
#include "AutograderMain.h"
using namespace std;

void MiniGUI::Detail::autograderMain() {
    /* 在控制台模式下运行所有测试，只包含自动评分测试。 */
    runConsoleModeTests([](const string&, const SimpleTest::Test& test) {
        return test.type == SimpleTest::TestType::AUTOGRADER;
    }, true);

    /* 强制中止；处理结束。 */
    _Exit(0);
}
