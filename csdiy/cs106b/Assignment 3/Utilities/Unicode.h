#ifndef MiniData_Unicode_Included
#define MiniData_Unicode_Included

#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iterator>

/* 给定 UTF-8 编码流，从中提取一个字符。若该流
 * 不包含字符的正确编码——包括已到达 EOF 的情况——此时会报告
 * 通过抛出 UTFException 报告错误。
 */
inline char32_t readChar(std::istream& source);

/* 给定 UTF-8 编码流，查看流中的下一个字符但不取出。若该流
 * 不包含字符的正确编码——包括已到达 EOF 的情况——此时会报告
 * 通过抛出 UTFException 报告错误。
 */
inline char32_t peekChar(std::istream& source);

/* 给定 UTF-32 的 Unicode 字符，返回该字符的 UTF-8 表示。 */
inline std::string toUTF8(char32_t ch);

/* 给定表示单个 UTF-8 字符的字符串，返回其 char32_t 表示
 * 该字符。若字符串不表示单个 UTF-8 字符，则抛出
 * UTFException。
 */
inline char32_t fromUTF8(const std::string& ch);

/* 给定 UTF-32 的 Unicode 字符，返回表示一系列 UTF-16 单元的字符串 
 * 该字符的转义序列。此字符串具有以下格式之一：
 * \uXXXX（用于不需要代理项的字符），或 \uXXXX\uXXXX（用于以下字符：
 * 执行。）
 */
inline std::string utf16EscapeFor(char32_t ch);

/* 给定一个指向形如 \uHHHH 的转义序列的字符串（代理对则为 \uHHHH\uHHHH），
 * 代理项对），读取转义序列并返回所得字符。若
 * 流不包含这种格式的序列——包括已到达 EOF——
 * 此时通过抛出 UTFException 报告错误。
 */
inline char32_t readUTF16EscapedChar(std::istream& source);

/* 表示 UTF 编码期间产生的异常类型。 */
class UTFException: public std::logic_error {
public:
    inline UTFException(const std::string& message);
};

/* 支持遍历字符串中字符的包装类型。此类型
 * 允许写出类似以下内容：
 *
 *     for (char32_t ch: utf8Reader(str)) {
 *          ...
 *     }
 */
class utf8Reader {
public:
    explicit utf8Reader(const std::string& str) : in(str) {}

    class const_iterator;
    const_iterator begin();
    const_iterator end();

private:
    std::istringstream in;
    friend class const_iterator;
};










/* * * * * 此处以下为实现部分 * * * * */

#include <sstream>
#include <iomanip>
#include <cctype>

namespace MiniData_UnicodeImpl {
    /* 报告 UTF 错误。 */
    [[ noreturn ]] inline void utfError(const std::string& message) {
        throw UTFException(message);
    }

    /* 从流中获取下一个原始字符；若无法获取，则调用 error() 报错。 */
    inline char get(std::istream& input) {
        char result;
        if (!input.get(result)) utfError("Unexpected end of stream.");

        return result;
    }
    
    /* 返回给定字节是否为后续字节（即以 10 开头的字节）。 */
    inline bool isFollowByte(char byte) {
        return (byte & 0b11000000) == 0b10000000;
    }
    
    /* 将给定字符转换为十六进制值。 */
    inline std::string toHex(char ch) {
        std::ostringstream builder;
        builder << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(ch));
        return builder.str();
    }
    
    /* 给定 UTF-8 编码流，读取组成单个 Unicode 字符的字节
     * 字符。
     */
    inline std::string nextBytesFrom(std::istream& source) {
        char header = get(source);
        std::string result(1, header);
        
        /* 若此字符未设置最高位，则只需读取这些内容。 */
        if ((header & 0b10000000) == 0) return result;
        
        /* 否则，确定需要读取多少个字符。 */
        std::size_t followBytes = 0;
        if      ((header & 0b11100000) == 0b11000000) followBytes = 1;
        else if ((header & 0b11110000) == 0b11100000) followBytes = 2;
        else if ((header & 0b11111000) == 0b11110000) followBytes = 3;
        else utfError("Byte header doesn't match UTF-8 patterns.");
        
        for (std::size_t i = 0; i < followBytes; i++) {
            char next = get(source);
            if (!isFollowByte(next)) utfError("Expected follow byte, got " + toHex(next));
            
            result += next;
        }
        
        return result;        
    }
    
    /* 给定表示 UTF-8 编码字符字节的字符串，解码这些字节
     * 将字节组合成单个字符。
     */
    inline char32_t decode(const std::string& bytes) {
        if (bytes.empty()) utfError("Empty byte string?");
        
        /* 若第一个字节以零位开头，则原样返回。 */
        if ((bytes[0] & 0b10000000) == 0) {
            if (bytes.size() != 1) utfError("Wrong number of bytes for 7-bit code point.");
            
            return bytes[0];
        }
        
        /* 若第一个字节以 110xxxxx 开头，则需要解码一个 11 位数
         * 格式为 110bbbbb 10bbbbbb
         */
        if ((bytes[0] & 0b11100000) == 0b11000000) {
            if (bytes.size() != 2) utfError("Wrong number of bytes for 11-bit code point.");
            if (!isFollowByte(bytes[1])) utfError("Paired byte has wrong header.");
            
            return ((bytes[0] & 0b00011111) << 6) +
                   ((bytes[1] & 0b00111111) << 0);
        }
        
        /* 若第一个字节以 1110xxxx 开头，则需要解码一个 16 位数
         * 格式为 1110bbbb 10bbbbbb 10bbbbbb。
         */
        if ((bytes[0] & 0b11110000) == 0b11100000) {
            if (bytes.size() != 3) utfError("Wrong number of bytes for 16-bit code point.");
            if (!isFollowByte(bytes[1])) utfError("First paired byte has wrong header.");
            if (!isFollowByte(bytes[2])) utfError("Second paired byte has wrong header.");
            
            return ((bytes[0] & 0b00001111) << 12) + 
                   ((bytes[1] & 0b00111111) <<  6) +
                   ((bytes[2] & 0b00111111) <<  0);
        }
        
        /* 若第一个字节以 11110xxx 开头，则需要解码一个 21 位数
         * 格式为 11110bbb 10bbbbbb 10bbbbbb 10bbbbbb。
         */
        if ((bytes[0] & 0b11111000) == 0b11110000) {
            if (bytes.size() != 4) utfError("Wrong number of bytes for 21-bit code point.");
            if (!isFollowByte(bytes[1])) utfError("First paired byte has wrong header.");
            if (!isFollowByte(bytes[2])) utfError("Second paired byte has wrong header.");
            if (!isFollowByte(bytes[3])) utfError("Third paired byte has wrong header.");
            
            return ((bytes[0] & 0b00000111) << 18) + 
                   ((bytes[1] & 0b00111111) << 12) +
                   ((bytes[2] & 0b00111111) <<  6) +
                   ((bytes[3] & 0b00111111) <<  0);
        }
        
        utfError("Not sure how to handle byte " + toHex(bytes[0]));
    }
    
    /* 给定 16 位值，写出其转义序列。 */
    inline std::string oneEscapeUTF16For(uint16_t value) {
        std::ostringstream builder;
        builder << "\\u" << std::hex << std::setfill('0') << std::setw(4) << value;
        return builder.str();
    }
    
    /* 给定需要代理项对的字符，返回两个代理分量。 */
    inline uint16_t highSurrogateFor(char32_t ch) {
        return ((ch - 0x10000) >> 10) + 0xD800;            // 高 10 位
    }
    inline uint16_t lowSurrogateFor(char32_t ch) {
        return ((ch - 0x10000) & 0b1111111111) + 0xDC00;   // 低 10 位
    }
    
    /* 给定代理项对，将其重新组合成单个 Unicode 字符。 */
    inline char32_t assembleSurrogates(uint16_t high, uint16_t low) {
        return ((high - 0xD800) << 10) + (low - 0xDC00) + 0x10000;
    }
    
    /* 给定一个流，读取形如 \uXXXX 的转义序列并返回其值
     * 以这种方式编码。它可能是代理项对的一部分，因此返回值可能并不
     * 实际上是有效字符。
     */
    inline char32_t readOneUTF16Escape(std::istream& input) {
        /* 确认开头为 \u。 */
        if (get(input) != '\\') utfError("Expected \\u.");
        if (get(input) != 'u')  utfError("Expected \\u.");
        
        /* 读取四个十六进制字节。 */
        std::string builder;
        for (int i = 0; i < 4; i++) {
            char next = get(input);
            if (!isxdigit(next)) utfError("Expected hexadecimal digit, got " + std::string(1, next));
            
            builder += next;
        }
        
        /* 将这些字节转换为整数。 */
        return char32_t(stoi(builder, nullptr, 16));
    }
}

inline char32_t readChar(std::istream& source) {
    return MiniData_UnicodeImpl::decode(MiniData_UnicodeImpl::nextBytesFrom(source));
}

inline char32_t peekChar(std::istream& source) {
    /* 读取字节并解码。 */
    auto bytes = MiniData_UnicodeImpl::nextBytesFrom(source);
    auto result = MiniData_UnicodeImpl::decode(bytes);
    
    /* 将字节放回。 */
    for (std::size_t i = 0; i < bytes.size(); i++) {
        source.unget();
        if (!source) MiniData_UnicodeImpl::utfError("Couldn't unget enough characters.");
    }
    
    return result;
}

inline std::string utf16EscapeFor(char32_t ch) {
    /* 若此字符处于可直接转换的范围，则直接转换。 */
    if (ch <= 0xD7FF || (ch >= 0xE000 && ch <= 0xFFFF)) {
        return MiniData_UnicodeImpl::oneEscapeUTF16For(ch);
    } else {
        return MiniData_UnicodeImpl::oneEscapeUTF16For(MiniData_UnicodeImpl::highSurrogateFor(ch)) +
               MiniData_UnicodeImpl::oneEscapeUTF16For(MiniData_UnicodeImpl::lowSurrogateFor(ch));
    }
}

inline char32_t readUTF16EscapedChar(std::istream& source) {
    char32_t result = MiniData_UnicodeImpl::readOneUTF16Escape(source);
    
    /* 若读取的是高代理项的一半，则读取下一半并重新组合。 */
    if (result >= 0xD800 && result <= 0xDFFF) {
        if (result >= 0xDC00) MiniData_UnicodeImpl::utfError("Read second half of surrogate pair with no matching first half?");
        
        return MiniData_UnicodeImpl::assembleSurrogates(result, MiniData_UnicodeImpl::readOneUTF16Escape(source));
    }
    
    return result;
}


inline std::string toUTF8(char32_t charCode) {
    std::ostringstream result;

    /* 占用不超过 7 位的内容直接映射为自身。 */
    if (charCode < (1u << 7)) {
        result << char(charCode);
    }
    /* 占用不超过 11 位的内容拆分为
     * 110xxxxx 10xxxxxx
     */
    else if (charCode < (1u << 11)) {
        uint32_t highFive = charCode >> 6;
        uint32_t lowSix   = charCode & 0b111111;

        result << char(highFive | 0b11000000) << char(lowSix | 0b10000000);
    }
    /* 占用不超过 16 位的内容拆分为
     * 1110xxxx 10xxxxxx 10xxxxxx
     */
    else if (charCode < (1u << 16)) {
        uint32_t highFour = charCode >> 12;
        uint32_t midSix   = (charCode >> 6) & 0b111111;
        uint32_t lowSix   = charCode & 0b111111;

        result << char(highFour | 0b11100000)
               << char(midSix | 0b10000000)
               << char(lowSix | 0b10000000);
    }
    /* 占用不超过 21 位的内容拆分为
     * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
     */
    else if (charCode < (1u << 22)) {
        uint32_t highThree = charCode >> 18;
        uint32_t topSix    = (charCode >> 12) & 0b111111;
        uint32_t midSix    = (charCode >>  6) & 0b111111;
        uint32_t lowSix    = charCode & 0b111111;

        result << char(highThree | 0b11110000)
               << char(topSix | 0b10000000)
               << char(midSix | 0b10000000)
               << char(lowSix | 0b10000000);
    }
    else {
        MiniData_UnicodeImpl::utfError("Unicode value out of range: " + std::to_string(charCode));
    }

    return result.str();
}

inline char32_t fromUTF8(const std::string& str) {
    std::istringstream input(str);
    char32_t result = readChar(input);
  
    if (input.get() != EOF) MiniData_UnicodeImpl::utfError("Unexpected bytes found in fromUTF8.");
  
    return result;
}

inline UTFException::UTFException(const std::string& message) : std::logic_error(message) {

}

class utf8Reader::const_iterator: public std::iterator<std::input_iterator_tag, const char32_t> {
public:
    const_iterator() = default;

    /* 只有当双方都是范围末尾迭代器，或双方都到达末尾时，才相等。 */
    bool operator== (const_iterator rhs) const {
        bool us   =     !owner ||     done;
        bool them = !rhs.owner || rhs.done;

        return us == them;
    }
    bool operator!= (const_iterator rhs) const {
        return !(*this == rhs);
    }

    reference operator* () const {
        return staged;
    }

    const_iterator& operator++() {
        read();
        return *this;
    }

    const_iterator operator++(int) {
        auto result = *this;
        ++*this;
        return result;
    }

private:
    const_iterator(utf8Reader* source) : owner(source) {
        if (owner) {
            read();
        } else {
            done = true;
        }
    }

    void read() {
        if (owner->in.peek() != EOF) {
            staged = readChar(owner->in);
        } else {
            done = true;
        }
    }

    friend class utf8Reader;
    utf8Reader* owner = nullptr;
    char32_t staged;
    bool done = false;
};

inline utf8Reader::const_iterator utf8Reader::begin() {
    return const_iterator(this);
}

inline utf8Reader::const_iterator utf8Reader::end() {
    return const_iterator();
}

#endif
