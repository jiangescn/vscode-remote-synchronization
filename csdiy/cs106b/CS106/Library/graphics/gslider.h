/*
 * 文件：gslider.h
 * ---------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 添加按键事件
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gslider.h，以替代 Java 版本
 * @version 2018/06/29
 * - 初始版本
 */


#ifndef _gslider_h
#define _gslider_h

#include <string>
#include <QSlider>

#include "ginteractor.h"

class _Internal_QSlider;

/**
 * 此交互控件子类表示屏幕上的滑块。
 * 拖动滑块控件会生成动作事件。
 */
class GSlider : public GInteractor {
public:
    /**
     * 滑块的两种有效方向。
     */
    enum Orientation {
        HORIZONTAL = 0,
        VERTICAL   = 1
    };

    /**
     * 滑块的默认最小值（0）。
     */
    static const int DEFAULT_MIN_VALUE;

    /**
     * 滑块的默认最大值（100）。
     */
    static const int DEFAULT_MAX_VALUE;

    /**
     * 滑块的默认初始值（50）。
     */
    static const int DEFAULT_INITIAL_VALUE;

    /**
     * 创建具有给定值范围的新水平滑块。
     * @throw 如果 min > max，或 value 不在 min 与 max 之间，则抛出 ErrorException
     */
    GSlider(int min = 0, int max = 100, int value = 50, QWidget* parent = nullptr);

    /**
     * 创建具有给定值范围的新水平或垂直滑块。
     * @throw 如果 min > max，或 value 不在 min 与 max 之间，则抛出 ErrorException
     */
    GSlider(Orientation orientation, int min = 0, int max = 100, int value = 50, QWidget* parent = nullptr);

    /**
     * 释放滑块内部分配的内存。
     */
    ~GSlider() override;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回滑块刻度之间的像素间距。
     * @private
     */
    virtual int getMajorTickSpacing() const;

    /**
     * 返回滑块允许的最大值。
     */
    virtual int getMax() const;

    /**
     * 返回滑块允许的最小值。
     */
    virtual int getMin() const;

    /**
     * 返回滑块小刻度之间的像素间距。
     * @private
     */
    virtual int getMinorTickSpacing() const;

    /**
     * 返回滑块方向，HORIZONTAL 或 VERTICAL。
     */
    virtual Orientation getOrientation() const;

    /**
     * 返回滑块是否按固定间隔绘制文本标签。
     * 默认为 false。
     * @private
     */
    virtual bool getPaintLabels() const;

    /**
     * 返回滑块是否按固定间隔绘制刻度线。
     * @private
     */
    virtual bool getPaintTicks() const;

    /**
     * 返回滑块光标是否被限制为只能停在
     * 其刻度线。
     * @private
     */
    virtual bool getSnapToTicks() const;

    /* @inherit */
    std::string getType() const override;

    /**
     * 返回滑块的当前值。
     */
    virtual int getValue() const;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 设置滑块刻度之间的像素间距。
     * @private
     */
    virtual void setMajorTickSpacing(int value);

    /**
     * 设置滑块允许的最大值。
     * @throw 如果 min > max，则抛出 ErrorException
     */
    virtual void setMax(int max);

    /**
     * 设置滑块允许的最小值。
     * @throw 如果 min > max，则抛出 ErrorException
     */
    virtual void setMin(int min);

    /**
     * 设置滑块小刻度之间的像素间距。
     * @private
     */
    virtual void setMinorTickSpacing(int value);

    /**
     * 设置滑块是否按固定间隔绘制文本标签。
     * 默认为 false。
     * @private
     */
    virtual void setPaintLabels(bool value);

    /**
     * 设置滑块是否按固定间隔绘制刻度线。
     * @private
     */
    virtual void setPaintTicks(bool value);

    /**
     * 设置滑块的最小-最大范围。
     * @throw 如果 min > max，或 value 不在 min 与 max 之间，则抛出 ErrorException
     */
    virtual void setRange(int min, int max);

    /**
     * 设置滑块光标是否被限制为只能停在
     * 其刻度线。
     * @private
     */
    virtual void setSnapToTicks(bool value);

    /**
     * 设置滑块的所有相关状态。
     * @throw 如果 min > max，或 value 不在 min 与 max 之间，则抛出 ErrorException
     */
    virtual void setState(int min, int max, int value);

    /**
     * 设置滑块的当前值。
     * @throw 如果 value 不在 min 和 max 之间，则抛出 ErrorException
     */
    virtual void setValue(int value);

protected:
    /**
     * @private
     */
    std::string getActionEventType() const override;

private:
    Q_DISABLE_COPY(GSlider)

    _Internal_QSlider* _iqslider;

    friend class _Internal_QSlider;
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QSlider : public QSlider, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QSlider(GSlider* qgslider, Qt::Orientation orientation = Qt::Horizontal, QWidget* parent = nullptr);
    void detach() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    QSize sizeHint() const override;

public slots:
    void handleChange(int value);

private:
    GSlider* _gslider;

    friend class GSlider;
};

#endif // _gslider_h
