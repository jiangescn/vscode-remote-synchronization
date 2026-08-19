#include "Huffman.h"
#include "map.h"
#include "priorityqueue.h"
using namespace std;

/**
 * 释放 Huffman 树中的所有节点。我们提供了这个辅助函数，是因为测试驱动程序
 * 中也会使用它，并且你在实现过程中可能也会用到它。
 */
void deleteTree(EncodingTreeNode *tree)
{
    if (tree != nullptr)
    {
        deleteTree(tree->zero);
        deleteTree(tree->one);
        delete tree;
    }
}

/**
 * 使用课堂上介绍的算法，为给定字符串构造一棵 Huffman 编码树。
 *
 * 如果输入字符串中不包含至少两个不同的字符，此函数应报告错误。
 *
 * 将较小的树组合成较大的树时，务必把从队列中取出的第一棵树设为新树的
 * zero 子树，把第二棵树设为 one 子树。
 */
EncodingTreeNode *huffmanTreeFor(const string &str)
{
    /* TODO：删除这条注释以及下面几行代码，然后完成实现。 */
    // (void) str;
    // return nullptr;
    Map<char, int> freq;
    for (char ch : str)
    {
        freq[ch]++;
    }

    if (freq.size() < 2)
    {
        error("Need at least two distinct characters.");
    }

    PriorityQueue<EncodingTreeNode *> pq;
    for (char ch : freq)
    {
        EncodingTreeNode *node = new EncodingTreeNode{ch, nullptr, nullptr};
        pq.enqueue(node, freq[ch]);
    }

    while (pq.size() > 1)
    {
        double weight0 = pq.peekPriority();
        EncodingTreeNode *zero = pq.dequeue();

        double weight1 = pq.peekPriority();
        EncodingTreeNode *one = pq.dequeue();

        EncodingTreeNode *parent = new EncodingTreeNode{' ', zero, one};
        pq.enqueue(parent, weight0 + weight1);
    }

    return pq.dequeue();
}

/**
 * 给定一个包含压缩消息的 Queue<Bit>，以及当初用于编码这些位的树，将这些位
 * 解码回原始消息。
 *
 * 可以假设输入树既不为空，也不是只包含单个字符；这些边界情况无需处理。
 *
 * 可以假设输入的 Queue<Bit> 格式正确：每个字符都已正确编码，Queue 中没有
 * 多余的位，等等。
 */
string decodeText(Queue<Bit> &bits, EncodingTreeNode *tree)
{
    /* TODO：删除这条注释以及下面几行代码，然后完成实现。 */
    // (void)bits;
    // (void)tree;
    // return "";
    string result = "";
    EncodingTreeNode *curr = tree;

    while (!bits.isEmpty())
    {
        Bit bit = bits.dequeue();

        if (bit == 0)
        {
            curr = curr->zero;
        }
        else
        {
            curr = curr->one;
        }

        if (curr->one == nullptr && curr->zero == nullptr)
        {
            result += curr->ch;
            curr = tree;
        }
    }
    return result;
}

/**
 * 给定一个字符串和一棵 Huffman 编码树，使用该树编码文本，并输出表示编码
 * 结果的 Queue<Bit>。
 *
 * 输入树不会为空，也不会只包含一个节点；这些边界情况无需处理。输入树会
 * 包含组成输入字符串的所有字符。
 */
Queue<Bit> encodeText(const string &str, EncodingTreeNode *tree)
{
    /* TODO：删除这条注释以及下面几行代码，然后完成实现。 */
    // (void)str;
    // (void)tree;
    // return {};
    Queue<Bit> result;

    Map<char, Vector<Bit>> codes;

    auto dfs = [&](auto dfs, Vector<Bit> code, EncodingTreeNode *cur) -> void
    {
        if (cur->one == nullptr && cur->zero == nullptr)
        {
            codes[cur->ch] = code;
            return;
        }

        if (cur->one != nullptr)
        {
            Vector<Bit> next = code;
            next.add(1);
            dfs(dfs, next, cur->one);
        }
        if (cur->zero != nullptr)
        {
            Vector<Bit> next = code;
            next.add(0);
            dfs(dfs, next, cur->zero);
        }
    };

    dfs(dfs, {}, tree);

    for (char ch : str)
    {
        for (Bit it : codes[ch])
        {
            result.enqueue(it);
        }
    }

    return result;
}

/**
 * 将给定的 Queue<Bit> 和 Queue<char> 解码成一棵 Huffman 编码树。
 *
 * 可以假设输入的两个 Queue 结构正确：它们表示一棵树的合法编码，其中没有
 * 多余的字符或位，等等。
 */
EncodingTreeNode *decodeTree(Queue<Bit> &bits, Queue<char> &leaves)
{
    /* TODO：删除这条注释以及下面几行代码，然后完成实现。 */
    // (void)bits;
    // (void)leaves;
    // return nullptr;
    Bit bit = bits.dequeue();

    if(bit == 0)
    {
        return new EncodingTreeNode{leaves.dequeue(), nullptr, nullptr};
    }

    EncodingTreeNode* zero = decodeTree(bits, leaves);
    EncodingTreeNode* one = decodeTree(bits, leaves);
    
    return new EncodingTreeNode({' ', zero, one});
}

/**
 * 按照作业讲义中规定的方式，将给定的 Huffman 树编码为 Queue<Bit> 和
 * Queue<char>。
 *
 * 可以假设调用此函数时，输入的两个 Queue 都为空。
 *
 * 可以假设给定的 Huffman 树结构正确：每个内部节点都有两个子节点，只有
 * 叶节点中的字符有意义，等等。
 */
void encodeTree(EncodingTreeNode *tree, Queue<Bit> &bits, Queue<char> &leaves)
{
    /* TODO：删除这条注释以及下面几行代码，然后完成实现。 */
    // (void)tree;
    // (void)bits;
    // (void)leaves;

    if(tree->one == nullptr && tree->zero == nullptr)
    {
        bits.enqueue(0);
        leaves.enqueue(tree->ch);
        return;
    }

    bits.enqueue(1);
    encodeTree(tree->zero, bits, leaves);
    encodeTree(tree->one, bits, leaves);
}

/**
 * 使用 Huffman 编码压缩给定的文本字符串，返回一个 HuffmanResult，其中包含
 * 编码后的树和消息。
 *
 * 如果输入字符串中不同字符的数量少于两个，此函数的实现应报告错误。
 */
HuffmanResult compress(const string &text)
{
    /* TODO：删除这条注释以及下面几行代码，然后完成实现。 */
    // (void)text;
    // return {};

    HuffmanResult result;

    EncodingTreeNode* tree = huffmanTreeFor(text);
    encodeTree(tree, result.treeBits, result.treeLeaves);
    result.messageBits = encodeText(text, tree);

    deleteTree(tree);

    return result;
}

/**
 * 解压给定的 HuffmanResult，并返回它所表示的字符串。
 *
 * 你的实现可以根据需要修改 file 参数；函数返回后，不要求 file 保持特定状态。
 *
 * 可以假设输入的 file 格式正确，并且由正确实现的 compress 创建。
 */
string decompress(HuffmanResult &file)
{
    /* TODO：删除这条注释以及下面几行代码，然后完成实现。 */
    // (void)file;
    // return "";

    EncodingTreeNode* tree = decodeTree(file.treeBits, file.treeLeaves);
    string result = decodeText(file.messageBits, tree);

    deleteTree(tree);

    return result;
}

/* * * * * * 以下为测试用例 * * * * * */
#include "GUI/SimpleTest.h"

/* TODO：在这里添加你自己的自定义测试！ */

/* * * * * 以下为提供的测试 * * * * */
#include <limits>

/* 用于检验一棵自称 Huffman 树的树是否确实是 Huffman 树的辅助函数。
 * 具体来说，它会检查每个内部节点的子节点数量是否为零或两个。还可能通过
 * 其他方式构造出无效的 Huffman 树，例如包含未初始化的指针或形成环；
 * 但这里不会检查这些情况。
 */
bool isEncodingTree(EncodingTreeNode *tree)
{
    /* 空树不是 Huffman 树。 */
    if (tree == nullptr)
        return false;

    /* 如果缺少一个子节点，那么两个子节点都应缺失。 */
    if ((tree->zero == nullptr) != (tree->one == nullptr))
        return false;

    /* 如果存在子节点，它们也必须是 Huffman 树。 */
    return tree->zero == nullptr || (isEncodingTree(tree->zero) && isEncodingTree(tree->one));
}

/* 用于判断两棵树是否相等的辅助函数。此函数改编自第 8 份课程讨论讲义，
 * 并针对 Huffman 树进行了调整。
 */
bool areEqual(EncodingTreeNode *lhs, EncodingTreeNode *rhs)
{
    /* 基本情况：如果其中一棵是叶节点，那么两棵都应是叶节点。 */
    bool lhsLeaf = lhs->zero == nullptr && lhs->one == nullptr;
    bool rhsLeaf = rhs->zero == nullptr && rhs->one == nullptr;
    if (lhsLeaf || rhsLeaf)
    {
        return lhs->ch == rhs->ch && lhsLeaf == rhsLeaf;
    }

    /* 否则，两者都是内部节点。检查它们是否匹配。 */
    return areEqual(lhs->zero, rhs->zero) && areEqual(lhs->one, rhs->one);
}

/* 用于返回包含所有可能字符的字符串的辅助函数。 */
string pangrammaticString()
{
    string result;

    char ch = numeric_limits<char>::min();
    result += ch;
    do
    {
        ch++;
        result += ch;
    } while (ch != numeric_limits<char>::max());

    return result;
}

/* 用于为给定字符构造一棵低效但仍然有效的编码树的辅助函数。
 */
EncodingTreeNode *strandTreeFor(const string &text, size_t index = 0)
{
    if (index == text.size())
        error("No characters provided to strandTreeFor.");

    /* 这里总会创建一个叶节点。 */
    EncodingTreeNode *leaf = new EncodingTreeNode{
        text[index], nullptr, nullptr};

    /* 这是最后一个字符吗？如果是，直接返回。 */
    if (index + 1 == text.size())
        return leaf;

    /* 否则，构造一棵更大的树。 */
    else
        return new EncodingTreeNode{
            ' ', leaf, strandTreeFor(text, index + 1)};
}

PROVIDED_TEST("huffmanTreeFor reports errors on invalid inputs.")
{
    EXPECT_ERROR(huffmanTreeFor(""));    // 没有字符
    EXPECT_ERROR(huffmanTreeFor("a"));   // 只有一个字符
    EXPECT_ERROR(huffmanTreeFor("aaa")); // 只有一个字符
}

PROVIDED_TEST("huffmanTreeFor builds tree for two characters.")
{
    EncodingTreeNode *reference = new EncodingTreeNode{
        ' ', new EncodingTreeNode{'a', nullptr, nullptr}, new EncodingTreeNode{'b', nullptr, nullptr}};

    EncodingTreeNode *tree = huffmanTreeFor("aaabbbb");
    EXPECT(isEncodingTree(tree));
    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("huffmanTreeFor works on the full range of characters.")
{
    /* 获取包含所有可能字符的字符串，然后将字符两两配对并观察结果。 */
    string allChars = pangrammaticString();
    for (size_t i = 0; i < allChars.size(); i += 2)
    {
        string toEncode;
        toEncode += allChars[i];
        toEncode += allChars[i + 1];
        toEncode += allChars[i + 1];

        EncodingTreeNode *reference = new EncodingTreeNode{
            ' ',
            new EncodingTreeNode{allChars[i], nullptr, nullptr},
            new EncodingTreeNode{allChars[i + 1], nullptr, nullptr}};

        EncodingTreeNode *tree = huffmanTreeFor(toEncode);
        EXPECT(isEncodingTree(tree));
        EXPECT(areEqual(tree, reference));

        deleteTree(reference);
        deleteTree(tree);
    }
}

PROVIDED_TEST("huffmanTreeFor uses cumulative weights (v1).")
{
    /* 这棵树如下：
     *                 *
     *                / \
     *               *   D
     *              / \
     *             C   *
     *                / \
     *               A   B
     */
    EncodingTreeNode *reference = new EncodingTreeNode{
        '*',
        new EncodingTreeNode{'!',
                             new EncodingTreeNode{'C', nullptr, nullptr},
                             new EncodingTreeNode{'?',
                                                  new EncodingTreeNode{'A', nullptr, nullptr},
                                                  new EncodingTreeNode{'B', nullptr, nullptr}}},
        new EncodingTreeNode{'D', nullptr, nullptr}};

    /* Ax2, Bx3, Cx4, Dx10 */
    EncodingTreeNode *tree = huffmanTreeFor("AABBBCCCCDDDDDDDDDD");
    EXPECT(isEncodingTree(tree));
    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("huffmanTreeFor uses cumulative weights (v2).")
{
    /*
     *          *
     *       /     \
     *      *       *
     *     / \     / \
     *    D   E   F   *
     *               / \
     *              C   *
     *                 / \
     *                A   B
     */
    EncodingTreeNode *reference = new EncodingTreeNode{
        ' ',
        new EncodingTreeNode{
            ' ',
            new EncodingTreeNode{'D', nullptr, nullptr},
            new EncodingTreeNode{'E', nullptr, nullptr}},
        new EncodingTreeNode{
            ' ',
            new EncodingTreeNode{'F', nullptr, nullptr},
            new EncodingTreeNode{
                ' ',
                new EncodingTreeNode{'C', nullptr, nullptr},
                new EncodingTreeNode{
                    ' ',
                    new EncodingTreeNode{'A', nullptr, nullptr},
                    new EncodingTreeNode{'B', nullptr, nullptr},
                }}}};

    /* Ax2, Bx3, Cx4, Dx6, Ex7, Fx8 */
    EncodingTreeNode *tree = huffmanTreeFor("AABBBCCCCDDDDDDEEEEEEEFFFFFFFF");
    EXPECT(isEncodingTree(tree));

    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("decodeText works on small sample.")
{
    /* 这棵树如下：
     *                 *
     *                / \
     *               O   *
     *                  / \
     *                 *   N
     *                / \
     *               M   S
     */
    EncodingTreeNode *tree = new EncodingTreeNode{
        '*',
        new EncodingTreeNode{'O', nullptr, nullptr},
        new EncodingTreeNode{'*',
                             new EncodingTreeNode{'*',
                                                  new EncodingTreeNode{'M', nullptr, nullptr},
                                                  new EncodingTreeNode{'S', nullptr, nullptr}},
                             new EncodingTreeNode{'N', nullptr, nullptr}}};

    /* 使用这棵树编码 MONSOON 后得到的结果。 */
    Queue<Bit> bits = {1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1};

    EXPECT_EQUAL(decodeText(bits, tree), "MONSOON");

    deleteTree(tree);
}

PROVIDED_TEST("Can decode all char values.")
{
    /* 所有可能的字符。 */
    string allChars = pangrammaticString();

    /* 尝试解码每一对相邻字符。 */
    for (size_t i = 0; i < allChars.size(); i += 2)
    {
        string expected;
        expected += allChars[i];
        expected += allChars[i + 1];
        expected += allChars[i + 1];

        EncodingTreeNode *tree = new EncodingTreeNode{
            ' ',
            new EncodingTreeNode{allChars[i], nullptr, nullptr},
            new EncodingTreeNode{allChars[i + 1], nullptr, nullptr}};

        /* 解码位流 011，它应还原为预期字符串。
         */
        Queue<Bit> bits = {0, 1, 1};
        EXPECT_EQUAL(decodeText(bits, tree), expected);

        deleteTree(tree);
    }
}

PROVIDED_TEST("encodeText works on small sample.")
{
    /* 这棵树如下：
     *                 *
     *                / \
     *               O   *
     *                  / \
     *                 *   N
     *                / \
     *               M   S
     */
    EncodingTreeNode *tree = new EncodingTreeNode{
        '*',
        new EncodingTreeNode{'O', nullptr, nullptr},
        new EncodingTreeNode{'*',
                             new EncodingTreeNode{'*',
                                                  new EncodingTreeNode{'M', nullptr, nullptr},
                                                  new EncodingTreeNode{'S', nullptr, nullptr}},
                             new EncodingTreeNode{'N', nullptr, nullptr}}};

    /* 使用这棵树编码 MONSOON 后得到的结果。 */
    Queue<Bit> expected = {1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1};

    EXPECT_EQUAL(encodeText("MONSOON", tree), expected);

    deleteTree(tree);
}

PROVIDED_TEST("Can encode all char values.")
{
    /* 所有可能的字符。 */
    string allChars = pangrammaticString();

    /* 尝试编码每一对相邻字符。 */
    for (size_t i = 0; i < allChars.size(); i += 2)
    {
        string toEncode;
        toEncode += allChars[i];
        toEncode += allChars[i + 1];
        toEncode += allChars[i + 1];

        EncodingTreeNode *tree = new EncodingTreeNode{
            ' ',
            new EncodingTreeNode{allChars[i], nullptr, nullptr},
            new EncodingTreeNode{allChars[i + 1], nullptr, nullptr}};

        /* 查看返回了哪些位。结果应为 011，因为第一个字符的编码是 0，
         * 第二个字符的编码是 1。
         */
        Queue<Bit> bits = encodeText(toEncode, tree);
        Queue<Bit> expected = {0, 1, 1};

        EXPECT_EQUAL(bits, expected);

        deleteTree(tree);
    }
}

PROVIDED_TEST("decodeText undoes encodeText on range of sample strings.")
{
    Vector<string> testCases = {
        "THAT THAT IS IS THAT THAT IS NOT IS NOT IS THAT IT IT IS",
        "AABAAABBABAAABAAAA",
        ":-) :-D XD <(^_^)>",
        pangrammaticString(),
    };

    for (string test : testCases)
    {
        /* 使用一种简单但低效的编码方案；无论提供什么字符，它都能正常工作。
         */
        EncodingTreeNode *tree = strandTreeFor(test);
        EXPECT(isEncodingTree(tree));

        Queue<Bit> bits = encodeText(test, tree);
        string result = decodeText(bits, tree);

        EXPECT_EQUAL(test.size(), result.size());
        EXPECT_EQUAL(test, result);

        deleteTree(tree);
    }
}

PROVIDED_TEST("Can decode an example tree.")
{
    /* 以下数据编码了这棵树：
     *
     *                 *
     *                / \
     *               *   C
     *              / \
     *             A   B
     */
    Queue<Bit> bits = {1, 1, 0, 0, 0};
    Queue<char> leaves = {'A', 'B', 'C'};

    EncodingTreeNode *tree = decodeTree(bits, leaves);
    EXPECT(isEncodingTree(tree));

    /* 确认这是正确的树。 */
    EncodingTreeNode *expected = new EncodingTreeNode{
        '*',
        new EncodingTreeNode{
            '*',
            new EncodingTreeNode{'A', nullptr, nullptr},
            new EncodingTreeNode{'B', nullptr, nullptr},
        },
        new EncodingTreeNode{'C', nullptr, nullptr}};

    EXPECT(areEqual(tree, expected));

    deleteTree(tree);
    deleteTree(expected);
}

PROVIDED_TEST("Can decode trees using all possible char values.")
{
    /* 所有可能的字符。 */
    string allChars = pangrammaticString();

    /* 尝试编码每一对相邻字符。 */
    for (size_t i = 0; i < allChars.size(); i += 2)
    {
        EncodingTreeNode *expected = new EncodingTreeNode{
            ' ',
            new EncodingTreeNode{allChars[i], nullptr, nullptr},
            new EncodingTreeNode{allChars[i + 1], nullptr, nullptr}};
        Queue<Bit> treeBits = {1, 0, 0};
        Queue<char> treeLeaves = {allChars[i], allChars[i + 1]};

        EncodingTreeNode *tree = decodeTree(treeBits, treeLeaves);
        EXPECT(isEncodingTree(tree));
        EXPECT(areEqual(tree, expected));

        deleteTree(tree);
        deleteTree(expected);
    }
}

PROVIDED_TEST("Can encode an example tree.")
{
    /* 为字符串 "ABBCCCC" 构造一棵编码树。它应如下所示：
     *
     *                 *
     *                / \
     *               *   C
     *              / \
     *             A   B
     *
     * 它会被压缩为
     *
     *        11000
     *        ABC
     */
    EncodingTreeNode *tree = huffmanTreeFor("ABBCCCC");

    Queue<Bit> bits;
    Queue<char> leaves;

    encodeTree(tree, bits, leaves);

    Queue<Bit> expectedBits = {1, 1, 0, 0, 0};
    Queue<char> expectedLeaves = {'A', 'B', 'C'};

    EXPECT_EQUAL(bits, expectedBits);
    EXPECT_EQUAL(leaves, expectedLeaves);

    deleteTree(tree);
}

PROVIDED_TEST("Can encode trees using all possible char values.")
{
    /* 所有可能的字符。 */
    string allChars = pangrammaticString();

    /* 尝试编码每一对相邻字符。 */
    for (size_t i = 0; i < allChars.size(); i += 2)
    {
        EncodingTreeNode *tree = new EncodingTreeNode{
            ' ',
            new EncodingTreeNode{allChars[i], nullptr, nullptr},
            new EncodingTreeNode{allChars[i + 1], nullptr, nullptr}};

        /* 查看返回的结果。它应是位串 100（根节点有两个子节点），以及按顺序
         * 排列的两个叶节点。
         */
        Queue<Bit> treeBits;
        Queue<char> treeLeaves;

        Queue<Bit> expectedBits = {1, 0, 0};
        Queue<char> expectedLeaves = {allChars[i], allChars[i + 1]};

        encodeTree(tree, treeBits, treeLeaves);
        EXPECT_EQUAL(treeBits, expectedBits);
        EXPECT_EQUAL(treeLeaves, expectedLeaves);

        deleteTree(tree);
    }
}

PROVIDED_TEST("decodeTree undoes encodeTree on sample strings.")
{
    /* 为包含所有字符的字符串构造一棵 Huffman 树。 */
    EncodingTreeNode *sourceTree = huffmanTreeFor(pangrammaticString());
    EXPECT(isEncodingTree(sourceTree));

    /* 先编码，再解码。 */
    Queue<Bit> bits;
    Queue<char> leaves;
    encodeTree(sourceTree, bits, leaves);

    EncodingTreeNode *resultTree = decodeTree(bits, leaves);
    EXPECT(isEncodingTree(resultTree));
    EXPECT(areEqual(sourceTree, resultTree));

    deleteTree(sourceTree);
    deleteTree(resultTree);
}

PROVIDED_TEST("Can decompress a small sample file.")
{
    HuffmanResult file = {
        {1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0},
        {'u', 'k', 'p', 'n', 'a', 'm', 'h'},
        {1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1,
         0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
         0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0}};

    EXPECT_EQUAL(decompress(file), "humuhumunukunukuapuaa");
}

PROVIDED_TEST("Compress reports errors on bad inputs.")
{
    EXPECT_ERROR(compress(""));
    EXPECT_ERROR(compress("A"));
    EXPECT_ERROR(compress("AAAA"));
}

PROVIDED_TEST("Can compress a small sample file.")
{
    HuffmanResult file = compress("ABANANAABANDANA");
    Queue<Bit> treeBits = {1, 1, 1, 0, 0, 0, 0};
    Queue<char> treeChars = {'D', 'B', 'N', 'A'};
    Queue<Bit> messageBits = {1, 0, 0, 1, 1, 0, 1, 1, 0,
                              1, 1, 1, 0, 0, 1, 1, 0, 1,
                              0, 0, 0, 1, 0, 1, 1};

    EXPECT_EQUAL(file.treeBits, treeBits);
    EXPECT_EQUAL(file.treeLeaves, treeChars);
    EXPECT_EQUAL(file.messageBits, messageBits);
}

PROVIDED_TEST("Compress undoes decompress on a range of strings.")
{
    Vector<string> testCases = {
        "THAT THAT IS IS THAT THAT IS NOT IS NOT IS THAT IT IT IS",
        "AABAAABBABAAABAAAA",
        ":-) :-D XD <(^_^)>",
        pangrammaticString(),
    };

    for (string test : testCases)
    {
        HuffmanResult file = compress(test);
        string result = decompress(file);

        EXPECT_EQUAL(result.size(), test.size());
        EXPECT_EQUAL(test, result);
    }
}
