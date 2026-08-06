/*
 * 文件：collections.h
 * -------------------
 * 包含可用于多种集合的通用函数。
 *
 * 例如，我们提供用于比较任何满足以下条件的集合的函数
 * 可见迭代器（begin()、end()）。
 * 用于实现集合上的 < 和 >= 等比较运算符。
 */

#ifndef _collections_h
#define _collections_h

#include <functional>
#include <iostream>
#include <sstream>
#include <type_traits>

#include "error.h"
#include "gmath.h"
#include "hashcode.h"
#include "random.h"

// 开始使用 strlib.h 中的全局命名空间字符串读写函数

/**
 * 将 infile 中的下一个字符读入引用参数 ch。
 * 若第一个非空白字符是单个
 * 或双引号，此函数会读取字符，直到遇到
 * 匹配的引号，并在此过程中处理标准转义序列。
 * 否则，readQuotedChar 会读取字符，直到遇到以下任一字符
 * 位于实现文件的字符串 STRING_DELIMITERS 中。
 *
 * @private
 */
bool readQuotedChar(std::istream& is, char& ch, bool throwOnError = true);

/**
 * 将 infile 中的下一个字符串读入引用参数 str。
 * 若第一个非空白字符是单个
 * 或双引号，此函数会读取字符，直到遇到
 * 匹配的引号，并在此过程中处理标准转义序列。
 * 否则，readQuotedString 会读取字符，直到遇到以下任一字符
 * 位于实现文件的字符串 STRING_DELIMITERS 中。
 *
 * @private
 */
bool readQuotedString(std::istream& is, std::string& str, bool throwOnError = true);

/**
 * 将字符 ch 用单引号包围后写入 outfile，并转换
 * 根据需要将特殊字符转换为转义序列。如果可选参数
 * 除非将参数 forceQuotes 显式设置为 false，否则会包含引号
 * 仅在必要时出现在输出中。
 *
 * @private
 */
std::ostream& writeQuotedChar(std::ostream& os, char ch, bool forceQuotes = true);

/**
 * 将字符串 str 用双引号包围后写入 outfile，并转换
 * 根据需要将特殊字符转换为转义序列。如果可选参数
 * 除非将参数 forceQuotes 显式设置为 false，否则会包含引号
 * 仅在必要时出现在输出中。
 *
 * @private
 */
std::ostream& writeQuotedString(std::ostream& os, const std::string& str,
                                bool forceQuotes = true);

/**
 * 检查字符串是否需要加引号才能被正确读取。
 * @private
 */
bool stringNeedsQuoting(const std::string& str);

/**
 * 将通用值写入输出流。如果该值是字符串，
 * 此函数使用 writeQuotedString 写入值。
 * @private
 */
template <typename ValueType>
std::ostream& writeGenericValue(std::ostream& os, const ValueType& value, bool) {
    return os << std::boolalpha << value;
}

inline std::ostream& writeGenericValue(std::ostream& os, char value,
                                       bool forceQuotes) {
    return writeQuotedChar(os, value, forceQuotes);
}

inline std::ostream& writeGenericValue(std::ostream& os, const std::string& value,
                                       bool forceQuotes) {
    return writeQuotedString(os, value, forceQuotes);
}

template <typename ValueType>
inline std::string genericValueToString(const ValueType& value,
                                        bool forceQuotes = false) {
    std::ostringstream os;
    writeGenericValue(os, value, forceQuotes);
    return os.str();
}

inline std::string genericValueToString(const std::string& value,
                                        bool forceQuotes) {
    std::ostringstream os;
    writeQuotedString(os, value, forceQuotes);
    return os.str();
}

/**
 * 从输入流读取通用值。如果该值是字符串，
 * 此函数使用 readQuotedString 读取值。
 * @private
 */
template <typename ValueType>
bool readGenericValue(std::istream& is, ValueType& value) {
    return (bool) (is >> value);
}

inline bool readGenericValue(std::istream& is, char& value) {
    return readQuotedChar(is, value, /* throwOnError */ false);
}

inline bool readGenericValue(std::istream& is, std::string& value) {
    return readQuotedString(is, value, /* throwOnError */ false);
}

// 结束 strlib.h 中的全局命名空间字符串读写函数
namespace stanfordcpplib {
namespace collections {

template <typename CollectionType, typename IteratorType>
void checkVersion(const CollectionType& coll, const IteratorType& itr,
                  const std::string& memberName = "") {
    unsigned int collVersion = coll.version();
    unsigned int itrVersion = itr.version();
    if (itrVersion != collVersion) {
        std::string msg = memberName;
        if (!msg.empty()) {
            msg += ": ";
        }
        msg += "A collection was modified during iteration, which invalidates operation.\n";
        msg += "Do not modify a collection within a for-each loop!";
        error(msg);
    }
}

/*
 * 对给定两个集合执行排序比较
 * 通过逐对比较它们的元素。
 * 如果集合 1“小于”集合 2，则返回 -1；
 * 如果集合 1“大于”集合 2，则返回 1；
 * 如果集合 1“等于”集合 2，则返回 0。
 * 元素类型必须具有 operator <。
 */
template <typename CollectionType>
int compare(const CollectionType& coll1, const CollectionType& coll2) {
    // 优化：如果它们是同一个对象，则它们相等
    if (&coll1 == &coll2) {
        return 0;
    }

    auto itr1 = coll1.begin(),
         itr2 = coll2.begin(),
         end1 = coll1.end(),
         end2 = coll2.end();
    for (;
         itr1 != end1 && itr2 != end2;
         ++itr1, ++itr2) {
        // 逐对比较迭代器中的各元素

        // 致学生：
        // 若程序中紧接下方的一行无法编译，通常
        // 表示你正在尝试创建一个嵌套集合
        // （例如 Set<Vector<T>>），其中某个元素类型 T 没有
        // 小于运算符 <。要使以下功能正常，*必须*定义该运算符：
        // 由 Vector 组成的 Set 或 Map，使该集合/映射知道如何排序
        // 将元素按升序排列。
        // 你应为类添加 < 运算符，或考虑使用
        // 不同的嵌套集合解决方案。祝你好运！
        if (*itr1 < *itr2) {
            return -1;
        } else if (*itr2 < *itr1) {
            return 1;
        }
    }

    // 若执行到这里，v1 的所有内容都与 v2 匹配，因此它们要么相等，
    // 或者其中一个比另一个短（元素更少），因而更小
    if (itr1 == end1 && itr2 == end2) {
        return 0;
    } else if (itr1 == end1) {
        return -1;
    } else {
        return 1;
    }
}

/*
 * 对给定两个映射执行排序比较
 * 通过逐对比较它们的键/值对。
 * 如果集合 1“小于”集合 2，则返回 -1；
 * 如果集合 1“大于”集合 2，则返回 1；
 * 如果集合 1“等于”集合 2，则返回 0。
 * 请注意，这里映射中键和值的顺序很重要；
 * 同一个映射若键的顺序不同，会产生不同结果。
 * 键和值的类型都必须具有 operator <。
 */
template <typename MapType>
int compareMaps(const MapType& map1, const MapType& map2) {
    // 优化：如果它们是同一个对象，则它们相等
    if (&map1 == &map2) {
        return 0;
    }

    auto itr1 = map1.begin(),
         itr2 = map2.begin(),
         end1 = map1.end(),
         end2 = map2.end();
    for (;
         itr1 != end1 && itr2 != end2;
         ++itr1, ++itr2) {
        // 逐对比较迭代器中的各元素

        // 致学生：
        // 若程序中紧接下方的一行无法编译，通常
        // 表示你正在尝试创建一个嵌套集合
        // （例如 Set<Map<K, V>>），其中某个元素类型 K 或 V 没有
        // 小于运算符 <。要使以下功能正常，*必须*定义该运算符：
        // 由 Map 组成的 Set 或 Map，使该集合/映射知道如何排序
        // 将键和值按升序排列。
        // 你应为键/值类型添加 < 运算符，或考虑使用
        // 不同的嵌套集合解决方案。祝你好运！
        if (*itr1 < *itr2) {
            return -1;
        } else if (*itr2 < *itr1) {
            return 1;
        }

        // key1 == key2，因此比较值
        auto value1 = map1[*itr1];
        auto value2 = map2[*itr2];
        if (value1 < value2) {
            return -1;
        } else if (value2 < value1) {
            return 1;
        }
    }

    // 若执行到这里，v1 的所有内容都与 v2 匹配，因此它们要么相等，
    // 或者其中一个比另一个短（元素更少），因而更小
    if (itr1 == end1 && itr2 == end2) {
        return 0;
    } else if (itr1 == end1) {
        return -1;
    } else {
        return 1;
    }
}

/*
 * 用于比较两个交错值序列的模板函数，返回
 * 如果第一个值小于第二个值，则为 -1，
 *  如果值相等，则为 0，
 *  如果第一个值大于第二个值，则为 1。
 * 传入的类型必须支持 < 小于运算符。
 */
inline int compareTo() {
    return 0;
}
template <typename T, typename... Rest>
int compareTo(const T& first, const T& second, const Rest&... rest) {
    if (first < second) return -1;
    if (second < first) return +1;
    return compareTo(rest...);
}

/*
 * 如果两个集合以相同顺序包含相同元素，则返回 true。
 * 元素类型必须具有 operator ==。
 */
template <typename CollectionType>
bool equals(const CollectionType& coll1, const CollectionType& coll2) {
    // 优化：如果实际上是同一个集合，则停止
    if (&coll1 == &coll2) {
        return true;
    }
    // 优化：若大小不同，则无需逐对比较
    if (coll1.size() != coll2.size()) {
        return false;
    }

    // 逐对检查元素是否相等
    auto itr1 = coll1.begin();
    auto end1 = coll1.end();
    auto itr2 = coll2.begin();
    auto end2 = coll2.end();
    while (itr1 != end1 && itr2 != end2) {
        if (!(*itr1 == *itr2)) {
            return false;
        }
        ++itr1;
        ++itr2;
    }
    return true;
}

/*
 * 如果两个集合以相同顺序包含相同元素，则返回 true。
 * 元素类型必须是 double、float 或任意浮点类型。
 */
template <typename CollectionType>
bool equalsDouble(const CollectionType& coll1, const CollectionType& coll2) {
    // 优化：如果实际上是同一个集合，则停止
    if (&coll1 == &coll2) {
        return true;
    }
    // 优化：若大小不同，则无需逐对比较
    if (coll1.size() != coll2.size()) {
        return false;
    }

    // 逐对检查元素是否相等
    auto itr1 = coll1.begin();
    auto end1 = coll1.end();
    auto itr2 = coll2.begin();
    auto end2 = coll2.end();
    while (itr1 != end1 && itr2 != end2) {
        if (!floatingPointEqual(*itr1, *itr2)) {
            return false;
        }
        ++itr1;
        ++itr2;
    }
    return true;
}

/*
 * 如果给定两个映射包含相同键集合，且每个
 * 该键在两个映射中对应相同的值。
 * 不考虑键的顺序。
 * 键和值的类型都必须具有 operator ==。
 */
template <typename MapType>
bool equalsMap(const MapType& map1, const MapType& map2) {
    // 优化：如果确实是同一映射，则停止
    if (&map1 == &map2) {
        return true;
    }
    // 优化：若大小不同，则无需逐对比较
    if (map1.size() != map2.size()) {
        return false;
    }

    // 检查第一个映射中的每个元素是否也在第二个映射中。
    // 由于大小相同，如果此条件为 true，则映射相等。
    for (auto itr1 = map1.begin(), end1 = map1.end(); itr1 != end1; ++itr1) {
        if (!map2.containsKey(*itr1) || !(map1.get(*itr1) == map2.get(*itr1))) {
            return false;
        }
    }
    return true;
}

/*
 * 为任意可迭代类型计算 hashCode。
 * 对于维持某种元素顺序的集合，将 'orderMatters' 传 true
 * 有意义的顺序。对于几乎所有集合而言都是如此
 * 基于哈希的集合除外，其顺序半随机且不重要。
 */
template <typename IteratorType>
int hashCodeIterable(IteratorType begin, IteratorType end, bool orderMatters = true) {
    int code = hashSeed();
    while (begin != end) {
        if (orderMatters) {
            code *= hashMultiplier();
        }
        code += hashCode(*begin);
        ++begin;
    }
    return int(code & hashMask());
}

/*
 * 为任意集合类型计算 hashCode。
 * 集合必须具有 begin() 和 end()
 */
template <typename CollectionType>
int hashCodeCollection(const CollectionType& collection, bool orderMatters = true) {
    return hashCodeIterable(collection.begin(), collection.end(), orderMatters);
}

/*
 * 哈希映射的模板哈希函数。
 * 要求 HashMap 中的键和值类型具有 hashCode 函数。
 */
template <typename MapType>
int hashCodeMap(const MapType& map, bool orderMatters = true) {
    int code = hashSeed();
    auto begin = map.begin();
    auto end = map.end();
    while (begin != end) {
        if (orderMatters) {
            code *= hashMultiplier();
        }
        code += hashCode(*begin);

        if (orderMatters) {
            code *= hashMultiplier();
        }
        code += hashCode(map[*begin]);
        ++begin;
    }
    return int(code & hashMask());
}

/*
 * 从给定集合中随机选择并返回一个元素。
 * 如果集合为空，则抛出错误。
 */
template <typename Collection>
auto randomElement(const Collection& collection) -> const decltype(*collection.begin())& {
    if (collection.isEmpty()) {
        error("randomElement: empty collection was passed");
    }
    return *std::next(collection.begin(), randomInteger(0, collection.size() - 1));
}

/*
 * 从给定集合中随机选择并返回一个元素。
 * 集合必须具有索引 [] 运算符。
 * 如果集合为空，则抛出错误。
 */
template <template <typename> class CollectionType, class ElementType>
const ElementType& randomElementIndexed(const CollectionType<ElementType>& collection) {
    if (collection.isEmpty()) {
        error("randomElement: empty collection was passed");
    }
    int index = randomInteger(0, collection.size() - 1);
    return collection[index];
}


template <typename CollectionType, typename ElementType>
    void readOne(CollectionType& collection, const ElementType& elem)
        { collection.add(elem); }
/*
 * 从给定输入流读取任意集合。
 * 集合必须具有接受单个值的 add() 方法，或者
 * （或提供自己的回调作为 add 操作）
 * 以及移除集合中所有元素的 clear() 方法。
 */
template <typename CollectionType, typename ElementType>
std::istream& readCollection(std::istream& input, CollectionType& collection, ElementType& element, std::string /* 描述符 */,
        void (*fn)(CollectionType&, const ElementType&) = readOne<CollectionType,ElementType>)
{

    char ch = '\0';
    input >> ch;
    if (ch != '{') {
        input.setstate(std::ios_base::failbit);
        return input;
    }
    collection.clear();
    input >> ch;
    if (ch != '}') {
        input.unget();
        while (true) {
            if (!readGenericValue(input, element)) {
                return input;
            }
            fn(collection, element);
            input >> ch;
            if (ch == '}') {
                break;
            }
            if (ch != ',') {
                input.setstate(std::ios_base::failbit);
                return input;
            }
        }
    }
    return input;
}


template <typename CollectionType, typename KeyType, typename ValueType>
    void readOne(CollectionType& collection, const KeyType& key, const ValueType& value)
        { collection.put(key, value); }
/*
 * 从给定输入流读取任意配对集合（Map 或 Priority Queue）。
 * 集合必须具有接受键和值的 put() 方法
 * （或提供一个用作 add 操作的回调）
 * 以及移除集合中所有元素的 clear() 方法。
 */

template <typename CollectionType, typename KeyType, typename ValueType>
std::istream& readPairedCollection(std::istream& input, CollectionType& collection, KeyType& key, ValueType& value, std::string /* 描述符 */,
        void (*fn)(CollectionType&, const KeyType&, const ValueType&) = readOne<CollectionType,KeyType,ValueType>)
{
    char ch = '\0';
    input >> ch;
    if (ch != '{') {
        input.setstate(std::ios_base::failbit);
        return input;
    }
    collection.clear();
    input >> ch;
    if (ch != '}') {
        input.unget();
        while (true) {
            if (!readGenericValue(input, key)) {
                return input;
            }
            input >> ch;
            if (ch != ':') {
                input.setstate(std::ios_base::failbit);
                return input;
            }
            if (!readGenericValue(input, value)) {
                return input;
            }
            fn(collection, key, value);
            input >> ch;
            if (ch == '}') {
                break;
            }
            if (ch != ',') {
                input.setstate(std::ios_base::failbit);
                return input;
            }
        }
    }
    return input;
}

/*
 * 使用两个迭代器将任意集合写入给定输出流，
 * 开始和结束。
 */
template <typename IteratorType>
std::ostream& writeIterable(std::ostream& out, IteratorType begin, IteratorType end) {
    out << "{";
    bool first = true;
    while (begin != end) {
        if (!first) {
            out << ", ";
        }
        first = false;
        writeGenericValue(out, *begin, /* forceQuotes */ true);
        ++begin;
    }
    out << "}";
    return out;
}

/*
 * 使用两个迭代器将任意集合写入给定输出流，
 * 开始和结束。
 */
template <typename CollectionType>
std::ostream& writeCollection(std::ostream& out, CollectionType collection) {
    return writeIterable(out, collection.begin(), collection.end());
}

/*
 * 使用两个迭代器将任意集合写入给定输出流，
 * 开始和结束。
 */
template <typename IteratorType>
std::ostream& writeIterableOfPointers(std::ostream& out, IteratorType begin, IteratorType end) {
    out << "{";
    bool first = true;
    while (begin != end) {
        if (!first) {
            out << ", ";
        }
        first = false;
        writeGenericValue(out, **begin, /* forceQuotes */ true);
        ++begin;
    }
    out << "}";
    return out;
}

/*
 * 使用两个迭代器将任意集合写入给定输出流，
 * 开始和结束。
 */
template <typename CollectionType>
std::ostream& writeCollectionOfPointers(std::ostream& out, CollectionType collection) {
    return writeIterableOfPointers(out, collection.begin(), collection.end());
}

/*
 * 实现说明：<< 和 >>
 * -------------------------------
 * 插入和提取运算符使用以下文件中的模板功能：
 * 使用 strlib.h 读写通用值，并以特殊方式处理字符串
 * 特殊处理。
 */
template <typename MapType>
std::ostream& writeMap(std::ostream& out, const MapType& map) {
    out << "{";
    auto begin = map.begin();
    auto end = map.end();
    bool first = true;
    while (begin != end) {
        if (!first) {
            out << ", ";
        }
        first = false;
        writeGenericValue(out, *begin, /* forceQuotes */ true);
        out << ":";
        writeGenericValue(out, map[*begin], /* forceQuotes */ true);
        ++begin;
    }
    out << "}";
    return out;
}

/*
 * 负责跟踪某个对象版本的类型。将其单独提取为
 * 它自己的对象带有特殊复制函数，因此每当底层对象
 * 被移动或赋值时，底层版本号会更新。
 */
class VersionTracker {
public:
    /* 对 VersionTracker 赋值会递增底层版本号。 */
    VersionTracker& operator= (VersionTracker) {
        ++_version;
        return *this;
    }

    /* 移动构造 VersionTracker 会采用以下对象的版本号
     * 正在移动的对象。
     */
    VersionTracker(VersionTracker&& rhs) {
        rhs._version++;
    }

    /* 使用默认构造函数和默认复制构造函数。 */
    VersionTracker() = default;
    VersionTracker(const VersionTracker &) = default;

    /* 标记版本必须更新。 */
    void update() {
        ++_version;
    }

    /* 返回版本号。 */
    unsigned int version() const {
        return _version;
    }

private:
    unsigned int _version = 0;
};

/*
 * 包装底层迭代器类型的受检迭代器类型，并添加边界检查
 * 以及版本检查。
 */
template <typename Iterator> class CheckedIterator {
public:
    /* 我们具有所包装迭代器的相同类型。 */
    using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using pointer           = typename std::iterator_traits<Iterator>::pointer;
    using reference         = typename std::iterator_traits<Iterator>::reference;
    using value_type        = typename std::iterator_traits<Iterator>::value_type;

    /*
     * 必须显式声明默认构造函数，以使私有构造函数
     * 不会遮蔽我们。
     */
    CheckedIterator() = default;

    /* 根据底层容器信息构造迭代器。 */
    template <typename Container>
    CheckedIterator(const VersionTracker* owner, Iterator iter, Container& c)
        : _version(owner->version()), _owner(owner), _iter(iter), _begin(c.begin()), _end(c.end()) {

    }

    /*
     * 我们与所有其他 CheckedIterator 类型互为友元，从而允许交叉构造
     * 诸如此类。
     */
    template <typename OtherItr> friend class CheckedIterator;

    /* 允许时使用的转换构造函数。 */
    template <typename OtherItr> CheckedIterator(const CheckedIterator<OtherItr>& rhs)
        : _version(rhs._version),
          _owner(rhs._owner),
          _iter(rhs._iter),
          _begin(rhs._begin),
          _end(rhs._end) {

    }

    template <typename OtherItr> operator CheckedIterator<OtherItr>() const {
        return CheckedIterator<OtherItr>{_version, _owner, _iter, _begin, _end};
    }

    /* 所有可能的迭代器函数。 */

    /* 比较运算符。 */
    template <typename OtherItr> bool operator ==(const CheckedIterator<OtherItr>& rhs) const {
        if (!_owner || !rhs._owner) {
            error("Cannot compare an uninitialized iterator.");
        }
        if ( _owner !=  rhs._owner) {
            error("Cannot compare iterators from two different containers.");
        }
        return _iter == rhs._iter;
    }
    template <typename OtherItr> bool operator !=(const CheckedIterator<OtherItr>& rhs) const {
        return !(*this == rhs);
    }

    /*
     * 如果底层所有者不同，我们会报告错误，否则
     * 行为未定义。
     */
    template <typename OtherItr> bool operator <(const CheckedIterator<OtherItr>& rhs) const {
        if (!_owner || !rhs._owner) {
            error("Cannot compare an uninitialized iterator.");
        }
        if (_owner != rhs._owner) {
            error("Cannot compare iterators from different containers.");
        }
        return _iter < rhs._iter;
    }
    template <typename OtherItr> bool operator >(const CheckedIterator<OtherItr>& rhs) const {
        return rhs < *this;
    }
    template <typename OtherItr> bool operator <=(const CheckedIterator<OtherItr>& rhs) const {
        return !(*this > rhs);
    }
    template <typename OtherItr> bool operator >=(const CheckedIterator<OtherItr>& rhs) const {
        return !(*this < rhs);
    }

    /* 随机访问。 */
    reference operator [](difference_type index) const {
        if (!_owner) {
            error("Cannot access elements through an uninitialized iterator.");
        }
        ::stanfordcpplib::collections::checkVersion(*_owner, *this);
        if (index >= 0 &&  index >= _end - _iter) {
            error("Out of bounds.");
        }
        if (index <  0 && -index >  _iter - _begin) {
            error("Out of bounds.");
        }

        return _iter[index];
    }

    CheckedIterator& operator +=(difference_type index) {
        if (!_owner) error("Cannot advance uninitialized iterators.");
        ::stanfordcpplib::collections::checkVersion(*_owner, *this);
        _iter += index;
        return *this;
    }
    CheckedIterator& operator -=(difference_type index) {
        return *this += (-index);
    }

    CheckedIterator operator +(difference_type index) const {
        auto result = *this;
        return result += index;
    }
    CheckedIterator operator -(difference_type index) const {
        return *this + (-index);
    }

    template <typename OtherItr>
    difference_type operator -(const CheckedIterator<OtherItr>& rhs) const {
        if (!_owner || !rhs._owner) {
            error("Cannot subtract uninitialized iterators.");
        }

        ::stanfordcpplib::collections::checkVersion(*_owner, *this);
        if (_owner != rhs._owner) {
            error("Cannot subtract iterators from two different containers.");
        }

        return _iter - rhs._iter;
    }

    /* 向前和向后。 */
    CheckedIterator& operator ++() {
        if (!_owner) {
            error("Cannot advance an uninitialized iterator.");
        }

        ::stanfordcpplib::collections::checkVersion(*_owner, *this);
        if (_iter == _end) {
            error("Cannot advance an iterator past end of range.");
        }
        ++_iter;
        return *this;
    }
    CheckedIterator operator ++(int) {
        auto result = *this;
        ++*this;
        return result;
    }

    CheckedIterator& operator --() {
        if (!_owner) {
            error("Cannot back up an uninitialized iterator.");
        }

        ::stanfordcpplib::collections::checkVersion(*_owner, *this);
        if (_iter == _begin) {
            error("Cannot back up an iteartor before start of range.");
        }

        --_iter;
        return *this;
    }
    CheckedIterator operator --(int) {
        auto result = *this;
        --*this;
        return result;
    }

    /* 解引用。 */
    reference operator *() const {
        if (!_owner) {
            error("Cannot dereference an uninitialized iterator.");
        }
        ::stanfordcpplib::collections::checkVersion(*_owner, *this);

        if (_iter == _end) {
            error("Iterator out of range.");
        }
        return *_iter;
    }
    pointer operator ->() const {
        return &**this;
    }

    /* 直接版本访问。 */
    unsigned int version() const {
        if (!_owner) {
            error("Cannot get version from an uninitialized iterator.");
        }
        return _version;
    }

private:
    unsigned int _version = 0;
    const VersionTracker* _owner = nullptr;
    Iterator _iter;
    Iterator _begin, _end;
};

/*
 * 用于键值对的迭代器，只投影第一个分量。本质上，它将
 * pair<const Key, Value> 的迭代器转换为 const Key 的迭代器。
 *
 * 所有边界检查、错误处理等都假定由底层对象提供
 * 迭代器类型。
 */
template <typename Iterator> class ProjectingIterator {
public:
    /* 我们所包装对象的类型。 */
    using value_type       = typename std::remove_reference<decltype(std::declval<Iterator>()->first)>::type;

    /* 我们具有所包装迭代器的相同类型。 */
    using difference_type   = typename std::iterator_traits<Iterator>::difference_type;
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using pointer           = const value_type *;
    using reference         = const value_type &;

    /*
     * 必须显式声明默认构造函数，以使私有构造函数
     * 不会遮蔽我们。
     */
    ProjectingIterator() = default;

    /* 包装现有迭代器。 */
    explicit ProjectingIterator(Iterator iter) : _iter(iter) {
        // 空
    }

    /*
     * 我们与所有其他相关类型互为友元，从而允许交叉构造
     * 诸如此类。
     */
    template <typename OtherItr> friend class ProjectingIterator;

    /* 允许时使用的转换构造函数。 */
    template <typename OtherItr> ProjectingIterator(const ProjectingIterator<OtherItr>& rhs)
        : _iter(rhs._iter) {
        // 空
    }

    template <typename OtherItr> operator ProjectingIterator<OtherItr>() const {
        return ProjectingIterator<OtherItr>(_iter);
    }

    /* 所有可能的迭代器函数。 */

    /* 比较运算符。 */
    template <typename OtherItr> bool operator ==(const ProjectingIterator<OtherItr>& rhs) {
        return _iter == rhs._iter;
    }
    template <typename OtherItr> bool operator !=(const ProjectingIterator<OtherItr>& rhs) {
        return !(*this == rhs);
    }

    template <typename OtherItr> bool operator <(const ProjectingIterator<OtherItr>& rhs) {
        return _iter < rhs._iter;
    }
    template <typename OtherItr> bool operator >(const ProjectingIterator<OtherItr>& rhs) {
        return rhs < *this;
    }
    template <typename OtherItr> bool operator <=(const ProjectingIterator<OtherItr>& rhs) {
        return !(*this > rhs);
    }
    template <typename OtherItr> bool operator >=(const ProjectingIterator<OtherItr>& rhs) {
        return !(*this < rhs);
    }

    /* 随机访问。 */
    reference operator [](difference_type index) const {
        return _iter[index];
    }
    ProjectingIterator& operator +=(difference_type index) {
        _iter += index;
        return *this;
    }
    ProjectingIterator& operator -=(difference_type index) {
        return *this += (-index);
    }
    ProjectingIterator operator +(difference_type index) const {
        auto result = *this;
        return result += index;
    }
    ProjectingIterator operator -(difference_type index) const {
        return *this + (-index);
    }
    template <typename OtherItr>
    difference_type operator -(const ProjectingIterator<OtherItr>& rhs) const {
        return _iter - rhs._iter;
    }

    /* 向前和向后。 */
    ProjectingIterator& operator ++() {
        ++_iter;
        return *this;
    }
    ProjectingIterator operator ++(int) {
        auto result = *this;
        ++*this;
        return result;
    }

    ProjectingIterator& operator --() {
        --_iter;
        return *this;
    }
    ProjectingIterator operator --(int) {
        auto result = *this;
        --*this;
        return result;
    }

    /* 解引用。 */
    reference operator *() const {
        return _iter->first;
    }
    pointer operator ->() const {
        return &**this;
    }

private:
    Iterator _iter;
};

/**
 * 类：GenericSet<SetTraits>
 * ----------------------------
 * 此类存储一组互不相同的元素。SetTraits 应
 * 包含以下内容的类型：
 *
 *     typename ValueType：映射中存储的任意类型
 *     typename MapType：应为 Map<ValueType, bool>
 *     static std::string name()：应返回类型名称。
 *
 * 还有一个要求：你需要定义一个函数
 *
 *     template <typename... Args>
 *        static MapType construct(Args&&... args)
 *
 * 使用指定参数构造内部 MapType 对象。
 * 此函数应做一些有创意或巧妙的事情，以确保
 * 是在参数不正确时生成的友好编译器错误
 * 无效，否则错误会深度嵌套在
 * GenericSet 模板。
 *
 * 这不应由学生直接使用。
 */
template <typename SetTraits>
class GenericSet {
public:
    /**
     * 便于使用的实用别名。
     */
    using value_type = typename SetTraits::ValueType;

    /**
     * 构造函数：GenericSet
     * 用法：GenericSet<ValueType, SetTraits> set;
     * --------------------------------------------
     * 初始化指定元素类型的空集合。
     */
    GenericSet() = default;

    /**
     * 构造函数：GenericSet
     * 用法：GenericSet<ValueType, SetTraits> set {1, 2, 3};
     * ------------------------------------------------------
     * 初始化一个存储给定元素的新集合。
     */
    GenericSet(std::initializer_list<value_type> list);

    /**
     * 构造函数：GenericSet
     * 用法：GenericSet<ValueType, SetTraits> set(... things for the map ...);
     * ------------------------------------------------------------------------
     * 将指定参数转发给底层 Map 类型。
     */
    template <typename... Args>
    explicit GenericSet(Args... args);

    /**
     * 构造函数：GenericSet
     * 用法：GenericSet<ValueType, SetTraits> set({1, 2, 3}, ... things for the map ...);
     * -----------------------------------------------------------------------------------
     * 使用指定元素构造集合，并将参数转发给
     * 底层映射。
     */
    template <typename... Args>
    GenericSet(std::initializer_list<value_type> list,
               Args... args);

    /**
     * 析构函数：~Set
     * ----------------
     * 释放与此集合关联的任何堆存储。
     */
    virtual ~GenericSet() = default;

    /**
     * 方法：add
     * 用法：set.add(value);
     * ----------------------
     * 如果元素尚不存在，则将其添加到此集合。
     */
    void add(const value_type& value);

    /**
     * 方法：back
     * 用法：ValueType value = set.last();
     * ------------------------------------
     * 按照以下顺序返回集合中的最后一个值
     * <code>for-each</code> 循环。如果集合为空，则产生错误。
     */
    value_type last() const;

    /**
     * 方法：clear
     * 用法：set.clear();
     * -------------------
     * 从此集合中删除所有元素。
     */
    void clear();

    /**
     * 方法：contains
     * 用法：if (set.contains(value)) ...
     * -----------------------------------
     * 如果指定值在此集合中，则返回 <code>true</code>。
     */
    bool contains(const value_type& value) const;

    /**
     * 方法：difference
     * 用法：set.difference(set2);
     * ----------------------------
     * 从此集合中删除给定另一集合的所有元素。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     * 返回对此集合的引用。
     *
     * 注意，此函数会就地修改当前集合，而不是
     * 返回一个新集合。如果需要新集合，请考虑使用 - 运算符
     * 改用此运算符（不是 -=），它会返回新创建的集合副本。
     *
     * 行为与 -= 运算符相同。
     */
    GenericSet& difference(const GenericSet& set);

    /**
     * 方法：equals
     * 用法：if (set.equals(set2)) ...
     * --------------------------------
     * 如果此集合包含完全相同的值，则返回 <code>true</code>
     * 与给定的另一个集合相同。
     * 行为与 == 运算符相同。
     */
    bool equals(const GenericSet& set2) const;

    /**
     * 方法：first
     * 用法：ValueType value = set.first();
     * -------------------------------------
     * 按照以下顺序返回集合中的第一个值
     * <code>for-each</code> 循环。如果集合为空，<code>first</code>
     * 生成错误。
     */
    value_type first() const;

    /**
     * 方法：intersect
     * 用法：set.intersect(set2);
     * ---------------------------
     * 从此集合中删除所有不包含在给定集合中的元素
     * 另一个集合。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     * 返回对此集合的引用。
     *
     * 注意，此函数会就地修改当前集合，而不是
     * 返回一个新集合。如果需要新集合，请考虑使用 * 运算符
     * 改用此运算符（不是 *=），它会返回新创建的集合副本。
     *
     * 行为与 *= 运算符相同。
     */
    GenericSet& intersect(const GenericSet& set);

    /**
     * 方法：isEmpty
     * 用法：if (set.isEmpty()) ...
     * -----------------------------
     * 如果此集合不包含元素，则返回 <code>true</code>。
     */
    bool isEmpty() const;

    /**
     * 方法：isSubsetOf
     * 用法：if (set.isSubsetOf(set2)) ...
     * ------------------------------------
     * 实现集合的子集关系。它返回
     * 若此集合的每个元素都满足条件，则为 <code>true</code>
     * 包含在 <code>set2</code> 中。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     */
    bool isSubsetOf(const GenericSet& set2) const;

    /**
     * 方法：isSupersetOf
     * 用法：if (set.isSupersetOf(set2)) ...
     * --------------------------------------
     * 实现集合的超集关系。它返回
     * 若此集合的每个元素都满足条件，则为 <code>true</code>
     * 包含在 <code>set2</code> 中。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     */
    bool isSupersetOf(const GenericSet& set2) const;

    /**
     * 方法：mapAll
     * 用法：set.mapAll(fn);
     * ----------------------
     * 遍历集合中的元素并调用 <code>fn(value)</code>
     * 分别处理每一个。迭代顺序与底层存储顺序一致
     * 元素的存储顺序。对于 Set，这是按照以下规则排序的顺序
     * 比较函数；对于 HashSet，则为元素的某种顺序
     * 恰好位于其中。
     */
    void mapAll(std::function<void (const value_type&)> fn) const;

    /**
     * 方法：remove
     * 用法：set.remove(value);
     * -------------------------
     * 从此集合中删除一个元素。如果该值原本不存在
     * 包含在集合中时，不会产生错误，并且集合
     * 保持不变。
     */
    void remove(const value_type& value);

    /**
     * 方法：size
     * 用法：count = set.size();
     * --------------------------
     * 返回此集合中的元素数量。
     */
    int size() const;

    /**
     * 方法：toString
     * 用法：string str = set.toString();
     * -----------------------------------
     * 将集合转换为可打印的字符串表示。
     */
    std::string toString() const;

    /**
     * 方法：unionWith
     * 用法：set.unionWith(set2);
     * ---------------------------
     * 将给定其他集合中的所有元素添加到此集合。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     * 返回对此集合的引用。
     * 行为与 += 运算符相同。
     *
     * 注意，此函数会就地修改当前集合，而不是
     * 返回一个新集合。如果需要新集合，请考虑使用 + 运算符
     * 改用此运算符（不是 +=），它会返回新创建的集合副本。
     *
     * （实现说明：此函数不能命名为“union”，因为
     * 它是 C/C++ 关键字。）
     */
    GenericSet& unionWith(const GenericSet& set);

    /**
     * 运算符：==
     * 用法：set1 == set2
     * -------------------
     * 如果 <code>set1</code> 和 <code>set2</code>，则返回 <code>true</code>
     * 包含相同元素。
     */
    bool operator ==(const GenericSet& set2) const;

    /**
     * 运算符：!=
     * 用法：set1 != set2
     * -------------------
     * 如果 <code>set1</code> 和 <code>set2</code>，则返回 <code>true</code>
     * 不同。
     */
    bool operator !=(const GenericSet& set2) const;

    /**
     * 运算符：<、>、<=、>=
     * 用法：if (set1 <= set2) ...
     * ...
     * ----------------------------
     * 用于比较两个集合的关系运算符。
     * <、>、<=、>= 运算符要求值类型具有 < 运算符
     * 以便逐对比较各元素。
     *
     * 这些函数实现为友元函数，因此，如果我们完整实例化
     * 此类型，以便使用关系运算符时不会出错。
     */
    template <typename Traits>
    friend bool operator <(const GenericSet<Traits>& set1, const GenericSet<Traits>& set2);
    template <typename Traits>
    friend bool operator <=(const GenericSet<Traits>& set1, const GenericSet<Traits>& set2);
    template <typename Traits>
    friend bool operator >(const GenericSet<Traits>& set1, const GenericSet<Traits>& set2);
    template <typename Traits>
    friend bool operator >=(const GenericSet<Traits>& set1, const GenericSet<Traits>& set2);

    /**
     * 运算符：+
     * 用法：set1 + set2
     *        set1 + element
     * ---------------------
     * 返回集合 <code>set1</code> 与 <code>set2</code> 的并集，即
     * 是至少出现在两个集合之一中的元素集合。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     * 右侧集合可以替换为值类型的一个元素，方式为
     * 在这种情况下，运算符返回添加该元素后形成的新集合。
     */
    GenericSet operator +(const GenericSet& set2) const;
    GenericSet operator +(const value_type& element) const;

    /**
     * 运算符：*
     * 用法：set1 * set2
     * ------------------
     * 返回集合 <code>set1</code> 与 <code>set2</code> 的交集，
     * 它是同时出现在两者中的所有元素的集合。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     */
    GenericSet operator *(const GenericSet& set2) const;

    /**
     * 运算符：-
     * 用法：set1 - set2
     *        set1 - element
     * ---------------------
     * 返回集合 <code>set1</code> 与 <code>set2</code> 的差集，
     * 它包含出现在 <code>set1</code> 中但
     * 而不是 <code>set2</code>。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     * 右侧集合可以替换为值类型的一个元素，方式为
     * 在这种情况下，运算符返回移除该元素后形成的新集合。
     */
    GenericSet operator -(const GenericSet& set2) const;
    GenericSet operator -(const value_type& element) const;

    /**
     * 运算符：+=
     * 用法：set1 += set2;
     *        set1 += value;
     * ---------------------
     * 将 <code>set2</code> 中的所有元素（或单个
     * 将指定值）添加到 <code>set1</code>。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     * 为方便使用，<code>Set</code> 包还重载了逗号
     * 运算符，使得可以像这样初始化集合：
     *
     *<pre>
     *    Set&lt;int&gt; digits;
     *    digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
     *</pre>
     */
    GenericSet& operator +=(const GenericSet& set2);
    GenericSet& operator +=(const value_type& value);

    /**
     * 运算符：*=
     * 用法：set1 *= set2;
     * --------------------
     * 从 <code>set1</code> 中删除不在以下集合中的元素
     * <code>set2</code>。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     */
    GenericSet& operator *=(const GenericSet& set2);

    /**
     * 运算符：-=
     * 用法：set1 -= set2;
     *        set1 -= value;
     * ---------------------
     * 从 <code>set2</code> 中删除这些元素（或单个
     * 从 <code>set1</code> 中删除指定值）。
     * 还可以传入初始化列表，例如 {1, 2, 3}。
     * 为方便使用，<code>Set</code> 包还重载了逗号
     * 运算符，使得可以从集合中移除多个元素
     * 如下所示：
     *
     *<pre>
     *    digits -= 0, 2, 4, 6, 8;
     *</pre>
     *
     * 它会从集合中移除值 0、2、4、6 和 8
     * <code>digits</code>。
     */
    GenericSet& operator -=(const GenericSet& set2);
    GenericSet& operator -=(const value_type& value);

    /*
     * 其他 Set 操作
     * -------------------------
     * 除本接口中列出的方法外，Set
     * 类支持以下操作：
     *
     *   - 使用 << 和 >> 运算符进行流输入/输出
     *   - 为复制构造函数和赋值运算符实现深拷贝
     *   - 使用基于范围的 for 语句和 STL 迭代器进行迭代
     *
     * 这些迭代形式按升序处理 Set。
     */

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

private:
    typename SetTraits::MapType _map = SetTraits::construct();  /* 用于存储元素的 Map    */
    bool _removeFlag = false;                                   /* 用于区分 += 和 -= 的标志   */

public:
    /*
     * 隐藏功能
     * ---------------
     * 此文件的剩余部分包含实现以下功能所需的代码：
     * 支持逗号运算符、复制和迭代。
     *
     * 将这些方法包含在公共接口中会使
     * 使普通客户端更难理解该接口。
     */
    GenericSet& operator ,(const value_type& value) {
        if (this->_removeFlag) {
            this->remove(value);
        } else {
            this->add(value);
        }
        return *this;
    }

    using const_iterator = typename SetTraits::MapType::const_iterator;
    using iterator = const_iterator;

    iterator begin() const {
        return _map.begin();
    }

    iterator end() const {
        return _map.end();
    }

    friend int hashCode(const GenericSet& set) {
        return hashCode(set._map);
    }
};

template <typename SetTraits>
GenericSet<SetTraits>::GenericSet(std::initializer_list<value_type> list)
    : _map(SetTraits::construct()) {
    /* 不能使用 addAll，因为那会递归尝试构造 GenericSet。
     * 改为直接在此添加所有内容。这里成为以下操作的集中位置：
     * 所有 initializer_list 转换。
     */
    for (const auto& elem: list) {
        add(elem);
    }
}

template <typename SetTraits>
template <typename... Args>
GenericSet<SetTraits>::GenericSet(Args... args) : GenericSet({}, std::move(args)...) {
    // 由其他构造函数处理
}

template <typename SetTraits>
template <typename... Args>
GenericSet<SetTraits>::GenericSet(std::initializer_list<value_type> list, Args... args)
    : _map(SetTraits::construct(std::move(args)...)) {

    /* 不能使用 addAll，因为那会递归尝试构造 GenericSet。
     * 改为直接在此添加所有内容。这里成为以下操作的集中位置：
     * 所有 initializer_list 转换。
     */
    for (const auto& elem: list) {
        add(elem);
    }
}

template <typename SetTraits>
void GenericSet<SetTraits>::add(const value_type& value) {
    _map.put(value, true);
}

template <typename SetTraits>
typename GenericSet<SetTraits>::value_type
GenericSet<SetTraits>::last() const {
    if (isEmpty()) {
        error(SetTraits::name() + "::back: set is empty");
    }
    return _map.lastKey();
}

template <typename SetTraits>
void GenericSet<SetTraits>::clear() {
    _map.clear();
}

template <typename SetTraits>
bool GenericSet<SetTraits>::contains(const value_type& value) const {
    return _map.containsKey(value);
}

template <typename SetTraits>
GenericSet<SetTraits>& GenericSet<SetTraits>::difference(const GenericSet<SetTraits>& set2) {
    _map.removeAll(set2._map);
    return *this;
}

template <typename SetTraits>
bool GenericSet<SetTraits>::equals(const GenericSet& set2) const {
    // 优化：如果确实是同一集合，则停止
    if (this == &set2) {
        return true;
    }

    /* 如果大小相同且我们是另一个集合的子集，则两者相等
     * 集合。
     */
    if (size() != set2.size()) {
        return false;
    }
    return isSubsetOf(set2);
}

template <typename SetTraits>
typename GenericSet<SetTraits>::value_type
GenericSet<SetTraits>::first() const {
    if (isEmpty()) {
        error(SetTraits::name() + "::first: set is empty");
    }
    return _map.firstKey();
}

template <typename SetTraits>
GenericSet<SetTraits>& GenericSet<SetTraits>::intersect(const GenericSet<SetTraits>& set2) {
    _map.retainAll(set2._map);
    return *this;
}

template <typename SetTraits>
bool GenericSet<SetTraits>::isEmpty() const {
    return _map.isEmpty();
}

template <typename SetTraits>
bool GenericSet<SetTraits>::isSubsetOf(const GenericSet& set2) const {
    for (const auto& elem: *this) {
        if (!set2.contains(elem)) {
            return false;
        }
    }
    return true;
}

template <typename SetTraits>
bool GenericSet<SetTraits>::isSupersetOf(const GenericSet& set2) const {
    for (const auto& value: set2) {
        if (!contains(value)) {
            return false;
        }
    }
    return true;
}

template <typename SetTraits>
void GenericSet<SetTraits>::mapAll(std::function<void (const value_type &)> fn) const {
    _map.mapAll([&](const value_type& elem, bool) {
        fn(elem);
    });
}

template <typename SetTraits>
void GenericSet<SetTraits>::remove(const value_type& value) {
    _map.remove(value);
}

template <typename SetTraits>
int GenericSet<SetTraits>::size() const {
    return _map.size();
}

template <typename SetTraits>
std::string GenericSet<SetTraits>::toString() const {
    std::ostringstream os;
    os << *this;
    return os.str();
}

template <typename SetTraits>
GenericSet<SetTraits>& GenericSet<SetTraits>::unionWith(const GenericSet<SetTraits>& set2) {
    for (const auto& value : set2) {
        add(value);
    }
    return *this;
}


/*
 * 实现说明：集合运算符
 * -----------------------------------
 * 集合运算符的实现使用迭代来遍历
 * 遍历一个或两个集合中的元素。
 */
template <typename SetTraits>
bool GenericSet<SetTraits>::operator ==(const GenericSet& set2) const {
    return equals(set2);
}

template <typename SetTraits>
bool GenericSet<SetTraits>::operator !=(const GenericSet& set2) const {
    return !equals(set2);
}

template <typename SetTraits>
bool operator <(const GenericSet<SetTraits>& set1, const GenericSet<SetTraits>& set2) {
    return set1._map < set2._map;
}

template <typename SetTraits>
bool operator <=(const GenericSet<SetTraits>& set1, const GenericSet<SetTraits>& set2) {
    return set1._map <= set2._map;
}

template <typename SetTraits>
bool operator >(const GenericSet<SetTraits>& set1, const GenericSet<SetTraits>& set2) {
    return set1._map > set2._map;
}

template <typename SetTraits>
bool operator >=(const GenericSet<SetTraits>& set1, const GenericSet<SetTraits>& set2) {
    return set1._map >= set2._map;
}

template <typename SetTraits>
GenericSet<SetTraits> GenericSet<SetTraits>::operator +(const GenericSet& set2) const {
    return GenericSet(*this).unionWith(set2);
}

template <typename SetTraits>
GenericSet<SetTraits> GenericSet<SetTraits>::operator +(const value_type& element) const {
    GenericSet result = *this;
    result.add(element);
    return result;
}

template <typename SetTraits>
GenericSet<SetTraits> GenericSet<SetTraits>::operator *(const GenericSet& set2) const {
    return GenericSet(*this).intersect(set2);
}

template <typename SetTraits>
GenericSet<SetTraits> GenericSet<SetTraits>::operator -(const GenericSet& set2) const {
    return GenericSet(*this).difference(set2);
}

template <typename SetTraits>
GenericSet<SetTraits> GenericSet<SetTraits>::operator -(const value_type& element) const {
    GenericSet result = *this;
    result.remove(element);
    return result;
}

template <typename SetTraits>
GenericSet<SetTraits>& GenericSet<SetTraits>::operator +=(const GenericSet& set2) {
    _removeFlag = false;
    return unionWith(set2);
}

template <typename SetTraits>
GenericSet<SetTraits>& GenericSet<SetTraits>::operator +=(const value_type& value) {
    add(value);
    _removeFlag = false;
    return *this;
}

template <typename SetTraits>
GenericSet<SetTraits>& GenericSet<SetTraits>::operator *=(const GenericSet& set2) {
    return intersect(set2);
}

template <typename SetTraits>
GenericSet<SetTraits>& GenericSet<SetTraits>::operator -=(const GenericSet& set2) {
    _removeFlag = true;
    return difference(set2);
}

template <typename SetTraits>
GenericSet<SetTraits>& GenericSet<SetTraits>::operator -=(const value_type& value) {
    remove(value);
    _removeFlag = true;
    return *this;
}

template <typename SetTraits>
std::ostream& operator <<(std::ostream& os, const GenericSet<SetTraits>& set) {
    return stanfordcpplib::collections::writeCollection(os, set);
}

template <typename SetTraits>
std::istream& operator >>(std::istream& is, GenericSet<SetTraits>& set) {
    typename SetTraits::ValueType element;
    return stanfordcpplib::collections::readCollection(is, set, element, /* 描述符 */ SetTraits::name() + "::operator >>");
}


/*
 * 用于使用以下方式自动检查类型是否可比较的类型
 * < 运算符，以及类型是否支持 operator== 和 hashCode。
 *
 * 这用于在以下情况下向学生提供更好的编译器诊断信息：
 * 它们试图以错误方式实例化我们的时间。
 *
 * 将来 C++20 concepts 推广后，我们应考虑
 * 使用 concepts 替换此代码。
 */
template <typename T>
struct IsLessThanComparable {
private:
    /* 使用 SFINAE 重载检测应选择这两个选项中的哪一个。 */
    struct Yes{};
    struct No {};

    template <typename U>
    static Yes check(int,
                     decltype(std::declval<U>() < std::declval<U>()) = 0);
    template <typename U> static No  check(...);

public:
    static constexpr bool value =
            std::conditional<std::is_same<decltype(check<T>(0)), Yes>::value,
                             std::true_type,
                             std::false_type>::type::value;
};

template <typename T>
struct IsHashable {
private:
    /* 使用 SFINAE 重载检测应选择这两个选项中的哪一个。 */
    struct Yes{};
    struct No {};

    template <typename U>
    static Yes check(int,
                     decltype(hashCode(std::declval<U>())) = 0,
                     decltype(std::declval<U>() == std::declval<U>()) = 0);
    template <typename U> static No  check(...);

public:
    static constexpr bool value =
            std::conditional<std::is_same<decltype(check<T>(0)), Yes>::value,
                             std::true_type,
                             std::false_type>::type::value;
};

/*
 * 返回 std::less<T>，但在其周围包装友好的静态断言，以便
 * 确保当 T 无法通过 < 比较时，错误消息
 * 更易读。
 */
template <typename T>
std::function<bool (const T&, const T&)> checkedLess() {
    static_assert(IsLessThanComparable<T>::value,
                  "Oops! You tried using a type as a key in our Map without making it comparable. Click this error for more details.");
    /*
     * CS106 的同学你好！如果编译错误将你指向此行代码，
     * 这可能意味着你尝试使用自定义结构体或类类型创建 Map
     * 作为键类型，或将自定义结构体作为值类型的 Set。
     *
     * 要让某类型成为 Map 的键类型——或成为其值类型
     * 在 Set 中——它需要能够使用 < 运算符进行比较。默认情况下，C++ 中的类型
     * 无法使用 < 运算符比较，因此出现错误。
     *
     * 有两种修复方式。第一种是直接不使用自定义
     * 将该类型用作 Map 的键或 Set 的值。这可能是最简单的选择。
     *
     * 解决此问题的第二种方法是为自定义类型显式定义 operator< 函数
     * 类型。语法如下：
     *
     *     bool operator< (const YourCustomType& lhs, const YourCustomType& rhs) {
     *         using namespace stanfordcpplib::collections;
     *         return compareTo(lhs.data1, rhs.data1,
     *                          lhs.data2, rhs.data2,
     *                          ...
     *                          lhs.dataN, rhs.dataN) == -1; // -1 表示小于
     *     }
     *
     * 其中 data1、data2、...、dataN 是该类型的数据成员。例如，如果你有
     * 自定义类型
     *
     *     struct MyType {
     *         int myInt;
     *         string myString;
     *     };
     *
     * 你需要定义函数
     *
     *     bool operator< (const MyType& lhs, const MyType& rhs) {
     *         using namespace stanfordcpplib::collections;
     *         return compareTo(lhs.myInt,    rhs.myInt,
     *                          lhs.myString, rhs.myString) == -1;
     *     }
     *
     * 希望这能有所帮助！
     */
    return std::less<T>();
}

/*
 * 始终包含值 false 的实用特征类型。
 */
template <typename... Args> struct Fail {
    static constexpr bool value = false;
};

} // namespace collections
} // namespace stanfordcpplib

#endif // _collections_h
