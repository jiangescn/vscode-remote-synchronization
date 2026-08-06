#include "MemoryDiagnostics.h"
#include "hashmap.h"
#include "error.h"
#include <sstream>
#include <unordered_map>
#include <typeindex>
#include <cxxabi.h> // 非标准功能，但 g++ 和 clang 支持。
using namespace std;

namespace {
    /* 类型 --> 频率 */
    unordered_map<type_index, int>& allocationTable() {
        static unordered_map<type_index, int> instance;
        return instance;
    }

    /* 名称 --> 类型 */
    unordered_map<string, type_index>& lookupTable() {
        static unordered_map<string, type_index> instance;
        return instance;
    }
}

namespace MemoryDiagnostics {
    /* 将类型注入相应的表中。 */
    int registerSentinel(const std::type_info& type) {
        /* std::type_info 不保证 .name() 的结果具有可读性。
         * 使用 g++/clang 专用逻辑，将名称“反修饰”为人类可读形式
         * 格式。
         */
        int statusCode;
        auto* realName = abi::__cxa_demangle(type.name(), nullptr, nullptr, &statusCode);
        if (statusCode != 0) error("Internal error: Couldn't demangle name?");

        /* C++ 的 type_info 对象不适合作为映射的键，但 std::type_index
         * 使我们能够修复该问题。
         */
        lookupTable().insert(make_pair(string(realName), type_index(type)));

        free(realName);
        return 137; // 就是想这么做，何乐而不为？
    }

    void recordNew(const type_info& type) {
        allocationTable()[type_index(type)]++;
    }

    void recordDelete(const type_info& type) {
        allocationTable()[type_index(type)]--;
    }

    /* 清空分配表。 */
    void clear() {
        allocationTable().clear();
    }

    /* 返回所有不平衡类型的列表。 */
    map<string, int> typesWithErrors() {
        map<string, int> result;

        /* 遍历各类型，查找不匹配项。 */
        for (const auto& entry: lookupTable()) {
            int record = allocationTable()[entry.second];
            if (record != 0) {
                result[entry.first] = record;
            }
        }

        return result;
    }
}
