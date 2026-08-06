/*
 * 文件：gridlocation.cpp
 * ----------------------
 * 此文件实现 <code>GridLocation</code> 结构体中声明的成员
 * 以及 <code>GridLocationRange</code> 类。
 * 每个成员的声明见 gridlocation.h。
 *
 * @version 2018/03/12
 * - 初始版本
 */

#include "gridlocation.h"
#include <sstream>
#include "hashcode.h"

GridLocation::GridLocation(int row, int col) {
    this->row = row;
    this->col = col;
}

GridLocation::GridLocation() : GridLocation(0, 0) {}

std::string GridLocation::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

int hashCode(const GridLocation& loc) {
    return hashCode(loc.row, loc.col);
}

bool operator <(const GridLocation& loc1, const GridLocation& loc2) {
    return loc1.row < loc2.row ||
            (loc1.row == loc2.row && loc1.col < loc2.col);
}

bool operator <=(const GridLocation& loc1, const GridLocation& loc2) {
    return loc1 < loc2 || loc1 == loc2;
}

bool operator ==(const GridLocation& loc1, const GridLocation& loc2) {
    return loc1.row == loc2.row && loc1.col == loc2.col;
}

bool operator !=(const GridLocation& loc1, const GridLocation& loc2) {
    return !(loc1 == loc2);
}

bool operator >(const GridLocation& loc1, const GridLocation& loc2) {
    return loc2 < loc1;
}

bool operator >=(const GridLocation& loc1, const GridLocation& loc2) {
    return !(loc1 < loc2);
}

std::ostream& operator <<(std::ostream& out, const GridLocation& loc) {
    return out << "r" << loc.row << "c" << loc.col;
}

std::istream& operator >>(std::istream& input, GridLocation& loc) {
    // 读取 'r'
    char ch = '\0';
    input >> ch;
    if (!input || ch != 'r' ) {
        input.setstate(std::ios_base::failbit);
        return input;
    }

    // 读取行
    int row;
    if (!(input >> row)) {
        input.setstate(std::ios_base::failbit);
        return input;
    }

    // 读取 'c'
    ch = input.get();
    if (!input || ch != 'c') {
        input.setstate(std::ios_base::failbit);
        return input;
    }

    // 读取列
    int col;
    if (!(input >> col)) {
        input.setstate(std::ios_base::failbit);
        return input;
    }

    // 成功！
    loc.row = row;
    loc.col = col;
    return input;
}

GridLocationRange::GridLocationRange(int startRow, int startCol, int endRow, int endCol, bool isRowMajor)
        : _start(startRow, startCol),
          _end(endRow, endCol),
          _isRowMajor(isRowMajor) {
    // 空
}

GridLocationRange::GridLocationRange(const GridLocation& startLoc, const GridLocation& endLoc, bool isRowMajor)
        : _start(startLoc),
          _end(endLoc),
          _isRowMajor(isRowMajor) {
    // 空
}

GridLocationRange::GridLocationRangeIterator GridLocationRange::begin() const {
    return GridLocationRangeIterator(this, /* 结束 */ false);
}

bool GridLocationRange::contains(const GridLocation& loc) const {
    return _start <= loc && loc <= _end;
}

GridLocationRange::GridLocationRangeIterator GridLocationRange::end() const {
    return GridLocationRangeIterator(this, /* 结束 */ true);
}

int GridLocationRange::endCol() const {
    return _end.col;
}

const GridLocation& GridLocationRange::endLocation() const {
    return _end;
}

int GridLocationRange::endRow() const {
    return _end.row;
}

bool GridLocationRange::isEmpty() const {
    return _start > _end;
}

bool GridLocationRange::isRowMajor() const {
    return _isRowMajor;
}

int GridLocationRange::startCol() const {
    return _start.col;
}

const GridLocation& GridLocationRange::startLocation() const {
    return _start;
}

int GridLocationRange::startRow() const {
    return _start.row;
}

std::string GridLocationRange::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

std::ostream& operator <<(std::ostream& out, const GridLocationRange& range) {
    return out << range.startLocation() << " .. " << range.endLocation();
}
