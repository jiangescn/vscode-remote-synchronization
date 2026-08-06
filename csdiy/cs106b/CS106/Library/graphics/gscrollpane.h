/*
 * 文件：gscrollpane.h
 * -------------------
 *
 * @author Marty Stepp
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/01
 * - 初始版本
 */


#ifndef _gscrollpane_h
#define _gscrollpane_h

#include <string>
#include <QScrollArea>

#include "ginteractor.h"

class _Internal_QScrollArea;

/**
 * GScrollPane 是一个容器，为另一个交互控件包装滚动条。
 * 它可用于让另一个交互控件保持其首选大小
 * （或某个任意大的大小），但实际只占用较少数量的
 * 使用垂直和/或水平滚动条显示屏幕像素。
 */
class GScrollPane : public GInteractor {
public:
    /**
     * 用于表示每个维度中滚动条是否应当显示的常量
     * 始终显示、从不显示，或仅当内部交互控件的大小满足条件时显示
     * 足够大，需要显示滚动条（默认）。
     */
    enum ScrollBarPolicy {
        SCROLLBAR_AS_NEEDED,
        SCROLLBAR_ALWAYS,
        SCROLLBAR_NEVER
    };

    /**
     * 创建用于滚动给定交互控件的新滚动窗格。
     * @throw 如果交互控件为空，则抛出 ErrorException
     */
    GScrollPane(GInteractor* interactor, QWidget* parent = nullptr);

    /**
     * 释放滚动窗格内部所分配的内存。
     */
    ~GScrollPane() override;

    /**
     * 返回一个常量，指示是否显示水平滚动条。
     */
    virtual ScrollBarPolicy getHorizontalScrollBarPolicy() const;

    /**
     * 返回一个常量，指示是否显示垂直滚动条。
     */
    virtual ScrollBarPolicy getVerticalScrollBarPolicy() const;

    /**
     * 返回此滚动窗格包装的内部交互控件。
     */
    virtual GInteractor* getInteractor() const;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 如果内部交互控件应拉伸到其目标大小，则返回 true
     * 首选大小。默认为 true。
     */
    virtual bool isInteractorStretch() const;

    /**
     * 设置是否显示水平滚动条。
     */
    virtual void setHorizontalScrollBarPolicy(ScrollBarPolicy policy);

    /**
     * 设置是否显示水平和垂直滚动条。
     */
    virtual void setScrollBarPolicy(ScrollBarPolicy policy);

    /**
     * 设置是否显示垂直滚动条。
     */
    virtual void setVerticalScrollBarPolicy(ScrollBarPolicy policy);

    /**
     * 设置内部交互控件是否应拉伸到其目标大小
     * 首选大小。默认为 true。
     */
    virtual void setInteractorStretch(bool stretch);

private:
    Q_DISABLE_COPY(GScrollPane)

    _Internal_QScrollArea* _iqscrollarea;
    GInteractor* _interactor;
    ScrollBarPolicy _horizontalScrollBarPolicy;
    ScrollBarPolicy _verticalScrollBarPolicy;

    friend class _Internal_QScrollArea;

    static Qt::ScrollBarPolicy toQtScrollBarPolicy(ScrollBarPolicy policy);
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QScrollArea : public QScrollArea, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QScrollArea(GScrollPane* gscrollpane, QWidget* parent = nullptr);
    QSize sizeHint() const override;

// private（私有）：
    // GScrollPane* _gscrollpane;
};

#endif // _gscrollpane_h
