#include "../SplicingAndDicing.h"
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

namespace {
    /* 分配器魔数，用于内部验证我们没有
     * 对指针执行某些不合理操作（并确保已释放的
     * 指针实际上有效！）
     */
    const uint32_t kMagicHeader = 0xC5106BA7; // CS106B, A7
    const uint32_t kMagicFooter = 0x13710642; // 137, 106, 42

    /* 一块足以容纳 Nucleotide 的内存。 */
    struct Block {
        uint32_t header = kMagicHeader;
        bool isFree = true;
        alignas(Nucleotide) char buffer[sizeof(Nucleotide)];
        uint32_t footer = kMagicFooter;
    };

    /* 所有可用块的列表。
     *
     * TODO：这里可能应使用 std::vector，而不是原始
     * 数组。
     */
    Block* theQueue;
    Block* theHead;
    const size_t kNumObjects = 1 << 22; // 400 万个核苷酸，远超所需数量。

    /* 已分配的实例数量。 */
    int theNumInstances = 0;

    /* 设置和拆除内存块。 */
    struct MemoryInitializer {
        MemoryInitializer() {
            theQueue = new Block[kNumObjects]();
            theHead  = theQueue;

            /* 用垃圾值填充所有块。 */
            for (size_t i = 0; i < kNumObjects; i++) {
                fill(begin(theQueue[i].buffer), end(theQueue[i].buffer), 0xBA);
            }
        }

        ~MemoryInitializer() {
            delete[] theQueue;
        }
    } theInitializer;
}

void* NucleotideAlloc::alloc(size_t numBytes) {
    ++theNumInstances;

    /* 如果分配的字节数不是预期值，则一定有问题
     * 是错误的。
     */
    if (numBytes != sizeof(Nucleotide)) {
        abort();
    }

    /* 一直遍历，直到找到空闲内存块。 */
    Block* orig = theHead;
    do {
        /* 如果此处空闲，则占用该空间。 */
        if (theHead->isFree) {
            /* 占用此位置。 */
            theHead->isFree = false;
            void* result = theHead->buffer;

            /* 前进到下一个空闲槽位。 */
            theHead++;
            if (theHead - theQueue == kNumObjects) {
                theHead = theQueue;
            }

            return result;
        }
    } while (theHead != orig);

    /* 糟糕，失败了。 */
    return ::operator new(numBytes);
}

void NucleotideAlloc::free(void* memory) {
    --theNumInstances;

    /* 如果位于队列内部，很好！回收该空间。 */
    if (memory >= theQueue && memory < theQueue + kNumObjects) {
        /* 将其映射回块，并确认没有发生未对齐。 */
        Block* theBlock = reinterpret_cast<Block*>(static_cast<char*>(memory) - offsetof(Block, buffer));
        if (theBlock->header != kMagicHeader || theBlock->footer != kMagicFooter) {
            abort();
        }

        /* 此时该内存块不应处于空闲状态。如果是，则发生了重复释放。 */
        if (theBlock->isFree) {
            cerr << "You have attempted to delete a Nucleotide object that is no longer allocated. "
                    "This may indicate that you are trying to delete the same pointer multiple times, "
                    "which is not allowed. Run your program with the debugger engaged and walk up the "
                    "call stack to identify the code that's deleting the same Nucleotide many times." << endl;
            abort();
        }

        /* 将块标记为空闲，并破坏块中的内存，使对它的使用
         * 越晚越可能触发错误。
         */
        theBlock->isFree = true;
        fill(begin(theBlock->buffer), end(theBlock->buffer), 0xBA);
    } else {
        ::operator delete(memory);
    }
}

int NucleotideAlloc::instances() {
    return theNumInstances;
}
