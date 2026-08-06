/*
 * 文件：gridlocation.h
 * --------------------
 * 此文件导出 <code>GridLocation</code> 结构体，它是一个小型
 * 表示行和列的结构。
 * 行/列值允许为负数或越界；如果
 * 如果向网格传入越界位置，网格会抛出错误。
 *
 * <code>Grid</code> 和 <code>SparseGrid</code> 类的若干成员
 * 已进行改造，可接受 <code>GridLocation</code> 来代替整数
 * 用于行/列索引。
 *
 * 此文件还声明了 <code>GridLocationRange</code> 类，
 * 它表示可循环遍历的二维网格位置范围。
 *
 * 每个成员的实现见 gridlocation.cpp。
 */

#ifndef _gridlocation_h
#define _gridlocation_h

#include <iostream>
#include <iterator>
#include <string>

#include "error.h"

class GridLocationRange;   // 前向声明

struct GridLocation {
public:

    /*
     * 构造表示给定行和列的位置。
     * 允许任何索引，包括负数和越界索引。
     */
    GridLocation(int row, int col);

    /*
     * 构造默认位置 0, 0。
     */
    GridLocation();

    /*
     * 返回此位置的字符串表示，例如 "r2c17"。
     */
    std::string toString() const;

    /* 行和列数据——可直接访问或修改 */
    int row;
    int col;
};

/*
 * 返回此网格位置的整数哈希码。
 */
int hashCode(const GridLocation& loc);

/*
 * 用于比较网格位置的关系运算符。
 */
bool operator <(const GridLocation& loc1, const GridLocation& loc2);
bool operator <=(const GridLocation& loc1, const GridLocation& loc2);
bool operator ==(const GridLocation& loc1, const GridLocation& loc2);
bool operator !=(const GridLocation& loc1, const GridLocation& loc2);
bool operator >(const GridLocation& loc1, const GridLocation& loc2);
bool operator >=(const GridLocation& loc1, const GridLocation& loc2);

/*
 * 用于按 toString 格式读取或写入位置的 I/O 流运算符。
 */
std::ostream& operator <<(std::ostream& out, const GridLocation& loc);
std::istream& operator >>(std::istream& input, GridLocation& loc);


/*
 * 表示网格位置范围。
 * 实际的各网格位置不会全部创建并存储在
 * 此对象；那将需要大量内存。
 * 相反，我们主要使用此类对给定范围进行 for-each 循环
 * 使用其内部迭代器遍历位置。
 *
 * 常见用法模式：
 * GridLocationRange range(0, 0, 10, 5);
 * for (GridLocation loc : range) { ... }
 *
 * 或者，如果有 Grid 集合，其 locations() 方法会返回 GridLocationRange
 * 可直接循环遍历的对象。
 *
 * for (GridLocation loc : grid.locations()) { ... }
 */
class GridLocationRange {
private:
    /*
     * 索引范围的内部迭代器。
     */
    class GridLocationRangeIterator : public std::iterator<std::input_iterator_tag, GridLocation> {
    private:
        const GridLocationRange* glr;
        GridLocation loc;

    public:
        GridLocationRangeIterator(const GridLocationRange* glr, bool end)
                : glr(glr) {
            if (end) {
                loc.row = glr->endRow() + 1;
                loc.col = glr->endCol() + 1;
            } else {
                loc = glr->startLocation();
            }
        }

        GridLocationRangeIterator(const GridLocationRangeIterator& itr)
                : glr(itr.glr),
                  loc(itr.loc) {
            // 空
        }

        GridLocationRangeIterator& operator ++() {
            if (glr->isRowMajor()) {
                loc.col++;
                if (loc.col > glr->endCol()) {
                    loc.col = glr->startCol();
                    loc.row++;
                }
            } else {
                loc.row++;
                if (loc.row > glr->endRow()) {
                    loc.row = glr->startRow();
                    loc.col++;
                }
            }
            if (!glr->contains(loc)) {
                loc.row = glr->endRow() + 1;
                loc.col = glr->endCol() + 1;
            }
            return *this;
        }

        GridLocationRangeIterator operator ++(int) {
            GridLocationRangeIterator copy(*this);
            operator++();
            return copy;
        }

        GridLocationRangeIterator& operator --() {
            if (glr->isRowMajor()) {
                loc.col--;
                if (loc.col < glr->startCol()) {
                    loc.col = glr->endCol();
                    loc.row--;
                }
            } else {
                loc.row--;
                if (loc.row < glr->startRow()) {
                    loc.row = glr->endRow();
                    loc.col--;
                }
            }
            return *this;
        }

        GridLocationRangeIterator operator --(int) {
            GridLocationRangeIterator copy(*this);
            operator--();
            return copy;
        }

        bool operator ==(const GridLocationRangeIterator& rhs) const {
            return loc == rhs.loc;
        }

        bool operator !=(const GridLocationRangeIterator& rhs) const {
            return !(*this == rhs);
        }

        bool operator <(const GridLocationRangeIterator& rhs) const {
            if (glr != rhs.glr) {
                error("GridLocationRange Iterator::operator <: Iterators are in different ranges");
            }
            return loc < rhs.loc;
        }

        bool operator <=(const GridLocationRangeIterator& rhs) const {
            if (glr != rhs.glr) {
                error("GridLocationRange Iterator::operator <=: Iterators are in different ranges");
            }
            return loc <= rhs.loc;
        }

        bool operator >(const GridLocationRangeIterator& rhs) const {
            if (glr != rhs.glr) {
                error("GridLocationRange Iterator::operator >: Iterators are in different ranges");
            }
            return loc > rhs.loc;
        }

        bool operator >=(const GridLocationRangeIterator& rhs) const {
            if (glr != rhs.glr) {
                error("GridLocationRange Iterator::operator >=: Iterators are in different ranges");
            }
            return loc >= rhs.loc;
        }

        const GridLocation& operator *() const {
            return loc;
        }

        const GridLocation* operator ->() const {
            return &loc;
        }
    };

    GridLocation _start;
    GridLocation _end;
    bool _isRowMajor;

public:
    /*
     * 在给定起止位置上构造闭区间范围。
     * isRowMajor 标志指示我们是否按以下顺序遍历范围：
     * 行优先顺序（true，默认）或列优先顺序（false）。
     */
    GridLocationRange(int startRow = 0, int startCol = 0, int endRow = 0, int endCol = 0, bool isRowMajor = true);

    /*
     * 在给定起止位置上构造闭区间范围。
     * isRowMajor 标志指示我们是否按以下顺序遍历范围：
     * 行优先顺序（true，默认）或列优先顺序（false）。
     */
    GridLocationRange(const GridLocation& startLoc, const GridLocation& endLoc, bool isRowMajor = true);

    /*
     * 返回遍历该范围的迭代器。
     */
    GridLocationRangeIterator begin() const;

    /*
     * 如果此范围完全包含给定另一范围，则返回 true。
     */
    bool contains(const GridLocation& loc) const;

    /*
     * 返回位于范围末尾的迭代器。
     */
    GridLocationRangeIterator end() const;

    /*
     * 返回此范围中的最后一列（含）。
     */
    int endCol() const;

    /*
     * 返回此范围中的最后一个行/列位置（含）。
     */
    const GridLocation& endLocation() const;

    /*
     * 返回此范围中的最后一行（含）。
     */
    int endRow() const;

    /*
     * 如果此范围不包含任何行或列，则返回 true。
     */
    bool isEmpty() const;

    /*
     * 如果应按行优先顺序遍历此范围，则返回 true，
     * 按构造时指定（默认 true）。
     */
    bool isRowMajor() const;

    /*
     * 返回此范围中的第一列。
     */
    int startCol() const;

    /*
     * 返回此范围中的第一个行/列位置。
     */
    const GridLocation& startLocation() const;

    /*
     * 返回此范围中的第一行。
     */
    int startRow() const;

    /*
     * 返回此范围的字符串表示，
     * 例如 "[r1c3 .. r4c7]"。
     */
    std::string toString() const;
};

/*
 * 用于按 toString 格式写入位置范围的 I/O 流运算符。
 */
std::ostream& operator <<(std::ostream& out, const GridLocationRange& range);

#endif // _gridlocation_h
