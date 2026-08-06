#include "ProblemHandler.h"
#include "gthread.h"
using namespace std;

/* 保存主窗口。 */
ProblemHandler::ProblemHandler(GWindow& window) : mainWindow(&window) {
    // 已在成员初始化列表中处理
}

/* 必要时发起重绘。 */
void ProblemHandler::draw() {
    if (isDirty) {
        GThread::runOnQtGuiThread([this] {
            repaint();
            window().repaint();
        });

        isDirty = false;
    }
}

/* 设置脏标记。 */
void ProblemHandler::requestRepaint() {
    isDirty = true;
}

/* 返回保存的窗口。 */
GWindow& ProblemHandler::window() const {
    return *mainWindow;
}

/* 默认绘制函数不执行任何操作。 */
void ProblemHandler::repaint() {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::actionPerformed(GObservable *) {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::changeOccurredIn(GObservable *) {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::timerFired() {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::mouseMoved(double, double) {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::mousePressed(double, double) {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::mouseDragged(double, double) {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::mouseReleased(double, double) {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::mouseExited() {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::mouseClicked(double, double) {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::mouseDoubleClicked(double, double) {
    // 不执行任何操作
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::hyperlinkClicked(const string &) {
    // 不执行任何操作
}

/* 默认处理程序允许关闭。 */
bool ProblemHandler::shuttingDown() {
    return true;
}

/* 默认处理程序不执行任何操作。 */
void ProblemHandler::settingUp() {
    // 不执行任何操作
}

/* 默认处理程序请求重绘。 */
void ProblemHandler::windowResized() {
    requestRepaint();
}
