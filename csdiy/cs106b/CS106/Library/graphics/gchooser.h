/*
 * 文件：gchooser.h
 * ----------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 添加按键事件支持
 * @version 2018/09/07
 * - 添加用于生成新文档的文档注释
 * @version 2018/09/04
 * - 添加 GComboBox 别名
 * @version 2018/08/23
 * - 重命名为 gchooser.h，以替代 Java 版本
 * @version 2018/06/28
 * - 初始版本
 */


#ifndef _gchooser_h
#define _gchooser_h

#include <initializer_list>
#include <string>
#include <QComboBox>

#include "ginteractor.h"
#include "vector.h"

class _Internal_QComboBox;

/**
 * 此交互控件子类表示可选择的下拉列表。
 * GChooser 构造函数创建一个空选择器。
 * 创建选择器后，客户端可以使用 addItem 添加选项。
 */
class GChooser : public GInteractor {
public:
    /**
     * 创建初始不包含任何项目的选择器。
     */
    GChooser(QWidget* parent = nullptr);

    /**
     * 创建初始包含给定项目的选择器。
     */
    GChooser(const std::initializer_list<std::string>& items, QWidget* parent = nullptr);

    /**
     * 创建初始包含给定项目的选择器。
     */
    GChooser(const Vector<std::string>& items, QWidget* parent = nullptr);

    /**
     * 释放选择器内部分配的内存。
     */
    ~GChooser() override;

    /**
     * 将由指定字符串组成的新项目添加到列表末尾。
     */
    virtual void addItem(const std::string& item);

    /**
     * 将给定列表中的每个项目添加到选择器列表末尾。
     */
    virtual void addItems(const std::initializer_list<std::string>& items);

    /**
     * 将给定向量中的每个项目添加到选择器列表末尾。
     */
    virtual void addItems(const Vector<std::string>& items);

    /**
     * 从选择器中删除所有项目。
     */
    virtual void clearItems();

    /* @inherit */
    std::string getActionCommand() const override;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回选择器中给定从 0 开始索引处的项目。
     * @throw 如果索引超出范围，则抛出 ErrorException
     */
    virtual std::string getItem(int index) const;

    /**
     * 返回选择器中的项目数。
     */
    virtual int getItemCount() const;

    /**
     * 返回选择器中选中项目的索引。
     * 如果未选择任何项，则返回 -1。
     * @return 选中的索引；如果没有选中项目，则为 -1
     */
    virtual int getSelectedIndex() const;

    /**
     * 返回选择器中当前选中的项目，
     * 如果当前未选择任何项，则返回空字符串。
     */
    virtual std::string getSelectedItem() const;

    /* @inherit */
    std::string getType() const override;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 如果选择器具有用于输入新项目的可编辑区域，则返回 true。
     * 默认值为 false，除非调用 setEditable(true)。
     */
    virtual bool isEditable() const;

    /**
     * 如果选择器没有项目，则返回 true。
     */
    virtual bool isEmpty() const;

    /**
     * 设置选择器是否具有用于输入新项目的可编辑区域。
     * 初始为 false。
     */
    virtual void setEditable(bool editable);

    /**
     * 将选择器中给定索引处的项目设为给定值。
     * @throw 如果索引超出范围，则抛出 ErrorException
     */
    virtual void setItem(int index, const std::string& item);

    /**
     * 将选择器中给定索引处的项目设为选中。
     * @throw 如果索引超出范围，则抛出 ErrorException
     */
    virtual void setSelectedIndex(int index);

    /**
     * 将选择器中的给定项目设为选中。
     * @throw 如果索引超出范围，则抛出 ErrorException
     */
    virtual void setSelectedItem(const std::string& item);

    /**
     * 返回选择器中的项目数。
     */
    virtual int size() const;

protected:
    /**
     * @private
     */
    std::string getActionEventType() const override;

private:
    Q_DISABLE_COPY(GChooser)

    _Internal_QComboBox* _iqcomboBox;

    void checkIndex(const std::string& member, int index, int min = 0, int max = -1) const;

    friend class _Internal_QComboBox;
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QComboBox : public QComboBox, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QComboBox(GChooser* gchooser, QWidget* parent = nullptr);
    void detach() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    QSize sizeHint() const override;

public slots:
    void handleChange();

private:
    GChooser* _gchooser;

    friend class GChooser;
};

// 为实现与 Java 和 Qt 的名称兼容，将 GComboBox 作为 GChooser 的别名
typedef GChooser GComboBox;

#endif // _gchooser_h
