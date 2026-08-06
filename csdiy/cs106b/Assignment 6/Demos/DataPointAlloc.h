#pragma once

#include "GUI/MemoryDiagnostics.h"
#include <cstdint>

struct DataPoint;

/* DataPoint 的自定义分配器，旨在让以下操作更容易：
 * 查看内存错误发生的时刻。
 */
namespace DataPointUtils {
    void* dataPointAlloc(size_t size,  bool isVector);
    void  dataPointFree (void* memory, bool isVector);
}

template <> struct MemoryDiagnostics::Allocator<DataPoint> {
    static void* scalarAlloc(std::size_t bytes) {
        return DataPointUtils::dataPointAlloc(bytes, false);
    }

    static void* vectorAlloc(std::size_t bytes) {
        return DataPointUtils::dataPointAlloc(bytes, true);
    }

    static void scalarFree(void* memory) {
        DataPointUtils::dataPointFree(memory, false);
    }

    static void vectorFree(void* memory) {
        DataPointUtils::dataPointFree(memory, true);
    }
};

/* 用于更容易发现无效读取或以下问题的额外逻辑
 * 写入 DataPoint。
 */
#define ADD_SAFETY_CHECKS_TO(Type)         \
    std::uint64_t _initializationFlag;     \
    DataPoint();                           \
    DataPoint(const std::string&, double); \
    ~DataPoint();                          \
    DataPoint(const DataPoint&);           \
    DataPoint(DataPoint&&);                \
    DataPoint& operator= (DataPoint)
