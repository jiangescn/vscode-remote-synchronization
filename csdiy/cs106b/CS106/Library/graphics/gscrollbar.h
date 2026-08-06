/*
 * 文件：qgscrollbar.h
 * -------------------
 *
 * @author Marty Stepp
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gscrollbar.h，以替代 Java 版本
 * @version 2018/07/16
 * - 初始版本
 */


#ifndef _gscrollbar_h
#define _gscrollbar_h

#include <string>
#include <QScrollBar>

#include "ginteractor.h"

class _Internal_QScrollBar;

/**
 * GScrollBar 表示可供使用的水平或垂直滚动条
 * 由用户拖动。滚动条本身不会使任何其他交互控件
 * 使其自身滚动。如果希望该滚动条产生任何效果，必须等待
 * 用于监听滚动事件并响应它们。
 *
 * 给定滚动条具有可表示的值范围，包含最小值和最大值，
 * 以及一个当前值。
 * 滚动条的“extent”表示滚动条当前可见的部分。
 */
class GScrollBar : public GInteractor {
public:
    /**
     * 滚动条的两种有效方向。
     */
    enum Orientation {
        HORIZONTAL = 0,
        VERTICAL   = 1
    };

    /**
     * 创建具有给定方向和值范围的新滚动条。
     * @throw 如果 min > max，或 value 不在 min 与 max 之间，则抛出 ErrorException
     */
    GScrollBar(Orientation orientation = VERTICAL, int value = 0, int extent = 10, int min = 0, int max = 100, QWidget* parent = nullptr);

    /**
     * 释放滚动条内部分配的内存。
     */
    ~GScrollBar() override;

    /**
     * 返回滚动条的 extent，即其范围中以下部分的大小
     * 当前可见。
     */
    virtual int getExtent() const;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回滚动条允许的最大值。
     */
    virtual int getMax() const;

    /**
     * 返回滚动条允许的最小值。
     */
    virtual int getMin() const;

    /**
     * 返回滚动条方向，HORIZONTAL 或 VERTICAL。
     */
    virtual Orientation getOrientation() const;

    /* @inherit */
    std::string getType() const override;

    /**
     * 返回滚动条的当前值。
     */
    virtual int getValue() const;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 设置滚动条的 extent，即其范围中以下部分的大小
     * 当前可见。
     */
    virtual void setExtent(int extent);

    /**
     * 设置滚动条允许的最大值。
     * @throw 如果 min > max，则抛出 ErrorException
     */
    virtual void setMax(int max);

    /**
     * 设置滚动条允许的最小值。
     * @throw 如果 min > max，则抛出 ErrorException
     */
    virtual void setMin(int min);

    /**
     * 设置滚动条的所有相关状态。
     * @throw 如果 min > max，或 value 不在 min 与 max 之间，则抛出 ErrorException
     */
    virtual void setState(int value, int extent, int min, int max);

    /**
     * 设置滚动条的当前值。
     * @throw 如果 value 不在 min 和 max 之间，则抛出 ErrorException
     */
    virtual void setValue(int value);

protected:
    /**
     * @private
     */
    std::string getActionEventType() const override;

private:
    Q_DISABLE_COPY(GScrollBar)

    _Internal_QScrollBar* _iqscrollbar;

    friend class _Internal_QScrollBar;

    void updateSize();
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QScrollBar : public QScrollBar, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QScrollBar(GScrollBar* qgscrollbar, Qt::Orientation orientation, QWidget* parent = nullptr);
    void detach() override;
    QSize sizeHint() const override;

public slots:
    void handleValueChange(int value);

private:
    GScrollBar* _gscrollbar;

    friend class GScrollBar;
};

#endif // _gscrollbar_h
