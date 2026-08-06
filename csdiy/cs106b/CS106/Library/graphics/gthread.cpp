/*
 * 文件：gthread.cpp
 * -----------------
 *
 * 此文件实现在 gthread.h 中声明的成员。
 *
 * @version 2019/04/13
 * - 重新实现 GThread，以包装 QThread 或 std::thread
 * - 添加用于线程抽象的 GThread 抽象基类
 * - 添加 GThreadQt 和 GThreadStd 子类
 * - 将 GFunctionThread 重命名为 QFunctionThread，以减少名称混淆
 * - 移除 GStudentThread 子类，并将其功能合并到 GThread
 * @version 2018/10/18
 * - 改进线程名称
 * @version 2018/10/01
 * - 修复 main 结束太快时输出不会显示在控制台上的问题
 * @version 2018/09/23
 * - 修复程序结束时关闭控制台的问题
 * @version 2018/08/23
 * - 重命名为 gthread.h，以替代 Java 版本
 * @version 2018/07/28
 * - 初始版本
 */

#include "gthread.h"
#include "consoletext.h"
#include "gevent.h"
#include "geventqueue.h"
#include "qtgui.h"
#include "require.h"
#include <chrono>
#include <pthread.h>

void native_set_thread_name(const char *name)
{
#ifdef __APPLE__
    pthread_setname_np(name);
#elif defined _WIN32
    pthread_setname_np(pthread_self(), name);
#else
    // 在其他平台上忽略
    // JDZ：Linux 上可能与 Windows 相同
    // 但我没有 Linux 系统可供测试确认
#endif
}

void native_thread_exit()
{
    pthread_exit(nullptr);
    // JDZ：Mac+Windows，但 Linux 也是吗？需要测试
}


QFunctionThread::QFunctionThread(GThunk func)
        : _func(func),
          _hasReturn(false),
          _returnValue(0) {
    // 空
}

QFunctionThread::QFunctionThread(GThunkInt func)
        : _funcInt(func),
          _hasReturn(true),
          _returnValue(0) {
    // 空
}

int QFunctionThread::returnValue() const {
    return _returnValue;
}

void QFunctionThread::run() {
    if (_hasReturn) {
        _returnValue = _funcInt();
    } else {
        _func();
    }
}


/*静态*/ GThread* GThread::_qtGuiThread = nullptr;
/*静态*/ GThread* GThread::_studentThread = nullptr;
Map<QThread*, GThread*> GThread::_allGThreadsQt;
Map<std::thread*, GThread*> GThread::_allGThreadsStd;

GThread::GThread() {
    // 空
}

/*静态*/ void GThread::ensureThatThisIsTheQtGuiThread(const std::string& message) {
    if (!iAmRunningOnTheQtGuiThread()) {
        error((message.empty() ? "" : (message + ": "))
              + "Qt GUI system must be initialized from the application's main thread.");
    }
}

/*静态*/ GThread* GThread::getCurrentThread() {
    QThread* currentQtThread = QThread::currentThread();
    if (_allGThreadsQt.containsKey(currentQtThread)) {
        return _allGThreadsQt[currentQtThread];
    } else {
        return new GThreadQt(currentQtThread);
    }
}

/*静态*/ GThread* GThread::getQtGuiThread() {
    return _qtGuiThread;
}

/*静态*/ GThread* GThread::getStudentThread() {
    return _studentThread;
}

/*静态*/ bool GThread::iAmRunningOnTheQtGuiThread() {
    return _qtGuiThread && _qtGuiThread == getCurrentThread();
}

/*静态*/ bool GThread::iAmRunningOnTheStudentThread() {
    return _studentThread && _studentThread == getCurrentThread();
}

/*静态*/ bool GThread::qtGuiThreadExists() {
    return _qtGuiThread != nullptr;
}

/*静态*/ void GThread::runInNewThread(GThunk func, const std::string& threadName) {
    GThread* currentThread = getCurrentThread();
    GThreadQt* thread = new GThreadQt(func, threadName);
    thread->start();
    while (thread->isRunning()) {
        currentThread->sleep(10);
    }
    delete thread;
}

/*静态*/ GThread* GThread::runInNewThreadAsync(GThunk func, const std::string& threadName) {
    GThreadQt* thread = new GThreadQt(func, threadName);
    thread->start();
    return thread;
}

/*静态*/ void GThread::runOnQtGuiThread(GThunk func) {
    if (iAmRunningOnTheQtGuiThread()) {
        // 已经位于 Qt GUI 线程；直接运行函数！
        func();
    } else if (qtGuiThreadExists()) {
        GEventQueue::instance()->runOnQtGuiThreadSync(func);
    } else {
        error("GThread::runOnQtGuiThread: Qt GUI thread has not been initialized properly. \n"
              "Make sure that the file containing your main() function #includes at least \n"
              "one .h header from the Stanford C++ library.");
    }
}

/*静态*/ void GThread::runOnQtGuiThreadAsync(GThunk func) {
    if (iAmRunningOnTheQtGuiThread()) {
        // 已经位于 Qt GUI 线程；直接运行函数！
        func();
    } else if (qtGuiThreadExists()) {
        GEventQueue::instance()->runOnQtGuiThreadAsync(func);
    } else {
        error("GThread::runOnQtGuiThreadAsync: Qt GUI thread has not been initialized properly. \n"
              "Make sure that the file containing your main() function #includes at least \n"
              "one .h header from the Stanford C++ library.");
    }
}

/*静态*/ void GThread::setGuiThread() {
    if (!_qtGuiThread) {
        _qtGuiThread = new GThreadQt(QThread::currentThread());
        _qtGuiThread->setName("Qt GUI Thread");
    }
}

/*静态*/ void GThread::startStudentThread(GThunkInt mainFunc) {
    if (!_studentThread) {
        _studentThread = new GThreadStd(mainFunc, "Student main()");
        _studentThread->start();
    }
}

/*静态*/ bool GThread::studentThreadExists() {
    return _studentThread != nullptr;
}

/*静态*/ bool GThread::wait(GThread* thread, long ms) {
    GThread* currentThread = getCurrentThread();
    if (currentThread == thread) {
        error("GThread::wait: a thread cannot wait for itself");
    }

    long startTime = GEvent::getCurrentTimeMS();
    unsigned long msToSleep = static_cast<unsigned long>(ms > 10 ? 10 : ms);
    while (thread && thread->isRunning()) {
        currentThread->sleep(msToSleep);

        // 如果已经等待至少给定时间，则停止
        if (ms > 0 && GEvent::getCurrentTimeMS() - startTime >= ms) {
            break;
        }
    }
    return thread->isRunning();
}

void GThread::yield() {
    QThread::yieldCurrentThread();
}


GThreadQt::GThreadQt(GThunk func, const std::string& threadName)
        : _qThread(nullptr) {
    _func = func;
    _hasReturn = false;
    _returnValue = 0;
    _qThread = new QFunctionThread(func);
    if (!threadName.empty()) {
        setName(threadName);
    }
    _allGThreadsQt[_qThread] = this;
}

GThreadQt::GThreadQt(GThunkInt func, const std::string& threadName)
        : _qThread(nullptr) {
    _funcInt = func;
    _hasReturn = true;
    _returnValue = 0;
    _qThread = new QFunctionThread(func);
    if (!threadName.empty()) {
        setName(threadName);
    }
    _allGThreadsQt[_qThread] = this;
}

GThreadQt::GThreadQt(QThread* qthread)
        : _qThread(qthread) {
    _hasReturn = false;
    _returnValue = 0;
    _allGThreadsQt[_qThread] = this;
}

GThreadQt::~GThreadQt() {
    // TODO：delete _qThread;
    _allGThreadsQt.remove(_qThread);
    _qThread = nullptr;
}

int GThreadQt::getResult() const {
    return _returnValue;
}

bool GThreadQt::isRunning() const {
    return _qThread->isRunning();
}

void GThreadQt::join() {
    if (_qThread->isRunning()) {
        _qThread->wait();
    }
}

// 实现说明：此行为可能不正确。
// 我认为当前行为会让此线程暂停自身，
// 而期望行为是让调用线程等待此线程。
bool GThreadQt::join(long ms) {
    require::nonNegative(ms, "GThread::join", "ms");
    return _qThread->wait(ms);
}

std::string GThreadQt::name() const {
    return _qThread->objectName().toStdString();
}

int GThreadQt::priority() const {
    return static_cast<int>(_qThread->priority());
}

void GThreadQt::run() {
    if (_hasReturn) {
        _returnValue = _funcInt();
    } else {
        _func();
    }
}

void GThreadQt::setName(const std::string& name) {
    _qThread->setObjectName(QString::fromStdString(name));
}

void GThreadQt::setPriority(int priority) {
    QThread::Priority priorityEnum;
    switch (priority) {
        case 0: priorityEnum = QThread::IdlePriority; break;
        case 1: priorityEnum = QThread::LowestPriority; break;
        case 2: priorityEnum = QThread::LowPriority; break;
        case 3: priorityEnum = QThread::NormalPriority; break;
        case 4: priorityEnum = QThread::HighPriority; break;
        case 5: priorityEnum = QThread::HighestPriority; break;
        case 6: priorityEnum = QThread::TimeCriticalPriority; break;
        case 7: priorityEnum = QThread::InheritPriority; break;
        default: priorityEnum = QThread::NormalPriority; break;
    }
    _qThread->setPriority(priorityEnum);
}

void GThreadQt::sleep(double ms) {
    require::nonNegative(ms, "GThread::sleep", "delay (ms)");
    _qThread->msleep(static_cast<unsigned long>(ms));
}

void GThreadQt::start() {
    _qThread->start();
}

void GThreadQt::stop() {
    _qThread->terminate();   // 注意：尽可能不要调用此函数！
}

void GThreadQt::yield() {
    QThread::yieldCurrentThread();   // 一般
}


GThreadStd::GThreadStd(GThunk func, const std::string& threadName)
        : _stdThread(nullptr) {
    _func = func;
    _hasReturn = false;
    _returnValue = 0;
    _running = false;
    if (!threadName.empty()) {
        setName(threadName);
    }
    _allGThreadsStd[_stdThread] = this;
}

GThreadStd::GThreadStd(GThunkInt func, const std::string& threadName)
        : _stdThread(nullptr) {
    _funcInt = func;
    _hasReturn = true;
    _returnValue = 0;
    _running = false;
    if (!threadName.empty()) {
        setName(threadName);
    }
    _allGThreadsStd[_stdThread] = this;
}

GThreadStd::GThreadStd(std::thread* stdThread)
        : _stdThread(stdThread) {
    _hasReturn = false;
    _returnValue = 0;
    _allGThreadsStd[_stdThread] = this;
}

GThreadStd::~GThreadStd() {
    // TODO：delete _stdThread;
    _allGThreadsStd.remove(_stdThread);
    _running = false;
    _stdThread = nullptr;
}

int GThreadStd::getResult() const {
    return _returnValue;
}

bool GThreadStd::isRunning() const {
    return _stdThread != nullptr && _running;
}

// 实现说明：此行为可能不正确。
// 我认为当前行为会让此线程暂停自身，
// 而期望行为是让调用线程等待此线程。
void GThreadStd::join() {
    if (isRunning() && _stdThread->joinable()) {
        _stdThread->join();
    }
}

// 实现说明：此行为可能不正确。
// 我认为当前行为会让此线程暂停自身，
// 而期望行为是让调用线程等待此线程。
bool GThreadStd::join(long ms) {
    require::nonNegative(ms, "GThread::join", "ms");
    long elapsed = 0;
    long amountToSleep = ms >= 50 ? 50 : ms;
    while (elapsed < ms && isRunning()) {
        sleep(amountToSleep);
        elapsed += amountToSleep;
    }
    return !isRunning();
}

std::string GThreadStd::name() const {
    return _name;
}

int GThreadStd::priority() const {
    return static_cast<int>(QThread::NormalPriority);
}



void GThreadStd::run() {
    native_set_thread_name(_name.c_str());
    // 运行给定函数
    _running = true;
    if (_hasReturn) {
        _returnValue = _funcInt();
    } else {
        _func();
    }
    _running = false;
}

void GThreadStd::setName(const std::string& name) {
    _name = name;
}

void GThreadStd::setPriority(int /*优先级*/) {
    // 不支持
}

void GThreadStd::sleep(double ms) {
    require::nonNegative(ms, "GThread::sleep", "delay (ms)");
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(ms)));
}

void GThreadStd::start() {
    // 不需要；std::thread 创建时会隐式自动启动
    _stdThread = new std::thread([&] {
        run();
    });
}

void GThreadStd::stop() {
    // 不支持
}

void GThreadStd::yield() {
    std::this_thread::yield();
}
