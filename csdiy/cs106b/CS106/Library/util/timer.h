/*
 * 文件：timer.h
 * -------------
 * 此文件导出 Timer 类，可用于测量经过的
 * 程序在给定时间间隔内的运行时间（毫秒）。
 *
 * @version 2018/09/25
 * - 添加用于生成新文档的文档注释
 */

#ifndef _timer_h
#define _timer_h

/**
 * Timer 对象可用于测量经过的
 * 程序在给定时间间隔内的运行时间（毫秒）。
 * 用法示例：
 *
 *<pre>
 * Timer tim;
 * tim.start();
 * ... 需要较长时间的代码 ...
 * tim.stop();
 * cout << "耗时 " << tim.elapsed() << "ms。" << endl;
 *</pre>
 */
class Timer {
public:
    /**
     * 构造新计时器。
     * 如果传入值为 true 的可选 bool 参数，也会启动计时器。
     */
    Timer(bool autostart = false);

    /**
     * 返回自此计时器以下状态起经过的毫秒数
     * 已启动。
     * 如果计时器从未启动，则返回 0。
     */
    long elapsed() const;

    /**
     * 如果计时器已启动，则返回 true。
     */
    bool isStarted() const;

    /**
     * 启动计时器。
     * 如果计时器已启动，则重新启动它，使其 'elapsed'
     * 调用时 time 将为 0。
     */
    void start();

    /**
     * 停止计时器并返回经过的毫秒数。
     * 如果计时器从未启动，则视为已经过 0 毫秒。
     */
    long stop();

    /**
     * 用于以 Unix 格式获取当前时间的静态实用函数
     * 自纪元以来的毫秒时间戳。
     */
    static long currentTimeMS();

private:
    // 实例变量
    long _startMS;
    long _stopMS;
    bool _isStarted;
};

#endif // _timer_h
