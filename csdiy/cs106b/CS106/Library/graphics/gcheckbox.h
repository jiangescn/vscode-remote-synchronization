/*
 * 文件：gcheckbox.h
 * -----------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 添加按键事件支持
 * @version 2018/10/06
 * - 添加 toggle()
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/04
 * - 添加双击事件支持
 * @version 2018/08/23
 * - 重命名为 gcheckbox.h，以替代 Java 版本
 * @version 2018/06/29
 * - 添加 change 事件
 * @version 2018/06/25
 * - 初始版本
 */


#ifndef _gcheckbox_h
#define _gcheckbox_h

#include <string>
#include <QCheckBox>

#include "ginteractor.h"

class _Internal_QCheckBox;

/**
 * 此交互控件子类表示屏幕上的复选框。
 * 单击一次复选框会选中它；再次单击会取消选中。
 * 可以通过设置操作监听器监听复选框点击，
 * 传入希望每次单击时调用的函数。
 */
class GCheckBox : public GInteractor {
public:
    /**
     * 创建具有给定文本的复选框。
     * 可以传入可选的第二个参数，使复选框初始为选中状态。
     */
    GCheckBox(const std::string& text = "", bool checked = false, QWidget* parent = nullptr);

    /**
     * 释放复选框内部分配的内存。
     */
    ~GCheckBox() override;

    /* @inherit */
    std::string getActionCommand() const override;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回复选框旁边的文本。
     */
    virtual std::string getText() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 如果复选框当前已选中，则返回 true。
     * 等价于 isSelected。
     */
    virtual bool isChecked() const;

    /**
     * 如果复选框当前已选中，则返回 true。
     * 等价于 isChecked。
     */
    virtual bool isSelected() const;

    /**
     * 设置复选框是否应被选中。
     * 等价于 setSelected。
     */
    virtual void setChecked(bool checked);

    /**
     * 设置复选框是否应被选中。
     * 等价于 setChecked。
     */
    virtual void setSelected(bool selected);

    /**
     * 设置复选框旁边显示的文本。
     */
    virtual void setText(const std::string& text);

    /**
     * 反转复选框的选中状态：若原先未选中则设为选中
     * 取消选中；如果已选中，则将其取消选中。
     */
    virtual void toggle();

protected:
    /**
     * @private
     */
    std::string getActionEventType() const override;

private:
    Q_DISABLE_COPY(GCheckBox)

    _Internal_QCheckBox* _iqcheckBox;

    friend class _Internal_QCheckBox;
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QCheckBox : public QCheckBox, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QCheckBox(GCheckBox* gcheckBox, bool checked = false, QWidget* parent = nullptr);
    void detach() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    QSize sizeHint() const override;

signals:
    void doubleClicked();

public slots:
    void handleStateChange(int);

protected:
    void mouseDoubleClickEvent(QMouseEvent* e) override;

private:
    GCheckBox* _gcheckBox;

    friend class GCheckBox;
};

#endif // _gcheckbox_h
