/*
 * 文件：gtable.cpp
 * ----------------
 * 此文件实现 GTable.h 接口。
 * 每个成员的文档见该文件。
 *
 * @author Marty Stepp
 * @version 2019/02/02
 * - 析构函数现在会停止事件处理
 * @version 2018/09/06
 * - 添加边界检查和 require() 调用
 * @version 2018/08/23
 * - 重命名为 gtable.cpp，以替代 Java 版本
 * @version 2018/07/21
 * - 为单元格、行、列、表格添加富格式
 * - 改进事件处理
 * @version 2018/07/17
 * - 初始版本，基于 gtable.h
 * @since 2018/07/17
 */

#include "gtable.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <QBrush>
#include <QColor>
#include <QHeaderView>
#include <QLineEdit>
#include <sstream>
#include "gclipboard.h"
#include "gcolor.h"
#include "gevent.h"
#include "gfont.h"
#include "gthread.h"
#include "require.h"

GTable::TableStyle GTable::_defaultCellStyle = GTable::TableStyle::unset();

GTable::GTable(int rows, int columns, double width, double height, QWidget* parent)
        : _iqtableview(nullptr),
          _columnHeaderStyle(GTable::COLUMN_HEADER_NONE) {
    GThread::runOnQtGuiThread([this, rows, columns, parent]() {
        _iqtableview = new _Internal_QTableWidget(this, rows, columns, getInternalParent(parent));
        _iqtableview->setSelectionMode(QAbstractItemView::SingleSelection);
        _globalCellStyle = TableStyle::unset();
    });
    require::nonNegative2D(rows, columns, "GTable::constructor", "rows", "columns");
    require::nonNegative2D(width, height, "GTable::constructor", "width", "height");
    setVisible(false);   // 所有控件在添加到窗口之前都不会显示
}

GTable::~GTable() {
    // TODO：delete _iqtableview;
    _iqtableview->detach();
    _iqtableview = nullptr;
}

void GTable::applyStyleToCell(int row, int column, const TableStyle& style) {
    setCellAlignmentInternal(row, column, style.alignment);
    setCellBackgroundInternal(row, column, style.background);
    setCellFontInternal(row, column, style.font);
    setCellForegroundInternal(row, column, style.foreground);
}

void GTable::autofitColumnWidths() {
    GThread::runOnQtGuiThread([this]() {
        _iqtableview->resizeColumnsToContents();
    });
}

void GTable::checkColumn(const std::string& member, int column) const {
    require::inRange(column, 0, numCols(), "GTable::" + member, "column");
}

void GTable::checkIndex(const std::string& member, int row, int column) const {
    require::inRange2D(row, column, 0, 0, numRows(), numCols(), "GTable::" + member, "row", "column");
}

void GTable::checkRow(const std::string& member, int row) const {
    require::inRange(row, 0, numRows(), "GTable::" + member, "row");
}

void GTable::clear() {
    GThread::runOnQtGuiThread([this]() {
        _iqtableview->clear();
        // 出于某种原因，清空表格也会清除 Excel 风格列标题
        updateColumnHeaders();
    });
}

void GTable::clearCell(int row, int column) {
    checkIndex("clearCell", row, column);
    set(row, column, /* 文本 */ "");
}

void GTable::clearFormatting() {
    GThread::runOnQtGuiThread([this]() {
        // 清除所有行、列和全局表格样式记录
        _columnStyles.clear();
        _rowStyles.clear();
        _globalCellStyle = TableStyle::unset();

        // 设置每个单元格的格式
        for (int row = 0, nr = numRows(), nc = numCols(); row < nr; row++) {
            for (int col = 0; col < nc; col++) {
                clearCellFormatting(row, col);
            }
        }
    });
}

void GTable::clearCellFormatting(int row, int column) {
    checkIndex("clearCellFormatting", row, column);
    GThread::runOnQtGuiThread([this, row, column]() {
        ensureDefaultFormatting();
        TableStyle style = _defaultCellStyle;
        if (style.background >= 0) {
            setCellBackgroundInternal(row, column, style.background);
        }
        if (!style.font.empty()) {
            setCellFontInternal(row, column, style.font);
        }
        if (style.foreground >= 0) {
            setCellForegroundInternal(row, column, style.foreground);
        }
        if (style.alignment >= 0) {
            setCellAlignmentInternal(row, column, style.alignment);
        }
    });
}

void GTable::clearSelection() {
    GThread::runOnQtGuiThread([this]() {
        _iqtableview->clearSelection();
    });
}

void GTable::ensureColumnStyle(int column) {
    ensureDefaultFormatting();
    if (!_columnStyles.containsKey(column)) {
        _columnStyles[column] = TableStyle::unset();
    }
}

void GTable::ensureDefaultFormatting() const {
    GTable* thisHack = (GTable*) this;
    if (!_defaultCellStyle.isSet()) {
        QPalette palette = thisHack->_iqtableview->palette();
        _defaultCellStyle.background = palette.base().color().rgb() & 0x00ffffff;
        _defaultCellStyle.foreground = palette.text().color().rgb() & 0x00ffffff;
        _defaultCellStyle.font       = GFont::toFontString(thisHack->_iqtableview->font());
        _defaultCellStyle.alignment  = ALIGN_LEFT;   // TODO：向单元格查询其对齐方式
    }
}

void GTable::ensureRowStyle(int row) {
    ensureDefaultFormatting();
    if (!_rowStyles.containsKey(row)) {
        _rowStyles[row] = TableStyle::unset();
    }
}

void GTable::fill(const std::string& text) {
    GThread::runOnQtGuiThread([this, text]() {
        int nr = numRows();
        int nc = numCols();
        for (int r = 0; r < nr; r++) {
            for (int c = 0; c < nc; c++) {
                set(r, c, text);
            }
        }
    });
}

std::string GTable::get(int row, int column) const {
    checkIndex("get", row, column);
    return _iqtableview->model()->data(_iqtableview->model()->index(row, column)).toString().toStdString();
}

GTable::ColumnHeaderStyle GTable::getColumnHeaderStyle() const {
    return _columnHeaderStyle;
}

double GTable::getColumnWidth(int column) const {
    checkColumn("getColumnWidth", column);
    return _iqtableview->columnWidth(column);
}

_Internal_QWidget* GTable::getInternalWidget() const {
    return _iqtableview;
}

GTable::TableStyle GTable::getMergedStyleForCell(int row, int column) {
    // 样式优先级：单元格 > 列 > 行 > 全局
    ensureDefaultFormatting();
    TableStyle style = _defaultCellStyle;
    style.mergeWith(_globalCellStyle);
    if (_rowStyles.containsKey(row)) {
        style.mergeWith(_rowStyles[row]);
    }
    if (_columnStyles.containsKey(column)) {
        style.mergeWith(_columnStyles[column]);
    }
    return style;
}

double GTable::getRowHeight(int row) const {
    checkRow("getRowHeight", row);
    return _iqtableview->rowHeight(row);
}

GridLocation GTable::getSelectedCell() const {
    QModelIndexList list = _iqtableview->selectionModel()->selectedIndexes();
    if (list.empty()) {
        return GridLocation(-1, -1);
    } else {
        QModelIndex index = list.at(0);
        return GridLocation(index.row(), index.column());
    }
}

void GTable::getSelectedCell(int& row, int& column) const {
    GridLocation loc = getSelectedCell();
    row = loc.row;
    column = loc.col;
}

std::string GTable::getSelectedCellValue() const {
    if (hasSelectedCell()) {
        GridLocation loc = getSelectedCell();
        return get(loc.row, loc.col);
    } else {
        return "";
    }
}

int GTable::getSelectedColumn() const {
    return getSelectedCell().col;
}

int GTable::getSelectedRow() const {
    return getSelectedCell().row;
}

std::string GTable::getType() const {
    return "GTable";
}

QWidget* GTable::getWidget() const {
    return static_cast<QWidget*>(_iqtableview);
}

bool GTable::hasSelectedCell() const {
    GridLocation loc = getSelectedCell();
    return loc.row >= 0 && loc.col >= 0;
}

int GTable::height() const {
    return numRows();
}

bool GTable::inTableBounds(int row, int column) const {
    return 0 <= row && row < height() && 0 <= column && column < width();
}

bool GTable::isEditable() const {
    return (_iqtableview->editTriggers() & QAbstractItemView::NoEditTriggers) != 0;
}

int GTable::numCols() const {
    return _iqtableview->model()->columnCount();
}

int GTable::numRows() const {
    return _iqtableview->model()->rowCount();
}

void GTable::removeTableListener() {
    removeEventListeners({"table",
                          "tableupdate",
                          "tableselect",
                          "tableeditbegin",
                          "tablereplacebegin",
                          "tablecut",
                          "tablecopy",
                          "tablepaste"});
}

void GTable::requestFocus() {
    bool wasEditing = _iqtableview->isEditing();
    GInteractor::requestFocus();
    if (!wasEditing && hasSelectedCell()) {
        GThread::runOnQtGuiThread([this]() {
            GridLocation loc = getSelectedCell();
            _iqtableview->closePersistentEditor(_iqtableview->item(loc.row, loc.col));
        });
    }
}

void GTable::resize(int newNumRows, int newNumCols) {
    require::nonNegative2D(newNumRows, newNumCols, "GTable::resize", "rows", "columns");
    GThread::runOnQtGuiThread([this, newNumRows, newNumCols]() {
        int oldNumRows = numRows();
        int oldNumCols = numCols();
        _iqtableview->setRowCount(newNumRows);
        _iqtableview->setColumnCount(newNumCols);

        // 确保每列显示正确的表头
        if (newNumCols > oldNumCols) {
            updateColumnHeaders();
        }

        // 向新添加的单元格应用适当样式
        if (newNumRows > oldNumRows || newNumCols > oldNumCols) {
            for (int row = 0; row < newNumRows; row++) {
                for (int col = 0; col < newNumCols; col++) {
                    if (row >= oldNumRows || col >= oldNumCols) {
                        // 确定适当样式（行、列、全局等）并应用
                        TableStyle style = getMergedStyleForCell(row, col);
                        applyStyleToCell(row, col, style);
                    }
                }
            }
        }
    });
}

bool GTable::rowColumnHeadersVisible() const {
    return _iqtableview->horizontalHeader()->isVisible()
            && _iqtableview->verticalHeader()->isVisible();
}

void GTable::select(int row, int column) {
    checkIndex("select", row, column);
    GThread::runOnQtGuiThread([this, row, column]() {
        QModelIndex index = _iqtableview->model()->index(row, column);
        _iqtableview->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
    });
}

void GTable::set(int row, int column, const std::string& text) {
    checkIndex("set", row, column);
    GThread::runOnQtGuiThread([this, row, column, text]() {
        QModelIndex index = _iqtableview->model()->index(row, column);
        _iqtableview->model()->setData(index, QVariant(text.c_str()));
    });
}

void GTable::setBackground(int rgb) {
    // GInteractor::setBackground(rgb);
    // （不要调用 super；那会设置标题及其他所有部分的背景色）

    GThread::runOnQtGuiThread([this, rgb]() {
        // 将此背景色保存到全局单元格样式中（供 resize() 等操作后的单元格使用）
        ensureDefaultFormatting();
        _globalCellStyle.background = rgb;

        // 从所有行/列样式中移除背景色，因为它们已被
        // 现在由此全局背景颜色样式覆盖
        TableStyle unset = TableStyle::unset();
        for (int row : _rowStyles) {
            _rowStyles[row].background = unset.background;
        }
        for (int col : _columnStyles) {
            _columnStyles[col].background = unset.background;
        }

        // 设置每个单元格的背景色
        for (int row = 0, nr = numRows(); row < nr; row++) {
            for (int col = 0, nc = numCols(); col < nc; col++) {
                setCellBackgroundInternal(row, col, rgb);
            }
        }
    });
}

void GTable::setBackground(const std::string& color) {
    setBackground(GColor::convertColorToRGB(color));
}

void GTable::setCellAlignment(int row, int column, HorizontalAlignment alignment) {
    checkIndex("setCellAlignment", row, column);
    GThread::runOnQtGuiThread([this, row, column, alignment]() {
        setCellAlignmentInternal(row, column, alignment);   // 执行实际工作
    });
}

void GTable::setCellAlignmentInternal(int row, int column, HorizontalAlignment alignment) {
    Qt::Alignment align = Qt::AlignVCenter | toQtAlignment(alignment);
    _iqtableview->model()->setData(_iqtableview->model()->index(row, column),
                                   QVariant(align), Qt::TextAlignmentRole);
}

void GTable::setCellBackground(int row, int column, int rgb) {
    checkIndex("setCellBackground", row, column);
    GThread::runOnQtGuiThread([this, row, column, rgb]() {
        setCellBackgroundInternal(row, column, rgb);   // 执行实际工作
    });
}

void GTable::setCellBackground(int row, int column, const std::string& color) {
    setCellBackground(row, column, GColor::convertColorToRGB(color));
}

void GTable::setCellBackgroundInternal(int row, int column, int rgb) {
    _iqtableview->item(row, column)->setBackground(QBrush(QColor(rgb)));
}

void GTable::setCellFont(int row, int column, const std::string& font) {
    checkIndex("setCellFont", row, column);
    GThread::runOnQtGuiThread([this, row, column, font]() {
        setCellFontInternal(row, column, font);   // 执行实际工作
    });
}

void GTable::setCellFontInternal(int row, int column, const std::string& font) {
    _iqtableview->item(row, column)->setFont(GFont::toQFont(_iqtableview->font(), font));
}

void GTable::setCellForeground(int row, int column, int rgb) {
    checkIndex("setCellForeground", row, column);
    GThread::runOnQtGuiThread([this, row, column, rgb]() {
        setCellForegroundInternal(row, column, rgb);   // 执行实际工作
    });
}

void GTable::setCellForegroundInternal(int row, int column, int rgb) {
    ensureDefaultFormatting();
    _iqtableview->item(row, column)->setForeground(QBrush(QColor(rgb)));
}

void GTable::setCellForeground(int row, int column, const std::string& color) {
    checkIndex("setCellForeground", row, column);
    setCellForeground(row, column, GColor::convertColorToRGB(color));
}

void GTable::setColor(int rgb) {
    setForeground(rgb);
}

void GTable::setColor(const std::string& color) {
    setForeground(color);
}

void GTable::setColumnAlignment(int column, HorizontalAlignment alignment) {
    checkColumn("setColumnAlignment", column);

    GThread::runOnQtGuiThread([this, column, alignment]() {
        // 将此对齐方式保存到列样式中（供 resize() 等操作后的单元格使用）
        ensureColumnStyle(column);
        _columnStyles[column].alignment = alignment;

        // 设置该列中每个单元格的对齐方式
        for (int row = 0, nr = numRows(); row < nr; row++) {
            setCellAlignmentInternal(row, column, alignment);
        }
    });
}

void GTable::setColumnBackground(int column, int rgb) {
    checkColumn("setColumnBackground", column);

    GThread::runOnQtGuiThread([this, column, rgb]() {
        // 将此背景色保存到列样式中（供 resize() 等操作后的单元格使用）
        ensureColumnStyle(column);
        _columnStyles[column].background = rgb;

        // 设置该列中每个单元格的背景色
        for (int row = 0, nr = numRows(); row < nr; row++) {
            setCellBackgroundInternal(row, column, rgb);
        }
    });
}

void GTable::setColumnBackground(int column, const std::string& color) {
    setColumnBackground(column, GColor::convertColorToRGB(color));
}

void GTable::setColumnFont(int column, const std::string& font) {
    checkColumn("setColumnFont", column);

    GThread::runOnQtGuiThread([this, column, font]() {
        // 将此字体保存到列样式中（供 resize() 等操作后的单元格使用）
        ensureColumnStyle(column);
        _columnStyles[column].font = font;

        // 设置该列中每个单元格的字体
        for (int row = 0, nr = numRows(); row < nr; row++) {
            setCellFontInternal(row, column, font);
        }
    });
}

void GTable::setColumnForeground(int column, int rgb) {
    checkColumn("setColumnForeground", column);

    GThread::runOnQtGuiThread([this, column, rgb]() {
        // 将此前景色保存到列样式中（供 resize() 等操作后的单元格使用）
        ensureColumnStyle(column);
        _columnStyles[column].foreground = rgb;

        // 设置该列中每个单元格的前景色
        for (int row = 0, nr = numRows(); row < nr; row++) {
            setCellForegroundInternal(row, column, rgb);
        }
    });
}

void GTable::setColumnForeground(int column, const std::string& color) {
    setColumnForeground(column, GColor::convertColorToRGB(color));
}

void GTable::setColumnHeaderStyle(GTable::ColumnHeaderStyle style) {
    GThread::runOnQtGuiThread([this, style]() {
        _columnHeaderStyle = style;
        if (style == GTable::COLUMN_HEADER_NONE) {
            // 没有表头
            setRowColumnHeadersVisible(false);
            return;
        } else {
            // 构建要显示的列名列表
            updateColumnHeaders();
            _iqtableview->horizontalHeader()->setVisible(true);
            _iqtableview->verticalHeader()->setVisible(true);
        }
    });
}

void GTable::setColumnWidth(int column, double width) {
    checkColumn("setColumnWidth", column);
    if (width < 0) {
        error("GTable::setColumnWidth: width cannot be negative");
    }
    GThread::runOnQtGuiThread([this, column, width]() {
        _iqtableview->setColumnWidth(column, (int) width);
    });
}

void GTable::setEditable(bool editable) {
    GThread::runOnQtGuiThread([this, editable]() {
        if (editable) {
            _iqtableview->setEditTriggers(
                        QAbstractItemView::CurrentChanged
                        | QAbstractItemView::DoubleClicked
                        | QAbstractItemView::EditKeyPressed
                        | QAbstractItemView::AnyKeyPressed);
        } else {
            _iqtableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
    });
}

void GTable::setEditorValue(int row, int column, const std::string& text) {
    checkIndex("setEditorValue", row, column);
    GThread::runOnQtGuiThread([this, text]() {
        _Internal_QItemDelegate* delegate = _iqtableview->getItemDelegate();
        if (delegate != nullptr) {
            QWidget* editor = delegate->getEditor();
            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor)) {
                lineEdit->setText(QString::fromStdString(text));
            }
        }
    });
}

void GTable::setFont(const QFont& font) {
    setFont(GFont::toFontString(font));
}

void GTable::setFont(const std::string& font) {
    GInteractor::setFont(font);   // 调用父类实现

    GThread::runOnQtGuiThread([this, font]() {
        // 将此字体保存到全局单元格样式中（供 resize() 等操作后的单元格使用）
        ensureDefaultFormatting();
        _globalCellStyle.font = font;

        // 从所有行/列样式中移除字体，因为它们已被
        // 现在由此全局字体样式覆盖
        TableStyle unset = TableStyle::unset();
        for (int row : _rowStyles) {
            _rowStyles[row].font = unset.font;
        }
        for (int col : _columnStyles) {
            _columnStyles[col].font = unset.font;
        }

        // 设置每个单元格的前景色
        for (int row = 0, nr = numRows(); row < nr; row++) {
            for (int col = 0, nc = numCols(); col < nc; col++) {
                setCellFontInternal(row, col, font);
            }
        }
    });
}

void GTable::setForeground(int rgb) {
    GThread::runOnQtGuiThread([this, rgb]() {
        // GInteractor::setForeground(rgb);
        // （不要调用 super；那会设置滚动条及其他所有部分的前景色）

        // 将此前景色保存到全局单元格样式中（供 resize() 等操作后的单元格使用）
        ensureDefaultFormatting();
        _globalCellStyle.foreground = rgb;

        // 从所有行/列样式中移除前景色，因为它们已被
        // 现在由此全局前景颜色样式覆盖
        TableStyle unset = TableStyle::unset();
        for (int row : _rowStyles) {
            _rowStyles[row].foreground = unset.foreground;
        }
        for (int col : _columnStyles) {
            _columnStyles[col].foreground = unset.foreground;
        }

        // 设置每个单元格的前景色
        for (int row = 0, nr = numRows(); row < nr; row++) {
            for (int col = 0, nc = numCols(); col < nc; col++) {
                setCellForegroundInternal(row, col, rgb);
            }
        }
    });
}

void GTable::setForeground(const std::string& color) {
    setForeground(GColor::convertColorToRGB(color));
}

void GTable::setHorizontalAlignment(HorizontalAlignment alignment) {
    GThread::runOnQtGuiThread([this, alignment]() {
        // 将此对齐方式保存到全局单元格样式中（供 resize() 等操作后的单元格使用）
        ensureDefaultFormatting();

        _globalCellStyle.alignment = alignment;

        // 从所有行/列样式中移除对齐设置，因为它们已被
        // 现在由此全局对齐样式覆盖
        TableStyle unset = TableStyle::unset();
        for (int row : _rowStyles) {
            _rowStyles[row].alignment = unset.alignment;
        }
        for (int col : _columnStyles) {
            _columnStyles[col].alignment = unset.alignment;
        }

        // 设置每个单元格的水平对齐方式
        for (int row = 0, nr = numRows(), nc = numCols(); row < nr; row++) {
            for (int col = 0; col < nc; col++) {
                setCellAlignmentInternal(row, col, alignment);
            }
        }
    });
}

void GTable::setRowAlignment(int row, HorizontalAlignment alignment) {
    checkRow("setRowAlignment", row);

    // 将此对齐方式保存到行样式中（供 resize() 等操作后的单元格使用）
    GThread::runOnQtGuiThread([this, row, alignment]() {
        ensureRowStyle(row);
        _rowStyles[row].alignment = alignment;

        // 设置该行中每个单元格的对齐方式
        for (int col = 0, nc = numCols(); col < nc; col++) {
            setCellAlignmentInternal(row, col, alignment);
        }
    });
}

void GTable::setRowBackground(int row, int rgb) {
    checkRow("setRowBackground", row);

    // 将此背景色保存到行样式中（供 resize() 等操作后的单元格使用）
    GThread::runOnQtGuiThread([this, row, rgb]() {
        ensureRowStyle(row);
        _rowStyles[row].background = rgb;

        // 设置该行中每个单元格的背景色
        for (int col = 0, nc = numCols(); col < nc; col++) {
            setCellBackgroundInternal(row, col, rgb);
        }
    });
}

void GTable::setRowBackground(int row, const std::string& color) {
    setRowBackground(row, GColor::convertColorToRGB(color));
}

void GTable::setRowFont(int row, const std::string& font) {
    checkRow("setRowFont", row);

    // 将此字体保存到行样式中（供 resize() 等操作后的单元格使用）
    GThread::runOnQtGuiThread([this, row, font]() {
        ensureRowStyle(row);
        _rowStyles[row].font = font;

        // 设置该行中每个单元格的字体
        for (int col = 0, nc = numCols(); col < nc; col++) {
            setCellFontInternal(row, col, font);
        }
    });
}

void GTable::setRowForeground(int row, int rgb) {
    checkRow("setRowForeground", row);

    // 将此前景色保存到行样式中（供 resize() 等操作后的单元格使用）
    GThread::runOnQtGuiThread([this, row, rgb]() {
        ensureRowStyle(row);
        _rowStyles[row].foreground = rgb;

        // 设置该行中每个单元格的前景色
        for (int col = 0, nc = numCols(); col < nc; col++) {
            setCellForegroundInternal(row, col, rgb);
        }
    });
}

void GTable::setRowForeground(int row, const std::string& color) {
    checkRow("setRowForeground", row);
    setRowForeground(row, GColor::convertColorToRGB(color));
}

void GTable::setRowColumnHeadersVisible(bool visible) {
    GThread::runOnQtGuiThread([this, visible]() {
        _iqtableview->horizontalHeader()->setVisible(visible);
        _iqtableview->verticalHeader()->setVisible(visible);
    });
}

void GTable::setRowHeight(int row, double height) {
    checkRow("setRowHeight", row);
    if (height < 0) {
        error("GTable::setRowHeight: height cannot be negative");
    }
    GThread::runOnQtGuiThread([this, row, height]() {
        _iqtableview->setRowHeight(row, (int) height);
    });
}

void GTable::setSelectedCellValue(const std::string& text) {
    if (hasSelectedCell()) {
        GridLocation loc = getSelectedCell();
        set(loc.row, loc.col, text);
    }
}

void GTable::setTableListener(GEventListener func) {
    setEventListeners({"table",
                       "tableupdate",
                       "tableselect",
                       "tableeditbegin",
                       "tablereplacebegin",
                       "tablecut",
                       "tablecopy",
                       "tablepaste"}, func);
}

void GTable::setTableListener(GEventListenerVoid func) {
    setEventListeners({"table",
                       "tableupdate",
                       "tableselect",
                       "tableeditbegin",
                       "tablereplacebegin",
                       "tablecut",
                       "tablecopy",
                       "tablepaste"}, func);
}

std::string GTable::toExcelColumnName(int col) {
    // 将列转换为近似的 Excel 26 进制列名，
    // 例如 0 -> “A”，1 -> “B”，26 -> “AA”，...
    std::string colStr;
    col = col + 1;   // 从 1 开始
    while (col-- > 0) {
        colStr = charToString((char) ('A' + (col % 26))) + colStr;
        col /= 26;
    }
    return colStr;
}

void GTable::updateColumnHeaders() {
    GThread::runOnQtGuiThread([this]() {
        if (_columnHeaderStyle == GTable::COLUMN_HEADER_NONE) {
            return;
        }

        // Qt 要求将表头放入字符串列表，显然
        // 你可以像使用 ostream 一样用 << 向列表添加内容（唉）
        QStringList columnHeaders;
        for (int col = 0, nc = numCols(); col < nc; col++) {
            if (_columnHeaderStyle == GTable::COLUMN_HEADER_EXCEL) {
                columnHeaders << QString::fromStdString(toExcelColumnName(col));
            } else {
                // style == GTable::COLUMN_HEADER_NUMERIC
                columnHeaders << QString::fromStdString(std::to_string(col));
            }
        }
        _iqtableview->setHorizontalHeaderLabels(columnHeaders);
    });
}

int GTable::width() const {
    return numCols();
}


_Internal_QItemDelegate::_Internal_QItemDelegate(QObject* parent)
        : QStyledItemDelegate(parent),
          _editor(nullptr) {
    // 空
}

QWidget* _Internal_QItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    QWidget* editor = QStyledItemDelegate::createEditor(parent, option, index);
    _Internal_QItemDelegate* hack = (_Internal_QItemDelegate*) this;
    hack->_editor = editor;
    return editor;
}

void _Internal_QItemDelegate::destroyEditor(QWidget* editor, const QModelIndex& index) const {
    _Internal_QItemDelegate* hack = (_Internal_QItemDelegate*) this;
    hack->_editor = nullptr;
    QStyledItemDelegate::destroyEditor(editor, index);
}

QWidget* _Internal_QItemDelegate::getEditor() const {
    return _editor;
}


_Internal_QTableWidget::_Internal_QTableWidget(GTable* gtable, int rows, int columns, QWidget* parent)
        : QTableWidget(rows, columns, parent),
          _gtable(gtable),
          _delegate(nullptr) {
    require::nonNull(gtable, "_Internal_QTableWidget::constructor");
    setObjectName(QString::fromStdString("_Internal_QTableWidget_" + std::to_string(gtable->getID())));
    _delegate = new _Internal_QItemDelegate();
    setItemDelegate(_delegate);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(this, SIGNAL(cellChanged(int, int)), this, SLOT(handleCellChange(int, int)));
    connect(this, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(handleCellDoubleClick(int, int)));
    connect(this->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(handleSelectionChange(const QItemSelection&, const QItemSelection&)));
}

void _Internal_QTableWidget::detach() {
    _gtable = nullptr;
}

bool _Internal_QTableWidget::edit(const QModelIndex& index, QAbstractItemView::EditTrigger trigger, QEvent* event) {
    bool result = QAbstractItemView::edit(index, trigger, event);   // 调用父类实现
    if (!_gtable) {
        return result;
    }
    if (result) {
        bool isEdit = _lastKeyPressed == 0 || _lastKeyPressed == Qt::Key_F2 || _lastKeyPressed == Qt::Key_Tab;
        _lastKeyPressed = 0;
        if (isEdit) {
            fireTableEvent(TABLE_EDIT_BEGIN, "tableeditbegin", index.row(), index.column());
        } else {
            fireTableEvent(TABLE_REPLACE_BEGIN, "tablereplacebegin", index.row(), index.column());
        }
    }
    return result;
}

void _Internal_QTableWidget::fireTableEvent(EventType eventType, const std::string& eventName, int row, int col) {
    if (!_gtable) {
        return;
    }
    GEvent tableEvent(
                /* 类  */ TABLE_EVENT,
                /* 类型   */ eventType,
                /* 名称   */ eventName,
                /* 来源 */ _gtable);
    if (row < 0 && col < 0) {
        tableEvent.setRowAndColumn(_gtable->getSelectedRow(), _gtable->getSelectedColumn());
    } else {
        tableEvent.setRowAndColumn(row, col);
    }
    tableEvent.setActionCommand(_gtable->getActionCommand());
    _gtable->fireEvent(tableEvent);
}

QWidget* _Internal_QTableWidget::getEditor() const {
    return _delegate->getEditor();
}

_Internal_QItemDelegate* _Internal_QTableWidget::getItemDelegate() const {
    return _delegate;
}

bool _Internal_QTableWidget::isEditing() const {
    return getEditor() != nullptr;
}

void _Internal_QTableWidget::closeEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint) {
    QTableWidget::closeEditor(editor, hint);
    if (!_gtable) {
        return;
    }
    // TODO：即使编辑已提交，这也会触发吗？
    fireTableEvent(TABLE_EDIT_CANCEL, "tableeditcancel");
}

void _Internal_QTableWidget::handleCellChange(int row, int column) {
    if (!_gtable) {
        return;
    }
    fireTableEvent(TABLE_UPDATED, "tableupdate", row, column);
}

void _Internal_QTableWidget::handleCellDoubleClick(int /*行*/, int /*列*/) {
    if (!_gtable) {
        return;
    }
    _lastKeyPressed = Qt::Key_F2;   // 模拟按下 F2
    // edit() 将触发编辑/替换开始事件
    // fireTableEvent(GEvent::TABLE_EDIT_BEGIN, "tableeditbegin", row, column);
}

void _Internal_QTableWidget::handleSelectionChange(const QItemSelection& selected, const QItemSelection& /*未选中*/) {
    if (!_gtable) {
        return;
    }
    QItemSelectionRange range;
    if (!selected.empty()) {
        range = selected.at(0);
        QPersistentModelIndex index = range.topLeft();
        fireTableEvent(TABLE_SELECTED, "tableselect", index.row(), index.column());
    }
}

void _Internal_QTableWidget::keyPressEvent(QKeyEvent* event) {
    require::nonNull(event, "_Internal_QTableWidget::keyPressEvent", "event");
    if (!_gtable) {
        QTableWidget::keyPressEvent(event);   // 调用父类实现
        return;
    }
    _lastKeyPressed = event->key();
    bool wasEditing = isEditing();
    if (!wasEditing && event->key() == Qt::Key_Delete) {
        // 清除所选单元格中的数据
        if (_gtable->hasSelectedCell()) {
            GridLocation loc = _gtable->getSelectedCell();
            _gtable->clearCell(loc.row, loc.col);
            return;
        }
    }

    // 任何其他按键
    if (wasEditing || !_gtable->hasSelectedCell()) {
        QTableWidget::keyPressEvent(event);   // 调用父类实现
        return;
    }

    bool nowEditing = isEditing();

    if (GClipboard::isCut(event)) {
        // 键盘“剪切”命令；从单元格移除数据并放入剪贴板
        GridLocation loc = _gtable->getSelectedCell();
        std::string cellValue = _gtable->get(loc.row, loc.col);
        GClipboard::set(cellValue);
        _gtable->clearCell(loc.row, loc.col);
        QTableWidget::keyPressEvent(event);   // 调用父类实现
        fireTableEvent(TABLE_CUT, "tablecut");
        return;
    }

    if (GClipboard::isCopy(event)) {
        // 键盘“复制”命令；将单元格数据复制到剪贴板
        std::string cellValue = _gtable->getSelectedCellValue();
        GClipboard::set(cellValue);
        QTableWidget::keyPressEvent(event);   // 调用父类实现
        fireTableEvent(TABLE_COPY, "tablecopy");
        return;
    }

    if (GClipboard::isPaste(event)) {
        // 键盘“粘贴”命令；将剪贴板数据复制到单元格
        std::string cellValue = GClipboard::get();
        _gtable->setSelectedCellValue(cellValue);
        QTableWidget::keyPressEvent(event);   // 调用父类实现
        fireTableEvent(TABLE_PASTE, "tablepaste");
        return;
    }

    // 如果单元格从非编辑状态变为编辑状态，则编辑已开始
    if (nowEditing) {
        if (event->key() == Qt::Key_F2) {
            // F2 键开始编辑单元格的现有值
            // edit() 方法将触发 edit_begin
            // fireTableEvent(GEvent::TABLE_EDIT_BEGIN, "tableeditbegin");
        } else if (event->key() == Qt::Key_Tab) {
            // Tab 键跳转到编辑相邻单元格
        } else {
            // 任何其他文本会开始用新值替换该值
            // replace_begin 将由 edit() 方法触发
            // fireTableEvent(GEvent::TABLE_REPLACE_BEGIN, "tablereplacebegin");
        }
    }
    QTableWidget::keyPressEvent(event);   // 调用父类实现
}

QSize _Internal_QTableWidget::sizeHint() const {
    if (hasPreferredSize()) {
        return getPreferredSize();
    } else {
        return QTableWidget::sizeHint();
    }
}


