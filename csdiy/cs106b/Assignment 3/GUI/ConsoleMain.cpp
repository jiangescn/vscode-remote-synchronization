#include "Core.h"
#include "ConsoleUtils.h"
#include "TextUtils.h"
#include "MemoryDiagnostics.h"
#include "SimpleTest.h"
#include "TestDriver.h"
#include "error.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include <cstdlib>
using namespace std;

namespace {
    void printIntro() {
        cout << "You have switched to the console window. Press ENTER to continue." << endl;
        (void) getLine();
    }

    int makeMenuSelection() {
        Vector<string> options;
        for (const auto& entry: MiniGUI::Config::menuOptions()) {
            options += entry.name;
        }
        options += "Quit";

        cout << MiniGUI::Config::programTitle() << endl;
        return makeSelectionFrom("Please make a selection:", options);
    }
}

namespace MiniGUI {
    namespace Detail {
        void consoleMain(function<void()> initialDemo) {
            printIntro();

            do {
                /* 若存在初始演示，则运行它。 */
                if (initialDemo) {
                    initialDemo();
                    initialDemo = nullptr;

                    /* 若没有菜单选项，则处理完成。 */
                    if (MiniGUI::Config::menuOptions().empty()) {
                        break;
                    }

                    /* 否则，隐式返回主菜单。 */
                }
                /* 否则，显示主菜单。 */
                else {
                    int selection = makeMenuSelection();

                    /* “退出”是最后一个选项。 */
                    if (selection == int(MiniGUI::Config::menuOptions().size())) {
                        break;
                    }
                    MiniGUI::Config::menuOptions()[selection].callback();
                }

                cout << endl;
            } while (getYesOrNo("You are back at the main menu. Would you like to pick again?"));

            cout << endl;
            cout << "Exiting..." << endl;
            
            /* 强制退出程序；正常退出路径可能导致段错误。 */
            _Exit(0);
        }
    }
}
