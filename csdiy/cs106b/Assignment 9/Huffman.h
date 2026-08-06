#pragma once

#include "Demos/Bit.h"
#include "GUI/MemoryDiagnostics.h"
#include "queue.h"
#include <string>
#include <ostream>

/**
 * 表示编码树中节点的类型。每个节点存储两个指针，
 * 一条指向标签为 0 的子节点，另一条指向标签为 1 的子节点。
 *
 * 树中的每个节点都有一个关联字符。但是，此字段
 * 仅当节点是叶节点（即没有子节点的节点）时才有意义。
 * 除非确定节点中的字符
 * 节点是叶节点。
 *
 * 完成本作业时不要修改此类型。
 */
struct EncodingTreeNode {
    char ch;
    EncodingTreeNode* zero;
    EncodingTreeNode* one;

    TRACK_ALLOCATIONS_OF(EncodingTreeNode); // 用于测试
};

/**
 * 表示 Huffman 编码文件的类型。
 *
 * 完成本作业时不要修改此类型。
 */
struct HuffmanResult {
    Queue<Bit>  treeBits;
    Queue<char> treeLeaves;
    Queue<Bit>  messageBits;
};

/* 出于调试目的，可以将 HuffmanResult 对象打印到 cout，以查看
 * 它们包含什么。
 */
std::ostream& operator<< (std::ostream& out, const HuffmanResult& file);

/**
 * 端到端处理例程。
 */
HuffmanResult compress(const std::string& text);
std::string decompress(HuffmanResult& file);
