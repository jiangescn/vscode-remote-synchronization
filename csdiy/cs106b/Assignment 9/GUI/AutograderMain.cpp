#include "Core.h"
#include "SimpleTest.h"
#include "TestingGUI.h"
#include "AutograderMain.h"
#include "qtgui.h"
using namespace std;

void MiniGUI::Detail::autograderMain() {
    int argc = QtGui::instance()->getArgc();
    char** argv = QtGui::instance()->getArgv();

    /* 需要知道要运行什么。 */
    if (argc == 1) {
        cerr << "Usage: autograder test-filename" << endl;
        _Exit(-1);
    }

    string testFileName = argv[1];

    /* 在控制台模式下运行所有测试，只包含自动评分测试。 */
    runConsoleModeTests([testFileName](const string& filename, const SimpleTest::Test& test) {
        return test.type == SimpleTest::TestType::AUTOGRADER &&
               filename == testFileName;
    }, true);

    /* 强制中止；处理结束。 */
    _Exit(0);
}
