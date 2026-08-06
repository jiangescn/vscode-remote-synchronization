/*
 * 文件：gtimer.cpp
 * ----------------
 * 此文件实现 gtimer.h 接口。
 * 
 * @version 2019/01/23
 * - 添加析构函数
 * @version 2015/07/05
 * - 移除全局静态 Platform 变量，改为在需要时调用 getPlatform
 * @version 2014/10/08
 * - 移除“using namespace”语句
 * - 移除不需要的 include 语句
 */

#include "gtimer.h"
#include "error.h"
#include "gthread.h"
#include "gwindow.h"
#include "require.h"

/* GTimer 类的实现 */

GTimer::GTimer(double milliseconds)
        : _ms(0),
          _id(-1) {
    setDelay(milliseconds);
}

GTimer::~GTimer() {
    stop();
}

double GTimer::getDelay() const {
    return _ms;
}

bool GTimer::isStarted() const {
    return _id >= 0;
}

void GTimer::restart() {
    stop();
    start();
}

void GTimer::setDelay(double ms) {
    require::positive(ms, "GTimer::setDelay", "delay (ms)");
    _ms = ms;
    if (isStarted()) {
        restart();
    }
}

void GTimer::start() {
    _Internal_QMainWindow* lastWindow = static_cast<_Internal_QMainWindow*>(GWindow::getLastWindow());
    if (!lastWindow) {
        error("GTimer::start: You must create at least one GWindow before starting a GTimer.");
        return;
    }
    GThread::runOnQtGuiThreadAsync([this, lastWindow]() {
        _id = lastWindow->timerStart(_ms);
    });
}

void GTimer::stop() {
    _Internal_QMainWindow* lastWindow = static_cast<_Internal_QMainWindow*>(GWindow::getLastWindow());
    if (!lastWindow) {
        error("GTimer::constructor: You must create at least one GWindow before stopping a GTimer.");
        return;
    }
    GThread::runOnQtGuiThreadAsync([this, lastWindow]() {
        lastWindow->timerStop(_id);
        _id = -1;
    });
}
