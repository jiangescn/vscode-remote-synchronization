#include "Huffman.h"
using namespace std;

/**
 * 释放 Huffman 树中的所有节点。我们提供了此辅助函数
 * 提供给你，因为我们的测试驱动程序也会使用它，并且认为你可能也想
 * 使用它。
 */
void deleteTree(EncodingTreeNode* tree) {
    if (tree != nullptr) {
        deleteTree(tree->zero);
        deleteTree(tree->one);
        delete tree;
    }
}

/**
 * 使用以下算法为给定字符串构造 Huffman 编码树：
 * 课堂中讲述的方式。
 *
 * 如果输入字符串不包含至少两个不同字符，
 * 此函数应报告错误。
 *
 * 由较小的树组装较大的树时，确保设置第一个
 * 从队列中取出的树作为新树的零子树，而
 * 将第二棵树作为唯一子树。
 */
EncodingTreeNode* huffmanTreeFor(const string& str) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) str;
    return nullptr;
}

/**
 * 给定包含压缩消息的 Queue<Bit> 和用于编码的树
 * 编码这些位，并将这些位解码回原始消息。
 *
 * 可以假定输入树非 null 且不是单个字符；
 * 这些是你无需处理的边界情况。
 *
 * 可以假定输入 Queue<Bit> 格式正确，即每个字符
 * 已正确编码，Queue 中没有多余位等。
 */
string decodeText(Queue<Bit>& bits, EncodingTreeNode* tree) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) bits;
    (void) tree;
    return "";
}

/**
 * 给定字符串和 Huffman 编码树，使用该树对文本编码
 * 并输出与编码表示对应的 Queue<Bit>。
 *
 * 输入树不会为空，也不会只包含单个节点；这些
 * 这些是无需处理的边界情况。输入树将包含所有
 * 构成输入字符串的字符。
 */
Queue<Bit> encodeText(const string& str, EncodingTreeNode* tree) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) str;
    (void) tree;
    return {};
}

/**
 * 将给定 Queue<Bit> 和 Queue<char> 解码为 Huffman 编码树。
 *
 * 可以假定输入 Queue 的结构正确，即它们
 * 表示树的合法编码，并且不存在多余字符
 * 或其中的位等。
 */
EncodingTreeNode* decodeTree(Queue<Bit>& bits, Queue<char>& leaves) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) bits;
    (void) leaves;
    return nullptr;
}

/**
 * 按照以下方式将给定 Huffman 树编码为 Queue<Bit> 和 Queue<char>：
 * 作业讲义中指定。
 *
 * 可以假定进入此函数时输入 Queue 为空。
 *
 * 可以假定提供的 Huffman 树结构正确，
 * 其中每个内部节点都有两个子节点，且只有字符位于
 * 叶节点是否重要等。
 */
void encodeTree(EncodingTreeNode* tree, Queue<Bit>& bits, Queue<char>& leaves) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) tree;
    (void) bits;
    (void) leaves;
}

/**
 * 使用 Huffman 编码压缩给定文本字符串，输出
 * 包含编码树和消息的 HuffmanResult。
 *
 * 如果存在以下情况，你对此函数的实现应报告错误：
 * 输入字符串中不同字符少于两个。
 */
HuffmanResult compress(const string& text) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) text;
    return {};
}

/**
 * 解压给定 HuffmanResult 并返回其表示的字符串。
 *
 * 你的实现可以按认为合适的方式修改 file 参数。其中
 * 对此函数结束后应呈现何种状态没有要求
 * 返回。
 *
 * 可以假定输入文件格式正确，并由正确的
 * compress 的实现。
 */
string decompress(HuffmanResult& file) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) file;
    return "";
}


/* * * * * * 此处以下为测试用例 * * * * * */
#include "GUI/SimpleTest.h"

/* TODO：在此添加你自己的自定义测试！ */













/* * * * * 此处以下为提供的测试 * * * * */
#include <limits>

/* 测试所谓 Huffman 树是否确实为 Huffman 树的实用函数。
 * 具体来说，检查每个内部节点是否恰好有零个或两个
 * 子节点。还有其他方式可能生成无效的 Huffman 树，例如
 * 例如，使用未初始化指针或链接成环——但我们
 * 不要在此处测试该情况。
 */
bool isEncodingTree(EncodingTreeNode* tree) {
    /* 空树不是 Huffman 树。 */
    if (tree == nullptr) return false;

    /* 如果缺少一个子节点，则应同时缺少两个子节点。 */
    if ((tree->zero == nullptr) != (tree->one == nullptr)) return false;

    /* 只要存在子节点，它们就必须是 Huffman 树。 */
    return tree->zero == nullptr || (isEncodingTree(tree->zero) && isEncodingTree(tree->one));
}

/* 测试两棵树是否相等的实用函数。此函数改编自第
 * 讲义 8，并针对 Huffman 树进行了具体化。
 */
bool areEqual(EncodingTreeNode* lhs, EncodingTreeNode* rhs) {
    /* 基本情况：如果任一节点是叶节点，则二者都应是叶节点。 */
    bool lhsLeaf = lhs->zero == nullptr && lhs->one == nullptr;
    bool rhsLeaf = rhs->zero == nullptr && rhs->one == nullptr;
    if (lhsLeaf || rhsLeaf) {
        return lhs->ch == rhs->ch && lhsLeaf == rhsLeaf;
    }

    /* 否则，两者都是内部节点。检查它们是否匹配。 */
    return areEqual(lhs->zero, rhs->zero) && areEqual(lhs->one, rhs->one);
}

/* 返回包含所有可能字符的字符串的实用函数。 */
string pangrammaticString() {
    string result;

    char ch = numeric_limits<char>::min();
    result += ch;
    do {
        ch++;
        result += ch;
    } while (ch != numeric_limits<char>::max());

    return result;
}

/* 创建低效但仍有效的编码树的实用函数
 * 用于给定字符。
 */
EncodingTreeNode* strandTreeFor(const string& text, size_t index = 0) {
    if (index == text.size()) error("No characters provided to strandTreeFor.");

    /* 我们始终得到一个叶节点。 */
    EncodingTreeNode* leaf = new EncodingTreeNode {
        text[index], nullptr, nullptr
    };

    /* 最后一个字符？如果是，到此结束。 */
    if (index + 1 == text.size()) return leaf;

    /* 否则，构建一棵更大的树。 */
    else return new EncodingTreeNode {
        ' ', leaf, strandTreeFor(text, index + 1)
    };
}

PROVIDED_TEST("huffmanTreeFor reports errors on invalid inputs.") {
    EXPECT_ERROR(huffmanTreeFor(""));    // 没有字符
    EXPECT_ERROR(huffmanTreeFor("a"));   // 一个字符
    EXPECT_ERROR(huffmanTreeFor("aaa")); // 一个字符
}

PROVIDED_TEST("huffmanTreeFor builds tree for two characters.") {
    EncodingTreeNode* reference = new EncodingTreeNode {
        ' ', new EncodingTreeNode {'a', nullptr, nullptr}, new EncodingTreeNode {'b', nullptr, nullptr}
    };

    EncodingTreeNode* tree = huffmanTreeFor("aaabbbb");
    EXPECT(isEncodingTree(tree));
    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("huffmanTreeFor works on the full range of characters.") {
    /* 获取所有可能字符的字符串，然后两两配对并查看结果。 */
    string allChars = pangrammaticString();
    for (size_t i = 0; i < allChars.size(); i += 2) {
        string toEncode;
        toEncode += allChars[i];
        toEncode += allChars[i + 1];
        toEncode += allChars[i + 1];

        EncodingTreeNode* reference = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        EncodingTreeNode* tree = huffmanTreeFor(toEncode);
        EXPECT(isEncodingTree(tree));
        EXPECT(areEqual(tree, reference));

        deleteTree(reference);
        deleteTree(tree);
    }
}

PROVIDED_TEST("huffmanTreeFor uses cumulative weights (v1).") {
    /* 此树：
     *                 *
     *                / \
     *               *   D
     *              / \
     *             C   *
     *                / \
     *               A   B
     */
    EncodingTreeNode* reference = new EncodingTreeNode {
        '*',
            new EncodingTreeNode { '!',
                new EncodingTreeNode { 'C', nullptr, nullptr },
                new EncodingTreeNode { '?',
                    new EncodingTreeNode { 'A', nullptr, nullptr },
                    new EncodingTreeNode { 'B', nullptr, nullptr }
                }
            },
            new EncodingTreeNode { 'D', nullptr, nullptr }
    };

    /* Ax2、Bx3、Cx4、Dx10 */
    EncodingTreeNode* tree = huffmanTreeFor("AABBBCCCCDDDDDDDDDD");
    EXPECT(isEncodingTree(tree));
    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("huffmanTreeFor uses cumulative weights (v2).") {
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
    EncodingTreeNode* reference =new EncodingTreeNode {
        ' ',
        new EncodingTreeNode {
            ' ',
            new EncodingTreeNode{ 'D', nullptr, nullptr },
            new EncodingTreeNode{ 'E', nullptr, nullptr }
        },
        new EncodingTreeNode {
            ' ',
            new EncodingTreeNode{ 'F', nullptr, nullptr },
            new EncodingTreeNode {
                ' ',
                new EncodingTreeNode{ 'C', nullptr, nullptr },
                new EncodingTreeNode{
                    ' ',
                    new EncodingTreeNode{ 'A', nullptr, nullptr },
                    new EncodingTreeNode{ 'B', nullptr, nullptr },
                }
            }
        }
    };

    /* Ax2、Bx3、Cx4、Dx6、Ex7、Fx8 */
    EncodingTreeNode* tree = huffmanTreeFor("AABBBCCCCDDDDDDEEEEEEEFFFFFFFF");
    EXPECT(isEncodingTree(tree));

    EXPECT(areEqual(tree, reference));

    deleteTree(reference);
    deleteTree(tree);
}

PROVIDED_TEST("decodeText works on small sample.") {
    /* 此树：
     *                 *
     *                / \
     *               O   *
     *                  / \
     *                 *   N
     *                / \
     *               M   S
     */
    EncodingTreeNode* tree = new EncodingTreeNode {
        '*',
            new EncodingTreeNode { 'O', nullptr, nullptr },
            new EncodingTreeNode { '*',
                new EncodingTreeNode{ '*',
                    new EncodingTreeNode { 'M', nullptr, nullptr },
                    new EncodingTreeNode { 'S', nullptr, nullptr }
                },
                new EncodingTreeNode{ 'N', nullptr, nullptr }
            }
    };

    /* 使用这棵树编码 MONSOON 后得到的结果。 */
    Queue<Bit> bits = { 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1 };

    EXPECT_EQUAL(decodeText(bits, tree), "MONSOON");

    deleteTree(tree);
}

PROVIDED_TEST("Can decode all char values.") {
    /* 所有可能的字符。 */
    string allChars = pangrammaticString();

    /* 尝试解码所有相邻字符对。 */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        string expected;
        expected += allChars[i];
        expected += allChars[i + 1];
        expected += allChars[i + 1];

        EncodingTreeNode* tree = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        /* 解码位流 011，它应映射回预期的
         * 字符串。
         */
        Queue<Bit> bits = { 0, 1, 1 };
        EXPECT_EQUAL(decodeText(bits, tree), expected);

        deleteTree(tree);
    }
}

PROVIDED_TEST("encodeText works on small sample.") {
    /* 此树：
     *                 *
     *                / \
     *               O   *
     *                  / \
     *                 *   N
     *                / \
     *               M   S
     */
    EncodingTreeNode* tree = new EncodingTreeNode {
           '*',
           new EncodingTreeNode { 'O', nullptr, nullptr },
               new EncodingTreeNode { '*',
               new EncodingTreeNode{ '*',
               new EncodingTreeNode { 'M', nullptr, nullptr },
               new EncodingTreeNode { 'S', nullptr, nullptr }
            },
            new EncodingTreeNode{ 'N', nullptr, nullptr }
        }
    };

    /* 使用这棵树编码 MONSOON 后得到的结果。 */
    Queue<Bit> expected = { 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1 };

    EXPECT_EQUAL(encodeText("MONSOON", tree), expected);

    deleteTree(tree);
}

PROVIDED_TEST("Can encode all char values.") {
    /* 所有可能的字符。 */
    string allChars = pangrammaticString();

    /* 尝试编码每一对相邻字符。 */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        string toEncode;
        toEncode += allChars[i];
        toEncode += allChars[i + 1];
        toEncode += allChars[i + 1];

        EncodingTreeNode* tree = new EncodingTreeNode {
                ' ',
                new EncodingTreeNode {allChars[i], nullptr, nullptr},
                new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        /* 查看返回的位。应得到 011，因为第一个
         * 第一个字符的编码为 0，第二个字符的编码为 1。
         */
        Queue<Bit> bits = encodeText(toEncode, tree);
        Queue<Bit> expected = { 0, 1, 1 };

        EXPECT_EQUAL(bits, expected);

        deleteTree(tree);
    }
}

PROVIDED_TEST("decodeText undoes encodeText on range of sample strings.") {
    Vector<string> testCases = {
        "THAT THAT IS IS THAT THAT IS NOT IS NOT IS THAT IT IT IS",
        "AABAAABBABAAABAAAA",
        ":-) :-D XD <(^_^)>",
        pangrammaticString(),
    };

    for (string test: testCases) {
        /* 使用一种看似简单但无论
         * 提供了字符。
         */
        EncodingTreeNode* tree = strandTreeFor(test);
        EXPECT(isEncodingTree(tree));

        Queue<Bit> bits = encodeText(test, tree);
        string result = decodeText(bits, tree);

        EXPECT_EQUAL(test.size(), result.size());
        EXPECT_EQUAL(test, result);

        deleteTree(tree);
    }
}

PROVIDED_TEST("Can decode an example tree.") {
    /* 这会编码以下树：
     *
     *                 *
     *                / \
     *               *   C
     *              / \
     *             A   B
     */
    Queue<Bit>  bits   = { 1, 1, 0, 0, 0 };
    Queue<char> leaves = { 'A', 'B', 'C' };

    EncodingTreeNode* tree = decodeTree(bits, leaves);
    EXPECT(isEncodingTree(tree));

    /* 确认这是正确的树。 */
    EncodingTreeNode* expected = new EncodingTreeNode {
        '*',
            new EncodingTreeNode {
                '*',
                new EncodingTreeNode { 'A', nullptr, nullptr },
                new EncodingTreeNode { 'B', nullptr, nullptr },
            },
            new EncodingTreeNode { 'C', nullptr, nullptr }
    };

    EXPECT(areEqual(tree, expected));

    deleteTree(tree);
    deleteTree(expected);
}

PROVIDED_TEST("Can decode trees using all possible char values.") {
    /* 所有可能的字符。 */
    string allChars = pangrammaticString();

    /* 尝试编码每一对相邻字符。 */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        EncodingTreeNode* expected = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };
        Queue<Bit>  treeBits   = { 1, 0, 0 };
        Queue<char> treeLeaves = { allChars[i], allChars[i + 1] };

        EncodingTreeNode* tree = decodeTree(treeBits, treeLeaves);
        EXPECT(isEncodingTree(tree));
        EXPECT(areEqual(tree, expected));

        deleteTree(tree);
        deleteTree(expected);
    }
}

PROVIDED_TEST("Can encode an example tree.") {
    /* 为“ABBCCCC”构建编码树。它应如下所示：
     *
     *                 *
     *                / \
     *               *   C
     *              / \
     *             A   B
     *
     * 这会压缩为
     *
     *        11000
     *        ABC
     */
    EncodingTreeNode* tree = huffmanTreeFor("ABBCCCC");

    Queue<Bit>  bits;
    Queue<char> leaves;

    encodeTree(tree, bits, leaves);

    Queue<Bit>  expectedBits   = { 1, 1, 0, 0, 0 };
    Queue<char> expectedLeaves = { 'A', 'B', 'C' };

    EXPECT_EQUAL(bits,   expectedBits);
    EXPECT_EQUAL(leaves, expectedLeaves);

    deleteTree(tree);
}

PROVIDED_TEST("Can encode trees using all possible char values.") {
    /* 所有可能的字符。 */
    string allChars = pangrammaticString();

    /* 尝试编码每一对相邻字符。 */
    for (size_t i = 0; i < allChars.size(); i += 2) {
        EncodingTreeNode* tree = new EncodingTreeNode {
            ' ',
            new EncodingTreeNode {allChars[i], nullptr, nullptr},
            new EncodingTreeNode {allChars[i + 1], nullptr, nullptr}
        };

        /* 查看返回结果。应为位串 100（根节点具有
         * 两个子节点）以及两个叶节点，按顺序排列。
         */
        Queue<Bit>  treeBits;
        Queue<char> treeLeaves;

        Queue<Bit>  expectedBits = { 1, 0, 0 };
        Queue<char> expectedLeaves = { allChars[i], allChars[i + 1] };

        encodeTree(tree, treeBits, treeLeaves);
        EXPECT_EQUAL(treeBits, expectedBits);
        EXPECT_EQUAL(treeLeaves, expectedLeaves);

        deleteTree(tree);
    }
}

PROVIDED_TEST("decodeTree undoes encodeTree on sample strings.") {
    /* 为包含所有字符的字符串创建 Huffman 树。 */
    EncodingTreeNode* sourceTree = huffmanTreeFor(pangrammaticString());
    EXPECT(isEncodingTree(sourceTree));

    /* 编码，然后解码。 */
    Queue<Bit>  bits;
    Queue<char> leaves;
    encodeTree(sourceTree, bits, leaves);

    EncodingTreeNode* resultTree = decodeTree(bits, leaves);
    EXPECT(isEncodingTree(resultTree));
    EXPECT(areEqual(sourceTree, resultTree));

    deleteTree(sourceTree);
    deleteTree(resultTree);
}

PROVIDED_TEST("Can decompress a small sample file.") {
    HuffmanResult file = {
        { 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0 },
        { 'u', 'k', 'p', 'n', 'a', 'm', 'h' },
        { 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1,
          0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
          0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0 }
    };

    EXPECT_EQUAL(decompress(file), "humuhumunukunukuapuaa");
}

PROVIDED_TEST("Compress reports errors on bad inputs.") {
    EXPECT_ERROR(compress(""));
    EXPECT_ERROR(compress("A"));
    EXPECT_ERROR(compress("AAAA"));
}

PROVIDED_TEST("Can compress a small sample file.") {
    HuffmanResult file = compress("ABANANAABANDANA");
    Queue<Bit>  treeBits    = { 1, 1, 1, 0, 0, 0, 0 };
    Queue<char> treeChars   = { 'D', 'B', 'N', 'A' };
    Queue<Bit>  messageBits = { 1, 0, 0, 1, 1, 0, 1, 1, 0,
                                1, 1, 1, 0, 0, 1, 1, 0, 1,
                                0, 0, 0, 1, 0, 1, 1 };

    EXPECT_EQUAL(file.treeBits, treeBits);
    EXPECT_EQUAL(file.treeLeaves, treeChars);
    EXPECT_EQUAL(file.messageBits, messageBits);
}

PROVIDED_TEST("Compress undoes decompress on a range of strings.") {
    Vector<string> testCases = {
        "THAT THAT IS IS THAT THAT IS NOT IS NOT IS THAT IT IT IS",
        "AABAAABBABAAABAAAA",
        ":-) :-D XD <(^_^)>",
        pangrammaticString(),
    };

    for (string test: testCases) {
        HuffmanResult file = compress(test);
        string result = decompress(file);

        EXPECT_EQUAL(result.size(), test.size());
        EXPECT_EQUAL(test, result);
    }
}
