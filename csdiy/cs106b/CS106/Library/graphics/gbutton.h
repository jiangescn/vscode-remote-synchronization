/*
 * 文件：gbutton.h
 * ---------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 将部分事件处理代码移到 GInteractor 父类
 * @version 2019/04/22
 * - 添加接受 QIcon 和 QPixmap 的 setIcon
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/04
 * - 添加双击事件支持
 * @version 2018/08/23
 * - 重命名为 gbutton.h，以替代 Java 版本
 * @version 2018/06/25
 * - 初始版本
 */


#ifndef _gbutton_h
#define _gbutton_h

#include <string>
#include <QToolButton>

#include "ginteractor.h"

class _Internal_QPushButton;

/**
 * 此交互控件子类表示屏幕上的按钮。
 * 可以使用 setActionListener 方法监听按钮点击，
 * 传入希望每次单击时调用的函数。
 */
class GButton : public GInteractor {
public:
    /**
     * 创建具有指定文本标签和可选图标的按钮。
     */
    GButton(const std::string& text = "", const std::string& iconFileName = "", QWidget* parent = nullptr);

    /**
     * 创建具有指定文本标签和图标的按钮。
     */
    GButton(const std::string& text, const QIcon& icon, QWidget* parent = nullptr);

    /**
     * 创建具有指定文本标签和图标的按钮。
     */
    GButton(const std::string& text, const QPixmap& icon, QWidget* parent = nullptr);

    /**
     * 释放按钮内部分配的内存。
     */
    ~GButton() override;

    /* @inherit */
    std::string getAccelerator() const override;

    /* @inherit */
    std::string getActionCommand() const override;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回按钮文本。
     * @return 文本
     */
    virtual std::string getText() const;

    /**
     * 返回按钮文本相对于图标的位置。
     * 默认值为 TEXT_BESIDE_ICON，但可以改为 TEXT_UNDER_ICON
     * 通过调用 setTextPosition 方法。
     */
    virtual GInteractor::TextPosition getTextPosition() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /* @inherit */
    void setAccelerator(const std::string& accelerator) override;

    /* @inherit */
    void setIcon(const QIcon& icon) override;

    /* @inherit */
    void setIcon(const QPixmap& icon) override;

    /* @inherit */
    void setIcon(const std::string& filename, bool retainIconSize = true) override;

    /**
     * 将按钮文本设为给定文本。
     */
    virtual void setText(const std::string& text);

    /**
     * 设置按钮文本相对于图标的位置。
     * 默认值为 TEXT_BESIDE_ICON，但可以改为 TEXT_UNDER_ICON。
     */
    virtual void setTextPosition(GInteractor::TextPosition position);

private:
    Q_DISABLE_COPY(GButton)
    _Internal_QPushButton* _iqpushbutton;

    friend class _Internal_QPushButton;
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QPushButton : public QToolButton, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QPushButton(GButton* button, QWidget* parent = nullptr);
    void detach() override;
    QSize sizeHint() const override;

signals:
    void doubleClicked();

public slots:
    void handleClick();

protected:
    void mouseDoubleClickEvent(QMouseEvent* e) override;

private:
    GButton* _gbutton;

    friend class GButton;
};

#endif // _gbutton_h
