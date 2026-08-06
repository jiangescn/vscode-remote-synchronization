#ifndef MiniData_CSV_Included
#define MiniData_CSV_Included

#include <vector>
#include <unordered_map>
#include <string>
#include <istream>
#include <stdexcept>

/* 表示从带标题行的 CSV 文件中读取的数据类型。访问方式为
 * 以 csv[row][column] 形式提供，其中 column 可由整数或以下方式指定：
 * 或作为某个列标题。
 */
class CSV {
public:
    /* 解析例程。 */
    inline static CSV parse(std::istream& source);
    inline static CSV parseFile(const std::string& filename);

    /* 基本访问器。 */
    inline std::size_t numRows() const;   // 不包含标题
    inline std::size_t numCols() const;
    
    /* 头部信息。 */
    inline std::vector<std::string> headers() const;

    /* 访问器代理类。 */
    class RowRef {
    public:
        inline std::string operator[] (std::size_t col) const;
        inline std::string operator[] (const std::string& colHeader) const;
    
    private:
        inline RowRef(const CSV* parent, std::size_t row);
        const CSV* mParent;
        std::size_t mRow;

        friend class CSV;
    };
    
    inline RowRef operator[] (std::size_t col) const;

private:
    /* 数据。内部表示为字符串二维网格，并附带
     * 辅助列标题数据。
     *
     * 网格本身按行优先顺序表示，不包含
     * 列标题。
     */
    std::vector<std::string> mData;
    std::size_t              mRows;

    /* 列标题编码为从标题到索引的映射，因为
     * 主要支持的操作是从名称映射到列。
     */
    std::unordered_map<std::string, std::size_t> mColumnHeaders;
};

/* 表示由 CSV 问题引起的错误类型。 */
class CSVException: public std::logic_error {
public:
    inline CSVException(const std::string& message);
};







/* * * * * 此处以下为实现部分 * * * * */

#include <sstream>
#include <fstream>
#include <tuple>

namespace MiniData_CSVImpl {
    /* 报告错误。 */
    [[ noreturn ]] inline void csvError(const std::string& message) {
        throw CSVException(message);
    }

    /* 从源中读取一个 CSV 词元。每个词元要么
     *
     *  1. 不以引号开头，此时读取到第一个逗号为止；或者
     *  2. 以引号开头，此时读取到接下来的右引号，并注意
     *     并在途中处理转义引号。
     *
     * 允许空条目。
     */
    inline std::string readOneTokenFrom(std::istream& input) {
        /* 边界情况：允许空条目。 */
        if (input.peek() == ',') return "";
        
        /* 若开头不是引号，则读取到引号为止。 */
        if (input.peek() != '"') {
            std::string result;           
            while (true) {
                int ch = input.peek();
                if (ch == EOF) return result;
                if (ch == ',') return result;
                result += char(input.get());
            }
        }
        
        /* 当前正在读取带引号的字符串。继续读取字符，同时注意右引号
         * 引号可能并不是真正的字符串结束标记。
         */
        input.get(); // 跳过引号
        
        std::string result;
        while (true) {
            int ch = input.get();
            
            if (ch == EOF) csvError("Unterminated string literal.");
            else if (ch != '"') result += char(ch);
            else {
                int next = input.peek();
                if (next == EOF || next == ',') return result; // 词元结束
                else if (next == '"') {
                    /* 读取并跳过此字符，以免重复处理。 */
                    input.get();
                    result += '"';
                } else csvError("Unexpected character found after quote.");
            }
        }
    }

    /* 将 CSV 文件的一行词元化，返回该行中的词元列表。 */
    inline std::vector<std::string> tokenize(const std::string& line) {
        /* 边界情况：假定不存在空行，尽管理论上可以
         * 设想一个 0 × n 的数据数组。这通常表示出了问题。
         */
        if (line.empty()) csvError("Empty line in CSV data.");
    
        /* 转换为流，以便像处理流一样处理这些字符。 */
        std::istringstream input(line);
        
        std::vector<std::string> result;
        while (true) {
            result.push_back(readOneTokenFrom(input));
            
            /* 此时应当看到逗号或 EOF。 */
            if (input.peek() == EOF) return result;
            if (input.get()  != ',') csvError("Entries in CSV file aren't comma-separated?");
        }
    }

    /* 读取 CSV 文件第一行，并将其拆分为标题。 */
    inline std::unordered_map<std::string, std::size_t> readHeaders(std::istream& input) {
        std::string line;
        if (!std::getline(input, line)) csvError("Could not read header row from CSV source.");
        
        std::unordered_map<std::string, std::size_t> result;
        for (auto token: tokenize(line)) {
            if (result.count(token)) csvError("Duplicate column header: " + token);
            
            std::size_t index = result.size();
            result[token] = index;
        }
        
        return result;
    }
    
    /* 读取 CSV 文件正文，并假定其具有一定数量的
     * 列。
     *
     * 结果由数据的行优先序列和以下内容配对组成：
     * 数据中的行数。
     */
    inline std::tuple<std::vector<std::string>, std::size_t> readBody(std::istream& input, std::size_t numCols) {
        /* 先将网格构建为 vector<vector<string>>，最后再折叠。 */
        std::vector<std::vector<std::string>> lines;
        for (std::string line; std::getline(input, line); ) {
            auto tokens = tokenize(line);
            if (tokens.size() != numCols) csvError("Lines have varying number of entries.");
            
            lines.push_back(tokens);
        }
        
        /* 展平该列表。 */
        std::vector<std::string> result;
        for (std::size_t row = 0; row < lines.size(); row++) {
            for (std::size_t col = 0; col < numCols; col++) {
                result.push_back(lines[row][col]);
            }
        }
        return std::make_tuple(result, lines.size());
    }
}

inline CSV CSV::parse(std::istream& input) {
    CSV result;

    result.mColumnHeaders = MiniData_CSVImpl::readHeaders(input);
    std::tie(result.mData, result.mRows) = MiniData_CSVImpl::readBody(input, result.mColumnHeaders.size());

    return result;
}

inline CSV CSV::parseFile(const std::string& filename) {
    std::ifstream input(filename);
    if (!input) MiniData_CSVImpl::csvError("Cannot open file " + filename);

    return CSV::parse(input);
}

inline size_t CSV::numRows() const {
    return mRows;
}

inline size_t CSV::numCols() const {
    return mColumnHeaders.size();
}

inline std::vector<std::string> CSV::headers() const {
    std::vector<std::string> result(mColumnHeaders.size());
    for (const auto& entry: mColumnHeaders) {
        result[entry.second] = entry.first;
    }
    return result;
}

inline CSV::RowRef CSV::operator[] (std::size_t row) const {
    if (row >= numRows()) MiniData_CSVImpl::csvError("Row out of range.");
    
    return RowRef(this, row);
}

inline CSV::RowRef::RowRef(const CSV* parent, std::size_t row) : mParent(parent), mRow(row) {

}

inline std::string CSV::RowRef::operator[] (std::size_t col) const {
    if (col >= mParent->numCols()) MiniData_CSVImpl::csvError("Column out of range.");
    
    return mParent->mData[mParent->numCols() * mRow + col];
}
inline std::string CSV::RowRef::operator[] (const std::string& colHeader) const {
    auto itr = mParent->mColumnHeaders.find(colHeader);
    if (itr == mParent->mColumnHeaders.end()) MiniData_CSVImpl::csvError("Column not found: " + colHeader);

    return (*this)[itr->second];
}

inline CSVException::CSVException(const std::string& message) : std::logic_error(message) {
    // 已在初始化列表中处理
}

#endif
