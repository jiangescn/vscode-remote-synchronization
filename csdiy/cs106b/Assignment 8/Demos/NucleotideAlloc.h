#pragma once
#include "../GUI/MemoryDiagnostics.h"

/* 更快分配 Nucleotide 类型；用于提高以下场景的性能：
 * Windows。你无需研究其工作原理。
 */
namespace NucleotideAlloc {
    void* alloc(std::size_t numBytes);
    void  free(void* memory);

    int instances();
}

struct Nucleotide;
namespace MemoryDiagnostics {
    template <> struct Allocator<Nucleotide> {
        static void* scalarAlloc(std::size_t numBytes) {
            return NucleotideAlloc::alloc(numBytes);
        }
        static void* vectorAlloc(std::size_t numBytes) {
            return ::operator new[](numBytes);
        }
        static void scalarFree(void* memory) {
            NucleotideAlloc::free(memory);
        }
        static void vectorFree(void* memory) {
            ::operator delete[](memory);
        }
    };
}
