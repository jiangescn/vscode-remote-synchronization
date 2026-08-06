#include "HuffmanResult.h"
#include <cstdint>
using namespace std;

namespace {
    /**
     * 验证给定 HuffmanFile 是否满足预期的所有不变量。
     */
    void checkIntegrityOf(const HuffmanResult& file) {
        /* 不同字符的数量必须至少为两个。 */
        if (file.treeLeaves.size() < 2) {
            error("File must contain at least two distinct characters.");
        }

        /* 树位数量应恰好为 2c - 1，其中 c 是
         * 不同字符。
         */
        if (file.treeBits.size() != file.treeLeaves.size() * 2 - 1) {
            error("Wrong number of tree bits for the given leaves.");
        }
    }

    /* 用于读写单个位的实用类型。灵感来自
     * Julie Zelenski 的类似实现。
     */
    class BitWriter {
    public:
        explicit BitWriter(ostream& out) : out(out) {}
        ~BitWriter() {
            if (bitIndex != 0) flush();
        }

        void put(Bit b) {
            if (b != 0) {
                bitBuffer |= (1u << bitIndex);
            }

            bitIndex++;
            if (bitIndex == 8) {
                flush();
            }
        }

    private:
        void flush() {
            out.put(bitBuffer);
            bitBuffer = 0;
            bitIndex = 0;
        }

        ostream& out;
        uint8_t bitBuffer = 0;
        uint8_t bitIndex  = 0;
    };

    class BitReader {
    public:
        explicit BitReader(istream& in) : in(in) {

        }

        Bit get() {
            if (bitIndex == 8) readMore();

            Bit result = !!(bitBuffer & (1u << bitIndex));
            bitIndex++;
            return result;
        }

    private:
        istream& in;
        uint8_t bitBuffer = 0;
        uint8_t bitIndex  = 8;

        void readMore() {
            char read;
            if (!in.get(read)) {
                error("Unexpected end of file when reading bits.");
            }

            bitBuffer = read;
            bitIndex = 0;
        }
    };

    /* “CS106B A8” */
    const uint32_t kFileHeader = 0xC5106BA8;
}

/**
 * 我们按如下方式将 HuffmanResult 数据存储到磁盘：
 *
 *
 * 1 字节：不同字符的数量减一。
 * c 字节：按顺序排列的树叶。
 * 1 字节：最后一个字节中的有效位数。
 * n 位：树位，后跟消息位。
 *
 * 无需存储树中有多少位，因为它始终由
 * 乘以 2*c - 1，因为这是具有 c 个叶节点的满二叉树的节点数。
 */
void writeHuffmanFile(HuffmanResult& file, ostream& out) {
    /* 验证不变量。 */
    checkIntegrityOf(file);

    /* 写入魔数头。 */
    out.write(reinterpret_cast<const char *>(&kFileHeader), sizeof kFileHeader);

    /* 字符数。 */
    const uint8_t charByte = file.treeLeaves.size() - 1;
    out.put(charByte);

    /* 树的叶节点。 */
    while (!file.treeLeaves.isEmpty()) out.put(file.treeLeaves.dequeue());

    /* 最后一个字节中要读取的位数。 */
    uint8_t modulus = (file.treeBits.size() + file.messageBits.size()) % 8;
    if (modulus == 0) modulus = 8;
    out.put(modulus);

    /* 位本身。 */
    BitWriter writer(out);
    while (!file.treeBits.isEmpty()) writer.put(file.treeBits.dequeue());
    while (!file.messageBits.isEmpty()) writer.put(file.messageBits.dequeue());
}

/**
 * 从磁盘解码 Huffman 文件。
 */
HuffmanResult readHuffmanFile(istream& in) {
    /* 读回魔数标头并确保匹配。 */
    uint32_t header;
    if (!in.read(reinterpret_cast<char *>(&header), sizeof header) ||
        header != kFileHeader) {
        error("Chosen file is not a Huffman-compressed file.");
    }

    HuffmanResult result;

    /* 读取字符计数。 */
    char skewCharCount;
    if (!in.get(skewCharCount)) {
        error("Error reading character count.");
    }

    /* 我们将其偏移了 1——把 1 加回来。 */
    int charCount = uint8_t(skewCharCount);
    charCount++;

    if (charCount < 2) {
        error("Character count is too low for this to be a valid file.");
    }

    /* 读入叶节点。 */
    vector<char> leaves(charCount);
    if (!in.read(leaves.data(), leaves.size())) {
        error("Could not read in all tree leaves.");
    }
    for (char leaf: leaves) {
        result.treeLeaves.enqueue(leaf);
    }

    /* 读入 modulus。 */
    char signedModulus;
    if (!in.get(signedModulus)) {
        error("Error reading modulus.");
    }
    uint8_t modulus = signedModulus;

    /* 查看需要读取多少位。为此，跳转到文件末尾
     * 并返回当前位置以计算字节数，然后将其转换为数字
     * 位。
     *
     * 感谢 Julie Zelenski 提出此技巧！
     */
    auto currPos = in.tellg();
    if (!in.seekg(0, istream::end)) {
        error("Error seeking to end of file.");
    }
    auto endPos  = in.tellg();
    if (!in.seekg(currPos, istream::beg)) {
        error("Error seeking back to middle of file.");
    }

    /* 要读取的位数 =（字节数 - 1）* 8 + modulus。 */
    uint64_t bitsToRead = (endPos - currPos - 1) * 8 + modulus;

    /* 读入树位。 */
    BitReader reader(in);
    for (int i = 0; i < 2 * charCount - 1; i++) {
        result.treeBits.enqueue(reader.get());
        bitsToRead--;
    }

    /* 读入消息位。 */
    while (bitsToRead > 0) {
        result.messageBits.enqueue(reader.get());
        bitsToRead--;
    }

    return result;
}

/* 用于调试。 */
ostream& operator<< (ostream& out, const HuffmanResult& file) {
    ostringstream builder;
    builder << "{treeBits:" << file.treeBits
            << ",treeLeaves:" << file.treeLeaves
            << ",messageBits:" << file.messageBits
            << "}";
    return out << builder.str();
}
