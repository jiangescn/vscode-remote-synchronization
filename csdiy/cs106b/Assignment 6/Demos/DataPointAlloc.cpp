#include "Demos/DataPointAlloc.h"
#include "Demos/DataPoint.h"
#include "strlib.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

namespace {
    /* 你好！如果调试器将你带到这里，这意味着
     * 你的代码中存在某种内存错误
     * 程序。请查看以下位置的“应用程序输出”选项卡
     * 在 Qt Creator 中查看刚刚出现的错误消息
     * 打印后，沿调用栈向上查看
     * 具体错误发生的位置。
     */
    [[ noreturn ]] void emergencyAbort(const char* message) {
        cerr << message << endl;
        abort();
    }
}

namespace DataPointUtils {
    /* 执行分配时，我们会在前面预留一个 DataPoint 的空间，并在后面预留一个 DataPoint
     * 位于已分配区域之后。这些区域实际上不会保存 DataPoint，
     * 而是保存以下结构体。
     */
    struct BlockBoundary {
        size_t blockSize;
        int type;
    };
    static_assert(sizeof(BlockBoundary) <= sizeof(DataPoint), "Internal error: contact course staff.");

    /* 用于跟踪执行了向量初始化还是标量初始化的常量。 */
    const int kIsVector    = 0xA110C2;
    const int kIsScalar    = 0xA110C1;
    const int kDeallocated = 0xA110C0;

    /* 分配一个比请求多包含一个 DataPoint 的内存块。
     * 额外的 DataPoint 是哨兵，告诉我们是否使用了标量
     * 或 vector 分配/释放函数。
     */
    void* dataPointAlloc(size_t space, bool isVector) {
        /* 获取比所需更多的空间。具体来说，需要所需空间加上
         * 用于页眉和页脚。
         */
        char* fullBlock  = static_cast<char *>(operator new(2 * sizeof(DataPoint) + space));
        char* headerAddr = fullBlock;
        char* footerAddr = fullBlock + sizeof(DataPoint) + space; // 跳过标头，跳过负载
        void* result     = fullBlock + sizeof(DataPoint);

        /* 构造页眉和页脚。 */
        ::new (headerAddr) BlockBoundary{space, isVector? kIsVector : kIsScalar};
        ::new (footerAddr) BlockBoundary{space, isVector? kIsVector : kIsScalar};

        return result;
    }

    /* 释放一块内存，并检查释放方式的类型
     * 所执行的操作是正确的。
     */
    void dataPointFree(void* memory, bool isVector) {\
        /* 获取头部。它是内存块之前的 DataPoint。 */
        BlockBoundary* header = reinterpret_cast<BlockBoundary *>(((DataPoint*) memory) - 1);

        /* 确认此项具有正确类型。 */
        if (header->type == kIsVector) {
            if (!isVector) {
                emergencyAbort("You are attempting to deallocate a block of memory that you allocated with "
                               "new[] using the delete operator. This will cause memory errors. Instead, "
                               "use the delete[] operator (with square brackets)."
                               "\n"
                               "Run your program with the debugger enabled and use the call stack to see "
                               "where this error occurred.");
            }
        } else if (header->type == kIsScalar) {
            if (isVector) {
                emergencyAbort("You are attempting to deallocate a block of memory that you allocated with "
                               "new using the delete[] operator. This will cause memory errors. Instead,"
                               "use the delete operator (without square brackets)."
                               "\n"
                               "Run your program with the debugger enabled and use the call stack to see "
                               "where this error occurred.");
            }
        } else if (header->type == kDeallocated) {
            emergencyAbort("You are attempting to delete memory that you have already deleted."
                           "\n"
                           "Run your program with the debugger enabled and use the call stack to see"
                           "where this error occurred.");
            abort();
        } else {
            emergencyAbort("We detected a memory error in your program when you tried deleting "
                           "memory. This error most likely occured somewhere earlier in the "
                           "program, but we're only just seeing that something bad happened "
                           "right now when we're doing the delete operation.\n\n"
                           "Make sure that all of your array accesses are in-bounds, that you "
                           "aren't deleting the same array twice, that you aren't mixing up "
                           "delete[] and delete, etc.\n\n"
                           "To see the specific spot in your code where this error occurred, "
                           "run the program again with the debugger and backtrace.");
        }

        /* 找到页脚。 */
        BlockBoundary* footer = reinterpret_cast<BlockBoundary*>(static_cast<char *>(memory) + header->blockSize);

        /* 确认页脚与页眉匹配。 */
        if (footer->blockSize != header->blockSize || footer->type != header->type) {
            cerr << "Something went wrong when you tried to deallocate memory. Specifically, the "
                    "memory right after the end of the allocated space has been modified since when "
                    "it was created. This might indicate writing off the end of an array, or could "
                    "be due to deallocating memory that wasn't allocated."
                    "\n"
                    "Run your program with the debugger enabled and use the call stack to see "
                    "where this error occurred." << endl;
            abort();
        }

        /* 清除页眉和页脚，以防将来再次使用。 */
        header->type = footer->type = kDeallocated;
        header->blockSize = footer->blockSize = kDeallocated;

        /* 销毁页眉和页脚。 */
        header->~BlockBoundary();
        footer->~BlockBoundary();

        /* 释放内存。 */
        operator delete(header);
    }
}

/* 使捕获内存错误更容易的自定义逻辑。 */
namespace {
    const uint64_t kInitialized = 0xC5106BA6DA1ADA1A; // CS106B, A6, DATA DATA
    const uint64_t kDestroyed   = 0xC5106BA6DEADDA1A; // CS106B, A6, DEAD DATA

    void checkInitializationFlag(uint64_t value);
    void defaultConstruct(uint64_t& flag);
    void destruct(uint64_t& flag);
    void copyConstruct(DataPoint& lhs, const DataPoint& rhs);
    void moveConstruct(DataPoint& lhs, DataPoint&& rhs);
    void assign(DataPoint& lhs, DataPoint& rhs);
}

DataPoint::DataPoint() {
    /* 若代码在紧接下方的一行崩溃，
     * 这通常表示使用了无效指针——可能是
     * 未初始化的指针或空指针。请在调试器中查看回溯
     * 在调试器中查看此代码发生的位置。
     */
    checkInitializationFlag(_initializationFlag);


    defaultConstruct(_initializationFlag);
}

DataPoint::~DataPoint() {
    /* 若代码在紧接下方的一行崩溃，
     * 这通常表示使用了无效指针——可能是
     * 未初始化的指针或空指针。请在调试器中查看回溯
     * 在调试器中查看此代码发生的位置。
     */
    checkInitializationFlag(_initializationFlag);


    destruct(_initializationFlag);
}

DataPoint::DataPoint(const DataPoint& rhs) {
    /* 若代码在紧接下方的几行崩溃，
     * 这通常表示使用了无效指针——可能是
     * 未初始化的指针或空指针。请在调试器中查看回溯
     * 在调试器中查看此代码发生的位置。
     */
    checkInitializationFlag(_initializationFlag);
    checkInitializationFlag(rhs._initializationFlag);


    copyConstruct(*this, rhs);
}

DataPoint::DataPoint(DataPoint&& rhs) {
    /* 若代码在紧接下方的几行崩溃，
     * 这通常表示使用了无效指针——可能是
     * 未初始化的指针或空指针。请在调试器中查看回溯
     * 在调试器中查看此代码发生的位置。
     */
    checkInitializationFlag(_initializationFlag);
    checkInitializationFlag(rhs._initializationFlag);


    moveConstruct(*this, std::move(rhs));
}

DataPoint& DataPoint::operator=(DataPoint data) {
    /* 若代码在紧接下方的一行崩溃，
     * 这通常表示使用了无效指针——可能是
     * 未初始化的指针或空指针。请在调试器中查看回溯
     * 在调试器中查看此代码发生的位置。
     */
    checkInitializationFlag(_initializationFlag);


    assign(*this, data);
    return *this;
}

DataPoint::DataPoint(const std::string& name, double weight) : name(name), weight(weight) {
    _initializationFlag = kInitialized;
}

namespace {
    /* 空操作；这里只是为了强制复制参数。 */
    void checkInitializationFlag(uint64_t) {

    }

    void defaultConstruct(uint64_t& initializationFlag) {
        initializationFlag = kInitialized;
    }

    void destruct(uint64_t& initializationFlag) {
        if (initializationFlag != kInitialized) {
            emergencyAbort("Your program has somehow tried to destroy a DataPoint object "
                           "that wasn't first initialized. This likely indicates some sort of "
                           "memory error in your code (accessing past the end of an array, mixing "
                           "up delete[] and delete, etc.)\n\n"
                           "Run this program in the debugger and backtrace to identify the spot "
                           "in your code where this was error was triggered.");
        }
        initializationFlag = kDestroyed;
    }

    void copyConstruct(DataPoint& lhs, const DataPoint& rhs) {
        if (rhs._initializationFlag != kInitialized) {
            emergencyAbort("You have tried to make a copy of a nonexistent DataPoint. "
                           "This sometimes happens if you try reading a DataPoint past "
                           "the end of an array, or before the start of the array.\n\n"
                           "Run your program with the debugger enabled and backtrace to "
                           "see the exact spot in the code where this error was triggered.");
        }
        lhs.weight = rhs.weight;
        lhs.name   = rhs.name;
        lhs._initializationFlag = kInitialized;
    }

    void moveConstruct(DataPoint& lhs, DataPoint&& rhs) {
        if (rhs._initializationFlag != kInitialized) {
            emergencyAbort("You have tried to make a copy of a nonexistent DataPoint. "
                           "This sometimes happens if you try reading a DataPoint past "
                           "the end of an array, or before the start of the array.\n\n"
                           "Run your program with the debugger enabled and backtrace to "
                           "see the exact spot in the code where this error was triggered.");
        }
        lhs.weight = std::move(rhs.weight);
        lhs.name   = std::move(rhs.name);
        lhs._initializationFlag = kInitialized;
    }

    void assign(DataPoint& lhs, DataPoint& rhs) {
        if (lhs._initializationFlag != kInitialized) {
            emergencyAbort("You have tried to assign to a nonexistent DataPoint. "
                           "This sometimes happens if you try writing a DataPoint past "
                           "the end of an array, or before the start of the array.\n\n"
                           "Run your program with the debugger enabled and backtrace to "
                           "see the exact spot in the code where this error was triggered.");
        }
        std::swap(lhs.weight, rhs.weight);
        std::swap(lhs.name,   rhs.name);
    }
}

/* 用于读写带引号字符串的实用工具。
 *
 * TODO：一旦满足以下条件，应将此处替换为使用 std::quoted：
 * Windows 上支持 C++14。
 */
namespace {
    string quotedVersionOf(const string& source) {
        ostringstream result;
        result << '"';

        for (char ch: source) {
            /* 转义右引号。 */
            if (ch == '"') result << "\\\"";

            /* 转义斜杠。 */
            else if (ch == '\\') result << "\\\\";

            /* 输出其他所有可打印字符。 */
            else if (isgraph(ch) || ch == ' ') result << ch;

            /* 否则，对其进行转义。 */
            else {
                result << "\\x" << hex << setfill('0') << setw(2) << +static_cast<unsigned char>(ch);
            }
        }

        result << '"';
        return result.str();
    }

    /* 读取带引号的字符串。 */
    bool readQuoted(istream& in, string& out) {
        /* 读取一个字符；它必须是引号。 */
        char read;
        in >> read;

        if (!in || read != '"') return false;

        /* 持续读取，直到遇到右引号。 */
        string result;
        while (true) {
            /* 无法读取？这是个问题！ */
            if (!in.get(read)) return false;

            /* 若这是引号，则处理完成。 */
            else if (read == '"') break;

            /* 否则，如果它是斜杠，则将其视为转义符。 */
            else if (read == '\\') {
                /* 获取下一个字符以确定应执行什么操作。 */
                if (!in.get(read)) return false;

                /* 输出斜杠和引号。 */
                else if (read == '\\' || read == '"') result += read;

                /* 十六进制？读取两个字符并解码。 */
                else if (read == 'x') {
                    string hexCode;
                    in >> setw(2) >> hexCode;
                    if (!in) return false;

                    /* 将其转换为数字。 */
                    try {
                        result += static_cast<char>(stringToInteger(hexCode, 16));
                    } catch (const ErrorException& e) {
                        return false;
                    }
                }
                /* 否则，我们无法判断它是什么。 */
                else return false;
            }

            /* 否则，直接追加它。 */
            else result += read;
        }

        out = result;
        return true;
    }
}

/* 相等性比较。 */
bool operator== (const DataPoint& lhs, const DataPoint& rhs) {
    /* 若代码在紧接下方的几行崩溃，
     * 这通常表示使用了无效指针——可能是
     * 未初始化的指针或空指针。请在调试器中查看回溯
     * 在调试器中查看此代码发生的位置。
     */
    checkInitializationFlag(lhs._initializationFlag);
    checkInitializationFlag(rhs._initializationFlag);

    /* 如果代码在此处崩溃，也可能表明存在内存错误。 */
    if (lhs._initializationFlag != kInitialized || rhs._initializationFlag != kInitialized) {
        emergencyAbort("You have tried comparing a nonexistent DataPoint "
                       "against another DataPoint. This likely indicates "
                       "a memory error. Backtrace in the debugger to see "
                       "where this error occurred.");
    }

    return lhs.name == rhs.name && lhs.weight == rhs.weight;
}

/* 当两点不相等时，不等关系成立。 */
bool operator!= (const DataPoint& lhs, const DataPoint& rhs) {
    return !(lhs == rhs);
}

/* 将 DataPoint 打印到流。输出格式为
 *
 *   { "数据点名称，\"已正确转义\"", pt.weight }
 */
ostream& operator<< (ostream& out, const DataPoint& pt) {
    /* 若代码在紧接下方的一行崩溃，
     * 这通常表示使用了无效指针——可能是
     * 未初始化的指针或空指针。请在调试器中查看回溯
     * 在调试器中查看此代码发生的位置。
     */
    checkInitializationFlag(pt._initializationFlag);


    /* 若代码在这里崩溃，说明存在内存错误
     * 在代码中的某处。
     */
    if (pt._initializationFlag != kInitialized) {
        emergencyAbort("You have attempted to print a nonexistent DataPoint "
                       "object. This is probably the result of a memory error "
                       "in your code. Run this program with the debugger engaged "
                       "and backtrace to locate where this occurred.");
    }


    ostringstream builder;
    builder << "{ " << quotedVersionOf(pt.name) << ", " << pt.weight << " }";
    return out << builder.str();
}

/* 从流中读取一个 DataPoint。 */
istream& operator>> (istream& in, DataPoint& result) {
    /* 若代码在紧接下方的一行崩溃，
     * 这通常表示使用了无效指针——可能是
     * 未初始化的指针或空指针。请在调试器中查看回溯
     * 在调试器中查看此代码发生的位置。
     */
    checkInitializationFlag(result._initializationFlag);


    /* 若代码在这里崩溃，说明存在内存错误
     * 在代码中的某处。
     */
    if (result._initializationFlag != kInitialized) {
        emergencyAbort("You have attempted to read into a nonexistent DataPoint "
                       "object. This is probably the result of a memory error "
                       "in your code. Run this program with the debugger engaged "
                       "and backtrace to locate where this occurred.");
    }


    istream::sentry sentry(in);
    if (sentry) {
        /* 获取下一个字符；它应当是左花括号。 */
        char expected;
        in >> ws >> expected;
        if (!in || expected != '{') {
            in.setstate(ios::failbit);
            return in;
        }

        /* 提取字符串。 */
        DataPoint read;
        in >> ws;
        if (!readQuoted(in, read.name) || !in) {
            in.setstate(ios::failbit);
            return in;
        }

        /* 确认这里有逗号。 */
        in >> ws >> expected;
        if (!in || expected != ',') {
            in.setstate(ios::failbit);
            return in;
        }

        /* 读取权重。 */
        in >> ws >> read.weight;
        if (!in) {
            in.setstate(ios::failbit);
            return in;
        }

        /* 读取右花括号。 */
        in >> ws >> expected;
        if (!in || expected != '}') {
            in.setstate(ios::failbit);
            return in;
        }

        result = read;
    }
    return in;
}
