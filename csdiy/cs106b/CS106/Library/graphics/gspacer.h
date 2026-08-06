/*
 * 文件：gspacer.h
 * ---------------
 *
 * GSpacer 只是一个空白空间块，用于为布局增加间距。
 *
 * @author Marty Stepp
 * @version 2018/10/06
 * - 初始版本
 */


#ifndef _gspacer_h
#define _gspacer_h

#include <string>

#include "ginteractor.h"

class _Internal_QSpacer;
/**
 * GSpacer 只是一个空白空间块，用于为布局增加间距。
 */
class GSpacer : public GInteractor {
public:
    GSpacer(double width, double height, QWidget* parent = nullptr);

    /**
     * 释放滚动窗格内部所分配的内存。
     */
    ~GSpacer() override;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

private:
    Q_DISABLE_COPY(GSpacer)

    _Internal_QSpacer* _iqspacer;

    friend class _Internal_QSpacer;
};


/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QSpacer : public QWidget, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QSpacer(GSpacer* gspacer, double width, double height, QWidget* parent = nullptr);
    QSize sizeHint() const override;

// private（私有）：
    // GSpacer* _gspacer;
};

#endif // _gspacer_h
