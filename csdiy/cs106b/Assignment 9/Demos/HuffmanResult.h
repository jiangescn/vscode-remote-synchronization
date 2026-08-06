#pragma once

#include "../Huffman.h"
#include <iostream>

/**
 * 用于将 HuffmanResult 对象读写到磁盘的例程。其中代码
 * 这里才是真正访问磁盘文件的地方。欢迎查看
 * 并了解其工作方式，但你不需要调用这些函数，也不会
 * 需要理解它们如何组合在一起。
 */
void writeHuffmanFile(HuffmanResult& file, std::ostream& out);
HuffmanResult readHuffmanFile(std::istream& in);

