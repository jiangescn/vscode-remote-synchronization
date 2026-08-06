/*
 * 文件：lexicon.h
 * ---------------
 * 此文件导出 <code>Lexicon</code> 类，它是一个
 * 用于存储单词列表的紧凑结构。
 */

#ifndef _lexicon_h
#define _lexicon_h

#include <initializer_list>
#include <iterator>
#include <set>
#include <string>

#include "hashcode.h"
#include "set.h"

/**
 * 此类用于表示一个<b><i>词典集</i></b>或单词列表。
 * 词典集与字典之间的主要区别是
 * 词典不提供任何存储定义的机制；
 * 该词典只包含单词，不包含关联信息。
 * 因此它类似于字符串集合，但具有更
 * 节省空间的内部表示。<code>Lexicon</code>
 * 该类支持对单词和前缀进行高效查找。
 *
 * <p>作为 <code>Lexicon</code> 类用法示例，以下
 * 以下程序列出词典中的所有双字母单词
 * 存储在 <code>EnglishWords.dat</code> 中：
 *
 *<pre>
 *    int main() {
 *       Lexicon english("EnglishWords.dat");
 *       for (string word : english) {
 *          if (word.length() == 2) {
 *             cout << word << endl;
 *          }
 *       }
 *       return 0;
 *    }
 *</pre>
 */

class Lexicon {
public:
    /*
     * 构造函数：Lexicon
     * 用法：Lexicon lex;
     *        Lexicon lex(filename);
     * -----------------------------
     * 初始化一个新词典。默认构造函数创建一个空
     * 词典。第二种形式从以下位置读取词典内容
     * 指定的数据文件。数据文件必须采用以下两种格式之一：
     * (1) 节省空间的预编译二进制格式，或 (2) 文本文件
     * 每行包含一个单词。Stanford 库发行版
     * 包含名为 <code>English.dat</code> 的二进制词典文件
     * 包含英语单词列表。标准代码模式
     * 初始化该词典集的代码如下：
     *
     *<pre>
     *    Lexicon english("English.dat");
     *</pre>
     */
    Lexicon();
    Lexicon(std::istream& input);
    Lexicon(const std::string& filename);

    /*
     * 此构造函数使用初始化列表设置词典集。
     * 用法：Lexicon lex {1, 2, 3};
     */
    Lexicon(std::initializer_list<std::string> list);

    /*
     * 析构函数：~Lexicon
     * --------------------
     * 析构函数释放与词典关联的所有存储空间。
     */
    virtual ~Lexicon();

    /**
     * 如果指定单词尚不存在，则将其添加到词典。
     * 该单词在加入词典集前会转换为小写。
     * 如果单词包含任何非字母字符（包括空白），
     * 它不会被添加。空字符串不能添加到词典中。
     * 如果单词成功添加到词典，则返回 true。
     */
    bool add(const std::string& word);

    /**
     * 将给定其他词典中的所有元素添加到此词典。
     * 返回对此词典的引用。
     * 行为与 += 运算符相同。
     */
    Lexicon& addAll(const Lexicon& lex);

    /**
     * 将给定初始化列表中的所有元素添加到此词典。
     * 返回对此词典的引用。
     * 行为与 += 运算符相同。
     */
    Lexicon& addAll(std::initializer_list<std::string> list);

    /**
     * 读取给定输入流并将其中所有单词添加到词典。
     * 流中的每个单词在添加前都会转换为小写。
     */
    void addWordsFromFile(std::istream& input);

    /**
     * 读取文件并将其中所有单词添加到词典。
     * 文件中的每个单词在添加前都会转换为小写。
     */
    void addWordsFromFile(const std::string& filename);

    /**
     * 按字母顺序返回词典中的最后一个值。
     * 若集合为空，则产生错误。
     */
    std::string back() const;

    /**
     * 从词典中删除所有单词。
     */
    void clear();

    /**
     * 如果 <code>word</code> 包含在以下对象中，则返回 <code>true</code>
     * 词典。在 <code>Lexicon</code> 类中，字母大小写
     * 会被忽略，因此 "Zoo" 与 "ZOO" 或 "zoo" 相同。
     * 空字符串不能包含在词典中，任何单词也不能
     * 包含任何非字母字符，例如标点符号或空白。
     */
    bool contains(const std::string& word) const;

    /**
     * 如果给定另一词典中的每个值都满足条件，则返回 <code>true</code>
     * 也存在于此词典中。
     * 行为等价于 isSupersetOf。
     */
    bool containsAll(const Lexicon& set2) const;

    /**
     * 如果给定初始化列表中的每个值都满足条件，则返回 <code>true</code>
     * 也存在于此词典中。
     * 行为等价于 isSupersetOf。
     */
    bool containsAll(std::initializer_list<std::string> list) const;

    /**
     * 如果词典中有任何单词以 <code>prefix</code> 开头，则返回 true。
     * 与 <code>containsWord</code> 类似，此方法忽略字母大小写
     * 因此 "MO" 是 "monkey" 或 "Monday" 的前缀。
     * 空字符串是每个字符串的前缀，因此此方法返回
     * 传入空字符串时为 true。
     */
    bool containsPrefix(const std::string& prefix) const;

    /**
     * 比较两个词典是否相等。
     */
    bool equals(const Lexicon& lex2) const;

    /**
     * 按字母顺序返回词典中的第一个值。
     * 如果集合为空，<code>first</code> 会产生错误。
     * 等价于 first。
     */
    std::string first() const;

    /**
     * 按字母顺序返回词典中的第一个值。
     * 若集合为空，则产生错误。
     * 等价于 first。
     */
    std::string front() const;

    /**
     * 如果元素尚不存在，则将其添加到此词典。此
     * 导出此方法是为了与 STL <code>set</code> 类兼容。
     */
    void insert(const std::string& word);

    /**
     * 如果词典不包含单词，则返回 <code>true</code>。
     */
    bool isEmpty() const;

    /**
     * 返回此词典中的每个单词是否都包含在给定集合中。
     */
    bool isSubsetOf(const Lexicon& lex2) const;

    /**
     * 返回此词典中的每个单词是否都包含在给定
     * 初始化列表。
     */
    bool isSubsetOf(std::initializer_list<std::string> list) const;

    /**
     * 返回给定词典中的每个单词是否都包含在此词典中。
     * 行为等价于 containsAll。
     */
    bool isSupersetOf(const Lexicon& lex2) const;

    /**
     * 返回给定列表中的每个单词是否都包含在此词典中。
     * 行为等价于 containsAll。
     */
    bool isSupersetOf(std::initializer_list<std::string> list) const;

    /**
     * 对词典中的每个单词调用指定函数。
     */
    void mapAll(void (*fn)(std::string)) const;

    /**
     * 对词典中的每个单词调用指定函数。
     */
    void mapAll(void (*fn)(const std::string&)) const;

    /**
     * 对词典中的每个单词调用指定函数。
     */
    template <typename FunctorType>
    void mapAll(FunctorType fn) const;

    /**
     * 如果指定单词存在，则从词典中删除它。
     * 如果单词之前包含在词典中，则返回 true；
     * 换句话说，如果删除了一个单词。
     * 空字符串不能包含在词典中，因此传入
     * 向此方法传入空字符串会返回 false。
     */
    bool remove(const std::string& word);

    /**
     * 从此词典中删除给定另一词典的所有元素。
     * 返回对此词典的引用。
     * 行为与 -= 运算符相同。
     */
    Lexicon& removeAll(const Lexicon& lex);

    /**
     * 从此词典中删除给定另一列表的所有元素。
     * 返回对此词典的引用。
     * 行为与 -= 运算符相同。
     */
    Lexicon& removeAll(std::initializer_list<std::string> list);

    /**
     * 从词典中删除所有以给定前缀开头的单词。
     * 如果该前缀之前包含在词典中，则返回 true；
     * 换句话说，如果删除了任何单词。
     * 如果传入空字符串，由于所有单词都以空字符串开头，
     * 字符串，所有单词都将被删除，并且此方法将
     * 如果调用前词典非空，则返回 true。
     */
    bool removePrefix(const std::string& prefix);

    /**
     * 从此词典中移除所有不包含在给定对象中的元素
     * 另一个词典。
     * 返回对此词典的引用。
     * 行为与 *= 运算符相同。
     */
    Lexicon& retainAll(const Lexicon& lex);

    /**
     * 从此词典中移除所有不包含在给定对象中的元素
     * 初始化列表。
     * 返回对此词典的引用。
     * 行为与 *= 运算符相同。
     */
    Lexicon& retainAll(std::initializer_list<std::string> list);

    /**
     * 返回词典中包含的单词数量。
     */
    int size() const;

    /**
     * 将词典转换为可打印的字符串表示
     * 例如 <code>{"a", "b", "c"}</code>。
     * 请注意，如果词典包含以下内容，此操作可能开销很大
     * 大量单词。
     */
    std::string toString() const;

    /**
     * 如果两个词典具有相同元素，则返回 true。
     */
    bool operator ==(const Lexicon& lex2) const;

    /**
     * 如果两个词典的元素不同，则返回 true。
     */
    bool operator !=(const Lexicon& lex2) const;

    /**
     * 用于比较两个词典的关系运算符。
     */
    bool operator <(const Lexicon& lex2) const;

    /**
     * 用于比较两个词典的关系运算符。
     */
    bool operator <=(const Lexicon& lex2) const;

    /**
     * 用于比较两个词典的关系运算符。
     */
    bool operator >(const Lexicon& lex2) const;

    /**
     * 用于比较两个词典的关系运算符。
     */
    bool operator >=(const Lexicon& lex2) const;

    /**
     * 返回词典 <code>lex1</code> 与 <code>lex2</code> 的并集，
     * 即至少出现在两个集合之一中的单词集合。
     */
    Lexicon operator +(const Lexicon& lex2) const;

    /**
     * 返回此词典与给定列表中单词的并集，
     * 即至少出现在两个集合之一中的单词集合。
     */
    Lexicon operator +(std::initializer_list<std::string> list) const;

    /**
     * 返回此词典与给定单词的并集。
     */
    Lexicon operator +(const std::string& word) const;

    /**
     * 返回两个词典的交集，
     * 即同时出现在两个集合中的所有单词的集合。
     */
    Lexicon operator *(const Lexicon& lex2) const;

    /**
     * 返回此词典与给定列表的交集，
     * 即同时出现在两个集合中的所有单词的集合。
     */
    Lexicon operator *(std::initializer_list<std::string> list) const;

    /**
     * 返回两个词典的差集，
     * 它包含出现在 <code>lex1</code> 中但
     * 而不是 <code>lex2</code>。
     * 还可以传入如 {"a", "b", "c"} 的初始化列表。
     * 右侧集合可以替换为单个单词，
     * 在这种情况下，运算符返回移除该单词后形成的新词典集。
     */
    Lexicon operator -(const Lexicon& lex2) const;

    /**
     * 返回两个词典的差集，
     * 它包含此词典集中有而
     * 给定初始化列表。
     */
    Lexicon operator -(std::initializer_list<std::string> list) const;

    /**
     * 返回从此词典中删除给定单词后形成的新词典。
     */
    Lexicon operator -(const std::string& word) const;

    /**
     * 将给定词典中的所有单词添加到此词典。
     */
    Lexicon& operator +=(const Lexicon& lex2);

    /**
     * 将给定列表中的所有单词添加到此词典。
     */
    Lexicon& operator +=(std::initializer_list<std::string> list);

    /**
     * 将指定单词添加到此词典。
     */
    Lexicon& operator +=(const std::string& word);

    /**
     * 从此词典中移除给定对象中不存在的所有元素
     * <code>lex2</code>。
     */
    Lexicon& operator *=(const Lexicon& lex2);

    /**
     * 从此词典中移除给定对象中不存在的所有元素
     * 给定初始化列表。
     */
    Lexicon& operator *=(std::initializer_list<std::string> list);

    /**
     * 从此词典中删除给定词典的所有元素。
     */
    Lexicon& operator -=(const Lexicon& lex2);

    /**
     * 从此词典中删除给定列表的所有元素。
     */
    Lexicon& operator -=(std::initializer_list<std::string> list);

    /**
     * 从此词典中删除给定单词。
     */
    Lexicon& operator -=(const std::string& value);

    /**
     * 允许一次向词典添加多个元素。
     *  @example  lex += "she", "sells", "sea", "shells";
     */
    Lexicon& operator ,(const std::string& word);

    /*
     * 其他 Lexicon 操作
     * -----------------------------
     * 除本接口中列出的方法外，Lexicon
     * 类支持以下操作：
     *
     *   - 为复制构造函数和赋值运算符实现深拷贝
     *   - 使用基于范围的 for 语句和 STL 迭代器进行迭代
     *
     * 所有迭代保证按字母顺序进行。所有
     * 词典集中的单词以小写形式存储。
     */

    /* 私有部分 */

    /**********************************************************************/
    /* 注意：文件中此处以下的所有内容在逻辑上都属于    */
    /* 属于实现细节，客户端无需关注。    */
    /**********************************************************************/

private:
    struct TrieNode {
    public:
        TrieNode() {
            _isWord = false;
            for (int i = 0; i < 26; i++) {
                _children[i] = nullptr;
            }
        }

        // 前置条件：letter 是 'a' 到 'z' 之间的小写字母
        inline TrieNode*& child(char letter) {
            return _children[letter - 'a'];
        }

        inline int childCount() const {
            int count = 0;
            for (int i = 0; i < 26; i++) {
                if (_children[i] != nullptr) {
                    count++;
                }
            }
            return count;
        }

        inline bool isLeaf() const {
            return childCount() == 0;
        }

        inline bool isWord() const {
            return _isWord;
        }

        inline void setWord(bool value) {
            _isWord = value;
        }

    private:
        /* 实例变量 */
        bool _isWord;
        TrieNode* _children[26];   // 0=a, 1=b, 2=c, ..., 25=z
    };

    /*
     * 私有辅助函数，包括
     * 用于实现公共 add/contains/remove 的递归辅助函数
     */
    bool addHelper(TrieNode*& node, const std::string& word, const std::string& originalWord);
    bool containsHelper(TrieNode* node, const std::string& word, bool isPrefix) const;
    void deepCopy(const Lexicon& src);
    void deleteTree(TrieNode* node);
    bool removeHelper(TrieNode*& node, const std::string& word, const std::string& originalWord, bool isPrefix);
    void removeSubtreeHelper(TrieNode*& node, const std::string& originalWord);

    friend std::ostream& operator <<(std::ostream& os, const Lexicon& lex);
    friend std::istream& operator >>(std::istream& is, Lexicon& lex);

    /* 实例变量 */
    TrieNode* _root;
    int _size;
    bool _removeFlag;             // 用于在与逗号一起使用时区分 += 和 -= 的标志
    Set<std::string> _allWords;   // 用于 foreach 的所有单词辅助结构；
                                  // 基本上是为了让我能够遍历单词而采取的权宜之计

public:
    /*
     * 深拷贝支持
     * --------------------
     * 定义此复制构造函数和 operator= 是为了使
     * 深拷贝，使词典能够按值传递/返回
     * 以及从一个词典赋值给另一个词典。以下对象的全部内容
     * 词典（包括其中的所有单词）都会被复制。进行复制
     * 通常由于成本高而避免使用，因此词典
     * 通常按引用传递。需要复制时，这些
     * 支持这些操作。
     */
    Lexicon(const Lexicon& src);
    Lexicon& operator =(const Lexicon& src);

    /*
     * 迭代器支持
     * ----------------
     * StanfordCPPLib 集合中的类实现输入
     * 迭代器，使其相对于以下内容对称工作
     * 对应的 STL 类。
     */
    class iterator : public Set<std::string>::iterator {
    public:
        iterator() : Set<std::string>::iterator() {}
        iterator(const iterator& it) : Set<std::string>::iterator(it) {}
        iterator(const Set<std::string>::iterator& it) : Set<std::string>::iterator(it) {}
    };

    /**
     * 返回位于词典第一个单词的迭代器。
     */
    iterator begin() const {
        return iterator(_allWords.begin());
    }

    /**
     * 返回位于词典最后一个单词的迭代器。
     */
    iterator end() const {
        return iterator(_allWords.end());
    }
};

template <typename FunctorType>
void Lexicon::mapAll(FunctorType fn) const {
    for (std::string word : *this) {
        fn(word);
    }
}

/**
 * 词典的哈希函数。
 */
int hashCode(const Lexicon& l);

/**
 * 将词典打印到给定输出流。
 */
std::ostream& operator <<(std::ostream& os, const Lexicon& lex);

/**
 * 从给定输入流读取词典内容。
 */
std::istream& operator >>(std::istream& is, Lexicon& lex);

#endif // _lexicon_h
