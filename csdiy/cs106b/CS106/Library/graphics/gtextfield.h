/*
 * 文件：gtextfield.h
 * ------------------
 *
 * @author Marty Stepp
 * @version 2019/04/23
 * - 添加按键事件
 * @version 2018/09/08
 * - 添加用于生成新文档的文档注释
 * @version 2018/08/23
 * - 重命名为 gtextfield.h，以替代 Java 版本
 * @version 2018/06/29
 * - 添加 textChange 事件
 * @version 2018/06/25
 * - 初始版本
 */


#ifndef _gtextfield_h
#define _gtextfield_h

#include <initializer_list>
#include <string>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QString>

#include "ginteractor.h"
#include "vector.h"

class _Internal_QLineEdit;
class _Internal_QSpinBox;
class _Internal_QDoubleSpinBox;

/**
 * 此交互控件子类表示用于输入短文本字符串的文本字段。
 * 在文本字段中按 Enter 会生成动作事件。
 */
class GTextField : public GInteractor {
public:
    /**
     * 文本字段输入有效类型的常量。
     */
    enum InputType {
        INPUT_TYPE_TEXT,
        INPUT_TYPE_INTEGER,
        INPUT_TYPE_REAL
    };

    /**
     * 创建具有给定初始文本的文本字段。
     * 如果传入可选的 charsWide 参数，则按其设置文本字段大小
     * 宽度足以显示给定数量的字符。
     */
    GTextField(const std::string& text = "", int charsWide = 0, QWidget* parent = nullptr);

    /**
     * 创建足够宽、可显示给定字符数的文本字段。
     */
    GTextField(int charsWide, QWidget* parent = nullptr);

    /**
     * 创建用于输入整数值的文本字段，并使用给定初始值。
     * 该值被限制在给定最小值和最大值之间，并按以下数值递增：
     * 给定步长。
     * @throw 如果 min > max，或 value 不在 min 与 max 之间，则抛出 ErrorException
     */
    GTextField(int value, int min, int max, int step = 1, QWidget* parent = nullptr);

    /**
     * 创建用于输入实数值的文本字段，并使用给定初始值。
     * 该值被限制在给定最小值和最大值之间，并按以下数值递增：
     * 给定步长。
     * @throw 如果 min > max，或 value 不在 min 与 max 之间，则抛出 ErrorException
     */
    GTextField(double value, double min, double max, double step, QWidget* parent = nullptr);

    /**
     * 释放文本字段内部分配的内存。
     */
    ~GTextField() override;

    /**
     * 返回以下对象可见区域中可容纳的字符数
     * 此文本字段。
     */
    virtual int getCharsWide() const;

    /**
     * 返回此文本字段接受的输入类型。
     * 默认为文本输入（GTextField::INPUT_TYPE_TEXT），但可以创建
     * 接受整数（INPUT_TYPE_INTEGER）或实数的字段
     * (INPUT_TYPE_REAL).
     */
    virtual InputType getInputType() const;

    /* @inherit */
    _Internal_QWidget* getInternalWidget() const override;

    /**
     * 返回文本字段允许的最大字符串长度。
     * 默认情况下不设置最大值，此时此方法返回 0。
     */
    virtual int getMaxLength() const;

    /**
     * 返回文本字段的占位文本，通常显示在
     * 当字段为空时，以浅灰色文本显示在字段中。
     * 这通常是向用户提示应输入什么值。
     */
    virtual std::string getPlaceholder() const;

    /**
     * 返回文本字段的当前文本。
     * 等价于 getValue。
     */
    virtual std::string getText() const;

    /* @inherit */
    std::string getType() const override;

    /**
     * 返回文本字段的当前文本。
     * 等价于 getText。
     */
    virtual std::string getValue() const;

    /**
     * 返回文本字段中当前输入的值，
     * 解释为 true 或 false 的 bool 值。
     * 有关以下内容的更多信息，请参阅 strlib.h 中的 stringToBool 函数
     * 字符串如何转换为 bool 值。
     * @throw 如果字符串无法转换为 bool 类型，则抛出 ErrorException
     */
    virtual bool getValueAsBool() const;

    /**
     * 以 char 值返回文本字段中当前输入的值。
     * 这会返回字符串的第一个字符；如果文本
     * 字段为空。
     */
    virtual char getValueAsChar() const;

    /**
     * 返回文本字段中当前输入的值，
     * 解释为实数值。
     * 有关以下内容的更多信息，请参阅 strlib.h 中的 stringToDouble 函数
     * 字符串如何转换为数值。
     * @throw 如果字符串无法转换为 double 类型，则抛出 ErrorException
     */
    virtual double getValueAsDouble() const;

    /**
     * 返回文本字段中当前输入的值，
     * 解释为整数值。
     * 有关更多信息，请参阅 strlib.h 中的 stringToInteger 函数
     * 字符串如何转换为数值。
     * 等价于 getValueAsInteger。
     * @throw 如果字符串无法转换为整数类型，则抛出 ErrorException
     */
    virtual int getValueAsInt() const;

    /**
     * 返回文本字段中当前输入的值，
     * 解释为整数值。
     * 有关更多信息，请参阅 strlib.h 中的 stringToInteger 函数
     * 字符串如何转换为数值。
     * 等价于 getValueAsInteger。
     * @throw 如果字符串无法转换为整数类型，则抛出 ErrorException
     */
    virtual int getValueAsInteger() const;

    /* @inherit */
    QWidget* getWidget() const override;

    /**
     * 如果此文本字段具有自动补全选项列表，则返回 true
     * 用户开始输入时会弹出的内容。
     * 文本字段初始没有这样的列表，但你可以提供一个
     * 通过调用 setAutocompleteList。
     */
    virtual bool isAutocompleteEnabled() const;

    /**
     * 如果文本字段的值可编辑，则返回 true。
     * 初始为 true，但可通过调用以下函数更改
     * setEditable(false)。
     */
    virtual bool isEditable() const;

    /**
     * 从此文本字段删除文本变化监听器，使其不再
     * 在用户输入字符时调用它。
     */
    virtual void removeTextChangeListener();

    /**
     * 将给定字符串列表设置为以下对象的自动补全列表：
     * 此文本字段。调用后，如果用户在其中输入字符
     * 文本字段中构成列表中任意字符串前缀的内容，这些字符串
     * 将显示为下拉式自动补全列表，供用户选择
     * 已完成的值来源。
     * 要再次关闭此功能，请调用 setAutocompleteEnabled(false)。
     */
    virtual void setAutocompleteList(std::initializer_list<std::string> strings);

    /**
     * 将给定字符串列表设置为以下对象的自动补全列表：
     * 此文本字段。调用后，如果用户在其中输入字符
     * 文本字段中构成列表中任意字符串前缀的内容，这些字符串
     * 将显示为下拉式自动补全列表，供用户选择
     * 已完成的值来源。
     * 要再次关闭此功能，请调用 setAutocompleteEnabled(false)。
     */
    virtual void setAutocompleteList(const Vector<std::string>& strings);

    /**
     * 设置此文本字段是否启用自动补全功能。
     * 如果调用 setAutocompleteList，自动补全功能会自动
     * 已启用；因此此方法的主要用途是稍后再次关闭它。
     */
    virtual void setAutocompleteEnabled(bool enabled);

    /**
     * 设置此文本字段宽度，使其恰好足以显示
     * 给定数量的字符。
     */
    virtual void setCharsWide(int charsWide);

    /**
     * 设置文本框中的值是否可编辑。
     * 初始为 true。
     */
    virtual void setEditable(bool value);

    /**
     * 设置字段中可输入的最大字符数。
     */
    virtual void setMaxLength(int maxLength);

    /**
     * 设置显示在文本字段背景中的灰色消息
     * 在用户输入任何值之前。
     * 这通常用于提示用户应输入哪类值。
     */
    virtual void setPlaceholder(const std::string& text);

    /**
     * 设置文本字段中的当前文本值。
     */
    virtual void setText(const std::string& text);

    /**
     * 在此文本字段上设置文本更改监听器，以便在以下情况发生时调用它
     * 当字段中的值发生变化时，这会在每次按键时发生。
     * 任何现有的文本更改监听器都会被替换。
     */
    virtual void setTextChangeListener(GEventListener func);

    /**
     * 在此文本字段上设置文本更改监听器，以便在以下情况发生时调用它
     * 当字段中的值发生变化时，这会在每次按键时发生。
     * 任何现有的文本更改监听器都会被替换。
     */
    virtual void setTextChangeListener(GEventListenerVoid func);

    /**
     * 将文本字段当前文本值设为以下内容的字符串表示：
     * 给定值的
     */
    virtual void setValue(bool value);

    /**
     * 将文本字段当前文本值设为以下内容的字符串表示：
     * 给定值的
     */
    virtual void setValue(char value);

    /**
     * 将文本字段当前文本值设为以下内容的字符串表示：
     * 给定值的
     */
    virtual void setValue(double value);

    /**
     * 将文本字段当前文本值设为以下内容的字符串表示：
     * 给定值的
     */
    virtual void setValue(int value);

    /**
     * 将文本字段当前文本值设为以下内容的字符串表示：
     * 给定值的
     * 等价于 setText。
     */
    virtual void setValue(const std::string& value);

    /**
     * 若文本字段中当前输入的值可以
     * 解释为 true 或 false 的 bool 值。
     * 如果为 true，调用 getValueAsBool 将成功。
     */
    virtual bool valueIsBool() const;

    /**
     * 若文本字段中当前输入的值可以
     * 解释为 char 值。
     * 如果其长度恰好为 1，此值将为 true。
     * 如果为 true，调用 getValueAsChar 将成功。
     */
    virtual bool valueIsChar() const;

    /**
     * 若文本字段中当前输入的值可以
     * 解释为实数。
     * 若此值为 true，则调用 getValueAsDouble 会成功。
     * 等价于 valueIsReal。
     */
    virtual bool valueIsDouble() const;

    /**
     * 若文本字段中当前输入的值可以
     * 解释为整数。
     * 若此值为 true，则调用 getValueAsInt/getValueAsInteger 会成功。
     * 等价于 valueIsInteger。
     */
    virtual bool valueIsInt() const;

    /**
     * 若文本字段中当前输入的值可以
     * 解释为整数。
     * 若此值为 true，则调用 getValueAsInt/getValueAsInteger 会成功。
     * 等价于 valueIsInt。
     */
    virtual bool valueIsInteger() const;

    /**
     * 若文本字段中当前输入的值可以
     * 解释为实数。
     * 若此值为 true，则调用 getValueAsDouble 会成功。
     * 等价于 valueIsDouble。
     */
    virtual bool valueIsReal() const;

protected:
    /**
     * @private
     */
    std::string getActionEventType() const override;

private:
    Q_DISABLE_COPY(GTextField)

    // 指向内部 Qt 文本字段的指针；
    // 对于给定实例，这些项中至多有一个非 null
    _Internal_QLineEdit* _iqlineedit;
    _Internal_QSpinBox* _iqspinbox;
    _Internal_QDoubleSpinBox* _iqdoublespinbox;

    // 文本字段类型；帮助我们判断应使用上述哪个内部 Qt 控件
    // 将为非 null
    InputType _inputType;

    friend class _Internal_QLineEdit;
    friend class _Internal_QSpinBox;
    friend class _Internal_QDoubleSpinBox;
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QLineEdit : public QLineEdit, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QLineEdit(GTextField* gtextField, QWidget* parent = nullptr);
    void detach() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    QSize sizeHint() const override;

public slots:
    void handleTextChange(const QString&);

private:
    GTextField* _gtextfield;

    friend class GTextField;
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QSpinBox : public QSpinBox, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QSpinBox(GTextField* qgtextField, int min, int max, int step = 1, QWidget* parent = nullptr);
    void detach() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    virtual QLineEdit* lineEdit() const;
    QSize sizeHint() const override;

public slots:
    void handleTextChange(const QString&);

private:
    GTextField* _gtextfield;

    friend class GTextField;
};

/**
 * 内部类；客户端代码不应使用。
 * @private
 */
class _Internal_QDoubleSpinBox : public QDoubleSpinBox, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QDoubleSpinBox(GTextField* qgtextField, double min, double max, double step = 0.1, QWidget* parent = nullptr);
    void detach() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    virtual QLineEdit* lineEdit() const;
    QSize sizeHint() const override;

public slots:
    void handleTextChange(const QString&);

private:
    GTextField* _gtextfield;

    friend class GTextField;
};

#endif // _gtextfield_h
