/*
 * 文件：gthread.h
 * ---------------
 *
 * 此文件包含与多线程相关的代码。
 * Qt 至少需要两个线程运行：一个主 Qt GUI 线程，
 * 以及单独的学生代码线程。
 * 学生的 main() 函数在后一个学生线程中运行。
 * 还可以使用静态方法在新线程中运行代码
 * GThread::runInNewThread 或 GThread::runInNewThreadAsync。
 *
 * @version 2019/04/13
 * - 重新实现 GThread，以包装 QThread 或 std::thread
 * - 添加用于线程抽象的 GThread 抽象基类
 * - 添加 GThreadQt 和 GThreadStd 子类
 * - 将 GFunctionThread 重命名为 QFunctionThread，以减少名称混淆
 * - 移除 GStudentThread 子类，并将其功能合并到 GThread
 * @version 2018/10/18
 * - 改进线程名称
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gthread.h，以替代 Java 版本
 * @version 2018/07/28
 * - 初始版本
 */

#ifndef _gthread_h
#define _gthread_h

#include <QThread>
#include <atomic>
#include <thread>

#include "gtypes.h"
#include "map.h"

class QtGui;

/**
 * QFunctionThread 是在自己的线程中运行函数的对象
 * 执行线程。
 *
 * 构造它时传入一个要运行的 void 函数作为参数，
 * 然后调用其 <code>run()</code> 方法，在该函数自己的
 * 自己的线程。
 *
 * 客户端通常无需直接访问此类。
 * 若要在库中使用线程，请使用静态方法
 * <code>GThread::runInNewThread</code> 和
 * <code>GThread::runInNewThreadAsync</code>。
 * @private
 */
class QFunctionThread : public QThread {
public:
    /**
     * 构造一个要执行的新线程。
     */
    QFunctionThread(GThunk func);

    /**
     * 构造一个要执行的新线程。
     */
    QFunctionThread(GThunkInt func);

    /**
     * 返回函数返回的值（如果有），否则返回 0。
     */
    int returnValue() const;

protected:
    /**
     * 在自己的线程中执行传给构造函数的函数。
     */
    void run();

private:
    Q_DISABLE_COPY(QFunctionThread)

    GThunk _func;
    GThunkInt _funcInt;
    bool _hasReturn;
    int _returnValue;
};

/**
 * GThread 类是一个包含静态方法的实用工具类，这些方法允许
 * 让你能在各种系统线程上运行代码。
 * 该库始终运行以下两个标准线程：
 *
 * <ol>
 *     <li> Qt GUI 线程，运行 Qt 的主 exec() 循环，
 *          处理所有 GUI 对象的创建和事件
 *          （严格来说，这是程序的主线程）
 *
 *     <li> 学生线程，运行学生的 main() 函数并
 *          main 调用的任何子函数
 * </ol>
 *
 * 学生和客户端通常无需担心线程问题。
 * 许多图形交互控件会在内部调用这些方法
 * 确保所有内部 Qt GUI 控件都在 Qt GUI
 * 线程。这是它们正常运行所必需的。
 *
 * 如果希望在独立线程中运行一段代码，请使用静态方法
 * <code>GThread::runInNewThread</code> 和
 * <code>GThread::runInNewThreadAsync</code>。
 */
class GThread {
public:
    /**
     * 返回线程函数返回的值。
     * 在函数运行结束前，此值将为 0。
     * 仅当你的线程执行的函数
     * 返回一个 int。
     */
    virtual int getResult() const = 0;

    /**
     * 如果给定线程当前正在运行，则返回 true。
     */
    virtual bool isRunning() const = 0;

    /**
     * 等待此线程完成。
     * 会按需无限期等待。
     */
    virtual void join() = 0;

    /**
     * 等待此线程完成。
     * 最多等待给定毫秒数。
     * 如果线程已结束则返回 true；如果仍在运行则返回 false。
     */
    virtual bool join(long ms) = 0;

    /**
     * 返回传给构造函数的线程名称，或一个默认名称
     * 如果未传入名称，则使用默认名称。
     * 并非所有线程实现都支持名称。
     */
    virtual std::string name() const = 0;

    /**
     * 返回线程的优先级。
     * 优先级较高的线程往往比优先级较低的线程获得更多运行时间。
     * 并非所有线程实现都支持优先级。
     */
    virtual int priority() const = 0;

    /**
     * 将线程名称设置为给定值。
     * 并非所有线程实现都支持名称。
     */
    virtual void setName(const std::string& name) = 0;

    /**
     * 将线程优先级设置为给定值。
     * 并非所有线程实现都支持优先级。
     */
    virtual void setPriority(int priority) = 0;

    /**
     * 使线程暂停指定的毫秒数。
     * @throw 如果 ms 为负，则抛出 ErrorException
     */
    virtual void sleep(double ms) = 0;

    /**
     * 指示线程开始运行。
     */
    virtual void start() = 0;

    /**
     * 强制终止线程。
     * 除非绝对必要，否则可能不应调用此函数，
     * 因为这可能导致程序状态混乱。
     */
    virtual void stop() = 0;

    /**
     * 表示当前线程愿意将执行权让给任何
     * 其他希望运行的线程。
     * 它与 sleep() 略有不同，因为 sleep() 要求暂停
     * 使当前线程暂停给定时间，而 yield() 更像是
     * 向其他线程发出提示：如果愿意，现在可以运行。
     */
    virtual void yield() = 0;

    // TODO：用于设置顶层异常处理程序的方法


    /**
     * 如果调用者不在 Qt GUI 线程上运行，则生成错误。
     * 可以传入可选的错误详细消息。
     */
    static void ensureThatThisIsTheQtGuiThread(const std::string& message = "");

    /**
     * 返回调用方的 Qt 线程对象。
     */
    static GThread* getCurrentThread();

    /**
     * 返回表示以下对象 Qt GUI 线程的 Qt 线程对象
     * 应用程序。
     */
    static GThread* getQtGuiThread();

    /**
     * 返回表示以下代码运行线程的 Qt 线程对象
     * 学生的 main() 函数运行。
     */
    static GThread* getStudentThread();

    /**
     * 如果调用方正在 Qt GUI 线程上运行，则返回 true。
     */
    static bool iAmRunningOnTheQtGuiThread();

    /**
     * 如果调用方正在学生线程上运行，则返回 true。
     */
    static bool iAmRunningOnTheStudentThread();

    /**
     * 如果 Qt GUI 线程已创建，则返回 true。
     * 这会发生在学生的 main() 函数运行之前。
     */
    static bool qtGuiThreadExists();

    /**
     * 在独立新线程中运行给定 void 函数，
     * 阻塞当前线程，等待其完成。
     * 可以为线程传入可选名称，这有助于查看
     * 在调试器中遍历线程列表。
     *
     * 新线程中未捕获的异常或错误会使以下对象崩溃：
     * 程序，并且调用线程无法捕获该异常。
     *
     * 若希望新线程在后台运行，
     * 改用 <code>runInNewThreadAsync</code> 函数。
     */
    static void runInNewThread(GThunk func, const std::string& threadName = "");

    /**
     * 在后台独立新线程中运行给定 void 函数；
     * 当前线程不会阻塞，而会继续执行。
     * 可以为线程传入可选名称，这有助于查看
     * 在调试器中遍历线程列表。
     * 返回指向给定线程的指针，以便你按需等待给定的
     * 供线程完成工作的一段时间。
     *
     * 新线程中未捕获的异常或错误会使以下对象崩溃：
     * 程序，并且调用线程无法捕获该异常。
     *
     * 如果希望调用者等待新线程运行结束，
     * 改用 <code>runInNewThread</code> 函数。
     */
    static GThread* runInNewThreadAsync(GThunk func, const std::string& threadName = "");

    /**
     * 在 Qt GUI 线程上运行给定 void 函数，
     * 阻塞当前线程，等待其完成。
     * 内部 GUI 控件会频繁调用此函数，并且
     * 库的交互控件，因为所有 Qt GUI 操作都必须
     * 在应用程序主线程上执行。
     *
     * Qt GUI 线程中未捕获的异常或错误会使以下对象崩溃：
     * 程序，并且调用线程无法捕获该异常。
     *
     * 若希望新线程在后台运行，
     * 改用 <code>runOnQtGuiThreadAsync</code> 函数。
     */
    static void runOnQtGuiThread(GThunk func);

    /**
     * 在后台 Qt GUI 线程上运行给定 void 函数；
     * 当前线程不会阻塞，而会继续执行。
     *
     * Qt GUI 线程中未捕获的异常或错误会使以下对象崩溃：
     * 程序，并且调用线程无法捕获该异常。
     *
     * 如果希望调用者等待 Qt GUI 线程代码运行结束，
     * 改用 <code>runOnQtGuiThread</code> 函数。
     */
    static void runOnQtGuiThreadAsync(GThunk func);

    /**
     * 启动学生线程，并让其运行给定函数，
     * 它不接收参数并返回 int。
     */
    static void startStudentThread(GThunkInt mainFunc);

    /**
     * 如果学生线程已创建，则返回 true。
     */
    static bool studentThreadExists();

    /**
     * 等待给定线程完成，最多等待给定毫秒数。
     * @return 如果线程在经过完整 ms 时间前未完成，则为 true
     */
    static bool wait(GThread* thread, long ms);

    /**
     * 将当前线程设置为应用程序的“Gui”线程。
     * 库初始化代码会调用此函数，以通知 GThread
     * 声明哪个线程是 GUI 线程的类。
     * 客户端无需直接调用此方法。
     * @private
     */
    static void setGuiThread();

protected:
    // 禁止构造
    GThread();
    virtual ~GThread() = default;

    virtual void run() = 0;

    // 成员变量
    GThunk _func;
    GThunkInt _funcInt;
    bool _hasReturn;
    int _returnValue;

    // 指向两个核心库线程的指针
    static GThread* _qtGuiThread;
    static GThread* _studentThread;

    // QThread 与相关 GThread 包装器之间的映射
    static Map<QThread*, GThread*> _allGThreadsQt;
    static Map<std::thread*, GThread*> _allGThreadsStd;



private:
    friend class QtGui;
};


/**
 * GThreadQt 是一个在自己的线程中运行函数的对象
 * Qt 执行线程。
 * 构造它时传入一个要运行的 void 函数作为参数，
 * 然后调用其 <code>run()</code> 方法，在该函数自己的
 * 自己的线程。
 *
 * 提供此功能是为了让你无需自行创建 QThread 子类
 * 仅用于运行给定代码片段。
 *
 * 客户端通常无需直接访问此类。
 * 若要在库中使用线程，请使用静态方法
 * <code>GThread::runInNewThread</code> 和
 * <code>GThread::runInNewThreadAsync</code>。
 * @private
 */
class GThreadQt : public GThread {
public:
    /**
     * 构造一个要执行的新线程，可指定线程名称。
     */
    GThreadQt(GThunk func, const std::string& threadName = "");

    /**
     * 构造一个要执行的新线程，可指定线程名称。
     */
    GThreadQt(GThunkInt func, const std::string& threadName = "");

    /**
     * 构造新线程以包装给定现有 Qt 线程。
     */
    GThreadQt(QThread* qthread);

    virtual ~GThreadQt();

    /* @inherit */
    int getResult() const override;

    /* @inherit */
    bool isRunning() const override;

    /* @inherit */
    void join() override;

    /* @inherit */
    bool join(long ms) override;

    /* @inherit */
    std::string name() const override;

    /* @inherit */
    int priority() const override;

    /* @inherit */
    void setName(const std::string& name) override;

    /* @inherit */
    void setPriority(int priority) override;

    /* @inherit */
    void sleep(double ms) override;

    /* @inherit */
    void start() override;

    /* @inherit */
    void stop() override;

    /* @inherit */
    void yield() override;

protected:
    /* @inherit */
    void run() override;

private:
    Q_DISABLE_COPY(GThreadQt)

    QThread* _qThread;   // 底层真实 Qt 线程
};


/**
 * GThreadQt 是一个在自己的线程中运行函数的对象
 * std::thread 执行线程。
 * 构造它时传入一个要运行的 void 函数作为参数，
 * 然后调用其 <code>run()</code> 方法，在该函数自己的
 * 自己的线程。
 *
 * 提供此功能是为了让你无需自行创建 QThread 子类
 * 仅用于运行给定代码片段。
 *
 * 客户端通常无需直接访问此类。
 * 若要在库中使用线程，请使用静态方法
 * <code>GThread::runInNewThread</code> 和
 * <code>GThread::runInNewThreadAsync</code>。
 * @private
 */
class GThreadStd : public GThread {
public:
    /**
     * 构造一个要执行的新线程，可指定线程名称。
     */
    GThreadStd(GThunk func, const std::string& threadName = "");

    /**
     * 构造一个要执行的新线程，可指定线程名称。
     */
    GThreadStd(GThunkInt func, const std::string& threadName = "");

    /**
     * 构造新线程以包装给定现有 std 线程。
     */
    GThreadStd(std::thread* stdThread);

    virtual ~GThreadStd();

    /* @inherit */
    int getResult() const override;

    /* @inherit */
    bool isRunning() const override;

    /* @inherit */
    void join() override;

    /* @inherit */
    bool join(long ms) override;

    /* @inherit */
    std::string name() const override;

    /* @inherit */
    int priority() const override;

    /* @inherit */
    void setName(const std::string& name) override;

    /* @inherit */
    void setPriority(int priority) override;

    /* @inherit */
    void sleep(double ms) override;

    /* @inherit */
    void start() override;

    /* @inherit */
    void stop() override;

    /* @inherit */
    void yield() override;

protected:
    /* @inherit */
    void run() override;

private:
    Q_DISABLE_COPY(GThreadStd)

    std::thread* _stdThread;   // 底层真实 std 线程
    std::string _name;
    std::atomic<bool> _running;
};


// 设置当前线程名称以在调试器中显示的平台特定方式
void native_set_thread_name(const char *name);

// 退出当前线程的平台特定方式
[[noreturn]] void native_thread_exit();

#endif // _gthread_h
