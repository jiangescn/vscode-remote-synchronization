/*
 * 文件：gtimer.h
 * --------------
 * 此文件定义 <code>GTimer</code> 类，该类实现一个
 * 通用间隔计时器。
 *
 * @version 2019/01/23
 * - 添加析构函数
 * @version 2018/09/09
 * - 更新以使用新的 Qt GUI 计时器接口
 * - 添加用于生成新文档的文档注释
 */


#ifndef _gtimer_h
#define _gtimer_h

#include <string>

/**
 * 此类实现了一个简单的间隔计时器，可生成
 * 具有指定频率的 <code>GTimerEvent</code>。
 */
class GTimer {
public:
    /**
     * 创建生成 <code>GTimerEvent</code> 的计时器对象
     * 每当经过指定毫秒数时。不会
     * 在客户端调用 <code>start</code> 前不会生成事件
     * 在计时器上。
     *
     * 由于实现细节，必须至少创建一个 GWindow
     * 在 start() GTimer 对象之前。
     *
     * @throw 如果 milliseconds 为负，则抛出 ErrorException
     */
    GTimer(double milliseconds);

    /**
     * 销毁计时器；如果它当前正在运行，则将其停止。
     */
    ~GTimer();

    /**
     * 返回此计时器每次滴答之间的延迟毫秒数。
     */
    double getDelay() const;

    /**
     * 方法：isStarted
     * 用法：if (timer.isStarted()) { ... }
     * -------------------------------------
     * 如果给定计时器已通过 start() 启动，则返回 true。
     * 如果停止计时器或尚未启动它，
     * 此方法将返回 false。
     */
    bool isStarted() const;

    /**
     * 停止计时器（如果已启动），然后重新启动。
     */
    void restart();

    /**
     * 更改此计时器每次滴答之间的毫秒延迟。
     * 如果计时器当前正在运行，调用此方法会停止
     * 并以新延迟重新启动计时器。
     *
     * @throw 如果 milliseconds 为负，则抛出 ErrorException
     */
    void setDelay(double ms);

    /**
     * 启动计时器。计时器会持续生成计时器事件，直到
     * 停止；要实现单次计时器效果，最简单的方式
     * 方法是在事件内部调用 <code>stop</code> 方法
     * 处理程序。
     */
    void start();

    /**
     * 停止计时器，使其停止生成事件，直到再次启动。
     */
    void stop();

private:
    double _ms;
    int _id;
};

#endif // _gtimer_h
