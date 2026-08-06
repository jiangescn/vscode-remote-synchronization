/*
 * 文件：lexicon.cpp
 * -----------------
 * Lexicon 是单词列表。此 Lexicon 由以下数据结构支持：
 * 称为前缀树或 trie（读作 "try"）的结构。
 *
 * 这是 Lexicon 的重新实现。其先前实现使用
 * 一对结构：有向无环词图（DAWG）和 STL 集合。
 * 由于多个原因，该实现被弃用：
 *
 * - 它依赖学生无法阅读的二进制文件格式。
 * - 它未提供 remove 等预期的类成员。
 * - 它使用了一对笨重的数据结构，必须分别搜索。
 * - 它针对空间占用进行了优化，而非易用性和可维护性。
 *
 * 原始 DAWG 实现保留在 dawglexicon.h/cpp 中。
 *
 * @version 2018/03/10
 * - 添加 front 方法
 * @version 2016/09/24
 * - 重构以使用 collections.h 实用函数
 * @version 2016/08/11
 * - 添加运算符 +、+=、-、-=、*、*=，以更好地匹配 Set/HashSet
 * @version 2016/08/10
 * - 添加对 std initializer_list 用法的构造函数支持，例如 {"a", "b", "c"}
 * @version 2016/08/04
 * - 修复 operator >>，使其不抛出错误
 * @version 2015/07/05
 * - 使用全局哈希函数而非全局变量
 * @version 2014/11/13
 * - 添加比较运算符 <、>= 等
 * - 添加 hashCode 函数
 * @version 2014/10/10
 * - 添加比较运算符 ==、!=
 * - 移除“using namespace”语句
 */

#include "lexicon.h"
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "collections.h"
#include "error.h"
#include "filelib.h"
#include "hashcode.h"
#include "strlib.h"

static bool scrub(std::string& str);

Lexicon::Lexicon() :
        _root(nullptr),
        _size(0),
        _removeFlag(false) {
    // 空
}

Lexicon::Lexicon(std::istream& input) :
        _root(nullptr),
        _size(0),
        _removeFlag(false) {
    addWordsFromFile(input);
}

Lexicon::Lexicon(const std::string& filename) :
        _root(nullptr),
        _size(0),
        _removeFlag(false) {
    addWordsFromFile(filename);
}

Lexicon::Lexicon(std::initializer_list<std::string> list) :
        _root(nullptr),
        _size(0),
        _removeFlag(false) {
    addAll(list);
}

Lexicon::Lexicon(const Lexicon& src) :
        _root(nullptr),
        _size(0),
        _removeFlag(false) {
    deepCopy(src);
}

Lexicon::~Lexicon() {
    clear();
}

bool Lexicon::add(const std::string& word) {
    if (word.empty()) {
        return false;
    }
    std::string scrubbed = word;
    if (!scrub(scrubbed)) {
        return false;
    }
    return addHelper(_root, scrubbed, /* originalWord */ scrubbed);
}

Lexicon& Lexicon::addAll(const Lexicon& lex) {
    for (const std::string& word : lex) {
        add(word);
    }
    return *this;
}

Lexicon& Lexicon::addAll(std::initializer_list<std::string> list) {
    for (const std::string& word : list) {
        add(word);
    }
    return *this;
}

void Lexicon::addWordsFromFile(std::istream& input) {
    std::string line;
    while (getline(input, line)) {
        add(trim(line));
    }
}

void Lexicon::addWordsFromFile(const std::string& filename) {
    std::ifstream input(filename.c_str());
    if (input.fail()) {
        error("Lexicon::addWordsFromFile: Couldn't read from input file " + filename);
    }
    addWordsFromFile(input);
    input.close();
}

std::string Lexicon::back() const {
    if (isEmpty()) {
        error("Lexicon::back: lexicon is empty");
    }
    return _allWords.last();
}

void Lexicon::clear() {
    _size = 0;
    _allWords.clear();
    deleteTree(_root);
    _root = nullptr;
}

bool Lexicon::contains(const std::string& word) const {
    if (word.empty()) {
        return false;
    }
    std::string scrubbed = word;
    if (!scrub(scrubbed)) {
        return false;
    }
    return containsHelper(_root, scrubbed, /* isPrefix */ false);
}

bool Lexicon::containsAll(const Lexicon& lex2) const {
    for (const std::string& word : lex2) {
        if (!contains(word)) {
            return false;
        }
    }
    return true;
}

bool Lexicon::containsAll(std::initializer_list<std::string> list) const {
    for (const std::string& word : list) {
        if (!contains(word)) {
            return false;
        }
    }
    return true;
}

bool Lexicon::containsPrefix(const std::string& prefix) const {
    if (prefix.empty()) {
        return true;
    }
    std::string scrubbed = prefix;
    if (!scrub(scrubbed)) {
        return false;
    }
    return containsHelper(_root, scrubbed, /* isPrefix */ true);
}

bool Lexicon::equals(const Lexicon& lex2) const {
    return stanfordcpplib::collections::equals(*this, lex2);
}

std::string Lexicon::first() const {
    if (isEmpty()) {
        error("Lexicon::first: lexicon is empty");
    }
    return _allWords.first();
}

std::string Lexicon::front() const {
    if (isEmpty()) {
        error("Lexicon::front: lexicon is empty");
    }
    return _allWords.first();
}

void Lexicon::insert(const std::string& word) {
    add(word);
}

bool Lexicon::isEmpty() const {
    return size() == 0;
}

bool Lexicon::isSubsetOf(const Lexicon& lex2) const {
    auto it = begin();
    auto end = this->end();
    while (it != end) {
        if (!lex2.contains(*it)) {
            return false;
        }
        ++it;
    }
    return true;
}

bool Lexicon::isSubsetOf(std::initializer_list<std::string> list) const {
    Lexicon lex2(list);
    return isSubsetOf(lex2);
}

bool Lexicon::isSupersetOf(const Lexicon& lex2) const {
    return containsAll(lex2);
}

bool Lexicon::isSupersetOf(std::initializer_list<std::string> list) const {
    return containsAll(list);
}

void Lexicon::mapAll(void (*fn)(std::string)) const {
    for (std::string word : _allWords) {
        fn(word);
    }
}

void Lexicon::mapAll(void (*fn)(const std::string&)) const {
    for (std::string word : _allWords) {
        fn(word);
    }
}

bool Lexicon::remove(const std::string& word) {
    if (word.empty()) {
        return false;
    }
    std::string scrubbed = word;
    if (!scrub(scrubbed)) {
        return false;
    }
    return removeHelper(_root, scrubbed, /* originalWord */ scrubbed, /* isPrefix */ false);
}

Lexicon& Lexicon::removeAll(const Lexicon& lex2) {
    Vector<std::string> toRemove;
    for (const std::string& word : *this) {
        if (lex2.contains(word)) {
            toRemove.add(word);
        }
    }
    for (const std::string& word : toRemove) {
        remove(word);
    }
    return *this;
}

Lexicon& Lexicon::removeAll(std::initializer_list<std::string> list) {
    for (const std::string& word : list) {
        remove(word);
    }
    return *this;
}

bool Lexicon::removePrefix(const std::string& prefix) {
    if (prefix.empty()) {
        bool result = !isEmpty();
        clear();
        return result;
    }
    std::string scrubbed = prefix;
    if (!scrub(scrubbed)) {
        return false;
    }

    return removeHelper(_root, scrubbed, /* originalWord */ scrubbed, /* isPrefix */ true);
}

Lexicon& Lexicon::retainAll(const Lexicon& lex2) {
    Vector<std::string> toRemove;
    for (const std::string& word : *this) {
        if (!lex2.contains(word)) {
            toRemove.add(word);
        }
    }
    for (const std::string& word : toRemove) {
        remove(word);
    }
    return *this;
}

Lexicon& Lexicon::retainAll(std::initializer_list<std::string> list) {
    Lexicon lex2(list);
    return retainAll(lex2);
}

int Lexicon::size() const {
    return _size;
}

std::string Lexicon::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

/*
 * 运算符
 */
bool Lexicon::operator ==(const Lexicon& lex2) const {
    return equals(lex2);
}

bool Lexicon::operator !=(const Lexicon& lex2) const {
    return !equals(lex2);
}

bool Lexicon::operator <(const Lexicon& lex2) const {
    return stanfordcpplib::collections::compare(*this, lex2) < 0;
}

bool Lexicon::operator <=(const Lexicon& lex2) const {
    return stanfordcpplib::collections::compare(*this, lex2) <= 0;
}

bool Lexicon::operator >(const Lexicon& lex2) const {
    return stanfordcpplib::collections::compare(*this, lex2) > 0;
}

bool Lexicon::operator >=(const Lexicon& lex2) const {
    return stanfordcpplib::collections::compare(*this, lex2) >= 0;
}

Lexicon Lexicon::operator +(const Lexicon& lex2) const {
    Lexicon lex = *this;
    lex.addAll(lex2);
    return lex;
}

Lexicon Lexicon::operator +(std::initializer_list<std::string> list) const {
    Lexicon lex = *this;
    lex.addAll(list);
    return lex;
}

Lexicon Lexicon::operator +(const std::string& word) const {
    Lexicon lex = *this;
    lex.add(word);
    return lex;
}

Lexicon Lexicon::operator *(const Lexicon& lex2) const {
    Lexicon lex = *this;
    return lex.retainAll(lex2);
}

Lexicon Lexicon::operator *(std::initializer_list<std::string> list) const {
    Lexicon lex = *this;
    return lex.retainAll(list);
}

Lexicon Lexicon::operator -(const Lexicon& lex2) const {
    Lexicon lex = *this;
    return lex.removeAll(lex2);
}

Lexicon Lexicon::operator -(std::initializer_list<std::string> list) const {
    Lexicon lex = *this;
    return lex.removeAll(list);
}

Lexicon Lexicon::operator -(const std::string& word) const {
    Lexicon lex = *this;
    lex.remove(word);
    return lex;
}

Lexicon& Lexicon::operator +=(const Lexicon& lex2) {
    return addAll(lex2);
}

Lexicon& Lexicon::operator +=(std::initializer_list<std::string> list) {
    return addAll(list);
}

Lexicon& Lexicon::operator +=(const std::string& word) {
    add(word);
    _removeFlag = false;
    return *this;
}

Lexicon& Lexicon::operator *=(const Lexicon& lex2) {
    return retainAll(lex2);
}

Lexicon& Lexicon::operator *=(std::initializer_list<std::string> list) {
    return retainAll(list);
}

Lexicon& Lexicon::operator -=(const Lexicon& lex2) {
    return removeAll(lex2);
}

Lexicon& Lexicon::operator -=(std::initializer_list<std::string> list) {
    return removeAll(list);
}

Lexicon& Lexicon::operator -=(const std::string& word) {
    remove(word);
    _removeFlag = true;
    return *this;
}

/* 私有辅助函数实现 */

Lexicon& Lexicon::operator ,(const std::string& word) {
    if (_removeFlag) {
        remove(word);
    } else {
        add(word);
    }
    return *this;
}

// 前置条件：word 已清理为仅包含小写 a-z 字母
bool Lexicon::addHelper(TrieNode*& node, const std::string& word, const std::string& originalWord) {
    if (!node) {
        // 一路向下创建节点，每个单词字母对应一个节点
        node = new TrieNode();
    }

    if (word.empty()) {
        // 基本情况：已添加此单词的所有字母
        if (node->isWord()) {
            return false;   // 重复单词；已存在
        } else {
            // 新单词；添加它
            node->setWord(true);
            _size++;
            _allWords.add(originalWord);
            return true;
        }
    } else {
        // 递归情况：截去第一个字母，遍历其余部分
        return addHelper(node->child(word[0]), word.substr(1), originalWord);
    }
}

// 前置条件：word 已清理为仅包含小写 a-z 字母
bool Lexicon::containsHelper(TrieNode* node, const std::string& word, bool isPrefix) const {
    if (!node) {
        // 基本情况：没有指向此处的指针，因此前缀一定不存在
        return false;
    } else if (word.length() == 0) {
        // 基本情况：一直向下找到了节点。
        // 如果我们正在查找前缀，这意味着该路径本身就是前缀，
        // 因此应返回 true。
        // 如果我们查找的是精确单词匹配而不是前缀，
        // 必须检查 isWord 标志，确认该单词已添加
        return (isPrefix ? true : node->isWord());
    } else {
        // 递归情况：针对一个字母沿适当的子指针前进
        return containsHelper(node->child(word[0]), word.substr(1), isPrefix);
    }
}

// 前置条件：word 已清理为仅包含小写 a-z 字母
bool Lexicon::removeHelper(TrieNode*& node, const std::string& word, const std::string& originalWord, bool isPrefix) {
    if (!node) {
        // 基本情况：死胡同；不得包含此单词/前缀
        return false;
    } else if (word.empty()) {
        // 基本情况：已遍历此单词/前缀的所有字母
        // 现在必须执行移除操作
        if (isPrefix) {
            // 删除此节点及其所有后代
            removeSubtreeHelper(node, originalWord);   // 从 m_allWords 中删除并设置 m_size
            node = nullptr;
        } else {
            // 在词典中找到了此单词；
            if (node->isLeaf()) {
                // 仅删除此叶节点
                delete node;
                node = nullptr;
            } else {
                // 取消此节点的单词状态，但保留它，因为它可能
                // 仍然有作为有效单词的子节点
                if (node->isWord()) {
                    node->setWord(false);
                }
            }
            _allWords.remove(originalWord);
            _size--;
        }
        return true;
    } else {
        // 递归情况：截去第一个字母，遍历其余部分
        bool wasLeaf = node->isLeaf();
        bool result = removeHelper(node->child(word[0]), word.substr(1), originalWord, isPrefix);

        // 内存清理：如果之前不是叶节点但现在是，并且不是单词，
        // 那么我也不再需要，因此也删除我
        if (result && !wasLeaf && node
                && node->isLeaf() && !node->isWord()) {
            delete node;
            node = nullptr;
        }
        return result;
    }
}

// 删除/释放此节点及其所有后代
void Lexicon::removeSubtreeHelper(TrieNode*& node, const std::string& originalWord) {
    if (node) {
        for (char letter = 'a'; letter <= 'z'; letter++) {
            removeSubtreeHelper(node->child(letter), originalWord + letter);
        }
        if (node->isWord()) {
            _allWords.remove(originalWord);
            _size--;
        }
        delete node;
        node = nullptr;
    }
}

void Lexicon::deepCopy(const Lexicon& src) {
    for (std::string word : src._allWords) {
        add(word);
    }
}

void Lexicon::deleteTree(TrieNode* node) {
    if (node) {
        for (char letter = 'a'; letter <= 'z'; letter++) {
            deleteTree(node->child(letter));
        }
        delete node;
    }
}

Lexicon& Lexicon::operator =(const Lexicon& src) {
    if (this != &src) {
        clear();
        deepCopy(src);
    }
    return *this;
}

std::ostream& operator <<(std::ostream& out, const Lexicon& lex) {
    out << lex._allWords;
    return out;
}

std::istream& operator >>(std::istream& is, Lexicon& lex) {
    std::string element;
    return stanfordcpplib::collections::readCollection(is, lex, element, /* 描述符 */ "Lexicon::operator >>");
}

/*
 * 词典的哈希函数。
 */
int hashCode(const Lexicon& lex) {
    return stanfordcpplib::collections::hashCodeCollection(lex);
}

static bool scrub(std::string& str) {
    size_t nChars = str.length();
    size_t outIndex = 0;
    for (size_t i = 0; i < nChars; i++) {
        std::string::value_type ch = tolower(str[i]);
        if (ch < 'a' || ch > 'z') {
            return false;   // 非法字符串
        } else {
            str[outIndex] = ch;
            outIndex++;
        }
    }
    if (outIndex != nChars) {
        str.erase(outIndex, nChars - outIndex);
    }
    return true;
}
