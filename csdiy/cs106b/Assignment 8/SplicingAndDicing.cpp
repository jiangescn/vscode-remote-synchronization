#include "SplicingAndDicing.h"
using namespace std;

/**
 * 释放 dna 指向的核苷酸链中的所有内存。如果
 * 如果输入为空指针，此函数不产生任何效果。
 *
 * 此函数应在 O(n) 时间内运行，并且不应使用任何容器
 * （例如 Vector、HashSet 等）。
 */
void deleteNucleotides(Nucleotide* dna) {
    /* TODO：删除此注释和下一行，并实现此函数。 */
    (void) dna;
}

/**
 * 返回拼写传入核苷酸序列内容的字符串
 * 作为参数。
 *
 * 此函数应在 O(n) 时间内运行，并且不应使用任何容器
 * （例如 Vector、HashSet 等）。
 */
string fromDNA(Nucleotide* dna) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) dna;
    return "";
}

/**
 * 生成一条新的核苷酸链，拼出以下参数给定的序列
 * str。
 *
 * 此函数应在 O(n) 时间内运行，并且不应使用任何容器
 * （例如 Vector、HashSet 等）。
 */
Nucleotide* toStrand(const string& str) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) str;
    return nullptr;
}

/**
 * 在 dna 中搜索目标序列的第一次出现，并返回指针
 * 指向该次出现的位置；如果目标序列不存在，则为 nullptr。
 *
 * 此函数没有指定的大 O 运行时间目标，但应当
 * 足够快，使每个压力测试在几秒内通过。
 *
 * 此函数不应使用任何容器（例如 Vector、HashSet 等）。
 */
Nucleotide* findFirst(Nucleotide* dna, Nucleotide* target) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) dna;
    (void) target;
    return nullptr;
}

/**
 * 删除序列中第一次出现的目标子序列
 * 由 dna 参数给出的核苷酸。如果所指向的核苷酸
 * 由于 dna 指向的内容被移除，dna 会更新为指向移除部分后的第一个核苷酸
 * 被移除的序列；如果整个序列都被移除，则为 nullptr。
 *
 * 此函数没有指定的大 O 运行时间目标，但应当
 * 足够快，使每个压力测试在几秒内通过。
 *
 * 此函数不应使用任何容器（例如 Vector、HashSet 等）。
 */
bool spliceFirst(Nucleotide*& dna, Nucleotide* target) {
    /* TODO：删除此注释及接下来的几行，然后实现此函数。 */
    (void) dna;
    (void) target;
    return false;
}



/* * * * * * 此处以下为测试用例 * * * * * */
#include "GUI/SimpleTest.h"

/* TODO：在此添加你自己的自定义测试！ */













/* * * * * 此处以下为提供的测试 * * * * */
#include "vector.h"
#include "strlib.h"
#include <fstream>

PROVIDED_TEST("deleteNucleotides cleans up a simple sequence.") {
    Nucleotide* dna = new Nucleotide;
    dna->value = 'A';
    dna->prev = nullptr;

    dna->next = new Nucleotide;
    dna->next->value = 'C';
    dna->next->prev = dna;
    dna->next->next = nullptr;

    /* 确认清理过程确实完成了清理。 */
    deleteNucleotides(dna);
}

PROVIDED_TEST("deleteNucleotides handles empty sequences.") {
    deleteNucleotides(nullptr);
}

const int kLargeNumber = 300000;

/* 返回文件内容的实用函数。如果最后一个参数
 * 不为 -1 时，只返回这么多个字符。
 */
string contentsOf(const string& filename, int numChars = -1) {
    ifstream input(filename);
    if (!input) error("Cannot open file " + filename);

    ostringstream buffer;
    buffer << input.rdbuf();
    string result = trim(buffer.str());

    return numChars == -1? result : result.substr(0, numChars);
}

/* 手动构造一个保存
 * 给定的字符串。此函数使用 Vector 类型，因此不能使用
 * 此处展示的实现策略用于你的 toStrand 实现。
 */
Nucleotide* vectorToStrand(const string& text) {
    Vector<Nucleotide*> cells;

    for (size_t i = 0; i < text.size(); i++) {
        cells += new Nucleotide;
    }
    for (size_t i = 0; i < text.size(); i++) {
        cells[i]->value = text[i];
        cells[i]->prev = (i == 0? nullptr : cells[i - 1]);
        cells[i]->next = (i == text.size() - 1? nullptr : cells[i + 1]);
    }

    return cells[0];
}

/* 返回大肠杆菌基因组内容的实用函数。 */
const string& eColiGenome() {
    static unique_ptr<string> theResult;
    if (!theResult) {
        theResult.reset(new string(contentsOf("res/EColi.dna", kLargeNumber)));
    }
    return *theResult;
}

PROVIDED_TEST("Stress Test: Can deallocate lengthy sequences.") {
    Nucleotide* ecoli = vectorToStrand(eColiGenome());

    /* 释放所有已分配内存。 */
    deleteNucleotides(ecoli);
}

PROVIDED_TEST("fromDNA handles empty strings.") {
    EXPECT_EQUAL(fromDNA(nullptr), "");
}

PROVIDED_TEST("fromDNA handles single-character strings.") {
    Nucleotide* singleton = new Nucleotide;
    singleton->value = 'A';
    singleton->next = singleton->prev = nullptr;

    EXPECT_EQUAL(fromDNA(singleton), "A");

    deleteNucleotides(singleton);
}

PROVIDED_TEST("fromDNA handles multicharacter strings.") {
    Nucleotide* one   = new Nucleotide;
    Nucleotide* two   = new Nucleotide;
    Nucleotide* three = new Nucleotide;
    Nucleotide* four  = new Nucleotide;

    one->prev    = nullptr;
    one->next    = two;

    two->prev    = one;
    two->next    = three;

    three->prev  = two;
    three->next  = four;

    four->prev   = three;
    four->next   = nullptr;

    one->value   = 'A';
    two->value   = 'C';
    three->value = 'T';
    four->value  = 'G';

    EXPECT_EQUAL(fromDNA(one), "ACTG");
    deleteNucleotides(one);
}

PROVIDED_TEST("fromDNA doesn't allocate memory.") {
    Nucleotide* one   = new Nucleotide;
    Nucleotide* two   = new Nucleotide;
    Nucleotide* three = new Nucleotide;
    Nucleotide* four  = new Nucleotide;

    one->prev    = nullptr;
    one->next    = two;

    two->prev    = one;
    two->next    = three;

    three->prev  = two;
    three->next  = four;

    four->prev   = three;
    four->next   = nullptr;

    one->value   = 'A';
    two->value   = 'C';
    three->value = 'T';
    four->value  = 'G';

    int allocs = NucleotideAlloc::instances();
    string result = fromDNA(one);
    EXPECT_EQUAL(allocs, NucleotideAlloc::instances());

    deleteNucleotides(one);
}

PROVIDED_TEST("Stress Test: fromDNA works on lengthy sequences.") {
    Nucleotide* dna = vectorToStrand(eColiGenome());

    string result = fromDNA(dna);
    EXPECT_EQUAL(result.length(), kLargeNumber);

    /* 不要使用 EXPECT_EQUAL；它会破坏控制台。 */
    EXPECT(result == eColiGenome());

    /* 释放所有已分配内存。 */
    deleteNucleotides(dna);
}

PROVIDED_TEST("toStrand converts empty strings.") {
    Nucleotide* dna = toStrand("");

    EXPECT_EQUAL(dna, nullptr);
}

PROVIDED_TEST("toStrand converts single-character strings.") {
    Nucleotide* dna = toStrand("A");
    EXPECT(dna != nullptr);
    EXPECT_EQUAL(dna->value, 'A');
    EXPECT_EQUAL(dna->next, nullptr);
    EXPECT_EQUAL(dna->prev, nullptr);

    deleteNucleotides(dna);
}

/* 检查链是否正确链接。 */
bool isLinkedInStrand(Nucleotide* start) {
    /* 如果位于链的起始处，则不应有 previous 指针。 */
    if (start != nullptr && start->prev != nullptr) {
        return false;
    }

    /* 遍历列表，确保每个位置的 next/prev 指针都
     * 彼此一致。
     */
    for (Nucleotide* curr = start; curr != nullptr; curr = curr->next) {
        if (curr->next != nullptr && curr->next->prev != curr) return false;
        if (curr->prev != nullptr && curr->prev->next != curr) return false;
    }

    return true;
}

PROVIDED_TEST("toStrand converts a multicharacter sequence.") {
    string original = "ACGT";
    Nucleotide* dna = toStrand(original);

    EXPECT(isLinkedInStrand(dna));

    /* 遍历序列并确认看到所需字母。 */
    Nucleotide* curr = dna;
    for (char ch: original) {
        /* 确认此处数据正确。 */
        EXPECT(curr != nullptr);
        EXPECT_EQUAL(curr->value, ch);

        curr = curr->next;
    }

    /* 确认刚刚越过末尾。 */
    EXPECT_EQUAL(curr, nullptr);

    deleteNucleotides(dna);
}

PROVIDED_TEST("Stress Test: Can load/convert E.Coli DNA (should take at most a few seconds).") {
    Nucleotide* dna = toStrand(eColiGenome());
    EXPECT(isLinkedInStrand(dna));

    /* 这里刻意不使用 EXPECT_EQUAL，因为如果此测试失败，我们不
     * 希望向控制台输出巨大的字符串。
     */
    EXPECT(fromDNA(dna) == eColiGenome());
    EXPECT(isLinkedInStrand(dna));

    deleteNucleotides(dna);
}

/* 返回指向核苷酸链中第 n 个单元格的指针。 */
Nucleotide* nth(Nucleotide* dna, int n) {
    for (int i = 0; i < n; i++) {
        if (dna == nullptr) error("Unexpected end of list.");
        dna = dna->next;
    }
    return dna;
}

PROVIDED_TEST("findFirst works for single nucleotide searching.") {
    Nucleotide* dna    = toStrand("ATATA");
    Nucleotide* target = toStrand("A");

    /* 从每个位置开始搜索，以确保找到预期内容。 */
    EXPECT_EQUAL(findFirst(nth(dna, 0), target), nth(dna, 0));
    EXPECT_EQUAL(findFirst(nth(dna, 1), target), nth(dna, 2));
    EXPECT_EQUAL(findFirst(nth(dna, 2), target), nth(dna, 2));
    EXPECT_EQUAL(findFirst(nth(dna, 3), target), nth(dna, 4));
    EXPECT_EQUAL(findFirst(nth(dna, 4), target), nth(dna, 4));
    EXPECT_EQUAL(findFirst(nth(dna, 5), target), nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target not present.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAAA");

    EXPECT_EQUAL(findFirst(dna, target), nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target is at front.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAA");

    EXPECT_EQUAL(findFirst(dna, target), dna);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target is at the back.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("CGGG");

    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 8));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target is in the middle.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("ATT");

    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 2));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target is empty.") {
    Nucleotide* dna = toStrand("AAATTTCCCGGG");

    EXPECT_EQUAL(findFirst(dna, nullptr), dna);
    deleteNucleotides(dna);
}

PROVIDED_TEST("findFirst works when DNA is empty.") {
    Nucleotide* target = toStrand("AAATTTCCCGGG");
    EXPECT_EQUAL(findFirst(nullptr, target), nullptr);
    EXPECT_EQUAL(findFirst(nullptr, nullptr), nullptr);

    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst works when target is the original sequence.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAATTTCCCGGG");

    EXPECT_EQUAL(findFirst(dna, target), dna);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("findFirst doesn't find string longer than original strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAATTTCCCGGGG");

    Nucleotide* result = findFirst(dna, target);
    EXPECT_EQUAL(result, nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

/* 释放旧链并用新链替换。 */
void reset(Nucleotide*& dna, const string& strand) {
    deleteNucleotides(dna);
    dna = toStrand(strand);
}

PROVIDED_TEST("findFirst works when partial matches exist.") {
    /* 当目标字符串的前几个字符满足以下条件时，会出现部分匹配：
     * 匹配 DNA 链的前几个字符。例如，链
     * AAAAC 与目标 AAC 匹配，但 AAC 有许多“几乎”匹配的位置
     * 匹配。
     *
     * 此测试抽样探索这些选项。
     */
    Nucleotide* dna    = toStrand("AAC");
    Nucleotide* target = toStrand("AC");

    /* 应在位置 1 匹配。 */
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 1));

    /* 扩展链并重试。 */
    reset(dna, "AAAC");
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 2));

    /* 尝试比较 AAAC 与 AAC。 */
    reset(dna, "AAAC");
    reset(target, "AAC");
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 1));

    /* AAAAC 与 AAC。 */
    reset(dna, "AAAAC");
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 2));

    /* 现在尝试一个更棘手的模式：ATATATC
     *                                ATATC
     */
    reset(dna,    "ATATATC");
    reset(target,   "ATATC");
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 2));

    /* ATATATATC
     *     ATATC
     */
    reset(dna,    "ATATATATC");
    reset(target,     "ATATC");
    EXPECT_EQUAL(findFirst(dna, target), nth(dna, 4));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("Stress Test: Can find at end of E.Coli (should take at most a few seconds).") {
    Nucleotide* dna = toStrand(eColiGenome());

    string tail = eColiGenome().substr(eColiGenome().size() - 80);
    Nucleotide* target = toStrand(tail);

    EXPECT(findFirst(dna, target) != nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("Stress Test: Can find E.Coli in itself (should take at most a few seconds).") {
    Nucleotide* dna    = toStrand(eColiGenome());
    Nucleotide* target = toStrand(eColiGenome());

    EXPECT_EQUAL(findFirst(dna, target), dna);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst on a missing sequence has no effect.") {
    Nucleotide* dna    = toStrand("TAGCATGATTACA");
    Nucleotide* target = toStrand("ATCG");

    /* 统计此时的分配次数。 */
    int allocs = NucleotideAlloc::instances();

    /* 确保移除失败，并确认此过程中没有
     * 更改 dna 指向的位置。
     */
    Nucleotide* originalDNA = dna;
    EXPECT(!spliceFirst(dna, target));
    EXPECT_EQUAL(dna, originalDNA);

    /* 确认链接结构有效。 */
    EXPECT(isLinkedInStrand(dna));

    /* 确认没有内存泄漏。如果有，则意味着 spliceFirst
     * 进行了分配或释放操作，而它不应这样做
     * 在这种情况下。
     */
    EXPECT_EQUAL(allocs, NucleotideAlloc::instances());
    EXPECT_EQUAL(fromDNA(dna), "TAGCATGATTACA");

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst works in the middle of a strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("TTTCCC");

    /* 移除该序列。确保没有改变 DNA 所在的位置
     * 指向。
     */
    Nucleotide* originalDNA = dna;
    EXPECT(spliceFirst(dna, target));

    /* 确认链接结构仍然良好。 */
    EXPECT(isLinkedInStrand(dna));

    EXPECT_EQUAL(fromDNA(dna), "AAAGGG");
    EXPECT_EQUAL(dna, originalDNA);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst works at the end of a strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("CCCGGG");

    /* 移除该序列。确保没有改变 DNA 所在的位置
     * 指向。
     */
    Nucleotide* originalDNA = dna;
    EXPECT(spliceFirst(dna, target));

    /* 确认链的连接方式仍然正确。 */
    EXPECT(isLinkedInStrand(dna));

    EXPECT_EQUAL(fromDNA(dna), "AAATTT");
    EXPECT_EQUAL(dna, originalDNA);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst works at the beginning of a strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAATTT");

    /* 在这种情况下，应更改 DNA 指向的位置。 */
    Nucleotide* originalDNA = dna;
    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));

    EXPECT_EQUAL(fromDNA(dna), "CCCGGG");
    EXPECT(dna != originalDNA);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst works when removing the whole strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAATTTCCCGGG");

    EXPECT(spliceFirst(dna, target));
    EXPECT_EQUAL(dna, nullptr);

    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst handles the empty string.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("");

    /* 确认执行此操作时没有改变 dna 指向的位置。 */
    Nucleotide* originalDNA = dna;
    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));

    EXPECT_EQUAL(fromDNA(dna), "AAATTTCCCGGG");
    EXPECT_EQUAL(dna, originalDNA);

    /* 还要尝试从空序列中移除，这应当成功，因为
     * 空序列出现在空序列的开头。
     */
    Nucleotide* empty = nullptr;
    EXPECT(spliceFirst(empty, target));
    EXPECT_EQUAL(empty, nullptr);

    deleteNucleotides(dna);
}

PROVIDED_TEST("spliceFirst leaves DNA unmodified except at remove site.") {
    /* 将 DNA 中所有链表单元写入一个 Vector，只为确保
     * 返回的单元格是否与预期单元格一致。
     */
    Nucleotide* dna = toStrand("AAACCCTTTGGG");
    Vector<Nucleotide*> nucleotides;
    for (Nucleotide* curr = dna; curr != nullptr; curr = curr->next) {
        nucleotides += curr;
    }

    /* 尝试不从 DNA 中移除任何内容，并确认与旧链匹配。 */
    Nucleotide* target = toStrand("GGGG");
    EXPECT(!spliceFirst(dna, target));

    int i = 0;
    for (Nucleotide* curr = dna; curr != nullptr; curr = curr->next) {
        EXPECT(i < nucleotides.size());
        EXPECT_EQUAL(curr, nucleotides[i]);
        i++;
    }
    EXPECT_EQUAL(i, nucleotides.size());

    deleteNucleotides(target);
    target = toStrand("CCC");

    /* 删除 C 核苷酸。 */
    EXPECT(nucleotides.size() >= 6);
    nucleotides.remove(3);
    nucleotides.remove(3);
    nucleotides.remove(3);
    EXPECT(spliceFirst(dna, target));

    i = 0;
    for (Nucleotide* curr = dna; curr != nullptr; curr = curr->next) {
        EXPECT(i < nucleotides.size());
        EXPECT_EQUAL(curr, nucleotides[i]);
        i++;
    }
    EXPECT_EQUAL(i, nucleotides.size());

    deleteNucleotides(target);

    /* 再来一次，不过这次从前端移除。 */
    target = toStrand("AAA");

    /* 删除 A 核苷酸。 */
    EXPECT(nucleotides.size() >= 3);
    nucleotides.remove(0);
    nucleotides.remove(0);
    nucleotides.remove(0);

    EXPECT(spliceFirst(dna, target));
    i = 0;
    for (Nucleotide* curr = dna; curr != nullptr; curr = curr->next) {
        EXPECT(i < nucleotides.size());
        EXPECT_EQUAL(curr, nucleotides[i]);
        i++;
    }
    EXPECT_EQUAL(i, nucleotides.size());

    deleteNucleotides(target);
    deleteNucleotides(dna);
}

PROVIDED_TEST("Repeated calls to spliceFirst work on strands.") {
    string dnaStrand = "ATGATAGCCATTAGCATATAAT";
    Nucleotide* dna    = toStrand(dnaStrand);
    Nucleotide* target = toStrand("AT");

    /* 不断删除 AT，直到一个也不剩。 */
    while (true) {
        bool exists = (dnaStrand.find("AT") != string::npos);
        EXPECT_EQUAL(spliceFirst(dna, target), exists);
        EXPECT(isLinkedInStrand(dna));

        /* 没有匹配？那么处理结束。 */
        if (!exists) break;

        auto position = dnaStrand.find("AT");
        dnaStrand.erase(position, 2);
    }

    /* 确认之后无法再取出一个元素。 */
    EXPECT(!spliceFirst(dna, target));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst works when target is longer than the original strand.") {
    Nucleotide* dna    = toStrand("AAATTTCCCGGG");
    Nucleotide* target = toStrand("AAATTTCCCGGGG");

    Nucleotide* oldDNA = dna;
    EXPECT(!spliceFirst(dna, target));
    EXPECT_EQUAL(dna, oldDNA);
    EXPECT(isLinkedInStrand(dna));

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("spliceFirst can remove all but the first/list nucleotide.") {
    Nucleotide* dna    = toStrand("AAAAC");
    Nucleotide* target = toStrand("AAAC");

    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));
    EXPECT_EQUAL(dna->value, 'A');
    EXPECT_EQUAL(dna->next,  nullptr);

    reset(dna,   "CAAAA");
    reset(target,"CAAA" );

    Nucleotide* expected = nth(dna, 4);
    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));
    EXPECT_EQUAL(dna, expected);
    EXPECT_EQUAL(dna->value, 'A');
    EXPECT_EQUAL(dna->next, nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("Stress Test: Can spliceFirst tail of E.Coli (should take at most a few seconds).") {
    Nucleotide* dna = toStrand(eColiGenome());

    string tail = eColiGenome().substr(eColiGenome().size() - 80);
    Nucleotide* target = toStrand(tail);

    Nucleotide* originalDNA = dna;
    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));

    /* 这里有意不使用 EXPECT_EQUAL，因为否则如果此测试
     * 否则失败时我们会向控制台输出一个巨大的字符串。
     */
    EXPECT(fromDNA(dna) == eColiGenome().substr(0, eColiGenome().size() - tail.size()));

    EXPECT_EQUAL(dna, originalDNA);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}

PROVIDED_TEST("Stress Test: Can spliceFirst E.Coli from itself (should take at most a few seconds).") {
    Nucleotide* dna    = toStrand(eColiGenome());
    Nucleotide* target = toStrand(eColiGenome());

    EXPECT(spliceFirst(dna, target));
    EXPECT(isLinkedInStrand(dna));

    EXPECT_EQUAL(dna, nullptr);

    deleteNucleotides(dna);
    deleteNucleotides(target);
}
