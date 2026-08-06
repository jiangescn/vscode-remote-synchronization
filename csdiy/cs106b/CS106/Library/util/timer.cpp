/*
 * 文件：timer.cpp
 * ---------------
 * timer.h 中声明的 Timer 类的实现。
 */

#include "timer.h"
#include <sys/time.h>
#include "error.h"

Timer::Timer(bool autostart) {
    _startMS = 0;
    _stopMS = 0;
    _isStarted = false;
    if (autostart) {
        start();
    }
}

long Timer::elapsed() const {
    return _stopMS - _startMS;
}

bool Timer::isStarted() const {
    return _isStarted;
}

void Timer::start() {
    _startMS = currentTimeMS();
    _isStarted = true;
}

long Timer::stop() {
    _stopMS = currentTimeMS();
    if (!_isStarted) {
        // error("计时器未启动");
        _startMS = _stopMS;
    }
    _isStarted = false;
    return elapsed();
}

long Timer::currentTimeMS() {
    timeval time;
    gettimeofday(&time, nullptr);
    return (time.tv_sec * 1000000 + time.tv_usec) / 1000;
}
