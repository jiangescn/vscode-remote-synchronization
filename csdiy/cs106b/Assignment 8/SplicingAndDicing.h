#pragma once
#include "Demos/NucleotideAlloc.h"

/**
 * 表示核苷酸的类型。请勿对此进行任何更改
 * 解决此问题过程中使用的 struct；不过，你也不应
 * 发现自己也需要这样做。
 */
struct Nucleotide {
    char value;
    Nucleotide* next;
    Nucleotide* prev;

    /* 此自定义宏有助于检测内存泄漏。 */
    TRACK_ALLOCATIONS_OF(Nucleotide);
};

