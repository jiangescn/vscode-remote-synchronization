/*
 * 文件：gradiobutton.h
 * --------------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 添加按键事件支持
 * @version 2018/10/06
 * - 添加 toggle()
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/04
 * - 添加双击事件支持
 * @version 2018/08/23
 * - 重命名为 gradiobutton.h，以替代 Java 版本
 * @version 2018/06/29
 * - 添加 change 事件
 * @version 2018/06/25
 * - 初始版本
 */


#ifndef _gradiobutton_h
#define _gradiobutton_h

#include <string>
#include <QButtonGroup>
#include <QRadioButton>

#include "ginteractor.h"
#include "map.h"

class _Internal_QRadioButton;

/**
 * 此交互控件子类表示屏幕上的单选按钮。
 * 单选按钮是圆形按钮，可通过点击进行“选中”。
 * 单选按钮与复选框的区别在于，它通常属于一个互斥的
 * 互斥选项组，其中最多只能选中一个按钮
 * 一次一个。选中某组中的一个单选按钮会选中它，同时取消选中
 * 同一组中的任何其他已选单选按钮。
 *
 * 可以通过设置操作监听器监听单选按钮点击，
 * 传入希望每次单击时调用的函数。
 */
class GRadioButton : public GInteractor {
public:
    /**
     * 创建具有给定文本的新单选按钮。
     * 可以传入表示一组逻辑单选按钮的字符串；
     * 如果这样做，此单选按钮将在内部进行管理，确保最多只有
     * 任意时刻，该组中只会有一个单选按钮被选中。
     * 如果未提供组，则单选按钮会被放入默认组。
     */
    GRadioButton(const std::string& text = "", const std::string& group = "default", bool checked = false, QWidget* parent = nullptr);

    /**
     * 释放单选按钮内部分配的内存。
     */
    ~GRadioButton() override;

    /* @inherit */
    std::string getActionCommand() const override;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回单选按钮旁边的文本。
     */
    virtual std::string getText() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 如果单选按钮当前已选中，则返回 true。
     * 等价于 isSelected。
     */
    virtual bool isChecked() const;

    /**
     * 如果单选按钮当前已选中，则返回 true。
     * 等价于 isChecked。
     */
    virtual bool isSelected() const;

    /**
     * 设置单选按钮是否应被选中。
     * 等价于 setSelected。
     */
    virtual void setChecked(bool checked);

    /**
     * 设置单选按钮是否应被选中。
     * 等价于 setChecked。
     */
    virtual void setSelected(bool selected);

    /**
     * 设置单选按钮旁边显示的文本。
     */
    virtual void setText(const std::string& text);

    /**
     * 反转按钮的选中状态：若原先未选中则设为选中
     * 未选中；如果已选中，则将其取消选中。
     */
    virtual void toggle();

protected:
    /**
     * @private
     */
    std::string getActionEventType() const override;

private:
    Q_DISABLE_COPY(GRadioButton)

    static Map<std::string, QButtonGroup*> _buttonGroups;
    static QButtonGroup* getButtonGroup(const std::string& group);

    _Internal_QRadioButton* _iqradioButton;

    friend class _Internal_QRadioButton;
};


/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QRadioButton : public QRadioButton, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QRadioButton(GRadioButton* gradioButton, bool checked = false, QWidget* parent = nullptr);
    void detach() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    QSize sizeHint() const override;

signals:
    void doubleClicked();

public slots:
    void handleClick();

protected:
    void mouseDoubleClickEvent(QMouseEvent* e) override;

private:
    GRadioButton* _gradioButton;

    friend class GRadioButton;
};

#endif // _gradiobutton_h
