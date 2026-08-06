/* 用于测试优先队列的交互式环境。 */
#include "GUI/MiniGUI.h"
#include "HeapPQueue.h"
#include "gwindow.h"
#include "ginteractors.h"
#include "hashmap.h"
#include "gthread.h"
#include "simpio.h"
#include <vector>
#include <iomanip>
using namespace std;

namespace {
    const string kButtonFont = "Monospaced-12";

    /* 允许用户以交互方式测试 PQueue 类型的问题处理程序。 */
    class InteractivePQueueGUI: public ProblemHandler {
    public:
        InteractivePQueueGUI(GWindow& window);

        void actionPerformed(GObservable* source) override;

    private:
        Temporary<GColorConsole> console;

        /* 控制项。分为两组：一组用于构造函数，
         * 一组用于构造函数，另一组用于析构函数和成员函数。
         */
        Temporary<GButton> construct;
        Temporary<GButton> destruct;

        /* 其他命令的列表。由于我们无法
         * 将它们用作映射键。
         */
        vector<Temporary<GButton>> memberFnButtons;
        HashMap<GButton*, std::string> memberFns;

        /* 用于 enqueue 的两个输入。 */
        Temporary<GTextField> name, weight;

        /* 这些输入周围的装饰。 */
        Temporary<GLabel> open, comma, close;

        /* 用于清空控制台的按钮。 */
        Temporary<GButton> clear;

        /* 实际的堆。 */
        HeapPQueue* pq = nullptr;

        /* 这是哪个队列。 */
        int index = 0;

        /* 返回给定可观察对象是否为命令的来源。 */
        bool sourceIs(GObservable* observable, const string& command) const;

        /* 执行函数并记录输出。 */
        template <typename Function>
        bool performSafely(const string& command, Function fn);

        /* 执行所有适当的操作。 */
        void setQueueExists(bool exists);
        void doConstruct();
        void doDestruct();
        void doSize();
        void doIsEmpty();
        void doPeek();
        void doEnqueue();
        void doDequeue();
        void doClear();
        void doPrintDebugInfo();
    };

    /* 创建具有指定名称的按钮，并将其安装到窗口的给定
     * 位置。
     */
    Temporary<GButton> makeButton(const string& name, GWindow& window, const string& location, bool enabled) {
        Temporary<GButton> result(new GButton(name), window, location);
        result->setFont(kButtonFont);
        result->setEnabled(enabled);
        return result;
    }

    InteractivePQueueGUI::InteractivePQueueGUI(GWindow& window): ProblemHandler(window) {
        /* 标准按钮。 */
        construct      = makeButton("HeapPQueue()", window, "WEST", true);
        destruct       = makeButton("~HeapPQueue()", window, "WEST", false);

        /* 成员函数。 */
        memberFnButtons.push_back(makeButton("size();", window, "WEST", false));
        memberFnButtons.push_back(makeButton("isEmpty();", window, "WEST", false));
        memberFnButtons.push_back(makeButton("peek();", window, "WEST", false));
        memberFnButtons.push_back(makeButton("dequeue();", window, "WEST", false));
        memberFnButtons.push_back(makeButton("printDebugInfo();", window, "WEST", false));

        /* 入队。 */
        memberFnButtons.push_back(makeButton("enqueue", window, "SOUTH", false));

        open = Temporary<GLabel>(new GLabel("( { \""), window, "SOUTH");
        open->setFont(kButtonFont);

        name = Temporary<GTextField>(new GTextField(), window, "SOUTH");
        name->setFont(kButtonFont);
        name->setEnabled(false);

        comma = Temporary<GLabel>(new GLabel("\", "), window, "SOUTH");
        comma->setFont(kButtonFont);

        weight = Temporary<GTextField>(new GTextField(), window, "SOUTH");
        weight->setFont(kButtonFont);
        weight->setEnabled(false);

        close = Temporary<GLabel>(new GLabel(" } );"), window, "SOUTH");
        close->setFont(kButtonFont);

        /* 输出窗格。 */
        console = Temporary<GColorConsole>(new GColorConsole(), window, "CENTER");

        /* 清除按钮。 */
        clear = makeButton("Clear Console", window, "EAST", true);

        /* 将所有命令组装到命令列表。 */
        for (const auto& button: memberFnButtons) {
            string command = button->getText();
            command = command.substr(0, command.find("("));

            memberFns[button.get()] = command;
        }
    }

    /* 给定可观察对象，报告其是否与给定名称的对象关联
     * 函数。
     */
    bool InteractivePQueueGUI::sourceIs(GObservable* observable, const string& name) const {
        auto* button = dynamic_cast<GButton *>(observable);
        return button && memberFns.get(button) == name;
    }

    template <typename T> struct Box {};

    template <typename Function, typename T>
    void logEffectsOf(GColorConsole& g, Function fn, Box<T>) {
        auto value = fn();
        g.doWithStyle("#008000", [&] {
             g << " // Returned " << boolalpha << value << endl;
        });
    }

    template <typename Function>
    void logEffectsOf(GColorConsole& g, Function fn, Box<void>) {
        fn();
        g << endl;
    }

    /* 执行给定操作并记录结果。 */
    template <typename Function>
    bool InteractivePQueueGUI::performSafely(const string& command, Function fn) {
        *console << stringReplace(command, "%s", "hpq" + to_string(index));
        try {
            logEffectsOf(*console, fn, Box<decltype(fn())>());
            return true;
        } catch (const ErrorException& e) {
            console->doWithStyle("#800000", [&, this] {
                *console << " // Triggered a call to error(\"" << e.what() << "\");" << endl;
            });
            return false;
        } catch (const exception& e) {
            console->doWithStyle("#FF0000", GColorConsole::BOLD_ITALIC, [&, this] {
                *console << " // !! runtime exception generated: \"" << e.what() << "\"" << endl;
            });
            return false;
        } catch (...) {
            console->doWithStyle("#FF0000", GColorConsole::BOLD_ITALIC, [&, this] {
                *console << " // !! unknown exception generated" << endl;
            });
            return false;
        }
    }

    /* 在队列创建/销毁时更新控件。 */
    void InteractivePQueueGUI::setQueueExists(bool exists) {
        construct->setEnabled(!exists);
        destruct->setEnabled(exists);
        name->setEnabled(exists);
        weight->setEnabled(exists);
        for (auto* button: memberFns) {
            button->setEnabled(exists);
        }
    }

    void InteractivePQueueGUI::doConstruct() {
        /* 创建优先队列。 */
        performSafely("HeapPQueue %s;", [&, this] {
            pq = new HeapPQueue();

            setQueueExists(true);
        });
    }

    void InteractivePQueueGUI::doDestruct() {
        /* 创建优先队列。 */
        performSafely("/* %s goes out of scope */", [&, this] {
            delete pq;
            pq = nullptr;
            index++;

            setQueueExists(false);
            *console << endl;
        });
    }
    void InteractivePQueueGUI::doEnqueue() {
        /* 获取名称/权重对，并验证权重是否合法。 */
        string name = this->name->getText();
        double weight;
        try {
            weight = stringToReal(this->weight->getText());
        } catch (const ErrorException &) {
            GOptionPane::showMessageDialog("Please enter a valid weight.", "Invalid weight");
            return;
        }

        /* 将其入队。 */
        ostringstream command;
        command << "%s.enqueue(" << DataPoint{name, weight} << ");";
        performSafely(command.str(), [&, this] {
            pq->enqueue({ name, weight });
        });
    }
    void InteractivePQueueGUI::doDequeue() {
        performSafely("%s.dequeue();", [&, this] {
            return pq->dequeue();
        });
    }
    void InteractivePQueueGUI::doPeek() {
        performSafely("%s.peek();", [&, this] {
            return pq->peek();
        });
    }
    void InteractivePQueueGUI::doSize() {
        performSafely("%s.size();", [&, this] {
            return pq->size();
        });
    }
    void InteractivePQueueGUI::doIsEmpty() {
        performSafely("%s.isEmpty();", [&, this] {
            return pq->isEmpty();
        });
    }
    void InteractivePQueueGUI::doPrintDebugInfo() {
        /* 临时接管 cout，将其重定向到我们自己的缓冲区。 */
        stringstream result;
        auto* oldBuf = cout.rdbuf(result.rdbuf());

        /* 调用 printDebugInfo 查看返回内容。 */
        performSafely("%s.printDebugInfo();", [&, this] {
            pq->printDebugInfo();
        });

        /* 恢复旧缓冲区。 */
        cout.rdbuf(oldBuf);

        /* 显示输出的内容。 */
        console->doWithStyle("#000080", [&, this] {
            for (string line; getline(result, line); ) {
                *console << "  // " << line << endl;
            }
            *console << endl;
        });
    }

    void InteractivePQueueGUI::actionPerformed(GObservable* source) {
        /* 若这是清除按钮，则清空日志。 */
        if (source == clear) {
            console->clearDisplay();
            console->flush();
        }
        /* 我们有两种基本模式：一种存在队列，另一种不存在队列。 */
        else if (pq == nullptr) {
            if (source == construct) {
                doConstruct();
            }
        } else {
            if (source == destruct) {
                doDestruct();
            } else if (source == name || source == weight || sourceIs(source, "enqueue")) {
                doEnqueue();
            } else if (sourceIs(source, "dequeue")) {
                doDequeue();
            } else if (sourceIs(source, "peek")) {
                doPeek();
            } else if (sourceIs(source, "size")) {
                doSize();
            } else if (sourceIs(source, "isEmpty")) {
                doIsEmpty();
            } else if (sourceIs(source, "printDebugInfo")) {
                doPrintDebugInfo();
            }
        }
    }
}

GRAPHICS_HANDLER("Interactive PQueue", GWindow& window) {
    return make_shared<InteractivePQueueGUI>(window);
}

namespace {
    /* 函数：printReplInstructions
     * ------------------------------------------------------------------
     * 打印如何使用 REPL 环境的说明。
     */
    void printReplInstructions() {
        cout << "Interactive Priority Queue Test" << endl;
        cout << "This environment allows you to type in commands that will be" << endl;
        cout << "executed on your priority queue.  The interpreter knows the" << endl;
        cout << "following commands:" << endl;
        cout << endl;
        cout << "   isEmpty:            Reports whether the priority queue is empty." << endl;
        cout << "   size:               Reports the size of the priority queue" << endl;
        cout << "   enqueue <str> <w>:  Enqueues a DataPoint with the given string and weight." << endl;
        cout << "   peek:               Peeks at the minimum element of the priority queue." << endl;
        cout << "   dequeue:            Dequeues the minimum element of the priority queue." << endl;
        cout << "   printDebugInfo:     Prints debug information." << endl;
        cout << "   quit:               Quits the interpret and returns to the menu." << endl;
        cout << endl;
        cout << "The first letter of any command can be used as a substitute" << endl;
        cout << "for any command name." << endl;
    }
}

CONSOLE_HANDLER("Interactive PQueue") {
    printReplInstructions();

            /* 这些花括号引入了新的作用域层级。这可以确保如果
             * 你的优先队列析构函数导致错误时，该错误会发生在
             * 此函数返回。
             */
            {
                HeapPQueue queue;
                while (true) {
                    /* 从用户获取命令。 */
                    istringstream command(getLine("Enter command: "));

                    /* 提取动作。 */
                    string action;
                    command >> action >> ws;
                    action = toLowerCase(action);

                    if (!command) {
                        cout << "Please enter a command." << endl;
                    } else {
                        try {
                            if (action == "peek" || action == "p") {
                                cout << queue.peek() << endl;
                            } else if (action == "isempty" || action == "i") {
                                cout << boolalpha << queue.isEmpty() << endl;
                            } else if (action == "size" || action == "s") {
                                cout << queue.size() << endl;
                            } else if (action == "dequeue" || action == "d") {
                                cout << queue.dequeue() << endl;
                            } else if (action == "quit" || action == "q") {
                                cout << "Leaving test environment...   " << flush;
                                break;
                            } else if (action == "enqueue" || action == "e") {
                                string toEnqueue;
                                double weight;
                                char leftover;
                                if (!(command >> toEnqueue >> weight) || (command >> ws >> leftover)) {
                                    cout << "Please specify a string and a weight." << endl;
                                } else {
                                    DataPoint pt{ toEnqueue, weight };
                                    queue.enqueue(pt);
                                    cout << "Enqueued " << pt << "." << endl;
                                }
                            } else if (action == "printdebuginfo") {
                                queue.printDebugInfo();
                            } else {
                                cout << "Unknown command." << endl;
                            }

                        } catch (ErrorException& e) {
                            cout << "A call to error() was triggered: " << e.getMessage() << endl;
                        } catch (exception& e) {
                            cout << "An error occurred: " << e.what() << endl;
                        } catch (...) {
                            cout << "An unknown error occurred." << endl;
                        }
                    }
                }
            }

            /* 若执行到这里，说明析构函数没有崩溃。 */
            cout << "success." << endl;
            cout << endl;
}
